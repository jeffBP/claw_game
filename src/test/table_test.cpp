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
    table.AddBlockToStack(block_b, open_table_idx);
    EXPECT_EQ(block_b->GetParent(), block_a);
    int block_a_stack_idx = open_table_idx;
    open_table_idx = table.GetTableSpace();
    table.AddBlockToStack(block_c, open_table_idx);
    std::pair<int, int> block_a_loc = table.FindBlockOnTable("A");
    std::pair<int, int> block_b_loc = table.FindBlockOnTable("B");
    std::pair<int, int> block_c_loc = table.FindBlockOnTable("C");
    std::pair<int, int> block_d_loc = table.FindBlockOnTable("D");
    EXPECT_EQ(block_a_loc, std::make_pair(0, 0));
    EXPECT_EQ(block_b_loc, std::make_pair(0, 1));
    EXPECT_EQ(block_c_loc, std::make_pair(1, 0));
    EXPECT_EQ(block_d_loc, std::make_pair(-1, -1));
    BlockPtr removed_block = table.RemoveBlockFromStack(0);
    table.AddBlockToStack(removed_block, 1);
    block_b_loc = table.FindBlockOnTable("B");
    EXPECT_EQ(block_b_loc, std::make_pair(1, 1));
}