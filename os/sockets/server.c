/*
 * server.c
 * derived from Advanced Programming in the UNIX Environment, 3rd Edition
 *
 * Eric McGregor 02/27/15
 */

#include <sys/types.h>	
#include <netdb.h>
#include <sys/socket.h> 
#include <stdio.h>	
#include <stdlib.h> 
#include <unistd.h>	
#include <arpa/inet.h>  
#include <string.h>	
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <errno.h>

#define QLEN 128

#ifndef HOST_NAME_MAX 
	#define HOST_NAME_MAX 256 
#endif

extern int errno;

void print_ip_addresses(struct addrinfo *ai);
void print_error(char *);

int main(int argc, char *argv[]) 
{
	char *host_name = malloc(HOST_NAME_MAX);
	memset(host_name, 0, HOST_NAME_MAX);

	if (gethostname(host_name, HOST_NAME_MAX) < 0) {
		print_error("gethostname error");
		return(-1);
	}

	printf("host name: %s\n", host_name);

	struct addrinfo 	*host_ai;
	struct addrinfo 	hint;

	hint.ai_flags = 0;
    hint.ai_family = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = 0;
    hint.ai_addrlen = 0;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;

	int err;
    if ((err = getaddrinfo(host_name, "tokenserver", &hint, &host_ai)) != 0) {
        printf("getaddrinfo error: %s\n", gai_strerror(err));
        return 0;
    }

	print_ip_addresses(host_ai);

   	int host_fd;
	if ((host_fd = socket(host_ai->ai_addr->sa_family, SOCK_STREAM, 0)) < 0) {
		print_error("unable to create socket"); 
	}
	printf("socket created [%d]\n", host_fd);

    if (bind(host_fd, host_ai->ai_addr, host_ai->ai_addrlen) < 0) {
        print_error("unable to bind to socket");
    }
	printf("bind returned success\n");

	freeaddrinfo(host_ai);

    if (listen(host_fd, QLEN) < 0) {
        print_error("listen failed");
    }
	printf("listen returned success\n");

	int last_client_ip_int = 0;

	struct sockaddr client_sockaddr;
	socklen_t client_sockaddr_len = sizeof(client_sockaddr);
	int token = 0;
	
	for (;;) {

		printf("waiting for connection ...\n");
		int clfd = accept(host_fd, &client_sockaddr, &client_sockaddr_len);
		if (clfd < 0) {
			print_error("accept error");
		}
		printf("accepted connection, socket [%d]\n", clfd);

		printf("sending token [%d]...\n", token);
		int len = send(clfd, &token, 4, 0);

		if (len < 0) {
			print_error("error sending data");
		}

		token++;
		printf("sent %d bytes\n", len);
		close(clfd);
	}
 
	close(host_fd);
}

void print_ip_addresses(struct addrinfo *host_ai)
{
	struct addrinfo	*next_ai; 
	unsigned long *ipv4_addr;
	unsigned char *ipv6_addr;

	char ip_str[INET6_ADDRSTRLEN];

	for (next_ai = host_ai; next_ai != NULL; next_ai = next_ai->ai_next) {

		memset(ip_str, '\0', INET6_ADDRSTRLEN);

		if (next_ai->ai_addr->sa_family == AF_INET) {
			printf("IPv4 ");
			ipv4_addr  = (unsigned long*) &(((struct sockaddr_in*)next_ai->ai_addr)->sin_addr);
			inet_ntop(AF_INET, ipv4_addr, ip_str, sizeof(ip_str));
		}
		else {
			printf("IPv6 ");
			ipv6_addr = (unsigned char*) &(((struct sockaddr_in6*)next_ai->ai_addr)->sin6_addr);
			inet_ntop(AF_INET6, ipv6_addr, ip_str, sizeof(ip_str));
		}

		printf("IP address: %s\n", ip_str);
	}
}

void print_error(char *str) {
	printf("%s: %s\n", str, strerror(errno));
	exit(1);
}

