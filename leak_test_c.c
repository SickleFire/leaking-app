#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Keep global references so the compiler knows the memory is "alive"
void* leak_registry[1000]; 

int main() {
    int i = 0;
    while (i < 1000) {
        // 1. Allocate 1MB
        void* ptr = malloc(1024 * 1024); 
        
        if (ptr != NULL) {
            // 2. CRITICAL: Write data to force the OS to create Private Dirty Pages
            memset(ptr, 0xAB, 1024 * 1024); 
            
            // 3. Save the reference
            leak_registry[i] = ptr; 
            i++;
        }
        
        printf("Leaked 1MB... Total: %d MB\n", i);
        Sleep(1 * 1000); // Sleep 1 second
    }
    return 0;
}