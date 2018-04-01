#pragma once

#include <boost/program_options.hpp>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "ICommand.hpp"
#include "output/output.hpp"
#include "boost_options_extended/OptionPrinter.hpp"

namespace CPTest {

class CCommand : public ICommand
{
public:
    CCommand();

    const std::string helpMessage() const override;
    const std::string manMessage() const override;
    void terminate() override;

protected:
    ICommand::EResult readArgs(const std::vector<std::string>& args);

protected:
    boost::program_options::variables_map m_var_map;
    boost::program_options::options_description m_desc;
    boost::program_options::positional_options_description m_positional;
};

inline CCommand::CCommand()
    : m_desc("Allowed options")
{
    m_desc.add_options()
        ("help,h", "Help message")
        ("man,?", "manual message");
}

inline const std::string CCommand::helpMessage() const
{
    std::stringstream ss;
    ss << m_desc;
    return ss.str();
}

inline const std::string CCommand::manMessage() const
{
    return std::string("No man message");
}

inline void CCommand::terminate()
{
    throw std::runtime_error("CCommand: terminate command is not defined");
}

inline ICommand::EResult CCommand::readArgs(const std::vector<std::string>& args)
{
    try
    {
        boost::program_options::parsed_options parser =
            boost::program_options::command_line_parser(args)
                .options(m_desc)
                .positional(m_positional)
                .run();
        boost::program_options::store(parser, m_var_map);
    }
    catch (boost::program_options::required_option e)
    {
        //rad::OptionPrinter::formatRequiredOptionError(e);
        error(e.what());

        return EResult::Failed;
    }

    if (m_var_map.count("help"))
    {
        rad::OptionPrinter::printStandardAppDesc("command", std::cout, m_desc, &m_positional);
        return EResult::Terminated;
    }
    if (m_var_map.count("manual"))
    {
        out(manMessage());
        return EResult::Terminated;
    }

    boost::program_options::notify(m_var_map);
    return EResult::Success;
}

} // namespace CPTest
