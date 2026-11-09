# ==================================================
# University Study Workflow
# ==================================================

study() {
    local course="${1:u}"
    local base="$HOME/Documents/MEI/SEM1-2627"
    local dir="$base/$course"

    if [[ -z "$course" ]]; then
        echo "Usage: study <course>"
        echo "Courses: ASCN DBA ESR MFES RAS SSC"
        return 1
    fi

    if [[ ! -d "$dir" ]]; then
        echo "Course not found: $course"
        return 1
    fi

    zed "$dir" || return 1

    echo "Studying $course for 25 minutes..."
    sleep 1500

    printf '\a'
    echo "Study session completed!"
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