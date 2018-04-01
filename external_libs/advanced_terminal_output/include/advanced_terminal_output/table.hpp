#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include "termcolor/termcolor.hpp"

namespace {

#define LUBORDER "+"
#define RUBORDER "+"
#define LBBORDER "+"
#define RBBORDER "+"
#define HORBORDER "-"
#define VERBORDER "|"
#define BORDERBOTTOM "-"
#define BORDERRIGHT "|"
#define BORDERLEFT "|"
#define BORDERUP "-"
#define PLUSBORDER "+"

/*#define LUBORDER "┌"
#define RUBORDER "┐"
#define LBBORDER "└"
#define RBBORDER "┘"
#define HORBORDER "─"
#define VERBORDER "│"
#define BORDERBOTTOM "─"
#define BORDERRIGHT "│"
#define BORDERLEFT "│"
#define BORDERUP "─"
#define PLUSBORDER "┼"
*/

#define SPACE ' '

} // anonymous namespace

namespace AdvancedTerm {

enum EAlign
{
    Left,
    Right,
    Center,
};

/**
 * Data chunk with same color
 *
 * */
class Data
{
public:
    Data(const std::string& data, termcolor::color_t color);

    std::string operator()() const;
    const std::string& string() const;
    std::size_t width() const;
    termcolor::color_t color() const;
private:
    termcolor::color_t m_color;
    std::string m_data;
};

template <typename Color = termcolor::color<termcolor::Empty>, typename T>
Data createData(const T& data);

class Cell
{
public:
    Cell(EAlign align, int collspan, int rowspan, const std::vector<Data>& data);

