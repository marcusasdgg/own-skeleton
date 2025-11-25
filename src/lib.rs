#![no_std]
#![no_main]

use core::ptr::write_volatile;
use core::{panic::PanicInfo, ptr};
use core::arch::asm;
mod mem;
mod paging;
mod limine;

use limine::LIMINE_FRAMEBUFFER_REQUEST;
use limine::limine_header::limine_framebuffer;

use crate::limine::limine_header::{limine_framebuffer_request, limine_framebuffer_response};


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
        if limine::limine_header::LIMINE_BASE_REVISION_SUPPORTED(limine::LIMINE_BASE_REVISION) == false {
        unsafe {
            asm!(
                "hlt"
            )
        }
    }
        if LIMINE_FRAMEBUFFER_REQUEST.response == ptr::null_mut() {
            unsafe {
                asm!(
                    "hlt"
                )
            }
        }
        let framebuffer_response: limine_framebuffer_response =  *(LIMINE_FRAMEBUFFER_REQUEST.response);
    

        // if framebuffer_response.framebuffer_count < 1 {
        //     unsafe {
        //         asm!(
        //             "hlt"
        //         )
        //     }
        // }


        let frame_buffers: *mut *mut limine_framebuffer = framebuffer_response.framebuffers;

        let first_buffer: limine_framebuffer = **(frame_buffers);

        let buffer_base_address: *mut u32 = first_buffer.address as *mut u32;

        let colo: u32 = 0x00FFFFFF;
        let pitch: u64 = first_buffer.pitch;

        let pitch_bytes = first_buffer.pitch as usize;
        let pixels_per_row = pitch_bytes / 4;
        
        for i in 0..100 {
            let offset: usize = i * pixels_per_row + i;
            write_volatile(buffer_base_address.add(offset), colo);
        }


    }
    loop {}
}