add_library(jangine STATIC
    "director/jdirector.cpp"
)
target_include_directories(jangine
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
