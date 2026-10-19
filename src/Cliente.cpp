#include "Cliente.hpp"
#include "Servidor.hpp"

 Cliente::Cliente(std::string nombre, Servidor* elServidor){

        if(verificarNombre(nombre)){
           this->nombre = nombre; 
           this->elServidor = elServidor;
           this->estatus = tipoEstatus::ACTIVE;

           //Creamos el socket, A_INET indica que sera IPv4, SOCK_STREAM el flujo, TCP y 0 el protocolo para esa combinación 
           this->socketCliente = socket(AF_INET, SOCK_STREAM, 0);


            // Especificamos la dirección del socket
            sockaddr_in serverAddress;
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(8080);
            serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

            // establecemos conexión con el socket del servidor. 
            connect(this->socketCliente, (struct sockaddr*)&serverAddress,sizeof(serverAddress)); 

            //Identificamos con el servidor. 
            std::string identify = "{ \"type\": \"IDENTIFY\", \"username\": \"" + this->nombre + "\" }\n";
            send(this->socketCliente, identify.c_str(), identify.size(), 0);



        }else{ 
            std::cout << "La longitud de tu nombre debe ser menor o igual a 8 caractares.  " << std::endl;
        }

     }


bool Cliente::operator==(const Cliente& otro) const{
    return this->nombre == otro.nombre;
}

Cliente* Cliente::getCliente(){
    return this; 
}

std::string Cliente::getNombre(){
    return this->nombre;
}

Cliente* Cliente::getInstanciaNombre(std::string nombre){
    return (nombre == this->nombre) ? this : nullptr; 
}

tipoEstatus Cliente::getEstatus(){
    return this->estatus;
}

std::string Cliente::getPersonaEstatus(){
    return this->nombre + " : " + toString(this->estatus);
}

void Cliente::enviarInformacion(std::string estrucJson){
    send(this->socketCliente,estrucJson.c_str(), estrucJson.size(),0);
}

json Servidor::recibo(int socketParam){
   
    char buffer[1024];
    int bytesRecibidos = recv(socketParam, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
       buffer[bytesRecibidos] = '\0';
       std::string mensaje(buffer, bytesRecibidos);
       nlohmann::json datos = nlohmann::json::parse(mensaje);
       return datos;
    }
   return nullptr;
}

void Cliente::actualizar(int socketParam){
     json respuesta = recibo(socketParam);
     std::string respuestaString = respuesta.dump();
     std::istringstream flujo(respuestaString); 
     std::string mensaje;
         
     while(std::getline(flujo, mensaje)){
        json datos = json::parse(mensaje);
         if(datos["type"] == "RESPONSE"){
            respRESPONSE(datos);
         }else if (datos["type"] == "NEW_STATUS"){
            respNEW_STATUS(datos);
         }else if (datos["type"] == "USER_LIST"){
            respUSER_LIST(datos);  
         }else if (datos["type"] == "TEXT_FROM"){
            respTEXT_FROM(datos);
         }else if (datos["type"] == "PUBLIC_TEXT_FROM"){
            respPUBLIC_TEXT_FROM(datos);
         }else if (datos["type"] == "INVITATION"){
            respINVITATION(datos);
         }else if (datos["type"] == "ROOM_USER_LIST"){
            respROOM_USER_LIST(datos);
         }else if (datos["type"] == "ROOM_TEXT_FROM"){
            respROOM_TEXT_FROM(datos);
         }else if (datos["type"] == "DISCONNECTED"){
            respDISCONNECTED(datos);
         }else {
                
         }
     }
}

std::string respRESPONSE(json json){
    std::string retorno;
    if (json["result"] == "SUCCESS"){
     retorno = json["extra"].get<std::string>() + " te conextaste con exito al servidor. (: ";
    }else{
      retorno = json["extra"].get<std::string>() + " ya estas en el servidor. ";
    }
    return retorno;
} 

    
std::string respNEW_STATUS(json json){
    return "El estatus de " + json["username"].get<std::string>() + " cambio a " + json["status"].get<std::string>(); 
} 

     
std::string respUSER_LIST(json json){
    return "Los integrantes y sus estatus son: " + json["users"].get<std::string>();
}

     
std::string respTEXT_FROM(json json){
    if (json["type"] == "RESPONSE"){
     return "El usuario " + json["username"].get<std::string>() + " no existe. "; 
    }else{
     return json["username"].get<std::string>() + " | << " + json["text"].get<std::string>();
    }
} 

     
std::string respPUBLIC_TEXT_FROM(json json){
     return json["username"].get<std::string>() + " | << " + json["text"].get<std::string>();
    
}

