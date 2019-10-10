#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comunication.h"
#include "conection.h"

int main (int argc, char *argv[]){
  // Se define una IP y un puerto
  char * IP = "0.0.0.0";
  int PORT = 8080;

  // Se crea el servidor y se obtiene al cliente
  int client_socket = prepare_sockets_and_get_clients(IP, PORT);
  
  // Le enviamos al cliente un mensaje de bienvenida
  char * welcome = "Bienvenido!!";
  server_send_message(client_socket, welcome);

  while (1){
    // Se obtiene el paquete del cliente
    int msg_code = server_receive_id(client_socket);
    printf("msgcode:%d\n", msg_code);

    if (msg_code == 3){
      char * client_message = server_receive_payload(client_socket);
      printf("El cliente dice: %s\n", client_message);
      // Damos vuelta el mensaje y lo enviamos de vuelta
      int len = strlen(client_message);
      char response[len];
      for (int i=1; i<=len; i++){
        response[len-i] = client_message[i-1];
      }
      server_send_message(client_socket, response);
    }
  }

  return 0;
}
