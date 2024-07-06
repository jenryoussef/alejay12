#include <iostream>
#include <fstream>    // Incluye la biblioteca estándar para manejo de archivos
#include <string>     // Incluye la biblioteca estándar para manejo de cadenas de texto
using namespace std;

struct cancion{
    int id;
    string nombre;
    string artista;
    string genero;
    int anio;
    cancion* siguiente;
};

struct persona{
    int id;
    string nombre;
    string correo;
    int edad;
    string contrasena;
    string pais;
    persona* siguiente;
};

// Definición del nodo para una Multi-Lista
struct nodo {
    int dato;
    nodo* siguiente;
    nodo* abajo; // Puntero al nodo en otra lista
};

void insertar_cancion(cancion*& nodo_principal, int id, string nombre, string artista, string genero, int anio) {
    cancion* nueva_cancion = new cancion;
    
    nueva_cancion->id = id;
    nueva_cancion->nombre = nombre;
    nueva_cancion->artista = artista;
    nueva_cancion->genero = genero;
    nueva_cancion->anio = anio;
    nueva_cancion->siguiente = nullptr;  

    if (nodo_principal==NULL){
        nodo_principal=nueva_cancion;
    }
    else{
        cancion* t= nodo_principal;
        while(t->siguiente!=NULL){
            t=t->siguiente;
        } 
    t->siguiente = nueva_cancion;

    }  
}

// Función para imprimir canciones
void imprimir_canciones(cancion* nodo_principal) {
    cancion* t = nodo_principal; 
    if (nodo_principal == nullptr) {
        cout << "No hay canciones para mostrar." << endl;
        return;
    }
    while (t != nullptr) {
        cout << "ID de la cancion: " << t->id << endl;
        cout << "Nombre: " << t->nombre << endl;
        cout << "Artista: " << t->artista << endl;
        cout << "Genero: " << t->genero << endl;
        cout << "anio: " << t->anio << endl;
        cout << endl;
        t = t->siguiente;
    }
}

