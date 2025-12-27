#!/bin/bash
# Detect available package managers on the system

declare -A MANAGERS
MANAGERS=()

# Check for APT (Debian/Ubuntu)
if command -v apt &> /dev/null; then
    MANAGERS["apt"]="1"
fi

# Check for DNF (Fedora)
if command -v dnf &> /dev/null; then
    MANAGERS["dnf"]="1"
fi

# Check for YUM (RHEL/CentOS)
if command -v yum &> /dev/null; then
    MANAGERS["yum"]="1"
fi

# Check for Pacman (Arch)
if command -v pacman &> /dev/null; then
    MANAGERS["pacman"]="1"
fi

# Check for Flatpak
if command -v flatpak &> /dev/null; then
    MANAGERS["flatpak"]="1"
fi

# Check for Snap
if command -v snap &> /dev/null; then
    MANAGERS["snap"]="1"
fi

# Check for Zypper (openSUSE)
if command -v zypper &> /dev/null; then
    MANAGERS["zypper"]="1"
fi

# Check for AppImage (check if appimagelauncher or similar is installed)
if [ -d "$HOME/.local/share/applications" ] && ls "$HOME"/*.AppImage &> /dev/null; then
    MANAGERS["appimage"]="1"
fi

# Output detected managers (one per line)
for manager in "${!MANAGERS[@]}"; do
    echo "$manager"
done
