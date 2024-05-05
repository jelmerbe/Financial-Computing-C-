#include "Lecture11/Member.hpp"
#include <iostream>
#include <string>

using namespace std;

UniversityMember::UniversityMember(std::string sFirstName,
				   std::string sSurName)
  : sFirstName_(sFirstName), sSurName_(sSurName){}

UniversityMember::~UniversityMember(){}

std::string UniversityMember::getName() const {
  return "Name: " + sFirstName_ + " " + sSurName_;
}

std::ostream & 
  UniversityMember::printDetails(std::ostream & os) const {
  os << getName();
  return os;
}

Student::Student(std::string sFirstName,
                 std::string sSurName,
                 std::string sCollege,
		 std::string sCourse)
  : UniversityMember(sFirstName, sSurName),
    sCollege_(sCollege),
    sCourse_(sCourse) {}

std::ostream & Student::printDetails(std::ostream & os) const {
  os<< getName() << ", College: " << sCollege_ 
    << ", Course: " << sCourse_;
  return os;
}

Faculty::Faculty(std::string sFirstName,
                 std::string sSurName,
		 std::string sDepartment,
		 unsigned int iGrade)
  : UniversityMember(sFirstName, sSurName),
    sDepartment_(sDepartment),
    iGrade_(iGrade) {}


std::ostream & Faculty::printDetails(std::ostream & os) const {
  os<< getName() << ", Department: " << sDepartment_ 
    << ", Grade: " << iGrade_;
  return os;
}

std::ostream & operator<<(std::ostream & os,
			  const UniversityMember & um) {
  return um.printDetails(os);
}

