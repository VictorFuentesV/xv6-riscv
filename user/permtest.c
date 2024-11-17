#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

char *test_file = "test.txt";
char *test_msg = "Hello, xv6!";
char *test_msg2 = "Writing again!";

int
main(void)
{
  int fd;
  
  // 1. Crear archivo con permisos de lectura/escritura
  printf("1. Creando archivo...\n");
  fd = open(test_file, O_CREATE | O_RDWR);
  if(fd < 0){
    printf("Error al crear archivo\n");
    exit(1);
  }
  
  // Escribir mensaje inicial
  if(write(fd, test_msg, strlen(test_msg)) != strlen(test_msg)){
    printf("Error en escritura inicial\n");
    exit(1);
  }
  close(fd);
  printf("Escritura inicial exitosa\n");

  // 2. Cambiar a solo lectura
  printf("\n2. Cambiando a solo lectura...\n");
  if(chmod(test_file, 1) < 0){
    printf("Error al cambiar permisos a solo lectura\n");
    exit(1);
  }

  // Intentar escribir (debe fallar)
  printf("Intentando escribir en modo solo lectura...\n");
  fd = open(test_file, O_WRONLY);
  if(fd >= 0){
    printf("Error: pudo abrir archivo de solo lectura en modo escritura\n");
    exit(1);
  }
  printf("Prueba de solo lectura exitosa (no permitió escritura)\n");

  // 3. Restaurar permisos de lectura/escritura
  printf("\n3. Restaurando permisos de lectura/escritura...\n");
  if(chmod(test_file, 3) < 0){
    printf("Error al restaurar permisos\n");
    exit(1);
  }

  // Intentar escribir de nuevo
  fd = open(test_file, O_WRONLY);
  if(fd < 0){
    printf("Error: no pudo abrir archivo para escritura\n");
    exit(1);
  }
  if(write(fd, test_msg2, strlen(test_msg2)) != strlen(test_msg2)){
    printf("Error en segunda escritura\n");
    exit(1);
  }
  close(fd);
  printf("Segunda escritura exitosa\n");

  // 4. Probar inmutabilidad
  printf("\n4. Probando inmutabilidad...\n");
  if(chmod(test_file, 5) < 0){
    printf("Error al establecer inmutabilidad\n");
    exit(1);
  }

  // Intentar escribir en archivo inmutable
  printf("Intentando escribir en archivo inmutable...\n");
  fd = open(test_file, O_WRONLY);
  if(fd >= 0){
    printf("Error: pudo abrir archivo inmutable en modo escritura\n");
    exit(1);
  }

  // Intentar cambiar permisos de archivo inmutable
  printf("Intentando cambiar permisos de archivo inmutable...\n");
  if(chmod(test_file, 3) >= 0){
    printf("Error: pudo cambiar permisos de archivo inmutable\n");
    exit(1);
  }
  printf("Pruebas de inmutabilidad exitosas\n");

  printf("\nTodas las pruebas completadas exitosamente!\n");
  exit(0);
}