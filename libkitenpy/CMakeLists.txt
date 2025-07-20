set(CURRENT_TARGET "libkitenpy")
set(CURRENT_TARGET_NAME "libkitenpy")

find_package(Qt6Core REQUIRED)
find_package(PythonInterp 3.11 REQUIRED)
find_package(PythonLibs 3.11 REQUIRED)

message(STATUS "Python include directory: ${PYTHON_INCLUDE_DIR}")
message(STATUS "Python library: ${PYTHON_LIBRARY}")

CreateTarget(${CURRENT_TARGET} SHARED ${CURRENT_TARGET_NAME} C++ 17)

# Qt deprecated warnings
target_compile_definitions(${CURRENT_TARGET} PRIVATE -DQT_DEPRECATED_WARNINGS)
target_compile_definitions(${CURRENT_TARGET} PRIVATE -DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

# disable Qt foreach macro
target_compile_definitions(${CURRENT_TARGET} PRIVATE -DQT_NO_FOREACH)

target_include_directories(${CURRENT_TARGET}
PRIVATE
    ${PYTHON_INCLUDE_DIR}
)

target_link_libraries(${CURRENT_TARGET}
PRIVATE
    Qt6::Core
    ${PYTHON_LIBRARY}
    -lkiten
)
