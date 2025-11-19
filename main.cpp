#include "Student.h"
#include "GradeCalc.h"
#include "StudentSort.h"
#include "StudentIO.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

int main()
{
#ifdef USE_VECTOR
    std::cout << ">>> Using std::vector container <<<\n";
#elif defined(USE_LIST)
    std::cout << ">>> Using std::list container <<<\n";
#else
    std::cout << ">>> No container macro defined, using std::vector as default <<<\n";
#endif

    using namespace std::chrono;
    std::string mode;
    StudentContainer students;
    bool showAddressForConsole = false;

    while (true)
    {
        int menuChoice = getUserMenuChoice();
        if (menuChoice == 1) // Add new student
        {
            std::cout << "Choose input method: \n1. Step-by-step entry\n2. Quick entry (stream operator)\n";
            int inputMethod;
            std::cin >> inputMethod;
            Student s;

            if (inputMethod == 1)
            {
                showAddressForConsole = true;
                s = getUserStudentInput();
                students.push_back(s);
            }
            else
            {
                std::cout << "Enter student data:\n";
                std::cout << "Format: FirstName LastName hw1 hw2 hw3 ... exam\n";

                std::cin >> s;
                students.push_back(s);
            }
            std::cout << "\n\nNew student is added:\n";
            std::cout << s << "\n";
        }
        else if (menuChoice == 2) // Calculate grades
        {

            if (students.size() == 0)
            {
                std::cout << "No student data found in the system!" << "\n";
                continue;
            }
            getModeChoice(mode);
            for (auto &s : students)
            {
                s = calcFinalGrade(s);
            }
            printStudents(students, mode, showAddressForConsole);
        }
        else if (menuChoice == 3) // Insert student data from a file
        {
            std::string fileName;
            std::cout << "Enter file name in the following format: fileName.txt" << "\n";
            while (true)
            {
                std::cin >> fileName;
                if (checkFileAvailability(fileName) == 0)
                {
                    break;
                }
                std::cout << "Enter correct file name!" << "\n";
            }

            loadStudentsFromFile(students, fileName);

#ifndef USE_LIST
            students.shrink_to_fit();
#endif

            std::cout << "\n";
            std::cout << "Student data is uploaded to the system." << "\n";
            std::cout << "\n";
#ifdef USE_LIST
            students.sort(compareStudentNames);

#else
            sort(students.begin(), students.end(), compareStudentNames);
#endif

            std::cout << "\n";
            for (auto &s : students)
            {
                s = calcFinalGrade(s);
            }
            printStudents(students, "b");
            std::cout << "\n";
        }
        else if (menuChoice == 4) // Generate random student file
        {
            StudentContainer studentData;

            int fileLenght;
            std::string fileName;
            std::string usrInput;
            while (true)
            {
                std::cout << "How many student records would you like to generate? ";
                std::cin >> usrInput;

                size_t parsed = 0;

                try
                {
                    fileLenght = stoi(usrInput, &parsed);
                    if (parsed != usrInput.size())
                    {
                        std::cout << "Invalid input!" << "\n";
                        continue;
                    }
                    break;
                }
                catch (const std::invalid_argument &err)
                {
                    std::cout << "Invalid input!" << "\n";
                    continue;
                }
            }

            fileName = "Student" + std::to_string(fileLenght) + ".txt";

            generateRandomStudentFile(fileName, fileLenght);
        }
        else if (menuChoice == 5) // sort student list into categories
        {
            StudentContainer studentData;
            StudentContainer strugglers;
            StudentContainer highAchievers;
            std::string fileName;
            std::string sortChoice;
            std::cout << "Enter file name in the following format: fileName.txt" << "\n";
            while (true)
            {
                std::cin >> fileName;
                if (checkFileAvailability(fileName) == 0)
                {
                    break;
                }
                std::cout << "Enter correct file name!" << "\n";
            }

            loadStudentsFromFile(studentData, fileName);

#ifndef USE_LIST
            studentData.shrink_to_fit();
#endif
            std::cout << "\n";
            std::cout << "Student data is uploaded to the system." << "\n";
            std::cout << "\n";

            for (auto &s : studentData)
            {
                s = calcFinalGrade(s);
            }

            int choice;
            std::cout << "Choose categorization stategy (1, 2 or 3): ";
            std::cin >> choice;

            if (choice == 1)
                categorizeStudents_1(studentData, strugglers, highAchievers);
            else if (choice == 2)
                categorizeStudents_2(studentData, strugglers, highAchievers);
            else
                categorizeStudents_3(studentData, strugglers, highAchievers);

            std::cout << "To sort categorized files by name type 'n' or 'g' to sort by grade: " << "\n";

            while (true)

            {
                std::cin >> sortChoice;

                if (sortChoice == "n")

                {
#ifdef USE_LIST
                    strugglers.sort(compareStudentNames);
                    highAchievers.sort(compareStudentNames);

#else
                    sort(strugglers.begin(), strugglers.end(), compareStudentNames);

                    sort(highAchievers.begin(), highAchievers.end(), compareStudentNames);
#endif
                    break;
                }

                else if (sortChoice == "g")

                {
#ifdef USE_LIST
                    strugglers.sort(compareStudentGrades);
                    highAchievers.sort(compareStudentGrades);
#else
                    sort(strugglers.begin(), strugglers.end(), compareStudentGrades);
                    sort(highAchievers.begin(), highAchievers.end(), compareStudentGrades);
#endif
                    break;
                }

                std::cout << "Invalid choice!\n";
            }

            createStudentFile(strugglers, "strugglers.txt");
            createStudentFile(highAchievers, "highAchievers.txt");
        }
        else
        {
            break;
        }
    }
    return 0;
}
