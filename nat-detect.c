#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "nat.h"

#define DEFAULT_STUN_HOST "stun.qqlive.qq.com"
#define DEFAULT_STUN_PORT 3478

void usage(char *name) {
	printf("%s STUN_HOST STUN_PORT\n", name);
}

int main(int argc, char *argv[]) {
	char stun_host[1024];
	unsigned short stun_port;

	juice_set_log_level(JUICE_LOG_LEVEL_WARN);

	if (argc == 1) {
		strcpy(stun_host, DEFAULT_STUN_HOST);
		stun_port = DEFAULT_STUN_PORT;
	}
	else if (argc == 3) {
		strcpy(stun_host, argv[1]);
		stun_port = (unsigned short)atoi(argv[2]);
	}
	else {
		usage(argv[0]);
		exit(1);
	}

	addr_record_t mapped_addr;
	juice_nat_type_t nat_type = juice_nat_detect(stun_host, stun_port, &mapped_addr);

	struct sockaddr_in *addr = (struct sockaddr_in *)&mapped_addr.addr;
	printf("Nat Type: %s\n", juice_nat_type_name(nat_type));
	printf("Mapped Address: %s:%d\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));  

	return 0;
}