void leer_archivo_canciones(){
    ifstream archivo;
    string contenido;

    archivo.open("C:/Users/user/Desktop/canciones.txt",ios::in); //abrimos el archivo en modo lectura

    if(!archivo){
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    while(!archivo.eof()) {             //mientras no sea el final del archivo 
        getline(archivo,contenido);
        cout << contenido << endl;                    
        
    }
    archivo.close();
    
}

void leer_archivo_personas(){
    ifstream archivo;
    string contenido;

    archivo.open("C:/Users/user/Desktop/usuarios.txt",ios::in); //abrimos el archivo en modo lectura (ios::in)

    if(!archivo){ 
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    while(!archivo.eof()) {             //mientras no sea el final del archivo 
        getline(archivo,contenido);
        cout << contenido << endl;                    
        
    }
    archivo.close();
    
}


void agregar_usuarios(){
    ofstream archivo;
    string usuario;

    archivo.open("C:/Users/user/Desktop/usuarios.txt",ios::app); //abrimos el archivo en modo escritura (ios::out)

    if(!archivo){
        cout << "error al abrir el archivo ... ";
        exit(1);
    }


        string id, nombre, gmail, edad, contrasena, pais;

        cout << "introduce el ID de usuario : ";
        cin >> id;
        cout << "introduce el nombre del usuario : ";
        cin >> nombre;
        cout << "introduce el gmail del usuario : ";
        cin >> gmail;
        cout << "introduce la edad del usuario : ";
        cin >> edad;
        cout << "introduce la contrasena del usuario : ";
        cin >> contrasena;
        cout << "introduce el pais del usuario : ";
        cin >> pais;

        archivo << "ID del usuario : " << id << endl;
        archivo << "nombre : " << nombre << endl;
        archivo << "gmail : " << gmail << endl;
        archivo << "edad : " << edad << endl;
        archivo << "contrasena : " << contrasena << endl;
        archivo << "pais : " << pais << endl;
        archivo << endl;

        cout << "usuario agregado con exito ." << endl;

    archivo.close();

}   

void agregar_canciones(){
    ofstream archivo;
    string cancion;

    archivo.open("C:/Users/user/Desktop/canciones.txt",ios::app); //abrimos el archivo en modo escritura (ios::out)

    if(!archivo){
        cout << "error al abrir el archivo ... ";
        exit(1);
    }


        string id, nombre, artista, genero, anio;

        cout << "introduce el ID de la cancion : ";
        cin >> id;
        cout << "introduce el nombre de la cancion : ";
        cin >> nombre;
        cout << "introduce el artista : ";
        cin >> artista;
        cout << "introduce el genero : ";
        cin >> genero;
        cout << "introduce el anio de salida : ";
        cin >> anio;

        archivo << "ID de la cancion : " << id << endl;
        archivo << "nombre : " << nombre << endl;
        archivo << "artista : " << artista << endl;
        archivo << "genero : " << genero << endl;
        archivo << "anio : " << anio << endl;
        archivo << endl;

        cout << "cancion agregada con exito ." << endl;

    archivo.close();

}  

void eliminar_usuarios() {
    ifstream archivo_original("C:/Users/user/Desktop/usuarios.txt");  // Abre el archivo "usuarios.txt" en modo lectura
    ofstream archivo_temporal("C:/Users/user/Desktop/temp.txt");   // Crea un archivo temporal "temp.txt" en modo escritura

    if (!archivo_original.is_open() || !archivo_temporal.is_open()) {
        cerr << "No se pudo abrir uno de los archivos." << endl;
        return;
    }

    string linea, id, id_usuario;
    bool eliminar = false;

    cout << "Ingresa el ID del usuario a eliminar: ";
    cin >> id;

    // Lee cada línea del archivo original
    while (getline(archivo_original, linea)) {
        if (linea.find("ID del usuario: ") == 0) {
            id_usuario = linea.substr(16); // Obtener el ID del usuario
            eliminar = (id_usuario == id); // Verificar si es el usuario a eliminar
        }

        // Si no es el usuario a eliminar, escribe la línea en el archivo temporal
        if (!eliminar) {
            archivo_temporal << linea << endl;
        }

        // Si se llega a una línea en blanco, se termina el bloque del usuario
        if (linea.empty()) {
            eliminar = false; // Reiniciar la variable para el siguiente usuario
        }
    }

    archivo_original.close();  // Cierra el archivo original
    archivo_temporal.close();  // Cierra el archivo temporal

    // Renombra el archivo temporal al nombre original
    if (remove("C:/Users/user/Desktop/usuarios.txt") != 0) {  //si retorna un valor diferente de cero hubo un error
        perror("Error eliminando el archivo original");
    }

    if (rename("C:/Users/user/Desktop/temp.txt", "C:/Users/user/Desktop/usuarios.txt") != 0) {  //renombra nuevamente el archivo al original
        perror("Error renombrando el archivo temporal");
    }

    cout << "Usuario eliminado correctamente." << endl;  // Muestra un mensaje
}



void eliminar_canciones() {
    ifstream archivo_original("C:/Users/user/Desktop/canciones.txt");  // Abre el archivo "canciones.txt" en modo lectura
    ofstream archivo_temporal("C:/Users/user/Desktop/temp.txt");       // Crea un archivo temporal "temp.txt" en modo escritura

    if (!archivo_original.is_open() || !archivo_temporal.is_open()) {
        cerr << "No se pudo abrir uno de los archivos." << endl;
        return;
    }

    string linea, id, id_cancion;
    bool eliminar = false;

    cout << "Ingresa el ID de la cancion a eliminar: ";
    cin >> id;

    // Lee cada línea del archivo original
    while (getline(archivo_original, linea)) {
        if (linea.find("ID de la cancion: ") == 0) { //find es para saber si estamoss en una linea que contiene ese texto desde posicion 0
            id_cancion = linea.substr(18); // Obtener el ID de la canción a partir de la posición 18
            eliminar = (id_cancion == id); // Verificar si es la canción a eliminar
        }

        // Si no es la canción a eliminar, escribe la línea en el archivo temporal
        if (!eliminar) {
            archivo_temporal << linea << endl;
        }

        // Si se llega a una línea en blanco, se termina el bloque de la canción
        if (linea.empty()) {
            eliminar = false; // Reiniciar la variable para la siguiente canción
        }
    }

    archivo_original.close();  // Cierra el archivo original
    archivo_temporal.close();  // Cierra el archivo temporal

    // Renombra el archivo temporal al nombre original
    if (remove("C:/Users/user/Desktop/canciones.txt") != 0) {  //si retorna un valor diferente de cero hubo un error
        perror("Error eliminando el archivo original");
    }

    if (rename("C:/Users/user/Desktop/temp.txt", "C:/Users/user/Desktop/canciones.txt") != 0) {  //renombra nuevamente el archivo al original
        perror("Error renombrando el archivo temporal");
    }

    cout << "Cancion eliminada correctamente." << endl;  // Muestra un mensaje
}


int main() {
    int v, s;
    string r,t;
    int opcion;
    cancion* cancion = nullptr;


    do {
        // Mostrar el menú
        cout << "Menu:" << endl;
        cout << "1. insertar canciones" << endl;
        cout << "2. imprimir canciones" << endl;
        cout << "3. leer archivo de canciones" << endl;
        cout << "4. imprimir usuarios" << endl;
        cout << "5. agregar usuarios" << endl;
        cout << "6. agregar canciones" << endl;
        cout << "7. eliminar usuarios" << endl;
        cout << "8. eliminar canciones" << endl;
        cout << "0. Salir" << endl;
        cout << "Selecciona una opcion: " << endl;
        
        // Leer la opción del usuario
        cin >> opcion;
        
        // Procesar la opción seleccionada
        switch (opcion) {
            case 1: {
                string r = "si";
                int id;
                string nombre;
                string artista;
                string genero;
                int anio;

                while (r == "si") {
                    cout << "inserta el id de la cancion: ";
                    cin >> id;
                    cout << "inserta el nombre de la cancion: ";
                    cin >> nombre;
                    cout << "inserta el artista de la cancion: ";
                    cin >> artista;
                    cout << "inserta el genero de la cancion: ";
                    cin >> genero;
                    cout << "inserta el anio de la cancion: ";
                    cin >> anio;
                    insertar_cancion(cancion, id, nombre, artista, genero, anio);
                    cout << "¿quieres insertar otra cancion? (si/no): ";
                    cin >> r;
                }
                break;
            }
            case 2:
                imprimir_canciones(cancion);
                break;

            case 3:
                leer_archivo_canciones();
            break;

            case 4:
                leer_archivo_personas();
            break;

            case 5:
                r = "si";
                while (r == "si") {
                    agregar_usuarios();
                    cout << "¿Quieres agregar otro usuario? (si/no): ";
                    cin >> r;
                }
                break;

            case 6:
                t = "si";
                while(t == "si"){
                    agregar_canciones();
                    cout << "quieres agregar otra cancion? (si/no): ";
                    cin >> t;

                }
                break;    

            case 7:
                eliminar_usuarios();
                break;

            case 8:
                eliminar_canciones();
                break;

            break;
            case 0: {
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
            }
                
        }

    } while (opcion != 0);

    return 0;
} 