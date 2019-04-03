
set(PROJECT_NAME tinyBGFX_bgfx)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/bgfx.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx.idl.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx_p.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/defines.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/embedded_shader.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/config.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/platform.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_dxbc.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_dxbc.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_dx9bc.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_dx9bc.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_spirv.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/shader_spirv.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vertexdecl.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vertexdecl.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/topology.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/topology.cpp			 
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vs_debugfont.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vs_debugfont.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_debugfont.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_debugfont.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vs_clear.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/vs_clear.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear0.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear0.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear1.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear1.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear2.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear2.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear3.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear3.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear4.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear4.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear5.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear5.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear6.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear6.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear7.bin.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/fs_clear7.sc
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/charset.h
			 )	

set(C99_SRCS
		${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/c99/bgfx.h
    )
source_group("c99" FILES ${C99_SRCS})	

set(DIR_SRCS ${DIR_SRCS} ${C99_SRCS})			 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/bgfx/3rdparty
			${CMAKE_ROOT_DIR}/bgfx/3rdparty/dxsdk/include
			${CMAKE_ROOT_DIR}/bgfx/3rdparty/khronos
			)

IF (WIN32)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc)
ENDIF()
			
#set(LINK_LIB winmm)

include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(${LINK_LIB})

Add_Definitions(-D__STDC_LIMIT_MACROS
				-D__STDC_FORMAT_MACROS
				-D__STDC_CONSTANT_MACROS
				-D_HAS_EXCEPTIONS=0
				-D_HAS_ITERATOR_DEBUGGING=0
				-D_ITERATOR_DEBUG_LEVEL=0
				-D_SCL_SECURE=0
				-D_SECURE_SCL=0
				-D_SCL_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_DEPRECATE
				-DBGFX_CONFIG_DEBUG=1
			)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
#add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

#INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
#INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinyBGFX")

