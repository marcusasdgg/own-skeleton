#![no_std]
#![no_main]

use core::panic::PanicInfo;
mod mem;
mod paging;
mod limine;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

// define our limine stuff up here maybe? idk 
// if we do this then 
// Todo! move this out when you start making it available for other architectures.


#[unsafe(no_mangle)] 
pub extern "C" fn _start() -> ! {
    loop {}
    
}