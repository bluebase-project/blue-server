local scrollOfAscencion = Action()

function scrollOfAscencion.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	if math.random(10) > 1 then
		player:setPokemonOutfit("Demon", 30 * 10 * 1000)
	else
		player:setPokemonOutfit("Ferumbras", 30 * 10 * 1000)
	end
	item:transform(25428)
	item:getPosition():sendMagicEffect(CONST_ME_MAGIC_RED)
	item:decay()
	player:say("Magical sparks whirl around the scroll as you read it and then your appearance is changing.", TALKTYPE_POKEMON_SAY)
	return true
end

scrollOfAscencion:id(25427)
scrollOfAscencion:register()
