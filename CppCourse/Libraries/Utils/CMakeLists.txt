file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
#file(GLOB inlinefiles "Inl/*.inl")
add_library(Utils STATIC ${sourcefiles} ${inlinefiles} ${headerfiles})
