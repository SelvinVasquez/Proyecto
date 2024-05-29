#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdio>
using namespace std;
namespace fs = std::filesystem;

void crearArchivo() {
    string directorio, nombreArchivo, contenido;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);
    string rutaArchivo = directorio + '/' + nombreArchivo;
    cout << "Ingrese el contenido del archivo:" << endl;
    getline(cin, contenido);
    ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        archivo << contenido << endl;
        archivo.close();
        cout << "Archivo creado exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void leerArchivo() {
    string directorio, nombreArchivo;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);
    string rutaArchivo = directorio + '/' + nombreArchivo;
    ifstream archivoEntrada(rutaArchivo);
    if (archivoEntrada.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
            cout << linea << endl;
        }
        archivoEntrada.close();
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}

void escribirArchivo() {
    string directorio, nombreArchivo, contenido;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);
    string rutaArchivo = directorio + '/' + nombreArchivo;
    ofstream archivo(rutaArchivo, ios::app);
    if (archivo.is_open()) {
        cout << "Ingrese el contenido que desea agregar al archivo:" << endl;
        getline(cin, contenido);
        archivo << contenido << endl;
        archivo.close();
        cout << "Contenido agregado al archivo exitosamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo para escritura." << endl;
    }
}

void listarArchivosCreados(const string& directorio) {
    cout << "Archivos creados en el directorio '" << directorio << "':" << endl;
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file()) {
            cout << entry.path().filename() << endl;
        }
    }
}

void verContenidoArchivos() {
    int numArchivos;
    string directorio, nombreArchivo;
    cout << "Ingrese el directorio de los archivos: ";
    getline(cin, directorio);
    cout << "¿Cuántos archivos desea ver?: ";
    cin >> numArchivos;
    cin.ignore(); // Limpiar el buffer de entrada
    vector<string> archivos;
    archivos.clear(); // Limpiamos la lista de archivos
    for (int i = 0; i < numArchivos; ++i) {
        cout << "Ingrese el nombre del archivo " << i + 1 << ": ";
        getline(cin, nombreArchivo);
        archivos.push_back(directorio + '/' + nombreArchivo);
    }
    for (const auto& archivo : archivos) {
        cout << "Contenido del archivo '" << archivo << "':" << endl;
        ifstream archivoEntrada(archivo);
        if (archivoEntrada.is_open()) {
            string linea;
            while (getline(archivoEntrada, linea)) {
                cout << linea << endl;
            }
            archivoEntrada.close();
        } else {
            cout << "No se pudo abrir el archivo para lectura." << endl;
        }
        cout << "------------------------------------------" << endl;
    }
}

void moverArchivo() {
    string directorio, nombreArchivo, directorio2;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);
    string rutaArchivo = directorio + '/' + nombreArchivo;
    cout << "Ingrese el nuevo directorio del archivo: ";
    getline(cin, directorio2);
    string rutaArchivo2 = directorio2 + '/' + nombreArchivo;
    const string& ruta_antiguo = rutaArchivo;
    const string& ruta_nuevo = rutaArchivo2;
    if (rename(ruta_antiguo.c_str(), ruta_nuevo.c_str()) == 0) {
        cout << "Archivo movido exitosamente a nueva ruta " << ruta_nuevo << "." << endl;
    } else {
        cout << "Error al intentar mover el archivo. Verifique el nombre y la ruta." << endl;
    }
}

void eliminarArchivo() {
    string directorio, nombreArchivo;
    cout << "Ingrese el directorio del archivo: ";
    getline(cin, directorio);
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);
    string rutaArchivo = directorio + '/' + nombreArchivo;
    if (remove(rutaArchivo.c_str()) != 0) {
        cout << "Error al intentar eliminar el archivo." << endl;
    } else {
        cout << "Archivo eliminado exitosamente." << endl;
    }
}

void copiarArchivo(const string& rutaOrigen, const string& rutaDestino) {
    if (fs::exists(rutaOrigen) && fs::is_regular_file(rutaOrigen)) {
        fs::copy(rutaOrigen, rutaDestino, fs::copy_options::overwrite_existing);
        cout << "Archivo copiado exitosamente de " << rutaOrigen << " a " << rutaDestino << "." << endl;
    } else {
        cout << "El archivo de origen no existe o no es un archivo regular." << endl;
    }
}

void mostrarDetallesArchivo(const string& rutaArchivo) {
    if (fs::exists(rutaArchivo) && fs::is_regular_file(rutaArchivo)) {
        fs::path pathObj(rutaArchivo);
        cout << "Detalles del archivo " << rutaArchivo << ":" << endl;
        cout << "Directorio: " << pathObj.parent_path().string() << endl;
        cout << "Tamaño: " << fs::file_size(rutaArchivo) << " bytes" << endl;
    } else {
        cout << "El archivo no existe o no es un archivo regular." << endl;
    }
}

