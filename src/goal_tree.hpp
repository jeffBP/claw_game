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
    static GoalTreeNodePtr Create(const ClawAction action=ClawAction::UNKNOWN, const BlockPtr block_arg1=nullptr, const BlockPtr block_arg2=nullptr, const GoalTreeNodePtr parent=nullptr);
    GoalTreeNode(const ClawAction action=ClawAction::UNKNOWN, const BlockPtr block_arg1=nullptr, const BlockPtr block_arg2=nullptr, const GoalTreeNodePtr parent=nullptr);

    const std::vector<GoalTreeNodePtr>& GetLowestDifficultyOrGroup() { return or_node_groups_.front(); };
    void SetComplete(const bool is_complete) { goal_complete_ = is_complete; };
    const std::vector<std::vector<GoalTreeNodePtr>>& GetOrGroups() { return or_node_groups_; };
    GoalTreeNodePtr GetParent() { return parent_; };

    void HeapifyOrGroupVec();

    uint16_t GetSize();
    void AddOrGroup(const std::vector<GoalTreeNodePtr>& or_group);

  private:
    ClawAction action_;
    std::vector<BlockPtr> block_args_;
    bool goal_complete_ = false;
    std::vector<std::vector<GoalTreeNodePtr>> or_node_groups_;
    GoalTreeNodePtr parent_ = nullptr;
};

GoalTreeNode* MakeGoalTree(ClawAction action, BlockPtr blocks...);