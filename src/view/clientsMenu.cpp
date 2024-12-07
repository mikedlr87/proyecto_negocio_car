#include<iostream>
#include<../controller/clientController.cpp>
using namespace std;

    manejoClientes gestionClientes;

} else if (eleccion == 2) {
            int opcionCliente;
            do {
                cout << "\nque desea hacer con los clientes\n";
                cout << "ingrese 1 para mostrar clientes\n";
                cout << "ingrese 2 para agregar un cliente\n";
                cout << "ingrese 3 para editar un cliente por cedula\n";
                cout << "ingrese 4 para eliminar un cliente por cedula\n";
                cout << "ingrese 5 para GUARDAR CAMBIOS\n";
                cout << "ingrese 6 para consultas\n";
                cout << "ingrese 0 para Volver al menu principal\n";
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
                        cout << "Ingrese la cedula del cliente que se editara: ";
                        cin >> cedula;
                        gestionClientes.editarClientePorCedula(cedula);
                        break;
                    }
                    case 4: {
                        int cedula;
                        cout << "Ingrese la cedula del cliente que se eliminara: ";
                        cin >> cedula;
                        gestionClientes.eliminarClientePorCedula(cedula);
                        break;
                    }
                    case 5: {
                        gestionClientes.guardarCambiosClientes();
                        cout << "\nCambios guardados \n";
                        break;
                    }
                    case 6: 
                        gestionClientes.mostrarConsultas();
                        break;
                    case 0:
                        cout << "Volviendo al menu anterior\n";
                        break;
                    default:
                        cout << "Opcion invalida\n";
                        break;
                }
            } while (opcionCliente != 0);