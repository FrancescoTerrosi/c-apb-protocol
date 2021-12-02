#ifndef

#define PCLK 0 // Clock source Clock. The rising edge of PCLK times all transfers on the APB.

#define PRESETn 1 // System bus equivalent Reset. The APB reset signal is active LOW. This signal is normally connected directly to the system bus reset signal.

#define PPROT 2 // APB bridge Protection type. This signal indicates the normal, privileged, or secure protection level of the transaction and whether the transaction is a data access or an instruction access.

#define PSELx 3 // APB bridge Select. The APB bridge unit generates this signal to each peripheral bus slave. It indicates that the slave device is selected and that a data transfer is required. There is a PSELx signal for each slave.

#define PENABLE 4 // APB bridge Enable. This signal indicates the second and subsequent cycles of an APB transfer.

#define PWRITE 5 // APB bridge Direction. This signal indicates an APB write access when HIGH and an APB read access when LOW.

#define PSTRB 6 // APB bridge Write strobes. This signal indicates which byte lanes to update during a write transfer. There is one write strobe for each eight bits of the write data bus. Therefore, PSTRB[n] corresponds to PWDATA[(8n + 7):(8n)]. Write strobes must not be active during a read transfer.

#define PREADY 7 // Slave interface Ready. The slave uses this signal to extend an APB transfer.

#define PRDATA 8 // Slave interface Read Data. The selected slave drives this bus during read cycles when PWRITE is LOW. This bus can be up to 32-bits wide.

#define PSLVERR 9 // Slave interface This signal indicates a transfer failure. APB peripherals are not required to support the PSLVERR pin. This is true for both existing and new APB peripheral designs. Where a peripheral does not include this pin then the appropriate input to the APB bridge is tied LOW.

#endif
