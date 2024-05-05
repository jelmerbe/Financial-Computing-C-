file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Lecture10 ${sourcefiles} ${headerfiles})

target_link_libraries(Lecture10 gtest)

