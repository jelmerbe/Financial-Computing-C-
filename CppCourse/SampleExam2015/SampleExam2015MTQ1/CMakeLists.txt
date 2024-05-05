file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(SampleExamQ1 ${sourcefiles} ${headerfiles})

target_link_libraries(SampleExamQ1 Utils)
