// single display support for now, i.e. one framebuffer discard rest given by limine


use core::ptr::write_volatile;

use crate::limine::limine_header::limine_framebuffer_response;
use crate::vga::pixel::Pixel;

pub struct VgaDriver {
    // lets have an internal buffer replicating the current one for now, 
    replicated_buffer: [[Pixel ; 1920]; 1080],
    pixel_size: usize,
    width: usize,
    height: usize,
    pitch: usize,
    buffer_base_address: *mut u8,
}

unsafe impl Sync for VgaDriver {

}

unsafe impl Send for VgaDriver {

}




impl VgaDriver {
    pub const fn fake_init() -> Self {
        Self { 
            replicated_buffer: [[Pixel::black() ; 1920] ; 1080],
            width: 0,
            height: 0,
            pitch: 0,
            buffer_base_address: 0 as *mut u8,
            pixel_size: 0
        }
    }

    pub fn init(&mut self, limine_response: limine_framebuffer_response) -> Result<u32, ()> {
        unsafe {
            if limine_response.framebuffer_count < 1 {
                return Err(());
            }

            let buffer = *(*(limine_response.framebuffers));
            
            self.height = buffer.height as usize;
            self.pitch = buffer.pitch as usize;
            self.width = buffer.width as usize;
            self.buffer_base_address = buffer.address as *mut u8;
            self.pixel_size = (buffer.bpp / 8) as usize;
            Ok(1)
        }
    }
    fn draw_real_pixel(&mut self, x: usize, y: usize) {
        let pixel: Pixel = self.replicated_buffer[y][x];
        unsafe {
            let offset = (y * self.pitch + x * self.pixel_size) as usize;
            let calculated_address: *mut u8 = self.buffer_base_address.add(offset);
            let modi = calculated_address as *mut u32;

            let color = pixel.get_rgba32();
            write_volatile(modi, color);
        }
    }

    pub fn draw_screen(&mut self) {
        for y in 0..720 {
            for x in 0..1280 {
                self.draw_real_pixel(x, y);
            }
        }
    }
    // this goes into our 2nd framebuffer.
    pub fn draw_pixel(&mut self, x: usize, y: usize, pixel: Pixel) {
        self.replicated_buffer[y][x] = pixel;
    }
}