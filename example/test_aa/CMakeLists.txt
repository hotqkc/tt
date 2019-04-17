
set(PROJECT_NAME test_aa)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/test_aa)

set(DIR_SRCS 
	${SRCROOT}/main.cpp
)

Add_Definitions(
	-D_HAS_ITERATOR_DEBUGGING=0
	-DBGFX_CONFIG_RENDERER_METAL=1
)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS}
)
