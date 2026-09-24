#ifndef CUARTO_HPP
#define CUARTO_HPP 

#include "Observador.hpp"
#include "Cliente.hpp"


//Librerias basicas 
#include <string>
#include <vector>
#include <algorithm>

//Libreria para json
#include <nlohmann/json.hpp>



class Cuarto : public Observador{
    
    private: 
     std::vector<Cliente> integrantes; 

     

    public: 

     Cuarto() {
     }

     /**
     * @brief getIntegrantes; retorna los integrantes del cuarto 
     * @param No tiene
     * @return Un vector de clientes  
     */
    std::vector<Cliente> getIntegrantes(); 

     /**
     * @brief actualizar; actualiza los datos del cuarto
     * @param No tiene 
     * @return No tiene  
     */
    void actualizar(); 
    
     /**
     * @brief listarPersonas; manda una lista de string de las personas con su estatus
     * @param No tiene
     * @return Un string de las personas 
     */
    std::string listarPersonas();
    
     /**
     * @brief agregarPersona; agrega una persona al cuarto 
     * @param El cliente a agregar
     * @return No retorna
     */
    void agregarPersona(Cliente persona);

     /**
     * @brief sacarPersona; Elimina un cliente del cuarto
     * @param La persona 
     * @return Un booleano para saber si se logro sacar o no.  
     */
    bool sacarPersona(Cliente persona);



};

#endif //CUARTO_HPP