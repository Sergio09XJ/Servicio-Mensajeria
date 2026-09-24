#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP 

#include "Sujeto.hpp"

#include "string"

class Servidor : public Sujeto{

    private:
     std::string nombre;  


    public: 
   
     public(std::string nombre): nombre(nombre){}

     ~public() = default;
}

#endif //SERVIDOR_HPP