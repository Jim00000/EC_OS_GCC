#include "device/rts5911/driver/espi_virtual_wire.h"

ec_error_t
espi_virtual_wire_set_index (uint8_t vw_index, uint8_t vw_data)
{
    ESPI->EVTXDAT_b.TXIDX = vw_index;
    ESPI->EVTXDAT_b.TXDAT = vw_data;
    while(ESPI->EVSTS_b.TXFULL == 1);

    espi_virtual_wire_clear_transaction();

    return EC_ERROR_ESPI_VW_OK;
}