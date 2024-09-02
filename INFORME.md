## Funcionamiento llamadas al sistema
### `getppid(void)`

La llamada al sistema `getppid` permite obtener el ID del proceso padre del proceso que la invoca.

- **Retorno**: El ID del proceso padre.
- **Ejemplo**:
  - Un proceso con PID 4 puede invocar `getppid()` para obtener el PID de su proceso padre.


### `getancestor(int level)`

La llamada al sistema `getancestor` permite obtener el ID de un proceso ancestro en función de un nivel especificado. El funcionamiento es el siguiente:

- **Parámetro**: Un entero `level` que indica el nivel del ancestro deseado:
  - `level = 0` retorna el mismo proceso.
  - `level = 1` retorna el proceso padre.
  - `level = 2` retorna el abuelo.
  - Y así sucesivamente.
- **Retorno**: El ID del proceso ancestro en el nivel indicado, o `-1` si no existe tal ancestro.
- **Ejemplo**:
  - `getancestor(0)` -> Retorna el PID del proceso actual.
  - `getancestor(1)` -> Retorna el PID del proceso padre.
  - `getancestor(2)` -> Retorna el PID del abuelo, etc.

## Explicación de las Modificaciones Realizadas

### Modificación para `getppid` y `getancestor`
Se modificaron los archivos `sysproc.c`, `syscall.c`, `usys.pl`, `Makefile`, `user.h` y `syscall.h`.
En estos archivos se agregaron las funciones y los prototipos de la llamada al sistema tanto de `getppid` y de `getancestor`, para lograr su buena incorporación.

## Dificultades Encontradas y Cómo se Resolvían 
El error encontrado tiene que ver con la función `getancestors`, la cual daba un error de querer toamr un valor como int en void.
La solución a esto fue mover una parte del código de `getancestors` una linea más arriba para asi llamarla antes de trabajar, y luego reemplazar la indentada con la letra n.

##Pruebas
Para probar que funciona debe escribir en qemu `yosoytupadre`, esto dará como resultado tanto la función `getppid` como `getancestors` en una fase de prueba buena.
Si quiere realizar solo una prueba de `getppid` escriba `test_getppid`.
