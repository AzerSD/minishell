#include <stdio.h>

int	main(void)
{
	char	buffer[256];

	printf("Please enter some text: ");
	while (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		printf("You entered: %s", buffer);
		printf("Please enter some text: ");
	}
	printf("\nEOF detected. Exiting program.\n");
	return (0);
}
