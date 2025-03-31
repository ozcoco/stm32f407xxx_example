# 该文件夹存放板载外设功能代码

# 板载功能是否启用配置
option(USE_BSP "是否启用板载功能" ON)
option(USE_BSP_LED "是否启用LED模块" ON)

if (USE_BSP)
    # 添加include目录
    include_directories(BSP)
    # 启用LED模块
    if(USE_BSP_LED)
        message(STATUS "启用LED模块")
        add_compile_definitions(USE_BSP_LED)
    endif ()
    # 添加编译源文件
    file(GLOB_RECURSE BSP_SOURCES "BSP/*.*")
    list(APPEND SOURCES ${BSP_SOURCES})
else ()
    message(STATUS "禁用板载功能")
endif ()