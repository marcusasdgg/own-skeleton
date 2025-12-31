

unsafe extern "C" {
    // we link this functions in the final linking step, no rust schenigans required.
    pub unsafe fn in_b(address: u16) -> u8;
    pub unsafe fn out_b(address: u16, value: u8);
}