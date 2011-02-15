#pragma once
/*! \file mt.h
	Обёртка вокруг генератора случайных чисел Mersenne Twister
	На выбор предлагаются алгоритмы SSE/SIMD и обычный, для SIMD предлагаются одинарная и двойная точность генерации
	
	При включении double оптимизации дополнительные функции появляются в неймспейсе
	gb::mersennetwister с именами dsfmt_*, для целых случайных чисел такой генератор работает
	медленнее, чем целочисленный GB_RANDOM_OPTIMIZE_FOR_DOUBLE=0
*/

#include <gb/Config.h>
#include <gb/base/Types.h>
#include <gb/base/Constants.h>

#include <cmath>
#include <math.h>

#if GB_RANDOM_OPTIMIZE_FOR_DOUBLE
	#include <gb/deplib/mt/dSFMT/dSFMT.h>
#else
	#include <gb/deplib/mt/SFMT/SFMT.h>
#endif

namespace gb
{
	namespace rand
	{


//! Стартовать рандом генератор с помощью числа
inline void seed( uint32_t seed_value )
{
#if GB_RANDOM_OPTIMIZE_FOR_DOUBLE
	gb::mersennetwister::dsfmt_gv_init_gen_rand( seed_value );
#else
	gb::mersennetwister::init_gen_rand( seed_value );
#endif
}


//! Стартовать рандом генератор с помощью массива случайных данных
inline void seedArray( uint32_t *init_key, int key_length )
{
#if GB_RANDOM_OPTIMIZE_FOR_DOUBLE
	gb::mersennetwister::dsfmt_gv_init_by_array( init_key, key_length );
#else
	gb::mersennetwister::init_by_array( init_key, key_length );
#endif
}


template <typename value_type>
value_type get();


#if GB_RANDOM_OPTIMIZE_FOR_DOUBLE
template <> float get()
{
	// случайное число от 0 включительно до 1 не включительно
	return (float)gb::mersennetwister::genrand_open_close();
}
template <> double get()
{
	// случайное число от 0 включительно до 1 не включительно
	return gb::mersennetwister::genrand_open_close();
}
template <> uint32_t get()
{
	//return gb::mersennetwister::dsfmt_gv_genrand_uint32();
	return (uint32_t)(gb::mersennetwister::genrand_open_close() * GB_CONST_UINT32MAX);
}
template <> uint64_t get()
{
	return (uint64_t)(gb::mersennetwister::genrand_open_close() * GB_CONST_UINT64MAX);
}

#else // ! GB_RANDOM_OPTIMIZE_FOR_DOUBLE

template <> uint32_t get()
{
	return (uint32_t)gb::mersennetwister::gen_rand64();
}
template <> uint64_t get()
{
	return gb::mersennetwister::gen_rand64();
}
template <> float get()
{
	return get <uint32_t>() * (float)GB_CONST_UINT32MAX_INV);
}
template <> double get()
{
	return get <uint64_t>() * GB_CONST_UINT64MAX_INV);
}
#endif


//! Get a random number in the range [a, b) or [a, b] depending on rounding
//! http://en.wikipedia.org/wiki/Uniform_distribution_%28continuous%29
template <typename value_type>
value_type getUniformVariate( value_type a, value_type b )
{
	return a + (b-a) * get <value_type> ();
}


/*! Continuous distribution bounded by given lower and upper limits,
 *	and having a given mode value in-between.
 *	http://en.wikipedia.org/wiki/Triangular_distribution
 */
template <typename value_type>
value_type getTriangularVariate( value_type a=0.0, value_type b=1.0, value_type mode=0.5 )
{
    value_type u = get <value_type>();
	value_type c = (mode - a) / (b - a); // 0.5 if mode is None else (mode - low) / (high - low)
    if ( u > c ) {
        u = (value_type)1.0 - u;
        c = (value_type)1.0 - c;
        std::swap( a, b );
	}
    return a + (b - a) * std::sqrt (u * c);
}


/*! Normal distribution.
 *	http://en.wikipedia.org/wiki/Normal_distribution
 *	mu is the mean, and sigma is the standard deviation.
 *
 *	mu = mean, sigma = standard deviation
 *
 *	Uses Kinderman and Monahan method. Reference: Kinderman,
 *	A.J. and Monahan, J.F., "Computer generation of random
 *	variables using the ratio of uniform deviates", ACM Trans
 *	Math Software, 3, (1977), pp257-260.
 */
template <typename value_type>
value_type getNormalVariate( value_type mu, value_type sigma)
{
	static value_type NV_MAGICCONST = 4 * std::exp ( (value_type)-0.5 ) / (value_type)GB_CONST_SQRT_2;
	value_type z;
    while (1)
	{
        value_type u1 = get <value_type> ();
        value_type u2 = (value_type)1.0 - get <value_type> ();
        z = NV_MAGICCONST * (u1 - (value_type)0.5) / u2;
        value_type zz = z * z * (value_type)0.25;
        if ( zz <= - std::log ( (value_type)u2 ) ) break;
	}
    return mu + z * sigma;
}


