#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int result = show_vm_areas();
    
    if (result == 0) {
        printf("show_vm_areas() system call executed successfully.\n");
    } else {
        printf("show_vm_areas() system call failed.\n");
    }

    exit(0);
}
