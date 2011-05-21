set (deplibs_lib_dir ${deplibs_dir}/lib)
link_directories( ${deplibs_lib_dir} )
include_directories( ${deplibs_dir}/include )

# jpeg library
set(jpeglib_dir ${deplibs_dir}/jpeglib)
set(JPEG_INCLUDE_DIR ${jpeglib_dir}/jpeg-8c )
set(JPEG_LIBRARY ${deplibs_lib_dir}/jpeglib.lib)

# freetype
set(freetype_dir ${deplibs_dir}/freetype)
set(FREETYPE_INCLUDE_DIRS ${freetype_dir}/freetype-2.4.4/include)
set(FREETYPE_LIBRARY ${deplibs_lib_dir}/freetype.lib)

# glm
include_directories( ${deplibs_dir}/glm/glm-0.9.2.0 )

# utfcpp
include_directories( ${deplibs_dir}/utfcpp/utf8_v2_3_1/source )

# yaml-cpp
set(YAML_CPP_LIBRARY ${deplibs_lib_dir}/libyaml-cppmd.lib)

# glew
include_directories( ${deplibs_dir}/glew/glew-1.6.0/include )
set(GLEW_LIBRARY ${deplibs_lib_dir}/glew.lib)

# gl3
include_directories( ${deplibs_dir}/gl3 )

# gtest
include_directories( ${deplibs_dir}/gtest/gtest-1.5.0/include )