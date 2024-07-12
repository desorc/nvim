-- !!! DEPEND !!! --
-- honza/vim-snippets



-- Trigger configuration. You need to change this to something other than <tab> if you use one of the following:
-- - https://github.com/Valloric/YouCompleteMe
-- - https://github.com/nvim-lua/completion-nvim
vim.g.UltiSnipsExpandTrigger = "<c-l>"
vim.g.UltiSnipsJumpForwardTrigger = "<c-j>"
vim.g.UltiSnipsJumpBackwardTrigger = "<c-k>"

-- vim.g.UltiSnipsExpandTrigger = "<tab>"
-- vim.g.UltiSnipsListSnippets = "<c-tab>"
-- vim.g.UltiSnipsJumpForwardTrigger = "<c-j>"
-- vim.g.UltiSnipsJumpBackwardTrigger = "<c-k>"

-- If you want :UltiSnipsEdit to split your window.
vim.g.UltiSnipsEditSplit = "vertical"

-- SNIPPETS
--g:

-- vim.cmd([[let g:UltiSnipsSnippetDirectories='/home/batya/.local/share/nvim/lazy/vim-snippets/UltiSnips']])
-- vim.g.UltiSnipsSnippetDirectories= {'~/.local/share/nvim/lazy/vim-snippets/UltiSnips'}
vim.g.UltiSnipsSnippetDirectories= {'~/.local/share/nvim/lazy/vim-snippets'}
