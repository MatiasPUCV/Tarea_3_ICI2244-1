# Tarea_3_ICI2244-1

![265290404-697cadcf-5b6e-4fd4-9301-baa3883555c3](https://github.com/MatiasPUCV/Tarea_3_ICI2244-1/assets/142541831/421cc7c9-bd59-4d76-bce8-baab96296b87)

## Compilación:

Ejecute en el directorio:

`gcc -Iinclude -o Tarea3 src/app.c src/book.c src/file.c src/hashmap.c src/list.c src/main.c src/pair.c src/treemap.c src/util.c`

Tambien puede usar `compile.bat` o usar cmake.

## Información de uso:
**1. Cargar Documentos** `<char* documentos ...>`:

Se insertan un conjunto de nombres, el programa revisa si son carpetas o archivos de texto (.txt) y se carga la lista de archivos en la aplicación.

**2. Mostrar Documentos** `none`:

La aplicación muestra los libros cargados, muestra su id, su título, su número de palabras y caracteres.

**3. Buscar libro por título** `<char* palabras ...>`:

Se insertan palabras y la aplicación busca los títulos con todas las coincidencias y los muestra en pantalla.

**4. Palabras con mayor frecuencia** `<int id>`:
   
Se ingresa el id de un libro y la aplicación muestra las 10 palabras más frecuentes en este.

**5. Palabras más relevantes** `<char* titulo>`:

Se ingresa el título de un libro y se muestran las 10 palabras más relevantes de un libro. Esto sigue una fórmula distinta a la opción anterior.

**6. Buscar palabra** `<char* palabra>`:

Se ingresa una palabra y se muestra en qué documentos aparece, esto en orden descendente.


## Problemas conocidos

En “Buscar libro por título”. A veces la aplicación sufre un error de segmentación cuando no hay elementos válidos. La causa es desconocida

También la función de leer carpetas solo funciona en Microsoft Windows™.

