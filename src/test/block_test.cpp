#include <gtest/gtest.h>

#include "../block.hpp"

TEST(BlockTest, BlockTest) {
    const BlockPtr block_a = Block::Create("A");
    EXPECT_EQ(block_a->GetName(), "A");
    EXPECT_EQ(block_a->GetParent(), nullptr);
    const BlockPtr block_b = Block::Create("B", block_a);
    block_a->SetChildBlock(block_b);
    EXPECT_EQ(block_b->GetParent(), block_a);
    EXPECT_EQ(block_a->GetChildBlock(), block_b);
    block_a->PopChildBlock();
    EXPECT_EQ(block_a->GetChildBlock(), nullptr);
    BlockPtr block_c = Block::Create("C");
    EXPECT_NE(block_c->GetParent(), block_a);
    block_a->SetChildBlock(block_c);
    EXPECT_NE(block_c->GetParent(), block_a);
    EXPECT_EQ(block_a->GetChildBlock(), block_c);
    block_c->SetParentBlock(block_a);
    EXPECT_EQ(block_c->GetParent(), block_a);
    EXPECT_TRUE(block_a->IsBlocked());
    EXPECT_TRUE(block_c->IsBlocking());
}