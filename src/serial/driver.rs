// the very initial serial driver, we will support like 3 ports
use crate::intrinsics::{out_b, in_b};
#[derive(Clone,Copy)]
pub enum COMM {
    None,
    COMM1(u16),
    COMM2(u16),
    COMM3(u16),
}


pub struct SerialDriver {
    availableports: [COMM ; 3],
}

impl SerialDriver {
    pub const fn new() -> Self {
        let availableports = [COMM::None ; 3];
        Self {availableports}
    }

    pub unsafe fn initialize(&mut self, port_addresses: [COMM ;3]) {

        for i in 0..port_addresses.len() {
            let port = port_addresses[i];
            
            let port = match port {
                COMM::COMM1(addr) => addr,
                COMM::COMM2(addr) => addr,
                COMM::COMM3(addr) => addr,
                _ => continue
            };
            unsafe  {
                out_b(port + 1, 0x00);    // Disable all interrupts
                out_b(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
                out_b(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
                out_b(port + 1, 0x00);    //                  (hi byte)
                out_b(port + 3, 0x03);    // 8 bits, no parity, one stop bit
                out_b(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
                out_b(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
                out_b(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
                out_b(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

                if(in_b(port + 0) == 0xAE) {
                    self.availableports[i] = port_addresses[i];
                }
            }   
        }
    }

    // preliminary sanitizer function.
    fn get_internal_port(&self, port: COMM) -> COMM {
        for i in self.availableports {
            if core::mem::discriminant(&i) == core::mem::discriminant(&port) {
                return port;
            }
        }
        return COMM::None;
    }

    fn check_fifo_empty(&self, port: COMM) -> bool {
        let port = self.get_internal_port(port);
        unsafe {
            let port = match port {
                COMM::COMM1(addr) => addr,
                COMM::COMM2(addr) => addr,
                COMM::COMM3(addr) => addr,
                _ => return false
            };
        
            return in_b(port + 5) & 0x20 == 0;
        }
    }

    pub fn putchar_serial(&self, char: u8, port: COMM) {
        let port = self.get_internal_port(port);
        while (self.check_fifo_empty(port) == false) {}
        unsafe {
            let port = match port {
                COMM::COMM1(addr) => addr,
                COMM::COMM2(addr) => addr,
                COMM::COMM3(addr) => addr,
                _ => return
            };
            out_b(port,char);
        }
    }
}