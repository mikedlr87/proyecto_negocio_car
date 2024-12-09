#include <iostream>
#include "../controller/clientController.h"

using namespace std;

int main() {
    int eleccion;
    do {
            manejoClientes gestionClientes;
            int opcionCliente;
            do {
                cout << "\nQue desea hacer con los clientes\n";
                cout << "Ingrese 1 para mostrar clientes\n";
                cout << "Ingrese 2 para agregar un cliente\n";
                cout << "Ingrese 3 para editar un cliente por cedula\n";
                cout << "Ingrese 4 para eliminar un cliente por cedula\n";
                cout << "Ingrese 5 para GUARDAR CAMBIOS\n";
                cout << "Ingrese 6 para consultas\n";
                cout << "Ingrese 0 para volver al menu principal\n";
                cin >> opcionCliente;

                switch (opcionCliente) {
                    case 1:
                        gestionClientes.mostrarClientes();
                        break;
                    case 2:
                        gestionClientes.agregarCliente();
                        break;
                    case 3: {
                        int cedula;
                        cout << "Ingrese la cédula del cliente que se editará: ";
                        cin >> cedula;
                        gestionClientes.editarClientePorCedula(cedula);
                        break;
                    }
                    case 4: {
                        int cedula;
                        cout << "Ingrese la cédula del cliente que se eliminará: ";
                        cin >> cedula;
                        gestionClientes.eliminarClientePorCedula(cedula);
                        break;
                    }
                    case 5:
                        gestionClientes.guardarCambiosClientes();
                        cout << "\nCambios guardados\n";
                        break;
                    case 6:
                        gestionClientes.mostrarConsultas();
                        break;
                    case 0:
                        cout << "Volviendo al menú anterior\n";
                        break;
                    default:
                        cout << "Opción inválida\n";
                        break;
                }
            } while (opcionCliente != 0);
        }
     while (eleccion != 0);

    return 0;
}
