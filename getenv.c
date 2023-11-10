#include "shell.h"
/**
 * get_environ - Returns a copy of the environment variables
 * @info: structure containing potential arguements. 
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;

	}
	return (info->environ);
}

/**
 * unset_environment - Remove an environment variable
 * @info: structure containing potential arguements. 
 * @var: The environment variable to remove
 * Return: 1 on success, 0 otherwise
 */
int unset_environment(info_t *info, char *var)
{
	list_t *current= info->env;
	size_t index = 0;
	char *ptr;

	if (!current || !var)
		return (0);

	while (current) {
	
		ptr = starts_with(current->str, var);
		if (ptr && *ptr == '=') {
		
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			current = info->env;
			continue;
		}
		current = current->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * set_environment - Initialize a new environment variable or modify an existing one.
 * @info: structure containing potential arguements.
 * @var: The environment variable to set 
 * @value: The value for the environment variable.
 * Return: Always 0
 */
int set_environment(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *current
	char *ptr;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	current = info->env;
	while (current) {
	
		ptr = starts_with(current->str, var);
		if (ptr && *ptr == '=') {
		
			free(current->str);
			current->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		current = current->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