    const std::vector<Data>& operator()(std::size_t i) const;
    std::size_t size() const;
    std::size_t size(std::size_t i) const;
    std::size_t collspan() const;
    EAlign align() const;
    std::size_t width() const;
    std::size_t width(std::size_t i) const;
    std::string data(std::size_t i) const;

private:
    std::vector<std::vector<Data>> m_data;
    EAlign m_align;
    std::size_t m_collspan;
    std::size_t m_rowspan;
};

template <typename T>
Data push_data(const T& data);

template <>
Data push_data<Data>(const Data& data);

template <EAlign Align = EAlign::Left, int Collspan = 1, int Rowspan = 1, typename... T>
Cell createCell(const T&... data);

using Row = std::vector<Cell>;
using Table = std::vector<Row>;

template <typename T>
Cell push_row_data(const T& data);

template <>
Cell push_row_data<Cell>(const Cell& cell);

template <typename... TTypes>
Row createRow(const TTypes&... data);

template <typename T>
Row push_table_data(const T& data);

template <>
Row push_table_data<Row>(const Row& row);

template <typename... TTypes>
Table createTable(const TTypes&... data);

//-----------------------------------------
//-----------------------------------------

inline Data::Data(const std::string& data, termcolor::color_t color)
    : m_data(data)
    , m_color(color)
{
}

inline std::string Data::operator()() const
{
    std::stringstream ss;
    ss << m_color << m_data << termcolor::reset;
    return ss.str();
}

inline const std::string& Data::string() const
{
    return m_data;
}

inline std::size_t Data::width() const
{
    return m_data.length();
}

inline termcolor::color_t Data::color() const
{
    return m_color;
}

template <typename T>
Data push_cell_data(const T& data)
{
    return createData(data);
}

template <>
Data push_cell_data<Data>(const Data& data)
{
    return data;
}

inline Cell::Cell(EAlign align, int collspan, int rowspan, const std::vector<Data>& data)
    : m_align(align)
    , m_collspan(collspan)
    , m_rowspan(rowspan)
{
    if (data.empty())
    {
        return;
    }

    std::size_t i = 0;
    std::size_t search_pos = 0;
    while (i < data.size())
    {
        if (i == 0)
        {
            m_data.push_back({});
        }

        const auto& d = data[i];
        while (true)
        {
            auto pos = d.string().find("\n", search_pos);
            if (pos == std::string::npos)
            {
                m_data.back().emplace_back(d.string().substr(search_pos), d.color());
                search_pos = 0;
                ++i;
                break;
            }
            else
            {
                m_data.back().emplace_back(
                    d.string().substr(search_pos, pos - search_pos), d.color());
                m_data.push_back({});
                search_pos = pos + 1;
                if (search_pos == d.string().length())
                {
                    search_pos = 0;
                    ++i;
                    break;
                }
            }
        }
    }
}

template <typename Color = termcolor::color<termcolor::Empty>, typename T>
inline Data createData(const T& data)
{
    std::stringstream ss;
    ss << data;
    return Data{ss.str(), termcolor::apply<Color>};
}

inline const std::vector<Data>& Cell::operator()(std::size_t i) const
{
    return m_data.at(i);
}

inline std::size_t Cell::size() const
{
    return m_data.size();
}

inline std::size_t Cell::size(std::size_t i) const
{
    return m_data[i].size();
}

inline std::size_t Cell::collspan() const
{
    return m_collspan;
}

inline EAlign Cell::align() const
{
    return m_align;
}

inline std::size_t Cell::width() const
{
    std::size_t ret = 0;
    for (std::size_t i = 0; i < size(); ++i)
    {
        ret = std::max(ret, width(i));
    }
    return ret;
}

inline std::size_t Cell::width(std::size_t i) const
{
    std::size_t ret = 0;
    for (std::size_t j = 0; j < size(i); ++j)
    {
        ret += m_data[i][j].string().length();
    }
    return ret;
}

inline std::string Cell::data(std::size_t i) const
{
    std::stringstream ss;
    for (const auto& data : m_data[i])
    {
        ss << data();
    }

    return ss.str();
}

template <typename T>
Data push_data(const T& data)
{
    return createData(data);
}

template <>
Data push_data<Data>(const Data& data)
{
    return data;
}

template <
    EAlign Align = EAlign::Left,
    int Collspan = 1,
    int Rowspan = 1,
    typename... T>
Cell createCell(const T&... data)
{
    return Cell(Align, Collspan, Rowspan, {push_data(data)...,});
}

template <typename T>
Cell push_row_data(const T& data)
{
    return createCell(data);
}

template <>
Cell push_row_data<Cell>(const Cell& cell)
{
    return cell;
}

template <typename... TTypes>
Row createRow(const TTypes&... data)
{
    return Row{push_row_data(data)...,};
}

template <typename T>
std::size_t push_table_data(Table& table, const T& data)
{
    table.push_back(createRow(data));
    return 0;
}

template <>
std::size_t push_table_data<Row>(Table& table, const Row& row)
{
    table.push_back(row);
    return 0;
}

template <>
std::size_t push_table_data<Table>(Table& table, const Table& data)
{
    for (const auto& it : data)
    {
        table.push_back(it);
    }
    return 0;
}

template <typename...TTypes>
Table createTable(const TTypes&... data)
{
    Table ret;
    std::size_t arr[] = {push_table_data(ret, data)...,};
    return ret;
}

inline std::vector<std::vector<int>> getCellsWidth(const Table& table)
{
    std::vector<std::vector<int>> ret(table.size());
    for (std::size_t i = 0; i < table.size(); ++i)
    {
        ret[i].resize(table[i].size(), 0);
    }
    std::vector<std::size_t> ptr(table.size(), 0);
    std::vector<int> cells(table.size());
    int completed = 0;
    for (int cell = 0; completed < table.size(); ++cell)
    {
        int mx = 0;
        for (std::size_t i = 0; i < table.size(); ++i)
        {
            if (ptr[i] == table[i].size())
            {
                continue;
            }
            if (cells[i] + table[i][ptr[i]].collspan() == cell)
            {
                int need_add = std::max<int>(0, table[i][ptr[i]].width() + 2 - ret[i][ptr[i]]);
                mx = std::max(mx, need_add);
            }
        }
        for (std::size_t i = 0; i < table.size(); ++i)
        {
            if (ptr[i] == table[i].size())
            {
                continue;
            }
            ret[i][ptr[i]] += mx;
            if (cells[i] + table[i][ptr[i]].collspan() == cell)
            {
                cells[i] = cell;
                ++ptr[i];
                if (ptr[i] == ret[i].size())
                {
                    ++completed;
                }
            }
        }
    }

    for (std::size_t i = 0; i < ret.size(); ++i)
    {
        for (std::size_t j = 0; j < ret[i].size(); ++j)
        {
            ret[i][j] += table[i][j].collspan() - 1;
        }
    }

    return ret;
}

inline std::string repeat_n_times(const std::string& s, std::size_t n)
{
    std::string ret;
    ret.reserve(s.length() * n);
    for (std::size_t i = 0; i < n; ++i)
    {
        ret += s;
    }
    return ret;
}

template <int offset = 1>
inline std::string getTableStr(
    const Table& table,
    termcolor::color_t border_color = termcolor::apply<termcolor::color<termcolor::Empty>>)
{
    std::stringstream str;
    str << border_color;
    std::vector<int> h(table.size());
    for (std::size_t i = 0; i < table.size(); ++i)
    {
        for (std::size_t j = 0; j < table[i].size(); ++j)
        {
            h[i] = std::max<int>(h[i], table[i][j].size());
        }
    }

    auto cellswidth = getCellsWidth(table);

    auto drawTop = [&str, &border_color](const std::vector<int>& w) {
        str << repeat_n_times(" ", offset);
        str << border_color << LUBORDER;
        for (std::size_t i = 0; i < w.size(); ++i)
        {
            str << repeat_n_times(HORBORDER, w[i]);
            if (i == w.size() - 1)
            {
                str << RUBORDER;
            }
            else
            {
                str << BORDERBOTTOM;
            }
        }
        str << termcolor::reset;
        str << std::endl;
    };

    auto drawMid = [&str, &border_color](const std::vector<int>& w, const std::vector<int>& nxt) {
        std::vector<int> pt{0};
        int sumw = 0, sumnxt = 0;
        for (int t : w)
        {
            sumw += t + 1;
            pt.push_back(sumw);
        }
        for (int t : nxt)
        {
            sumnxt += t + 1;
            pt.push_back(sumnxt);
        }
        std::sort(pt.begin(), pt.end());
        int cnt = std::unique(pt.begin(), pt.end()) - pt.begin();
        pt.resize(cnt);
        str << repeat_n_times(" ", offset);
        str << border_color << BORDERRIGHT;
        std::size_t ptrw = 0, ptrnxt = 0;
        sumw = 0, sumnxt = 0;
        for (std::size_t i = 1; i < pt.size(); ++i)
        {
            str << repeat_n_times(HORBORDER, pt[i] - pt[i - 1] - 1);
            if (i == pt.size() - 1)
            {
                str << BORDERLEFT;
            }
            else
            {
                if (sumw + w[ptrw] > pt[i])
                {
                    str << BORDERBOTTOM;
                    sumnxt += nxt[ptrnxt++];
                }
                else if (sumnxt + nxt[ptrnxt] > pt[i])
                {
                    str << BORDERUP;
                    sumw += w[ptrw++];
                }
                else
                {
                    sumw += w[ptrw++];
                    sumnxt += nxt[ptrnxt++];
                    str << PLUSBORDER;
                }
            }
        }
        str << termcolor::reset;
        str << std::endl;
    };

    auto drawBottom = [&str, &border_color](const std::vector<int>& w) {
        str << repeat_n_times(" ", offset);
        str << border_color << LBBORDER;
        for (std::size_t i = 0; i < w.size(); ++i)
        {
            str << repeat_n_times(HORBORDER, w[i]);
            if (i == w.size() - 1)
            {
                str << RBBORDER;
            }
            else
            {
                str << BORDERUP;
            }
        }
        str << termcolor::reset;
        str << std::endl;
    };

    auto drawCellPart = [&str](const Cell& cell, int needw, int idx) {
        std::stringstream to_append;
        to_append << " ";
        std::size_t len = 0;
        if (cell.size() > idx)
        {
            to_append << cell.data(idx);
            len = cell.width(idx);
        }
        int spaces = needw - len - 2;
        to_append << " ";

        if (cell.align() == EAlign::Left)
        {
            str << to_append.str() << std::string(spaces, SPACE);
        }
        else if (cell.align() == EAlign::Right)
        {
            str << std::string(spaces, SPACE) << to_append.str();
        }
        else
        {
            str << std::string(spaces / 2, SPACE) << to_append.str()
                << std::string(spaces - (spaces / 2), SPACE);
        }
        str << termcolor::reset;
    };

    drawTop(cellswidth.front());
    for (std::size_t i = 0; i < table.size(); ++i)
    {
        for (int idx = 0; idx < h[i]; ++idx)
        {
            str << repeat_n_times(" ", offset);
            str << border_color << VERBORDER << termcolor::reset;
            for (std::size_t j = 0; j < table[i].size(); ++j)
            {
                drawCellPart(table[i][j], cellswidth[i][j], idx);
                str << border_color << VERBORDER << termcolor::reset;
            }
            str << std::endl;
        }
        i == table.size() - 1 ? drawBottom(cellswidth.back())
                              : drawMid(cellswidth[i], cellswidth[i + 1]);
    }

    return str.str();
}

} // namespace AdvancedTerm
