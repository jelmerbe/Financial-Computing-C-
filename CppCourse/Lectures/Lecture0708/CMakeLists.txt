file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Lecture0708 ${sourcefiles} ${headerfiles})

target_link_libraries(Lecture0708 Utils)

