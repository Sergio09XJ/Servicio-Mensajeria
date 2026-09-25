
#include "Servidor.hpp"


std::string Servidor::respuesta() override;

bool existeElUsuario(Cliente usuario){
     auto estaPersona = std::find(this->listClientes.begin(), this->listClientes.end(), usuario);
     estaPersona != this->listClientes.end() ? return true : return false;
}

std::string verExisUsuario(Cliente usuario){
  
     if (existeElUsuario(usuario)) {
        return  "  { \"type\": \"RESPONSE\",
                     \"operation\": \"IDENTIFY\",
                     \"result\": \"SUCCESS\",
                     \"extra\": " + usuario.getNombre() + " } \n ";
     }else{
         return  "  { \"type\": \"RESPONSE\",
                     \"operation\": \"IDENTIFY\",
                     \"result\": \"USER_ALREADY_EXISTS\",
                     \"extra\": " + usuario.getNombre() + " } \n ";
     }
}

std::string Servidor::nuevoUsuario(std::string nombre){
    return  " { \"type \":\"NEW_USER\",
                \"username \": " + nombre + " } \n ";
} 

std::string Servidor::nuevoStatus(std::string nombre, std::string estatus){
    return " { \"type\": \"NEW_STATUS\",
               \"username\": " + nombre + ",
               \"status\": " + estatus + " } \n ";
} 

std::string Servidor::usuariosList(std::vector<string> listaUsuarios){
    std::vector<std::string> listaUsuarios; 
    for (int i = 0; i < this->listClientes; i++ ){
        listaUsuarios.push_back(this->listClientes[i].getPersonaEstatus());
    }
        return " { \"type\": \"USER_LIST\",
                   \"users\": " + listaUsuarios +  " } \n";
} 

std::string Servidor::mandarMensaje(std::string msg, Cliente usuario){
   if (existeElUsuario(usuario)){
     return " { \"type\": \"TEXT_FROM\",
                \"username\": " + usuario.getNombre() + ",
                \"text\": " + msg + " } \n";
   } else {
     return " { \"type\": \"RESPONSE\",
                \"operation\": \"TEXT\",
                \"result\": \"NO_SUCH_USER\",
                \"extra\": " + usuario.getNombre() + " } \n";
   }
}

std::string Servidor::mandarMensajePublico(std::string msg, Cliente usuario){
  return "{ \"type\": \"PUBLIC_TEXT_FROM\",
            \"username\": " + usuario.getNombre() + ",
            \"text\": " + msg + " } \n"
}

std::string Servidor::seUnioCuarto(Cliente usuario, Cuarto nombreCuarto); 
std::string Servidor::listaUsuariosCuarto(std::string nombreCuarto); }

std::string Servidor::abandonarCuarto(Cliente usuario){
    if (existeElUsuario(usuario)){
       return { "type": "LEFT_ROOM",
                "roomname": "Sala 1",
                "username": "Fernando" }
    }else{

    }
}

std::string Servidor::desconectado(Cliente usuario){
    return "{ \"type\": \"DISCONNECTED\",
              \"username\": " + usuario.getNombre() + " } \n"
} 
