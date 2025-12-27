#!/bin/bash
# Flatpak package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        flatpak update --appstream
        ;;
    "upgrade")
        flatpak update -y
        ;;
    "list")
        flatpak list --app
        ;;
    "search")
        flatpak search "$PACKAGE"
        ;;
    "install")
        flatpak install -y "$PACKAGE"
        ;;
    "remove")
        flatpak uninstall -y "$PACKAGE"
        ;;
    "info")
        flatpak info "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "Flatpak rollback - showing commit history:"
        flatpak remote-info --log flathub "$PACKAGE" 2>/dev/null
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
