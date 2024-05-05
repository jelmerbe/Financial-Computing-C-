file(GLOB sourcefiles "Src/*.cpp")
file(GLOB headerfiles "*.hpp")
file(GLOB inlinefiles "Inl/*.inl")
add_library(MCLib STATIC ${sourcefiles} ${inlinefiles} ${headerfiles})
