
pub mod limine_header;
use limine_header;
use limine_header::limine_framebuffer_request;
use limine_header::LIMINE_FRAMEBUFFER_REQUEST_ID;
use limine_header::LIMINE_REQUESTS_END_MARKER;


#[link_section = ".limine_requests"]
#[used]
pub static LIMINE_BASE_REVISION: [u64;4] = LIMINE_BASE_REVISION(4);

#[link_section = ".limine_requests"]
#[used]
pub static LIMINE_FRAMEBUFFER_REQUEST: limine_framebuffer_request = limine_framebuffer_request { 
    id: LIMINE_FRAMEBUFFER_REQUEST_ID,
    revision: 0,
    response: core::ptr::null_mut()
};


#[link_section = ".limine_requests_start"]
#[used]
pub static LIMINE_REQUESTS_START_MARKER: [u64;4] = LIMINE_REQUESTS_START_MARKER;


#[link_section = ".limine_requests_end"]
#[used]
pub static LIMINE_REQUESTS_END_MARKER: [u64;4] = LIMINE_REQUESTS_END_MARKER;

