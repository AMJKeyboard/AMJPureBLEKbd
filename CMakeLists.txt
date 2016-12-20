PROJECT(AMJPureBLEKbd C)
CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

SET(SDK_ROOT ${CMAKE_SOURCE_DIR}/nRF5_SDK)

IF(NOT EXISTS "${SDK_ROOT}/components" )
    MESSAGE( FATAL_ERROR "Not found nRF_SDK. need nRF5 SDK v12.1.0" )
ENDIF()

SET(NRF_TOOLS ${CMAKE_SOURCE_DIR}/nRF5_TOOLS)

SET(NRFJPROGBIN ${NRF_TOOLS}/nrfjprog/nrfjprog)
SET(MERGEHEXBIN ${NRF_TOOLS}/mergehex/mergehex)

IF(NOT EXISTS "${NRFJPROGBIN}" )
    MESSAGE( WARNING "Not found nrfjprog." )
ENDIF()

IF(NOT EXISTS "${MERGEHEXBIN}" )
    MESSAGE( WARNING "Not found mergehex." )
ENDIF()

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_C_COMPILER "arm-none-eabi-gcc")
SET(CMAKE_LINKER "arm-none-eabi-ld")
SET(CMAKE_OBJCOPY "arm-none-eabi-objcopy")
SET(CMAKE_SIZE "arm-none-eabi-size")

SET(FAMILY "NRF51")
SET(DEVICE "NRF51822")
SET(SOFTDEVICE "S130")
SET(SOFTDEVICE_HEX ${SDK_ROOT}/components/softdevice/s130/hex/s130_nrf51_2.0.1_softdevice.hex)
SET(MERGE_HEX merge.hex)
SET(MAP_SCRIPT nfr51822_xxaa.map)
SET(LINK_SCRIPT ${CMAKE_SOURCE_DIR}/src/script/s130_nrf51822_xxaa.ld)
#SET(LINK_SCRIPT ${SDK_ROOT}/components/softdevice/s130/toolchain/armgcc/armgcc_s130_nrf51822_xxaa.ld)
SET(LINK_COMMON_SCRIPT ${SDK_ROOT}/components/toolchain/gcc)

