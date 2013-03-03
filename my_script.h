/*
** my_script.h for my_script in /home/ignati_i//projects/myscript-2015s-2016-2017si-ignati_i
** 
** Made by ivan ignatiev
** Login   <ignati_i@epitech.net>
** 
** Started on  Sat Mar  2 19:42:43 2013 ivan ignatiev
** Last update Sat Mar  2 20:11:31 2013 ivan ignatiev
*/

#ifndef MYSCRIPT_H_
# define MYSCRIPT_H_

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/select.h>
# include <grp.h>

# define MASTER_PATH_		"/dev/ptmx"
# define SLAVE_PATH_		"/dev/pts/%u"
# define TTY_GROUP_		"tty"
# define DEFAULT_SCRIPT_	"typescript"

struct termios	g_origin_tc;
struct termios	g_changed_tc;
struct winsize	g_ws;

int		open_master(int *master_fd);
int		get_ptsname(int master_fd, char *ptsfilename, int size);
int		prepare_slave(int master_fd, char *slave_filename);
int		open_slave(int *slave_fd, char *slave_filename);
int		login_pty(int slave_fd);
int		my_script(int master_fd, char *filename, int mode);
int		exec_current_shell();
int		my_shell(int master_fd);

#endif /* !MYSCRIPT_H_ */
