cmake_minimum_required(VERSION 3.2)



IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release."  )
ELSE()
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" )
ENDIF()


set(DO_DEBUG "1")

list (INSERT _COMPILE_FLAGS 0
                    -std=c++14 
                    -Wall 
                    -Werror
                    -fPIC
                  #  -Wpedantic
                    # needed for boost library
                    -Wno-unused-function 
                    -Wno-unused-local-typedefs 
                    -Wno-unused-variable 
                    -Wno-unused-value                   
                    -Wno-deprecated-declarations
                    -Wno-placement-new # needed for gcc6 and boost 1.61 boost.function
                    )


#IF(CMAKE_BUILD_TYPE STREQUAL Debug)
IF(DO_DEBUG STREQUAL "2")

   # list (APPEND _COMPILE_FLAGS  
   #                 -g
   #                 -gdwarf-2)
                    
     if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections ")       

        list(APPEND _COMPILE_FLAGS                     
                -ffunction-sections
                -fdata-sections                             
        )
    endif()
    
ELSE()


    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections -flto")
        #set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections ")
        list(APPEND _COMPILE_FLAGS
                -fvisibility=hidden                
                -ffunction-sections
                -fdata-sections
                -flto                
                -fuse-linker-plugin
                #-fno-rtti                        
        )

        
       
    endif()
    list(APPEND _COMPILE_FLAGS        
                -Os         
                -s                       
        )    
ENDIF()



# Boost
set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
hunter_add_package(Boost COMPONENTS system)
find_package(Boost 1.59 COMPONENTS system REQUIRED)
include_directories (AFTER ${Boost_INCLUDE_DIRS})

## pre
#hunter_add_package(lib-cpp-pre)
#find_package(lib-cpp-pre 1.4.1 REQUIRED)
#include_directories(AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})

hunter_add_package(libsodium)
find_package(libsodium CONFIG REQUIRED)
include_directories(AFTER ${LIB_SODIUM_INCLUDE_DIRS})

# Threads
find_package(Threads)

## fill blocks.hpp
# Get list of some *.hpp files in folder include 
#file(GLOB block_include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/sauter/real_device/ddc/blocks/*/*.hpp)
#file(GLOB block_include_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/sauter/real_device/ddc/block/[a-z_]*/[a-z_]*.hpp)

# Convert the list of files into #includes
foreach(block_include_file ${block_include_files})
  message(INFO "BLOCK: ${block_include_files}") 
  set(include_statements "${include_statements}#include <${block_include_file}>\n")
endforeach(block_include_file ${block_include_files})

# Fill the template    
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sauter/real_device/ddc/block/blocks.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/sauter/real_device/ddc/block/blocks.hpp)



####
# Create targets

#add_definitions(${_COMPILE_FLAGS})
#include_directories(${CMAKE_CURRENT_LIST_DIR})
#add_executable(ddc_main ddc_main.cpp)
#target_link_libraries(ddc_main ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)

add_executable(test_main2 test_main2.cpp)
target_link_libraries(test_main2 ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread libsodium::libsodium)


#add_definitions(${_COMPILE_FLAGS})
#include_directories(${CMAKE_CURRENT_LIST_DIR})
#add_executable(hardware_main hardware_main.cpp)
#target_link_libraries(hardware_main ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)


