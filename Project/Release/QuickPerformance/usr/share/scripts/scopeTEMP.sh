#!/bin/bash

SCRIPT_PATH=$1

likwid-perfscope -C 1 -g TEMP -t 500ms "$SCRIPT_PATH/scopeForever"
