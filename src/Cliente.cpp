
#include "Cliente.hpp"

 std::String Cliente::getNombre(){
        return nombre; 
     }
     tipoEstatus Cliente::getEstatus(){
        return estatus; 
     }
     Servidor Cliente::getServidor(){
        return servidor; 
     }

void actualizar(){} 

bool Cliente::verificarNombre(std::String nombre){
        return servidor.existe(nombre); 
}



std::String Cliente::mensaje(std::String nombre, std::String msg){
   
        return "{ \"type\": \"TEXT\",
                      \"username\": " << strlen(nombre) << "
                      \"text\": " << strlen(msg) << "
                     }\n"
}


std::String Cliente::mensajeTodos(std:String msg){

        return  "{ \"type\": \"PUBLIC_TEXT\",
                   \"text\": " << strlen(msg) << " }\n"
       
     }


std::String Cliente::crearCuarto(std::String nombreSala){

    return "{ \"type\": \"NEW_ROOM\",
             \"roomname\": " << strlen(nombreSala) << " } \n"
}


std::String Cliente::invitarCuartoUno(std::String nombre, std::String nombreSala){

   return " { \"type\": \"INVITE\",
            \"roomname\": , " << strlen(nombreSala) << "
            \"usernames\": " <<  strlen(nombre) << " } \n"
}

std::String Cliente::invitarCuartoVarios(std::vector<std::String> nombres, std::String nombreSala){
std::vector<std::String> nombreAux[nombre.size()]; 

   for(int i = 0; i < nombre.size(); i ++){
      nombreAux[i] = strlen(nombre[i])
   }
   return " { \"type\": \"INVITE\",
            \"roomname\": , " << strlen(nombreSala) << "
            \"usernames\": " <<  nombreAux  << " } \n"
}

std::String Cliente::entrarCuarto(std::String nombreSala){
    return "{ \"type\": "JOIN_ROOM",
              \"roomname\": " << strlen(nombreSala) << " }"
}

std::String Cliente::roomUsers(std::String cuarto){
     return " { \"type\": \"ROOM_USERS\",
                \"roomname\": " << strlen(cuarto) << " } \n"
}
std::String Cliente::mensajeCuarto(std::String msg,std::String nombreSala){
    return " { \"type\": \"ROOM_TEXT\",
             \"roomname\": " << strlen(nombreSala) << ",
             \"text\": " <<  strlen(msg)  << "} "
}
std::String Cliente::salirCuarto(std::String nombreSala){
    return "{ \"type\": \"LEAVE_ROOM\",
              \"roomname\": " << strlen(nombreSala) << " } \n"
}
std::String Cliente::desconectar(){
    return  " { \"type\": \"DISCONNECT\" } \n"
}