/*! Log normal distribution.
 *	http://en.wikipedia.org/wiki/Log-normal_distribution
 *	If you take the natural logarithm of this distribution, you'll get a
 *	normal distribution with mean mu and standard deviation sigma.
 *	mu can have any value, and sigma must be greater than zero.
*/
template <typename value_type>
value_type getLogNormalVariate( value_type mu, value_type sigma )
{
	return std::exp <value_type>( getNormalVariate( mu, sigma ) );
}


/*! Exponential distribution.
 *	http://en.wikipedia.org/wiki/Exponential_distribution
 *	lambd is 1.0 divided by the desired mean.  It should be
 *	nonzero. Returned values range from 0 to positive infinity if lambd is positive, 
 *	and from negative infinity to 0 if lambd is negative.
 *
 *	lambd: rate lambd = 1/mean
 */
template <typename value_type>
value_type getExponentialVariate( value_type lambd )
{
    value_type u = get <value_type> ();
    while ( u <= (value_type)1e-7 ) {
		//std::cout << u << std::endl;
        u = get <value_type> ();
	}
    return -std::log( u ) / lambd;
}


//! Остаток от деления X на Y
template <typename value_type>
value_type modulo ( value_type x,  value_type y )
{
	return x - std::floor( (value_type)(x / y) ) * y;
}


/*! Circular data distribution.
 *	http://en.wikipedia.org/wiki/Von_Mises_distribution
 *	mu is the mean angle, expressed in radians between 0 and 2*pi, and
 *	kappa is the concentration parameter, which must be greater than or
 *	equal to zero.  If kappa is equal to zero, this distribution reduces
 *	to a uniform random angle over the range 0 to 2*pi.
 *
 *	\param mu - mean angle (in radians between 0 and 2*pi)
 *	\param kappa - concentration parameter kappa (>= 0)
 *	if kappa = 0 generate uniform random angle
 *
 *	Based upon an algorithm published in: Fisher, N.I.,
 *	"Statistical Analysis of Circular Data", Cambridge
 *	University Press, 1993.
 *
 *	Thanks to Magnus Kessler for a correction to the
 *	implementation of step 4.
 */
template <typename value_type>
value_type getVonMisesVariate( value_type mu, value_type kappa )
{
    if ( kappa <= (value_type)1e-6 ) return (value_type)GB_CONST_DOUBLE_PI * get <value_type>();

    value_type a = (value_type)1.0 + std::sqrt ((value_type)1.0 + (value_type)4.0 * kappa * kappa);
    value_type b = (a - std::sqrt( (value_type)2.0 * a )) / ((value_type)2.0 * kappa);
    value_type r = ((value_type)1.0 + b * b) / ((value_type)2.0 * b);

	value_type f;
    while (1)
	{
        value_type u1 = get <value_type> ();

        value_type z = std::cos( (value_type)(GB_CONST_PI * u1) );
        f = ((value_type)1.0 + r * z)/(r + z);
        value_type c = kappa * (r - f);

        value_type u2 = get <value_type> ();

        if ( u2 < c * (2.0 - c) || u2 <= c * std::exp( (value_type)(1.0 - c) ) )
		{
            break;
		}
	}

    value_type u3 = get <value_type> ();
	value_type theta;
    if ( u3 > (value_type)0.5 ) {
        theta = modulo <value_type> (mu, (value_type)GB_CONST_DOUBLE_PI) + std::acos( (value_type)f );
	}
	else {
        theta = modulo <value_type> (mu, (value_type)GB_CONST_DOUBLE_PI) - std::acos( (value_type)f );
	}

    return theta;
}


/*!	Gamma distribution.  Not the gamma function!
 *	Conditions on the parameters are alpha > 0 and beta > 0.
 *
 *	alpha > 0, beta > 0, mean is alpha*beta, variance is alpha*beta**2
 *
 *	Warning: a few older sources define the gamma distribution in terms
 *	of alpha > -1.0
 */
