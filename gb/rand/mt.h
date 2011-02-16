#pragma once
/*! \file mt.h
	Обёртка вокруг генератора случайных чисел Mersenne Twister
	На выбор предлагаются алгоритмы SSE/SIMD и обычный, для SIMD предлагаются одинарная и двойная точность генерации
	
	При включении GB_RANDOM_OPTIMIZE_FOR_DOUBLE=1 дополнительные функции появляются в неймспейсе
	gb::mersennetwister с именами dsfmt_*, для целых случайных чисел такой генератор работает
	медленнее, чем целочисленный GB_RANDOM_OPTIMIZE_FOR_DOUBLE=0

	\author Дмитрий Литовченко kvakvs@yandex.ru
	\authors Mutsuo Saito, Makoto Matsumoto  (Hiroshima University) авторы алгоритма MT
	http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/index.html
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


/*! Получить случайное число от [0..1) для float, double,
 *	и от 0 до (MAXVALUE=0xFFFF...FFFF) для выбранного типа данных для uint32_t, uint64_t
 *	Допустимый параметр шаблона: value_type = [float, double, uint32_t, uint64_t]
 **/
template <typename value_type>
value_type get();


#if GB_RANDOM_OPTIMIZE_FOR_DOUBLE

//! Получить случайный float 0..1, оптимизированная версия для double
template <> float get()
{
	// случайное число от 0 включительно до 1 не включительно
	return (float)gb::mersennetwister::genrand_open_close();
}

//! Получить случайный double 0..1, оптимизированная самая быстрая версия
template <> double get()
{
	// случайное число от 0 включительно до 1 не включительно
	return gb::mersennetwister::genrand_open_close();
}

//! Получить случайный uint32_t 0..0xFFFFFFFF, медленная версия сделана через get<double>
template <> uint32_t get()
{
	//return gb::mersennetwister::dsfmt_gv_genrand_uint32();
	return (uint32_t)(gb::mersennetwister::genrand_open_close() * GB_CONST_UINT32MAX);
}

//! Получить случайный uint64_t 0..0xFFFFFFFFFFFFFFFF, медленная версия сделана через get<double>
template <> uint64_t get()
{
	return (uint64_t)(gb::mersennetwister::genrand_open_close() * GB_CONST_UINT64MAX);
}

#else // ! GB_RANDOM_OPTIMIZE_FOR_DOUBLE

//! Получить случайный uint32_t 0..0xFFFFFFFF, оптимизированная версия сделана через
//! половинку get<uint64_t> (алгоритм плохо относится к выборке 32 бит вперемешку с 64 битными
//! значениями, потому приводим все выборки к 64 битным).
template <> uint32_t get()
{
	return (uint32_t)gb::mersennetwister::gen_rand64();
}

//! Получить случайный uint64_t 0..0xFFFFFFFFFFFFFFFF, оптимизированная самая быстрая версия
template <> uint64_t get()
{
	return gb::mersennetwister::gen_rand64();
}

//! Получить случайный float 0..1
template <> float get()
{
	return get <uint32_t>() * (float)GB_CONST_UINT32MAX_INV);
}

//! Получить случайный double 0..1
template <> double get()
{
	return get <uint64_t>() * GB_CONST_UINT64MAX_INV);
}
#endif


/*! \brief Получить равномерно распределённое случайное число в диапазоне [a, b) или [a, b]
 *	\brief в зависимости от округления
 *	http://en.wikipedia.org/wiki/Uniform_distribution_%28continuous%29
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
 */
template <typename value_type>
value_type getUniformVariate( value_type a, value_type b )
{
	return a + (b-a) * get <value_type> ();
}


/*! \brief Непрерывное распределение, ограниченное верхним и нижним лимитами, с заданной фиксированной
 *	\brief точкой между ними (в форме треугольника).
 *	http://en.wikipedia.org/wiki/Triangular_distribution
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
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


/*! \brief Получить число согласно нормальному распределению случайных чисел
 *	http://en.wikipedia.org/wiki/Normal_distribution
 *	http://ru.wikipedia.org/wiki/Нормальное_распределение
 *	\param mu - середина (математическое ожидание)
 *	\param sigma - стандартное отклонение (дисперсия).
 *
 *	Использует метод Kinderman и Monahan. Reference: Kinderman, A.J. and Monahan, J.F.,
 *	"Computer generation of random variables using the ratio of uniform deviates",
 *	ACM Trans Math Software, 3, (1977), pp257-260.
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
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


/*! Логнормальное распределение
 *	http://en.wikipedia.org/wiki/Log-normal_distribution
 *	http://ru.wikipedia.org/wiki/Логнормальное_распределение
 *	Если взять натуральный логарифм от этого распределения, то Вы получите нормальное
 *	распределение, со средним значением mu и стандартным отклонением sigma.
 *	\param mu - среднее значение (мат.ожидание), может принимать любое значение
 *	\param sigma - дисперсия (отклонение), больше нуля
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
*/
template <typename value_type>
value_type getLogNormalVariate( value_type mu, value_type sigma )
{
	return std::exp <value_type>( getNormalVariate( mu, sigma ) );
}


