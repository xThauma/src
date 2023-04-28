/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_GAME_SCHEDULING_TASKS_H_
#define SRC_GAME_SCHEDULING_TASKS_H_

#include "utils/thread_holder_base.h"

const int DISPATCHER_TASK_EXPIRATION = 2000;
const auto SYSTEM_TIME_ZERO = std::chrono::system_clock::time_point(std::chrono::milliseconds(0));

class Task {
	public:
		// DO NOT allocate this class on the stack
		explicit Task(std::function<void(void)> &&f) :
			func(std::move(f)) { }
		Task(uint32_t ms, std::function<void(void)> &&f) :
			expiration(std::chrono::system_clock::now() + std::chrono::milliseconds(ms)), func(std::move(f)) { }

		virtual ~Task() = default;
		void operator()() {
			func();
		}

		void setDontExpire() {
			expiration = SYSTEM_TIME_ZERO;
		}

		bool hasExpired() const {
			if (expiration == SYSTEM_TIME_ZERO) {
				return false;
			}
			return expiration < std::chrono::system_clock::now();
		}

	protected:
		std::chrono::system_clock::time_point expiration = SYSTEM_TIME_ZERO;

	private:
		// Expiration has another meaning for scheduler tasks,
		// then it is the time the task should be added to the
		// dispatcher
		std::function<void(void)> func;
};

Task* createTask(std::function<void(void)> f);
Task* createTask(uint32_t expiration, std::function<void(void)> f);

class Dispatcher : public ThreadHolder<Dispatcher> {
	public:
		Dispatcher() = default;

		Dispatcher(const Dispatcher &) = delete;
		void operator=(const Dispatcher &) = delete;

		static Dispatcher &getInstance() {
			// Guaranteed to be destroyed
			static Dispatcher instance;
			// Instantiated on first use
			return instance;
		}

		void addTask(Task* task, bool push_front = false);

		void shutdown();

		uint64_t getDispatcherCycle() const {
			return dispatcherCycle;
		}

		void threadMain();

	private:
		std::mutex taskLock;
		std::condition_variable taskSignal;

		std::list<Task*> taskList;
		uint64_t dispatcherCycle = 0;
};

constexpr auto g_dispatcher = &Dispatcher::getInstance;

#endif // SRC_GAME_SCHEDULING_TASKS_H_
