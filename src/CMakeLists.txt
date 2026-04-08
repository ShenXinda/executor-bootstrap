# ---- Src dependencies ----
CPMAddPackage(
    NAME mcl
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/mcl/a345efe4087df11796d5fe08e3f6de391602e738"
)

CPMAddPackage(
    NAME alert-intf
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/alert-intf/f816d7e3369137c820a2e5e428726608b0a46f91"
)

CPMAddPackage(
    NAME clean-intf
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/clean-intf/7a18a6ad20cddd672473c0631ea1907da2193788"
)

CPMAddPackage(
    NAME wifi-intf
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/deps/wifi-intf/a16ac36c8682d9981ce5cf7ffc6b5d73457258bd"
)

# -----------------------------
# 生成 compile_commands.json，用于 LSP（clangd/ccls）
# -----------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Collect all src files except main.c ----

file(GLOB_RECURSE MAIN_FILE 
    "main.cpp"
)

file(GLOB_RECURSE SOURCES
    "*.c" "*.C" "*.cc" "*.CC" "*.cpp" "*.CPP" "*.c++"
)

list(REMOVE_ITEM SOURCES ${MAIN_FILE})

# ---- Define library target ----

if (SHARED)
    set(LIB_TYPE SHARED)
    set(CMAKE_C_VISIBILITY_PRESET hidden)
else()
    set(LIB_TYPE STATIC)
endif()

add_library(${TARGET_LIB} ${LIB_TYPE} ${SOURCES})

target_link_libraries(${TARGET_LIB} PUBLIC mcl alert-intf clean-intf wifi-intf)

target_include_directories(${TARGET_LIB}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/deps
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(${TARGET_LIB} PRIVATE CUSTOMER_LOG)

# ---- Add executable target ----

if (EXECUTABLE)
    set(EXEC_TARGET ${TARGET_LIB}_service)
    add_executable(${EXEC_TARGET} ${MAIN_FILE})
    target_link_libraries(${EXEC_TARGET} PRIVATE ${TARGET_LIB})
endif()
