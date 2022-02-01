#include <string>

#include "table.hpp"
#include "block_fwd.hpp"
#include "goal_tree.hpp"
#include "claw_action.hpp"

class ClawGame {
  public:
    explicit ClawGame();

    GoalTreeNodePtr HandleAction(const ClawAction action, 
                                 const std::string block_1="", 
                                 const std::string block2="");

    GoalTreeNodePtr HandleAction(const ClawAction action,
                                 BlockPtr block_1=nullptr,
                                 BlockPtr block_2=nullptr);
    
    GoalTreeNodePtr HandlePutOnBlock(BlockPtr block_1, BlockPtr block_2);
    GoalTreeNodePtr HandleGetSpace(BlockPtr block);
    GoalTreeNodePtr HandleMakeSpace(BlockPtr block);
    GoalTreeNodePtr HandlePutOnTable(BlockPtr block);
    GoalTreeNodePtr HandleGrasp(BlockPtr block);
    GoalTreeNodePtr HandleClearTop(BlockPtr block);
    GoalTreeNodePtr HandleMove(BlockPtr block);
    GoalTreeNodePtr HandleUngrasp(BlockPtr block);

  private:
    GoalTreeNodePtr root_node_;
    Table table_;
};