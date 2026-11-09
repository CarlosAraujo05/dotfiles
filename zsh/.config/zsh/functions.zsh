# ==================================================
# University Study Workflow
# ==================================================

study() {
    local course="${1:u}"
    local base="$HOME/Universidade/2026-2027/semestre-1"
    local dir="$base/$course"

    if [[ -z "$course" ]]; then
        echo "Usage: study <course>"
        echo "Courses: MFES SSC ESR ASCN RAS ABD"
        return 1
    fi

    if [[ ! -d "$dir" ]]; then
        echo "Directory not found: $dir"
        return 1
    fi

    zed "$dir" || return 1

    echo "Starting 25-minute study session: $course"

    sleep 1500

    printf '\a'
    echo "Study session complete!"
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