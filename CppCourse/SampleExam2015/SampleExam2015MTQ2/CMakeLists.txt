file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(SampleExamQ2 ${sourcefiles} ${headerfiles}
        Src/Interpolator.cpp)

target_link_libraries(SampleExamQ2 Utils)
