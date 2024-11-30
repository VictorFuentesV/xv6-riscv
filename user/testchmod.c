#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    char filename[] = "testfile"; // Definido como char[], no const char*

    // Creación del archivo con permisos de lectura/escritura
    int fd = open(filename, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf("Error: No se pudo crear el archivo\n");
        exit(1);
    }

    // Escritura inicial para validar los permisos
    if (write(fd, "hola", 4) != 4) {
        printf("Error: Falló la escritura inicial\n");
        close(fd);
        exit(1);
    }
    close(fd);

    // Cambio de permisos a solo lectura
    if (chmod(filename, 1) < 0) {
        printf("Error: Falló al cambiar permisos a solo lectura\n");
        exit(1);
    }

    // Prueba de escritura en modo solo lectura
    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        printf("Permisos respetados: No se puede abrir en modo escritura\n");
    } else {
        printf("Error: El archivo debería ser solo lectura\n");
        close(fd);
    }

    // Cambio de permisos a lectura/escritura
    if (chmod(filename, 3) < 0) {
        printf("Error: No se pudo restaurar permisos de escritura\n");
        exit(1);
    }

    // Escritura final para confirmar permisos restaurados
    fd = open(filename, O_RDWR);
    if (fd < 0) {
        printf("Error: No se pudo abrir el archivo en modo lectura/escritura\n");
        exit(1);
    }
    if (write(fd, "mundo", 5) != 5) {
        printf("Error: Falló la escritura final\n");
    } else {
        printf("Escritura final exitosa\n");
    }
    close(fd);

    // Cambio de permisos a inmutable
    if (chmod(filename, 5) < 0) {
        printf("Error: No se pudo marcar el archivo como inmutable\n");
        exit(1);
    }


    // Intento de restaurar permisos a lectura/escritura
    if (chmod(filename, 3) < 0) {
        printf("Archivo inmutable: No se pueden cambiar los permisos\n");
    } else {
        printf("Error: El archivo no debería permitir cambios de permisos\n");
    }



    // Limpieza del archivo
    if (unlink(filename) < 0) {
        printf("Error: No se pudo eliminar el archivo\n");
    } else {
        printf("Archivo eliminado exitosamente\n");
    }

    
    

    exit(0);
}
