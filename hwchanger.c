#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

extern int errno;

unsigned short int rand_get()
{
	return (unsigned short int)(rand() % 16);
}

void set_addr(unsigned short int octets[])
{
	//PROBLEMS WITH FGETS NEWLINE
	char change_command[64];
	char device[8];
	printf("Device to change:\n");
	fgets(device, 8, stdin);
	snprintf(change_command, 64, "%s %s %s %.2x:%.2x:%.2x:%.2x:%.2x:%.2x", "ifconfig", device, "hw ether", octets[0], octets[1], octets[2], octets[3], octets[4], octets[5]);
	printf("\nCommand: %s", change_command);
	system("ifconfig wlp3s0 down");
	if(system(change_command) == -1)
		perror("\n[Error] Could not change your MAC address");
	else
		printf("\n[Ok]");
	printf("\n[Error no.] %d", errno);
	system("ifconfig wlp3s0 up");
	return;
}

void new_addr(char* addr[])
{
	time_t t;
	srand((unsigned)time(&t));
	unsigned short int octets[6];

	octets[0] = rand_get();
	octets[1] = rand_get();
	octets[2] = rand_get();
	octets[3] = rand_get();
	octets[4] = rand_get();
	octets[5] = rand_get();

	set_addr(octets);
	return;
}

int main(void)
{
	printf("[Message]Oscars MAC/Hardware Address Changer <2020> Do as you wish.. Its free code\nWARNING! This program will change your MAC address. Some interfaces may set the IG bit to 1\n");
	char* addr[6];
	new_addr(addr);
	return 0;
}
