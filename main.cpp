#include <iostream>
#include <array>
#include "pu1.hpp"
#include "pu2.hpp"
#include "pu3.hpp"
#include "sspp.hpp"

int main() {
    // Creating an instance of SSPP with PU1, PU2, and PU3.
    sspp::SSPP<sspp::PU1, sspp::PU2, sspp::PU3> pipeline;

    // Example execution cases provided in the assignment description
    std::array cases{
            std::array<int, 5>{1, 2, 3, 4, 5},
            std::array<int, 5>{0, 0, 0, 0, 0},
            std::array<int, 5>{3, 3, 4, 4, 5},
            std::array<int, 5>{2, 2, 8, 8, 5}
    };

    // Going through each example case
    for (const auto& case_input : cases) {
        // Print the current case being processed
        if (!case_input.empty()) {
            std::cout << "\nProcessing input: ";
            for (const auto &val: case_input) {
                std::cout << val << " ";
            }
            std::cout << std::endl;

            auto result = pipeline.execute(case_input);
            if (result.has_value()) {
                std::cout << "Output: " << result.value() << std::endl;
            } else {
                std::cout << "No output" << std::endl;
            }
        }
    }

    // After processing all cases that have an input
    std::cout << "\nProcessing case with no input" << std::endl;
    auto result = pipeline.execute();
    if (result.has_value()) {
        std::cout << "Output from no input: " << result.value() << std::endl;
    } else {
        std::cout << "No output from no input." << std::endl;
    }

    std::cout << "\nProcessing case with no input" << std::endl;
    result = pipeline.execute();
    if (result.has_value()) {
        std::cout << "Output from no input: " << result.value() << std::endl;
    } else {
        std::cout << "No output from no input." << std::endl;
    }

    std::cout << "\nProcessing case with no input" << std::endl;
    result = pipeline.execute();
    if (result.has_value()) {
        std::cout << "Output from no input: " << result.value() << std::endl;
    } else {
        std::cout << "No output from no input." << std::endl;
    }

    std::cout << "\nProcessing case with no input" << std::endl;
    result = pipeline.execute();
    if (result.has_value()) {
        std::cout << "Output from no input: " << result.value() << std::endl;
    } else {
        std::cout << "No output from no input." << std::endl;
    }

    return 0;
}
