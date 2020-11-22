#pragma once
#include "Client.h"
#include <thread>
#include "util/Logger.h"
#include <zlib/zlib.h>

Client::Client(Network::Connection* con) : conn(con), safe_conn(*con) {
	connected = true;
	compression = false;
}

Client::~Client() {
	safe_conn->Close();
	thr.join();

	delete conn;
}

auto Client::receivePacket() -> bool {
	auto pack = safe_conn->Recv(false);

	if (pack != nullptr) {
		receivedQueue->emplace(pack);
		return true;
	}

	return false;
}

auto Client::addPacket(Network::PacketOut* pack) -> void{
	packetQueue->emplace(pack);
}

auto Client::sendPacket() -> void {
	size_t len = packetQueue->size();

	for (int i = 0; i < len; i++) {
		size_t packetLength;
		packetLength = packetQueue->front()->buffer->GetUsedSpace() + 1;

		Network::ByteBuffer* bbuf = new Network::ByteBuffer(packetLength + 5); //512 KB

		if (compression) {
			if (packetLength > 256) {
				bbuf->WriteVarInt32(static_cast<u32>(packetLength));


				Network::ByteBuffer* bbuf2 = new Network::ByteBuffer(packetLength + 5);
				bbuf2->WriteBEUInt8(static_cast<u8>(packetQueue->front()->ID));
				for (int i = 0; i < packetQueue->front()->buffer->GetUsedSpace(); i++) {
					uint8_t temp;
					packetQueue->front()->buffer->ReadBEUInt8(temp);
					bbuf2->WriteBEUInt8(temp);
				}

				//COMPRESS DATA!
				u8 *byteBuffer = new u8[200 KiB];

				uLongf csize = compressBound(static_cast<uLong>(packetLength));
				if (csize > 200 KiB) {
					throw std::runtime_error("FATAL! COMPRESSED SIZE TOO LARGE: " + std::to_string(csize));
				}

				int32_t stat = compress2((Bytef*)byteBuffer, &csize, (const Bytef*)bbuf2->m_Buffer, static_cast<uLong>(bbuf2->GetUsedSpace()), Z_DEFAULT_COMPRESSION);

				if (stat != Z_OK) {
					throw std::runtime_error("FAILED TO COMPRESS: " + std::to_string(stat));
				}

				for (size_t i = 0; i < csize; i++) {
					bbuf->WriteBEUInt8(byteBuffer[i]);
				}

				delete[] byteBuffer;

			}
			else {
				bbuf->WriteVarInt32(0);
				bbuf->WriteBEUInt8(static_cast<u8>(packetQueue->front()->ID));

				packetQueue->front()->buffer->ResetRead();
				//Add body
				for (int i = 0; i < packetQueue->front()->buffer->GetUsedSpace(); i++) {
					uint8_t temp;
					packetQueue->front()->buffer->ReadBEUInt8(temp);
					bbuf->WriteBEUInt8(temp);
				}
			}

			Network::ByteBuffer* bbuf2 = new Network::ByteBuffer(bbuf->GetUsedSpace() + 5);
			bbuf2->WriteVarInt32(static_cast<u32>(bbuf->GetUsedSpace()));

			for (int i = 0; i < bbuf->GetUsedSpace(); i++) {
				uint8_t temp;
				bbuf->ReadBEUInt8(temp);
				bbuf2->WriteBEUInt8(temp);
			}

			//Send over socket
			safe_conn->Send(bbuf2->GetUsedSpace(), bbuf2->m_Buffer);

			delete bbuf2;
		}
		else {
			//Header
			bbuf->WriteVarInt32(static_cast<u32>(packetLength));

			bbuf->WriteBEUInt8(static_cast<u8>(packetQueue->front()->ID));

			packetQueue->front()->buffer->ResetRead();
			//Add body
			for (int i = 0; i < packetQueue->front()->buffer->GetUsedSpace(); i++) {
				uint8_t temp;
				packetQueue->front()->buffer->ReadBEUInt8(temp);
				bbuf->WriteBEUInt8(temp);
			}

			//Send over socket
			safe_conn->Send(bbuf->GetUsedSpace(), bbuf->m_Buffer);
		}

		delete bbuf;
		delete packetQueue->front()->buffer;
		delete packetQueue->front();
		packetQueue->pop();
	}
}

auto Client::handlePackets() -> void {

	int len = receivedQueue->size();
	for (size_t i = 0; i < len; i++) {
		auto packet = receivedQueue->front();
		receivedQueue->pop();

		//Validate ID

		//TODO: HANDLE


		delete packet;
	}
}


void Client::start() {
	thr = std::thread(Client::run, this);
}

auto Client::run(Client* self) -> void {

	g_Logger->info("Started new thread!");

	//Loop
	while (self->safe_conn->isAlive()) {

		//Receive up to 50 packets at once
		int packetCounter = 0;
		while (self->receivePacket() && packetCounter < 50) {
			packetCounter++;
		}

		self->handlePackets();

		self->sendPacket();

		//Sleep for a tick
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	self->connected = false;
}
