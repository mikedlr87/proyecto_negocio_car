#include<iostream>
#include<../controller/partsController.cpp>

using namespace std;

    manejoRepuestos gestionRepuesto;

  } else if (eleccion == 3) {
            int opcionRepuesto;
            do {
                cout << "\nque desea hacer con los repuestos:\n";
                cout << "ingrese 1 para mostrar repuestos\n";
                cout << "ingrese 2 para agregar un repuesto\n";
                cout << "ingrese 3 para editar un repuesto por nombre\n";
                cout << "ingrese 4 para eliminar un repuesto por nombre\n";
                cout << "ingrese 5 para GUARDAR CAMBIOS\n";
                cout << "ingrese 6 para consultas\n";
                cout << "ingrese 0 para Volver al menu principal\n";
                cin >> opcionRepuesto;

                switch (opcionRepuesto) {
                    case 1:
                        gestionRepuesto.mostrarRepuestos();
                        break;
                    case 2:
                        gestionRepuesto.agregarRepuesto();
                        break;
                    case 3: {
                        string nombre;
                        cout << "Ingrese el nombre del repuesto a editar: ";
                        cin >> nombre;
                        gestionRepuesto.editarRepuesto(nombre);
                        break;
                    }
                    case 4: {
                        string nombre;
                        cout << "Ingrese el nombre del repuesto a eliminar: ";
                        cin >> nombre;
                        gestionRepuesto.eliminarRepuesto(nombre);
                        break;
                    }
                    case 5: {
                        gestionRepuesto.guardarCambiosRepuestos();
                        cout << "\nCambios guardados\n";
                        break;
                    }
                    case 6:
                        gestionRepuesto.mostrarConsultas();
                        break;
                    case 0:
                        cout << "Volviendo al menu principal\n";
                        break;
                    default:
                        cout << "Opcion invalida, intente otra vez.\n";
                        break;
                }
            } while (opcionRepuesto != 0);
        } else if (eleccion == 0) {
            cout << "Saliendo del programa\n";
        } else {
            cout << "Opcion invalida\n";
        }
    } while (eleccion != 0);