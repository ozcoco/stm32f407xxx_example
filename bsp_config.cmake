# 该文件夹存放板载外设功能代码

# 板载功能是否启用配置
option(USE_USER "是否启用板载功能" ON)
option(USE_USER_LED "是否启用LED模块" ON)
option(USE_USER_FLASH "是否启用FLASH模块" ON)
option(USE_USER_LIGHT_SENSOR "是否启用light sensor模块" ON)

if (USE_USER)
    # 添加include目录
    include_directories(User)
    # 启用LED模块
    if (USE_USER_LED)
        message(STATUS "启用LED模块")
        add_compile_definitions(USE_USER_LED)
    endif ()
    # 启用FLASH模块
    if (USE_USER_FLASH)
        message(STATUS "启用FLASH模块")
        add_compile_definitions(USE_USER_FLASH)
    endif ()
    # 启用light sensor模块
    if (USE_USER_LIGHT_SENSOR)
        message(STATUS "启用light sensor模块")
        add_compile_definitions(USE_USER_LIGHT_SENSOR)
    endif ()
    # 添加编译源文件
    file(GLOB_RECURSE USER_SOURCES "User/*.*")
    list(APPEND SOURCES ${USER_SOURCES})
else ()
    message(STATUS "禁用板载功能")
endif ()