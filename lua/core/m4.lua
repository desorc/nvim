vim.cmd([[let b:delimitMate_quotes = "\""]])

-- namespace
CharPair = {}

-- symbol expansion ( warinng: using 1 symbol )
CharPair.symbols = {
	{"`", "'"}
}
CharPair.symbols_len = #CharPair.symbols

-- print pair
function CharPair.SymbolsPrint(symbols_id)
	-- put before cursor
	vim.api.nvim_put({CharPair.symbols[symbols_id][1]}, "c", false, true)
	-- put after curcor
	vim.api.nvim_put({CharPair.symbols[symbols_id][2]}, "c", false, false)
end

-- event press symbol
function CharPair.Event(symbol_press, symbols_id)
	cursor_position = vim.api.nvim_win_get_cursor(0)
	buf = vim.api.nvim_buf_get_text(0, cursor_position[1]-1, cursor_position[2], cursor_position[1]-1, cursor_position[2]+1, {})
	if (symbol_press == CharPair.symbols[symbols_id][2] and buf[1] == CharPair.symbols[symbols_id][2]) then
		cursor_position[2] = cursor_position[2]+1
		vim.api.nvim_win_set_cursor(0, cursor_position)
	elseif symbol_press == CharPair.symbols[symbols_id][1] then
		CharPair.SymbolsPrint(symbols_id)
	else
		vim.api.nvim_put({symbol_press}, "c", false, true)
	end
end

-- register event press symbol
for i=1, CharPair.symbols_len do
	vim.keymap.set('i', CharPair.symbols[i][1], function() CharPair.Event(CharPair.symbols[i][1], i) end )
	-- if "begin" symbol != "end" symbol than => add "end" symbol to processing
	if CharPair.symbols[i][1] ~= CharPair.symbols[i][2] then
		vim.keymap.set('i', CharPair.symbols[i][2], function() CharPair.Event(CharPair.symbols[i][2], i) end )
	end
end
