#include <memory>
#include <map>
#include "commands/ICommand.hpp"

namespace CPTest {

enum class CommandType
{
    Init,
    Test,

    Utils,

    Total
};

class CCommandFactory
{
public:
    CCommandFactory();

    std::shared_ptr<ICommand> create(int argc, char** argv);

private:
    template <CommandType type>
    void createFuncRegistrator();

    template <CommandType type>
    std::shared_ptr<ICommand> createImpl(int argc, char** argv);

    using TCreatorFunc = std::shared_ptr<ICommand> (CCommandFactory::*)(int, char**);

private:
    std::map<std::string, CommandType> m_str_to_cmd_map;
    TCreatorFunc m_create_func[static_cast<std::size_t>(CommandType::Total) + 1];
};

} // namespace CPTest
