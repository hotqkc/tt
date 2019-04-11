
set(PROJECT_NAME example_00-HelloWorld)

set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++1y)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/example_00-HelloWorld)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
	${SRCROOT}/logo.h
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)

if(SXB_OS_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm gdi32)
elseif(SXB_OS_MACOSX)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")
elseif(SXB_OS_IOS)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework UIKit" "-framework CoreGraphics" "-framework QuartzCore" "-framework CoreMotion" "-framework Metal" "-framework OpenGLES")
elseif(SXB_OS_ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE android)
endif()
