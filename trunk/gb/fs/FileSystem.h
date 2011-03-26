/**
 * @page filesystem Виртуальная файловая система
 * Виртуальная файловая система служит для абстрагирования
 * методов получения с сохранения данных от их источников.
 * Теоретически данные могут храниться как на диске непостредственно,
 * так и лежать в архивах, загружаться из сети или генерироваться на лету.
 */

#pragma once

#include <string>
#include <gb/fs/Stream.h>

namespace gb
{
	namespace fs
	{
		/**
		 * \brief Интерфейс файловой системы.
		 * 
		 * Предоставляет потоки для чтения и/или записи по имени файла.
		 * Все имена файлов задаются в utf-8.
		 */
		class FileSystem : public base::IRefCountable
		{
		public:
			/** Открывает поток для чтения */
			virtual InputStream *getInputStream(const std::string &path) = 0;
			/** Открывает поток для записи */
			virtual OutputStream *getOutputStream(const std::string &path, bool truncate) = 0;
			/** Открывает поток для чтения и записи */
			virtual IOStream *getIOStream(const std::string &path, bool truncate) = 0;
		};
		
		typedef base::RefCntHolder<FileSystem> PFileSystem;
	}
}