#!/bin/bash
# Pacman package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo pacman -Sy
        ;;
    "upgrade")
        sudo pacman -Syu --noconfirm
        ;;
    "list")
        pacman -Q
        ;;
    "search")
        pacman -Ss "$PACKAGE"
        ;;
    "install")
        sudo pacman -S --noconfirm "$PACKAGE"
        ;;
    "remove")
        sudo pacman -R --noconfirm "$PACKAGE"
        ;;
    "info")
        pacman -Si "$PACKAGE" 2>/dev/null || pacman -Qi "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "Pacman rollback - check package cache:"
        ls -lh /var/cache/pacman/pkg/ | grep "$PACKAGE" | tail -10
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
