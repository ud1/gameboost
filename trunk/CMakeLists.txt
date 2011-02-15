project( GAMEBOOST )
cmake_minimum_required(VERSION 2.8)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${GAMEBOOST_SOURCE_DIR}/bin CACHE PATH "Single Directory for all Executables." )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GAMEBOOST_SOURCE_DIR}/linklib CACHE PATH "Single Directory for all static libraries." )

add_subdirectory( test/deplib/gtest-1.5.0 )
add_subdirectory( gb )
add_subdirectory( test )

# kv: не смог доказать CMake::FindBoost что у меня есть на машине буст.
# параметры окружения не помогли. Пришлось отрезать всю ветку ;) убедитесь что он может успешно найти буст,
# установленный в gb/deplib/boost/, у меня не находит или просто привяжите его к этой папке
# add_subdirectory( lib )
