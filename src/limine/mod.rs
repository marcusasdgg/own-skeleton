
pub mod limine_header;
use limine_header::limine_framebuffer_request;
use limine_header::LIMINE_FRAMEBUFFER_REQUEST_ID;

use limine_header::limine_framebuffer_response;
use core::ptr;


#[unsafe(link_section = ".limine_requests")]
#[used]
#[unsafe(no_mangle)]
pub static mut LIMINE_BASE_REVISION: [u64;3] = limine_header::LIMINE_BASE_REVISION(4);


#[unsafe(link_section = ".limine_requests")]
#[used]
#[unsafe(no_mangle)]
pub static mut LIMINE_FRAMEBUFFER_REQUEST: limine_framebuffer_request = limine_header::limine_framebuffer_request { 
    id: limine_header::LIMINE_FRAMEBUFFER_REQUEST_ID,
    revision: 0,
    response: core::ptr::null_mut()
};


#[unsafe(link_section = ".limine_requests_start")]
#[used]
#[unsafe(no_mangle)]
pub static LIMINE_REQUESTS_START_MARKER: [u64;4] = limine_header::LIMINE_REQUESTS_START_MARKER;


#[unsafe(link_section = ".limine_requests_end")]
#[used]
#[unsafe(no_mangle)]
pub static LIMINE_REQUESTS_END_MARKER: [u64;2] = limine_header::LIMINE_REQUESTS_END_MARKER;

// the function that checks if limine loaded our kernel properly with proper features like framebuffer etc.
// NOTE: This does not check the validity of all framebuffers just that it returned a nonnull response.
pub fn limine_checks() -> Result<limine_framebuffer_response,()> {
    unsafe{
        if limine_header::LIMINE_BASE_REVISION_SUPPORTED(LIMINE_BASE_REVISION) == false {
            return Err(())
        }

        if LIMINE_FRAMEBUFFER_REQUEST.response == ptr::null_mut() {
            return Err(())
        }

        Ok(*(LIMINE_FRAMEBUFFER_REQUEST.response))
    }
}

