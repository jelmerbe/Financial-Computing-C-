file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Practical05 ${sourcefiles} ${inlinefiles} ${headerfiles}
        Src/BitManip.cpp
        Src/Regression.cpp
        Src/Projection.cpp
        Src/MonteCarlo4.cpp)

target_link_libraries(Practical05 gtest)
target_link_libraries(Practical05 Utils)