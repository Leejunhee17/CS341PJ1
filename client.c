#include "client.h"

int main(int argc, const char *argv[]) {
  char *ptr = malloc(sizeof(char) * strlen(argv[2]));
  char *host;
  struct hostent *h;
  char *ip;
  int port;
  char *url;

  if(argc == 3) {
    strcpy(ptr, argv[2]);
    host = strtok(ptr, ":");
    // printf("host: %s\n", host);
    if ((h = gethostbyname(host)) == NULL) {
      fprintf(stderr, "Host?\n");
      return -1;
    }
    ip = inet_ntoa(*((struct in_addr *)h->h_addr));
    // printf("ip: %s\n", ip);
    port = atoi(strtok(NULL, "/"));
    // printf("port: %d\n", port);
    url = strtok(NULL, " ");
    if(!url) {
      url = "";
    }
    // printf("url: %s\n", url);

    if(strcmp("-g", argv[1]) == 0) {
      // printf("GET\n");
      int sockfd;
      struct sockaddr_in addr;
      char buf[BUFF];

      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if(sockfd == -1) {
        fprintf(stderr, "Client: Socket Failed\n");
        return -1;
      }
      memset(&addr, 0, sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip);

      if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Client: Connection Failed\n");
        return -1;
      }
      printf("Client: Connection Success\n");

      sprintf(buf, "GET /%s HTTP/1.0\r\nHost: %s\r\n\r\n", url, host);
      write(sockfd, buf, strlen(buf));
      read(sockfd, buf, BUFF);
      printf("%s", buf);
      close(sockfd);
      return 0;
    }
    else if(strcmp("-p", argv[1]) == 0) {
      // printf("POST\n");
      char c;
      int conlen = 0;
      char *input;
      while((c = fgetc(stdin)) != EOF) {
        conlen = strlen(input);
        input[conlen] = c;
        input[conlen + 1] = '\0';
      }
      fflush(stdin);
      printf("Client: conlen: %d\n", conlen);
      printf("Client: input: %s\n", input);


      int sockfd;
      struct sockaddr_in addr;
      char buf[BUFF];

      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if(sockfd == -1) {
        fprintf(stderr, "Client: Socket Failed\n");
        return -1;
      }
      memset(&addr, 0, sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      addr.sin_addr.s_addr = inet_addr(ip);

      if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Client: Connection Failed\n");
        return -1;
      }
      printf("Client: Connection Success\n");

      sprintf(buf, "POST /%s HTTP/1.0\r\nHost: %s\r\nContent-Length: %d\r\n\r\n%s", url, host, conlen + 1, input);
      write(sockfd, buf, strlen(buf));
      read(sockfd, buf, BUFF);
      printf("%s\n", buf);
      close(sockfd);
      return 0;
    }
  }
  fprintf(stderr, "Client: plz -g xxx or -p xxx\n");
  return -1;
}
