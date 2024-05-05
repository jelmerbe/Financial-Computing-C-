file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Exam2023Q3 ${sourcefiles} ${headerfiles}
        Src/callable.cpp)

target_link_libraries(Exam2023Q3 MCLib)
target_link_libraries(Exam2023Q3 Utils)