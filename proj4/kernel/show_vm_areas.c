#include "../../kernel/types.h"
#include "../../kernel/param.h" 
#include "../../kernel/memlayout.h" 
#include "../../kernel/riscv.h" 
#include "../../kernel/defs.h" 
#include "../../kernel/spinlock.h"
#include "../../kernel/proc.h"
#include "../../kernel/sleeplock.h"
#include "../../kernel/fs.h"
#include "../../kernel/file.h"
#include "../../kernel/fcntl.h"

uint64 sys_show_vm_areas(void) {
    struct proc *p = myproc();
    pagetable_t pagetable = p->pagetable;
    if (p == 0 || pagetable == 0) {
        printf("No process found or invalid pagetable.\n");
        return -1;
    }

    printf("Memory-mapped areas for process %d:\n", p->pid);

    uint64 start = 0, end = 0;
    int mem_size = 0;

    for (uint64 va = 0; va < MAXVA; va += PGSIZE) {
        pte_t *pte = walk(pagetable, va, 0);
        if (pte && (*pte & PTE_V)) { 
            if (start == 0) 
                start = va;
            end = va + PGSIZE;
            mem_size++;
        }
        else if (start != 0) {
            printf("0x%lx - 0x%lx: %d pages\n", start, end, mem_size);
            start = 0;
            mem_size = 0;
        }
    }   

    return 0;
}