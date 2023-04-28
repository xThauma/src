/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#ifndef SRC_ITEMS_CONTAINERS_CONTAINER_H_
#define SRC_ITEMS_CONTAINERS_CONTAINER_H_

#include "items/cylinder.h"
#include "items/item.h"
#include "items/tile.h"

class Container;
class DepotChest;
class DepotLocker;
class RewardChest;
class Reward;

class ContainerIterator {
	public:
		bool hasNext() const {
			return !over.empty();
		}

		void advance();
		Item* operator*();

	private:
		std::list<const Container*> over;
		ItemDeque::const_iterator cur;

		friend class Container;
};

class Container : public Item, public Cylinder {
	public:
		explicit Container(uint16_t type);
		Container(uint16_t type, uint16_t size, bool unlocked = true, bool pagination = false);
		explicit Container(Tile* type);
		~Container();

		// non-copyable
		Container(const Container &) = delete;
		Container &operator=(const Container &) = delete;

		Item* clone() const override final;

		Container* getContainer() override final {
			return this;
		}
		const Container* getContainer() const override final {
			return this;
		}

		Container* getRootContainer() const;

		virtual DepotLocker* getDepotLocker() {
			return nullptr;
		}
		virtual const DepotLocker* getDepotLocker() const {
			return nullptr;
		}

		virtual RewardChest* getRewardChest() {
			return nullptr;
		}
		virtual const RewardChest* getRewardChest() const {
			return nullptr;
		}

		virtual Reward* getReward() {
			return nullptr;
		}
		virtual const Reward* getReward() const {
			return nullptr;
		}
		virtual bool isInbox() const {
			return false;
		}
		virtual bool isDepotChest() const {
			return false;
		}

		Attr_ReadValue readAttr(AttrTypes_t attr, PropStream &propStream) override;
		bool unserializeItemNode(OTB::Loader &loader, const OTB::Node &node, PropStream &propStream, Position &itemPosition) override;
		std::string getContentDescription(bool oldProtocol) const;

		size_t size() const {
			return itemlist.size();
		}
		bool empty() const {
			return itemlist.empty();
		}
		uint32_t capacity() const {
			return maxSize;
		}

		ContainerIterator iterator() const;

		const ItemDeque &getItemList() const {
			return itemlist;
		}

		ItemDeque::const_reverse_iterator getReversedItems() const {
			return itemlist.rbegin();
		}
		ItemDeque::const_reverse_iterator getReversedEnd() const {
			return itemlist.rend();
		}

		bool countsToLootAnalyzerBalance();
		bool hasParent() const;
		void addItem(Item* item);
		StashContainerList getStowableItems() const;
		Item* getItemByIndex(size_t index) const;
		bool isHoldingItem(const Item* item) const;
		bool isHoldingItemWithId(const uint16_t id) const;

		uint32_t getItemHoldingCount() const;
		uint32_t getContainerHoldingCount() const;
		uint16_t getFreeSlots() const;
		uint32_t getWeight() const override final;

		bool isUnlocked() const {
			return !this->isCorpse() && unlocked;
		}
		bool hasPagination() const {
			return pagination;
		}

		// cylinder implementations
		virtual ReturnValue queryAdd(int32_t index, const Thing &thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const override;
		ReturnValue queryMaxCount(int32_t index, const Thing &thing, uint32_t count, uint32_t &maxQueryCount, uint32_t flags) const override final;
		ReturnValue queryRemove(const Thing &thing, uint32_t count, uint32_t flags, Creature* actor = nullptr) const override final;
		Cylinder* queryDestination(int32_t &index, const Thing &thing, Item** destItem, uint32_t &flags) override final;

		void addThing(Thing* thing) override final;
		void addThing(int32_t index, Thing* thing) override final;
		void addItemBack(Item* item);

		void updateThing(Thing* thing, uint16_t itemId, uint32_t count) override final;
		void replaceThing(uint32_t index, Thing* thing) override final;

		void removeThing(Thing* thing, uint32_t count) override final;

		int32_t getThingIndex(const Thing* thing) const override final;
		size_t getFirstIndex() const override final;
		size_t getLastIndex() const override final;
		uint32_t getItemTypeCount(uint16_t itemId, int32_t subType = -1) const override final;
		std::map<uint32_t, uint32_t> &getAllItemTypeCount(std::map<uint32_t, uint32_t> &countMap) const override final;
		Thing* getThing(size_t index) const override final;

		ItemVector getItems(bool recursive = false) const;

		void postAddNotification(Thing* thing, const Cylinder* oldParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;
		void postRemoveNotification(Thing* thing, const Cylinder* newParent, int32_t index, CylinderLink_t link = LINK_OWNER) override;

		void internalAddThing(Thing* thing) override final;
		void internalAddThing(uint32_t index, Thing* thing) override final;
		void startDecaying() override;
		void stopDecaying() override;

		bool isAnyKindOfRewardChest() const;
		bool isAnyKindOfRewardContainer() const;
		bool isBrowseFieldAndHoldsRewardChest() const;
		bool isInsideContainerWithId(const uint16_t id) const;

	protected:
		std::ostringstream &getContentDescription(std::ostringstream &os, bool oldProtocol) const;

		uint32_t maxSize;
		uint32_t totalWeight = 0;
		ItemDeque itemlist;
		uint32_t serializationCount = 0;

		bool unlocked;
		bool pagination;

	private:
		void onAddContainerItem(Item* item);
		void onUpdateContainerItem(uint32_t index, Item* oldItem, Item* newItem);
		void onRemoveContainerItem(uint32_t index, Item* item);

		Container* getParentContainer();
		Container* getTopParentContainer() const;
		void updateItemWeight(int32_t diff);

		friend class ContainerIterator;
		friend class IOMapSerialize;
};

#endif // SRC_ITEMS_CONTAINERS_CONTAINER_H_
