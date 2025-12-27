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
        echo "═══════════════════════════════════════════════════════════"
        echo "Flatpak Rollback Options for: $PACKAGE"
        echo "═══════════════════════════════════════════════════════════"
        echo ""
        if [ -n "$PACKAGE" ]; then
            echo "Current version:"
            flatpak info "$PACKAGE" 2>/dev/null | grep -E "(ID|Version|Branch|Commit)"
            echo ""
            echo "Commit history (use commit hash to rollback):"
            flatpak remote-info --log flathub "$PACKAGE" 2>/dev/null | head -20
            echo ""
            echo "To rollback to a specific commit:"
            echo "  flatpak update --commit=<commit-hash> $PACKAGE"
        else
            echo "Please specify a flatpak package name"
        fi
        echo "═══════════════════════════════════════════════════════════"
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
