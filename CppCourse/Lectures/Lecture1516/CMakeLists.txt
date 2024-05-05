file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Lecture1516 ${sourcefiles} ${headerfiles})

target_link_libraries(Lecture1516 MCLib)
