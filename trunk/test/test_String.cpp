/*!	\file test_Path.h
 *  Тесты для модуля base/String
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include "test_pch.h"

#include <gtest/gtest.h>

#include <base/String.h>

// The fixture for testing class Foo.
class gb_base_String_test : public ::testing::Test
{
protected:
	gb_base_String_test() { }
    virtual ~gb_base_String_test() { }
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F (gb_base_String_test, test_caseConvert)
{
	std::string t1 = "ABCD";
	gb::str::toLower( t1 );
	ASSERT_EQ( t1, "abcd" );
	ASSERT_EQ( gb::str::toLowerCopy("ABCD"), "abcd" );
	// русские буквы АБВ в UTF8
	ASSERT_EQ( gb::str::toLowerCopy("\xd0\x90\xd0\x91\xd0\x92"), "\xd0\xb0\xd0\xb1\xd0\xb2" );

	std::string t2 = "abcd";
	gb::str::toUpper( t2 );
	ASSERT_EQ( t2, "ABCD" );
	ASSERT_EQ( gb::str::toUpperCopy("abcd"), "ABCD" );
	ASSERT_EQ( gb::str::toUpperCopy(""), "" );
	// русские буквы АБВ в UTF8
	ASSERT_EQ( gb::str::toUpperCopy("\xd0\xb0\xd0\xb1\xd0\xb2"), "\xd0\x90\xd0\x91\xd0\x92" );
}
