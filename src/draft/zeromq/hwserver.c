#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main(void) {
  void *context = zmq_ctx_new();
  void *responder = zmq_socket(context, ZMQ_REP);
  int rc = zmq_bind(responder, "tcp://*:5555");
  assert(rc == 0);

  while (1) {
    char buffer[10];
    rc = zmq_recv(responder, buffer, 10, ZMQ_DONTWAIT);
    if (rc == -1 && errno == EAGAIN) {
      printf("Received Nothing.\n");
    } else if (rc == -1 && errno == EFSM) {
      printf("States Error!\n");
    } else {
      printf("Received Hello\n");
    }
    sleep(1);
    rc = zmq_send(responder, "World", 5, 0);
    if (rc == -1 && errno == EFSM) {
      printf("States Error!\n");
    }
  }
  return 0;
}
