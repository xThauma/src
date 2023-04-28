/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_SERVER_NETWORK_CONNECTION_CONNECTION_H_
#define SRC_SERVER_NETWORK_CONNECTION_CONNECTION_H_

#include "declarations.hpp"
#include "server/network/message/networkmessage.h"

static constexpr int32_t CONNECTION_WRITE_TIMEOUT = 30;
static constexpr int32_t CONNECTION_READ_TIMEOUT = 30;

class Protocol;
using Protocol_ptr = std::shared_ptr<Protocol>;
class OutputMessage;
using OutputMessage_ptr = std::shared_ptr<OutputMessage>;
class Connection;
using Connection_ptr = std::shared_ptr<Connection>;
using ConnectionWeak_ptr = std::weak_ptr<Connection>;
class ServiceBase;
using Service_ptr = std::shared_ptr<ServiceBase>;
class ServicePort;
using ServicePort_ptr = std::shared_ptr<ServicePort>;
using ConstServicePort_ptr = std::shared_ptr<const ServicePort>;

class ConnectionManager {
	public:
		static ConnectionManager &getInstance() {
			static ConnectionManager instance;
			return instance;
		}

		Connection_ptr createConnection(asio::io_service &io_service, ConstServicePort_ptr servicePort);
		void releaseConnection(const Connection_ptr &connection);
		void closeAll();

	private:
		ConnectionManager() = default;

		phmap::flat_hash_set<Connection_ptr> connections;
		std::mutex connectionManagerLock;
};

class Connection : public std::enable_shared_from_this<Connection> {
	public:
		// Constructor
		Connection(asio::io_service &initIoService, ConstServicePort_ptr initservicePort);
		// Constructor end

		// Destructor
		~Connection() = default;

		// Singleton - ensures we don't accidentally copy it
		Connection(const Connection &) = delete;
		Connection &operator=(const Connection &) = delete;

		void close(bool force = false);
		// Used by protocols that require server to send first
		void accept(Protocol_ptr protocolPtr);
		void accept(bool toggleParseHeader = true);

		void resumeWork();
		void send(const OutputMessage_ptr &outputMessage);

		uint32_t getIP();

	private:
		void parseProxyIdentification(const std::error_code &error);
		void parseHeader(const std::error_code &error);
		void parsePacket(const std::error_code &error);

		void onWriteOperation(const std::error_code &error);

		static void handleTimeout(ConnectionWeak_ptr connectionWeak, const std::error_code &error);

		void closeSocket();
		void internalWorker();
		void internalSend(const OutputMessage_ptr &outputMessage);

		asio::ip::tcp::socket &getSocket() {
			return socket;
		}

		NetworkMessage msg;

		asio::high_resolution_timer readTimer;
		asio::high_resolution_timer writeTimer;

		std::recursive_mutex connectionLock;

		std::list<OutputMessage_ptr> messageQueue;

		ConstServicePort_ptr service_port;
		Protocol_ptr protocol;

		asio::ip::tcp::socket socket;

		time_t timeConnected;
		uint32_t packetsSent = 0;

		std::underlying_type_t<ConnectionState_t> connectionState = CONNECTION_STATE_OPEN;
		bool receivedFirst = false;

		friend class ServicePort;
		friend class ConnectionManager;
};

#endif // SRC_SERVER_NETWORK_CONNECTION_CONNECTION_H_
