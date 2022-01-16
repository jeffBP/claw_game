add_library(src)

target_sources(src
    PUBLIC
        block_fwd.hpp
        block.hpp
        table.hpp
        table.cpp
        claw_action.hpp
        goal_tree.hpp
        goal_tree.cpp)