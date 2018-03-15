#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int GET(const char *str) {
  int sockfd;
  struct sockaddr_in addr;
  char buf[1024];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1) {
    fprintf(stderr, "Socket Failed\n");
    return 1;
  }
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9817);
  addr.sin_addr.s_addr = inet_addr(str);

  if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    fprintf(stderr, "Connection Failed\n");
    return 1;
  }

  sprintf(buf, "GET /%s\n");
  write(sockfd, buf, strlen(buf));
  while(1) {
    if(read(sockfd, buf, 1024) == 0) {
      break;
    }
    printf("%s\n", buf);
  }
  return 0;
}

int main(int argc, const char *argv[]) {
  if(argc == 3) {
    if(strcmp("-G", argv[1]) == 0) {
      printf("GET URL: %s\n", argv[2]);
      GET(argv[2]);
      return 0;
    }
    else if(strcmp("-P", argv[1]) == 0) {
      printf("POST URL: %s\n", argv[2]);
      return 0;
    }
  }
  fprintf(stderr, "plz -G URL or -P URL\n");
  return 1;
}
