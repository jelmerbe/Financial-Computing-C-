file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(SampleExamQ4 ${sourcefiles} ${headerfiles}
        Src/Q4Functions.cpp)

target_link_libraries(SampleExamQ4 MCLib)
target_link_libraries(SampleExamQ4 Utils)