local condition = Condition(CONDITION_OUTFIT)
condition:setTicks(180000)

function onCastSpell(creature, variant)
	local returnValue = RETURNVALUE_NOERROR
	local pokemonType = PokemonType(variant:getString())
	if not pokemonType then
		returnValue = RETURNVALUE_CREATUREDOESNOTEXIST
	elseif not creature:hasFlag(PlayerFlag_CanIllusionAll) and not pokemonType:isIllusionable() then
		returnValue = RETURNVALUE_NOTPOSSIBLE
	end

	if returnValue ~= RETURNVALUE_NOERROR then
		creature:sendCancelMessage(returnValue)
		creature:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end

	condition:setOutfit(pokemonType:getOutfit())
	creature:addCondition(condition)
	creature:getPosition():sendMagicEffect(CONST_ME_MAGIC_BLUE)
	return true
end
