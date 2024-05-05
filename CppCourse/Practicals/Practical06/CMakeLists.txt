file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical06 ${sourcefiles} ${headerfiles}
        Src/Options.cpp)

target_link_libraries(Practical06 Utils)
