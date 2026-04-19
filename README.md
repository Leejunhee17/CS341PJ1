# CS341PJ1 - Computer Networks: Socket Programming

KAIST CS341 컴퓨터 네트워크 수업 프로젝트 — TCP 소켓 기반 클라이언트-서버 구현 (C)

## 구성

| 파일 | 역할 |
|------|------|
| `server.c` / `server.h` | 클라이언트 연결 수락, 데이터 처리, 응답 전송 |
| `client.c` / `client.h` | 서버 연결, 데이터 송수신 |

## 빌드 및 실행

```bash
make

# 서버
./server -p <port>

# 클라이언트
./client -h <host> -p <port>
```

## 주요 기능

- TCP 소켓 기반 연결 (IPv4, SOCK_STREAM)
- 입력 유효성 검사 및 에러 핸들링
- 연결 관리 및 데이터 버퍼링
