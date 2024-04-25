#include <cmath>

/**
 * Authors (Group Members):
 * Name: Yash Kapoor (Student ID: 101163338)
 * Name: Max Curkovic (Student ID: 101139937)
 */
namespace sspp {
    struct PU3 {
        void input(float f) {
            _output = std::floor(f);
        }

        int output() { return this->_output; }

    private:
        int _output;
    };
} // namespace sspp