#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP 

#include "Sujeto.hpp"
#include "Cuarto.hpp"
#include "Cliente.hpp"

//Librerias basicas 
#include <string>
#include <vector>
#include <algorithm>

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


    public: 
     
     /**
     * @brief Servidor; constructor de la clase servidor
     * @param Sin parametros 
     * @return Sin return 
     */
     Servidor(): {
          
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
    
     /**
     * @brief ~Servidor; destructor de la clase Servidor 
     * @param Sin parametros 
     * @return Sin return 
     */
     ~Servidor() = default;

     /**
     * @brief existeElUsuario; permite saber si el usuario esta en la lista del servidor
     * @param el nombre del usuario
     * @return booleano 
     */
     bool existeElUsuario()
     
     /**
     * @brief respuesta; es parte del la interface(Sujeto) manda la respuesta a los usuarios 
     * @param Sin parametros. 
     * @return Sin retorno. 
     */
     std::string respuesta() override; 

     /**
     * @brief verExisUsuario; Verifica si ya hay un usuario con ese nombre. 
     * @param El nombre del usuario 
     * @return string con formato json 
     */
     bool verExisUsuario(std::String nombre);
     
     /**
     * @brief nuevoUsuario; avisa a los demas de un nuevo usuario y maneja las conexiones 
     * @param sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoUsuario(); 

     /**
     * @brief nuevoStatus; modifica el status  
     * @param Sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoStatus();
     
     /**
     * @brief usuariosList; manda la lista de usuarios conectados al servidor.   
     * @param sin parametros
     * @return  string de tipo json 
     */
     std::string usuariosList(); 

     /**
     * @brief mandarMensaje; manda un mensaje a cierta persona 
     * @param El cliente a mandar mensaje y el mensaej 
     * @return string de tipo json 
     */
     std::string mandarMensaje(std::string msg, Cliente nombre);

     /**
     * @brief mandarMensajePublico; manda un mensaje a todos los usuarios conectados 
     * @param No hay 
     * @return string de tipo json 
     */
     std::string mandarMensajePublico(std::string msg); 

     /**
     * @brief seUnioCuarto; une un cliente a cierto cuarto  
     * @param El cliente a agregar, nombre del cuarto 
     * @return un string de tipo json 
     */
     std::string seUnioCuarto(Cliente usuario, Cuarto nombreCuarto); 

     /**
     * @brief listaUsuariosCuarto; retorna la lista de usuarios en el cuarto
     * @param el nombre del cuarto
     * @return un string de tipo json
     */
     std::string listaUsuariosCuarto(std::string nombreCuarto); 

     /**
     * @brief abandonarCuarto; saca a una persona del cuarto e informa.  
     * @param El cliente a sacar
     * @return un string de tipo json
     */
     std::string abandonarCuarto(Cliente usuario); 
     /**
     * @brief desconectado; desconecta al usuario del servidor
     * @param El cliente a desconectar
     * @return un string de tipo json
     */
     std::string desconectado(Cliente usuario);  

}

#endif //SERVIDOR_HPP