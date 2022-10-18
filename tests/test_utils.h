#ifndef SLIB_TESTS_TEST_UTILS_H_
#define SLIB_TESTS_TEST_UTILS_H_

#include <string>
#include <source_location>

#ifndef __cpp_lib_source_location
static_assert(false, "Need compiler supporting source_location c++20 std lib");
#endif

std::string ToString(
    const std::source_location location = std::source_location::current()) {
    using namespace std::string_literals;
    std::stringstream ss;
    return location.file_name() + "("s + std::to_string(location.line()) +
           ":"s + std::to_string(location.column()) + ") `"s +
           location.function_name() + "`"s;
}

#endif  // SLIB_TESTS_TEST_UTILS_H_