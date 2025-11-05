#include "GradeCalc.h"
#include <algorithm>
#include <random>
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

int getRandomGrade()
{
    static mt19937 gen(random_device{}()); // seed once
    static uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

double hwMean(const std::vector<int> &grades)
{
    if (grades.empty())
    {
        return 0.0;
    }

    double sum = 0.0;
    for (double i : grades)
        sum += i;
    return sum / grades.size();
}

double hwMedian(std::vector<int> grades)
{
    if (grades.empty())
    {
        return 0.0;
    }

    std::sort(grades.begin(), grades.end());
    int n = grades.size();
    if (n % 2 != 0)
    {
        return grades[n / 2];
    }
    else
    {
        return (grades[(n - 1) / 2] + grades[n / 2]) / 2.0;
    }
}

Student calcFinalGrade(Student student)
{
    const double mean = hwMean(student.grades());
    const double median = hwMedian(student.grades());

    student.setFinalMean(0.4 * mean + 0.6 * student.exam());
    student.setFinalMedian(0.4 * median + 0.6 * student.exam());

    return student;
}