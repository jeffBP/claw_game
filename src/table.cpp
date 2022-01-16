#include "table.hpp"

#include <iostream>

Table::Table(int num_stacks) {
    block_stacks_ = std::vector<BlockPtr>(num_stacks, nullptr);
}

void Table::AddBlockToTable(BlockPtr block) {
    for (int i = 0; i < block_stacks_.size(); ++i) {
        if (block_stacks_.at(i) == nullptr) {
            block_stacks_[i] == block;
            return;
        }
    }
    std::cout << "Couldn't find open space on the table to place block " << block->GetName() << std::endl;
}

void Table::AddBlockToStack(BlockPtr block, int stack_idx) {
    BlockPtr cur_block = block_stacks_.at(stack_idx);
    while(cur_block->GetTopBlock()) {
        cur_block = cur_block->GetTopBlock();
    }
    cur_block->SetTopBlock(block);
}