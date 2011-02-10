//------------------------------------------------------------------------------
//
// GameBoost
//
// copyright:	(c) 2011 GameDev.ru
// authors:		Alexey Egorov (FadeToBlack aka EvilSpirit) anandamide@mail.ru
//
// url:			http://gameboost.googlecode.com/
//				http://www.gamedev.ru/community/gameboost
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include <String>
#include <Map>

//------------------------------------------------------------------------------
//
// namespace gb
//
//------------------------------------------------------------------------------

namespace gb {

	//--------------------------------------------------------------------------
	//
	// namespace base
	//
	//--------------------------------------------------------------------------
	
	namespace base {

		//----------------------------------------------------------------------
		//
		// template Creator
		//
		//----------------------------------------------------------------------
		
		template <class Parent, class Child, class Param>
		class Creator {

		public:
			static Parent *create(Param param) {
				return new Child(param);
			}

		};

		//----------------------------------------------------------------------
		//
		// template Creator
		//
		//----------------------------------------------------------------------

		template <class Parent, class Child>
		class Creator <Parent, Child, void> {

		public:
			static Parent *create() {
				return new Child();
			}

		};

		//----------------------------------------------------------------------
		//
		// template Factory
		//
		//----------------------------------------------------------------------

		template <class Parent, class Param>
		class Factory {

			typedef Parent *(*CreateFunctionType)(Param);

			std::map <std::string, CreateFunctionType> types;

		public:

			template <class Child>
			void addType(const char *name) {
				addType(name, Creator<Parent, Child, Param>::create);
			}

			void addType(const char *name, CreateFunctionType creator) {
				types.insert(std::make_pair(std::string(name), creator));
			}

			void removeType(const char *id) {
				types.erase(id);
			}

			Parent *create(const char *type, Param param) const {
				std::map<std::string, CreateFunctionType>::const_iterator it = types.find(type);
				if (it != types.end()) {
					return it->second(param);
				}
				return NULL;
			}

			bool check(const char *id) {
				std::map<std::string, CreateFunctionType>::const_iterator it = types.find(id);
				return it != types.end();
			}

			int getTypesCount() {
				return types.size();
			}

			std::string getTypeName(int index) {
				int i = 0;
				for (std::map <std::string, CreateFunctionType>::iterator it = types.begin(); it != types.end(); it++) {
					if (i == index) return it->first;
					i++;
				}
				return "";
			}

		};

		//----------------------------------------------------------------------
		//
		// template Factory
		//
		//----------------------------------------------------------------------

		template <class Parent>
		class Factory <Parent, void> {

			typedef Parent *(*CreateFunctionType)();

			std::map <std::string, CreateFunctionType> types;

		public:

			template <class Child>
			void addType(const char *name) {
				addType(name, Creator<Parent, Child, void>::create);
			}

			void addType(const char *name, CreateFunctionType creator) {
				types.insert(std::make_pair(std::string(name), creator));
			}

			void removeType(const char *id) {
				types.erase(id);
			}

			Parent *create(const char *type) const {
				std::map<std::string, CreateFunctionType>::const_iterator it = types.find(type);
				if (it != types.end()) {
					return it->second();
				}
				return NULL;
			}

			bool check(const char *id) {
				std::map<std::string, CreateFunctionType>::const_iterator it = types.find(id);
				return it != types.end();
			}

			int getTypesCount() {
				return types.size();
			}

			std::string getTypeName(int index) {
				int i = 0;
				for (std::map <std::string, CreateFunctionType>::iterator it = types.begin(); it != types.end(); it++) {
					if (i == index) return it->first;
					i++;
				}
				return "";
			}
			

		};

		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
