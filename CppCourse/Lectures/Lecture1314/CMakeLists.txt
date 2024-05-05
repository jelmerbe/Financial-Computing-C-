file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Lecture1314 ${sourcefiles} ${headerfiles})

target_link_libraries(Lecture1314 MCLib)
