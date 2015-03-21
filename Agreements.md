
---

Соглашения получены путем подсчета голосов участников проекта и являются мнением большинства.

---


# Назначение проекта #
  * GameBoost - набор общих библиотек наподобие boost, только заточенный под разработку игр
  * Классы библиотеки максимально независимые, и предназначены для добавления в проекты игр и движков
  * Делать из библиотеки полноценный движок в планы не входит
  * Библиотека не предназначена для написания игр с нуля.
  * Рендер в библиотеке не требуется, либо должен быть максимально упрощен и служить только для демонстрации шейдеров



# Соглашения по разработке #

Смотри документ CodeStyle

  * Имя главного namespace-а: gb
  * Префикс C у имен классов не используется, либо у класса используется два имени если сам автор для класса желает использовать вариант с префиксом.
  * Условия и т.п. блоки пишутся с переносом скобок на новую строку

# Соглашения по типам данных и библиотекам #

  * Строки - std::string, char `*`
  * Пути к файлам и ресурсам - boost::filesystem::path (utf8) при доступе к реальной файловой системе переводить в boost::filesystem::wpath
  * Целочисленные типы - stdint.h
  * Размеры и смещения - size\_t, std::streamoff, std::streampos
  * Шаред указатели - boost::shared\_ptr<> (можно переназначить на std::shared\_ptr для C++0x)
  * Короткоживущие scoped указатели - boost::scoped\_ptr<> (можно переназначить на std::scoped\_ptr для C++0x)
  * Массивы - boost::array, boost::scoped\_array (можно переназначить на std::array для C++0x)
  * Доступ к файлам - C++ streams (избегать stdio/FILE `*`, использовать mmapped io где можно).
  * Форматирование строк stringstream где возможно, иначе snprintf.
  * Вывод в консоль std::cout/std::cerr <<
  * Треды - boost::thread или свой велосипед?