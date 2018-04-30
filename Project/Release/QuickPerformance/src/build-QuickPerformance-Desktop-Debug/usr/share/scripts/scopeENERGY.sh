#!/bin/bash

SCRIPT_PATH=$1
SCRIPT="scopeForever"
echo "$SCRIPT_PATH$SCRIPT"
likwid-perfscope -C 1 -g ENERGY -t 500ms "$SCRIPT_PATH$SCRIPT"
