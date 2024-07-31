local mType = Game.createPokemonType("example")
local pokemon = {}
pokemon.description = "an example"
pokemon.experience = 1
pokemon.outfit = {
	lookType = 37
}

pokemon.health = 99200
pokemon.maxHealth = pokemon.health
pokemon.race = "fire"
pokemon.corpse = 5995
pokemon.speed = 280
pokemon.maxSummons = 2

pokemon.changeTarget = {
	interval = 4*1000,
	chance = 20
}

pokemon.flags = {
	summonable = false,
	attackable = true,
	hostile = true,
	challengeable = true,
	convinceable = false,
	ignoreSpawnBlock = false,
	illusionable = false,
	canPushItems = true,
	canPushCreatures = true,
	targetDistance = 1,
	staticAttackChance = 70
}

pokemon.summons = {
	{name = "demon", chance = 10, interval = 2*1000}
}

pokemon.voices = {
	interval = 5000,
	chance = 10,
	{text = "I'm an example", yell = false},
	{text = "You shall bow", yell = false}
}

pokemon.loot = {
	{id = "gold coin", chance = 60000, maxCount = 100},
	{id = 1987, chance = 60000, -- bag
		child = {
			{id = "platinum coin", chance = 60000, maxCount = 100},
			{id = "crystal coin", chance = 60000, maxCount = 100}
		}
	}
}

pokemon.attacks = {
	{name = "melee", attack = 130, skill = 70, effect = CONST_ME_DRAWBLOOD, interval = 2*1000},
	{name = "energy strike", range = 1, chance = 10, interval = 2*1000, minDamage = -210, maxDamage = -300, target = true},
	{name = "combat", type = COMBAT_MANADRAIN, chance = 10, interval = 2*1000, minDamage = 0, maxDamage = -120, target = true, range = 7, effect = CONST_ME_MAGIC_BLUE},
	{name = "combat", type = COMBAT_FIREDAMAGE, chance = 20, interval = 2*1000, minDamage = -150, maxDamage = -250, radius = 1, target = true, effect = CONST_ME_FIREAREA, shootEffect = CONST_ANI_FIRE},
	{name = "speed", chance = 15, interval = 2*1000, speed = -700, radius = 1, target = true, duration = 30*1000, effect = CONST_ME_MAGIC_RED},
	{name = "firefield", chance = 10, interval = 2*1000, range = 7, radius = 1, target = true, shootEffect = CONST_ANI_FIRE},
	{name = "combat", type = COMBAT_LIFEDRAIN, chance = 10, interval = 2*1000, length = 8, spread = 0, minDamage = -300, maxDamage = -490, effect = CONST_ME_PURPLEENERGY}
}

pokemon.defenses = {
	defense = 55,
	armor = 55,
	{name = "combat", type = COMBAT_HEALING, chance = 15, interval = 2*1000, minDamage = 180, maxDamage = 250, effect = CONST_ME_MAGIC_BLUE},
	{name = "speed", chance = 15, interval = 2*1000, speed = 320, effect = CONST_ME_MAGIC_RED}
}

pokemon.elements = {
	{type = COMBAT_PHYSICALDAMAGE, percent = 30},
	{type = COMBAT_DEATHDAMAGE, percent = 30},
	{type = COMBAT_ENERGYDAMAGE, percent = 50},
	{type = COMBAT_EARTHDAMAGE, percent = 40},
	{type = COMBAT_ICEDAMAGE, percent = -10},
	{type = COMBAT_HOLYDAMAGE, percent = -10}
}

pokemon.immunities = {
	{type = "fire", combat = true, condition = true},
	{type = "drown", condition = true},
	{type = "lifedrain", combat = true},
	{type = "paralyze", condition = true},
	{type = "invisible", condition = true}
}

mType.onThink = function(pokemon, interval)
	print("I'm thinking")
end

mType.onAppear = function(pokemon, creature)
	if pokemon:getId() == creature:getId() then
		print(pokemon:getId(), creature:getId())
	end
end

mType.onDisappear = function(pokemon, creature)
	if pokemon:getId() == creature:getId() then
		print(pokemon:getId(), creature:getId())
	end
end

mType.onMove = function(pokemon, creature, fromPosition, toPosition)
	if pokemon:getId() == creature:getId() then
		print(pokemon:getId(), creature:getId(), fromPosition, toPosition)
	end
end

mType.onSay = function(pokemon, creature, type, message)
	print(pokemon:getId(), creature:getId(), type, message)
end

mType:register(pokemon)
