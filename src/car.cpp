#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <filesystem>
#include <sstream>
#include "./view/clientsMenu.h" 
#include "./view/partsMenu.h" 
#include "./view/vehiclesMenu.h"

namespace fs = std::filesystem;

using namespace std;

string obtenerRutaCompleta(const string& rutaRelativa) {
    fs::path p = fs::current_path();
    return (p / rutaRelativa).string();
}

void crearCopiaDeSeguridad(const string& rutaArchivoOriginal) {
    if (!fs::exists(rutaArchivoOriginal)) {
        cout << "El archivo original no existe: " << rutaArchivoOriginal << endl;
        return;
    }

    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    struct tm buf;
    localtime_r(&in_time_t, &buf);

    stringstream fechaArchivo;
    fechaArchivo << put_time(&buf, "%Y-%m-%d_%H-%M-%S");

    string nombreBackup = "./backups/" + fechaArchivo.str() + "_" + fs::path(rutaArchivoOriginal).filename().string();

    if (!fs::exists("./backups")) {
        fs::create_directory("./backups");
    }

    try {
        fs::copy(rutaArchivoOriginal, nombreBackup);
        cout << "Copia de seguridad creada exitosamente: " << nombreBackup << endl;
    } catch (const fs::filesystem_error& e) {
        cout << "Error al crear la copia de seguridad: " << e.what() << endl;
    }
}

int main() {
    int opcionPrincipal;

    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "Ingrese 1 para ir al menu de Clientes\n";
        cout << "Ingrese 2 para ir al menu de Repuestos\n";
        cout << "Ingrese 3 para ir al menu de Vehiculos\n";
        cout << "Ingrese 4 para administrar usuarios\n";
        cout << "Ingrese 5 para crear una copia de seguridad\n";
        cout << "Ingrese 0 para salir del programa\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1: {
                MenuClientes menuClientes;
                menuClientes.iniciarMenu();
                break;
            }
            case 2: {
                MenuRepuestos menuRepuestos;
                menuRepuestos.iniciarMenu();
                break;
            }
            case 3: {
                VehiclesMenu menuVehiculos;
                menuVehiculos.iniciarMenuVehiculos();
                break;
            }
            case 4: {
                MenuUsuarios menuUsuarios;
                menuUsuarios.iniciarMenu();
            }
            case 5: {
                string archivo;
                cout << "Ingrese la ruta completa del archivo que desea respaldar: ";
                cin >> archivo;
                crearCopiaDeSeguridad(archivo);
                break;
            }
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    } while (opcionPrincipal != 0);

    return 0;
}
