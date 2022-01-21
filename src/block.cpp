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
