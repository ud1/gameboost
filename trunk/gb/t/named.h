

#pragma once

namespace gb
{

	namespace t
	{


		template <class T>
		class named	 {
		public:

			named(const std::string& _name_) : _name(_name_) { _value = T(); }
			named(const std::string& _name_, const T& _value_): _name(_name_), _value(_value_) {}
			named(const named<T>& a) : _name(a._name), _value(a._value) {}

		   ~named() {}

			const std::string& name() const { return _name; }

			void operator = (const T& val) { _value = val; }
			operator T() const { return _value; }

			      T& reference ()        { return _value; }
			const T& reference () const  { return _value; }

				  T* pointer ()        { return &_value; }
			const T* pointer () const  { return &_value; }

			std::string to_name_value() const 
			{
				std::string res;

			}

			void from_name_value (const std::string& str)
			{
				val = str;
			}


		private:

			T _value;
			std::string _name;
		};



	}
}
