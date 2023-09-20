#include "minishell.h"

void	ft_debug_pre_while(t_master *master)
{
	if (DEBUG == FALSE)
		return ;
	printf(YELLOW "===============" RED " EJECUCION " YELLOW "===================\n" RESET);
	printf("NUM PIPES == (%i)\n", master->num_pipes);
	printf("NUM CMDS == (%i)\n", master->num_cmds);
}

void	ft_debug_post_while(t_master *master)
{
	(void)master;
	if (DEBUG == FALSE)
		return ;
	printf(YELLOW "==================== " RED "END" YELLOW" ====================\n" RESET);
}

void	ft_debug(t_master *master, t_data *list)
{
	t_data *temp;
	t_down *aux;
	//int x;
	(void)list;
	if (DEBUG == FALSE)
		return ;
	print(YELLOW "===============" RED " DETALLESS " YELLOW "===================\n" RESET "MASTER STR == (" RED "%s" RESET "), CMDS == (" RED "%i" RESET ")\n" RESET, master->str, master->num_cmds);
	temp = master->list;
	while (temp != NULL) {
		//x = 0;
		if (temp->cmd) {
			printf("COMANDO     == (" RED "%s" RESET ")", temp->cmd);
		} else if (temp->type == 2)
			print("REDIRECCION == (" YELLOW ">" RESET ")");
		else if (temp->type == 3)
			print("REDIRECCION == (" YELLOW "<" RESET ")");
		else if (temp->type == 4)
			print("REDIRECCION == (" YELLOW ">>" RESET ")");
		else if (temp->type == 5)
			print("REDIRECCION == (" YELLOW "<<" RESET ")");

		if (temp->down) {
			aux = temp->down;
		}
		if (temp->type == 1)
			print("PIPE");
		else if (temp->type == 0 || temp->type == BUILTIN) {
			if (temp->num_args > 0)
				printf(" ---> ");
			while (aux && aux != NULL && temp->num_args != 0) {
				printf("(%s) ", aux->arg);
				aux = aux->next;
				//x++;
			}
			printf("\n");
		}
		temp = temp->next;
	}
	print(YELLOW "=============================================\n" RESET);
}

