// preface:
// this deals with setting up a rudimentary paging model 
//import summary:
// Page: A specific section of virtual memory that when accessed yields a specific configurable physical address

// pml4: the 512 entry table on the top of the hiearchy and holds 512 pml3 tables.
// pml3: The 512 entry table linked by pml4 either can point to 512 1gb pages directly or 512 pml2 tables
// pml2: the 512 entry table that can eitehr point to 512 2mb pages directly or 512 pml1 tables
// pml1: the 512 entry table pointing to 512 4 kb pages.



unsafe extern "C" {
    static mut PML4_TABLE: [u64; 512];
}


// this struct represents any 64 bit page entry for any page table level cus they all take 64 bits anyways.
#[repr(C, packed)]
struct PageEntry64 {
    value: u64
}

// all these functions assume that the caller knows what
// the fields are, and do not rely on address to be padded correctly
// on another thought maybe not pmln_ entry does that but the others correclty pad 

// Oh yeah do not use 
impl PageEntry64 {
    
    fn pmln_entry(
        execute_disable: bool, 
        avl1: u8, 
        addr: u64,
        avl2: u8,
        page_size: bool,
        avl3: bool,
        accessed: bool,
        cache_disable: bool,
        write_through: bool,
        user_super: bool,
        read_write: bool,
        present: bool
    ) -> Self {
            let mut value: u64 = (execute_disable as u64) << 11;

        todo!()
    }

    fn pml3_entry() -> Self {
        todo!()
    }


    fn pml2_entry() -> Self {
        todo!()
    }
}



// basic function to start initialising of paging should change this later.
pub fn initialise_paging(){
    todo!()
}