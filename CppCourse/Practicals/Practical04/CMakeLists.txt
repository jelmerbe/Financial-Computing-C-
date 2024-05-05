file(GLOB sourcefiles "Src/*.cpp")
file(GLOB inlinefiles "Inl/*.inl")
file(GLOB headerfiles "*.hpp")

add_executable(Practical04 ${sourcefiles} ${inlinefiles} ${headerfiles}
        Src/BinaryOperators.cpp
        Src/BinaryOperators.cpp)

target_compile_definitions(Practical04 PRIVATE _PRACTICAL_04_)
target_link_libraries(Practical04 Utils)
