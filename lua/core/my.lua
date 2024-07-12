vim.cmd("set number")
vim.cmd("set relativenumber")

-- nvim-tree --
local nvim_tree = require "nvim-tree.api"
vim.keymap.set('n', 't', nvim_tree.tree.open)
vim.keymap.set('n', 'T', nvim_tree.tree.close)