void renombrarArchivo(const string& rutaArchivo, const string& nuevoNombre) {
    fs::path pathObj(rutaArchivo);
    if (fs::exists(pathObj) && fs::is_regular_file(pathObj)) {
        fs::path nuevoPath = pathObj.parent_path() / nuevoNombre;
        fs::rename(pathObj, nuevoPath);
        cout << "Archivo renombrado exitosamente de " << rutaArchivo << " a " << nuevoPath << "." << endl;
    } else {
        cout << "El archivo no existe o no es un archivo regular." << endl;
    }
}
void buscarPalabraEnArchivos(const vector<string>& archivos, const string& palabra) {
    for (const auto& archivo : archivos) {
        ifstream archivoEntrada(archivo);
        if (archivoEntrada.is_open()) {
            string linea;
            cout << "Buscando en el archivo: " << archivo << endl;
            bool encontrado = false;
            while (getline(archivoEntrada, linea)) {
                if (linea.find(palabra) != string::npos) {
                    if (!encontrado) {
                        cout << "Líneas que contienen la palabra \"" << palabra << "\":" << endl;
                        encontrado = true;
                    }
                    cout << linea << endl;
                }
            }
            if (!encontrado) {
                cout << "No se encontró la palabra \"" << palabra << "\" en el archivo " << archivo << "." << endl;
            }
            archivoEntrada.close();
        } else {
            cout << "No se pudo abrir el archivo " << archivo << " para lectura." << endl;
        }
        cout << "------------------------------------------" << endl;
    }
}
int main() {
    int opcion;
    do {
        cout << "Seleccione una opción:" << endl;
        cout << "1. Crear archivo" << endl;
        cout << "2. Leer archivo" << endl;
        cout << "3. Escribir en archivo" << endl;
        cout << "4. Listar archivos creados" << endl;
        cout << "5. Ver contenido de varios archivos" << endl;
        cout << "6. Mostrar detalles de archivo" << endl;
        cout << "7. Mover un archivo" << endl;
        cout << "8. Renombrar archivo" << endl;
        cout << "9. Copiar archivo" << endl;
        cout << "10. Eliminar un archivo" << endl;
        cout << "11. Buscar palabra en varios archivos" << endl;
        cout << "12. Salir" << endl;
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada
        switch (opcion) {
            case 1:
                crearArchivo();
                break;
            case 2:
                leerArchivo();
                break;
            case 3:
                escribirArchivo();
                break;
            case 4: {
                string directorio;
                cout << "Ingrese el directorio para listar archivos creados: ";
                getline(cin, directorio);
                listarArchivosCreados(directorio);
                break;
            }
            case 5:
                verContenidoArchivos();
                break;
            case 6: {
                string rutaArchivo;
                cout << "Ingrese la ruta del archivo para mostrar detalles: ";
                getline(cin, rutaArchivo);
                mostrarDetallesArchivo(rutaArchivo);
                break;
            }
            case 7:
                moverArchivo();
                break;
            case 8: {
                string rutaArchivo, nuevoNombre;
                cout << "Ingrese la ruta del archivo a renombrar: ";
                getline(cin, rutaArchivo);
                cout << "Ingrese el nuevo nombre para el archivo: ";
                getline(cin, nuevoNombre);
                renombrarArchivo(rutaArchivo, nuevoNombre);
                break;
            }
            case 9: {
                string rutaOrigen, rutaDestino;
                cout << "Ingrese la ruta del archivo a copiar: ";
                getline(cin, rutaOrigen);
                cout << "Ingrese la ruta de destino: ";
                getline(cin, rutaDestino);
                copiarArchivo(rutaOrigen, rutaDestino);
                break;
            }
            case 10:
                eliminarArchivo();
                break;
            case 11: {
                int numArchivos;
                string directorio, nombreArchivo, palabra;
                cout << "Ingrese el directorio de los archivos: ";
                getline(cin, directorio);
                cout << "¿Cuántos archivos desea buscar?: ";
                cin >> numArchivos;
                cin.ignore(); // Limpiar el buffer de entrada
                vector<string> archivos;
                for (int i = 0; i < numArchivos; ++i) {
                    cout << "Ingrese el nombre del archivo " << i + 1 << ": ";
                    getline(cin, nombreArchivo);
                    archivos.push_back(directorio + '/' + nombreArchivo);
                }
                cout << "Ingrese la palabra clave a buscar: ";
                getline(cin, palabra);
                buscarPalabraEnArchivos(archivos, palabra);
                break;
            }
            case 12:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }

        if (opcion != 12) {
            char continuar;
            cout << "¿Desea realizar otra operación? (s/n): ";
            cin >> continuar;
            cin.ignore(); // Limpiar el buffer de entrada
            if (continuar != 's') {
                break;
            }
        }
    } while (opcion != 12);
    return 0;
}