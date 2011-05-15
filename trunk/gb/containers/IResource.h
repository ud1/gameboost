/*      \file FileStream.cpp
 *      \author -Eugene-, kozlov_eugene@list.ru
*/
#pragma once
#include "gb/io/MemoryStream.h"

namespace gb
{
    namespace containers
    {
        /*
         * Класс ресурса, основанный на потоке данных. Данные в нем разбиты на группы, можно обновлять
         * их, как удобно.
         *
         * isOpened() должно возвращать, был ли создан собственно поток данных(массив байт),
         * isExist() же проверяет, был ли правильно настроен класс потомка.
         *
         * У потомков нужно определить функцию init(...) и в ней инициализировать потомок так, чтобы isExist()
         * возвращало true, только после этго можно использовать остальные функции.
         * Функция create() с настройками доступа убрана в защищенную зону за ненадобностью.
         *
         * Функция close() уничтожает поток с данными, но оставляет "интерфейс" - например, уничтожит текстуру,
         * но оставит ее размер и тип, смещение и размер блоков(сиречь мипмапов)
         * 
         * Специфика работы остальных функций осталась та же, что и у MemoryStream.
         */
        class IResource : public gb::io::MemoryStream
        {
        protected:
            size_t  groups_count;
            size_t *groups_sizes;
            size_t *groups_offsets;
            size_t  total_size;
        protected:
            virtual uint8_t*create(size_t size, int mode);
        public:
            IResource(void);
            virtual ~IResource(void);
            virtual bool create(const size_t size);
            virtual bool create(const size_t size, const void*data);
            virtual bool update(const size_t size, const void*data);
            virtual bool updateGroup(const size_t size, const void*data, const size_t group);
            virtual bool isExist() = 0;
            size_t  getGroupsCount()                    { return groups_count; };
            size_t  getGroupSize(const size_t group)    { return groups_sizes[group]; };
            size_t  getGroupOffset(const size_t group)  { return groups_offsets[group]; };
            size_t  getTotalSize()                      { return total_size; };
            void*   getDataPointer()                    { return file; };
        };
    };
};
