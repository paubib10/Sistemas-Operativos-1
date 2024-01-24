 #include "my_lib.h"

// METODOS

size_t my_strlen(const char *str) {
    size_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
} 

char *my_strcpy(char *dest, const char *src) {

    while (*src != '\0') {
        *dest = *src;  // Copiar el carácter de src a dest
        ++dest;        // Mover el puntero dest al siguiente elemento
        ++src;         // Mover el puntero src al siguiente elemento
    }

    *dest = '\0';  // Agregar el carácter nulo al final de dest

    return dest; // Devolver el puntero al inicio de dest
}

char *my_strncpy(char *dest, const char *src, size_t n) {

    while (n > 0 && *src != '\0') {
        *dest++ = *src++;
        n--;
    }

    // Rellenar con '\0' si strlen(src) < n
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }

    return dest; 
}

char *my_strcat(char *dest, const char *src) {

    // Avanzar hasta el final de dest
    while (*dest != '\0') {
        dest++;
    }

    // Copiar caracteres de src a dest
    while (*src != '\0') {
        *dest++ = *src++;
    }

    // Añadir el carácter nulo al final de la cadena resultante
    *dest = '\0';

    return dest; // Devolver el puntero al inicio de dest
}

char *my_strchr(const char *str, int c) {

    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str; // Convertir const char * a char *
        }
        str++;
    }

    // Si no se encuentra el carácter, devolver NULL
    return NULL;
}

// PILA

struct my_stack *my_stack_init(int size) {
  struct my_stack *stack = malloc(sizeof(struct my_stack));

  stack->size = size;
  stack->top = NULL;

  return stack;
}

int my_stack_push(struct my_stack *stack, void *data) {
  // VERIFICA SI LA PILA ESTA VACIA O EL TAMAÑO ES NEGATIVO
  if (!stack|| stack->size <= 0) return -1;

  // CREA UN NUEVO NODO DE LA PILA Y RESERVA MEMORIA PARA ÉL
  struct my_stack_node *new_node = malloc(sizeof(struct my_stack_node));
  if (!new_node) return -1;
  
  // ASIGNAMOS EL PUNTERO A LOS DATOS Y ACTUALIZA EL PUNTERO AL SIGUIENTE NODO
  new_node->data = data;
  new_node->next = stack->top;

  // ACTUALIZAMOS EL PUNTERO AL NODO SUPERIOR DE LA PILA
  stack->top = new_node;

  return 0;
}

void *my_stack_pop(struct my_stack *stack) {
  // VERIFICA SI LA PILA ESTA VACIA O EL TAMAÑO ES NEGATIVO
  if (!stack || stack->size <= 0 || !stack->top) return NULL;

  // GUARDAMOS EL NODO TOP EN UNA VARIABLE TEMPORAL
  struct my_stack_node *aux = stack->top;
  void *data = aux->data;

  //ACTUALIZA TOP Y LIBERA LA MEMORIA OCUPADA POR EL NODO EXTRAIDO
  stack->top = aux->next;
  free(aux);

  // DEVOLVEMOS EL PUNTERO A LOS DATOS DEL ELEMENTO ELIMINADO
  return data;
}

int my_stack_len(struct my_stack *stack) {
  int count = 0;

  // INICIALIZAMOS UN PUNTERO AL NODO ACTUAL, APUNTANDO AL NODO SUPERIOR DE LA PILA
  struct my_stack_node *actual = stack->top;

  // RECORRE LA PILA MIENTRAS HAYA NODOS (ACTUAL NO SEA NULL)
  while (actual != NULL) {
    count++;
    actual = actual->next;
  }

  // DEVOLVEMOS EL CONTADOR (LONGITUD DE LA PILA)
  return count;
}