/*! Exponential distribution.
 *	http://en.wikipedia.org/wiki/Exponential_distribution
 *	http://ru.wikipedia.org/wiki/Экспоненциальное_распределение
 *	\param Lambda - 1.0 делённое на желаемую середину распределения (мат.ожидание), должно быть ненулевым
 *	\return значения от 0 до плюс бесконечности при положительном Lambda и от минус бесконечности до 0 иначе
 */
template <typename value_type>
value_type getExponentialVariate( value_type Lambda )
{
    value_type u = get <value_type> ();
    while ( u <= (value_type)1e-7 ) {
		//std::cout << u << std::endl;
        u = get <value_type> ();
	}
    return -std::log( u ) / Lambda;
}


/*! Остаток от деления X на Y
 *	\param x - делимое
 *	\param y - делитель
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
 */
template <typename value_type>
value_type modulo ( value_type x,  value_type y )
{
	return x - std::floor( (value_type)(x / y) ) * y;
}


/*! Круговое нормальное распределение (von Mises) - непрерывное распределение на круге.
 *	Может представляться как приближение к замкнутому на круге нормальному распределению.
 *	http://en.wikipedia.org/wiki/Von_Mises_distribution
 *	\param mu - угол пика распределения (мат. ожидание), выраженный в радианах между 0 и 2*pi
 *	\param kappa - параметр концентрации, должен быть больше или равен нулю
 *	Если kappa равен нулю, распределение становится равномерным случайным на круге.
 *
 *	Основано на алгоритме, опубликованном в: Fisher, N.I., "Statistical Analysis of
 *	Circular Data", Cambridge University Press, 1993.
 *
 *	Допустимый параметр шаблона: value_type = [float, double]
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


/*!	Га́мма распределе́ние — двухпараметрическое семейство абсолютно непрерывных распределений.
 *	Если параметр alpha принимает целое значение, то такое гамма-распределение также называется
 *	распределе́нием Эрла́нга.
 *	http://en.wikipedia.org/wiki/Gamma_distribution
 *	http://ru.wikipedia.org/wiki/Гамма-распределение
 *	Мат.ожидание (пик распределения) - alpha*beta, дисперсия (разброс) - alpha*beta*beta
 *	\param alpha > 0
 *	\param beta > 0
 *
 *	Осторожно: ряд устаревших источников определяют гамма-распределение, как основанное на alpha > -1.0
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


/*! Распределение Гаусса (оно же Нормальное распределение)
 *	Это несколько более быстрая версия определённой выше функции getNormalVariate
 *	http://hyperphysics.phy-astr.gsu.edu/hbase/math/gaufcn.html
 *	http://en.wikipedia.org/wiki/Normal_distribution
 *	\param mu - мат.ожидание
 *	\param sigma - стандартное отклонение (дисперсия)
 *	
 *	Примечание по потокобезопасности: Когда два потока вызывают одновременно эту функцию,
 *	из-за наличия static переменной в функции есть шанс, что оба получат одинаковое возвращаемое 
 *	значение. Однако, окно для возникновения такого бага достаточно маленькое. Чтобы 
 *	избежать проблемы, используйте блокировку между вызовами этой функции.
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


/*! Бета-распределение
 *	http://en.wikipedia.org/wiki/Beta_distribution
 *	http://ru.wikipedia.org/wiki/Бета-распределение
 *	Требования к параметрам - alpha > 0 и beta > 0.
 *	\return Возвращает значения между 0 и 1.
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


/*!	Парето-распределение
 *	\param alpha - форма фигуры, см. страницу с русским или английским пояснением для иллюстраций
 *	http://en.wikipedia.org/wiki/Pareto_distribution
 *	http://ru.wikipedia.org/wiki/Распределение_Парето
 */
template <typename value_type>
value_type getParetoVariate( value_type alpha )
{
    value_type u = (value_type)1.0 - get <value_type> ();
    return (value_type)1.0 / std::pow( u, (value_type)1.0 / alpha );
}


/*! Распределение Вейбулла
 *	http://en.wikipedia.org/wiki/Weibull_distribution
 *	http://ru.wikipedia.org/wiki/Распределение_Вейбулла
 *	\param alpha - масштаб
 *	\param beta - форма фигуры (см. страницу с английским пояснением для иллюстраций)
 */
template <typename value_type>
value_type getWeibullVariate( value_type alpha, value_type beta )
{
    value_type u = (value_type)1.0 - get <value_type> ();
    return alpha * std::pow( -std::log( u ), (value_type)1.0 / beta );
}


	} // namespace rand
} // namespace gb
