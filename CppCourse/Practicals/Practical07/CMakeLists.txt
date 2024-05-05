file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")

add_executable(Practical07 ${sourcefiles} ${headerfiles}
        Src/Val_FDDelta_FDGamma.cpp
        Src/Val_FDDelta_FDGamma.cpp)

target_link_libraries(Practical07 MCLib)
target_link_libraries(Practical07 Utils)
