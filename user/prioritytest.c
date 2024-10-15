#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int i;
    int pid;

    // 20 procesos buenos (tenemos 21 puesto que el primero sale erroneo)
    for(i = 0; i < 21; i++) {
        pid = fork();
        if(pid < 0) {
            printf("Error al crear el proceso\n");
            exit(1);
        }
        if(pid == 0) { // Proceso hijo
            // sleep para evitar colisiones
            sleep(i * 10);

            // Formato de impresión del proceso hijo
            printf("Ejecutando proceso hijo %d, PID: %d\n", i, getpid());

            sleep(200); // Sleep

            
        } else {
            // Impresión
            printf("Ejecutando proceso hijo %d con PID: %d\n", i, pid);
        }
    }
}