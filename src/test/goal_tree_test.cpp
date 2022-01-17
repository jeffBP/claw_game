#include <gtest/gtest.h>

#include "../block.hpp"
#include "../claw_action.hpp"
#include "../goal_tree.hpp"

// Demonstrate some basic assertions.
TEST(GoalTreeTest, OrGroupSizeTest) {
    /**
     * This test constructs a goal tree and 
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

    GoalTreeNodePtr clear_top_a = GoalTreeNode::Create(ClawAction::CLEAR_TOP, block_a);
    clear_top_a->AddOrGroup({put_b_on_table});

    GoalTreeNodePtr grasp_a = GoalTreeNode::Create(ClawAction::GRASP, block_a);
    grasp_a->AddOrGroup({clear_top_a});

    GoalTreeNodePtr move_a_to_c = GoalTreeNode::Create(ClawAction::MOVE, block_a, block_c);
    GoalTreeNodePtr ungrasp_a = GoalTreeNode::Create(ClawAction::UNGRASP, block_a);

    root_node->AddOrGroup({get_space_c, grasp_a, move_a_to_c, ungrasp_a});

    EXPECT_EQ(17, root_node->GetSize());
    std::cout << "Goal Tree size: " << root_node->GetSize() << std::endl;
}