#!/bin/bash
# APT package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo apt update
        ;;
    "upgrade")
        sudo apt upgrade -y
        ;;
    "list")
        apt list --installed 2>/dev/null | grep -v "^Listing"
        ;;
    "search")
        apt search "$PACKAGE" 2>/dev/null | grep -E "^[a-zA-Z]"
        ;;
    "install")
        sudo apt install -y "$PACKAGE"
        ;;
    "remove")
        sudo apt remove -y "$PACKAGE"
        ;;
    "info")
        apt show "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "═══════════════════════════════════════════════════════════"
        echo "APT Rollback Options for: $PACKAGE"
        echo "═══════════════════════════════════════════════════════════"
        echo ""
        if [ -n "$PACKAGE" ]; then
            echo "Available versions of $PACKAGE:"
            apt list -a "$PACKAGE" 2>/dev/null
            echo ""
            echo "To install a specific version, use:"
            echo "  sudo apt install $PACKAGE=<version>"
            echo ""
            echo "Example: sudo apt install $PACKAGE=1.2.3-1"
        else
            echo "Please specify a package name"
        fi
        echo "═══════════════════════════════════════════════════════════"
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
