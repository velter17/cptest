#include "output/output.hpp"
#include <string>
#include "termcolor/termcolor.hpp"

namespace CPTest {

void out(const std::string& message)
{
    std::cout << message << std::endl;
}

void info(const std::string& message)
{
    std::cout << " [ " << termcolor::apply<termcolor::bold_color<termcolor::Green>> << "Info"
              << termcolor::reset << " ] " << message << std::endl;
}

void error(const std::string& message)
{
    std::cout << " [ " << termcolor::apply<termcolor::bold_color<termcolor::Red>> << "Error"
              << termcolor::reset << " ] " << message << std::endl;
}

void warning(const std::string& message)
{
    std::cout << " [ " << termcolor::apply<termcolor::bold_color<termcolor::Yellow>> << "Warning"
              << termcolor::reset << " ] " << message << std::endl;
}

} // namespace CPTest
