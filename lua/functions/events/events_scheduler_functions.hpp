/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_GAME_SCHEDUNLING_EVENTS_SCHEDULER_FUNCTIONS_HPP_
#define SRC_GAME_SCHEDUNLING_EVENTS_SCHEDULER_FUNCTIONS_HPP_

#include "lua/scripts/luascript.h"

class EventsSchedulerFunctions final : private LuaScriptInterface {
	public:
		static void init(lua_State* L) {
			registerTable(L, "EventsScheduler");

			registerMethod(L, "EventsScheduler", "getEventSLoot", EventsSchedulerFunctions::luaEventsSchedulergetEventSLoot);
			registerMethod(L, "EventsScheduler", "getEventSSkill", EventsSchedulerFunctions::luaEventsSchedulergetEventSSkill);
			registerMethod(L, "EventsScheduler", "getEventSExp", EventsSchedulerFunctions::luaEventsSchedulergetEventSExp);
			registerMethod(L, "EventsScheduler", "getSpawnMonsterSchedule", EventsSchedulerFunctions::luaEventsSchedulergetSpawnMonsterSchedule);
		}

	private:
		static int luaEventsSchedulergetEventSLoot(lua_State* L);
		static int luaEventsSchedulergetEventSSkill(lua_State* L);
		static int luaEventsSchedulergetEventSExp(lua_State* L);
		static int luaEventsSchedulergetSpawnMonsterSchedule(lua_State* L);
};

#endif // SRC_GAME_SCHEDUNLING_EVENTS_SCHEDULER_FUNCTIONS_HPP_
