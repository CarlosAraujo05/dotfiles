return {
    "mikavilpas/yazi.nvim",
    event = "VeryLazy",
    keys = {
        {
            "<leader>-",
            function()
                require("yazi").yazi()
            end,
            desc = "Abrir o Yazi",
        },
    },
    opts = {
        open_for_directories = false,
    },
}
