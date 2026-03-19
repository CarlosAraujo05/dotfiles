#!/bin/bash
set -e

DOTFILES_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
STOW_DIRS=(btop fastfetch git kitty niri nvim zsh)

install_packages() {
  if ! command -v yay &>/dev/null; then
    echo "yay nao encontrado. Instale-o primeiro."
    exit 1
  fi

  echo "Instalando pacotes..."
  yay -Syu --noconfirm \
    git \
    zsh \
    stow \
    neovim \
    kitty \
    fastfetch \
    btop \
    niri \
    rust \
    xdg-desktop-portal-gnome \
    xdg-desktop-portal-gtk \
    xwayland-satellite \
    udiskie \
    ttf-jetbrains-mono-nerd \
    pipewire \
    wireplumber \
    pavucontrol \
    blueman \
    noctalia-shell \
    yazi \
    discord
  echo "Pacotes instalados!"
}

stow_packages() {
  echo "Criando symlinks..."
  for dir in "${STOW_DIRS[@]}"; do
    if [ -d "$DOTFILES_DIR/$dir" ]; then
      echo "  Stowing $dir..."
      stow -v -t "$HOME" "$dir"
    else
      echo "  Pulando $dir (nao encontrado)"
    fi
  done
  echo "Pronto!"
}

unstow_packages() {
  echo "Removendo symlinks..."
  for dir in "${STOW_DIRS[@]}"; do
    if [ -d "$DOTFILES_DIR/$dir" ]; then
      echo "  Unstowing $dir..."
      stow -v -D -t "$HOME" "$dir"
    fi
  done
  echo "Pronto!"
}

setup_shell() {
  echo "Configurando zsh como shell padrao..."
  if ! command -v zsh &>/dev/null; then
    echo "zsh nao esta instalado. Execute './install.sh install-pkgs' primeiro."
    return
  fi

  if [ "$SHELL" != "/bin/zsh" ] && [ "$SHELL" != "/usr/bin/zsh" ]; then
    echo "Trocando shell para zsh..."
    chsh -s /bin/zsh
  fi

  if [ ! -f "$HOME/.zshrc" ]; then
    echo "Arquivo .zshrc nao encontrado. Criando link simbolico..."
    stow -t "$HOME" zsh
  fi
}

usage() {
  echo "Uso: $0 [comando]"
  echo ""
  echo "Comandos:"
  echo "  install      Verifica/instala stow e cria symlinks (padrao)"
  echo "  install-pkgs Instala todos os pacotes via yay"
  echo "  all          Instala tudo (pacotes e symlinks)"
  echo "  shell        Configura zsh como shell padrao"
  echo "  uninstall    Remove todos os symlinks"
  echo "  help         Mostra esta ajuda"
}

case "${1:-install}" in
install | i)
  stow_packages
  ;;
install-pkgs | pkgs)
  install_packages
  ;;
all | a)
  install_packages
  stow_packages
  ;;
shell | sh)
  setup_shell
  ;;
uninstall | u)
  unstow_packages
  ;;
help | h | --help | -h)
  usage
  ;;
*)
  echo "Comando desconhecido: $1"
  usage
  exit 1
  ;;
esac
