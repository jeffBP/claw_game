#pragma once

#include <memory>
#include <string>
#include <vector>

#include "claw_action.hpp"
#include "block_fwd.hpp"

class GoalTreeNode;
using GoalTreeNodePtr = std::shared_ptr<GoalTreeNode>;

class GoalTreeNode {
  public: 
    GoalTreeNode();
    GoalTreeNode(const ClawAction action);
    GoalTreeNode(const ClawAction action, const BlockPtr block_arg);
    GoalTreeNode(const ClawAction action, const BlockPtr block_arg1, const BlockPtr block_arg2);

    const std::vector<GoalTreeNodePtr>& GetLowestDifficultyOrGroup() { return or_node_groups_.front(); };
    void SetComplete(const bool is_complete) { goal_complete_ = is_complete; };

    uint16_t GetSize();
    void AddOrGroup(const std::vector<GoalTreeNodePtr>& or_group);

  private:
    ClawAction action_;
    std::vector<BlockPtr> block_args_;
    bool goal_complete_ = false;
    std::vector<std::vector<GoalTreeNodePtr>> or_node_groups_;
};

GoalTreeNode* MakeGoalTree(ClawAction action, BlockPtr blocks...);