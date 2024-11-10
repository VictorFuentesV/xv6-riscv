#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define PGSIZE 4096

int main() {
    // Obtener la dirección actual del heap alineada a página
    char *addr = (char*)(((uint64)sbrk(0) + PGSIZE-1) & ~(PGSIZE-1));
    
    // Reservar una página
    if (sbrk(PGSIZE) == (void*)-1) {
        printf("sbrk failed\n");
        exit(1);
    }

    // Primero verificar que podemos escribir
    printf("Writing to page before protection...\n");
    addr[0] = 'A';
    printf("Successfully wrote 'A'\n");

    // Intentar proteger la página
    printf("Protecting page...\n");
    if (mprotect(addr, 1) < 0) {
        printf("mprotect failed\n");
        exit(1);
    }
    printf("Page protected successfully\n");

    // Intentar escribir en la página protegida - esto debería causar un error
    printf("Attempting to write to protected page (should fail)...\n");
    addr[0] = 'B';  // Esto debería causar un trap
    
    // No deberíamos llegar aquí
    printf("ERROR: Successfully wrote to protected page!\n");
    return 1;
}