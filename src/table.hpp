#pragma once

#include <memory>
#include <string>
#include <vector>

#include "block_fwd.hpp"

using BlockPtr = std::shared_ptr<Block>;

class Table {
  public:
    Table(const int num_stacks);

    int GetTableSpace();

    void AddBlockToTable(BlockPtr block);

    void AddBlockToStack(BlockPtr block, const int stack_idx);

    std::pair<int, int> FindBlockOnTable(const std::string block_name);

    BlockPtr RemoveBlockFromStack(const int stack_idx);

  private:
    std::vector<BlockPtr> block_stacks_;
};