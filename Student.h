#pragma once
#include "Human.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

class Student : public Human
{
private:
    std::vector<int> grades_;
    int exam_{0};
    double finalGradeMean_{0.0};
    double finalGradeMedian_{0.0};

    friend std::istream &operator>>(std::istream &in, Student &s);
    friend std::ostream &operator<<(std::ostream &out, const Student &s);

public:
    // Constructors
    Student() = default;
    Student(std::string firstN, std::string lastN) : Human(std::move(firstN), std::move(lastN)) {}

    // Copy constructor
    Student(const Student &other) : Human(other.firstName_, other.lastName_),
                                    grades_(other.grades_),
                                    exam_(other.exam_),
                                    finalGradeMean_(other.finalGradeMean_),
                                    finalGradeMedian_(other.finalGradeMedian_)
    {
        std::cout << "Copy constructor is called\n";
    }

    // Copy assigment operator
    Student &operator=(const Student &other)
    {
        if (this != &other)
        {
            firstName_ = other.firstName_;
            lastName_ = other.lastName_;
            grades_ = other.grades_;
            exam_ = other.exam_;
            finalGradeMean_ = other.finalGradeMean_;
            finalGradeMedian_ = other.finalGradeMedian_;
        }
        std::cout << "Copy assigment operator is called\n";
        return *this;
    }

    // Getters
    const std::string &firstName() const override { return firstName_; }
    const std::string &lastName() const override { return lastName_; }
    const std::vector<int> &grades() const { return grades_; }
    int exam() const { return exam_; }
    double finalMean() const { return finalGradeMean_; }
    double finalMedian() const { return finalGradeMedian_; }

    // Setters
    void setFirstName(std::string v) override { firstName_ = std::move(v); }
    void setLastName(std::string v) override { lastName_ = std::move(v); }
    void addGrade(int g) { grades_.push_back(g); }
    void setExam(int e) { exam_ = e; }
    void setFinalMean(double v) { finalGradeMean_ = v; }
    void setFinalMedian(double v) { finalGradeMedian_ = v; }

    ~Student()
    {
        firstName_.clear();
        lastName_.clear();
        grades_.clear();
        std::cout << "Student object destroyed \n";
    }
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