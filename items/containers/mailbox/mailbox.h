/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_ITEMS_CONTAINERS_MAILBOX_MAILBOX_H_
#define SRC_ITEMS_CONTAINERS_MAILBOX_MAILBOX_H_

#include "items/item.h"
#include "items/cylinder.h"

class Mailbox final : public Item, public Cylinder {
	public:
		explicit Mailbox(uint16_t itemId) :
			Item(itemId) { }

		Mailbox* getMailbox() override {
			return this;
		}
		const Mailbox* getMailbox() const override {
			return this;
		}

		// cylinder implementations
		ReturnValue queryAdd(int32_t index, const Thing &thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const override;
		ReturnValue queryMaxCount(int32_t index, const Thing &thing, uint32_t count, uint32_t &maxQueryCount, uint32_t flags) const override;
		ReturnValue queryRemove(const Thing &thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const override;
		Cylinder* queryDestination(int32_t &index, const Thing &thing, Item** destItem, uint32_t &flags) override;

		void addThing(Thing* thing) override;
		void addThing(int32_t index, Thing* thing) override;

		void updateThing(Thing* thing, uint16_t itemId, uint32_t count) override;
		void replaceThing(uint32_t index, Thing* thing) override;

		void removeThing(Thing* thing, uint32_t count) override;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;

	private:
		bool getReceiver(Item* item, std::string &name) const;
		bool sendItem(Item* item) const;

		static bool canSend(const Item* item);
};

#endif // SRC_ITEMS_CONTAINERS_MAILBOX_MAILBOX_H_
