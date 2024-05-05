file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
add_executable(Practical01 ${sourcefiles} ${headerfiles}
        Src/Norm2.cpp
        Src/NormInf.cpp
        Src/MonteCarlo1.cpp
        Src/MonteCarlo2.cpp
        Src/callAt1.cpp
        Src/Norm2.cpp
        Src/NormInf.cpp
        Src/MonteCarlo1.cpp
        Src/MonteCarlo2.cpp
        Src/callAt1.cpp)

target_link_libraries(Practical01 Utils)
