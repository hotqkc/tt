
set(PROJECT_NAME test_sfml)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_sfml)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

set(LINK_LIBS 
    sfml-system
    sfml-window
)
link_libraries(${LINK_LIBS})

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon" -ObjC)

#sfml_find_package(OpenGL INCLUDE "OPENGL_INCLUDE_DIR" LINK "OPENGL_gl_LIBRARY")

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)

