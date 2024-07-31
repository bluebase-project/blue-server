local explosivePresent = Action()

function explosivePresent.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	player:say("KABOOOOOOOOOOM!", TALKTYPE_POKEMON_SAY)
	player:getPosition():sendMagicEffect(CONST_ME_FIREAREA)
	item:remove()
	return true
end

explosivePresent:id(9074)
explosivePresent:register()
