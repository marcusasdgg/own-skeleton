
pub mod driver;
pub mod pixel;
pub use driver::*;

use spin::Mutex;

// consider using spin crate for this to synchronise it or maybe just create your own spinlock crate.
// man bullshit that a 1920x1080 array uses 38 mb. fuck u fuck u fuck u fuck u
#[unsafe(link_section = ".bss")]
pub static GLOBAL_VGA_DRIVER: Mutex<VgaDriver> = Mutex::new(VgaDriver::fake_init());
