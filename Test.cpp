
#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>

using namespace ariel;
using namespace std;

static vector<string> units = {"m"};
ifstream units_file{"units.txt"};


TEST_CASE("Addition Testing"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{12, "km"};
    NumberWithUnits b{2, "m"};
    NumberWithUnits c{2, "sec"};
    CHECK_EQ(a+b , NumberWithUnits{12.002, "km"});
    CHECK_EQ(b+a , NumberWithUnits{12002, "m"});
    CHECK_THROWS(a+c);
    CHECK_THROWS(c+a);
}


TEST_CASE("Subtraction Testing"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{12, "km"};
    NumberWithUnits b{250,"m"};

    CHECK_EQ(a - b, NumberWithUnits{11.750,"km"});

}


TEST_CASE("Increment/Decrement Operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "km"};
    CHECK(a++ == NumberWithUnits{5, "km"});
    CHECK(a == NumberWithUnits{6, "km"});
    CHECK(++a == NumberWithUnits{7, "km"});
    CHECK(a == NumberWithUnits{7, "km"});
    CHECK(a-- == NumberWithUnits{7, "km"});
    CHECK(a == NumberWithUnits{6, "km"});
    CHECK(--a == NumberWithUnits{5, "km"});
    CHECK(a == NumberWithUnits{5, "km"});
}

TEST_CASE("+=, -= operators"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{10, "km"};
    NumberWithUnits b{3000, "m"};
    CHECK((a+=b) == NumberWithUnits{13, "km"});
    CHECK(a == NumberWithUnits{13, "km"});
    CHECK((b+=a) == NumberWithUnits{16000, "m"});
    CHECK(b == NumberWithUnits{16000, "m"});
    CHECK((a-=b) == NumberWithUnits{-3, "km"});
    CHECK(a == NumberWithUnits{-3, "km"});
    CHECK((b-=a) == NumberWithUnits{19000, "m"});
    CHECK(b == NumberWithUnits{19000, "m"});
}

TEST_CASE("Multiplication operators: {float*x, x*float, x*=float, float*=x}"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};

    CHECK((a*0.5) == NumberWithUnits{1, "km"});
    CHECK((2.7*a) == NumberWithUnits{5.4, "km"});
    CHECK((a*=3.5) == NumberWithUnits{7, "km"});
    CHECK(a == NumberWithUnits{7, "km"});
}

TEST_CASE("Comparison operators: {>, >=, <, <=, ==, !=}"){
    NumberWithUnits::read_units(units_file);

    CHECK_LT(NumberWithUnits{2, "km"}  , NumberWithUnits{3000, "m"});
    CHECK_GT(NumberWithUnits{3000, "m"}, NumberWithUnits{2, "km"});
    CHECK_NE(NumberWithUnits{2, "km"}  , NumberWithUnits{3000, "m"});
    CHECK_NE(NumberWithUnits{3000, "m"}, NumberWithUnits{2, "km"});

    CHECK_LT(NumberWithUnits{90, "cm"} , NumberWithUnits{3000, "m"});
    CHECK_GT(NumberWithUnits{3000, "m"}, NumberWithUnits{90, "cm"});
    CHECK_NE(NumberWithUnits{90, "cm"} , NumberWithUnits{3000, "m"});
    CHECK_NE(NumberWithUnits{3000, "m"}, NumberWithUnits{90, "cm"});

    CHECK_EQ(NumberWithUnits{300, "cm"}, NumberWithUnits{3, "m"});
    CHECK_EQ(NumberWithUnits{3, "m"}, NumberWithUnits{300, "cm"});

}
