#!/bin/bash
# YUM package manager operations

OPERATION=$1
PACKAGE=$2

case "$OPERATION" in
    "update")
        sudo yum check-update
        ;;
    "upgrade")
        sudo yum update -y
        ;;
    "list")
        yum list installed 2>/dev/null
        ;;
    "search")
        yum search "$PACKAGE" 2>/dev/null
        ;;
    "install")
        sudo yum install -y "$PACKAGE"
        ;;
    "remove")
        sudo yum remove -y "$PACKAGE"
        ;;
    "info")
        yum info "$PACKAGE" 2>/dev/null
        ;;
    "rollback")
        echo "YUM rollback - showing available versions:"
        yum list --showduplicates "$PACKAGE" 2>/dev/null
        ;;
    *)
        echo "Unknown operation: $OPERATION"
        exit 1
        ;;
esac
