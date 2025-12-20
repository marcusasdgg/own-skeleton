#![no_std]
#![no_main]

use core::ptr::write_volatile;
use core::{panic::PanicInfo, ptr};
use core::arch::asm;
mod mem;
mod paging;
mod limine;
mod vga;

use limine::LIMINE_FRAMEBUFFER_REQUEST;
use limine::limine_header::limine_framebuffer;

use limine::limine_checks;
use crate::limine::limine_header::{limine_framebuffer_request, limine_framebuffer_response};
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

        let mut pixel = Pixel::green();
        let position1 = Coordinate::new(0, 0);

        let position2 = Coordinate::new(720,720);

        lock.draw_line(position1, position2, pixel);

        lock.draw_box(position1, 719, 719, pixel);

        lock.draw_screen();

        drop(lock)
    }
    loop {}
}
