#include "main.h"

/**
 * free_mem_exec - support execute process by freeing memory
 * @arr_token: array of strings that contains the commands and arguments
 * @index_ptr: pointer to the index of arr_token
 * @flag_command: flag to clear memory for command_path
 * @command_path: string potentially containing the full path of the command
 * Return: void
 */
void free_mem_exec(char **arr_token, int *index_ptr, int flag_command,
				   char *command_path)
{
	free_mem(index_ptr, arr_token);
	if (!flag_command)
		free(command_path);
}
