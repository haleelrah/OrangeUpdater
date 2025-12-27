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
        echo "Snap rollback for $PACKAGE:"
        sudo snap revert "$PACKAGE"
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
