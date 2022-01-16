#pragma once

#include <memory>
#include <string>
#include <vector>

#include "block_fwd.hpp"

using BlockPtr = std::shared_ptr<Block>;

class Table {
  public:
    Table(int num_stacks);

    void AddBlockToTable(BlockPtr block);

    void AddBlockToStack(BlockPtr block, int stack_idx);

    BlockPtr RemoveBlockFromTable(BlockPtr block);

    BlockPtr RemoveBlockFromStack(int stack);

    void FindBlockOnTable(std::string block_name);

  private:
    std::vector<BlockPtr> block_stacks_;
};