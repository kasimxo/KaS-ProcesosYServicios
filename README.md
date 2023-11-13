# KaS-ProcesosYServicios

Programas diseñados como ejercicio para el módulo de Programación de servicios y procesos.

## Menu
Tiene un menú con distintas opciones:

  1. - Directorio: Consultará el directorio actual con el uso de system()
  2. - Fibonacci: Genera un proceso hijo con el uso de fork() para calcular tantos números de la secuencia Fibonacci como el usuario haya introducido, después, finaliza el proceso hijo.
  3. - Factorial: Calcula el valor factorial de un número introducido por el usuario, de manera recursiva.
  4. - Batería: Ejecuta el programa Bateria mediante excel().
  5. - Usuario: Imprimer el nombre del usuario actual por pantalla y después lo muestra invertido 
  6. - 
  7. - 
  8. - 
  9. - 
  10. - 
  11. - Salir: Cierra el programa.
 
  
## Bateria
Consulta el % de batería actual.
Para ello primero comprueba que el SO del sistema sea Linux (esto puede fallar en algunas distribuciones).
Si no lo es, aborta el programa.
En caso de que sea un sistema Linux, consultará los archivos del sistema correspondientes para poder calcular el % de batería actual.
