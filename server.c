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
        // printf("port number: %d\n", port);

        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(server_socket == -1) {
          fprintf(stderr, "Sever: Socket Failed\n");
          exit(1);
        }

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
          fprintf(stderr, "Sever: Bind Failed\n");
          exit(1);
        }

        if(listen(server_socket, 5) == -1) {
          fprintf(stderr, "Sever: Listen Failed\n");
          exit(1);
        }

        client_addr_size = sizeof(client_addr);
        while(1) {
          client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
          if(client_socket == -1) {
            fprintf(stderr, "Sever: Accept Failed\n");
            exit(1);
          }

          read(client_socket, buf, BUFF);
          // printf("buf: %s\n", buf);
          char *ptr;
          ptr = strtok(buf, "/");
          // printf("ptr: %s\n", ptr);
          if(strcmp(ptr, "GET ") == 0) {
            // printf("Sever: get GET\n");
            ptr = strtok(NULL, " ");
            // printf("ptr: %s\n", ptr);
            int fd = open(ptr, O_RDONLY);
            if(fd > 0) {
              char *tmp;
              ssize_t size;
              sprintf(buf, "HTTP/1.0 200 OK\r\n");
              write(client_socket, buf, strlen(buf) + 1);
              while((size = read(fd, buf, BUFF)) > 0) {
                // printf("Server: read!\n");
                // buf[size] = '\0';
                // printf("%s", buf);
                write(client_socket, buf, strlen(buf) + 1);
              }
              close(fd);
            } else {
              sprintf(buf, "HTTP/1.0 404 Not Found\r\n");
              write(client_socket, buf, strlen(buf) + 1);
            }
          } else if(strcmp(ptr, "POST ") == 0) {
            printf("Sever: get POST\n");

          } else {
            sprintf(buf, "HTTP/1.0 400 Bad Request\r\n");
            write(client_socket, buf, strlen(buf) + 1);
          }
          close(client_socket);
        }
        return 0;
      }
    }
  }

  fprintf(stderr, "Sever: plz -p (port number)\n");
  return -1;
}
