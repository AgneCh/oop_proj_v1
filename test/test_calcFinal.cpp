#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../GradeCalc.h"
#include <vector>


TEST_CASE("calcFinalGrade correctly computes final grade (mean and median)", "[Student]") {
    
    Student s("Test", "Tester");

    // hw grades
    s.addGrade(7);
    s.addGrade(8);
    s.addGrade(9);

    // exam grade
    s.setExam(10);

    s = calcFinalGrade(s);

    
    REQUIRE(s.finalMean() == Approx(9.2));
    REQUIRE(s.finalMedian() == Approx(9.2));
}