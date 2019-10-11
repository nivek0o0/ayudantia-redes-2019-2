#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comunication.h"
#include "conection.h"

char * revert(char * message){
  int len = strlen(message);
  char * response = malloc(len);
  
  for (int i = 0; i < len; i++)
  {
    printf("char: %c\n", message[len-1-i]);
    response[i] = message[len-1-i];
  }
  response[len-1] = '\0';

  return response;
}

int main(int argc, char *argv[])
  // Se define una IP y un puerto
  char *IP = "0.0.0.0";
  int PORT = 8080;

  // Se crea el servidor y se obtienen los sockets de ambos clientes
  PlayersInfo * players_info = prepare_sockets_and_get_clients(IP, PORT);

  // Le enviamos al primer cliente un mensaje de bienvenida
  char * welcome = "Bienvenido Cliente 1!!";
  server_send_message(players_info->socket_c1, 1, welcome);

  while (1)
  {
    // Se obtiene el paquete del cliente 1
    int msg_code = server_receive_id(players_info->socket_c1);
    printf("msgcode:%d\n", msg_code);

    if (msg_code == 1) //El cliente me envió un mensaje a mi (servidor)
    {
      char * client_message = server_receive_payload(players_info->socket_c1);
      printf("El cliente dice: %s\n", client_message);
      
      // Le enviaremos el mismo mensaje invertido jeje
      char * response = revert(client_message);
      
      // Le enviamos la respuesta
      server_send_message(players_info->socket_c1, 1, response);
    }
    else if (msg_code == 2){ //El cliente le envía un mensaje al otro cliente
      char * client_message = server_receive_payload(players_info->socket_c1);
      printf("Servidor traspasando el mensaje: %s\n", client_message);
      server_send_message(players_info->socket_c2, 2, client_message);
    }
  }

  return 0;
}
