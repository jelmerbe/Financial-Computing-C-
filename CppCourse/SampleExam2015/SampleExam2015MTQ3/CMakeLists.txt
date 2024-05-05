file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(SampleExamQ3 ${sourcefiles} ${headerfiles}
        Src/FiniteFunctions.cpp)

target_link_libraries(SampleExamQ3 Utils)
