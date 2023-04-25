#include "shell.h"



/**
 *
 *
 *
 *
 *
 *
 */



int is_chain(info_t *info, char *buff, size_t *ptr)
{
	size_t m = *ptr;

	if (buff[m] == '|' && buff[m + 1] == '|')
	{
		buff[m] = 0;
		m++;
		info->cmd_buff_type == CMD_OR;
	}
	else if (buff[m] == '&' && buff[j + 1] == '&')
	{
		buff[m] = 0;
		m++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[m] == ';')
	{
		buff[m] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = m;
	return (1);
}



/**
 *
 *
 *
 *
 *
 *
 *
 */




void check_chain(info_t *info, char *buff, size_t *ptr, size_t i, size_t len)
{
	size_t m;

	m = *ptr;

	if (inf0->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			m = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (info->status == 0)
		{
			buff[i] = 0;
			m = len;
		}
	}
	*ptr = m;
}













































