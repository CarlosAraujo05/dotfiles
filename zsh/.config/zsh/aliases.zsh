# Navigation
alias ..="cd .."
alias ...="cd ../.."
alias ....="cd ../../.."

# Listing
alias ll="ls -lah"
alias la="ls -A"
alias l="ls -CF"

# Editors
alias v="nvim"
alias z="zed"

# Git
alias gs="git status"
alias ga="git add"
alias gc="git commit"
alias gp="git push"
alias gl="git log --oneline --graph --decorate"

# Packages
alias update="sudo pacman -Syu"
alias install="sudo pacman -S"
alias remove="sudo pacman -Rns"
alias searchpkg="pacman -Ss"

# Build
alias make="make -j`nproc`)"
alias ninja="ninja -j`nproc`"
alias n="ninja"

# Utilities
alias c="clear"
alias reload="source ~/.zshrc"

# University
alias uni="cd ~/Universidade"