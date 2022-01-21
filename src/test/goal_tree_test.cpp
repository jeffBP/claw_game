#include <gtest/gtest.h>

#include "test_utils.hpp"
#include "../block.hpp"
#include "../claw_action.hpp"
#include "../goal_tree.hpp"

// Demonstrate some basic assertions.
TEST(GoalTreeTest, OrGroupSizeTest) {
    /**
     * This test assumes a table set up of Block B on top of Block A, and Block C on it's own stack
     * on the table. This test tests the size function of an or-group node.
     * Full explanation of an or-group and goal tree node can be found in the README.md file in the project
     * directory
     */
    BlockPtr block_a = std::make_shared<Block>("A");
    BlockPtr block_b = std::make_shared<Block>("B");
    BlockPtr block_c = std::make_shared<Block>("C");
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::PUT_ON_BLOCK, block_a, block_c);

    GoalTreeNodePtr get_space_c = GoalTreeNode::Create(ClawAction::GET_SPACE, block_c);

    GoalTreeNodePtr get_space_b = GoalTreeNode::Create(ClawAction::GET_SPACE, block_b);
    GoalTreeNodePtr grasp_b = GoalTreeNode::Create(ClawAction::GRASP, block_b);
    GoalTreeNodePtr move_b = GoalTreeNode::Create(ClawAction::MOVE, block_b);
    GoalTreeNodePtr ungrasp_b = GoalTreeNode::Create(ClawAction::UNGRASP, block_b);

    GoalTreeNodePtr put_b_on_table = GoalTreeNode::Create(ClawAction::PUT_ON_TABLE, block_b);
    put_b_on_table->AddOrGroup({get_space_b, grasp_b, move_b, ungrasp_b});

    GoalTreeNodePtr get_rid_of_b = GoalTreeNode::Create(ClawAction::GET_RID_OF, block_b);
    get_rid_of_b->AddOrGroup({put_b_on_table});

    GoalTreeNodePtr clear_top_a = GoalTreeNode::Create(ClawAction::CLEAR_TOP, block_a);
    clear_top_a->AddOrGroup({get_rid_of_b});

    GoalTreeNodePtr grasp_a = GoalTreeNode::Create(ClawAction::GRASP, block_a);
    grasp_a->AddOrGroup({clear_top_a});

    GoalTreeNodePtr move_a_to_c = GoalTreeNode::Create(ClawAction::MOVE, block_a, block_c);
    GoalTreeNodePtr ungrasp_a = GoalTreeNode::Create(ClawAction::UNGRASP, block_a);

    root_node->AddOrGroup({get_space_c, grasp_a, move_a_to_c, ungrasp_a});

    EXPECT_EQ(17, root_node->GetSize());
    EXPECT_EQ(1, get_space_c->GetSize());
    EXPECT_EQ(1, get_space_b->GetSize());
    EXPECT_EQ(1, grasp_b->GetSize());
    EXPECT_EQ(1, move_b->GetSize());
    EXPECT_EQ(1, ungrasp_b->GetSize());
    EXPECT_EQ(6, put_b_on_table->GetSize());
    EXPECT_EQ(8, get_rid_of_b->GetSize());
    EXPECT_EQ(10, clear_top_a->GetSize());
    EXPECT_EQ(12, grasp_a->GetSize());
    EXPECT_EQ(1, move_a_to_c->GetSize());
    EXPECT_EQ(1, ungrasp_a->GetSize());
}

TEST(GoalTreeTest, OrGroupVectorMinHeapTest)
{
    /**
     * This tests for whether the or group vector for a given goal node
     * is organized as a max heap. Explanations for "or groups" and their requirements
     * available in README.md in project directory.
     */
     
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::UNKNOWN);
    
    GoalTreeNodePtr sub_node_a = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);
    GoalTreeNodePtr sub_node_b = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);

    GoalTreeNodePtr sub_node_c = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);
    GoalTreeNodePtr sub_node_d = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);
    GoalTreeNodePtr sub_node_e = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);

    root_node->AddOrGroup({sub_node_a, sub_node_b});
    root_node->AddOrGroup({sub_node_c, sub_node_d, sub_node_e});

    EXPECT_EQ(2, root_node->GetLowestDifficultyOrGroup().size());
 
    EXPECT_TRUE(IsOrGroupVectorMinHeap(root_node->GetOrGroups()));

    GoalTreeNodePtr sub_node_a_sub_node_a = GoalTreeNode::Create(ClawAction::UNKNOWN);
    sub_node_a->AddOrGroup({sub_node_a_sub_node_a});

    EXPECT_EQ(3, root_node->GetLowestDifficultyOrGroup().size());
    EXPECT_TRUE(IsOrGroupVectorMinHeap(root_node->GetOrGroups()));

    GoalTreeNodePtr sub_node_f = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);
    root_node->AddOrGroup({sub_node_f});

    EXPECT_EQ(1, root_node->GetLowestDifficultyOrGroup().size());
    EXPECT_TRUE(IsOrGroupVectorMinHeap(root_node->GetOrGroups()));
}

TEST(GoalTreeTest, GoalTreeNodeParentTest)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::UNKNOWN);
    EXPECT_EQ(root_node->GetParent(), nullptr);

    GoalTreeNodePtr sub_node_a = GoalTreeNode::Create(ClawAction::UNKNOWN, root_node);
    EXPECT_EQ(root_node->GetParent(), nullptr);
    EXPECT_EQ(sub_node_a->GetParent(), root_node);
}