INCLUDE_DIRECTORIES(
    ${SDK_ROOT}/components
    ${SDK_ROOT}/components/ble/ble_advertising
    ${SDK_ROOT}/components/ble/ble_dtm
    ${SDK_ROOT}/components/ble/ble_racp
    ${SDK_ROOT}/components/ble/ble_services/ble_ancs_c
    ${SDK_ROOT}/components/ble/ble_services/ble_ans_c
    ${SDK_ROOT}/components/ble/ble_services/ble_bas
    ${SDK_ROOT}/components/ble/ble_services/ble_bas_c
    ${SDK_ROOT}/components/ble/ble_services/ble_cscs
    ${SDK_ROOT}/components/ble/ble_services/ble_cts_c
    ${SDK_ROOT}/components/ble/ble_services/ble_dfu
    ${SDK_ROOT}/components/ble/ble_services/ble_dis
    ${SDK_ROOT}/components/ble/ble_services/ble_gls
    ${SDK_ROOT}/components/ble/ble_services/ble_hids
    ${SDK_ROOT}/components/ble/ble_services/ble_hrs
    ${SDK_ROOT}/components/ble/ble_services/ble_hrs_c
    ${SDK_ROOT}/components/ble/ble_services/ble_hts
    ${SDK_ROOT}/components/ble/ble_services/ble_ias
    ${SDK_ROOT}/components/ble/ble_services/ble_ias_c
    ${SDK_ROOT}/components/ble/ble_services/ble_lbs
    ${SDK_ROOT}/components/ble/ble_services/ble_lbs_c
    ${SDK_ROOT}/components/ble/ble_services/ble_lls
    ${SDK_ROOT}/components/ble/ble_services/ble_nus
    ${SDK_ROOT}/components/ble/ble_services/ble_nus_c
    ${SDK_ROOT}/components/ble/ble_services/ble_rscs
    ${SDK_ROOT}/components/ble/ble_services/ble_rscs_c
    ${SDK_ROOT}/components/ble/ble_services/ble_tps
    ${SDK_ROOT}/components/ble/common
    ${SDK_ROOT}/components/ble/nrf_ble_qwr
    ${SDK_ROOT}/components/ble/peer_manager
    ${SDK_ROOT}/components/device
    ${SDK_ROOT}/components/drivers_nrf/adc
    ${SDK_ROOT}/components/drivers_nrf/clock
    ${SDK_ROOT}/components/drivers_nrf/common
    ${SDK_ROOT}/components/drivers_nrf/comp
    ${SDK_ROOT}/components/drivers_nrf/delay
    ${SDK_ROOT}/components/drivers_nrf/gpiote
    ${SDK_ROOT}/components/drivers_nrf/hal
    ${SDK_ROOT}/components/drivers_nrf/i2s
    ${SDK_ROOT}/components/drivers_nrf/lpcomp
    ${SDK_ROOT}/components/drivers_nrf/pdm
    ${SDK_ROOT}/components/drivers_nrf/ppi
    ${SDK_ROOT}/components/drivers_nrf/pwm
    ${SDK_ROOT}/components/drivers_nrf/qdec
    ${SDK_ROOT}/components/drivers_nrf/rng
    ${SDK_ROOT}/components/drivers_nrf/rtc
    ${SDK_ROOT}/components/drivers_nrf/saadc
    ${SDK_ROOT}/components/drivers_nrf/spi_master
    ${SDK_ROOT}/components/drivers_nrf/spi_slave
    ${SDK_ROOT}/components/drivers_nrf/swi
    ${SDK_ROOT}/components/drivers_nrf/timer
    ${SDK_ROOT}/components/drivers_nrf/twi_master
    ${SDK_ROOT}/components/drivers_nrf/twis_slave
    ${SDK_ROOT}/components/drivers_nrf/uart
    ${SDK_ROOT}/components/drivers_nrf/wdt
    ${SDK_ROOT}/components/libraries/button
    ${SDK_ROOT}/components/libraries/crc16
    ${SDK_ROOT}/components/libraries/crc32
    ${SDK_ROOT}/components/libraries/csense
    ${SDK_ROOT}/components/libraries/csense_drv
    ${SDK_ROOT}/components/libraries/experimental_section_vars
    ${SDK_ROOT}/components/libraries/fds
    ${SDK_ROOT}/components/libraries/fifo
    ${SDK_ROOT}/components/libraries/fstorage
    ${SDK_ROOT}/components/libraries/hardfault
    ${SDK_ROOT}/components/libraries/hci
    ${SDK_ROOT}/components/libraries/led_softblink
    ${SDK_ROOT}/components/libraries/log
    ${SDK_ROOT}/components/libraries/log/src
    ${SDK_ROOT}/components/libraries/low_power_pwm
    ${SDK_ROOT}/components/libraries/mailbox
    ${SDK_ROOT}/components/libraries/mem_manager
    ${SDK_ROOT}/components/libraries/pwm
    ${SDK_ROOT}/components/libraries/scheduler
    ${SDK_ROOT}/components/libraries/slip
    ${SDK_ROOT}/components/libraries/timer
    ${SDK_ROOT}/components/libraries/twi
    ${SDK_ROOT}/components/libraries/uart
    ${SDK_ROOT}/components/libraries/util
    ${SDK_ROOT}/components/libraries/sensorsim/
    ${SDK_ROOT}/external/freertos/source
    ${SDK_ROOT}/external/freertos/source/include/
    ${SDK_ROOT}/external/freertos/portable
    ${SDK_ROOT}/external/freertos/portable/CMSIS/nrf51/
    ${SDK_ROOT}/external/freertos/portable/GCC/nrf51/
    ${SDK_ROOT}/components/softdevice/common/softdevice_handler
    ${SDK_ROOT}/components/softdevice/s130/headers
    ${SDK_ROOT}/components/softdevice/s130/headers/nrf51
    ${SDK_ROOT}/components/toolchain
    ${SDK_ROOT}/components/toolchain/gcc
    ${SDK_ROOT}/components/toolchain/cmsis/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/config
)

