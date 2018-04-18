#!/bin/bash

SCRIPT_PATH=$1
echo $SCRIPT_PATH
scopeL2="scopeL2.sh"
scopeL3="scopeL3.sh"
scopeTEMP="scopeTEMP.sh"
scopeENERGY="scopeENERGY.sh"

"$SCRIPT_PATH$scopeL2"&
"$SCRIPT_PATH$scopeL3"&
"$SCRIPT_PATH$scopeTEMP"&
"$SCRIPT_PATH$scopeENERGY"&
