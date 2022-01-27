#include <string>

#include "table.hpp"
#include "block_fwd.hpp"
#include "goal_tree.hpp"
#include "claw_action.hpp"

class ClawGame {
  public:
    explicit ClawGame();

    bool HandleAction(ClawAction action, std::string block_1="", std::string block2="");

  private:
    GoalTreeNodePtr root_node_;
};