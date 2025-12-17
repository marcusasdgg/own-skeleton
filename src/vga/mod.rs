
pub mod driver;
pub mod pixel;
pub use driver::*;

use spin::Mutex;

// consider using spin crate for this to synchronise it or maybe just create your own spinlock crate.
#[unsafe(link_section = ".bss")]
pub static GLOBAL_VGA_DRIVER: Mutex<VgaDriver> = Mutex::new(VgaDriver::fake_init());
