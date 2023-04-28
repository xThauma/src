/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_LUA_FUNCTIONS_CREATURES_MONSTER_LOOT_FUNCTIONS_HPP_
#define SRC_LUA_FUNCTIONS_CREATURES_MONSTER_LOOT_FUNCTIONS_HPP_

#include "lua/scripts/luascript.h"

class LootFunctions final : LuaScriptInterface {
	public:
		static void init(lua_State* L) {
			registerClass(L, "Loot", "", LootFunctions::luaCreateLoot);
			registerMetaMethod(L, "Loot", "__gc", LootFunctions::luaDeleteLoot);
			registerMethod(L, "Loot", "delete", LootFunctions::luaDeleteLoot);

			registerMethod(L, "Loot", "setId", LootFunctions::luaLootSetId);
			registerMethod(L, "Loot", "setIdFromName", LootFunctions::luaLootSetIdFromName);
			registerMethod(L, "Loot", "setMinCount", LootFunctions::luaLootSetMinCount);
			registerMethod(L, "Loot", "setMaxCount", LootFunctions::luaLootSetMaxCount);
			registerMethod(L, "Loot", "setSubType", LootFunctions::luaLootSetSubType);
			registerMethod(L, "Loot", "setChance", LootFunctions::luaLootSetChance);
			registerMethod(L, "Loot", "setActionId", LootFunctions::luaLootSetActionId);
			registerMethod(L, "Loot", "setText", LootFunctions::luaLootSetText);
			registerMethod(L, "Loot", "setNameItem", LootFunctions::luaLootSetNameItem);
			registerMethod(L, "Loot", "setArticle", LootFunctions::luaLootSetArticle);
			registerMethod(L, "Loot", "setAttack", LootFunctions::luaLootSetAttack);
			registerMethod(L, "Loot", "setDefense", LootFunctions::luaLootSetDefense);
			registerMethod(L, "Loot", "setExtraDefense", LootFunctions::luaLootSetExtraDefense);
			registerMethod(L, "Loot", "setArmor", LootFunctions::luaLootSetArmor);
			registerMethod(L, "Loot", "setShootRange", LootFunctions::luaLootSetShootRange);
			registerMethod(L, "Loot", "setHitChance", LootFunctions::luaLootSetHitChance);
			registerMethod(L, "Loot", "setUnique", LootFunctions::luaLootSetUnique);
			registerMethod(L, "Loot", "addChildLoot", LootFunctions::luaLootAddChildLoot);
		}

	private:
		static int luaCreateLoot(lua_State* L);
		static int luaDeleteLoot(lua_State* L);
		static int luaLootSetId(lua_State* L);
		static int luaLootSetIdFromName(lua_State* L);
		static int luaLootSetMinCount(lua_State* L);
		static int luaLootSetMaxCount(lua_State* L);
		static int luaLootSetSubType(lua_State* L);
		static int luaLootSetChance(lua_State* L);
		static int luaLootSetActionId(lua_State* L);
		static int luaLootSetText(lua_State* L);
		static int luaLootSetNameItem(lua_State* L);
		static int luaLootSetArticle(lua_State* L);
		static int luaLootSetAttack(lua_State* L);
		static int luaLootSetDefense(lua_State* L);
		static int luaLootSetExtraDefense(lua_State* L);
		static int luaLootSetArmor(lua_State* L);
		static int luaLootSetShootRange(lua_State* L);
		static int luaLootSetHitChance(lua_State* L);
		static int luaLootSetUnique(lua_State* L);
		static int luaLootAddChildLoot(lua_State* L);
};

#endif // SRC_LUA_FUNCTIONS_CREATURES_MONSTER_LOOT_FUNCTIONS_HPP_
