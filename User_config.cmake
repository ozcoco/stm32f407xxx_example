# 该文件夹存放板载外设功能代码

# 板载功能是否启用配置
option(USE_USER "是否启用板载功能" ON)
option(USE_USER_DELAY "是否启用delay模块" ON)
option(USE_USER_LED "是否启用LED模块" ON)
option(USE_USER_LOG "是否启用log模块" ON)
option(USE_USER_FLASH "是否启用FLASH模块" ON)
option(USE_USER_LIGHT_SENSOR "是否启用light sensor模块" ON)
option(USE_USER_MPU_6050 "是否启用MPU6050模块" OFF)
option(USE_USER_LCD "是否启用LCD模块" ON)
option(USE_USER_AT24C02 "是否启用AT24C02模块" OFF)

if (USE_USER)
    message(STATUS "启用板载功能")
    # 定义源文件变量
    set(USER_SOURCES "")
    file(GLOB USER_MODULE_SOURCES "User/*.*")
    list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
    message(STATUS "板载功能源文件: ${USER_SOURCES}")
    # 添加include目录
    include_directories(User)
    # 启用log模块
    if (USE_USER_DELAY)
        message(STATUS "启用delay模块")
        add_compile_definitions(USE_USER_DELAY)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/delay/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用log模块
    if (USE_USER_LOG)
        message(STATUS "启用log模块")
        add_compile_definitions(USE_USER_LOG)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/log/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用LED模块
    if (USE_USER_LED)
        message(STATUS "启用LED模块")
        add_compile_definitions(USE_USER_LED)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/led/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用FLASH模块
    if (USE_USER_FLASH)
        message(STATUS "启用FLASH模块")
        add_compile_definitions(USE_USER_FLASH)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/flash/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用light sensor模块
    if (USE_USER_LIGHT_SENSOR)
        message(STATUS "启用light sensor模块")
        add_compile_definitions(USE_USER_LIGHT_SENSOR)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/sensor/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用MPU6050模块
    if (USE_USER_MPU_6050)
        message(STATUS "启用MPU6050模块")
        add_compile_definitions(USE_USER_MPU_6050)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/mpu/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用LCD模块
    if (USE_USER_LCD)
        message(STATUS "启用LCD模块")
        add_compile_definitions(USE_USER_LCD)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/lcd/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 启用AT24C02模块
    if (USE_USER_AT24C02)
        message(STATUS "启用AT24C02模块")
        add_compile_definitions(USE_USER_AT24C02)
        file(GLOB_RECURSE USER_MODULE_SOURCES "User/at24c02/*.*")
        list(APPEND USER_SOURCES ${USER_MODULE_SOURCES})
        message(STATUS "板载功能源文件: ${USER_SOURCES}")
    endif ()
    # 添加编译源文件
    list(APPEND SOURCES ${USER_SOURCES})
else ()
    message(STATUS "禁用板载功能")
endif ()