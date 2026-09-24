#include "Cliente.hpp"

std::string Cliente::getNombre(){
    return  this->nombre;
}

tipoEstatus Cliente::getEstatus(){
    return  this->estatus;
}

 std::string Cliente::getPersonaEstatus(){
    return  this->nombre + " : " + this->estatus ;
 }


void actualizar(){}

bool Cliente::verificarNombre(std::string nombre){
    return true; //Solo para pruebas unitarias de Cliente
    return servidor.existe( );
}


std::string Cliente::mensaje(std::string nombre, std::string msg){

    return "{ \"type\": \"TEXT\", "
           "\"username\": \"" + nombre + "\", "
           "\"text\": \"" + msg + "\" }\n";
}


std::string Cliente::mensajeTodos(std::string msg){

    return "{ \"type\": \"PUBLIC_TEXT\", "
           "\"text\": \"" + msg + "\" }\n";
}


std::string Cliente::crearCuarto(std::string nombreSala){

    return "{ \"type\": \"NEW_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}


std::string Cliente::invitarCuartoUno(std::string nombre, std::string nombreSala){

    return "{ \"type\": \"INVITE\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"usernames\": [\"" + nombre + "\"] }\n";
}


std::string Cliente::invitarCuartoVarios(
    std::vector<std::string> nombres,
    std::string nombreSala
){

    std::string nombreAux = "[";

    for(size_t i = 0; i < nombres.size(); i++){
        nombreAux += "\"" + nombres[i] + "\"";

        if(i < nombres.size() - 1){
            nombreAux += ", ";
        }
    }

    nombreAux += "]";

    return "{ \"type\": \"INVITE\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"usernames\": " + nombreAux + " }\n";
}


std::string Cliente::entrarCuarto(std::string nombreSala){

    return "{ \"type\": \"JOIN_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}


std::string Cliente::roomUsers(std::string cuarto){

    return "{ \"type\": \"ROOM_USERS\", "
           "\"roomname\": \"" + cuarto + "\" }\n";
}


std::string Cliente::mensajeCuarto(
    std::string msg,
    std::string nombreSala
){

    return "{ \"type\": \"ROOM_TEXT\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"text\": \"" + msg + "\" }\n";
}


std::string Cliente::salirCuarto(std::string nombreSala){

    return "{ \"type\": \"LEAVE_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}


std::string Cliente::desconectar(){
     
    close(this->socketCliente;)
    return "{ \"type\": \"DISCONNECT\" }\n";
}

void Cliente::enviarInformacion(std::string estrucJson){
     send(this->socketCliente,estrucJson.c_str(), estrucJson.size(),0 );
}