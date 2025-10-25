#include "../pic.h"
#include "../io.h"

static void PIC_remap(int offset1, int offset2)
{
	out_b(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	out_b(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	out_b(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	out_b(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	out_b(PIC1_DATA, 1 << CASCADE_IRQ);        // ICW3: tell Master PIC that there is a slave PIC at IRQ2
	io_wait();
	out_b(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	
	out_b(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	out_b(PIC2_DATA, ICW4_8086);
	io_wait();

	// Unmask both PICs.
	out_b(PIC1_DATA, 0);
	out_b(PIC2_DATA, 0);
}

//can change this if u need to map more interrupts ig pogchamp
void initialize_PIC(){
    PIC_remap(32,40);
}


