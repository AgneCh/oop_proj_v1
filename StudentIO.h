#pragma once
#include "Student.h"
#include <string>
#include <vector>

//input
Student getUserStudentInput();
int getUserMenuChoice();
void getModeChoice(std::string& mode);

// inour/output stream overloads
std::istream& operator>>(std::istream& in, Student& s);
std::ostream& operator<<(std::ostream& out, const Student& s);

// formatting
std::string createHeader(const std::string& mode, bool showAddress = false);
std::string formatStudentRow(const Student& student, const std::string& mode, bool showAddress = false);
void printStudents(StudentContainer& students, const std::string& mode, bool showAddress = false);


// files
int  checkFileAvailability(std::string file);
void generateRandomStudentFile(std::string fileName, int numOfLines);
void loadStudentsFromFile(StudentContainer& students, std::string fileName);
void createStudentFile(StudentContainer& studentList, std::string fileName);

// parsing
void stripWhiteSpace(std::string& s, std::vector<std::string>& result);
Student processStudentRow(std::vector<std::string> studentRow);