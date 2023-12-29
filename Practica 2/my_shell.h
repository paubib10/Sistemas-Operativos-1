//
// Created by Brouse on 13/11/2023.
//

#ifndef SHELL_MY_SHELL_H
#define SHELL_MY_SHELL_H

#include "sys/types.h"

#define SHELL_MAX_BUFFER     1024   // Longitud de la línea de comando (IN ALL)
#define SHELL_MAX_ARGS       64     // Longitud de los argumentos (IN ALL)

#define SHELL_PREFIX         "%s:%s$ "
#define SHELL_CMD_DELIMITER  " "

#define COMMAND_LINE_SIZE    1024

#define MAX_CMD_SIZE         10

#define N_JOBS 64

// Carácter de prompt
#define PROMPT '$'

/*Habria que quitar los debugs y poner cada debug en su correspondiente nivel, obviamente ya activados 
en su debido nivel, mas que nada porque se pueden imprimir debugs de otros niveles en un nivel que no toca.*/
// dummy debug variables
#define DEBUG1               0
#define DEBUG2               0
#define DEBUG3               1
#define DEBUGN4              1
#define DEBUG5               1
#define DEBUG6               1

// Text colors
#define T_BLACK "\x1b[30m"
#define T_GRAY "\x1b[38;5;244m"
#define T_RED "\x1b[38;5;196m"
#define T_GREEN "\x1b[32m"
#define T_YELLOW "\x1b[33m"
#define T_BLUE "\x1b[34m"
#define T_MAGENTA "\x1b[35m"
#define T_CYAN "\x1b[36m"
#define T_WHITE "\x1b[97m"
#define GRIS_T "\x1b[94m"

#define CREMA_T "\x1b[38;2;255;235;155m"

#define T_TEST "\x1b[37;42m"
#define T_TEST1 "\x1b[32;44m"
#define T_TEST2 "\x1b[37;44m"
#define T_TEST3 "\x1b[34;49m"

// Special symbols
#define RESET "\033[0m"
#define NEGRITA "\x1b[1m"

typedef char job_status;    // ‘N’: None
                            // ‘E’: Executing
                            // ‘D’: Stopped
                            // ‘F’: Ended
struct info_job {
    pid_t pid;                   // Job process id
    job_status status;           // Job status
    char cmd[COMMAND_LINE_SIZE]; // Associated command line
};

/**
 * Print the SHELL_PREFIX, then, read a
 * buffer from the buffer and return the pointer to
 * it start.
 * @note The max size of the buffer is defined by
 * SHELL_MAX_BUFFER
 *
 * @param buffer buffer where to store the buffer
 * @return the buffer start pointer
 */
char* read_line(char* buffer);

/**
 * Execute a non internal command
 *
 * @param buffer shell line buffer
 * @return ????
 */
int execute_line(char *line);

/**
 * Parse the command args and split it by the delimiter
 * ' '.
 * @note The command will have a max of SHELL_MAX_ARGS
 * size.
 *
 * @param args shell args buffer
 * @param buffer shell buffer
 * @return the args size
 */
int parse_args(char** args, char* buffer);

/**
 * Exit from the console
 *
 * @return the command result status
 */
int internal_exit();

/**
 * Check if the command is an internal command.
 *
 * @param args shell args buffer
 * @return if the command is internal command
 */
int check_internal(char** args);

/**
 * Move the pwd to the specified by the args. It has
 * 3 cases:
 * - 0 args: Move to HOME
 * - 1 args: Move to arg[1]
 * - 2 args: Move to args[1..n] It must start and end by \' or \"
 *           or eac black space must be preceded by \
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_cd(char **args);

/**
 * Export the enviorment variable
 * @use export [key]=[value]
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_export(char **args);

/**
 * Execute the source command
 * @use source [file]
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_source(char **args);

/**
 * Execute the jobs command
 * @use jobs
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_jobs();

/**
 * Execute the fg command
 * @use fg [job]
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_fg(char **args);

/**
 * Execute the bg command
 * @use bg [job]
 *
 * @param args command args with the command name
 * @return 0 if success otherwise -1
 */
int internal_bg(char **args);


// Jobs.h
/**
 * Create a new job associating only the pid
 *
 * @param name
 */
struct info_job* createJob(pid_t pid);

/**
 *
 * @param pid
 * @param state
 * @param cmd
 * @return
 */
int jobs_list_add(pid_t pid, char state, char *cmd);

/**
 *
 * @param pid
 * @return
 */
int jobs_list_find(pid_t pid);

/**
 *
 * @param pos
 * @return
 */
int jobs_list_remove(int pos);

/**
 *
 * @param args
 * @return
 */
int is_background(char** args);

// Signal handlers
/**
 * Reaper function to handle the zombie processes
 *
 * @param signum signal to handle
 */
void reaper(int signum);

/**
 * Ctrl+C handler.
 *
 * @param signum signal to handle
 */
void ctrlc(int signum);

/**
 * Ctrl+Z handler.
 *
 * @param signum signal to handle
 */
void ctrlz(int signum);

int is_output_redirection(char **args);

void procesar_token(char *dest, const char *src);

#endif //SHELL_MY_SHELL_H
