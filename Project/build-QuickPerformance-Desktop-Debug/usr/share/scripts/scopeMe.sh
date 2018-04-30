#!/bin/bash

SCRIPT_PATH=$1

TEST1="scopeL2.sh"
TEST2="scopeL3.sh"
TEST3="scopeTEMP.sh"
TEST4="scopeENERGY.sh"

# For some reason on the test machine
# running all of these tests will not work
# the cache data were zeroed out.
# Also, doesn't seem that perfscope supports
# multiple groups in the current version 4.3.2
# because it would just error out when I tested

#sh "$SCRIPT_PATH$TEST1" "SCRIPT_PATH"&
#sh "$SCRIPT_PATH$TEST2" "SCRIPT_PATH"&
sh "$SCRIPT_PATH$TEST3" "$SCRIPT_PATH"&
sh "$SCRIPT_PATH$TEST4" "$SCRIPT_PATH"&
