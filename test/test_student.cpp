#include "catch.hpp"
#include "Student.h"

TEST_CASE("Copy constructor copies homework grades independently", "[Student]"){
    Student original("Test", "Tester");

    // hw grades
    original.addGrade(6);
    original.addGrade(8);
    original.addGrade(10);

    Student copy = original;

    // hw must match after copy
    REQUIRE(copy.grades() == original.grades());

    // modify the original
    original.addGrade(3);

    // copy must not change
    std::vector<int> expectedCopyHW = {6, 8, 10};
    REQUIRE(copy.grades() == expectedCopyHW);

    // original has the new value
    std::vector<int> expectedOriginalHW = {6, 8, 10, 3};
    REQUIRE(original.grades() == expectedOriginalHW);

}