// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_MOVES_H_D78A7CCB7080406E8CAA6B1D31D3DA71
#define FS_MOVES_H_D78A7CCB7080406E8CAA6B1D31D3DA71

#include "luascript.h"
#include "player.h"
#include "actions.h"
#include "talkaction.h"
#include "baseevents.h"

class InstantMove;
class RuneMove;
class Move;

using VocMoveMap = std::map<uint16_t, bool>;
using InstantMove_ptr = std::unique_ptr<InstantMove>;
using RuneMove_ptr = std::unique_ptr<RuneMove>;

class Moves final : public BaseEvents
{
	public:
		Moves();
		~Moves();

		// non-copyable
		Moves(const Moves&) = delete;
		Moves& operator=(const Moves&) = delete;

		Move* getMoveByName(const std::string& name);
		RuneMove* getRuneMove(uint32_t id);
		RuneMove* getRuneMoveByName(const std::string& name);

		InstantMove* getInstantMove(const std::string& words);
		InstantMove* getInstantMoveByName(const std::string& name);

		TalkActionResult_t playerSayMove(Player* player, std::string& words);

		static Position getCasterPosition(Creature* creature, Direction dir);
		std::string getScriptBaseName() const override;

		const std::map<std::string, InstantMove>& getInstantMoves() const {
			return instants;
		};

		void clearMaps(bool fromLua);
		void clear(bool fromLua) override final;
		bool registerInstantLuaEvent(InstantMove* event);
		bool registerRuneLuaEvent(RuneMove* event);

	private:
		LuaScriptInterface& getScriptInterface() override;
		Event_ptr getEvent(const std::string& nodeName) override;
		bool registerEvent(Event_ptr event, const pugi::xml_node& node) override;

		std::map<uint16_t, RuneMove> runes;
		std::map<std::string, InstantMove> instants;

		friend class CombatMove;
		LuaScriptInterface scriptInterface { "Move Interface" };
};

class BaseMove
{
	public:
		constexpr BaseMove() = default;
		virtual ~BaseMove() = default;

		virtual bool castMove(Creature* creature) = 0;
		virtual bool castMove(Creature* creature, Creature* target) = 0;
};

class CombatMove final : public Event, public BaseMove
{
	public:
		CombatMove(Combat_ptr combat, bool needTarget, bool needDirection);

		// non-copyable
		CombatMove(const CombatMove&) = delete;
		CombatMove& operator=(const CombatMove&) = delete;

		bool castMove(Creature* creature) override;
		bool castMove(Creature* creature, Creature* target) override;
		bool configureEvent(const pugi::xml_node&) override {
			return true;
		}

		//scripting
		bool executeCastMove(Creature* creature, const LuaVariant& var);

		bool loadScriptCombat();
		Combat_ptr getCombat() {
			return combat;
		}

	private:
		std::string getScriptEventName() const override {
			return "onCastMove";
		}

		Combat_ptr combat;

		bool needDirection;
		bool needTarget;
};

class Move : public BaseMove
{
	public:
		Move() = default;

		bool configureMove(const pugi::xml_node& node);
		const std::string& getName() const {
			return name;
		}
		void setName(std::string n) {
			name = n;
		}
		uint8_t getId() const {
			return moveId;
		}
		void setId(uint8_t id) {
			moveId = id;
		}

		void postCastMove(Player* player, bool finishedCast = true, bool payCost = true) const;
		static void postCastMove(Player* player, uint32_t manaCost, uint32_t soulCost);

		uint32_t getManaCost(const Player* player) const;
		uint32_t getSoulCost() const {
			return soul;
		}
		void setSoulCost(uint32_t s) {
			soul = s;
		}
		uint32_t getLevel() const {
			return level;
		}
		void setLevel(uint32_t lvl) {
			level = lvl;
		}
		uint32_t getMagicLevel() const {
			return magLevel;
		}
		void setMagicLevel(uint32_t lvl) {
			magLevel = lvl;
		}
		uint32_t getMana() const {
			return mana;
		}
		void setMana(uint32_t m) {
			mana = m;
		}
		uint32_t getManaPercent() const {
			return manaPercent;
		}
		void setManaPercent(uint32_t m) {
			manaPercent = m;
		}
		bool isPremium() const {
			return premium;
		}
		void setPremium(bool p) {
			premium = p;
		}
		bool isEnabled() const {
			return enabled;
		}
		void setEnabled(bool e) {
			enabled = e;
		}

		virtual bool isInstant() const = 0;
		bool isLearnable() const {
			return learnable;
		}
		void setLearnable(bool l) {
			learnable = l;
		}

		const VocMoveMap& getVocMap() const {
			return vocMoveMap;
		}
		void addVocMap(uint16_t n, bool b) {
			vocMoveMap[n] = b;
		}

		const MoveGroup_t getGroup() const {
			return group;
		}
		void setGroup(MoveGroup_t g) {
			group = g;
		}
		const MoveGroup_t getSecondaryGroup() const {
			return secondaryGroup;
		}
		void setSecondaryGroup(MoveGroup_t g) {
			secondaryGroup = g;
		}

		uint32_t getCooldown() const {
			return cooldown;
		}
		void setCooldown(uint32_t cd) {
			cooldown = cd;
		}
		uint32_t getSecondaryCooldown() const {
			return secondaryGroupCooldown;
		}
		void setSecondaryCooldown(uint32_t cd) {
			secondaryGroupCooldown = cd;
		}
		uint32_t getGroupCooldown() const {
			return groupCooldown;
		}
		void setGroupCooldown(uint32_t cd) {
			groupCooldown = cd;
		}

