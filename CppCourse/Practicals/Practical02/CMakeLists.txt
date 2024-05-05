file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical02 ${sourcefiles} ${headerfiles}
        Src/eulerStep.cpp
        Src/milsteinStep.cpp
        Src/MonteCarlo3.cpp
        Src/eulerStep.cpp
        Src/milsteinStep.cpp
        Src/MonteCarlo3.cpp
        Src/ComplexNumber.cpp)

target_link_libraries(Practical02 Utils)
