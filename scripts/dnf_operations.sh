#!/bin/bash
# DNF package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo dnf check-update
        ;;
    "upgrade")
        sudo dnf upgrade -y
        ;;
    "list")
        dnf list installed 2>/dev/null | tail -n +2
        ;;
    "search")
        dnf search "$PACKAGE" 2>/dev/null
        ;;
    "install")
        sudo dnf install -y "$PACKAGE"
        ;;
    "remove")
        sudo dnf remove -y "$PACKAGE"
        ;;
    "info")
        dnf info "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "═══════════════════════════════════════════════════════════"
        echo "DNF Rollback Options for: $PACKAGE"
        echo "═══════════════════════════════════════════════════════════"
        echo ""
        if [ -n "$PACKAGE" ]; then
            echo "Available versions:"
            dnf list --showduplicates "$PACKAGE" 2>/dev/null
            echo ""
            echo "To install a specific version:"
            echo "  sudo dnf downgrade $PACKAGE-<version>"
            echo ""
            echo "Or use: sudo dnf install $PACKAGE-<version>"
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
