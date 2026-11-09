# Default editor
export EDITOR="zeditor --wait"
export VISUAL="zeditor --wait"

# Terminal
export TERMINAL="kitty"

# Locale
export LANG="en_US.UTF-8"

# FZF
export FZF_DEFAULT_OPTS="--height 40% --layout=reverse --border"

# User binaries
typeset -U path
path=("$HOME/.local/bin" "$HOME/bin" $path)
export PATH