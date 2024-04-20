#include <unistd.h>
#include <string.h>  // For strlen - replace with libft later
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h> // (remember to compile with -lreadline)
#include <signal.h>

volatile sig_atomic_t	exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT || sig == SIGHUP || sig == SIGTERM)
		exit_flag = 1;
	else if (sig == SIGINT)
		write(1, "\nhandle signal interrupt\n", 25);
}

int main(void)
{
	char	*input;

	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGTERM, handle_signal);
	while (!exit_flag)
	{
		input = readline("Input something to echo (or type 'exit' to quit): ");
		if (input == NULL || strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		write(1, input, strlen(input));
		write(1, "\n", 1);
		free(input);
	}
	return (0);
}
