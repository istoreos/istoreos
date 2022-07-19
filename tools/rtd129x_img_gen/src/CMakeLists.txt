cmake_minimum_required(VERSION 3.6.0)

project( rtd129x_img_gen )

# WjCryptLib Static Library
add_library( WjCryptLib STATIC
    WjCryptLib_Sha256.h
    WjCryptLib_Sha256.c )
target_include_directories( WjCryptLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties ( WjCryptLib PROPERTIES FOLDER lib )

# cJSON Static Library
add_library( cJSON STATIC
    cJSON.h
    cJSON.c )
target_include_directories( cJSON PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties ( cJSON PROPERTIES FOLDER lib )

# common Static Library
add_library( common STATIC
    io.c io.h
    hash.c hash.h)
target_include_directories( common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties ( common PROPERTIES FOLDER lib )

add_executable( rtd129x_img_gen
    rtd129x_img_gen.c
    fwtbl.h mbr.h
    io.h hash.h
    layout.h layout.c
    layout_json.c)
target_link_libraries( rtd129x_img_gen
    common
    WjCryptLib
    cJSON
)

install(TARGETS rtd129x_img_gen DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable( rtd129x_encode_hwsetting
    encode_hwsetting.c
)

install(TARGETS rtd129x_encode_hwsetting DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable( rtd129x_decode_hwsetting
    decode_hwsetting.c
)

add_executable( rtd129x_bootcode_gen
    rtd129x_bootcode_gen.c
)
target_link_libraries( rtd129x_bootcode_gen
    common
    WjCryptLib
)
install(TARGETS rtd129x_bootcode_gen DESTINATION ${CMAKE_INSTALL_BINDIR})
