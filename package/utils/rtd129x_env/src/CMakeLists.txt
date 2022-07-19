cmake_minimum_required(VERSION 3.6.0)

project( rtd129x_env )

add_executable( rtd129x_env
	rtk_env.c
	env.c env.h
	hashtable.c search.h
	crc32.c crc32.h
	io.c io.h)

install(TARGETS rtd129x_env DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable( rtk_factory_sign
	rtk_factory_sign.c
	tar.c tar.h
	io.c io.h)

install(TARGETS rtk_factory_sign DESTINATION ${CMAKE_INSTALL_BINDIR})
