#include "../io.h"
#include "../serial.h"
/** serial_is_transmit_fifo_empty:
    *  Checks whether the transmit FIFO queue is empty or not for the given COM
    *  port.
    *
    *  @param  com The COM port
    *  @return 0 if the transmit FIFO queue is not empty
    *          1 if the transmit FIFO queue is empty
*/
int serial_is_transmit_fifo_empty(unsigned int com)
{
    return in_b(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}