
set(PROJECT_NAME tinyBGFX_bx)

set(DIR_SRCS ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/platform.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/macros.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/bx.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/bx_p.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/bx.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/debug.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/debug.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/bxstring.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/bxstring.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/allocator.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/allocator.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/hash.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/hash.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/readerwriter.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/endian.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/error.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/filepath.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/filepath.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/file.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/file.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/os.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/os.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/uint32_t.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/config.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/math.h
			 ${CMAKE_ROOT_DIR}/tinyBGFX/src/bx/math.cpp
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/simd_t.h
			 )	
			 
set(INLINE_SRC
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/bx.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/bxstring.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/allocator.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/hash.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/readerwriter.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/endian.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/error.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/uint32_t.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/math.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/simd128_swizzle.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/simd128_sse.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/simd128_ref.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/simd256_ref.inl
			 ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/inline/simd_ni.inl
    )
source_group("inline" FILES ${INLINE_SRC})

# add platform specific sources
if(WIN32)
    set(PLATFORM_SRC
        ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc/alloca.h
        ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc/dirent.h
        ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc/inttypes.h
        ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc/stdbool.h
        ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc/pre1600/stdint.h
    )
    source_group("msvc" FILES ${PLATFORM_SRC})
endif()

set(DIR_SRCS ${DIR_SRCS} ${PLATFORM_SRC} ${INLINE_SRC})			 

set(INC_DIR ${CMAKE_ROOT_DIR}/tinyBGFX/include
			${CMAKE_ROOT_DIR}/tinyBGFX/include/bx
			${CMAKE_ROOT_DIR}/bx/3rdparty
			)

IF (WIN32)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/msvc)
ELSEIF (APPLE)
	set(INC_DIR ${INC_DIR} ${CMAKE_ROOT_DIR}/tinyBGFX/include/bx/compat/osx)
ENDIF()
			
#set(LINK_LIB winmm)

include_directories(${INC_DIR})
#link_directories(${LINK_DIR})
#link_libraries(${LINK_LIB})

Add_Definitions(-D__STDC_LIMIT_MACROS
				-D__STDC_FORMAT_MACROS
				-D__STDC_CONSTANT_MACROS
				-D_DEBUG
				-DWIN32
				-D_WIN32
				-D_HAS_EXCEPTIONS=0
				-D_HAS_ITERATOR_DEBUGGING=0
				-D_ITERATOR_DEBUG_LEVEL=0
				-D_SCL_SECURE=0
				-D_SECURE_SCL=0
				-D_SCL_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_WARNINGS
				-D_CRT_SECURE_NO_DEPRECATE
				-D_WIN64
				-DBX_CONFIG_DEBUG=1
				)


SET(LIBRARY_OUTPUT_PATH ${CMAKE_ROOT_DIR}/lib/x64)
#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_ROOT_DIR}/bin/x64)

add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})
#add_library(${PROJECT_NAME} SHARED ${DIR_SRCS})

#INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_ROOT_DIR}/bin/x64/Debug)
#INSTALL(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_ROOT_DIR}/bin/x64)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "tinyBGFX")

