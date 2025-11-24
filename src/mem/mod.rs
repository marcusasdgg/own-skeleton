
// required memory functions for std::core to work properly

// near future if u see any bugs whatsoever 
// todo! replace all own representations with std::libcore versions
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn memcpy(dst: *mut u8, src: *const u8, len: usize) -> *mut u8 {
    for i in 0..len {
        unsafe {
            *dst.add(i) = *src.add(i);
        }
    }
    dst
}
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn memcmp(a: *const u8, b: *const u8, len: usize) -> i32 {
    for i in 0..len {
        unsafe {
            if *a.add(i) != *b.add(i) {
                return i as i32
            }
        }
    }
    0
}
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn memmove(dst: *mut u8, src: *const u8, len: usize) -> *mut u8 {
    if (dst as *const u8) < src {
        for i in 0..len {
            unsafe {
                *dst.add(i) = *src.add(i);
            }
        }
    } else {
        for i in (0..len).rev() {
            unsafe {
                *dst.add(i-1) = *src.add(i-1);
            }
        }
    }
    dst
}
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn memset(dst: *mut u8, src_byte: i32, len: usize) -> *mut u8 {
    for i in 0..len {
        unsafe {
            *dst.add(i) = src_byte as u8;
        }
    }
    dst
}
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn bcmp(a: *const u8, b: *const u8, len: usize) -> i32{
    return unsafe {memcmp(a, b, len)}
}
#[unsafe(no_mangle)] 
pub unsafe extern "C" fn strlen(src: *const u8) -> i32 {
    let mut i: i32 = 0;
    unsafe{
        while *src.add(i as usize) != 0 {
            i += 1;
        }
    }
    return i
}