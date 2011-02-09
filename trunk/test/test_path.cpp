/*!	\file test_Path.h
 *  Тесты для модуля system/Path
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include "test_pch.h"

#include <gtest/gtest.h>
#include <boost/system/error_code.hpp>

#include <system/path.h>

// The fixture for testing class Foo.
class gb_system_Path_test : public ::testing::Test
{
protected:
    gb_system_Path_test() { }
    virtual ~gb_system_Path_test() { }
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F (gb_system_Path_test, test_getExtension)
{
	gb::system::Path	p( "/home/test/file.txt" );
	ASSERT_EQ( p.getExtension(), ".txt" );
	ASSERT_EQ( p.getLeaf(), "file.txt" );

	gb::system::Path	pp = p.getParent();
	ASSERT_EQ( pp.getLeaf(), "test" );

	p.changeExtension( ".zip" );
	ASSERT_EQ( p.getExtension(), ".zip" );
}
