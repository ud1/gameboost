#pragma once

// синглтон не нужен
namespace ??
{ 

	template <typename t_class>
	class Singleton
	{
	public:
		static t_class& instance()
		{
			static t_class _instance;
			return _instance;
		}

	protected: 
		Singleton() { };
		Singleton(const Singleton&) { };
		Singleton& operator = (const Singleton&) { };
	};

#define ??_SINGLETON_CONSTRUCTORS(t) private:         \
	t() { }         \
	t(const t&) { } \
	t& operator = (const t&) { return *this; } \
	friend class Singleton<t>;

#define ??_SINGLETON_COPY_DENY(t) private:         \
	t(const t&) { } \
	t& operator = (const t&) { return *this; } \
	friend class Singleton<t>;

}