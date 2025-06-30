set(RAW_BINFILE_NAME rts5911.bin)

add_executable(rts5911)

set_target_properties(rts5911 PROPERTIES LINKER_LANGUAGE C)

# add_subdirectory(${CMAKE_SOURCE_DIR}/Crypto)

# add_dependencies(rts5911 crypto)

set(COMPILE_C_OPTIONS
    -std=gnu11
    -mcpu=real-m300
    -march=armv8-m.main
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -mthumb
    -mlittle-endian
    -fsigned-char
    -ffunction-sections
    -fdata-sections
    -fstack-usage
    # -finstrument-functions
    -static
    -O0
    -g3
    -ggdb
    -Wall
    -Wextra
    -Wstack-usage=256)

if(Git_FOUND)
  execute_process(
    COMMAND git describe --tags
    RESULT_VARIABLE result
    OUTPUT_VARIABLE PROJECT_VERSION)

  string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")
else()
  set(PROJECT_VERSION "v0.1.0")
endif()

# configure_file(${CMAKE_SOURCE_DIR}/src/system/Ver.c.in
# ${CMAKE_BINARY_DIR}/generated/system/Ver.c)

set(RTK_SRC
    ${CMAKE_SOURCE_DIR}/src/device/system.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/reset.s
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/crt0.s
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/svc.s
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/vector_table.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/system.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/driver/slow_timer.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/driver/i2c.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/driver/uart.c
    ${CMAKE_SOURCE_DIR}/src/device/rts5911/driver/espi_virtual_wire.c
    ${CMAKE_SOURCE_DIR}/src/kernel/main.c
    ${CMAKE_SOURCE_DIR}/src/kernel/task.c
    ${CMAKE_SOURCE_DIR}/src/kernel/scheduler.c
    ${CMAKE_SOURCE_DIR}/src/kernel/thread.c
    ${CMAKE_SOURCE_DIR}/src/kernel/malloc.c
    ${CMAKE_SOURCE_DIR}/src/debug/instrument.c
    ${CMAKE_SOURCE_DIR}/src/armv8m/init.c)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/ldscripts/rts5911.ld)

set_target_properties(rts5911 PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

target_sources(rts5911 PUBLIC ${RTK_SRC})

target_include_directories(rts5911 PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_definitions(rts5911 PRIVATE "__RTS5911__" "__FPU_PRESENT=1")

target_compile_options(rts5911 PRIVATE ${COMPILE_C_OPTIONS})

target_link_libraries(rts5911 m ${CMAKE_SOURCE_DIR}/Crypto/libcrypto.a)

target_link_options(
  rts5911
  PRIVATE
  -mcpu=real-m300
  -mfloat-abi=hard
  -mfpu=fpv5-sp-d16
  -T${LINKER_SCRIPT}
  -static
  -nostartfiles
  --specs=nosys.specs
  --specs=nano.specs
  -Xlinker
  --gc-sections
  -Wl,-Map,${CMAKE_BINARY_DIR}/EC.map
  -Wl,--start-group
  -lgcc
  -lc
  -lm
  -Wl,--print-memory-usage
  -Wl,--end-group)

# Create raw bin file
add_custom_command(
  TARGET rts5911
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:rts5911>
          "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}")

# Create elf disassembly dump
add_custom_command(
  TARGET rts5911
  POST_BUILD
  COMMAND ${CMAKE_OBJDUMP} -S -d $<TARGET_FILE:rts5911> >
          "$<TARGET_FILE:rts5911>.dump.txt")

# Create naming map
add_custom_command(
  TARGET rts5911
  POST_BUILD
  COMMAND ${CMAKE_NM} --print-size --size-sort --radix=x $<TARGET_FILE:rts5911>
          > "$<TARGET_FILE:rts5911>.nm.txt")

# Generate tag address bin
add_custom_command(
  TARGET rts5911
  POST_BUILD
  COMMAND ${TOOL_DIR}/image_tag_gen.exe ${SIGN_TAG0_ADDRESS}
          ${SIGN_TAG1_ADDRESS} ${SIGN_TAG_BIN_FILE_NAME})

# Generate signed bin file
add_custom_command(
  TARGET rts5911
  POST_BUILD DEPENDS "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}"
  COMMAND
    ${TOOL_DIR}/imgtool.exe sign --key=${TOOL_DIR}/key1.pem
    --public-key-format=full --align=32 --version=0.0.0 --header-size=32
    --load-addr=${SIGN_LOAD_ADDRESS} --pad --slot-size=${SIGN_SLOT_SIZE}
    --pad-header --spi-freq=${SIGN_SPI_FREQ} --spi-mode=0
    --spi-rdcmd=${SIGN_SPI_MODE} --dbg-en=0
    "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}"
    "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}")

# Create a duplicate signed bin as backup
add_custom_command(
  TARGET rts5911
  POST_BUILD DEPENDS "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}"
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}"
          "${CMAKE_BINARY_DIR}/${SIGN_BACKUP_BIN_FILE_NAME}")

# Copy attach_debug.bat to build directory
add_custom_command(
  TARGET rts5911
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/script/attach_debug.bat"
    "${CMAKE_BINARY_DIR}/attach_debug.bat")
