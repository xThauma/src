/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "game/game.h"
#include "io/iobestiary.h"
#include "lua/functions/creatures/monster/charm_functions.hpp"

int CharmFunctions::luaCharmCreate(lua_State* L) {
	// charm(id)
	if (isNumber(L, 2)) {
		charmRune_t charmid = getNumber<charmRune_t>(L, 2);
		std::vector<Charm*> charmList = g_game().getCharmList();
		for (auto &it : charmList) {
			Charm* charm = it;
			if (charm->id == charmid) {
				pushUserdata<Charm>(L, charm);
				setMetatable(L, -1, "Charm");
				pushBoolean(L, true);
			}
		}
	}

	lua_pushnil(L);
	return 1;
}

int CharmFunctions::luaCharmName(lua_State* L) {
	// get: charm:name() set: charm:name(string)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		pushString(L, charm->name);
	} else {
		charm->name = getString(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmDescription(lua_State* L) {
	// get: charm:description() set: charm:description(string)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		pushString(L, charm->description);
	} else {
		charm->description = getString(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmType(lua_State* L) {
	// get: charm:type() set: charm:type(charm_t)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->type);
	} else {
		charm->type = getNumber<charm_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmPoints(lua_State* L) {
	// get: charm:points() set: charm:points(value)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->points);
	} else {
		charm->points = getNumber<int16_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmDamageType(lua_State* L) {
	// get: charm:damageType() set: charm:damageType(type)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->dmgtype);
	} else {
		charm->dmgtype = getNumber<CombatType_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmPercentage(lua_State* L) {
	// get: charm:percentage() set: charm:percentage(value)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->percent);
	} else {
		charm->percent = getNumber<int8_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmChance(lua_State* L) {
	// get: charm:chance() set: charm:chance(value)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->chance);
	} else {
		charm->chance = getNumber<int8_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmMessageCancel(lua_State* L) {
	// get: charm:messageCancel() set: charm:messageCancel(string)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		pushString(L, charm->cancelMsg);
	} else {
		charm->cancelMsg = getString(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmMessageServerLog(lua_State* L) {
	// get: charm:messageServerLog() set: charm:messageServerLog(string)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		pushString(L, charm->logMsg);
	} else {
		charm->logMsg = getString(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}

int CharmFunctions::luaCharmEffect(lua_State* L) {
	// get: charm:effect() set: charm:effect(value)
	Charm* charm = getUserdata<Charm>(L, 1);
	if (lua_gettop(L) == 1) {
		lua_pushnumber(L, charm->effect);
	} else {
		charm->effect = getNumber<uint8_t>(L, 2);
		pushBoolean(L, true);
	}
	return 1;
}
