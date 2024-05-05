file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Exam2023Q2 ${sourcefiles} ${headerfiles}
        Src/Integrals.cpp)

target_link_libraries(Exam2023Q2 Utils)
