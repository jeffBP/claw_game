#include <gtest/gtest.h>

#include "../block.hpp"

TEST(BlockTest, BlockTest) {
    const BlockPtr block_a = Block::Create("A");
    EXPECT_EQ(block_a->GetParent(), nullptr);
    const BlockPtr block_b = Block::Create("B", block_a);
    block_a->SetChildBlock(block_b);
    EXPECT_EQ(block_b->GetParent(), block_a);
    EXPECT_EQ(block_a->GetChildBlock(), block_b);
}