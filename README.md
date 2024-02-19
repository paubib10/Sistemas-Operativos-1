# Algoritmia y Estructura de Datos I
Bienvenido al repositorio de Sistemas Operativos I, con un enfoque mayoritario en el lenguaje de programación C. Aquí encontrarás recursos clave para mejorar tu comprensión de los conceptos fundamentales y prácticas asociadas con los sistemas operativos.

## Prácticas

### Práctica 1: Tratamiento de Cadenas y Gestor de Pilas
Primer proyecto de Sistemas Operativos I, de la asignatura de 2º curso de Ingeniería Informática, en la UIB.

**Tratamiento de Cadenas:**
- Implementa funciones similares a `<string.h>`.
- Operaciones incluyen copiar, concatenar y encontrar la longitud.

**Gestor de Pilas Dinámico y Genérico:**
- Implementa un gestor de pilas dinámico y genérico.
- Capaz de manejar elementos de cualquier tipo.
- Operaciones básicas de pila: apilar, desapilar, y verificar si está vacía.

### Practica 2: MiniShell

Segundo proyecto de Sistemas Operativos I, de la asignatura de 2º curso de Ingeniería Informática, en la UIB.

Esta práctica consistirá en la implementación de un mini shell básico basado en bash de Linux. Para su correcto funcionamiento se ha hecho por niveles, es decir, se ha dividido para desarrollarlo progresivamente, concretamente en seis niveles, y finalmente obtener el my_shell.c

**Caracteristicas del MiniShell:**

 * Admitirá varios comandos internos.
 * Admitirá comandos de shell estándar.
 * Admitirá la redirección de la salida de un comando a un archivo.
 * Admitirá procesos en segundo plano.
 * Se admitirá la interrupción con Ctrl + C y Ctrl + Z.

**Projecto hecho por:**

 * Grupo: LaTripleta
   * Atienzar Martinez, Blanca
   * Bibiloni Martinez, Pau Toni
   * Pueyo Almodóvar, Unai

**Observaciones del projecto:**

Principalmente, esta practica constaba en crear un miniShell, lo que nos parecio mas sencillo despues de ya haberlo creado, pensamos que fueron los niveles mas basicos y principales (nivel1.c, nivel2.c, nivel3.c). Por otro lado, el resto de niveles (nivel4.c, nivel5.c, nivel6.c) fueron mas dificiles porque en estos surgieron errores o warnings de niveles inferiores a estos que no habian surgido hasta el momento, lo que nos hizo volver hacia atras en varios momentos, y relentizar el tiempo para ejecutar esta practica.

### Práctica 3: Hilos y Exclusión Mutua

En esta práctica, implementaremos un sistema de hilos que accederán concurrentemente a una pila, garantizando la exclusión mutua para operaciones seguras.

**Desafío**
- Gestionar el acceso concurrente de múltiples hilos a una pila compartida de forma segura y consistente.

**Conceptos Clave:**
- Procesos e Hilos en C de Unix/Linux
- Semáforos y exclusión mutua
- Librería pthread.h: `pthread_create()`, `pthread_join()`, `pthread_exit()`, `pthread_self()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`
- Macro `PTHREAD_MUTEX_INITIALIZER`

**Implementación:**
1. **Preparación de la Pila:**
   - Verificar y crear la pila según sea necesario.
   - Manejar la inicialización y actualización de la pila de manera adecuada.

2. **Creación de Hilos:**
   - Crear 10 hilos para acceder a la pila de forma concurrente.

3. **Función del Hilo:**
   - Implementar una función segura que cada hilo ejecutará.
   - Acceder, modificar e insertar datos en la pila utilizando un mutex.

4. **Espera y Volcado de Datos:**
   - El hilo principal espera a que todos los hilos terminen.
   - Guardar la pila en un archivo después de la ejecución de los hilos.

5. **Comprobación de Datos:**
   - Reconstruir la pila desde el archivo y realizar cálculos estadísticos.

## Contribuciones

Siéntete libre de contribuir añadiendo tus propias soluciones, proponiendo mejoras o sugiriendo nuevos ejercicios. La diversidad de perspectivas enriquecerá nuestro aprendizaje colectivo.

## ¿Cómo contribuir?

1. Realiza un fork del repositorio.
2. Crea una rama para tu contribución: `git checkout -b tu-nueva-funcionalidad`
3. Haz tus cambios y haz commit: `git commit -m 'Añade nueva funcionalidad'`
4. Sube tus cambios: `git push origin tu-nueva-funcionalidad`
5. Abre un pull request para que podamos revisar y fusionar tus contribuciones.

¡Espero que disfrutes trabajando en estas practicas y aprendas mucho! Happy coding! 🚀
