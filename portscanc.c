#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

/*
(int domain, int type, int protocol);
int domain = protocol family. AF_INET = ipv4
int type = socket type. SOCKSTEAM - tcp,  SOCK_DGRAM - udp
int protocol = 0 is mostly used because its "automatic"
*/

void error_msg()
{
	//fprintf(stderr,"Failed to initialize scan. Please verify that the parameters are entered correctly.\n");
	printf("\nUsage:\n");
	printf(" -To scan a single port:\n");
	printf("  ./portscanc <ip> <port> \n\n");
	printf(" -Scan a range of ports:\n");
	printf("  ./portscanc <ip> <StartPort> <EndPort>\n\n");
	printf(" -Scan all the ports:\n");
	printf("  ./portscanc <ip>");
	printf("\n\n -Example: \n  ./portscanc 192.168.0.1 0 5000\n");
	exit(1);
}

// Socket que verifica se a porta ta aberta
int scan(char *ip, int p)
{
	int meu_socket;
	int conectar;

	//Instância da struct sockaddr_in chamada server.
	struct sockaddr_in server; 

	//                 (ipv4   , TCP        ,0 - automatic protocol)
	meu_socket = socket(AF_INET, SOCK_STREAM, 0); 

	// Setando a struct
	server.sin_family = AF_INET;
	server.sin_port = htons(p); // the port we're testing
	server.sin_addr.s_addr = inet_addr(ip); // ip address

	//Segundo parâm.: converte a struct sockaddr para o mesmo tipo do "server"
	conectar = connect(meu_socket, (struct sockaddr *)&server, sizeof server);
	if(conectar == 0)
	{	
		printf("Porta aberta - %i\n", p);
		close(server);
		close(conectar);
	}
	//else
	//{
	//	printf("Falhou porta %i\n", porta);
	//}
}

// Void = tipo de dado genérico, qualquer coisa.
int main(int argc, char *argv[]) 
{
	// ./portscanc <ip> <start port> <end port>
	int porta;
	char *target;
	target = argv[1];
	
	// Detects if IP has less than 7 chars.
	if (argc>1)
	{
		if(strlen(argv[1]) <7)
		{
			fprintf(stderr, "(Error): Please write a proper IP address.\n");
			error_msg();
		}
	}
//	check_valid_ip(int arg)
//	{
//		if(strlen(arg) < 7)
//			error_msg();
//		}
//	
//	}

	// Scan all ports.
	if(argc==2)
	{
		printf("Scanning all 65535 ports in %s:\n\n", target);		
		int porta_0 = 0;
		int porta_65535 = 65535;

		// Porta = 0, enquanto porta for < que (numero), porta ++ (continua a incrementar)
		for(porta=porta_0; porta<porta_65535; porta++)
		{
			scan(target, porta);		
		}
		printf("\nDone.\n");
	}

	// Scan single port.
	else if	(argc==3)
	{	
		char *porta_string;
		porta_string = argv[2];
		int porta = atoi(porta_string);

		printf("Scanning port %d in %s\n",porta, target);		
		scan(target, porta);			
		printf("\nDone.\n");
	}

	// Scan range of ports.
	else if(argc==4)
	{
		char *startport;
		char *endport;
		startport = argv[2];
		endport = argv[3];
		
		int start_port = atoi(startport);
		int end_port = atoi(endport);

		// %d para imprimir variáveis tipo int. %s para string.
		printf("Scanning ports from %d to %d:\n\n", start_port, end_port);
		for(porta=start_port; porta<end_port; porta++)
		{
			scan(target, porta);
		}
		printf("\nDone.\n");
	}
	//Help/error msg.
	else
	{
		error_msg();
	}
}

