#include <unistd.h>
#include <string.h>  // For strlen - replace with libft later
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h> // (remember to compile with -lreadline)

int main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Input something to echo (or type 'exit' to quit): ");
		if (strcmp(input, "exit") == 0)
			break;
		add_history(input);
		write(STDOUT_FILENO, input, strlen(input));
		write(STDOUT_FILENO, "\n", 1);
		free(input);
	}

	return 0;
}
