#include <functional>
#include <map>
#include "commands/CCommand.hpp"

namespace CPTest {

class CUtilsCommand : public CCommand
{
public:
    CUtilsCommand();

    EResult run(const std::vector<std::string>& args);

private:
    EResult testCount(const std::vector<std::string>& args);
    EResult testFolder(const std::vector<std::string>& args);
    EResult isProblemDir(const std::vector<std::string>& args);

private:
    std::map<std::string, std::function<EResult(const std::vector<std::string>&)>> m_funcs;
};

} // namespace CPTest
