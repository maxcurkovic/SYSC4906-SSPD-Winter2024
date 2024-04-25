#include <tuple>
#include <vector>
#include <optional>
#include <concepts>
#include <utility>

/**
 * Authors (Group Members):
 * Name: Yash Kapoor (Student ID: 101163338)
 * Name: Max Curkovic (Student ID: 101139937)
 *
 * We have documented important decisions in the code as comments below.
 * Also, we tested this file with the test cases that were provided on
 * Brightspace. They all successfully passed. You can run the "tests"
 * executable as specified in the MakeFile to ensure all of them pass as well.
 */
namespace sspp {

    /**
     * Concept that checks that the PU has an output function.
     * @tparam PU   the Processing Unit (e.g., PU1, PU2, PU3)
     */
    template<typename PU>
    concept HasOutputFunction = requires(PU pu) {
        pu.output();
    };

    template <typename... PUs>

    /**
     * Struct that defines the implementation of the SSPP.
     * This struct is designed to manage a sequence of Processing Units,
     * correctly processing input data.
     * @tparam PUs Template parameter that defines the PUs.
     */
    struct SSPP {
        // storing all the PUs in a tuple, allowing this program to handle
        // an arbitrary number of PUs. I added a tuple of PUs to ensure flexibility
        // in my design.
        std::tuple<PUs...> _pus;

        // The _inputs vector represents a stage in the processing
        // of the current input through the sequence of PUs.
        // This vector is tracking the remaining number of Processing Units
        // (PUs) that have yet to complete their processing for
        // the current input.
        std::vector<int> _inputs;

        // This is determined dynamically based on the output type of the last PU in the sequence.
        // Allows the SSPP to be flexible since it can automatically adapt to the
        // types of PUs it contains, ensuring the pipeline's final output type matches with the
        // last PU's output.
        using ReturnType = decltype(std::get<sizeof...(PUs) - 1>(_pus).output());

        // ensuring that each processing unit has an output function
        static_assert((HasOutputFunction<PUs> && ...), "All PUs must have an output function");

        /**
         * Defines the struct that defines the PU output.
         */
        struct output_t{
            std::optional<ReturnType> _value = std::nullopt;

            bool has_value() {
                return _value.has_value();
            }

            ReturnType value() {
                return _value.value();
            }
        };

        template <int I = sizeof...(PUs) - 1>
        /**
         * Method that processes all of the PUs.
         * It recursively invokes the input and output methods of the PUs in sequence.
         * This design ensures that data flows through the pipeline in the
         * correct order.
         * @tparam I Int I that defines the size of the list of PUs.
         */
        void process_all() {
            if constexpr (I == 0) {
                return;
            } else {
                auto&& r = std::get<I - 1>(_pus).output();
                std::get<I>(_pus).input(r);
                process_all<I - 1>();
            }
        }

        /**
         * Method that iterates over each element in the _inputs vector.
         * and decreases each element in _inputs by 1.
         * Tracks
         */
        void reduce_all() {
            for (int i = 0; i < _inputs.size(); i++) {
                _inputs[i]--;
            }
        }

        /**
        * Method to execute the SSPP when a new input is introduced into the PU.
        * When the PU has an input, this method shall be invoked.
        *
        * I have this method to ensure that the pipeline is reliable,
        * ensuring consistent state management across executions.
        *
        * This method includes strong exception safety by preserving the
        * pipeline's state unless the entire operation be successfully completed.
        *
        * @tparam T  Template T for the input.
        * We used a template to ensure that various types of PUs inputs
        * can be accepted to provide flexibility.
        *
        * @param input The input into the PU.
        * @return The output of the next PU in the sequence. Depending on what it is, it will either return null or the output of the next PU.
        */
        template <typename T>
        output_t execute(const T &input) { // Strong exception safety
            auto temp = _inputs;
            // We SAVE the temp variable, preserve any invariants and ensure no state changes.
            try {
                _inputs.insert(_inputs.begin(), sizeof...(PUs));

                process_all();
                reduce_all();
                std::get<0>(_pus).input(input);

                if (!_inputs.empty() && _inputs.back() == 0) {
                    _inputs.pop_back();

                    return output_t{std::get<sizeof...(PUs) - 1>(_pus).output()};
                }

                return output_t{std::nullopt};
            } catch (...){
                // If an exception is caught within the try block,
                // switch the temp back into the inputs and restore the original inputs,
                // then throw the exception.
                std::swap(_inputs, temp);
                throw;
            }
        }

        /**
         * Method to execute the SSPP.
         * When the PU has no input, this method shall get executed.
         *
         * This method includes basic exception safety by ensuring that
         * if there is an exception, the system state gets reset instead of being
         * left in an inconsistent state.
         *
         * @return Similar to above, it returns the next PU output
         *         in the sequence or, if there is no output, it returns null.
         */
        output_t execute() { // Basic exception safety
            try{
                // To ensure basic exception safety, we enclose the functionality in a try block...
                process_all();
                reduce_all();

                if (!_inputs.empty() && _inputs.back() == 0){
                    _inputs.pop_back();

                    return output_t{std::get<sizeof...(PUs) - 1>(_pus).output()};
                }

                return output_t{std::nullopt};
            } catch (...){
                // ...if an exception is caught, we do not care about the state of the program,
                // so we reset the inputs and catch the exception.
                _inputs = std::vector<int>();
                throw;    // signals failure
            }
        }
    };
} // namespace sspp

