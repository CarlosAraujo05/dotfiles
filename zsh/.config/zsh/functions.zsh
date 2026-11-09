# ==================================================
# University Study Workflow
# ==================================================

study() {
  local course="${1:u}"
  local minutes="${2:-25}"
  local root="$HOME/Documents/MEI"
  local course_dir="$root/SEM1-2627/$course"
  local notes_dir="$root/Knowledge/01-Cadeiras/$course"

  case "$course" in
    ASCN|DBA|ESR|MFES|RAS|SSC) ;;
    *)
      echo "Uso: study <ascn|dba|esr|mfes|ras|ssc> [minutos]"
      return 1
      ;;
  esac

  if [[ ! -d "$course_dir" || ! -d "$notes_dir" ]]; then
    echo "Erro: diretório da cadeira não encontrado."
    return 1
  fi

  if [[ ! "$minutes" =~ ^[0-9]+$ ]] || (( minutes < 1 )); then
    echo "Erro: duração inválida."
    return 1
  fi

  echo "📚 $course — $minutes minutos"

  if command -v zeditor >/dev/null 2>&1; then
    zeditor "$course_dir" >/dev/null 2>&1 &!
  else
    echo "Aviso: zeditor não encontrado."
  fi

  local uri="obsidian://open?vault=Knowledge&file=01-Cadeiras%2F${course}"

  if command -v xdg-open >/dev/null 2>&1; then
    xdg-open "$uri" >/dev/null 2>&1 &!
  fi

  echo "⏳ Sessão iniciada. Ctrl+C para cancelar."
  sleep "$((minutes * 60))" || return 130

  printf '\a'
  echo "✅ Sessão de $course concluída!"
}

# Create and enter a directory
mkcd() {
    mkdir -p -- "$1" && cd -- "$1"
}

# Git repository root
croot() {
    local root
    root=$(git rev-parse --show-toplevel 2>/dev/null) || return 1
    cd "$root"
}