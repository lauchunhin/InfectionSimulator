#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch_test_macros.hpp>
#include "infection.h"
#include <sstream>


TEST_CASE("Test max function", "[max]") {
    SECTION("Test case 1") {
        REQUIRE(max(5, 10) == 10);
    }
    SECTION("Test case 2") {
        REQUIRE(max(-5, -10) == -5);
    }
    SECTION("Test case 3") {
        REQUIRE(max(0, 0) == 0);
    }
}

TEST_CASE("Test isDoctor function", "[isDoctor]") {
    SECTION("Test case 4") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', 'p', '.', '.', 'p', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F'}
        };
        REQUIRE(isDoctor(map, width, height, 0, 0) == false);
        REQUIRE(isDoctor(map, width, height, 5, 5) == true);
    }
}

TEST_CASE("Test isInfected function", "[isInfected]") {
    SECTION("Test case 5") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', '9', '.', '.', '1', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F'}
        };
        REQUIRE(isInfected(map, width, height, 0, 0) == false);
        REQUIRE(isInfected(map, width, height, 4, 1) == true);
    }
}


TEST_CASE("Test printMap and infect functions", "[printMap]") {
    SECTION("Test case 6") {
        int width = 6;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', 'p', '.', '.', 'p', '.'}
        };
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = ". p . p . . \n"
                                     "p p p . p . \n"
                                     ". p . p p . \n"
                                     "p p . . . p \n"
                                     ". p . . p . \n";
        REQUIRE(output.str() == expectedOutput);
    }
    
    SECTION("Test case 7") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = ". p . p . \n"
                                     "p p p . p \n"
                                     ". p . p p \n"
                                     "p p . . . \n"
                                     ". p . . p \n"
                                     "p p p p p \n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Test case 8") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        REQUIRE(infect(map, width, height, 1, 1) == 27);
    }

    //this test case is very similar to the previous test case
    //the only difference is that we do not output the return value of the infect function
    SECTION("Test case 9") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        infect(map, width, height, 1, 1);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = ". v v v v \n"
                                     "v v v v v \n"
                                     "v v v v v \n"
                                     "v v v v v \n"
                                     "v v . v v \n"
                                     "v v v v v \n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Test case 10") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', '.', '.'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', '.', '.', '.', '.'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        REQUIRE(infect(map, width, height, 4, 5) == 20);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = "v v . p p \n"
                                     "v v v . . \n"
                                     "v v . v v \n"
                                     "v v v v v \n"
                                     "v . . . . \n"
                                     "v v v v v \n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Test case 11") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        REQUIRE(infect(map, width, height, 0, 0) == 0);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = ". p . p . \n"
                                     "p p p . p \n"
                                     ". p . p p \n"
                                     "p p . . . \n"
                                     ". p . . p \n"
                                     "p p p p p \n";
        REQUIRE(output.str() == expectedOutput);
    }    
}

TEST_CASE("Test countCharacter function", "[countCharacter]") {
    SECTION("Test case 12") {
        int width = 6;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', 'p', '.', '.', 'p', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F'}
        };
        REQUIRE(countCharacter(map, width, height, '.') == 10);
        REQUIRE(countCharacter(map, width, height, 'p') == 14);
        REQUIRE(countCharacter(map, width, height, 'A') == 1);
    }

    SECTION("Test case 13") {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'v'},
            {'.', 'p', '.', 'v', 'v'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        REQUIRE(countCharacter(map, width, height, 'p') == 15);
        REQUIRE(countCharacter(map, width, height, 'v') == 3);
        REQUIRE(countCharacter(map, width, height, '.') == 12);
    }
}

