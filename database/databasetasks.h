/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_DATABASE_DATABASETASKS_H_
#define SRC_DATABASE_DATABASETASKS_H_

#include "database/database.h"
#include "utils/thread_holder_base.h"

struct DatabaseTask {
		DatabaseTask(std::string &&initQuery, std::function<void(DBResult_ptr, bool)> &&initCallback, bool initStore) :
			query(std::move(initQuery)), callback(std::move(initCallback)), store(initStore) { }

		std::string query;
		std::function<void(DBResult_ptr, bool)> callback;
		bool store;
};

class DatabaseTasks : public ThreadHolder<DatabaseTasks> {
	public:
		DatabaseTasks();

		// non-copyable
		DatabaseTasks(const DatabaseTasks &) = delete;
		void operator=(const DatabaseTasks &) = delete;

		static DatabaseTasks &getInstance() {
			// Guaranteed to be destroyed
			static DatabaseTasks instance;
			// Instantiated on first use
			return instance;
		}

		bool SetDatabaseInterface(Database* database);
		void start();
		void startThread();
		void flush();
		void shutdown();

		void addTask(std::string query, std::function<void(DBResult_ptr, bool)> callback = nullptr, bool store = false);

		void threadMain();

	private:
		void runTask(const DatabaseTask &task);

		Database* db_;
		std::thread thread;
		std::list<DatabaseTask> tasks;
		std::mutex taskLock;
		std::condition_variable taskSignal;
		std::condition_variable flushSignal;
		bool flushTasks = false;
};

constexpr auto g_databaseTasks = &DatabaseTasks::getInstance;

#endif // SRC_DATABASE_DATABASETASKS_H_
