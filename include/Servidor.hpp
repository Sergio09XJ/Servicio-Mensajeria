#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP 

#include "Sujeto.hpp"

//Librerias basicas 
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>
#include <sstream>

//Libreria para json
#include <nlohmann/json.hpp>

//Libreria para socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct conectClienteSocket{

  public: 
   std::string nombreCliente; 
   int socketCliente; 

   conectClienteSocket(std::string nombreCliente, int socketCliente) : 
   nombreCliente(nombreCliente), socketCliente(socketCliente) {};

  
};

class Cuarto;
class Servidor : public Sujeto{

    private:

     std::vector<std::unique_ptr<Cliente>> listClientes; 
     std::vector<std::unique_ptr<Cuarto>> listCuartos; 
     int socketServidor;
     std::mutex mtx;
     std::vector<conectClienteSocket> listaConectados; 


    public: 
     
     /**
     * @brief Servidor; constructor de la clase servidor
     * @param Sin parametros 
     * @return Sin return 
     */
     Servidor();

     /**
     * @brief ~Servidor; destructor de la clase servidor
     * @param Sin parametros 
     * @return Sin return 
     */
     ~Servidor();


      /**
     * @brief getSocket; retorna el socket del servidor
     * @param nada 
     * @return El socket del servidor
     */
     int getSocket();


     /**
     * @brief buscarNombre; se encarga de buscar el nombre en base al socket de la lista de listaConectados 
     * @param El socket de la relación socket-cliente
     * @return El nombre de la relación 
     */
     std::string buscarNombre(int socketParam);

      /**
     * @brief buscarSocket; se encarga de buscar el socket en base al nombre de la lista de listaConectados
     * @param El nombre de la relación socket-cliente
     * @return El socket de la relación. 
     */
     int buscarSocket(std::string nombre);

     /**
     * @brief devolverCliente; busca un cliente y lo devuelve en base a su nombre
     * @param El nombre del cliente
     * @return El cliente 
     */
     Cliente& devolverCliente(std::string nombre);

    /**
     * @brief devolverCuarto; busca un cuarto y lo devuelve en base a su nombre
     * @param El nombre del cuarto
     * @return El cuarto 
     */
     Cliente& devolverCuarto(std::string nombre);

     /**
     * @brief entradaUsuario; se encarga de mandar a llamar a recibo pero desde un thread  
     * @param El socket de donde viene. 
     * @return nada
     */
     void entradaUsuario(int socketParam);

     /**
     * @brief recibo; recibe los mensaje de los clientes  
     * @param El socket de donde viene. 
     * @return El json respectivo a el socket. 
     */
     nlohmann::json recibo(int socketParam);

      /**
     * @brief respuesta; es parte del la interface(Sujeto) manda la respuesta a los usuarios 
     * @param Lista de tipo String con personas a enviar, el mensaje 
     * @return Sin retorno. 
     */
     void respuesta(std::vector<std::string> PersonasEnviar, std::string msg); 

     /**
     * @brief respuesta; es parte del la interface(Sujeto) manda la respuesta a los usuarios 
     * @param Lista de tipo cliente con personas a enviar, el mensaje
     * @return Sin retorno. 
     */
     void respuesta(std::vector<Cliente> PersonasEnviar, std::string msg) override;

     /**
     * @brief conexion; método que checa conexiones constantemente para agregar. 
     * @param Sin parametros. 
     * @return Sin retorno. 
     */
     void conexion(); 

     
    /**
     * @brief existeElUsuario; permite saber si el usuario esta en la lista del servidor
     * @param el nombre del usuario
     * @return booleano 
     */
     bool existeElUsuario(Cliente usuario);

     /**
     * @brief existeElCuarto; permite saber si la sala esta en la lista del servidor
     * @param el nombre de la sala
     * @return booleano 
     */
     bool existeElCuarto(Cuarto sala);


     /**
     * @brief fueInvitado; Verifica si un usuario fue invitado a un cuarto
     * @param El Usuario  
     * @return sUn booleano
     */
     bool fueInvitado(Cliente usuario);
     
     /**
     * @brief nuevoUsuario; avisa a los demas de un nuevo usuario y maneja las conexiones 
     * @param sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoUsuario(std::string nombre); 

     /**
     * @brief nuevoStatus; modifica el status  
     * @param Sin parametros 
     * @return string de tipo json 
     */
     std::string nuevoStatus(std::string nombre, std::string estatus);
     
     /**
     * @brief usuariosList; manda la lista de usuarios conectados al servidor.   
     * @param sin parametros
     * @return  string de tipo json 
     */
     std::string usuariosList(); 

     /**
     * @brief mandarMensaje; manda un mensaje a cierta persona 
     * @param El cliente a mandar mensaje y para quien es el mensaje
     * @return string de tipo json 
     */
     std::string mandarMensaje(std::string msg, Cliente usuario);

     /**
     * @brief mandarMensajePublico; manda un mensaje a todos los usuarios conectados 
     * @param El mensaje
     * @return string de tipo json 
     */
     std::string mandarMensajePublico(std::string msg, Cliente usuario); 

     /**
     * @brief respuestaNuevoCuarto; responde a la creación de un cuarto nuevo.  
     * @param El nombre del cuarto
     * @return string de tipo json 
     */
     std::string respuestaNuevoCuarto(std::string cuartoNuevo);

     /**
     * @brief invitacion; invita a uno o mas usuarios a un cuarto. 
     * @param El mensaje
     * @return string de tipo json 
     */
     std::string invitacion(Cuarto sala, std::vector<Cliente> listaUsuarios);
     

     /**
     * @brief mandarMensajeCuarto; manda un mensaje al cuarto 
     * @param El mensaje y el cuarto a mandar el mensaje
     * @return string de tipo json 
     */
     std::string mandarMensajeCuarto(std::string msg, Cuarto sala, Cliente usuario);

     /**
     * @brief seUnioCuarto; une un cliente a cierto cuarto  
     * @param El cliente a agregar, nombre del cuarto 
     * @return un string de tipo json 
     */
     std::string seUnioCuarto(Cliente usuario, Cuarto sala); 

     /**
     * @brief listaUsuariosCuarto; retorna la lista de usuarios en el cuarto
     * @param el nombre del cuarto
     * @return un string de tipo json
     */
     std::string listaUsuariosCuarto(Cuarto sala, Cliente usuario); 

     /**
     * @brief abandonarCuarto; saca a una persona del cuarto e informa.  
     * @param El cliente a sacar
     * @return un string de tipo json
     */
     std::string abandonarCuarto(Cliente usuario, Cuarto sala);

     /**
     * @brief eliminarCuarto; elimina el cuarto en caso de tener 0 elementos. 
     * @param El cuarto
     * @return nada
     */
     void eliminarCuarto(Cuarto sala);

     /**
     * @brief desconectado; desconecta al usuario del servidor
     * @param El cliente a desconectar
     * @return un string de tipo json
     */
     std::string desconectado(Cliente usuario);  

};

#endif //SERVIDOR_HPP