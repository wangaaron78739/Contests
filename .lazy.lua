local contest_name = os.getenv("CONTEST_NAME")
if contest_name then
	print("Contest name from env: " .. contest_name)
	return {
		"nvim-telescope/telescope.nvim",
		keys = {
			-- add a keymap to browse plugin files
			{
				"<leader><leader>",
				function()
					require("telescope.builtin").find_files({
						search_dirs = { "./Codeforces/" .. contest_name .. "/", "./libs/" },
					})
				end,
				desc = "Find Contest File",
			},
		},
	}
end

return {}
