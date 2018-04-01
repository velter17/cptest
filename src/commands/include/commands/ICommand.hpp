#pragma once

#include <string>
#include <vector>

namespace CPTest {

class ICommand
{
public:
    enum class EResult
    {
        Success,
        Failed,
        Terminated,
    };
public:
    virtual EResult run(const std::vector<std::string>& args) = 0;
    virtual const std::string helpMessage() const = 0;
    virtual const std::string manMessage() const = 0;
    virtual void terminate() = 0;

    virtual ~ICommand() = default;
};

} // namespace CPTest
