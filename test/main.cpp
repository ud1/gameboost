#include "test_pch.h"

#include <gtest/gtest.h>

// studio 2010
// #if _MSC_VER >= 0x0A00
// 	#pragma comment( lib, "libboost_system-vc100-mt-gd.lib" )
// 	#pragma comment( lib, "libboost_filesystem-vc100-mt-gd.lib" )
// #endif

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest( & argc, argv );
    return RUN_ALL_TESTS();
}
