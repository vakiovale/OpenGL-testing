#include "file_loader.h"

#include "catch.hpp"

SCENARIO("File loader", "[file]") {
    GIVEN("Given a file and a file loader") {
        FileLoader file_loader;
        WHEN("when loading file to a string") {
            std::string file = "resources/test.txt";
            std::string content = file_loader.load(file);
            THEN("string should match file's content") { REQUIRE(content == "Hello World!\n"); }
        }
    }
}