template <typename value_type>
value_type getGammaVariate( value_type alpha, value_type beta )
{
    if ( alpha <= 0.0 || beta <= 0.0 ) {
        throw std::exception( "getGammaVariate: alpha and beta must be > 0.0" );
	}

	static double LOG4 = std::log (4.0);
	static double SG_MAGICCONST = 1.0 + std::log (4.5);

    if ( alpha > 1.0 )
	{
        // Uses R.C.H. Cheng, "The generation of Gamma variables with non-integral shape parameters",
        // Applied Statistics, (1977), 26, No. 1, p71-74
        value_type ainv = std::sqrt ( (value_type)(2.0 * alpha - 1.0) );
        value_type bbb = alpha - (value_type)LOG4;
        value_type ccc = alpha + ainv;

        while (1) 
		{
            value_type u1 = get <value_type> ();
            if (!( 1e-7 < u1 && u1 < 0.9999999 )) {
                continue;
			}
            value_type u2 = (value_type)1.0 - get <value_type> ();
            value_type v = std::log( (value_type)(u1/(1.0-u1)) ) / ainv;
            value_type x = alpha * std::exp (v);
            value_type z = u1*u1*u2;
            value_type r = bbb+ccc*v-x;
            if ( r + SG_MAGICCONST - 4.5*z >= 0.0 || r >= std::log (z))
			{
                return x * beta;
			}
		}
	}

    else if ( alpha == 1.0 )
	{
        // expovariate(1)
        value_type u = get <value_type> ();
        while (u <= 1e-7) {
            u = get <value_type> ();
		}
        return -std::log (u) * beta;
	}
	else {
		// alpha is between 0 and 1 (exclusive)
		// Uses ALGORITHM GS of Statistical Computing - Kennedy & Gentle
		value_type x;
        while (1) 
		{
            value_type u = get <value_type> ();
            value_type b = ((value_type)GB_CONST_E + alpha) / (value_type)GB_CONST_E;
            value_type p = b*u;
            if (p <= 1.0) {
                x = std::pow ( (value_type)p, (value_type)(1.0/alpha));
			}
			else {
                x = -std::log ((b-p)/alpha);
			}
            value_type u1 = get <value_type> ();
            if (p > 1.0) {
                if ( u1 <= std::pow( (value_type)x, (value_type)(alpha - 1.0) ) )
				{
                    break;
				}
			}
            else if (u1 <= std::exp (-x)) {
                break;
			}
		}
        return x * beta;
	}
}


/*! Gaussian (Normal) distribution
 *	Более быстрая версия getNormalVariate
 *
 *	mu is the mean, and sigma is the standard deviation.  This is
 *	slightly faster than the normalvariate() function.
 *
 *	Not thread-safe without a lock around calls.
 *	
 *	When x and y are two variables from [0, 1), uniformly distributed, then
 *		cos(2*pi*x)*sqrt(-2*log(1-y))
 *		sin(2*pi*x)*sqrt(-2*log(1-y))
 *	
 *	are two *independent* variables with normal distribution
 *	(mu = 0, sigma = 1).
 *	(Lambert Meertens)
 *	(corrected version; bug discovered by Mike Miller, fixed by LM)
 *	
 *	Multithreading note: When two threads call this function simultaneously, it is
 *	possible that they will receive the same return value.  The window is very small
 *	though. To avoid this, you have to use a lock around all calls.  (I didn't want
 *	to slow this down in the serial case by using a lock here.)
 *	http://en.wikipedia.org/wiki/Normal_distribution
 */
template <typename value_type>
value_type getGaussianVariate( value_type mu, value_type sigma )
{
	static double gauss_next;

    double z = gauss_next;
    gauss_next = gb::getNaN();

    if (z != z) // test for NaN
	{
        value_type x2pi = get <value_type> () * (value_type)GB_CONST_DOUBLE_PI;
        value_type g2rad = std::sqrt( (value_type)-2.0 * std::log( (value_type)1.0 - get <value_type> ()) );
        z = std::cos( x2pi ) * g2rad;
        gauss_next = std::sin( x2pi ) * g2rad;
	}

    return mu + (value_type)z * sigma;
}


/*! Beta distribution.
 *	http://en.wikipedia.org/wiki/Beta_distribution
 *	Conditions on the parameters are alpha > 0 and beta > 0.
 *	Returned values range between 0 and 1.
 *
 *	This version due to Janne Sinkkonen, and matches all the std
 *	texts (e.g., Knuth Vol 2 Ed 3 pg 134 "the beta distribution").
 */
template <typename value_type>
value_type getBetaVariate( value_type alpha, value_type beta )
{
    y = getGammaVariate <value_type>( alpha, (value_type)1.0 );
    if (y == 0) {
        return (value_type)0.0;
	}
    else {
        return y / (y + getGammaVariate <value_type> ( beta, (value_type)1.0 ));
	}
}


//! Pareto distribution.  alpha is the shape parameter
template <typename value_type>
value_type getParetoVariate( value_type alpha )
{
    value_type u = (value_type)1.0 - get <value_type> ();
    return (value_type)1.0 / std::pow( u, (value_type)1.0 / alpha );
}


/*! Weibull distribution.
 *	alpha is the scale parameter and beta is the shape parameter.
 */
template <typename value_type>
value_type getWeibullVariate( value_type alpha, value_type beta )
{
    value_type u = (value_type)1.0 - get <value_type> ();
    return alpha * std::pow( -std::log( u ), (value_type)1.0 / beta );
}


	} // namespace rand
} // namespace gb
