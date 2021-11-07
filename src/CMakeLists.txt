find_package(expected REQUIRED)
print_target_properties(expected-lite)

populate_source_vars(${PROJECT_SRC_DIR} ${PROJECT_NAME}_SRCS)
print_variable(${PROJECT_NAME}_SRCS)

# core target
add_library(${PROJECT_NAME}_core OBJECT "${${PROJECT_NAME}_SRCS}")
target_link_libraries(${PROJECT_NAME}_core PUBLIC ${LINK_TARGETS})

# shared target
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_core>)

