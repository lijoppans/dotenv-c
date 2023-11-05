#ifndef DOTENV_DOTENV_H
#define DOTENV_DOTENV_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @param path Can be a directory containing a file named .env, or the path of the env file itself
 * @param overwrite Existing variables will be overwritten
 * @return 0 on success, -1 if can't open the file
 */
int env_load(const char* path, bool overwrite);

/**
 * @param path Can be a directory containing a file named .env, or the path of the env file itself
 * @param name The name of the variable to get
 * @return NULL if the variable is not found, or the value of the variable
 */
char * env_get_from_file(const char *path, const char *name);

#ifdef __cplusplus
}
#endif

#endif
