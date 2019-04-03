
set(PROJECT_NAME tinyBGFX_bgfx)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/bgfx.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx.idl.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bgfx/bgfx_p.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/defines.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bgfx/embedded_shader.h
			 )	 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinyBGFX/include
			)
			
#set(LINK_LIB winmm)

include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(${LINK_LIB})

#Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
#add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

#INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
#INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinyBGFX")