TEST_CASE("Test getProtectionLevel function", "[getProtectionLevel]") {
    SECTION("Test case 14") {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        REQUIRE(getProtectionLevel(map, width, height, 3, 2) == 0);
        REQUIRE(getProtectionLevel(map, width, height, 2, 2) == 2);
        REQUIRE(getProtectionLevel(map, width, height, 4, 2) == 2);
        REQUIRE(getProtectionLevel(map, width, height, 3, 1) == 2);
        REQUIRE(getProtectionLevel(map, width, height, 3, 3) == 0);
    }

    SECTION("Test case 15") {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'C', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'A', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        REQUIRE(getProtectionLevel(map, width, height, 3, 2) == 0);
        REQUIRE(getProtectionLevel(map, width, height, 2, 2) == 0);
        REQUIRE(getProtectionLevel(map, width, height, 4, 2) == 2);
        REQUIRE(getProtectionLevel(map, width, height, 3, 1) == 3);
        REQUIRE(getProtectionLevel(map, width, height, 3, 3) == 0);
    }
}

TEST_CASE("Test infectWithPower function", "[infectWithPower]") {
    SECTION("Test case 16") {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'p', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        infectWithPower(map, width, height, 1, 1, 3);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = ". 2 . p . . . p \n"
                                     "2 3 2 1 p . . . \n"
                                     ". 2 1 p p . . p \n"
                                     ". . . . p p . p \n"
                                     ". . . . p . . . \n";
        REQUIRE(output.str() == expectedOutput);
    }

    SECTION("Test case 17") {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        infectWithPower(map, width, height, 3, 3, 8);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = "2 3 4 5 4 3 2 1 \n"
                                     "3 4 5 6 5 4 3 2 \n"
                                     "4 5 6 7 6 5 4 3 \n"
                                     "5 6 7 8 7 6 5 4 \n"
                                     "4 5 6 7 6 5 4 3 \n"
                                     "3 4 5 6 5 4 3 2 \n"
                                     "2 3 4 5 4 3 2 1 \n"
                                     "1 2 3 4 3 2 1 p \n";
        REQUIRE(output.str() == expectedOutput);
    }
    
    SECTION("Test case 18") {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'C', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        infectWithPower(map, width, height, 3, 3, 8);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = "2 3 4 5 4 3 2 1 \n"
                                     "3 4 5 6 5 4 3 2 \n"
                                     "4 5 6 7 6 5 4 3 \n"
                                     "5 6 7 8 7 6 5 4 \n"
                                     "4 5 6 7 6 5 4 3 \n"
                                     "3 4 5 6 5 C p 2 \n"
                                     "2 3 4 5 4 p p 1 \n"
                                     "1 2 3 4 3 2 1 p \n";
        REQUIRE(output.str() == expectedOutput);
    }
}

TEST_CASE("Test random function", "[random]") {
    SECTION("Test case 19") {
        REQUIRE(random(1234, 1) == 5227);
        REQUIRE(random(1234, 2) == 3215);
        REQUIRE(random(1234, 3) == 3362);
        REQUIRE(random(1234, 4) == 3030);
    }
    
    SECTION("Test case 20") {
        REQUIRE(random(1001, 1) == 20);
        REQUIRE(random(1001, 2) == 4);
        REQUIRE(random(1001, 3) == 0);
        REQUIRE(random(1001, 4) == 0);
    }
}

TEST_CASE("Test infectWithProbability function", "[infectWithProbability]") {
    SECTION("Test case 21") {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = "p p p p p p p p \n"
                                     "p p p p 4 p p p \n"
                                     "p p p 4 3 4 p p \n"
                                     "p p 4 3 2 3 4 p \n"
                                     "p 4 3 2 1 2 3 4 \n"
                                     "p p 4 3 2 3 4 p \n"
                                     "p p p 4 3 4 p p \n"
                                     "p p p p 4 p p p \n";
        REQUIRE(output.str() == expectedOutput);
    }
    
    SECTION("Test case 22") {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', '.', '.', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        std::stringstream output;
        printMap(map, width, height);
        std::string expectedOutput = "p p p p p p p p \n"
                                     "p p p p 4 p p p \n"
                                     "p p p 4 3 4 p p \n"
                                     "p p 4 3 2 3 4 p \n"
                                     "p 4 3 2 1 2 3 4 \n"
                                     "p p 4 . . 3 4 p \n"
                                     "p p p p p 4 p p \n"
                                     "p p p p p p p p \n";
        REQUIRE(output.str() == expectedOutput);
    }
}