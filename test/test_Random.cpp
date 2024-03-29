/*!	\file test_Path.h
 *  Тесты для модуля base/String
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include "pch_test.h"

#include <gtest/gtest.h>

#include <gb/rand/mt.h>

// The fixture for testing class Foo.
class gb_rand_mt_test : public ::testing::Test
{
protected:
	gb_rand_mt_test() { }
    virtual ~gb_rand_mt_test() { }
    virtual void SetUp() { }
    virtual void TearDown() { }
};

TEST_F( gb_rand_mt_test, test_simple )
{
	gb::rand::seed( (uint32_t) std::time( NULL ) );

	for (int i = 0; i < 10; i++) {
		uint32_t ui32 = gb::rand::get <uint32_t>();
		uint64_t ui64 = gb::rand::get <uint64_t>();
		std::cout << "UI64=" << ui64 << " UI32=" << ui32 << std::endl;
	}

	float f;
	double d;

	for (int i = 0; i < 10; i++) {
		f = gb::rand::get <float> ();
		d = gb::rand::get <double> ();
		std::cout << "FLOAT=" << f << " DOUBLE=" << d << std::endl;
	}
	exit(0);

	f = gb::rand::getTriangularVariate <float> ();
	d = gb::rand::getTriangularVariate <double> ();

	f = gb::rand::getExponentialVariate <float> (1.1f);
	d = gb::rand::getExponentialVariate <double> (1.1);

	f = gb::rand::getGammaVariate <float> (1.1f, 2.2f);
	d = gb::rand::getGammaVariate <double> (1.1, 2.2);

	f = gb::rand::getNormalVariate <float> ( 10, 20 );
	d = gb::rand::getNormalVariate <double> ( 10, 20 );

	f = gb::rand::getVonMisesVariate <float> ( 10, 20 );
	d = gb::rand::getVonMisesVariate <double> ( 10, 20 );

	f = gb::rand::getGaussianVariate <float> ( 10, 20 );
	d = gb::rand::getGaussianVariate <double> ( 10, 20 );

	f = gb::rand::getParetoVariate <float> ( 10 );
	d = gb::rand::getParetoVariate <double> ( 10 );

	f = gb::rand::getWeibullVariate <float> ( 10, 20 );
	d = gb::rand::getWeibullVariate <double> ( 10, 20 );
}
