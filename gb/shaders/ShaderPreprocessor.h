/**
 * C-препроцессор для загрузки шейдеров через виртуальную файловую
 * систему. Если необходимо чтобы в результат попал некоторый текст
 * без изменений, то можно использовать #pragma shader echo (...)
 * Например результатом обработки следующей строки
 * <div>#pragma shader echo (#version 130)</div>
 * будет
 * <div>#version 130</div>
 */

#pragma once
#include <gb/Config.h>

#if GB_ALLOW_BOOST_LIBRARY

#include <string>
#include <vector>

#include <gb/fs/FileSystem.h>

namespace gb
{
	namespace shaders
	{
		class ShaderPreprocessor
		{
		public:
			/**
			 * @param fs файловая система используемая для открытия файлов шейдеров
			 */
			ShaderPreprocessor(fs::FileSystem *fs);
			~ShaderPreprocessor();
			
			/**
			 * Прогоняет файл path через препроцессор, и результат возвращает через параметр shader_out.
			 * В процессе работы может загружать дополнительные файлы объявленные в #include'ах.
			 * @param path имя файла
			 * @param macro_definitions список предопределенных макросов
			 * @param shader_out строка в которой будет сохранен текст шейдера
			 */
			bool load(const std::string &path, const std::vector<std::string> &macro_definitions, std::string &shader_out);
			
		private:
			class ShaderPreprocessorImpl;
			ShaderPreprocessorImpl *pimpl;
		};
	}
}


#endif // GB_ALLOW_BOOST_LIBRARY
