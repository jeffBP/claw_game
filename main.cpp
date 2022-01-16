#include <iostream>
#include <memory>
#include <string>

#include "src/claw_action.hpp"
#include "src/goal_tree.hpp"
#include "src/block.hpp"

int main(int argc, char** argv) {
    std::cout << "Hello World!" << std::endl;
    
    BlockPtr block_a = std::make_shared<Block>("A");
    GoalTreeNodePtr root_node = std::make_shared<GoalTreeNode>(ClawAction::PUT_ON_TABLE, block_a);
    
    
    std::cout << "Goal Tree size: " << root_node->GetSize() << std::endl;
    return 0;
}