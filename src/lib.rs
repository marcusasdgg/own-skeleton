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


        // let frame_buffers: *mut *mut limine_framebuffer = framebuffer_response.framebuffers;

        // let first_buffer: limine_framebuffer = **(frame_buffers);

        // let buffer_base_address: *mut u32 = first_buffer.address as *mut u32;

        // let colo: u32 = 0x0000FFFF;
        // let pitch: u64 = first_buffer.pitch;

        // let pitch_bytes = first_buffer.pitch as usize;
        // let pixels_per_row = pitch_bytes / 4;

        let mut lock = GLOBAL_VGA_DRIVER.lock();
        lock.init(limine_goodies).unwrap();

        let mut pixel = Pixel::black();
        let mut i = 0;

        for y in 0..720{
            for x in 0..1280 {
                lock.draw_pixel(Coordinate::new(x,y), pixel);
            }
            i += 1;
            if i == 1 {
                pixel = Pixel::red();
            } 
            if i == 2{
                pixel = Pixel::green();
            }
            if i == 3 {
                pixel = Pixel::blue();
            }
            if i == 4 {
                pixel = Pixel::black();
                i = 0;
            }
            
        }
        

        lock.draw_screen();
    }
    loop {}
}
