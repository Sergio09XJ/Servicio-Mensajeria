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
     std::string nombre; 
     std::vector<Cliente> integrantes; 

     

    public: 

     Cuarto(std::string nombre) nombre(nombre) {
        if(!verificarNombreCuarto(nombre) ){
            std::cout << "La longitud de del nombre del cuarto debe ser menor o igual a 16 caractares.  " << std::endl
            ~Observador(); 
        }
     }

     /**
     * @brief getIntegrantes; retorna el nombre 
     * @param No tiene
     * @return El string del nombre  
     */
    std::string getNombre(); 

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
     * @brief verificarNombreCuarto; verifica que el número de caracteres del cuerto, sea menor o igual a 16. 
     * @param  El nombre, string
     * @return un booleano, true or false. 
     */
     bool verificarNombreCuarto(std::string nombre);
    
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