#include "block.hpp"

#include <memory>
#include <string>

BlockPtr Block::Create(const std::string name, const BlockPtr parent_block)
{
  return std::make_shared<Block>(name, parent_block);
}

Block::Block(const std::string name, const BlockPtr parent_block)
                    : name_(name), parent_block_(parent_block)
{
}

void Block::SetChildBlock(BlockPtr sub_block)
{
  if (child_block_) {
    child_block_->SetParentBlock(nullptr);
  }
  child_block_ = sub_block;
}

void Block::SetParentBlock(BlockPtr parent_block)
{
  if (parent_block_) {
    parent_block_->SetChildBlock(nullptr);
  }
  parent_block_ = parent_block;
}