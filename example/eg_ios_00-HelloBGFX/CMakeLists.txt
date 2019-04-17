
set(PROJECT_NAME eg_ios_00-HelloBGFX)

set(SRCROOT ${CMAKE_ROOT_DIR}/example/eg_ios_00-HelloBGFX)

set(DIR_SRCS 
	${SRCROOT}/main.mm
	${SRCROOT}/cube.h
	${SRCROOT}/cube.cpp
)

set(RESOURCE_SRCS
	${CMAKE_ROOT_DIR}/ios/Assets.xcassets
	${CMAKE_ROOT_DIR}/runtime.bundle
)

Add_Definitions(-D_HAS_ITERATOR_DEBUGGING=0)

sxb_add_executable(
				${PROJECT_NAME} 
				FOLDER "example" 
				SOURCES ${DIR_SRCS} ${RESOURCE_SRCS}
)

set_target_properties(
	${PROJECT_NAME}
	PROPERTIES
	MACOSX_BUNDLE YES
    RESOURCE "${RESOURCE_SRCS}"
)
