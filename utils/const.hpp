/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_UTILS_CONST_H_
#define SRC_UTILS_CONST_H_

const uint32_t MAX_LOOTCHANCE = 100000;
const uint32_t MAX_STATICWALK = 100;

static constexpr size_t NETWORKMESSAGE_PLAYERNAME_MAXLENGTH = 30;
static constexpr int32_t NETWORKMESSAGE_MAXSIZE = 65500;

static constexpr int32_t INPUTMESSAGE_MAXSIZE = 4096;

static constexpr int32_t CHANNEL_GUILD = 0x00;
static constexpr int32_t CHANNEL_PARTY = 0x01;
static constexpr int32_t CHANNEL_PRIVATE = 0xFFFF;

// This is in miliseconds
static constexpr int32_t EVENT_IMBUEMENT_INTERVAL = 1000;
static constexpr uint8_t IMBUEMENT_MAX_TIER = 3;

static constexpr int32_t STORAGEVALUE_PROMOTION = 30018;
static constexpr int32_t STORAGEVALUE_EMOTE = 30019;
static constexpr int32_t STORAGEVALUE_PODIUM = 30020;
static constexpr int32_t STORAGEVALUE_DAILYREWARD = 14898;
static constexpr int32_t STORAGEVALUE_BESTIARYKILLCOUNT = 61305000; // Can get up to 2000 storages!
// Reserved player storage key ranges;
// [10000000 - 20000000];
static constexpr int32_t PSTRG_RESERVED_RANGE_START = 10000000;
static constexpr int32_t PSTRG_RESERVED_RANGE_SIZE = 10000000;
// [1000 - 1500];
static constexpr int32_t PSTRG_OUTFITS_RANGE_START = (PSTRG_RESERVED_RANGE_START + 1000);
static constexpr int32_t PSTRG_OUTFITS_RANGE_SIZE = 500;
// [2001 - 2011];
static constexpr int32_t PSTRG_MOUNTS_RANGE_START = (PSTRG_RESERVED_RANGE_START + 2001);
static constexpr int32_t PSTRG_MOUNTS_RANGE_SIZE = 10;
static constexpr int32_t PSTRG_MOUNTS_CURRENTMOUNT = (PSTRG_MOUNTS_RANGE_START + 10);
// [3000 - 3500];
static constexpr int32_t PSTRG_FAMILIARS_RANGE_START = (PSTRG_RESERVED_RANGE_START + 3000);
static constexpr int32_t PSTRG_FAMILIARS_RANGE_SIZE = 500;

static constexpr int32_t IMMOVABLE_ACTION_ID = 100;

#define IS_IN_KEYRANGE(key, range) \
	(key >= PSTRG_##range##_START && ((key - PSTRG_##range##_START) <= PSTRG_##range##_SIZE))

#endif // SRC_UTILS_CONST_H_
