#include "table.hpp"

#include <iostream>
#include <utility>

#include "block.hpp"

Table::Table(const int num_stacks) {
    block_stacks_ = std::vector<BlockPtr>(num_stacks, nullptr);
}

int Table::GetTableSpace() {
    for (int i = 0; i < block_stacks_.size(); ++i) {
        if ( block_stacks_.at(i) == nullptr) {
            std::cout << "Found table space at index " << i << "." << std::endl;
            return i;
        }
    }
    std::cout << "Could not find table space.";
    return -1;
}

void Table::AddBlockToStack(BlockPtr block, const int stack_idx)
{
    BlockPtr cur_block = block_stacks_.at(stack_idx);
    if (!cur_block) {
        block_stacks_[stack_idx] = block;
        return;
    }
    while ( cur_block->GetChildBlock() ) {
        cur_block = cur_block->GetChildBlock();
    }
    cur_block->SetChildBlock(block);
    block->SetParentBlock(cur_block);
}

std::pair<int, int> Table::FindBlockOnTable(const std::string block_name)
{
    int depth = 0;
    for (int stack_idx = 0; stack_idx < block_stacks_.size(); ++stack_idx) {
        BlockPtr block = block_stacks_.at(stack_idx);
        while( block != nullptr) {
            if (block->GetName() == block_name) {
                return std::make_pair(stack_idx, depth);
            } else {
                block = block->GetChildBlock();
                ++depth;
            }
        }
        depth = 0;
    }
    return std::make_pair(-1, -1);
}

BlockPtr Table::RemoveBlockFromStack(const int stack_idx)
{
    BlockPtr cur_block = block_stacks_.at(stack_idx);
    while(cur_block->GetChildBlock() != nullptr) {
        std::cout << cur_block->GetName() << std::endl;
        cur_block = cur_block->GetChildBlock();
    }
    cur_block->GetParent()->PopChildBlock();
    return cur_block;
}