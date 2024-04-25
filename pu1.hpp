#include <array>

/**
 * Authors (Group Members):
 * Name: Yash Kapoor (Student ID: 101163338)
 * Name: Max Curkovic (Student ID: 101139937)
 */
namespace sspp {
    struct PU1 {
        void input(const std::array<int, 5> &arr) {
            int sum = 0;
            for (int i = 0; i < 5; i++) {
                sum += arr[i];
            }
            float average = static_cast<float>(sum) / 5;

            for (int i = 0; i < 3; i++) {
                _output[i] = average;
            }
        }

        std::array<float, 3> output() { return this->_output; }

    private:
        std::array<float, 3> _output;
    };
} // namespace sspp