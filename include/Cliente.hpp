#ifndef CLIENTE_HPP
#define CLIENTE_HPP 

//Librerias del programa. 
#include "Observador.hpp"
#include "tipoEstatus.hpp"

//Librerias basicas 
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>



//Libreria para json
#include <nlohmann/json.hpp>

//Libreria para socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using json = nlohmann::json;

class Cliente : public Observador{


    private: 

     std::string nombre; 
     tipoEstatus estatus;
     int socketCliente; 
     class Servidor* elServidor; 

    public:

     /**
     * @brief Constructor de Cliente
     *        Verifica que nombre no este siendo usado ya. 
     * @param El nombre, el estatus, el servidor 
     */

     Cliente(std::string nombre, Servidor* elServidor);

     /**
     * @brief ==; operador para permitir la comparación usando ==
     * @param La referencia a un cliente
     * @return booleano, si es el mismo o no lo es. 
     */
     bool operator==(const Cliente& otro) const;

     /**
     * @brief get() permite devolver un puntero de la instancia
     * @param Nada
     * @return un puntero a Cliente.  
     */
     Cliente* getCliente();

     /**
     * @brief getNombre; para obtener el nombre de la instancía 
     * @param Sin parametros
     * @return el nombre, string
     */
     std::string getNombre();

     /**
     * @brief getInstanciaNombre; para obtener la instancia a partir del nombre. 
     * @param El nombre del usuario
     * @return un puntero a la instancía. 
     */
     Cliente* getInstanciaNombre(std::string nombre);

     /**
     * @brief getEstatus; para obtener el estatus de la instancía
     * @param Sin parametros
     * @return la instancia, tipoEstatus
     */
     tipoEstatus getEstatus();

     /**
     * @brief getPersonaEstatus; obtiene un string de tipo json con el nombre y el estatus. 
     * @param Sin parametros
     * @return string de tipo json. 
     */
     std::string getPersonaEstatus();

    /**
     * @brief recibo; permite recibir mensajes desde el servidor y pararlos a json 
     * @param Sin un socket 
     * @return el json. 
     */
     json recibo(int socketParam);
     
     /**
     * @brief actualizar; permite actualizar el estado de la instancia
     * @param Sin parametros
     * @return 
     */
     void actualizar(int socketParam) override; 
     
     /**
     * @brief respRESPONSE; string para usuario cuando sea tipo response
     * @param Sin json 
     * @return string
     */
     std::string respRESPONSE(json json); 

     /**
     * @brief respNEW_STATUS; string para usuario cuando sea tipo New_status
     * @param Sin json
     * @return string
     */
     std::string respNEW_STATUS(json json); 

     /**
     * @brief respUSER_LIST; string para usuario cuando sea tipo User_list
     * @param Sin json
     * @return string
     */
     std::string respUSER_LIST(json json); 

     /**
     * @brief respTEXT_FROM;string para usuario cuando sea tipo Text from 
     * @param Sin json
     * @return string
     */
     std::string respTEXT_FROM(json json); 

     /**
     * @brief respPUBLIC_TEXT_FROM; string para usuario cuando sea tipo Public Text from 
     * @param Sin json
     * @return string
     */
     std::string respPUBLIC_TEXT_FROM(json json);
     
     /**
     * @brief resNEW_ROOM; string para usuario cuando sea tipo new room 
     * @param Sin json
     * @return string
     */
     std::string resNEW_ROOM(json json);

     /**
     * @brief respINVITATION; string para usuario cuando sea tipo Invitation
     * @param Sin json
     * @return string
     */
     std::string respINVITATION(json json); 

     /**
     * @brief respJOINED_ROOM; string para usuario cuando sea tipo joined room 
     * @param Sin json
     * @return string
     */
     std::string respJOINED_ROOM(json json);

     /**
     * @brief respROOM_USER_LIST; string para usuario cuando sea tipo User list
     * @param Sin json
     * @return string
     */
     std::string respROOM_USER_LIST(json json); 

