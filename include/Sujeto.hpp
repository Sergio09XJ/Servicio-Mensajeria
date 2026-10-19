#ifndef SUJETO_HPP
#define SUJETO_HPP 

#include<vector>
#include<string>
class Cliente; 

/**
* @class Clase interface para el sujeto.
         Quien manda actualizaciones a los observadores. 
* @brief Permite mandar respuestas a los obesrvadores.  
*/
class Sujeto{

    public: 

     /**
      * @brief Método respuesta; mandar actualizaciones/respuestas a los observadores
      * @param sin parametros.  
      */
      virtual void respuesta(std::vector<Cliente> PersonasEnviar, std::string msg) = 0;

     /**
      * @brief Destructor Sujeto; lo genera automaticamente. 
      * @param in parametros.  
      */
     virtual ~Sujeto() = default;

       
 
     
     

};

#endif //SUJETO_HPP



