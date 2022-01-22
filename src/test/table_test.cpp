#include <gtest/gtest.h>

#include "../block.hpp"
#include "../table.hpp"

TEST(TableTest, TableTest) {
    int num_stacks = 3;
    Table table = Table(num_stacks);
    BlockPtr block_a = Block::Create("A");
    BlockPtr block_b = Block::Create("B");
    BlockPtr block_c = Block::Create("C");
    int open_table_idx = table.GetTableSpace();
    table.AddBlockToStack(block_a, open_table_idx);
}