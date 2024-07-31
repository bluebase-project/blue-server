local movebook = Action()

function movebook.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local text = {}
	local moves = {}
	for _, move in ipairs(player:getInstantMoves()) do
		if move.level ~= 0 then
			if move.manapercent > 0 then
				move.mana = move.manapercent .. "%"
			end
			if move.params > 0 then
				move.words = move.words .. " para"
			end
			moves[#moves + 1] = move
		end
	end

	table.sort(moves, function(a, b) return a.level < b.level end)

	local prevLevel = -1
	for i, move in ipairs(moves) do
		if prevLevel ~= move.level then
			if i == 1 then
				text[#text == nil and 1 or #text+1] = "Moves for Level "
			else
				text[#text+1] = "\nMoves for Level "
			end
			text[#text+1] = move.level .. "\n"
			prevLevel = move.level
		end
		text[#text+1] = move.words .. " - " .. move.name .. " : " .. move.mana .. "\n"
	end

	player:showTextDialog(item:getId(), table.concat(text))
	return true
end

movebook:id(2175, 6120, 8900, 8901, 8902, 8903, 8904, 8918, 16112, 18401, 22422, 22423, 22424, 23771)
movebook:register()
