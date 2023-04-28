/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "creatures/appearance/mounts/mounts.h"
#include "game/game.h"
#include "lua/functions/creatures/player/mount_functions.hpp"

int MountFunctions::luaCreateMount(lua_State* L) {
	// Mount(id or name)
	Mount* mount;
	if (isNumber(L, 2)) {
		mount = g_game().mounts.getMountByID(getNumber<uint8_t>(L, 2));
	} else if (isString(L, 2)) {
		std::string mountName = getString(L, 2);
		mount = g_game().mounts.getMountByName(mountName);
	} else {
		mount = nullptr;
	}

	if (mount) {
		pushUserdata<Mount>(L, mount);
		setMetatable(L, -1, "Mount");
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetName(lua_State* L) {
	// mount:getName()
	Mount* mount = getUserdata<Mount>(L, 1);
	if (mount) {
		pushString(L, mount->name);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetId(lua_State* L) {
	// mount:getId()
	Mount* mount = getUserdata<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->id);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetClientId(lua_State* L) {
	// mount:getClientId()
	Mount* mount = getUserdata<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->clientId);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int MountFunctions::luaMountGetSpeed(lua_State* L) {
	// mount:getSpeed()
	Mount* mount = getUserdata<Mount>(L, 1);
	if (mount) {
		lua_pushnumber(L, mount->speed);
	} else {
		lua_pushnil(L);
	}

	return 1;
}