
#include "Cuarto.hpp"

std::vector<Cliente> Cuarto::getIntegrantes(){
    return integrantes;
}

void Cuarto::actualizar(){}

std::string Cuarto::listarPersonas(){

  std::vector<std::string> listaPersonas;

  for (int i = 0; i < integrantes.size(); i++ ){
          listaPersonas.push_back(integrantes[i].getPersonaEstatus());
  }
  return "{ \"type\": \"ROOM_USER_LIST\",
            \"roomname\": \"Sala 1\",
            \"users\": " +  listaPersonas  + " }\n";
}

void Cuarto::agregarPersona(Cliente persona){
    integrantes.push_back(persona);
}

bool Cuarto::sacarPersona(Cliente persona){
     auto estaPersona = std::find(integrantes.begin(), integrantes.end(), persona);
     if (estaPersona != integrantes.end()) {
       std::erase(integrantes, persona) 
       return true; 
     }else{
         return false;
     }
}
