#include "CommandFactory.hpp"
#include <cassert>
#include "commands/InitCommand.hpp"
#include "commands/TestCommand.hpp"
#include "commands/UtilsCommand.hpp"

namespace CPTest {

CCommandFactory::CCommandFactory()
{
    createFuncRegistrator<static_cast<CommandType>(0)>();

    m_str_to_cmd_map.insert({"init", CommandType::Init});
    m_str_to_cmd_map.insert({"test", CommandType::Test});
    m_str_to_cmd_map.insert({"utils", CommandType::Utils});
}

std::shared_ptr<ICommand> CCommandFactory::create(int argc, char** argv)
{
    auto itr = m_str_to_cmd_map.find(argv[1]);
    if (itr == m_str_to_cmd_map.end())
    {
        throw std::runtime_error("Command is not registered");
    }
    return (this->*m_create_func[static_cast<std::size_t>(itr->second)])(argc, argv);
}

template <CommandType type>
void CCommandFactory::createFuncRegistrator()
{
    m_create_func[static_cast<std::size_t>(type)] = &CCommandFactory::createImpl<type>;
    createFuncRegistrator<static_cast<CommandType>(static_cast<std::size_t>(type) + 1)>();
}

template <>
void CCommandFactory::createFuncRegistrator<CommandType::Total>()
{
}

template <>
std::shared_ptr<ICommand> CCommandFactory::createImpl<CommandType::Init>(int argc, char** argv)
{
    return std::make_shared<CInitCommand>();
}

template <>
std::shared_ptr<ICommand> CCommandFactory::createImpl<CommandType::Test>(int argc, char** argv)
{
    return std::make_shared<CTestCommand>();
}

template <>
std::shared_ptr<ICommand> CCommandFactory::createImpl<CommandType::Utils>(int argc, char** argv)
{
    return std::make_shared<CUtilsCommand>();
}

template <>
std::shared_ptr<ICommand> CCommandFactory::createImpl<CommandType::Total>(int argc, char** argv)
{
    return nullptr;
}

} // namespace CPTest
