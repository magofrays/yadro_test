
add_library(
    ClubSystemLib
    utilities/clock.cpp
    events/events.cpp
    club/club_system.cpp
    events/event_manager.cpp
    )
target_include_directories(ClubSystemLib PUBLIC utilities events club)
add_executable(ComputerClub main.cpp)
target_link_libraries(ComputerClub ClubSystemLib)