int my_stack_purge(struct my_stack *stack) {
  // VERIFICA SI LA PILA ESTA VACIA
  if (!stack) return 0;

  int bytes_liberados = 0;

  // RECORRE LA PILA LIBERANDO MEMORIA DE NODOS Y DATOS
  while (stack->top) {
    // GUARDAMOS EL NODO TOP EN UNA VARIABLE TEMPORAL
    struct my_stack_node *aux = stack->top;

    stack->top = aux->next; // nodo superior de la pila apunta al siguiente nodo
    free(aux->data);
    free(aux);

    // ACTUALIZAMOS EL CONTADOR SUMANDO LA CANTIDAD DE MEMORIA LIBERADA PARA EL NODO Y SUS DATOS
    bytes_liberados += sizeof(struct my_stack_node) + stack->size;
  }

  free(stack);
  // ACTUALIZAMOS EL CONTADOR SUMANDO LA CANTIDAD DE MEMORIA LIBERADA PARA LA ESTRUCTURA DE LA PILA COMPLETA
  bytes_liberados += sizeof(struct my_stack);

  return bytes_liberados;
}

/* Función: stackIterator
 * --------------------
 * recorre cada nodo desde la parte superior hasta llegar al último nodo y
 * por lo tanto escribe los datos desde el elemento inferior al superior.
 * fd: archivo donde debemos escribir/leer.
 * stack: puntero a la pila, que deberia haber sido inicializada.
 * node: nodo actual en el esta situado el top.
 * length: número de nodos que hay en los elementos de la pila.
 * Devuelve: el total de cambios realizados. Mientras
 * que cuando no quedan elementos, devolvemos 0
 */
int stackIterator(int fd, struct my_stack* stack, struct my_stack_node* node, int length) {
    int changes = 0;
    void* data;

    //Loop por cada elementos de la pila
    if(length--) {
        data = node->data;
        node = node->next;

        //Llamada recursiva para obtener el primer elemento
        changes += stackIterator(fd, stack, node, length);


        //Verificamos que la escritura fue exitosa
        int res = write(fd, data, stack->size);
        if(res == -1) {
            perror("Error: ");
            return 0;
        }

        changes++;
        return changes;
    }

    return 0;
}

/* Función: my_stack_write
 * --------------------
 * Almacena los datos de la pila en el fichero indicado por filename. Los 
 * datos han de quedar escritos en el fichero en el mismo orden en que 
 * fueron introducidos en la pila.
 * stack: puntero a la pila, que deberia haber sido inicializada.
 * filename: caracter que indica el fichero.
 * Devuelve: el número de elementos almacenados, -1 si hubo error.
 */
int my_stack_write (struct my_stack *stack, char *filename){
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    //Verificamos si el fichero se ha abierto correctamente
    if(fd == -1) {
        perror("Error: ");
        return -1;
    }


    //Verificamos si la escritura ha sido correctamente
    int res = write(fd, &stack->size, sizeof(int));
    if(res == -1 ) {
        perror("Error: ");
        return -1;
    }

    //Llamamos al escritor recurrente
    int count = stackIterator(fd, stack, stack->top, my_stack_len(stack));

    //Verificacion del cierre del fichero
    res = close(fd);
    if(res == -1 ) {
        perror("Error: ");
        return -1;
    }

    return count;
}

/* Función: my_stack_read
 * --------------------
 * Lee los datos de la pila almacenados en el fichero y 
 * reconstruye la pila en memoria principal.
 * filename: caracter que indica el fichero.
 * Devuelve: el puntero a la pila creada, y si hubo error, retorna NULL.
 */
struct my_stack *my_stack_read (char *filename){
    //Verificamos si el fichero se ha abierto correctamente
    int fd = open(filename, O_RDONLY);
    if(!fd) {
        perror("Error: ");
        return NULL;
    }

    int size = 0;
    read(fd, &size, sizeof(int));

    //Inicializar una nueva pila con el tamaño leído
    struct my_stack* stack = my_stack_init(size);

    //Leer datos desde el archivo y agregarlos a la pila
    void* buffer = malloc(size);
    while (read(fd, buffer, size) > 0) {
        my_stack_push(stack, buffer);
        buffer = malloc(size);
    }

    //Verificacion del cierre del fichero
    if(close(fd) == -1){
        perror("Error: ");
        return NULL;
    }

    return stack;
}