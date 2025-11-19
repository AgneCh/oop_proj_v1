#include "StudentIO.h"
#include "GradeCalc.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <cassert>
#include <cctype>
#include <iterator>
#include <sstream>

std::istream &operator>>(std::istream &in, Student &s)
{
    in >> s.firstName_ >> s.lastName_;

    std::vector<int> allGrades;
    int grade;

    while (in >> grade)
    {
        if (grade < 1 || grade > 10)
        {
            std::cout << "\nInvalid grade: " << grade
                      << ".\nEnter correct grade as well as the remaining ones after: ";

            // print valid grades so far
            for (int g : allGrades)
                std::cout << g << " ";

            std::cout << "\n";

            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        allGrades.push_back(grade);

        if (in.peek() == '\n')
        {
            break;
        }
    }

    if (!allGrades.empty())
    {
        s.exam_ = allGrades.back(); // the last grade is the exam grade
        allGrades.pop_back();
        s.grades_ = allGrades;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Student &s)
{
    out << s.firstName() << " " << s.lastName() << " | Grades: ";
    for (int g : s.grades())
        out << g << " ";
    out << "| Exam: " << s.exam();
    return out;
}

std::string createHeader(const std::string &mode, bool showAddress)
{
    std::ostringstream header;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (showAddress)
    {
        header << std::left
               << std::setw(18) << "Address";
    }

    if (mode == "m")
    {
        // -- header --
        header << std::left
               << std::setw(wFirsName) << "Name"
               << std::setw(wLastName) << "Last name"
               << std::setw(wGrade) << "Final grade (mean)" << '\n';
        // -- separator line --
        header << std::setfill('-');
        if (showAddress)
            header << std::setw(18) << "";

        header << std::setw(wFirsName) << ""
               << std::setw(wLastName) << ""
               << std::setw(wGrade) << "" << '\n'
               << std::setfill(' ');
    }
    else if (mode == "md")
    {
        // -- header --
        header << std::left
               << std::setw(wFirsName) << "Name"
               << std::setw(wLastName) << "Last name"
               << std::setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --

        header << std::setfill('-');
        if (showAddress)
            header << std::setw(18) << "";

        header << std::setw(wFirsName) << ""
               << std::setw(wLastName) << ""
               << std::setw(wGrade) << "" << '\n'
               << std::setfill(' ');
    }
    else
    {
        // -- header --
        header << std::left
               << std::setw(wFirsName) << "Name"
               << std::setw(wLastName) << "Last name"
               << std::setw(wGrade) << "Final grade (mean)"
               << std::setw(wGrade) << "Final grade (median)" << '\n';

        // -- separator line --
        header << std::setfill('-');
        if (showAddress)
            header << std::setw(18) << "";

        header << std::setw(wFirsName) << ""
               << std::setw(wLastName) << ""
               << std::setw(wGrade) << ""
               << std::setw(wGrade) << "" << '\n'
               << std::setfill(' ');
    }

    return header.str();
}

std::string formatStudentRow(const Student &student, const std::string &mode, bool showAddress)
{
    std::ostringstream studentRow;
    const int wLastName = 15;
    const int wFirsName = 15;
    const int wGrade = 20;

    if (showAddress)
    {
        std::ostringstream address;
        const void *studAddr = static_cast<const void *>(&student);
        address << studAddr;
        studentRow << std::left
                   << std::setw(18) << address.str();
    }

    if (mode == "m")
    {

        // -- student data --
        studentRow << std::left
                   << std::setw(wFirsName) << student.firstName()
                   << std::setw(wLastName) << student.lastName()
                   << std::fixed << std::setprecision(2)
                   << std::setw(wGrade) << student.finalMean() << '\n';
    }
    else if (mode == "md")
    {

        // -- student data --
        studentRow << std::left
                   << std::setw(wFirsName) << student.firstName()
                   << std::setw(wLastName) << student.lastName()
                   << std::fixed << std::setprecision(2)
                   << std::setw(wGrade) << student.finalMedian() << '\n';
    }
    else
    {

        // -- student data --
        studentRow << std::left
                   << std::setw(wFirsName) << student.firstName()
                   << std::setw(wLastName) << student.lastName()
                   << std::fixed << std::setprecision(2)
                   << std::setw(wGrade) << student.finalMean()
                   << std::setw(wGrade) << student.finalMedian() << '\n';
    }

    return studentRow.str();
}

void printStudents(StudentContainer &students, const std::string &mode, bool showAddress)
{

    std::cout << createHeader(mode, showAddress);
    for (auto &student : students)
    {
        std::cout << formatStudentRow(student, mode, showAddress);
    }
}

Student getUserStudentInput()
{
    Student student;
    std::string grade;
    double temp_grade;
    std::string stopWord = "stop";
    std::string randomWord = "r";
    std::string userInput;
    std::string firstN, lastN;

    std::cout << "Input student data." << std::endl;
    std::cout << "First name: ";
    std::cin >> firstN;
    student.setFirstName(firstN);

    std::cout << "Last name: ";
    std::cin >> lastN;
    student.setLastName(lastN);

    while (true)
    {
        std::cout << "" << std::endl;
        std::cout << "Enter " << student.firstName() << " " << student.lastName() << " homework grade (1-10) manually, type 'r' to generated random grade or type 'stop': ";
        std::cin >> userInput;
        if (userInput == stopWord)
        {
            break;
        }

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            std::cout << "Random grade is: " << temp_grade << std::endl;
        }
        else
        {
            // check if input contains a digit
            size_t parsed = 0;
            try
            {
                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }
            }
            catch (const std::invalid_argument &err)
            {
                std::cout << "Invalid input!" << std::endl;
                continue;
            }
        }

        // check if grade is 1-10
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.addGrade(temp_grade);
        }
        else
        {
            std::cout << "Grade must be between 1 and 10." << std::endl;
        }
    }

    while (true)
    {
        std::cout << "" << std::endl;
        std::cout << "Input exam grade manually, or write 'r' to generated random grade: ";
        std::cin >> userInput;

        if (userInput == randomWord)
        {
            temp_grade = getRandomGrade();
            std::cout << "Random exam grade is: " << temp_grade << std::endl;
        }
        else
        {
            size_t parsed = 0;
            try
            {

                temp_grade = stoi(userInput, &parsed);
                if (parsed != userInput.size())
                {
                    std::cout << "Invalid input!" << std::endl;
                    continue;
                }
            }
            catch (const std::invalid_argument &err)
            {
                std::cout << "Invalid input!" << std::endl;
                continue;
            }
        }
        if (temp_grade >= 1 && temp_grade <= 10)
        {
            student.setExam(temp_grade);
            break;
        }
        else
        {
            std::cout << "Grade must be between 1 and 10." << std::endl;
        }
    }

    return student;
}

