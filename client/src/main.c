#include <unistd.h>
#include <stdio.h>
#include "conection.h"
#include "comunication.h"


int main (int argc, char *argv[]){
  //Se obtiene la ip y el puerto donde está escuchando el servidor (la ip y puerto de este cliente da igual)
  char * IP = "0.0.0.0";
  int PORT = 8080;

  // Se prepara el socket
  int server_socket = prepare_socket(IP, PORT);

  // Se inicializa un loop para recibir todo tipo de paquetes y tomar una acción al respecto
  while (1){
    int msg_code = client_receive_id(server_socket);
    
    if (msg_code == 1) { //Recibimos el mensaje y escribimos una respuesta
      printf("Recibí un paquete con ID: 1\n");
      char * message = client_receive_payload(server_socket);
      printf("Mensaje recibido: %s\n", message);
      free(message);

      printf("Escribe una respuesta: ");
      char response[20];
      int pos=0;
      while (1){
        char c = getchar();
        response[pos] = c;
        if (c == '\n') break;
        pos++;
      }
      printf("Respuesta: %s\n", response);
    }

    if (msg_code == 2) { //Recibimos el mensaje y enviamos una respuesta automática
      printf("Recibí un paquete con ID: 2\n");
      char * message = client_receive_payload(server_socket);
      printf("Mensaje recibido: %s\n", message);
      free(message);

      char * response = "Respuesta automática";
      client_send_message(server_socket, response);
    }
  }
  

  // Se cierra el socket
  close(server_socket);
  free(IP);

  return 0;
}
