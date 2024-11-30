## Funcionamiento y lógica

# Inicialización y Creación de Archivo

Se define un nombre de archivo estático: "testfile"
Utiliza open() con banderas O_CREATE | O_RDWR para crear el archivo, además se incluye un manejo de errores para la creación del archivo. Luego se realiza una escritura inicial de prueba con el texto "hola"

#  Ciclo de Pruebas de Permisos
Fase 1: Restricción de Permisos

Cambia los permisos a solo lectura usando chmod(filename, 1)
Intenta abrir el archivo en modo escritura y se verifica que se bloquee el acceso de escritura correctamente.

Fase 2: Restauración de Permisos

Restaura permisos a lectura/escritura con chmod(filename, 3)
Realiza una escritura de prueba con el texto "mundo" y confirma que se pueden restaurar los permisos correctamente.

Fase 3: Prueba de Inmutabilidad

Marca el archivo como inmutable con chmod(filename, 5)
Intenta cambiar los permisos nuevamente y verifica que no se puedan modificar los permisos del archivo.


# Limpieza Final

Se intenta eliminar el archivo usando unlink() para luego registrar el resultado de la operación de la eliminación del archivo


# Características Técnicas Destacadas
# Gestión Detallada de Permisos

Distintos modos de chmod():

1: Permisos de solo lectura
3: Permisos de lectura/escritura
5: Modo inmutable



# Manejo Robusto de Errores

Se realizaron muchas verificaciones en cada operación con mensajes informativos para ver los diferentes errores que puedan ocurrir. Además se hace un control de flujo para poder garantizar la integridad de las pruebas.

# Operaciones Realizadas

-Creación de archivo
-Escritura inicial
-Cambio de permisos
-Prueba de restricciones
-Restauración de permisos
-Prueba de inmutabilidad
-Eliminación de archivo

## Problemas Encontrados

Se encontró un problema, el cual era ocasionado por el archivo "risv.h"
La solución para este problema fue editar el archivo que se encuentra en kernel y luego de eso no hubieron problemas.

Tuvimos un problema con BSIZE donde se tuvo que hacer un arreglo en "mkfs.c" para arreglar este error. "printf("BSIZE = %d, sizeof(struct dinode) = %lu\n", BSIZE, sizeof(struct dinode));".



## Explicación de las modificaciones realizadas

# usys.pl
Se agregó "entry(chmod)"

# user.h
Se agregó "int chmod(char *path, int mode);"

# sysfile.c
Se agregó sys_chmod al sysfile.

# syscall.c
Se agregaron los extern y los syscalls de sys_chmod.

# syscall.h
Se agregó la definición de sys_chmod.

# fs.h
Se agregó al dinode "int perm;" y "char padding[57];"

# fs.c
Se editaron estructuras ialloc, iupdate y ilock para que contengan los cambios necesarios para lo solicitado.

# file.h
Se agregó al inode "int perm".

# mkfs.c
Se agregó la solución a un problema del BSIZE.

# testchmod.c
Se agregó el archivo de prueba.

# Makefile
Se agregó el "$U/_testchmod\"