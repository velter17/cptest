#pragma once

#include <algorithm>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "advanced_terminal_output/table.hpp"

namespace CPTest {

inline void parseRange(const std::string& s, std::vector<std::size_t>& tests)
{
    std::vector<std::size_t> ret;

    std::size_t i = 0;
    std::size_t x = 0;
    bool is_dash = false;
    while (i < s.length())
    {
        char c = s[i++];
        if (c == ',' || c == '-' || i == s.length())
        {
            if (i == s.length())
            {
                if (!std::isdigit(c))
                {
                    throw std::runtime_error(
                        std::string("Unrecognized character ") + c + " is test range");
                }
                x = x * 10 + c - '0';
            }
            ret.push_back(x);
            x = 0;
        }
        else if (std::isdigit(c))
        {
            x = x * 10 + c - '0';
        }
        else
        {
            throw std::runtime_error(std::string("Unrecognized character ") + c + " is test range");
        }
        is_dash |= c == '-';
    }
    if (ret.size() == 2 && is_dash)
    {
        auto t(std::move(ret));
        if (t.front() > t.back())
        {
            throw std::runtime_error("Invalid test range");
        }
        ret.resize(std::min<std::size_t>(100, t.back() - t.front() + 1));
        std::iota(ret.begin(), ret.end(), t.front());
    }

    for (const auto& it : ret)
    {
        tests.push_back(it);
    }
}

inline AdvancedTerm::Cell split(const std::string& s)
{
    const std::size_t width_max = 50;
    const std::size_t height_max = 50;
    using additional_info_color = termcolor::color<termcolor::LightBlue>;
    std::stringstream str(s);
    std::vector<AdvancedTerm::Data> data_vec;
    std::string temp;
    int additional_lines = 0;
    bool f = false;
    while (std::getline(str, temp))
    {
        if (f)
        {
            data_vec.push_back(AdvancedTerm::createData("\n"));
        }
        f = true;
        if (data_vec.size() < height_max)
        {
            if (temp.length() > width_max)
            {
                auto d1 = AdvancedTerm::createData(temp.substr(0, width_max));
                auto d2 = AdvancedTerm::createData<additional_info_color>(
                    " ... [ +" + std::to_string(temp.length() - width_max) + " ]");
                data_vec.emplace_back(d1);
                data_vec.emplace_back(d2);
            }
            else 
            {
                data_vec.push_back(AdvancedTerm::createData(temp));
            }
        }
        else
        {
            ++additional_lines;
            f = false;
        }
    }
    if (additional_lines > 0)
    {
        data_vec.push_back(AdvancedTerm::createData<additional_info_color>("...\n"));
        data_vec.push_back(AdvancedTerm::createData<additional_info_color>("[ + " + std::to_string(additional_lines) + " lines ]\n"));
    }
    return AdvancedTerm::Cell(AdvancedTerm::EAlign::Left, 1, 1, data_vec);
}

} // namespace CPTest
