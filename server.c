//  Hello World server

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (int argc, char *argv[])
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    printf("Argument : %s \n", argv[1]);
    char p [128];
    //p = sprintf("tcp://%s:5555", argv[1]);
    snprintf(p, sizeof(p), "tcp://%s:%s", argv[1], argv[2]);
    zmq_bind (responder, p);
    //assert (rc == 1);
    
    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}
//clang -Wall server.c -o hwserver -L/usr/local/lib -lzmq