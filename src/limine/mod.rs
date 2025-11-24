
pub mod limine_header;
use limine_header::limine_framebuffer_request;
use limine_header::LIMINE_FRAMEBUFFER_REQUEST_ID;


#[unsafe(link_section = ".limine_requests")]
#[used]
pub static LIMINE_BASE_REVISION: [u64;3] = limine_header::LIMINE_BASE_REVISION(4);

#[unsafe(link_section = ".limine_requests")]
#[used]
pub static LIMINE_FRAMEBUFFER_REQUEST: limine_framebuffer_request = limine_header::limine_framebuffer_request { 
    id: limine_header::LIMINE_FRAMEBUFFER_REQUEST_ID,
    revision: 0,
    response: core::ptr::null_mut()
};


#[unsafe(link_section = ".limine_requests_start")]
#[used]
pub static LIMINE_REQUESTS_START_MARKER: [u64;4] = limine_header::LIMINE_REQUESTS_START_MARKER;


#[unsafe(link_section = ".limine_requests_end")]
#[used]
pub static LIMINE_REQUESTS_END_MARKER: [u64;2] = limine_header::LIMINE_REQUESTS_END_MARKER;

