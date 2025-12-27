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
        echo "APT rollback requires specific version: apt install package=version"
        if [ -n "$PACKAGE" ]; then
            apt list -a "$PACKAGE" 2>/dev/null
        fi
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
