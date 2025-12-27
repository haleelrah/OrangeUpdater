#!/bin/bash
# Zypper package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo zypper refresh
        ;;
    "upgrade")
        sudo zypper update -y
        ;;
    "list")
        zypper search -i 2>/dev/null
        ;;
    "search")
        zypper search "$PACKAGE" 2>/dev/null
        ;;
    "install")
        sudo zypper install -y "$PACKAGE"
        ;;
    "remove")
        sudo zypper remove -y "$PACKAGE"
        ;;
    "info")
        zypper info "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "Zypper rollback - showing available versions:"
        zypper search -s "$PACKAGE" 2>/dev/null
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
