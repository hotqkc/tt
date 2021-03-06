
MESSAGE(STATUS "operation system is " ${CMAKE_SYSTEM})
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(SXB_OS_WINDOWS 1)
	set(OPENGL_ES 0)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    if(IOS)
        set(SXB_OS_IOS 1)
		set(OPENGL_ES 1)
	else()
		set(SXB_OS_MACOS 1)
		set(OPENGL_ES 0)
		
		# detect OS X version. (use '/usr/bin/sw_vers -productVersion' to extract V from '10.V.x'.)
        EXEC_PROGRAM(/usr/bin/sw_vers ARGS -productVersion OUTPUT_VARIABLE MACOSX_VERSION_RAW)
        STRING(REGEX REPLACE "10\\.([0-9]+).*" "\\1" MACOSX_VERSION "${MACOSX_VERSION_RAW}")
        if(${MACOSX_VERSION} LESS 7)
            message(FATAL_ERROR "Unsupported version of OS X: ${MACOSX_VERSION_RAW}")
            return()
        endif()
	endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(SXB_OS_UNIX 1)
	message(WARNING "UNIX has not been adapted yet.")
	
	if(ANDROID)
        set(SXB_OS_ANDROID 1)
		set(OPENGL_ES 1)
    else()
        set(SXB_OS_LINUX 1)
		set(OPENGL_ES 0)
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
    set(SXB_OS_IOS 1)
	set(OPENGL_ES 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(SXB_OS_ANDROID 1)
	set(OPENGL_ES 1)
else()
	message(FATAL_ERROR "Unsupported operating system or environment")
	return()
endif()

