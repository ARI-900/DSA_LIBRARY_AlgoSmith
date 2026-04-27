# ── User Workspace CMake Configuration ───────────────────────────────────────
#
# This file manages the user's workspace.
# By default, it compiles 'main.cpp' without linking the algosmith library.
# If you want to use the library, uncomment the target_link_libraries line.

add_executable(user_main main.cpp)

# Uncomment the line below to link the AlgoSmith library to your project!
target_link_libraries(user_main PRIVATE algosmith)
