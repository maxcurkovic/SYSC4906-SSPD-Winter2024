#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "pu1.hpp"
#include "pu2.hpp"
#include "pu3.hpp"
#include "sspp.hpp"
#include <iostream>

/**
 * Authors (Group Members):
 * Name: Yash Kapoor (Student ID: 101163338)
 * Name: Max Curkovic (Student ID: 101139937)
 */

SCENARIO("Wrapped PU1 in sspp executes") {
  GIVEN("A sspp object with 1 PU") {
    using namespace sspp;
    using input_t = std::array<int, 5>;
    SSPP<PU1> pipeline;
    WHEN("We run the pipeline one step") {
      input_t input = {1, 2, 3, 4, 5};
      auto output = pipeline.execute(input);
      THEN("There is output of 3.0s") {
        REQUIRE(output.has_value());
        for (auto item : output.value()) {
          REQUIRE(item == 3.0);
        }
      }
    }
    WHEN("We run the pipeline a second step") {
      input_t input = {1, 1, 1, 1, 1};
      auto output = pipeline.execute(input);
      THEN("There is output of 1.0s") {
        REQUIRE(output.has_value());
        for (auto item : output.value()) {
          REQUIRE(item == 1.0);
        }
      }
    }
    WHEN("We run the pipeline a third step with no input") {
      auto output = pipeline.execute();
      THEN("There is no output") {
            std::cout << "Executing test case: Test Case Name" << std::endl;
            REQUIRE_FALSE(output.has_value());
      }
    }
  }
}

SCENARIO("Integration test") {
  GIVEN("A sspp object with 3 PUs") {
    using namespace sspp;
    using input_t = std::array<int, 5>;
    SSPP<PU1, PU2, PU3> pipeline;
    WHEN("We run the pipeline") {
      input_t input1 = {1, 2, 3, 4, 5};
      auto o = pipeline.execute(input1);
      THEN("The output is empty") { REQUIRE_FALSE(o.has_value()); }
      input_t input2 = {0, 0, 0, 0, 0};
      o = pipeline.execute(input2);
      THEN("The output is empty") { REQUIRE_FALSE(o.has_value()); }
      input_t input3 = {3, 3, 4, 4, 5};
      o = pipeline.execute(input3);
      THEN("The output is 3") {
        REQUIRE(o.has_value());
        REQUIRE(o.value() == 3);
      }
      input_t input4 = {2, 2, 8, 8, 5};
      o = pipeline.execute(input4);
      THEN("The output is 3") {
        REQUIRE(o.has_value());
        REQUIRE(o.value() == 3);
      }
      // no more inputs
      o = pipeline.execute();
      THEN("The output is 3") {
        REQUIRE(o.has_value());
        REQUIRE(o.value() == 3);
      }
      o = pipeline.execute();
      THEN("The output is 5") {
        REQUIRE(o.has_value());
        REQUIRE(o.value() == 5);
      }
      o = pipeline.execute();
      THEN("There is no more output") { REQUIRE_FALSE(o.has_value()); }
    }
  }
}
