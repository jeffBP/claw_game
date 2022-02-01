#include <memory>

#include "game.hpp"
#include "block.hpp"


GoalTreeNodePtr ClawGame::HandleAction(const ClawAction action, 
                                       const std::string block_1, 
                                       const std::string block_2)
{
    BlockPtr block_1_ptr = table_.GetBlock(block_1);
    BlockPtr block_2_ptr = table_.GetBlock(block_2);
    return HandleAction(action, block_1_ptr, block_2_ptr);
}

GoalTreeNodePtr ClawGame::HandleAction(const ClawAction action,
                                       BlockPtr block_1,
                                       BlockPtr block_2)
{
    // TODO: Add input guards for each case.
    GoalTreeNodePtr root_node;
    std::vector<GoalTreeNodePtr> or_group;
    switch ( action ) {
        case ClawAction::PUT_ON_BLOCK:
            root_node = HandlePutOnBlock(block_1, block_2);
            break;
        case ClawAction::GET_SPACE:
            root_node = HandleGetSpace(block_1);
            break;
        case ClawAction::MAKE_SPACE:
            root_node = HandleMakeSpace(block_1);
        case ClawAction::PUT_ON_TABLE:
            root_node = HandlePutOnTable(block_1);
            break;
        case ClawAction::GRASP:
            root_node = HandleGrasp(block_1);
            break;
        case ClawAction::CLEAR_TOP:
            root_node = HandleClearTop(block_1);
            break;
        case ClawAction::MOVE:
            root_node = HandleMove(block_1);
            break;
        case ClawAction::UNGRASP:
            root_node = HandleUngrasp(block_1);
            break;
        case ClawAction::UNKNOWN:
            break;
    }
    return root_node;
}

GoalTreeNodePtr ClawGame::HandlePutOnTable(BlockPtr block)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::PUT_ON_TABLE, block);
    std::vector<GoalTreeNodePtr> or_group;
    or_group.push_back(HandleAction(ClawAction::GET_SPACE, block));
    or_group.push_back(HandleAction(ClawAction::GRASP, block));
    or_group.push_back(HandleAction(ClawAction::MOVE, block));
    or_group.push_back(HandleAction(ClawAction::UNGRASP, block));
    root_node->AddOrGroup(or_group);
    return root_node;    
}

GoalTreeNodePtr ClawGame::HandlePutOnBlock(BlockPtr block_1, BlockPtr block_2)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::PUT_ON_BLOCK, block_1, block_2);
    std::vector<GoalTreeNodePtr> or_group;
    or_group.push_back(HandleAction(ClawAction::GET_SPACE, block_2));
    or_group.push_back(HandleAction(ClawAction::GRASP, block_1));
    or_group.push_back(HandleAction(ClawAction::MOVE, block_1, block_2));
    or_group.push_back(HandleAction(ClawAction::UNGRASP, block_1));
    root_node_->AddOrGroup(or_group);
    return root_node;
}

GoalTreeNodePtr ClawGame::HandleGetSpace(BlockPtr block)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::GET_SPACE, block);
    if (block->IsBlocked()) {
        std::vector<GoalTreeNodePtr> or_group;
        or_group.push_back(HandleAction(ClawAction::MAKE_SPACE, block->GetChildBlock()));
        root_node->AddOrGroup(or_group);
    }
    return root_node;
}

GoalTreeNodePtr ClawGame::HandleMakeSpace(BlockPtr block)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::MAKE_SPACE, block);
    std::vector<GoalTreeNodePtr> or_group;
    or_group.push_back(HandleAction(ClawAction::GET_RID_OF, block));
    root_node->AddOrGroup(or_group);
    return root_node;
}

GoalTreeNodePtr ClawGame::HandleGrasp(BlockPtr block)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::GRASP, block);
    std::vector<GoalTreeNodePtr> or_group;
    or_group.push_back(HandleAction(ClawAction::CLEAR_TOP, block));
    root_node->AddOrGroup(or_group);
    return root_node;
}

GoalTreeNodePtr ClawGame::HandleClearTop(BlockPtr block)
{
    GoalTreeNodePtr root_node = GoalTreeNode::Create(ClawAction::CLEAR_TOP, block);
    std::vector<GoalTreeNodePtr> or_group;
    if (block->IsBlocked())
    {
        or_group.push_back(HandleAction(ClawAction::PUT_ON_TABLE, block->GetChildBlock()));
    }
    or_group.push_back(HandleAction(ClawAction::PUT_ON_TABLE, block));
    root_node->AddOrGroup(or_group);
    return root_node;
}

GoalTreeNodePtr ClawGame::HandleMove(BlockPtr block)
{
    return GoalTreeNode::Create(ClawAction::MOVE, block);
}

GoalTreeNodePtr ClawGame::HandleUngrasp(BlockPtr block)
{
    return GoalTreeNode::Create(ClawAction::UNGRASP, block);
}