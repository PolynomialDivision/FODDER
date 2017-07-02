cmake_minimum_required(VERSION 2.6)
PROJECT(fodder)

ADD_DEFINITIONS(-Os -Wall -Werror --std=gnu99 -Wmissing-declarations -Wno-unknown-warning-option -Wno-format-truncation)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

SET(SOURCES
	main.c)
	#lib_serial.c lib_serial.h)

SET(LIBS
	ubox ubus)

ADD_EXECUTABLE(fodder ${SOURCES})

TARGET_LINK_LIBRARIES(fodder ${LIBS})

INSTALL(TARGETS fodder
	RUNTIME DESTINATION /usr/sbin/
)