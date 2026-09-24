#ifndef CLIENTE_HPP
#define CLIENTE_HPP 

#include "Observador.hpp"
#include "tipoEstatus.hpp"
#include "Servidor.hpp"
#include "tipoEstatus.hpp"

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

class Cliente : public Observador{
  
    private: 

     std::string nombre; 
     tipoEstatus estatus;
     Servidor servidor;


    public:
     /**
     * @brief Constructor de Cliente
     *        Verifica que nombre no este siendo usado ya. 
     * @param El nombre, el estatus, el servidor 
     */
     Cliente(std::string nombre, Servidor servidor ) : servidor(servidor) {
     
        if(verificarNombre(nombre)){
           this->nombre = verificarNombre(nombre)
           this->nombre = tipoEstatus::ACTIVE
        }else{ 
            ~Observador(); 
        }
     }
     /**
     * @brief getNombre; para obtener el nombre de la instancía 
     * @param Sin parametros
     * @return el nombre, string
     */
     std::string getNombre();

     /**
     * @brief getEstatus; para obtener en estatus de la isntancía
     * @param Sin parametros
     * @return la instancia, tipoEstatus
     */
     tipoEstatus getEstatus();

     /**
     * @brief getServido; para obtener el servidor al que es parte el cliente
     * @param Sin parametros
     * @return el servidor, Servidor.
     */
     Servidor getServidor();
     
     /**
     * @brief actualizar; permite actualizar el el estado de la instacia
     * @param Sin parametros
     * @return 
     */
     void actualizar() override; 
     /**
     * @brief verificarNombre; verifica que no exista un usuario ya con el mismo nombre en el servidor o cuarto. 
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
     * @brief mensajeTodos; manda un str par para el servidor, el mensaje a mandara todos. 
     * @param El mensaje a mandar
     * @return Un string con formato json.  
     */
     std::string mensajeTodos(std:string msg); 

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


}; 

#endif //CLIENTE_HPP