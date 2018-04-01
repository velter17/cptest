#pragma once

#include <iomanip>
#include <sstream>
#include "filesystem/filesystem.hpp"
#include "test_archive/StoredTest.hpp"

namespace CPTest {
namespace TestArchive {

template <typename T>
struct TestToStore
{
    using type = T;
};

template <>
struct TestToStore<CTest>
{
    using type = CTempStoredTest;
};

template <typename TestType>
class CTestArchive
{
public:
    CTestArchive(const std::vector<CTest>& tests);
    CTestArchive(const Filesystem::PathType& path);

    const TestType& operator[](std::size_t idx) const;
    TestType& operator[](std::size_t idx);
    size_t size() const;

private:
    std::vector<typename TestToStore<TestType>::type> m_test_data;
};

template <typename TestType>
inline CTestArchive<TestType>::CTestArchive(const std::vector<CTest>& tests)
{
    for (const auto& test : tests)
    {
        m_test_data.emplace_back(test);
    }
}

template <typename TestType>
inline CTestArchive<TestType>::CTestArchive(const Filesystem::PathType& path)
{
    for (std::size_t test_number = 1; ; ++test_number)
    {
        auto test = CStoredTest(path, test_number);
        if (test.exists())
        {
            m_test_data.emplace_back(test);
        }
        else
        {
            break;
        }
    }
}

template <typename TestType>
inline const TestType& CTestArchive<TestType>::operator[](std::size_t idx) const
{
    return m_test_data.at(idx);
}

template <typename TestType>
inline TestType& CTestArchive<TestType>::operator[](std::size_t idx)
{
    return m_test_data.at(idx);
}

template <typename TestType>
inline std::size_t CTestArchive<TestType>::size() const
{
    return m_test_data.size();
}

} // namespace TestArchive
} // namespace CPTest
