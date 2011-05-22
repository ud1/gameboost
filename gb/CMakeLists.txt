project( LIBGAMEBOOST )
cmake_minimum_required(VERSION 2.8)

if (MSVC)
	# Параметры компиляции для MSVC
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D_WIN32_WINNT=0x0501 -D_USE_MATH_DEFINES -DGLEW_STATIC /MP )
else()
	# для прочих компиляторов
	add_definitions(-pedantic -Wall)
endif()

# Исходники
set( GAMEBOOST_SOURCES
		base/Atomic.h  base/Guid.h
		base/Debug.h
		base/IRefCountable.h
		base/SimpleLog.cpp  base/SimpleLog.h  base/CommonLog.cpp  base/CommonLog.h
		base/Timer.h  base/Timer.cpp  base/FPSCounter.cpp  base/FPSCounter.h 
		base/Types.h  base/Constants.h  base/Constants.cpp
		base/Logger.h base/Logger.cpp
		base/Factory.h 
		base/Atlas.h base/Atlas.cpp
		base/alignedMalloc.h base/alignedMalloc.cpp
		base/Camera.h
		graphics/Font.h graphics/FontFreeType.h graphics/FontFreeType.cpp

		t/clamp.h t/debug_cast.h
		window_subsystem/Input.h window_subsystem/KeyCodes.h window_subsystem/Window.h
		window_subsystem/WindowManager.h window_subsystem/linux/WindowManager.cpp
		graphics/Device.h graphics/Device.cpp graphics/Texture.h graphics/opengl/GLDevice.h graphics/opengl/GLDevice.cpp

		engineBlocks/BaseApplication.h engineBlocks/BaseApplication.cpp engineBlocks/GameApplication.h engineBlocks/GameApplication.cpp
		engineBlocks/EventTranslator.h engineBlocks/EventTranslator.cpp engineBlocks/InputHandlerContainer.h engineBlocks/InputHandlerMap.h
		engineBlocks/InputBase.h engineBlocks/InputBase.cpp engineBlocks/CameraInput.h engineBlocks/CameraInput.cpp
		containers/Mesh.h containers/Mesh.cpp

		color/color.h
		str/UnicodeHelpers.h

		containers/IResource.cpp containers/IResource.h containers/Texture2D.cpp containers/Texture2D.h

		containers/Image.h containers/Image.cpp
		containers/PixelFormat.h containers/PixelFormat.cpp

		loaders/images/ImageLoader.h
		loaders/images/BmpLoader.h loaders/images/BmpLoader.cpp
		loaders/images/JpegLoader.h loaders/images/JpegLoader.cpp
		loaders/models/Obj.h loaders/models/Obj.cpp

		io/DDSParser.cpp io/DDSParser.h io/FileStream.cpp io/FileStream.h io/IStream.h io/MemoryStream.cpp io/MemoryStream.h
		fs/FileSystem.h fs/Helpers.cpp fs/Helpers.h fs/LocalFS.cpp fs/LocalFS.h fs/SeekType.h fs/Stream.h
		
		mt/Job.h mt/Job.cpp mt/JobScheduler.h mt/JobScheduler.cpp mt/ThreadPolicy.h mt/ThreadPolicy.cpp mt/syncPrimitives.h

 		resource/Resource.h resource/Resource.cpp
		resource/CacheBase.h resource/CacheNoGarbage.h resource/LRUCache.h resource/AsyncLoader.h

		shaders/ShaderPreprocessor.cpp shaders/ShaderPreprocessor.h
		
		system/Path.h  system/Path.cpp  system/Path_linux.cpp  system/Path_win32.cpp  system/Path_macosx.cpp
		
		i18n/I18n.cpp  i18n/I18n.h  i18n/IntlString.h  i18n/IntlString.cpp
		i18n/Japanese.h  i18n/Japanese.cpp

		terrain/ElevationData.h terrain/IndexBuffer.h terrain/IndexBuffer.cpp
		
		Config.h )

# группы файлов в IDE
source_group( base REGULAR_EXPRESSION "base/" )
source_group( containers REGULAR_EXPRESSION "containers/" )
source_group( engineBlocks REGULAR_EXPRESSION "engineBlocks/" )
source_group( fs REGULAR_EXPRESSION "fs/" )
source_group( graphics REGULAR_EXPRESSION "graphics/" )
source_group( graphics\\opengl REGULAR_EXPRESSION "graphics/opengl/" )
source_group( i18n REGULAR_EXPRESSION "i18n/" )
source_group( io REGULAR_EXPRESSION "io/" )
source_group( loaders REGULAR_EXPRESSION "loaders/" )
source_group( math REGULAR_EXPRESSION "math/" )
source_group( mt REGULAR_EXPRESSION "mt/" )
source_group( rand REGULAR_EXPRESSION "rand/" )
source_group( shaders REGULAR_EXPRESSION "shaders/" )
source_group( system REGULAR_EXPRESSION "system/" )
source_group( strings REGULAR_EXPRESSION "str/" )
source_group( terrain REGULAR_EXPRESSION "terrain/" )
source_group( util REGULAR_EXPRESSION "util/" )

if (MSVC)
	set_source_files_properties( pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h" )
	foreach( src_file ${GAMEBOOST_SOURCES} )
		# Только для *.cpp файлов
		if (src_file MATCHES ".*[.]cpp$")
			set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yupch.h /FIpch.h" )
		endif (src_file MATCHES ".*[.]cpp$")
	endforeach( src_file ${GAMEBOOST_SOURCES} )
	list( APPEND GAMEBOOST_SOURCES pch.cpp pch.h )
endif()

#------ target -----
add_library( gameboost STATIC ${GAMEBOOST_SOURCES} )