# Install script for directory: /Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Libraries/Utils/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Libraries/MCLib/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Libraries/googletest_1_14/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture01/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture010203/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture05/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture06/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture0708/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture09/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture10/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture11/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture1314/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Lecture1516/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Lectures/Examples_TemplateDesignPattern/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical01/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical02/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical03/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical04/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical05/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical06/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Practicals/Practical07/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/SampleExam2015/SampleExam2015MTQ1/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/SampleExam2015/SampleExam2015MTQ2/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/SampleExam2015/SampleExam2015MTQ3/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/SampleExam2015/SampleExam2015MTQ4/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Exam/ExamQ1/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Exam/ExamQ2/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Exam/ExamQ3/cmake_install.cmake")
  include("/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/Exam/ExamQ4/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/jelmerbennema/Documents/Oxford/MSc/Michaelmas/Financial Computing/CppCourse/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
