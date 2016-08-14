cmake_minimum_required (VERSION 2.8.12)
project (Icyus)

set (program_name "Icyus")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (HOST_LIBS_DIR "C:/moje/libs/lib/x86")
set (HOST_INC_DIR "C:/moje/libs/include")

find_package (ZMQ REQUIRED)
if (NOT ZMQ_FOUND)
    message (ERROR "ZMQ not found!")
endif()
include_directories (${ZMQ_INCLUDE_DIR})

set(BOOST_ROOT C:/moje/libs/boost/boost_1_61_0)
find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message (ERROR "Boost not found!")
endif()
include_directories (${Boost_INCLUDE_DIRS})

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)
set (internals_dir ${src_dir}/internals)
set (internals_inc_dir ${inc_dir}/internals)
set (ui_dir ${src_root}/uiforms)
set (lib_dir ${src_root}/lib)
set (install_dir ${src_root}/bin)
set (resources_dir ${src_root}/resources)

message (${program_name} " will be installed in:")
message (${install_dir})

include_directories (${inc_dir}
                     ${Qt5UiTools_INCLUDE_DIRS})

set (IcyusInternals_src ${internals_dir}/view/QtView.cpp
                        ${internals_dir}/view/View.cpp)
                     
set (IcyusInternals_inc ${internals_inc_dir}/view/QtView.hpp
                        ${internals_inc_dir}/view/View.hpp
                        ${internals_inc_dir}/view/detail/QtWidgetManager.hpp)
                     
set (Icyus_src  ${src_dir}/main.cpp
                ${src_dir}/mainwindow.cpp)
                    
set (Icyus_inc   ${inc_dir}/mainwindow.hpp)

set (Icyus_hdr ${inc_dir}/mainwindow.hpp)
set (Icyus_ui  ${ui_dir}/mainwindow.ui)

qt5_wrap_cpp(Icyus_hdr_moc ${Icyus_hdr})
qt5_wrap_ui (Icyus_ui_moc  ${Icyus_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_executable(Icyus 
                ${Icyus_src}
                ${Icyus_inc}
                ${IcyusInternals_src}
                ${IcyusInternals_inc} 
                ${Icyus_hdr_moc}
                ${Icyus_ui_moc})
               
target_link_libraries (Icyus Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES})


install(TARGETS Icyus DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)