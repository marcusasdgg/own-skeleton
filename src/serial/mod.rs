
use crate::intrinsics;
use spin::Mutex;
pub mod driver;
pub use driver::*;


// initialize glorious serial 
#[unsafe(link_section = ".bss")]
pub static GLOBAL_SERIAL_DRIVER: Mutex<SerialDriver> = Mutex::new(SerialDriver::new());
