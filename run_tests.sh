#!/bin/bash

BLOCK_TEST_FILE="./build/src/test/block_test"
GOAL_TREE_TEST_FILE="./build/src/test/goal_tree_test"
TABLE_TEST_FILE="./build/src/test/table_test"

if [[ -f "$BLOCK_TEST_FILE" ]]; then
    ./build/src/test/block_test
fi
if [[ -f "$GOAL_TREE_TEST_FILE" ]]; then
    ./build/src/test/goal_tree_test
fi
if [[ -f "$TABLE_TEST_FILE" ]]; then
    ./build/src/test/table_test
fi