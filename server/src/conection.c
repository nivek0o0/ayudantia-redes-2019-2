#include "conection.h"

int prepare_sockets_and_get_clients(char * IP, int port){
  // Se definen las estructuras para el socket del servidor
  struct sockaddr_in server_addr;

  // Se definen las estructuras para el socket de los clientes
  struct sockaddr_in client1_addr;
  socklen_t addr_size = sizeof(client1_addr);;

  // Se crea el socket del servidor
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Se guardan puerto e IP
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_aton(IP, &server_addr.sin_addr);

  // Se configura el socket a gusto (recomiendo fuertemente el REUSEPORT!)
  int opt = 1;
  int ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

  // Se le asigna al socket del servidor un puerto y una IP donde escuchar
  int ret2 = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Se escuchan conexiones entrantes
  int ret3 = listen(server_socket, 1);

  // Se acepta al primer cliente que llegue
  int client1_socket = accept(server_socket, (struct sockaddr *)&client1_addr, &addr_size);

  return client1_socket;
}
