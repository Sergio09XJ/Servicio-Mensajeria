
#include "Cuarto.hpp"

std::vector<Cliente> Cuarto::getIntegrantes(){
    return this->integrantes;
}

 
std::string getNombre(){
    return this->nombre
} 

void Cuarto::actualizar(){}

std::string Cuarto::listarPersonas(){

  std::vector<std::string> listaPersonas;

  for (int i = 0; i < this->integrantes.size(); i++ ){
          listaPersonas.push_back(this->integrantes[i].getPersonaEstatus());
  }
  return "{ \"type\": \"ROOM_USER_LIST\",
            \"roomname\": \"Sala 1\",
            \"users\": " +  listaPersonas  + " }\n";
}

bool Cliente::verificarNombreCuarto(std::string nombre){
    if  this->nombre.size() <= 16 ? return true : return false; 
}


void Cuarto::agregarPersona(Cliente persona){
    this->integrantes.push_back(persona);
}

bool Cuarto::sacarPersona(Cliente persona){
     auto estaPersona = std::find(this->integrantes.begin(), this->integrantes.end(), persona);
     if (estaPersona != this->integrantes.end()) {
       std::erase(this->integrantes, persona) 
       return true; 
     }else{
       return false;
     }
}
