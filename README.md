# KaS-ProcesosYServicios

Programas diseñados como ejercicio para el módulo de Programación de servicios y procesos.

## Documentación

### Menu
Tiene un menú con distintas opciones:

  1. - Directorio: Consultará el directorio actual con el uso de system()
  2. - Fibonacci: Genera un proceso hijo con el uso de fork() para calcular tantos números de la secuencia Fibonacci como el usuario haya introducido, después, finaliza el proceso hijo.
  3. - Factorial: Calcula el valor factorial de un número introducido por el usuario, de manera recursiva.
  4. - Batería: Ejecuta el programa Bateria mediante excel().
  5. - Usuario: Imprimer el nombre del usuario actual por pantalla y después lo muestra invertido 
  6. - Consola: Permite al usuario introducir cualquier comando y ejecutarlo en consola. El resultado se imprime en la pantalla.
  7. - Eliminar registro de opciones: Elimina el archivo "RegistroOpciones" si este existe.
  8. - Consultar registro de opciones: Muestra por pantalla el contenido del archivo "RegistroOpciones".
  9. - Iniciar registro de opciones: Inicia un subproceso al que le enviará los mismos inputs que hace el usuario sobre la selección de opciones a través de una pipe. Estos inputs se grabarán en un archivo denominado "RegistroOpciones" junto con la fecha y hora.
  10. - Finalizar registro de opciones: Finaliza el subproceso que graba las opciones.
  11. - Salir: Cierra el programa.
 
  
### Bateria
Consulta el % de batería actual.
Para ello primero comprueba que el SO del sistema sea Linux (esto puede fallar en algunas distribuciones).
Si no lo es, aborta el programa.
En caso de que sea un sistema Linux, consultará los archivos del sistema correspondientes para poder calcular el % de batería actual.

## Set-up

Para hacer el set-up solamente se necesitan compilar los dos archivos con extensión .c. Para ello, basta con introducir esta secuencia de comandos:

	gcc menu.c -o Menu
	gcc bateria.c -o Bateria

IMPORTANTE: El programa Bateria no necesita tener compilado el programa Menu, pero a la inversa no es así, ya que una de las opciones del Menu es ejecutar Bateria, y dará error.

Con esto, habremos compilado los dos archivos en la misma ruta en la que estuvieran descargados. Para ejecutar cualquiera de ellos, desde la consola:

	./Menu -> Ejecuta el programa principal
	./Bateria -> Ejecuta la consulta de la batería directamente (se puede hacer desde el programa Menu)
