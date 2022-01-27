#pragma once

#include <string>
#include <memory>

class Block;
using BlockPtr = std::shared_ptr<Block>;

class Block {
  public:
    static BlockPtr Create(const std::string name, const BlockPtr parent_block=nullptr);
    Block(const std::string name, const BlockPtr parent_block=nullptr);

    std::string GetName() { return name_; };

    bool IsBlocked() { return child_block_ != nullptr; };

    BlockPtr GetChildBlock() { return child_block_; };

    void SetChildBlock(BlockPtr sub_block);

    bool IsBlocking() { return parent_block_ != nullptr; };

    void SetParentBlock(BlockPtr parent_block);
    
    BlockPtr GetParent() { return parent_block_; };

    void PopChildBlock() { child_block_ = nullptr; };

  private:
    std::string name_;
    BlockPtr child_block_; // Block placed above this block.
    BlockPtr parent_block_; // Block placed below this block.
};
