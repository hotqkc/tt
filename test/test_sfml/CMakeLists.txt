
set(PROJECT_NAME test_sfml)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(SRCROOT ${CMAKE_ROOT_DIR}/test/test_sfml)

set(DIR_SRCS 
	${SRCROOT}/main.mm
	${SRCROOT}/AppDelegate.h
	${SRCROOT}/AppDelegate.mm
	${SRCROOT}/ViewController.h
	${SRCROOT}/ViewController.mm
)

set(INC_DIR
    ${CMAKE_ROOT_DIR}/src
)
include_directories(${INC_DIR})

set(LINK_LIBS 
	bx
	bimg
	bgfx
	sfml-system
	sfml-window
)
link_libraries(${LINK_LIBS})

Add_Definitions(
	-D_HAS_ITERATOR_DEBUGGING=0
	-DHAS_METAL_SDK
	)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "test" 
				SOURCES ${DIR_SRCS}
)

if(SXB_OS_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOSX)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")
elseif(SXB_OS_IOS)
	target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion")
elseif(SXB_OS_ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE android)
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL)

