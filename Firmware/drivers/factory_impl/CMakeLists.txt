add_library(
    ble_factory
    ble_services_stub.cpp
    ih_ble_service_factory.cpp
    ih_ible_softdevice.cpp
)

target_include_directories(
    ble_factory
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    ble_factory
    PRIVATE
    UtilsLibrary
    drivers_ih
    logger_service
    ble_services
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(
        ble_factory
        PRIVATE
        NordicSDK::Common
        ble_services
    )
    target_compile_definitions(
        ble_factory
        PRIVATE
        USE_BLE_SERVICES
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    target_compile_definitions(
        ble_factory
        PRIVATE
        USE_DESKTOP_SIMULATOR
    )
endif()