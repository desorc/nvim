vim.cmd([[let g:ycm_global_ycm_extra_conf = "~/.config/nvim/lua/core/ycm/.ycm_extra_conf.py"]])
vim.cmd([[let g:ycm_add_preview_to_completeopt = 1]])
vim.cmd([[set completeopt=popup]])
-- vim.cmd([[let g:ycm_confirm_extra_conf = 1]])
-- vim.cmd("let g:ycm_extra_conf_globlist = ['~/.config/nvim/lua/core/ycm/*']")

vim.keymap.set("n", "go", function() vim.cmd("YcmCompleter GoTo") end)
