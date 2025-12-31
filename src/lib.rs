#![no_std]
#![no_main]

use core::ptr::write_volatile;
use core::{panic::PanicInfo, ptr};
use core::arch::asm;
mod mem;
mod paging;
mod limine;
mod vga;
mod intrinsics;
mod serial;

use limine::LIMINE_FRAMEBUFFER_REQUEST;
use limine::limine_header::limine_framebuffer;

use limine::limine_checks;
use crate::limine::limine_header::{limine_framebuffer_request, limine_framebuffer_response};
use crate::serial::{GLOBAL_SERIAL_DRIVER, COMM};
use crate::vga::pixel::{Coordinate, Pixel};
use crate::vga::{GLOBAL_VGA_DRIVER, VgaDriver};


#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

// define our limine stuff up here maybe? idk 
// if we do this then 
// Todo! move this out when you start making it available for other architectures.





#[unsafe(no_mangle)] 
pub extern "C" fn _start() -> ! {
    
    unsafe {

        // if even these essential goodies don't get passed by limine we might as well stop.
        let limine_goodies = limine_checks().unwrap();

        let framebuffer_response: limine_framebuffer_response = limine_goodies;


        let mut lock = GLOBAL_VGA_DRIVER.lock();
        lock.init(limine_goodies).unwrap();

        let mut serial_lock = GLOBAL_SERIAL_DRIVER.lock();
        serial_lock.initialize([COMM::COMM1(0x3F8), COMM::None, COMM::None]);

        //serial here


        let mut pixel = Pixel::green();
        let position1 = Coordinate::new(300, 0);

        lock.draw_box(position1, 100, 100, pixel);
        lock.draw_box(Coordinate::new(400, 0), 100, 100, pixel);
        lock.draw_box(Coordinate::new(500, 0), 100, 100, pixel);
        lock.draw_box(Coordinate::new(400, 100), 100, 100, pixel);
        lock.draw_box(Coordinate::new(400, 200), 100, 100, pixel);
        
        lock.draw_screen();

        drop(lock)
    }
    loop {}
}
