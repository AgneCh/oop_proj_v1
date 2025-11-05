#pragma once
#include <string>
#include <vector>
#include <list>

class Student
{
private:
    std::string firstName_;
    std::string lastName_;
    std::vector<int> grades_;
    int exam_{0};
    double finalGradeMean_{0.0};
    double finalGradeMedian_{0.0};

public:
    // Constructors
    Student() = default;
    Student(std::string firstN, std::string lastN) : firstName_(std::move(firstN)), lastName_(std::move(lastN)) {}

    // Getters
    const std::string &firstName() const { return firstName_; }
    const std::string &lastName() const { return lastName_; }
    const std::vector<int> &grades() const { return grades_; }
    int exam() const { return exam_; }
    double finalMean() const { return finalGradeMean_; }
    double finalMedian() const { return finalGradeMedian_; }

    // Setters
    void setFirstName(std::string v) { firstName_ = std::move(v); }
    void setLastName(std::string v) { lastName_ = std::move(v); }
    void addGrade(int g) { grades_.push_back(g); }
    void setExam(int e) { exam_ = e; }
    void setFinalMean(double v) { finalGradeMean_ = v; }
    void setFinalMedian(double v) { finalGradeMedian_ = v; }

    ~Student() {}
};

#ifdef USE_LIST
using StudentContainer = std::list<Student>;
inline const char *getContainerName()
{
    return "std::list<Student>";
}
#else
using StudentContainer = std::vector<Student>;
inline const char *getContainerName()
{
    return "std::vector<Student>";
}
#endif