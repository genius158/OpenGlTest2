cmake_minimum_required(VERSION 3.4.1)

add_library(render SHARED
            Render.cpp
            RenderContext.cpp
        )

# Include libraries needed for hello-jnicallback lib
target_link_libraries(render
        GLESv3
        log)
