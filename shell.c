/*
** shell.c for my_script in /home/ignati_i//projects/myscript-2015s-2016-2017si-ignati_i
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sat Mar  2 19:56:18 2013 ivan ignatiev
** Last update Sat Mar  2 20:53:28 2013 ivan ignatiev
*/

#include	"my_script.h"

int		exec_current_shell()
{
  char		*current_shell;

  if ((current_shell = getenv("SHELL")) == NULL)
    {
      fprintf(stderr, "shell not found : %s", strerror(errno));
      return (0);
    }
  if (execlp(current_shell, current_shell, NULL) != 0)
    {
      fprintf(stderr, "shell can not be executed : %s", strerror(errno));
      return (0);
    }
  return (1);
}

int		my_shell(int master_fd)
{
  int		slave_fd;
  char		slave_filename[255];

  slave_fd = -1;
  if (setsid() == (pid_t) -1)
    {
      fprintf(stderr, "Session error : %s \n", strerror(errno));
      return (0);
    }
  if (get_ptsname(master_fd, slave_filename, 255))
    {
      if (prepare_slave(master_fd, slave_filename))
	if (open_slave(&slave_fd, slave_filename))
	  if (login_pty(slave_fd))
	    if (exec_current_shell())
	      {
		close(slave_fd);
		return (1);
	      }
    }
  if (slave_fd >= 0)
    close(slave_fd);
  return (0);
}
