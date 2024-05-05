file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Examples_TemplateDesignePattern ${sourcefiles} ${headerfiles}
        ../../SampleExam2015/SampleExam2015MTQ1/Src/Vasicek_Functions.cpp)


