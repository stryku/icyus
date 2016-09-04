cmake_minimum_required (VERSION 2.8.8)

set(PROJECT_NAME_STR Icyus)
project(${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)


add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)


include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS} ${COMMON_INCLUDES})
message(${GTEST_INCLUDE_DIRS})
message(${GMOCK_INCLUDE_DIRS})


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

#helpers
set (program_name "Icyus")
set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)
set (test_src_dir ${src_root}/sources/tests)
set (test_inc_dir ${test_src_dir})
set (internals_dir ${src_dir}/internals)
set (internals_inc_dir ${inc_dir}/internals)
set (ui_dir ${src_root}/uiforms)
set (lib_dir ${src_root}/lib)
set (install_dir ${src_root}/bin)
set (resources_dir ${src_root}/resources)

#install message
message (${program_name} " will be installed in:")
message (${install_dir})

include_directories (${inc_dir}
                     ${Qt5UiTools_INCLUDE_DIRS}
                     ${PROJECT_SOURCE_DIR}
                     ${PROJECT_BINARY_DIR}
                     ${test_inc_dir}) 
                     
#internals 
set (IcyusInternals_src ${internals_dir}/view/QtView.cpp
                        ${internals_dir}/view/detail/QtWidgetManager.cpp
                        ${internals_dir}/input/InputPropagator.cpp
                        ${internals_dir}/model/Model.cpp
                        ${internals_dir}/system/QtSystemInteractor.cpp
                        ${internals_dir}/system/FileWrapper.cpp
                        ${internals_dir}/utils/utils.cpp)
 
set (IcyusInternals_inc ${internals_inc_dir}/Internals.hpp
                        ${internals_inc_dir}/view/QtView.hpp
                        ${internals_inc_dir}/view/IView.hpp
                        ${internals_inc_dir}/view/detail/QtViewControls.hpp
                        ${internals_inc_dir}/view/detail/QtWidgetManager.hpp
                        ${internals_inc_dir}/view/detail/GuiUpdater.hpp
                        ${internals_inc_dir}/input/InputCallbacks.hpp
                        ${internals_inc_dir}/input/InputPropagator.hpp
                        ${internals_inc_dir}/input/IInputObserver.hpp
                        ${internals_inc_dir}/input/IInputHandler.hpp
                        ${internals_inc_dir}/model/Model.hpp
                        ${internals_inc_dir}/model/IModelObserver.hpp
                        ${internals_inc_dir}/controller/Controller.hpp
                        ${internals_inc_dir}/system/ISystemInteractor.hpp
                        ${internals_inc_dir}/system/QtSystemInteractor.hpp
                        ${internals_inc_dir}/system/FileWrapper.hpp
                        ${internals_inc_dir}/communication/FileSender.hpp
                        ${internals_inc_dir}/communication/FileReceiver.hpp
                        ${internals_inc_dir}/communication/details/TransferHeaderParser.hpp
                        ${internals_inc_dir}/communication/details/TransferHeader.hpp
                        ${internals_inc_dir}/communication/details/TransferHeaderMsgFactory.hpp
                        ${internals_inc_dir}/communication/details/FormatTraits.hpp
                        ${internals_inc_dir}/communication/details/ZmqSocket.hpp
                        ${internals_inc_dir}/utils/foreach.hpp
                        ${internals_inc_dir}/utils/log.hpp
                        ${internals_inc_dir}/utils/utils.hpp
                        ${internals_inc_dir}/utils/TestClass.hpp)  
       
       
set (Icyus_src  ${src_dir}/main.cpp
                ${src_dir}/mainwindow.cpp)
                    
set (Icyus_inc   ${inc_dir}/mainwindow.hpp
                 ${inc_dir}/InternalsCreators.hpp)


set (Icyus_hdr ${inc_dir}/mainwindow.hpp
               ${internals_inc_dir}/view/detail/GuiUpdater.hpp
               ${internals_inc_dir}/view/detail/QtWidgetManager.hpp)
set (Icyus_ui  ${ui_dir}/mainwindow.ui)

qt5_wrap_cpp(Icyus_hdr_moc ${Icyus_hdr})
#qt5_wrap_cpp(Icyus_widgetManager_moc ${internals_inc_dir}/view/detail/QtWidgetManager.hpp)
#qt5_wrap_cpp(Icyus_tmp_moc ${internals_inc_dir}/view/QtView.hpp)
qt5_wrap_ui (Icyus_ui_moc  ${Icyus_ui})


add_executable(Icyus 
                ${Icyus_src}
                ${Icyus_inc}
                ${IcyusInternals_src}
                ${IcyusInternals_inc} 
                ${Icyus_hdr_moc}
                ${Icyus_ui_moc})
               
target_link_libraries (Icyus Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES})


set( TEST_SRC_FILES ${test_src_dir}/main.cpp
                    ${test_src_dir}/FileSenderTest.cpp)
                    
set (TEST_INC_FILES ${test_src_dir}/details/SocketMock.hpp
                    ${test_src_dir}/details/FileMock.hpp
                    ${test_src_dir}/utils/utils.hpp)


add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${TEST_INC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest googlemock)

if(NOT WIN32 OR MINGW)
    target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        ${GMOCK_LIBS_DIR}/libgmock.a
        ${GMOCK_LIBS_DIR}/libmock_main.a
        )
else()
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})


install(TARGETS Icyus DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)
