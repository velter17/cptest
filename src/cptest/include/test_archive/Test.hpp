#pragma once

#include <string>

namespace CPTest {
namespace TestArchive {

class CTest
{
public:
    CTest(
        const std::string& input_data,
        const std::string& output_data,
        const std::string& additional_data = std::string());

    const std::string& getInput() const;
    const std::string& getOutput() const;
    const std::string& getAdditionalData() const;

private:
    std::string m_input;
    std::string m_output;
    std::string m_additional_data;
};

} // namespace TestArchive
} // namespace CPTest
