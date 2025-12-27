#!/bin/bash
# Snap package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo snap refresh --list
        ;;
    "upgrade")
        sudo snap refresh
        ;;
    "list")
        snap list
        ;;
    "search")
        snap find "$PACKAGE"
        ;;
    "install")
        sudo snap install "$PACKAGE"
        ;;
    "remove")
        sudo snap remove "$PACKAGE"
        ;;
    "info")
        snap info "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "═══════════════════════════════════════════════════════════"
        echo "Snap Rollback for: $PACKAGE"
        echo "═══════════════════════════════════════════════════════════"
        echo ""
        if [ -n "$PACKAGE" ]; then
            echo "Current snap info:"
            snap list "$PACKAGE" 2>/dev/null
            echo ""
            echo "Attempting to revert to previous version..."
            echo ""
            sudo snap revert "$PACKAGE" 2>&1
            RESULT=$?
            echo ""
            if [ $RESULT -eq 0 ]; then
                echo "✓ Successfully reverted $PACKAGE to previous version"
                echo ""
                echo "Updated snap info:"
                snap list "$PACKAGE" 2>/dev/null
            else
                echo "✗ Could not revert $PACKAGE"
                echo "This may mean there is no previous version to revert to."
            fi
        else
            echo "Please specify a snap package name"
        fi
        echo "═══════════════════════════════════════════════════════════"
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
