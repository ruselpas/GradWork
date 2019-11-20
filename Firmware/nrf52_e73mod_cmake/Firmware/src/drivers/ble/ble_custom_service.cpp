#include "ble_custom_service.hpp"

#include "logger_service.hpp"
#include "CallbackConnector.hpp"

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_sdh_ble.h"

#include <cstring>

namespace Ble::CustomService
{

CustomService::CustomService()
    :   m_serviceHandle{}
    ,   m_customValueHandles{}
    ,   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
    ,   m_uuidType{}
{
    initEventHandler();
    initCustomService();
    initAdvertisment();
    initCustomCharacteric();
}
//TODO: Remove and think about better. Just for test :/
void ble_cus_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
   // ble_cus_t * p_cus = (ble_cus_t *) p_context;
    
    NRF_LOG_INFO("BLE event received. Event type = %d\r\n", p_ble_evt->header.evt_id); 
    // if (p_cus == NULL || p_ble_evt == NULL)
    // {
    //     return;
    // }
    
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            //on_connect(p_cus, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            //on_disconnect(p_cus, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            //on_write(p_cus, p_ble_evt);
            break;
/* Handling this event is not necessary
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            NRF_LOG_INFO("EXCHANGE_MTU_REQUEST event received.\r\n");
            break;
*/
        default:
            // No implementation needed.
            break;
    }
}

void CustomService::initEventHandler()
{

    static auto customServiceHandler = cbc::obtain_connector(
        [ this ]( ble_evt_t const * _pEvent, void * _pContext )
        {
            return serviceBleEventHandler( _pEvent,_pContext );
        }
    );

        NRF_SDH_BLE_OBSERVER(
            m_serviceEvent
        ,   ServiceObserverPriority
        ,   ble_cus_on_ble_evt
        ,   nullptr
    );
    
 }

void CustomService::serviceBleEventHandler( ble_evt_t const * _pEvent, void * _pContext )
{
    Logger::Instance().logDebug( "BLE event received." );
}

void CustomService::initCustomService()
{
    struct CustomServiceInit
    {
        std::uint8_t m_initialCustomValue;
        ble_srv_cccd_security_mode_t m_customValueCharAttribute;
    };

    ret_code_t errCode{};

    // Add Custom Service UUID
    ble_uuid128_t baseUuid{};
    std::memcpy(
            &baseUuid
        ,   CustomServiceUuid.data()
        ,   CustomServiceUuid.size()
    );

    errCode = sd_ble_uuid_vs_add( &baseUuid, &m_uuidType ); // Add the Custom Service

    APP_ERROR_CHECK( errCode );

    ble_uuid_t bleUuid{ ServiceUuid, m_uuidType };

    errCode = sd_ble_gatts_service_add(
            BLE_GATTS_SRVC_TYPE_PRIMARY
        ,   &bleUuid
        ,   &m_serviceHandle
    );

    APP_ERROR_CHECK( errCode );

}

void CustomService::initCustomCharacteric()
{

}

void CustomService::initAdvertisment()
{

}

};