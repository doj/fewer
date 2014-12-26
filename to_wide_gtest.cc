/* -*- mode: C++; c-basic-offset: 4; tab-width: 8; -*-
 * vi: set shiftwidth=4 tabstop=8:
 * :indentSize=4:tabSize=8:
 */
#include "gtest/gtest.h"
#include "to_wide.h"

class to_wide_fix : public ::testing::Test {
protected:
    virtual void SetUp()
    {
	setlocale(LC_ALL, "en_US.UTF-8");
    }
    virtual void TearDown()
    {
	setlocale(LC_ALL, "C");
    }
};

TEST_F(to_wide_fix, handles_empty_string)
{
    std::wstring expected = L"";
    ASSERT_EQ(expected, to_wide(""));
}

TEST_F(to_wide_fix, handles_ascii)
{
    std::wstring expected = L"abc";
    ASSERT_EQ(expected, to_wide("abc"));
}

TEST_F(to_wide_fix, handles_utf8)
{
    std::wstring euro = L"\u20AC";
    ASSERT_EQ(1u, euro.size());
    std::string eur = "\u20AC";
    ASSERT_EQ(3u, eur.size());
    ASSERT_EQ(std::string("\xE2\x82\xAC"), eur);
    ASSERT_EQ(euro, to_wide(eur));
}

TEST_F(to_wide_fix, resync_on_overlong_utf8)
{
    std::string invalid = "\u20AC" "\xF0\x82\x82\xAC" "\u00A2";
    std::wstring expected = L"\u20AC\uFFFD\uFFFD\uFFFD\uFFFD\u00A2";
    ASSERT_EQ(expected, to_wide(invalid));
}


TEST_F(to_wide_fix, resync_on_invalid_utf8)
{
    std::string invalid = "Dirk\u20ACJagdmann" "\xF4" "Writes\u00A2Fewer";
    std::wstring expected = L"Dirk\u20ACJagdmann\uFFFDWrites\u00A2Fewer";
    ASSERT_EQ(expected, to_wide(invalid));
}