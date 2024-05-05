file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical03 ${sourcefiles} ${headerfiles}
        Src/Length.cpp
        Src/hasElement.cpp
        Src/lastElement.cpp
        Src/nextToLast.cpp
        Src/clone.cpp)

target_link_libraries(Practical03 Utils)
