#pragma once

/*!
 * \file String.h
 * Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
 * алгоритмов без подключения библиотеки Boost
 */

#if ! GB_NO_BOOST_LIBRARY
#include <boost/algorithm/string.hpp>
#endif


namespace gb
{
	namespace str {

// Boost запрещён, пишем велосипеды здесь
#if GB_NO_BOOST_LIBRARY

		//! Привести к верхнему регистру на месте
		void toUpper( std::string & v );

		//! Вернуть копию, приведённую к верхнему регистру
		std::string toUpperCopy( const std::string & v );

		//! Привести к нижнему регистру на месте
		void toLower( std::string & v );

		//! Вернуть копию, приведённую к нижнему регистру
		std::string toLowerCopy( const std::string & v );

		//! Обрезать пробелы и табуляции слева, на месте
		void trimLeft( std::string & v );

		//! Обрезать пробелы и табуляции слева, вернуть исправленную копию
		std::string trimLeftCopy( const std::string & v );

		//! Обрезать пробелы и табуляции справа, на месте
		void trimRight( std::string & v );

		//! Обрезать пробелы и табуляции справа, вернуть исправленную копию
		std::string trimRightCopy( const std::string & v );

		//! Обрезать пробелы и табуляции слева и справа, на месте
		void trim( std::string & v );

		//! Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
		std::string trimCopy( const std::string & v );

		//-------------------------------------------------------------------------
		// Предикаты для использования в функциях поиска, или в обычных условиях
		//-------------------------------------------------------------------------

		//! Начинается ли строка text с фрагмента search?
		bool startsWith( const std::string & text, const std::string & search );
		//! Начинается ли строка text с фрагмента search? (без учёта регистра)
		bool iStartsWith( const std::string & text, const std::string & search );

		//! Завершается ли строка text фрагментом search?
		bool endsWith( const std::string & text, const std::string & search );
		//! Завершается ли строка text фрагментом search? (без учёта регистра)
		bool iEndsWith( const std::string & text, const std::string & search );

		//! Содержит ли строка text фрагмент search?
		bool contains( const std::string & text, const std::string & search );
		//! Содержит ли строка text фрагмент search? (без учёта регистра)
		bool iContains( const std::string & text, const std::string & search );

		//! Равны ли строки друг другу
		//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
		inline bool equals( const std::string & a, const std::string & b ) {
			return a == b;
		}
		//! Равны ли строки друг другу без учёта регистра?
		//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
		bool iEquals( const std::string & a, const std::string & b );

#else

		//! Привести к верхнему регистру на месте
		inline void toUpper( std::string & v ) {
			boost::algorithm::to_upper( v );
		}

		//! Вернуть копию, приведённую к верхнему регистру
		inline std::string toUpperCopy( const std::string & v ) {
			return boost::algorithm::to_upper_copy( v );
		}

		//! Привести к нижнему регистру на месте
		inline void toLower( std::string & v ) {
			boost::algorithm::to_lower( v );
		}

		//! Вернуть копию, приведённую к нижнему регистру
		inline std::string toLowerCopy( const std::string & v ) {
			return boost::algorithm::to_lower_copy( v );
		}

		//! Обрезать пробелы и табуляции слева, на месте
		inline void trimLeft( std::string & v ) {
			boost::algorithm::trim_left( v );
		}

		//! Обрезать пробелы и табуляции слева, вернуть исправленную копию
		inline std::string trimLeftCopy( const std::string & v ) {
			return boost::algorithm::trim_left_copy( v );
		}

		//! Обрезать пробелы и табуляции справа, на месте
		inline void trimRight( std::string & v ) {
			boost::algorithm::trim_right( v );
		}

		//! Обрезать пробелы и табуляции справа, вернуть исправленную копию
		inline std::string trimRightCopy( const std::string & v ) {
			return boost::algorithm::trim_right_copy( v );
		}

		//! Обрезать пробелы и табуляции слева и справа, на месте
		inline void trim( std::string & v ) {
			boost::algorithm::trim( v );
		}

		//! Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
		inline std::string trimCopy( const std::string & v ) {
			return boost::algorithm::trim_copy( v );
		}

		//-------------------------------------------------------------------------
		// Предикаты для использования в функциях поиска, или в обычных условиях
		//-------------------------------------------------------------------------

		//! Начинается ли строка text с фрагмента search?
		inline bool startsWith( const std::string & text, const std::string & search ) {
			return boost::algorithm::starts_with( text, search );
		}
		//! Начинается ли строка text с фрагмента search? (без учёта регистра)
		inline bool iStartsWith( const std::string & text, const std::string & search ) {
			return boost::algorithm::istarts_with( text, search );
		}

		//! Завершается ли строка text фрагментом search?
		inline bool endsWith( const std::string & text, const std::string & search ) {
			return boost::algorithm::ends_with( text, search );
		}
		//! Завершается ли строка text фрагментом search? (без учёта регистра)
		inline bool iEndsWith( const std::string & text, const std::string & search ) {
			return boost::algorithm::iends_with( text, search );
		}

		//! Содержит ли строка text фрагмент search?
		inline bool contains( const std::string & text, const std::string & search ) {
			return boost::algorithm::contains( text, search );
		}
		//! Содержит ли строка text фрагмент search? (без учёта регистра)
		inline bool iContains( const std::string & text, const std::string & search ) {
			return boost::algorithm::icontains( text, search );
		}

		//! Равны ли строки друг другу
		//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
		inline bool equals( const std::string & a, const std::string & b ) {
			return a == b;
		}
		//! Равны ли строки друг другу без учёта регистра?
		//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
		inline bool iEquals( const std::string & a, const std::string & b ) {
			return boost::algorithm::iequals( a, b );
		}

#endif // GB_NO_BOOST_LIBRARY

	} // namespace str
} // namespace gb
