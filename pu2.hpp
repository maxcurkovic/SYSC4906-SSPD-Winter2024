#include <array>
#include <algorithm>
#include <limits>

/**
 * Authors (Group Members):
 * Name: Yash Kapoor (Student ID: 101163338)
 * Name: Max Curkovic (Student ID: 101139937)
 */
namespace sspp {
    struct PU2 {
        void input(const std::array<float, 3> &arr) {
            auto it_max = std::max_element(arr.begin(), arr.end());
            this->_output = std::max(*it_max, _output);
        }

        float output() { return this->_output; }

    private:
        float _output=std::numeric_limits<float>::min();
    };
} // namespace sspp