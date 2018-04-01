#pragma once

#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace CPTest {
namespace Settings {

class CSettingsFile
{
public:
    CSettingsFile(const boost::filesystem::path& p);
    ~CSettingsFile();

    template <typename T>
    T get(const std::string& key);

    template <typename T>
    void set(const std::string& key, const T& value);

private:
    const boost::filesystem::path m_path;
    boost::property_tree::ptree m_tree;
};

inline CSettingsFile::CSettingsFile(const boost::filesystem::path& p)
    : m_path(p)
{
    boost::property_tree::read_ini(p.string(), m_tree);
}

inline CSettingsFile::~CSettingsFile()
{
    boost::property_tree::write_ini(m_path.string(), m_tree);
}

template <typename T>
inline T CSettingsFile::get(const std::string& key)
{
    return m_tree.get<T>(key);
}

template <typename T>
inline void CSettingsFile::set(const std::string& key, const T& value)
{
    m_tree.put(key, value);
}

} // namespace Settings
} // namespace CPTest
