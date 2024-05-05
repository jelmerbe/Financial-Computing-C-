file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Exam2023Q4 ${sourcefiles} ${headerfiles}
        Src/Q4_functions.cpp)

target_link_libraries(Exam2023Q4 MCLib)
target_link_libraries(Exam2023Q4 Utils)