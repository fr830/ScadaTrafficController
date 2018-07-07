cmake_minimum_required(VERSION 2.8)

project(ScadaTrafficController)

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/include)
#set log4cplus
if(NOT LOG4CPLUS_ROOT)
    set(LOG4CPLUS_ROOT ${CMAKE_SOURCE_DIR}/log4cplus)
endif()

include_directories(${PROJECT_NAME} ${LOG4CPLUS_ROOT}/include)
link_directories(${PROJECT_NAME} ${LOG4CPLUS_ROOT}/lib)
add_definitions (-DUNICODE -D_UNICODE -UMBCS -U_MBCS)

#Find headers and sources files
file(GLOB_RECURSE STC_SOURCES "src/*.cpp")
file(GLOB_RECURSE STC_HEADERS "include/STC/*.hpp" "include/STC/*.h")

set(MANIFEST_RCF "${CMAKE_SOURCE_DIR}/resources/ScadaTrafficController.rc")
set(MANIFEST_OBJ "${CMAKE_BINARY_DIR}/resources/ScadaTrafficControllerResource.o")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/resources")
add_custom_command(OUTPUT ${MANIFEST_OBJ}
    COMMAND "windres"
        --input ${MANIFEST_RCF}
        --output ${MANIFEST_OBJ}
        --output-format=coff
    DEPENDS ${MANIFEST_RCF}
    COMMENT "Build manifest resource"
    )

add_executable(${PROJECT_NAME} "main.cpp" ${MANIFEST_OBJ} ${STC_SOURCES} ${STC_HEADERS})
target_link_libraries(${PROJECT_NAME} "Ws2_32")




#copy log4cplus library
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LOG4CPLUS_ROOT}/bin/liblog4cplusU.dll"
        ${CMAKE_BINARY_DIR}/liblog4cplusU.dll)
target_link_libraries(${PROJECT_NAME} "log4cplus.dll")
target_link_libraries(${PROJECT_NAME} "IPHLPAPI.dll")


set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -s")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
