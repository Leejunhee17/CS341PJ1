#include "server.h"

int isdigit_str(char str[]) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if(isdigit(str[i]) == 0) {
      return 1;
    }
  }
  return 0;
}


int main(int argc, char *argv[]) {
  int port;

  int server_socket;
  int client_socket;
  int client_addr_size;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  char buf[BUFF];

  if(argc == 3) {
    if(strcmp(argv[1], "-p") == 0) {
      if(isdigit_str(argv[2]) == 0) {
        port = atoi(argv[2]);
        printf("port number: %d\n", port);

        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(server_socket == -1) {
          fprintf(stderr, "Socket Failed\n");
          exit(1);
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
          fprintf(stderr, "Bind Failed\n");
          exit(1);
        }

        if(listen(server_socket, 5) == -1) {
          fprintf(stderr, "Listen Failed\n");
          exit(1);
        }

        client_addr_size = sizeof(client_addr);
        while(1) {
          client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
          if(client_socket == -1) {
            fprintf(stderr, "Accept Failed\n");
            exit(1);
          }

          read(client_socket, buf, BUFF);

          close(client_socket);
        }
        return 0;
      }
    }
  }

  fprintf(stderr, "plz -p (port number)\n");
  return -1;
}
