#pragma once
#include <string>
#include <memory>

class Block {
  public:
    Block(std::string name);

    std::string GetName() { return name_; };

    bool IsSupporting() { return top_block_ != nullptr; };

    std::shared_ptr<Block> GetTopBlock() { return top_block_; };

    void SetTopBlock(std::shared_ptr<Block> top_block) { top_block_ = top_block; };

  private:
    std::string name_;
    std::shared_ptr<Block> top_block_;
};