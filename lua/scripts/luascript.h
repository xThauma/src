/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_LUA_SCRIPTS_LUASCRIPT_H_
#define SRC_LUA_SCRIPTS_LUASCRIPT_H_

#include "lua/functions/lua_functions_loader.hpp"
#include "lua/scripts/script_environment.hpp"

class LuaScriptInterface : public LuaFunctionsLoader {
	public:
		explicit LuaScriptInterface(std::string interfaceName);
		virtual ~LuaScriptInterface();

		// non-copyable
		LuaScriptInterface(const LuaScriptInterface &) = delete;
		LuaScriptInterface &operator=(const LuaScriptInterface &) = delete;

		virtual bool initState();
		bool reInitState();

		int32_t loadFile(const std::string &file, const std::string &scriptName);

		const std::string &getFileById(int32_t scriptId);
		int32_t getEvent(const std::string &eventName);
		int32_t getEvent();
		int32_t getMetaEvent(const std::string &globalName, const std::string &eventName);

		const std::string &getInterfaceName() const {
			return interfaceName;
		}
		const std::string &getLastLuaError() const {
			return lastLuaError;
		}
		const std::string &getLoadingFile() const {
			return loadingFile;
		}

		const std::string &getLoadingScriptName() const {
			// If scripty name is empty, return warning informing
			if (loadedScriptName.empty()) {
				SPDLOG_WARN("[LuaScriptInterface::getLoadingScriptName] - Script name is empty");
			}

			return loadedScriptName;
		}
		void setLoadingScriptName(const std::string &scriptName) {
			loadedScriptName = scriptName;
		}

		lua_State* getLuaState() const {
			return luaState;
		}

		bool pushFunction(int32_t functionId);

		bool callFunction(int params);
		void callVoidFunction(int params);

		std::string getStackTrace(const std::string &error_desc);

	protected:
		virtual bool closeState();
		lua_State* luaState = nullptr;
		int32_t eventTableRef = -1;
		int32_t runningEventId = EVENT_ID_USER;
		std::map<int32_t, std::string> cacheFiles;

	private:
		std::string lastLuaError;
		std::string interfaceName;
		std::string loadingFile;
		std::string loadedScriptName;
};

#endif // SRC_LUA_SCRIPTS_LUASCRIPT_H_
