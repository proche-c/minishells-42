/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkspipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:34:36 by vaguilar          #+#    #+#             */
/*   Updated: 2022/05/11 11:39:52 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf
#include <unistd.h> //fork, getcwd
#include <sys/wait.h> //wait
#include <stdlib.h> //malloc
#include <sys/stat.h> //stat
#include <string.h> //strerror

int	main(int argc, char **argv, char **envp) //envp - lista de variables de entorno
{
	int		fd[2]; //Se crea para poder crear el pipe
	char	buffer[500];
	pid_t	pid;
	int		pid2;
	int		test;
	
	struct stat buf;
	int result = 0;
	char *file_name = "test.txt";


	//printf("\033[H\033[J"); //Limpiar pantalla

	/*	PID & FORKS	*/
	// pipe(fd);
	// pid2 = getpid();
	// pid = fork();	
	// if (pid == -1)
	// 	printf("ERROR\n");
	// else if (pid == 0) //Estoy en el proceso hijo
	// {
	// 	pid2 = getpid();
	// 	printf("SOY EL HIJO, PID == (%i), PID 2 == (%i)\n", pid, pid2);
	// 	chdir(".."); // Cambio la direccion en el proceso hijo, retorna 0 si la funcion ha sido exitoso
	// 	printf("SOY EL HIJO Y ESTOY EN LA DIRECCION == (%s)\n\n", getcwd(buffer, -1));
	// 	return (0);
	// }
	// else //Estoy en el proceso padre
	// {
	// 	wait(0); //Suspende  la  ejecución del proceso actual hasta que un proceso hijo ha terminado.
	// 	//waitpid(0, 0, 0); //Suspende  la  ejecución del proceso actual hasta que un el proceso PID ha terminado
	// 	printf("SOY EL PADRE, PID == (%i), PID 2 == (%i)\n", pid, pid2);
	// 	printf("SOY EL PADRE ESTOY EN LA DIRECCION == (%s)\n", getcwd(buffer, -1));
	// }
	/*	END PID & FORKS	*/
	// printf("=====================================================\n\n");



	/*	LS	*/
	printf("EJECUCION DE LS\n");
	execve("/bin/ls", argv, envp);
	/*	END LS	*/

	

	/*	STAT	*/
	// result = stat(file_name, &buf);
	// if (result != 0)
	// {
	// 		printf("Error");
	// 		exit(1);
	// }
	// else
	// {
	// 	printf("mode_t st_mode == (%i)\n", buf.st_mode); /* File type & mode (permissions) */
	// 	printf("ino_t st_ino == (%llu)\n", buf.st_ino); /* I-node number (serial number) */
	// 	printf("dev_t st_dev == (%i)\n", buf.st_dev); /* device number (file system) */
	// 	printf("dev_t st_rdev == (%i)\n", buf.st_rdev); /* device number for special file */
	// 	printf("nlink_t st_nlink == (%i)\n", buf.st_nlink); /* number of links */
	// 	printf("uid_t st_uid == (%i)\n", buf.st_uid); /* Owner's user id */
	// 	printf("gid_t st_gid == (%i)\n", buf.st_gid); /* owner's group id */
	// 	printf("off_t st_size = [%lld]\n", buf.st_size); 
	// 	printf("time_t st_atime == (%li)\n", buf.st_atime); /* last access */
	// 	printf("time_t st_mtime == (%li)\n", buf.st_mtime); /* last variant */
	// 	printf("time_t st_ctime == (%li)\n", buf.st_ctime); /* Last file state change */
	// 	printf("long st_blksize == (%i)\n", buf.st_blksize); /* The most suitable I/O block size */
	// 	printf("long st_blocks == (%i)\n", buf.st_mode); /* Number of 512-byte blocks */
	// }
	/*	The main reason to use the stat function is the ls -l command, which needs to know all the information in the file. source	*/



	/*	MENSAJES DE ERRORES	*/
	// int     x;
    // char    *error_message;

	// x = 0;
	// while (x < 108)
	// {
	// 	error_message = strerror(x);
    //     printf("#%d. (%s)\n", x, error_message);
	// 	x++;
	// }
	/*	END MENSAJES DE ERRORES	*/


	return (0);
}

void	ft_cc(int num)
{
	printf("CONTROL + C, %i\n", num);
	return ;
}

void	ft_cr(int num)
{
	printf("CONTROL + \\, %i\n", num);
}

void	ft_signals(void)
{
	signal(SIGINT, &ft_cc);
	signal (SIGQUIT, &ft_cr);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;
	char	*prog_path = "/bin/ls";
	char *const args[] = {"ls", "-la","/bin", 0};

	execve(prog_path, args, envp);
	ft_signals();
	while (argc && argv && envp)
	{
		//str = readline(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
		if (str == NULL)
   			exit(0);
	}

	return(0);
}
