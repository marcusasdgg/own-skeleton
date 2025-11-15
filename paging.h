#include <stdint.h>
#include <stddef.h>

struct PAGEDIRECTORY_ENTRY {
    uint32_t present : 1;
    uint32_t read_write: 1;
    uint32_t user_supervisor: 1;
    uint32_t pwt : 1;
    uint32_t pcd : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t page_size : 1;
    uint32_t global : 1;
    uint32_t address_bits: 20; // this is pretty iffy this changes dpeending on 4mb or 4kb page directory entry.
}__attribute__((packed)); 

// for now we use identity paging i.e. 1 to 1 relationship
void initialize_paging();

// this page 