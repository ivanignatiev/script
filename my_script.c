/*
** my_script.c for myscript-2015s-2016-2017si-ignati_i in /home/ignati_i/projects/myscript-2015s-2016-2017si-ignati_i
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sat Mar 02 14:18:54 2013 ivan ignatiev
** Last update Sat Mar  2 20:21:18 2013 ivan ignatiev
*/

#include	"my_script.h"

int		fork_pty(int master_fd, char *filename, int mode)
{
  int		pid;

  pid = fork();
  if (pid < 0)
    {
      fprintf(stderr, "Can't fork process : %s\n" , strerror(errno));
      return (0);
    }
  if (pid == 0)
    {
      if (my_shell(master_fd))
	{
	  close(master_fd);
	  exit(EXIT_SUCCESS);
	}
      close(master_fd);
      exit(EXIT_FAILURE);
    }
  else
    {
      if (my_script(master_fd, filename, mode))
	  return (1);
    }
  return (0);
}

int		prepare_tcattr()
{
  if (tcgetattr(STDIN_FILENO, &g_origin_tc) != 0)
    {
      fprintf(stderr, "Problem with tcgetattr : %s\n", strerror(errno));
      return (0);
    }
  g_changed_tc = g_origin_tc;
  g_changed_tc.c_lflag &= ~ECHO;
  g_changed_tc.c_lflag &= ~ICANON;
  g_changed_tc.c_cc[VMIN] = 1;
  g_changed_tc.c_cc[VTIME] = 3;
  if (tcsetattr(STDIN_FILENO, 0, &g_changed_tc) != 0)
    {
      fprintf(stderr, "Problem with tcsetattr : %s\n", strerror(errno));
      return (0);
  }
  return (1);
}

int		reset_settings()
{
  if (tcsetattr(STDIN_FILENO, 0, &g_origin_tc) != 0)
    {
      fprintf(stderr, "Problem with reset setting: %s\n", strerror(errno));
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		prepare_options(int argc, char **argv, int *options)
{
  int		i;
  i = 1;
  options[0] = -1;
  options[1] = O_TRUNC;
  while (i < argc)
    {
      if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--append") == 0)
	options[1] = O_APPEND;
      else
	options[0] = i;
      ++i;
    }
  return (1);
}

int		main(int argc, char **argv)
{
    int		master_fd;
    int		opt[2];

    if (prepare_options(argc, argv, opt))
      {
	if (prepare_tcattr())
	  {
	    if (open_master(&master_fd))
	      {
		if (fork_pty(master_fd,
			     (opt[0] == -1 ? DEFAULT_SCRIPT_ : argv[opt[0]]),
			     opt[1]))
		  {
		    close(master_fd);
		    return (reset_settings());
		  }
		close(master_fd);
	      }
	    reset_settings();
	  }
      }
    return (EXIT_FAILURE);
}
