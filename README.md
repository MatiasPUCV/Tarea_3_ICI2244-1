# Tarea_3_ICI2244-1

![265290404-697cadcf-5b6e-4fd4-9301-baa3883555c3](https://github.com/MatiasPUCV/Tarea_3_ICI2244-1/assets/142541831/421cc7c9-bd59-4d76-bce8-baab96296b87)

## Compilación:

Ejecute en el directorio:

`gcc -Iinclude -o Tarea3 src/app.c src/book.c src/file.c src/hashmap.c src/list.c src/main.c src/pair.c src/treemap.c src/util.c`

Tambien puede usar `compile.bat` o usar cmake.

## Información de uso:
**1. Cargar Documentos** <char* documentos ...>:

Se insertan un conjunto de nombres, el programa revisa si son carpetas o archivos de texto (.txt) y se carga la lista de archivos en la aplicación.

**2. Mostrar Documentos** :

La aplicación muestra los libros cargados, muestra su id, su título, su número de palabras y caracteres.

**3. Buscar libro por título**: <char* palabras ...>:

Se insertan palabras y la aplicación busca los títulos con todas las coincidencias y los muestra en pantalla.

## Problemas conocidos

En cada instancia que se consulta todos los libros, ocurre en opciones 2 y 3. A la hora de liberar memoria se omitirá uno de los libros. La raíz del problema ha de ser `FirstTreeMap()` ya que una sola consulta de los libros existentes no causa problemas, pero la segunda es quien los causa. Por ende `FirstTreeMap()` no da un resultado correcto cuando su `current` no es `NULL`

En la opción 3, “Buscar libro por título” es posible que se omita uno de los documentos en la fase de descarte, llevando a resultados incorrectos. El motivo se desconoce.

Por último la función de leer carpetas solo funciona en winfows.
