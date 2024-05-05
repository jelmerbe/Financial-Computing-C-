cmake_minimum_required (VERSION 3.10)

project(CppCourse VERSION 1.0 LANGUAGES CXX)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (GOOGLETEST_VERSION 1.14.0)
if(MSVC)
   set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
   set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()
#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${CMAKE_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/boostRoot)
include_directories(${CMAKE_SOURCE_DIR}/Lectures)
include_directories(${CMAKE_SOURCE_DIR}/Libraries)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest_1_14)
include_directories(${CMAKE_SOURCE_DIR}/Practicals)
include_directories(${CMAKE_SOURCE_DIR}/SampleExam2015)
include_directories(${CMAKE_SOURCE_DIR}/Exam)

include(CMakeDependentOption)
include(GNUInstallDirs)

option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

add_definitions(-DCOURSE_OUTPUT_DIR="${PROJECT_SOURCE_DIR}")

# libraries
add_subdirectory(Libraries/Utils)
add_subdirectory(Libraries/MCLib)
add_subdirectory(Libraries/googletest_1_14)

# Projects used on lectures
add_subdirectory(Lectures/Lecture01)
add_subdirectory(Lectures/Lecture010203)
add_subdirectory(Lectures/Lecture05)
add_subdirectory(Lectures/Lecture06)
add_subdirectory(Lectures/Lecture0708)
add_subdirectory(Lectures/Lecture09)
add_subdirectory(Lectures/Lecture10)
add_subdirectory(Lectures/Lecture11)
add_subdirectory(Lectures/Lecture1314)
add_subdirectory(Lectures/Lecture1516)
add_subdirectory(Lectures/Examples_TemplateDesignPattern)

# Practicals and solutions
add_subdirectory(Practicals/Practical01)
#add_subdirectory(Practicals/Practical01Solutions)
add_subdirectory(Practicals/Practical02)
#add_subdirectory(Practicals/Practical02Solutions)
add_subdirectory(Practicals/Practical03)
#add_subdirectory(Practicals/Practical03Solutions)
add_subdirectory(Practicals/Practical04)
#add_subdirectory(Practicals/Practical04Solutions)
add_subdirectory(Practicals/Practical05)
#add_subdirectory(Practicals/Practical05Solutions)
add_subdirectory(Practicals/Practical06)
#add_subdirectory(Practicals/Practical06Solutions)
add_subdirectory(Practicals/Practical07)
#add_subdirectory(Practicals/Practical07Solutions)

# Sample exam
add_subdirectory(SampleExam2015/SampleExam2015MTQ1)
#add_subdirectory(SampleExam2015/SampleExam2015MTQ1_Solutions)
add_subdirectory(SampleExam2015/SampleExam2015MTQ2)
#add_subdirectory(SampleExam2015/SampleExam2015MTQ2_Solutions)
add_subdirectory(SampleExam2015/SampleExam2015MTQ3)
#add_subdirectory(SampleExam2015/SampleExam2015MTQ3_Solutions)
add_subdirectory(SampleExam2015/SampleExam2015MTQ4)
#add_subdirectory(SampleExam2015/SampleExam2015MTQ4_Solutions)

# Exam projects
add_subdirectory(Exam/ExamQ1)
#add_subdirectory(Exam/ExamQ1_solutions)
add_subdirectory(Exam/ExamQ2)
#add_subdirectory(Exam/ExamQ2_solutions)
add_subdirectory(Exam/ExamQ3)
#add_subdirectory(Exam/ExamQ3_solutions)
add_subdirectory(Exam/ExamQ4)
#add_subdirectory(Exam/ExamQ4_solutions)



