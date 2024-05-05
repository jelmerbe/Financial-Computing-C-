#ifndef __MEMBER_HPP__
#define __MEMBER_HPP__

#include <iostream>
#include <list>

class UniversityMember; // forward declaration

std::ostream & operator<<(std::ostream & os,
			  const UniversityMember & um);


class UniversityMember {
public:
  UniversityMember(std::string sFirstName, std::string sSurName);
  virtual ~UniversityMember();
  std::string getName() const;
  virtual std::ostream & printDetails(std::ostream & os) const;

private:
  std::string sFirstName_;
  std::string sSurName_;
};


class Student : public UniversityMember {
public:
  Student(std::string sFirstName, std::string sSurName,
	  std::string sCollege, std::string sCourse);
  std::ostream & printDetails(std::ostream & os) const;

private:
  std::string sCollege_;
  std::string sCourse_;

};


class Faculty : public UniversityMember {
public:
  Faculty(std::string sFirstName, std::string sSurName,
	  std::string sDepartment, unsigned int iGrade);
  std::ostream & printDetails(std::ostream & os) const;
  void addStudent(Student &);

private:
  std::list<Student> getStudents() const;
  std::string sDepartment_;
  unsigned int iGrade_;
  std::list<Student> lSupervisedStudents_;
};

#endif
