#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int my_pid = getpid();

    // Probar getppid
    int ppid = getppid();
    printf("PID %d: El ID del proceso padre es: %d\n", my_pid, ppid);

    // Probar getancestor
    int n = 0;  // Comenzar con el proceso actual (n=0)

    while (1) {
        int ancestor = getancestor(n);

        if (ancestor < 0) {
            printf("PID %d: No ancestor at level %d\n", my_pid, n);
            break;  // Romper el ciclo si no hay más ancestros
        } else {
            printf("PID %d: Ancestor at level %d is process %d\n", my_pid, n, ancestor);
        }

        n++;  // Incrementar el nivel de ancestros
    }

    exit(0);
}
