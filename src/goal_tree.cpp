#include "goal_tree.hpp"

#include <algorithm>

#include "block.hpp"
static bool CompareOrGroups(std::vector<GoalTreeNodePtr>& group1, std::vector<GoalTreeNodePtr>& group2)
{
    uint16_t group1_size = 0;
    for (const GoalTreeNodePtr& node : group1) {
        group1_size = group1_size + node->GetSize();
    }
    uint16_t group2_size = 0;
    for (const GoalTreeNodePtr& node : group2) {
        group2_size = group2_size + node->GetSize();
    }
    return group1_size >= group2_size;
}

GoalTreeNode::GoalTreeNode() : action_(ClawAction::UNKNOWN) {}

GoalTreeNode::GoalTreeNode(const ClawAction action) : action_(action) {}

GoalTreeNode::GoalTreeNode(const ClawAction action, const BlockPtr block_arg)
            :  action_(action)
{
    block_args_.push_back(block_arg);
}

GoalTreeNode::GoalTreeNode(const ClawAction action, const BlockPtr block_arg1, const BlockPtr block_arg2)
            : action_(action)
{
    block_args_.push_back(block_arg1);
    block_args_.push_back(block_arg2);
}

uint16_t GoalTreeNode::GetSize()
{
    uint16_t node_size = 0;
    for (const std::vector<GoalTreeNodePtr>& or_group : or_node_groups_) {
        for (const GoalTreeNodePtr& node : or_group) {
            // Add size for sub_nodes.
            node_size = node_size + node->GetSize();
        }
        //Add Size for each or group.
        ++node_size;
    }
    // Increment to include this node.
    ++node_size;
    return node_size;
}

void GoalTreeNode::AddOrGroup(const std::vector<GoalTreeNodePtr>& or_group)
{
    or_node_groups_.push_back(or_group);
    std::make_heap(or_node_groups_.begin(), or_node_groups_.end(), CompareOrGroups);
}