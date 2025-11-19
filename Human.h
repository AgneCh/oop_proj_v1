#pragma once
#include <string>
#include <iostream>

class Human
{
protected:
    std::string firstName_;
    std::string lastName_;

public:
    Human() = default;
    Human(std::string firstN, std::string lastN) : firstName_(std::move(firstN)), lastName_(std::move(lastN)) {}

    virtual const std::string &firstName() const = 0;
    virtual const std::string &lastName() const = 0;
    virtual void setFirstName(std::string) = 0;
    virtual void setLastName(std::string) = 0;

    virtual ~Human()
    {
        std::cout << "Human destructor called\n";
    }
};