std::string resNEW_ROOM(json json){
     if (json["result"] == "ROOM_ALREADY_EXISTS"){
     return "El cuarto " + json["extra"].get<std::string>() + " ya existe. "; 
    }else{
     return "El cuarto " + json["extra"].get<std::string>() + "se creo con exito. ";
    }
}

    
std::string respINVITATION(json json){
    if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_ROOM"){
     return "El cuarto " + json["extra"].get<std::string>() + " no existe. "; 
    }else if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_USER"){
     return "El usuario " + json["extra"].get<std::string>() + " no existe. ";
    }else{
        return "Fuiste invitad@ al cuarto " + json["roomname"].get<std::string>();
    }
} 

     
std::string respJOINED_ROOM(json json){
    if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_ROOM"){
     return "El cuarto " + json["extra"].get<std::string>() + " no existe."; 
    }else if (json["type"] == "RESPONSE" && json["result"] == "NOT_INVITED"){
     return "No haz sido invitad@ al cuarto " + json["extra"].get<std::string>();
    }else if(json["type"] == "RESPONSE" && json["result"] == "SUCCESS"){
        return "Entraste al cuarto " + json["extra"].get<std::string>();
    }else{
        return "Fuiste invitad@ al cuarto " + json["roomname"].get<std::string>();
    }
} 

std::string respROOM_USER_LIST(json json){
  if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_ROOM"){
     return "El cuarto " + json["extra"].get<std::string>() + " no existe."; 
    }else if (json["type"] == "RESPONSE" && json["result"] == "NOT_JOINED"){
     return "No estas en el cuarto " + json["extra"].get<std::string>() + " o no haz sido invitado.";
    }else{
        return "La lista de usuarios es: " + json["users"].get<std::string>();
    }
}
     
std::string respROOM_TEXT_FROM(json json){
    if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_ROOM"){
     return "El cuarto " + json["extra"].get<std::string>() + " no existe."; 
    }else if (json["type"] == "RESPONSE" && json["result"] == "NOT_JOINED"){
     return "No estas en el cuarto " + json["extra"].get<std::string>() + " o no haz sido invitado.";
    }else{
        return json["extra"].get<std::string>() + " - " + json["username"].get<std::string>() + " | << " + json["text"].get<std::string>();
    }
}

std::string respLEFT_ROOM(json json){
    if (json["type"] == "RESPONSE" && json["result"] == "NO_SUCH_ROOM"){
     return "El cuarto " + json["extra"].get<std::string>() + " no existe."; 
    }else if (json["type"] == "RESPONSE" && json["result"] == "NOT_JOINED"){
     return "No estas en el cuarto " + json["extra"].get<std::string>() + " o no haz sido invitado.";
    }else{
        return "Un usuario abandono el cuarto " + json["roomname"].get<std::string>();
    }
}

     
std::string respDISCONNECTED(json json){
    if(json["type"] == "DISCONNECTED"){
        return "Un usuario se ha desconectado del servicio. ";
    }else{
        return respLEFT_ROOM(json);
    }
}

bool Cliente::verificarNombre(std::string nombre){
    return (nombre.size() <= 8) ? true : false; 
}

std::string Cliente::mensaje(std::string nombre, std::string msg){

    return "{ \"type\": \"TEXT\", "
           "\"username\": \"" + nombre + "\", "
           "\"text\": " + msg + " }\n";
}

std::string Cliente::nuevoEstatus(std::string estatus){
    this->estatus = toEstatus(estatus); 
    return "{ \"type\": \"STATUS\", "
           "\"status\": \"" + estatus + "\" }\n";
}

std::string Cliente::listaUsuarios(){
    return " { \"type\": \"USERS\" }\n";
}

std::string Cliente::mensajeTodos(std::string msg){

    return "{ \"type\": \"PUBLIC_TEXT\", "
           "\"text\": " + msg + " }\n";
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

std::string Cliente::invitarCuartoVarios( std::vector<std::string> nombres, std::string nombreSala){

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

std::string Cliente::mensajeCuarto(std::string msg,std::string nombreSala){

    return "{ \"type\": \"ROOM_TEXT\", "
           "\"roomname\": \"" + nombreSala + "\", "
           "\"text\": \"" + msg + "\" }\n";
}

std::string Cliente::salirCuarto(std::string nombreSala){

    return "{ \"type\": \"LEAVE_ROOM\", "
           "\"roomname\": \"" + nombreSala + "\" }\n";
}

std::string Cliente::desconectar(){
     
    close(this->socketCliente);
    return "{ \"type\": \"DISCONNECT\" }\n";
}



std::string Cliente::toString(tipoEstatus estatus){
    switch (estatus) {
        case tipoEstatus::ACTIVE:  return "ACTIVE";
        case tipoEstatus::AWAY:    return "AWAY";
        case tipoEstatus::BUSY:    return "BUSY";
        case tipoEstatus::INVALID: return "INVALID";
    }
    return nullptr;
}

tipoEstatus Cliente::toEstatus(std::string cadenaEstatus){
    if (cadenaEstatus == "ACTIVE"){
        return tipoEstatus::ACTIVE;
    }else if (cadenaEstatus == "AWAY"){
        return tipoEstatus::AWAY;
    }else if (cadenaEstatus == "BUSY"){
        return tipoEstatus::BUSY;
    }else{
        return tipoEstatus::INVALID;
    }
}