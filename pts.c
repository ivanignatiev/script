/*
** pts.c for my_script in /home/ignati_i//projects/myscript-2015s-2016-2017si-ignati_i
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sat Mar  2 19:49:38 2013 ivan ignatiev
** Last update Sat Mar  2 20:52:25 2013 ivan ignatiev
*/

#include	"my_script.h"

int		open_master(int *master_fd)
{
  if ((*master_fd = open(MASTER_PATH_, O_RDWR | O_NOCTTY)) < 0)
    {
      fprintf(stderr, "Master open error : %s\n", strerror(errno));
      return (0);
    }
  return (1);
}

int		get_ptsname(int master_fd, char *ptsfilename, int size)
{
  unsigned int	slave_number;

  if (ioctl(master_fd, TIOCGPTN, &slave_number) != 0)
    {
      fprintf(stderr, "Slave number not found : %s\n", strerror(errno));
      return (0);
    }
  if (snprintf(ptsfilename, size, SLAVE_PATH_, slave_number) >= size)
    return (0);
  return (1);
}

int		prepare_slave(int master_fd, char *slave_filename)
{
  struct group	*tty_group;
  int		unlock;

  if (chmod(slave_filename, S_IWUSR | S_IRUSR | S_IWGRP) != 0)
    {
      fprintf(stderr, "Problem with chmod : %s", strerror(errno));
      return (0);
    }
  if ((tty_group = getgrnam(TTY_GROUP_)) == NULL)
    {
      fprintf(stderr, "Tty group not found : %s\n", strerror(errno));
      return (0);
  }
  if (chown(slave_filename, getuid(), tty_group->gr_gid) != 0)
    {
      fprintf(stderr, "Problem with chown : %s\n", strerror(errno));
      return (0);
    }
  unlock = 0;
  if (ioctl(master_fd, TIOCSPTLCK, &unlock) != 0)
    {
      fprintf(stderr, "Can't unlockpt : %s\n", strerror(errno));
      return (0);
    }
  return (1);
}

int		open_slave(int *slave_fd, char *slave_filename)
{
  int		ctty;

  if ((*slave_fd = open(slave_filename, O_RDWR | O_NOCTTY)) < 0)
    {
      fprintf(stderr, "Slave (%s) open error : %s\n", slave_filename,
	      strerror(errno));
      return (0);
    }
  ctty = 1;
  if (ioctl(*slave_fd, TIOCSCTTY, &ctty) != 0)
    {
      fprintf(stderr, "Slave can't control tty : %s\n",
	      strerror(errno));
      return (0);
    }
  if (tcsetattr(*slave_fd, 0, &g_origin_tc) != 0)
    {
      fprintf(stderr, "Error with slave : %s\n", strerror(errno));
      return (0);
    }
  return (1);
}

int		login_pty(int slave_fd)
{
  if (dup2(slave_fd, STDERR_FILENO) < 0)
    return (0);
  if (dup2(slave_fd, STDOUT_FILENO) < 0)
    return (0);
  if (dup2(slave_fd, STDIN_FILENO) < 0)
    return (0);
  return (1);
}
