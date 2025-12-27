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
        dnf list installed 2>/dev/null | grep -v "^Installed Packages"
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
        echo "DNF rollback - showing available versions:"
        dnf list --showduplicates "$PACKAGE" 2>/dev/null
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
