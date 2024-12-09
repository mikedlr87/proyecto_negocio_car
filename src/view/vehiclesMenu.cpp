#include<iostream>
#include<../controller/vehiclesController.h>

using namespace std;

    manejoVehiculo gestionVehiculo;
    


 if (eleccion == 1) {
            int opcionVehiculo;
            do {
                cout << "\nque desea hacer con los vehiculos";
                cout << "\ningrese 1 para mostrar vehiculos test";
                cout << "\ningrese 2 para agregar un vehiculo";
                cout << "\ningrese 3 para editar un vehiculo por placa";
                cout << "\ningrese 4 para eliminar un vehiculo por placa";
                cout << "\ningrese 5 para GUARDAR CAMBIOS";
                cout << "\ningrese 6 para consultas";
                cout << "\ningrese 0 para Volver al menu principal\n";
                cin >> opcionVehiculo;

                switch (opcionVehiculo) {
                    case 1:
                        gestionVehiculo.mostrarVehiculo();
                        break;
                    case 2:
                        gestionVehiculo.agregarVehiculo();
                        break;
                    case 3: {
                        string placa;
                        cout << "Ingrese la placa del vehiculo a editar: ";
                        cin >> placa;
                        gestionVehiculo.editarVehiculoPorPlaca(placa);
                        break;
                    }
                    case 4: {
                        string placa;
                        cout << "Ingrese la placa del vehiculo a eliminar: ";
                        cin >> placa;
                        gestionVehiculo.eliminarVehiculoPorPlaca(placa);
                        break;
                    }
                    case 5: {
                        gestionVehiculo.guardarCambiosVehiculos();
                        cout << "\nCambios guardados\n";
                        break;
                    }
                    case 6:
                        gestionVehiculo.mostrarConsultas();
                        break;
                    case 0:
                        cout << "Volviendo al menu principal\n";
                        break;
                    default:
                        cout << "Opcion invalida, intente otra vez.\n";
                        break;
                }
            } while (opcionVehiculo != 0);