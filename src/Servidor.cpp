
#include "Servidor.hpp"


std::string Servidor::respuesta() override;

bool verExisUsuario(std::String nombre); 

std::string Servidor::nuevoUsuario(); 
std::string Servidor::nuevoStatus(); 
std::string Servidor::usuariosList(); 

std::string Servidor::mandarMensaje(std::string msg);
std::string Servidor::mandarMensajePublico(); 
std::string Servidor::seUnioCuarto(Cliente usuario); 
std::string Servidor::listaUsuariosCuarto(std::string nombre); }

std::string Servidor::abandonarCuarto(Cliente usuario); 
std::string Servidor::desconectado(Cliente usuario);  
