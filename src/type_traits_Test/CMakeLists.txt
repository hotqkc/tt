
set(PROJECT_NAME type_traits_Test)

aux_source_directory(. DIR_SRCS)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "test")