     /**
     * @brief respROOM_TEXT_FROM; string para usuario cuando sea tipo Room text from 
     * @param Sin json
     * @return string
     */
     std::string respROOM_TEXT_FROM(json json); 
     
     /**
     * @brief respLEFT_ROOM; string para usuario cuando sea tipo left room 
     * @param Sin json
     * @return string
     */
     std::string respLEFT_ROOM(json json);

     /**
     * @brief respDISCONNECTED; string para usuario cuando sea tipo Disconnected
     * @param Sin json
     * @return string
     */
     std::string respDISCONNECTED(json json); 


     /**
     * @brief verificarNombre; verifica que el número de caracteres del usuario sea menor a 8. 
     * @param  El nombre, string
     * @return un booleano, true or false. 
     */
     bool verificarNombre(std::string nombre);

     
     /**
     * @brief mensaje; manda un str par para el servidor, el mensaje a mandar. 
     * @param El mensaje a mandar y el nombre de quien 
     * @return Un string con formato json.  
     */
     std::string mensaje(std::string nombre, std::string msg); 


     /**
     * @brief listaUsuarios; es para indicar que se quiere la lista de usuarios en el servidor 
     * @param Sin parametros 
     * @return Un string con formato json.
    */
     std::string listaUsuarios();

     /**
     * @brief mensajeTodos; manda un str par para el servidor, el mensaje a mandar todos. 
     * @param El mensaje a mandar
     * @return Un string con formato json.  
     */
     std::string mensajeTodos(std::string msg); 

      /**
     * @brief nuevoEstatus; modifica el estatus 
     * @param El estatus como string
     * @return el string en formato json con el estatus
     */
     std::string nuevoEstatus(std::string estatus);

     /**
     * @brief crearCuarto; manda un str con formato json indicando que se quiere crear un cuarto
     * @param El nombre de la sala/cuarto.
     * @return Un string con formato json.  
     */
     std::string crearCuarto(std::string nombreSala);

     /**
     * @brief invitarCuartoUno; invitamos al cuarto a un usuario 
     * @param El nombre del usuario, el nombre de la sala. 
     * @return Un string con formato json.  
     */
     std::string invitarCuartoUno(std::string nombre, std::string nombreSala);

     /**
     * @brief invitarCuartoVarios; Invitamos al cuarto a varios. 
     * @param Una lista de nombres de usuarios, el nombre de la sala. 
     * @return Un string con formato json.  
     */
     std::string invitarCuartoVarios(std::vector<std::string> nombres, std::string nombreSala);
     
     /**
     * @brief entrarCuarto; método para acceder a una sala. 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string entrarCuarto(std::string nombreSala); 

     /**
     * @brief roomUsers; llamada al servidor para tener la lista de usuarios de un cuarto. 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string roomUsers(std::string cuarto);
     
     /**
     * @brief mensajeCuarto; método para mandar un mensaje a cierto cuarto  
     * @param El nombre de la sala y el mensaje a mandar  
     * @return Un string con formato json.  
     */
     std::string mensajeCuarto(std::string msg,std::string nombreSala); 

     /**
     * @brief salirCuarto; método para salir de un cuarto 
     * @param El nombre de la sala.  
     * @return Un string con formato json.  
     */
     std::string salirCuarto(std::string nombreSala); 

    /**
     * @brief desconectar; nos permite salir del servidor 
     * @param Sin parametros  
     * @return Un string en formato json. 
     */
     std::string desconectar(); 

     /**
     * @brief enviarInformación
     * @param La estructura Json de tipo string a mandar  
     * @return nada
     */
     void enviarInformacion(std::string estrucJson);

    
     /**
     * @brief toString; pasa de tipoEstatus a cadena 
     * @param El valor de tipo estatus 
     * @return El valor como string
     */
    std::string toString(tipoEstatus estatus);
    
     /**
     * @brief toEstatus; pasa de cadena a tipoEstatus
     * @param El valor en string  
     * @return El valor como tipoEstatus
     */
    tipoEstatus toEstatus( std::string cadenaEstatus);


}; 

#endif //CLIENTE_HPP