		int32_t getRange() const {
			return range;
		}
		void setRange(int32_t r) {
			range = r;
		}

		bool getNeedTarget() const {
			return needTarget;
		}
		void setNeedTarget(bool n) {
			needTarget = n;
		}
		bool getNeedWeapon() const {
			return needWeapon;
		}
		void setNeedWeapon(bool n) {
			needWeapon = n;
		}
		bool getNeedLearn() const {
			return learnable;
		}
		void setNeedLearn(bool n) {
			learnable = n;
		}
		bool getSelfTarget() const {
			return selfTarget;
		}
		void setSelfTarget(bool s) {
			selfTarget = s;
		}
		bool getBlockingSolid() const {
			return blockingSolid;
		}
		void setBlockingSolid(bool b) {
			blockingSolid = b;
		}
		bool getBlockingCreature() const {
			return blockingCreature;
		}
		void setBlockingCreature(bool b) {
			blockingCreature = b;
		}
		bool getAggressive() const {
			return aggressive;
		}
		void setAggressive(bool a) {
			aggressive = a;
		}
		bool getPzLock() const {
			return pzLock;
		}
		void setPzLock(bool pzLock) {
			this->pzLock = pzLock;
		}

		MoveType_t moveType = MOVE_UNDEFINED;

	protected:
		bool playerMoveCheck(Player* player) const;
		bool playerInstantMoveCheck(Player* player, const Position& toPos);
		bool playerRuneMoveCheck(Player* player, const Position& toPos);

		VocMoveMap vocMoveMap;

		MoveGroup_t group = MOVEGROUP_NONE;
		MoveGroup_t secondaryGroup = MOVEGROUP_NONE;

		uint32_t cooldown = 1000;
		uint32_t groupCooldown = 1000;
		uint32_t secondaryGroupCooldown = 0;
		uint32_t level = 0;
		uint32_t magLevel = 0;
		int32_t range = -1;

		uint8_t moveId = 0;

		bool selfTarget = false;
		bool needTarget = false;

	private:
		uint32_t mana = 0;
		uint32_t manaPercent = 0;
		uint32_t soul = 0;

		bool needWeapon = false;
		bool blockingSolid = false;
		bool blockingCreature = false;
		bool aggressive = true;
		bool pzLock = false;
		bool learnable = false;
		bool enabled = true;
		bool premium = false;

		std::string name;
};

class InstantMove final : public TalkAction, public Move
{
	public:
		explicit InstantMove(LuaScriptInterface* interface) : TalkAction(interface) {}

		bool configureEvent(const pugi::xml_node& node) override;

		virtual bool playerCastInstant(Player* player, std::string& param);

		bool castMove(Creature* creature) override;
		bool castMove(Creature* creature, Creature* target) override;

		//scripting
		bool executeCastMove(Creature* creature, const LuaVariant& var);

		bool isInstant() const override {
			return true;
		}
		bool getHasParam() const {
			return hasParam;
		}
		void setHasParam(bool p) {
			hasParam = p;
		}
		bool getHasPlayerNameParam() const {
			return hasPlayerNameParam;
		}
		void setHasPlayerNameParam(bool p) {
			hasPlayerNameParam = p;
		}
		bool getNeedDirection() const {
			return needDirection;
		}
		void setNeedDirection(bool n) {
			needDirection = n;
		}
		bool getNeedCasterTargetOrDirection() const {
			return casterTargetOrDirection;
		}
		void setNeedCasterTargetOrDirection(bool d) {
			casterTargetOrDirection = d;
		}
		bool getBlockWalls() const {
			return checkLineOfSight;
		}
		void setBlockWalls(bool w) {
			checkLineOfSight = w;
		}
		bool canCast(const Player* player) const;
		bool canThrowMove(const Creature* creature, const Creature* target) const;

	private:
		std::string getScriptEventName() const override;

		bool internalCastMove(Creature* creature, const LuaVariant& var);

		bool needDirection = false;
		bool hasParam = false;
		bool hasPlayerNameParam = false;
		bool checkLineOfSight = true;
		bool casterTargetOrDirection = false;
};

class RuneMove final : public Action, public Move
{
	public:
		explicit RuneMove(LuaScriptInterface* interface) : Action(interface) {}

		bool configureEvent(const pugi::xml_node& node) override;

		ReturnValue canExecuteAction(const Player* player, const Position& toPos) override;
		bool hasOwnErrorHandler() override {
			return true;
		}
		Thing* getTarget(Player*, Creature* targetCreature, const Position&, uint8_t) const override {
			return targetCreature;
		}

		bool executeUse(Player* player, Item* item, const Position& fromPosition, Thing* target, const Position& toPosition, bool isHotkey) override;

		bool castMove(Creature* creature) override;
		bool castMove(Creature* creature, Creature* target) override;

		//scripting
		bool executeCastMove(Creature* creature, const LuaVariant& var, bool isHotkey);

		bool isInstant() const override {
			return false;
		}
		uint16_t getRuneItemId() const {
			return runeId;
		}
		void setRuneItemId(uint16_t i) {
			runeId = i;
		}
		uint32_t getCharges() const {
			return charges;
		}
		void setCharges(uint32_t c) {
			if (c > 0) {
				hasCharges = true;
			}
			charges = c;
		}

	private:
		std::string getScriptEventName() const override;

		bool internalCastMove(Creature* creature, const LuaVariant& var, bool isHotkey);

		uint16_t runeId = 0;
		uint32_t charges = 0;
		bool hasCharges = false;
};

#endif
