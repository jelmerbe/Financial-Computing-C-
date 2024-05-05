file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Exam2023Q1 ${sourcefiles} ${headerfiles}
        Src/HullWhite.cpp)

target_link_libraries(Exam2023Q1 Utils)
