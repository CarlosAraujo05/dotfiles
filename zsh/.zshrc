# ==================================================
# ZSH CONFIGURATION
# CachyOS + Niri + Kitty
# ==================================================

# Powerlevel10k instant prompt
if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
    source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

# --------------------------------------------------
# History
# --------------------------------------------------

HISTFILE="$HOME/.zsh_history"
HISTSIZE=10000
SAVEHIST=10000

setopt HIST_IGNORE_ALL_DUPS
setopt HIST_IGNORE_SPACE
setopt SHARE_HISTORY
setopt HIST_REDUCE_BLANKS
setopt EXTENDED_HISTORY

# --------------------------------------------------
# Completion
# --------------------------------------------------

setopt AUTO_CD
setopt AUTO_PUSHD
setopt PUSHD_IGNORE_DUPS

# --------------------------------------------------
# Environment
# --------------------------------------------------

[[ -f ~/.config/zsh/exports.zsh ]] &&
    source ~/.config/zsh/exports.zsh

# --------------------------------------------------
# Aliases
# --------------------------------------------------

[[ -f ~/.config/zsh/aliases.zsh ]] &&
    source ~/.config/zsh/aliases.zsh

# --------------------------------------------------
# Functions
# --------------------------------------------------

[[ -f ~/.config/zsh/functions.zsh ]] &&
    source ~/.config/zsh/functions.zsh
    
# --------------------------------------------------
# Powerlevel10k
# --------------------------------------------------

if [[ -f /usr/share/zsh-theme-powerlevel10k/powerlevel10k.zsh-theme ]]; then
    source /usr/share/zsh-theme-powerlevel10k/powerlevel10k.zsh-theme
fi

[[ -f ~/.p10k.zsh ]] && source ~/.p10k.zsh

# --------------------------------------------------
# Autosuggestions / Syntax highlighting
# --------------------------------------------------

[[ -f /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh ]] &&
    source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh

[[ -f /usr/share/zsh/plugins/zsh-history-substring-search/zsh-history-substring-search.zsh ]] &&
    source /usr/share/zsh/plugins/zsh-history-substring-search/zsh-history-substring-search.zsh

# Syntax highlighting should load last
[[ -f /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh ]] &&
    source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh