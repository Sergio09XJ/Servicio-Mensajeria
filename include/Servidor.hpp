#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP 

#include "Sujeto.hpp"
#include "Cuarto.hpp"
#include "Cliente.hpp"

//Librerias basicas 
#include <string>
#include <vector>

//Libreria para json
#include <nlohmann/json.hpp>

//Libreria para socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Servidor : public Sujeto{

    private:

     std::vector<Clientes> listClientes; 
     std::vector<Cuarto> listCuartos; 
     int socketServidor;
     int socketClienteServ;


    public: 
   
     public(): {
          
           //Creamos el socket, A_INET indica que sera IPv4, SOCK_STREAM el flujo, TCP y 0 el protocolo para esa combinación 
           this->socketServidor = socket(AF_INET, SOCK_STREAM, 0) 
           
            // Especificamos la dirección del socket
            sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET; //Indicamos las dirección a usar  AF_INET es IPv4
            serverAddress.sin_port = htons(8080); //Indicamos el puerto a usar 
            serverAddress.sin_addr.s_addr = INADDR_ANY; //Indicamos las direciones IP a usar, que son del tipo IPv4

            // establecemos conexión con el socket del servidor. 
            bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
            //Indicamos el socket | La dirección que configuramos(IPv4) | El tamaño de la dirección. 

            //Convertimos este socket a uno de escucha 
            listen(socketServidor, 10);

            while (true) {

              // cuando un cliente hace conect accept es quien lo enlaza con el servidor. 
              int socketCliente = accept(socketServidor, nullptr, nullptr);

            
             }

     }

     ~public() = default;

     std::string respeusta() override; 

     bool verExisUsuario(std::String nombre); 

     std::string nuevoUsuario(); 
     std::string nuevoStatus(); 
     std::string usuariosList(); 

     std::string mandarMensaje(std::string msg);
     std::string mandarMensajePublico(); 
     std::string seUnioCuarto(Cliente usuario); 
     std::string listaUsuariosCuarto(std::string nombre); 

     std::string abandonarCuarto(Cliente usuario); 
     std::string desconectado(Cliente usuario);  

}

#endif //SERVIDOR_HPP