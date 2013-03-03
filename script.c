/*
** script.c for my_script in /home/ignati_i//projects/myscript-2015s-2016-2017si-ignati_i
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sat Mar  2 19:57:18 2013 ivan ignatiev
** Last update Sat Mar  2 20:50:13 2013 ivan ignatiev
*/

#include	"my_script.h"

static int	init_select(int master_fd, fd_set *fdsin)
{
  FD_ZERO(fdsin);
  FD_SET(STDIN_FILENO, fdsin);
  FD_SET(master_fd, fdsin);
  if (select(master_fd + 1, fdsin, NULL, NULL, NULL) < 0)
    return (0);
  return (1);
}

static int	logme(int master_fd, int script_fd)
{
  char		buffer[255];
  int		size;
  fd_set	fdsin;

  if (!init_select(master_fd, &fdsin))
    return (0);
  if (FD_ISSET(STDIN_FILENO, &fdsin))
    {
      if ((size = read(STDIN_FILENO, buffer, 255)) > 0)
	write(master_fd, buffer, size);
      else
	return (1);
    }
  if (FD_ISSET(master_fd, &fdsin))
    {
      if ((size = read(master_fd, buffer, 255)) > 0)
	{
	  write(STDOUT_FILENO, buffer, size);
	  write(script_fd, buffer, size);
	}
      else
	return (1);
    }
  return (-1);
}

int		my_script(int master_fd, char *filename, int mode)
{
  int		script_fd;
  int		result;

  if ((script_fd = open(filename,
			O_WRONLY | O_CREAT | mode,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
      fprintf(stderr, "Can't open script file : %s\n", strerror(errno));
      return (0);
    }
  printf("Script started, file is %s\n", filename);
  while ((result = logme(master_fd, script_fd)) == -1);
  close(script_fd);
  printf("Script done, file is %s\n", filename);
  return (result);
}
