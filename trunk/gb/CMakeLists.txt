project( LIBGAMEBOOST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	# Параметры компиляции для MSVC
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 /MP )
else()
	# для прочих компиляторов
endif()

# Исходники
set( GAMEBOOST_SOURCES
		base/Atomic.h  base/Guid.h
		base/Debug.h
		base/IRefCountable.h
		base/SimpleLog.cpp  base/SimpleLog.h  base/CommonLog.cpp  base/CommonLog.h
		base/Timer.h  base/Timer.cpp  base/FPSCounter.cpp  base/FPSCounter.h 
		base/Types.h
		base/Logger.h base/Logger.cpp
		base/Factory.h

		color/color.h

		containers/IResource.cpp containers/IResource.h containers/Texture2D.cpp containers/Texture2D.h

		io/DDSParser.cpp io/DDSParser.h io/FileStream.cpp io/FileStream.h io/IStream.h io/MemoryStream.cpp io/MemoryStream.h
		fs/FileSystem.h fs/Helpers.cpp fs/Helpers.h fs/LocalFS.cpp fs/LocalFS.h fs/SeekType.h fs/Stream.h
		
		mt/Job.h mt/Job.cpp mt/JobScheduler.h mt/JobScheduler.cpp mt/ThreadPolicy.h mt/ThreadPolicy.cpp mt/syncPrimitives.h

		rand/rand.cpp rand/rand.h
		
		math/Vector.h

		# shaders/ShaderPreprocessor.cpp shaders/ShaderPreprocessor.h
		
		system/Path.h  system/Path.cpp  system/Path_linux.cpp  system/Path_win32.cpp  system/Path_macosx.cpp
		
		str/formater.cpp str/formater.h str/KsDefines.h str/KsString.cpp str/KsString.h str/KsUtils.cpp str/KsUtils.h str/String.cpp str/String.h
		
		i18n/I18n.cpp  i18n/I18n.h  i18n/IntlString.h  i18n/IntlString.cpp
		i18n/Japanese.h  i18n/Japanese.cpp
		i18n/RomanicGermanic.h  i18n/RomanicGermanic.cpp
		
		Config.h )

# группы файлов в IDE
source_group( base REGULAR_EXPRESSION "base/" )
source_group( mt REGULAR_EXPRESSION "mt/" )
source_group( io REGULAR_EXPRESSION "io/" )
source_group( math REGULAR_EXPRESSION "math/" )
source_group( system REGULAR_EXPRESSION "system/" )
source_group( i18n REGULAR_EXPRESSION "i18n/" )
source_group( strings REGULAR_EXPRESSION "str/" )

#------ additional includes ------
include_directories( ${GAMEBOOST_SOURCE_DIR} )
include_directories( ${LIBGAMEBOOST_SOURCE_DIR} )
include_directories( ${LIBGAMEBOOST_SOURCE_DIR}/deplib/boost )
include_directories( ${LIBGAMEBOOST_SOURCE_DIR}/deplib/utfcpp.sourceforge.net )

if (MSVC)
	set_source_files_properties( pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h" )
	foreach( src_file ${GAMEBOOST_SOURCES} )
		set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yupch.h" )
	endforeach( src_file ${GAMEBOOST_SOURCES} )
	list( APPEND GAMEBOOST_SOURCES pch.cpp pch.h )
endif()

#------ target -----
add_library( gameboost STATIC ${GAMEBOOST_SOURCES} )