# Enable Powerlevel10k instant prompt. Should stay close to the top of ~/.zshrc.
# Initialization code that may require console input (password prompts, [y/n]
# confirmations, etc.) must go above this block; everything else may go below.
if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
  source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

# ===============================
# OH MY ZSH BASE
# ===============================

export ZSH="$HOME/.oh-my-zsh"

ZSH_THEME="powerlevel10k/powerlevel10k"

plugins=(
  git
  zsh-autosuggestions
  zsh-syntax-highlighting
  z
  fzf
  sudo
  colored-man-pages
  history-substring-search
)

source $ZSH/oh-my-zsh.sh


# ===============================
# HISTORY CONFIG
# ===============================

HISTSIZE=10000
SAVEHIST=10000
HISTFILE=~/.zsh_history

setopt SHARE_HISTORY
setopt HIST_IGNORE_ALL_DUPS
setopt HIST_REDUCE_BLANKS
setopt INC_APPEND_HISTORY


# ===============================
# BETTER COMPLETION
# ===============================

autoload -Uz compinit
compinit


# ===============================
# ZOXIDE (better cd)
# ===============================

if command -v zoxide >/dev/null 2>&1; then
  eval "$(zoxide init zsh)"
fi


# ===============================
# ALIASES
# ===============================
alias cd='z'
alias ls='eza --icons'
alias ll='eza -lah --icons --group-directories-first'
alias la='eza -a --icons'
alias l='eza --icons --group-directories-first'
alias tree='eza --icons --tree'
alias lg='eza -lah --icons --git'
alias gs='git status'
alias gc='git commit'
alias gp='git push'
alias gl='git pull'
alias v='nvim'
alias update='sudo pacman -Syu || sudo apt update && sudo apt upgrade'
alias knime="GDK_BACKEND=x11 /home/carlos/Documentos/ADI/knime_5.9.0/knime"
alias startvm='VBoxManage startvm --type headless'
alias runningvms='VBoxManage list runningvms'


stopvm() {
  VBoxManage controlvm "$1" poweroff
}
# ===============================
# EDITOR DEFAULT
# ===============================

export EDITOR=nvim
export VISUAL=nvim


# ===============================
# POWERLEVEL10K INSTANT PROMPT
# (keep at bottom)
# ===============================

[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh
export PATH="/home/carlos/.local/bin:$PATH"
export PATH="/home/carlos/.local/bin:$PATH"
