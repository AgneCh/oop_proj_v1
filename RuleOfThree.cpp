#include "RuleOfThree.h"

void testRuleOfThree()
{
    Student s1("Test", "Tester");
    s1.addGrade(10);
    s1.addGrade(7);
    s1.addGrade(8);
    s1.setExam(9);

    Student s2 = s1;
    Student s3;
    s3 = s1;

    // s1.setFirstName("Modified");
    // s1.addGrade(9);

    std::cout << "[Original student s1]\n";
    printStudentInfo(s1);

    std::cout << "[Student copy s2 (copy constructor)]\n";
    printStudentInfo(s2);

    std::cout << "[Student copy s3 (assignment operator)]\n";
    printStudentInfo(s3);
}

void printStudentInfo(const Student &s)
{
    std::cout << "First name: " << s.firstName() << "\n";
    std::cout << "Surname: " << s.lastName() << "\n";
    std::cout << "Grades: ";
    for (int g : s.grades())
        std::cout << g << " ";
    std::cout << "\nExam: " << s.exam() << "\n";
    std::cout << "---------------------------\n";
}