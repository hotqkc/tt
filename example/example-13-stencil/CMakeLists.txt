
set(PROJECT_NAME example-13-stencil)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example-13-stencil)

set(DIR_SRCS ${SRCROOT}/main.cpp
			 ${SRCROOT}/stencil.h
			 ${SRCROOT}/stencil.cpp
			)

set(INC_DIR ${CMAKE_ROOT_DIR}/include 
			${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/tinySFML/include
			)
		
IF (WIN32)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc)
ELSEIF (APPLE)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/osx)
ENDIF()

set(LINK_LIBS 
		tinyBGFX_bgfx
		tinyBGFX_bx 
		tinyBGFX_bimg
		tinySFML_System
		tinySFML_Window
		sxbCommon
	)

include_directories(${INC_DIR})
link_libraries(${LINK_LIBS})

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)