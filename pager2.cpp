/*
 * File:   pager.cc
 * Author: suyang1
 *
 * Created on February 26, 2011, 2:46 PM
 */

#include <cstdlib>
#include <iostream>
#include "vm_pager.h"
#include <stack>
#include <queue>
#include <map>
#include <assert.h>
#include <iterator>

using namespace std;

typedef struct {
    unsigned int ppage : 30;
    unsigned int read_enable : 1;
    unsigned int write_enable : 1;
    unsigned int reference : 1;
    unsigned int dirty : 1;
    unsigned int zero : 1;
    unsigned int resident : 1;
    unsigned int valid : 1;
    unsigned int disk_block;

} vpage;

typedef struct {
    vpage* ptes[VM_ARENA_SIZE/VM_PAGESIZE];
    int top_valid_index;
} page_info_table_t;

pid_t current_id;
page_info_table_t *current_table;

stack<unsigned int> free_pages;
stack<unsigned int> free_disk_blocks;

map<pid_t, page_table_t*> ptbl_map;
map<pid_t, page_info_table_t*> ptbl_info_map;

queue<vpage*> clock_q;



/*
 * vm_init
 *
 * Called when the pager starts.  It should set up any internal data structures
 * needed by the pager, e.g. physical page bookkeeping, process table, disk
 * usage table, etc.
 *
 * vm_init is passed both the number of physical memory pages and the number
 * of disk blocks in the raw disk.
 */
void vm_init(unsigned int memory_pages, unsigned int disk_blocks)
{
    for (unsigned int i = 0; i <memory_pages; i++) {
        free_pages.push(i);
    }
    //init all free disk_blocks
    for (unsigned int i = 0; i <disk_blocks; i++) {
        free_disk_blocks.push(i);
    }

    page_table_base_register = NULL;
    current_table = NULL;
}

/*
 * vm_create
 *
 * Called when a new process, with process identifier "pid", is added to the
 * system.  It should create whatever new elements are required for each of
 * your data structures.  The new process will only run when it's switched
 * to via vm_switch().
 */
void vm_create(pid_t pid)
{
    page_table_t* ptbl = new page_table_t;
    page_info_table_t* pitbl = new page_info_table_t;

    pitbl->top_valid_index=-1;
    
    ptbl_map[pid]=ptbl;
    ptbl_info_map[pid]=pitbl;
}

/*
 * vm_switch
 *
 * Called when the kernel is switching to a new process, with process
 * identifier "pid".  This allows the pager to do any bookkeeping needed to
 * register the new process.
 */
void vm_switch(pid_t pid)
{
    current_id=pid;
    assert(ptbl_map.find(pid) != ptbl_map.end());
    page_table_base_register=ptbl_map.find(pid)->second;
    assert(ptbl_info_map.find(pid) != ptbl_info_map.end());
    current_table=ptbl_info_map.find(pid)->second;
}


/*
 * vm_extend
 *
 * A request by current process to declare as valid the lowest invalid virtual
 * page in the arena.  It should return the lowest-numbered byte of the new
 * valid virtual page.  E.g., if the valid part of the arena before calling
 * vm_extend is 0x60000000-0x60003fff, the return value will be 0x60004000,
 * and the resulting valid part of the arena will be 0x60000000-0x60005fff.
 * vm_extend should return NULL on error, e.g., if the disk is out of swap
 * space.
 */
void * vm_extend()
{
    //If top valid index is exceeds the bounds of the arena, return NULL
    if ((current_table->top_valid_index+1) >= VM_ARENA_SIZE / VM_PAGESIZE)
        return NULL;
    //If there are no free disk blocks, return NULL (Eager allocation)
    if (free_disk_blocks.empty())
        return NULL;

    current_table->top_valid_index++;
    
    page_table_base_register->ptes[current_table->top_valid_index].read_enable=0;
    page_table_base_register->ptes[current_table->top_valid_index].write_enable=0;

    vpage* p = new vpage;
    p->read_enable=0;
    p->write_enable=0;
    p->reference=0;
    p->resident=0;
    
    p->disk_block=free_disk_blocks.top();
    free_disk_blocks.pop();
    
    p->valid=1;
    p->zero=1;

    current_table->ptes[current_table->top_valid_index]=p;
    return (void *) ((unsigned long long) VM_ARENA_BASEADDR + current_table->top_valid_index * VM_PAGESIZE);


}

/*
 * vm_fault
 *
 * Called when current process has a fault at virtual address addr.  write_flag
 * is true if the access that caused the fault is a write.
 * Should return 0 on success, -1 on failure.
 */
int vm_fault(void *addr, bool write_flag)
{
    if (((unsigned long long)addr - (unsigned long long)VM_ARENA_BASEADDR) >= (current_process->top_valid_index+1)*VM_PAGESIZE)
    return -1;

    //page number
    vpage* p = current_table->ptes[((unsigned long long)addr - (unsigned long long)VM_ARENA_BASEADDR) / VM_PAGESIZE];

    assert(p->valid);
    p->reference = true;

    if(write_flag)
    {
        p->
        if(p->resident==1)
        {
            
        }
        else
        {
            if(p->zero==1)
            {
                assert(p->resident==0);

            }
        }
    }
    return 0;
}

void remove(vpage* p)
{

}

void evict()
{
    
}

/*
 * vm_syslog
 *
 * A request by current process to log a message that is stored in the process'
 * arena at address "message" and is of length "len".
 *
 * Should return 0 on success, -1 on failure.
 */
int vm_syslog(void *message, unsigned int len)
{
    return 0;
}

/*
 * vm_destroy
 *
 * Called when current process exits.  It should deallocate all resources
 * held by the current process (page table, physical pages, disk blocks, etc.)
 */
void vm_destroy()
{
        for (unsigned int i = 0; i <=current_table->top_valid_index; i++) {
            vpage* p = current_table->ptes[i];
            if (p->resident==1) {
                free_pages.push(p->ppage);
                remove(p);
            }
            free_disk_blocks.push(p->disk_block);
            delete p;
        }
        delete current_table;
        delete page_table_base_register;

        ptbl_map.erase(current_id);
        ptbl_info_map.erase(current_id);
}