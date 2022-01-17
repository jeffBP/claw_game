#include "../goal_tree.hpp"

bool is_or_group_vec_max_heap(const std::vector<std::vector<GoalTreeNodePtr>>& or_group_vector) {
    for (int i = 0; i < or_group_vector.size(); ++i) {
        uint16_t parent_or_group_size = 0;
        for (const GoalTreeNodePtr& node : or_group_vector.at(i)){
            parent_or_group_size = parent_or_group_size + node->GetSize();
        }
        int left_child_idx = 2*i+1;
        int right_child_idx = 2*i+2;
        if (left_child_idx < or_group_vector.size()) {
            uint16_t left_child_size = 0;
            for (const GoalTreeNodePtr& node : or_group_vector.at(left_child_idx)) {
                left_child_size = left_child_size + node->GetSize();
            }
            if (left_child_size > parent_or_group_size) {
                return false;
            }
        }
        if (right_child_idx < or_group_vector.size()) {
            uint16_t right_child_size = 0;
            for (const GoalTreeNodePtr& node : or_group_vector.at(right_child_idx)) {
                right_child_size = right_child_size + node->GetSize();
            }
            if (right_child_size > parent_or_group_size) {
                return false;
            }
        }
    }
    return true;
}