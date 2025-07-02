########################################
#
# Dynamic Thread
#
########################################

cmake_minimum_required(VERSION 3.15)

project(DynaminThread)

set(EXE_NAME "dynamic_thread")

set(CMAKE_CXX_STANDARD 11) # C++11 or Higher version
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    # Windows 설정
    add_definitions(-D_WIN32_WINNT=0x0601)
    # set(PLATFORM_LIBS ws2_32)
elseif(UNIX)
    # Unix 계열 설정
    if(CMAKE_SYSTEM_NAME STREQUAL "Android")
        # Android
        set(PLATFORM_LIBS pthread)
    elseif(APPLE)
        # macOS, iOS
        set(PLATFORM_LIBS pthread)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR
           CMAKE_SYSTEM_NAME STREQUAL "NetBSD" OR
           CMAKE_SYSTEM_NAME STREQUAL "OpenBSD" OR
           CMAKE_SYSTEM_NAME STREQUAL "DragonFly")
        # BSD 계열
        set(PLATFORM_LIBS pthread)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
        # AIX에서는 `pthread`가 일부 환경에서 제한적일 수 있음
        set(PLATFORM_LIBS pthread)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "HP-UX")
        # HP-UX는 POSIX 스레드 지원 여부 확인 필요
        set(PLATFORM_LIBS pthread)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "QNX")
        # QNX
        set(PLATFORM_LIBS pthread)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Solaris")
        # Solaris
        set(PLATFORM_LIBS pthread)
    else()
        # 일반적인 Unix-like 시스템
        set(PLATFORM_LIBS pthread)
    endif()
else()
    message(WARNING "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
    set(PLATFORM_LIBS "")
endif()


add_executable(${EXE_NAME}
    main.cpp
    DynamicThread.h
)

target_link_libraries(${EXE_NAME} PRIVATE
    ${PLATFORM_LIBS}
)