int getUserMenuChoice()
{
    int n;

    while (true)
    {
        std::cout << "\n\nChoose a number from the menu:" << std::endl;
        std::cout << "1. Add new student" << std::endl;
        std::cout << "2. Calculate grades" << std::endl;
        std::cout << "3. Insert student data from a file" << std::endl;
        std::cout << "4. Generate random student file" << std::endl;
        std::cout << "5. Sort student data into categories" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "" << std::endl;
        std::cin >> n;
        if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6)
        {
            return n;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid menu number!" << std::endl;
    }
}

void getModeChoice(std::string &mode)
{
    std::cout << "" << std::endl;
    std::cout << "Would you like to view the calculated final grade with:" << std::endl;
    std::cout << "m = mean" << std::endl;
    std::cout << "md = median" << std::endl;
    std::cout << "b = both" << std::endl;
    std::cout << "" << std::endl;

    while (true)
    {
        std::cin >> mode;
        if (mode != "m" && mode != "md" && mode != "b")
        {
            std::cout << "You must input valid value!" << std::endl;
            continue;
        }
        break;
    }
}

int checkFileAvailability(std::string file)
{
    std::string fileText;
    std::ifstream f(file);

    if (!f.is_open())
    {
        std::cout << "Error opening the file!" << std::endl;
        return 1;
    }

    f.close();
    return 0;
}

void stripWhiteSpace(std::string &line, std::vector<std::string> &result)
{
    result.clear();
#ifndef USE_LIST
    result.reserve(8);
#endif

    const size_t len = line.size();
    size_t currPosition = 0;

    while (currPosition < len)
    {
        while (currPosition < len && isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        if (currPosition >= len)
            break;

        size_t start = currPosition;
        while (currPosition < len && !isspace(static_cast<unsigned char>(line[currPosition])))
            ++currPosition;
        result.emplace_back(line, start, currPosition - start);
    }
}

Student processStudentRow(std::vector<std::string> studentRow)
{

    assert(!(studentRow.size() == 0));

    std::string firstname = studentRow[0];
    std::string lastname = studentRow[1];

    Student student(firstname, lastname);

    for (std::size_t i = 2; i < studentRow.size(); i++)
    {
        double tempGrade = std::stoi(studentRow[i]);
        if (i + 1 == studentRow.size())
        {
            student.setExam(tempGrade);
        }
        else
        {

            student.addGrade(tempGrade);
        }
    }

    return student;
}

void generateRandomStudentFile(std::string fileName, int numOfLines)
{
    std::ofstream f(fileName);
    if (!f.is_open())
    {
        std::cout << "Error creating file!" << fileName << std::endl;
        return;
    }

    // create header
    f << std::left << std::setw(15) << "Name" << std::setw(15) << "Surname";
    for (int i = 0; i < 5; ++i)
        f << std::setw(5) << "HM" + std::to_string(i + 1);
    f << std::setw(5) << "Exam" << '\n';

    for (int i = 0; i < numOfLines; ++i)
    {
        f << std::left << std::setw(15) << "Name" + std::to_string(i + 1)
          << std::setw(15) << "Surname" + std::to_string(i + 1);

        for (int j = 0; j < 5; ++j)
        {
            f << std::setw(5) << getRandomGrade();
        }
        f << std::setw(5) << getRandomGrade() << '\n';
    }

    f.close();
    std::cout << std::endl;
    std::cout << "File " << fileName << " is successfully created." << '\n';
}

void loadStudentsFromFile(StudentContainer &students, std::string fileName)
{
    std::ifstream file(fileName);

    size_t numOfLines = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');

    file.clear();
    file.seekg(0);

    std::string curLine;
    std::getline(file, curLine); // skip header
    if (numOfLines > 0)
        --numOfLines;
#ifndef USE_LIST
    students.reserve(numOfLines);
#endif

    std::vector<std::string> row;

    while (getline(file, curLine))
    {
        if (curLine.empty())
        {
            continue;
        }

        stripWhiteSpace(curLine, row);
        Student student = processStudentRow(row);
        students.push_back(std::move(student));
    }
}

void createStudentFile(StudentContainer &studentList, std::string fileName)
{
    std::ofstream f(fileName);
    if (!f.is_open())
    {
        std::cout << "Error creating file!" << fileName << "\n";
        return;
    }

    f << createHeader("m");
    for (auto &student : studentList)
    {
        f << formatStudentRow(student, "m");
    }
    f.close();
    std::cout << "\n";
    std::cout << "File " << fileName << " is successfully created." << "\n";
}