SET(SRC_DEVICE
    ${SDK_ROOT}/components/toolchain/gcc/gcc_startup_nrf51.S
    ${SDK_ROOT}/components/toolchain/system_nrf51.c
    ${SDK_ROOT}/components/softdevice/common/softdevice_handler/softdevice_handler.c
    ${SDK_ROOT}/components/softdevice/common/softdevice_handler/softdevice_handler_appsh.c
)

SET(SRC_DRIVERS
    ${SDK_ROOT}/components/drivers_nrf/clock/nrf_drv_clock.c
    ${SDK_ROOT}/components/drivers_nrf/common/nrf_drv_common.c
    ${SDK_ROOT}/components/drivers_nrf/rtc/nrf_drv_rtc.c

    ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c
    ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c

    ${SDK_ROOT}/components/drivers_nrf/gpiote/nrf_drv_gpiote.c
    ${SDK_ROOT}/components/drivers_nrf/uart/nrf_drv_uart.c
    ${SDK_ROOT}/components/drivers_nrf/twi_master/nrf_drv_twi.c
)

SET(SRC_LIBRARIES
    ${SDK_ROOT}/components/libraries/util/nrf_assert.c
    ${SDK_ROOT}/components/libraries/util/app_error.c
    ${SDK_ROOT}/components/libraries/util/app_error_weak.c
    ${SDK_ROOT}/components/libraries/util/app_util_platform.c
    ${SDK_ROOT}/components/libraries/timer/app_timer.c
    ${SDK_ROOT}/components/libraries/timer/app_timer_appsh.c

    ${SDK_ROOT}/components/libraries/hardfault/hardfault_implementation.c
    ${SDK_ROOT}/components/libraries/hardfault/nrf51/handler/hardfault_handler_gcc.c
    ${SDK_ROOT}/components/libraries/fstorage/fstorage.c
    ${SDK_ROOT}/components/libraries/sensorsim/sensorsim.c
    ${SDK_ROOT}/components/drivers_nrf/hal/nrf_adc.c
    ${SDK_ROOT}/components/libraries/util/sdk_mapped_flags.c
    ${SDK_ROOT}/components/libraries/fds/fds.c
    ${SDK_ROOT}/components/libraries/crc16/crc16.c

    ${SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
    ${SDK_ROOT}/components/libraries/log/src/nrf_log_backend_serial.c

    ${SDK_ROOT}/components/libraries/uart/app_uart_fifo.c
    ${SDK_ROOT}/components/libraries/scheduler/app_scheduler.c
    ${SDK_ROOT}/components/libraries/uart/retarget.c
)

SET(SRC_BLE
    ${SDK_ROOT}/components/ble/common/ble_advdata.c
    ${SDK_ROOT}/components/ble/ble_advertising/ble_advertising.c
    ${SDK_ROOT}/components/ble/common/ble_conn_params.c
    ${SDK_ROOT}/components/ble/common/ble_srv_common.c
    ${SDK_ROOT}/components/ble/common/ble_conn_state.c
    ${SDK_ROOT}/components/ble/peer_manager/gatt_cache_manager.c
    ${SDK_ROOT}/components/ble/peer_manager/gatts_cache_manager.c
    ${SDK_ROOT}/components/ble/peer_manager/id_manager.c
    ${SDK_ROOT}/components/ble/peer_manager/peer_data.c
    ${SDK_ROOT}/components/ble/peer_manager/peer_data_storage.c
    ${SDK_ROOT}/components/ble/peer_manager/peer_database.c
    ${SDK_ROOT}/components/ble/peer_manager/peer_id.c
    ${SDK_ROOT}/components/ble/peer_manager/peer_manager.c
    ${SDK_ROOT}/components/ble/peer_manager/pm_buffer.c
    ${SDK_ROOT}/components/ble/peer_manager/pm_mutex.c
    ${SDK_ROOT}/components/ble/peer_manager/security_dispatcher.c
    ${SDK_ROOT}/components/ble/peer_manager/security_manager.c
)

SET(SRC_BLE_SERVICES
    ${SDK_ROOT}/components/ble/ble_services/ble_bas/ble_bas.c
    ${SDK_ROOT}/components/ble/ble_services/ble_dis/ble_dis.c
    ${SDK_ROOT}/components/ble/ble_services/ble_hids/ble_hids.c
)

SET(SRC_APP ${CMAKE_SOURCE_DIR}/src/main.c
            ${CMAKE_SOURCE_DIR}/src/matrix.c
            ${CMAKE_SOURCE_DIR}/src/battery_service.c
            ${CMAKE_SOURCE_DIR}/src/hids_service.c
            ${CMAKE_SOURCE_DIR}/src/timers.c
            ${CMAKE_SOURCE_DIR}/src/layer.c
            ${CMAKE_SOURCE_DIR}/src/actions.c
            ${CMAKE_SOURCE_DIR}/src/eeprom.c
            ${CMAKE_SOURCE_DIR}/src/keymap_common.c
            ${CMAKE_SOURCE_DIR}/src/keymap_default.c)

SET_PROPERTY(SOURCE ${SDK_ROOT}/components/toolchain/gcc/gcc_startup_nrf51.S PROPERTY LANGUAGE C)

SET(CMAKE_C_FLAGS_DEBUG " -DDEBUG -O0 -g3 -ggdb")
SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET_PROPERTY(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${MAP_SCRIPT} ${MERGE_HEX})
SET(MCU_FLAGS "-mcpu=cortex-m0 -march=armv6-m -mthumb -mabi=aapcs -mfloat-abi=soft ")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall --std=c99 -MP -MD --short-enums -fno-builtin -fno-strict-aliasing -ffunction-sections -fdata-sections")
ADD_DEFINITIONS(-D${FAMILY} -D${DEVICE} -D${SOFTDEVICE} -D__STACK_SIZE=2048 -D__HEAP_SIZE=1024 -DSOFTDEVICE_PRESENT -DBLE_STACK_SUPPORT_REQD -DSWI_DISABLE0 -DNRF_SD_BLE_API_VERSION=2)
SET(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs -lc -lnosys -static -Wl,-Map=${MAP_SCRIPT} -Wl,--gc-section  -L${LINK_COMMON_SCRIPT} -T${LINK_SCRIPT}")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

CMAKE_POLICY(SET CMP0015 OLD)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

ADD_EXECUTABLE(${PROJECT_NAME}.elf ${SRC_APP} ${SRC_BLE} ${SRC_DEVICE} ${SRC_DRIVERS} ${SRC_RTOS} ${SRC_LIBRARIES} ${SRC_BLE_SERVICES})

ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.hex COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.elf OUTPUT ${PROJECT_NAME}.bin COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf)
ADD_CUSTOM_COMMAND(DEPENDS ${PROJECT_NAME}.hex OUTPUT ${MERGE_HEX} COMMAND ${MERGEHEXBIN} -m ${SOFTDEVICE_HEX} ${PROJECT_NAME}.hex -o ${MERGE_HEX})

ADD_CUSTOM_TARGET(generate_merge_hex ALL DEPENDS ${MERGE_HEX})
ADD_CUSTOM_TARGET(generate_bin ALL DEPENDS ${PROJECT_NAME}.bin)
ADD_CUSTOM_TARGET(generate_hex ALL DEPENDS ${PROJECT_NAME}.hex)

ADD_CUSTOM_TARGET(erase ${NRFJPROGBIN} -e -f NRF51)

ADD_CUSTOM_TARGET(reset ${NRFJPROGBIN} -r -f NRF51)

ADD_CUSTOM_TARGET(flash_softdevice ${NRFJPROGBIN} --program ${SOFTDEVICE_HEX} -f NRF51 --chiperase)

ADD_CUSTOM_TARGET(flash ${NRFJPROGBIN} --program ${PROJECT_NAME}.hex --verify -f NRF51 --sectorerase
    COMMAND ${NRFJPROGBIN} -r -f NRF51
    DEPENDS ${PROJECT_NAME}.hex)
