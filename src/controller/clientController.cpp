#include<iostream>
#include <../model/client.cpp>

using namespace std;

class manejoClientes{
    public:

    manejoClientes():numClientes (0){   
        cargarClientes();
    }

    void cargarClientes(){
        ifstream file("../bin/client.csv");
        string line;

        (getline(file,line));

        while (getline(file,line) && numClientes < maxClientes){
            istringstream row(line);
            Cliente& cliente = clientes[numClientes];
            string temp;

            getline(row, temp, ',');
            cliente.ced_cliente = (!temp.empty() ? stoi(temp) : 0);
            getline(row, cliente.nombre, ',');
            getline(row, cliente.apellido, ',');
            getline(row, cliente.e_mail, ',');
            getline(row, temp, ',');
            cliente.cantidad_vehiculos_rentados = (!temp.empty() ? stoi(temp) : 0);
            getline(row, cliente.direccion, ',');
            getline(row, temp, ',');
            cliente.activo = (temp=="true");

            numClientes++;
            }
        file.close();            
    };


        void mostrarClientes() const {
            for (int i=0; i<numClientes; ++i) {
                const Cliente& cli = clientes[i];
                cout << i + 1 << ". Cedula: " << cli.ced_cliente
                    << ", Nombre: " << cli.nombre << " " << cli.apellido
                    << ", Email: " << cli.e_mail << ", Vehiculos rentados: "
                    << cli.cantidad_vehiculos_rentados << ", Direccion: " << cli.direccion
                    << ", Activo: " << (cli.activo ? "si":"no") << "\n";
            }
        }

        int buscarClientePorCedula(const int cedula) const {
            for (int i = 0; i < numClientes; ++i) {
                if (clientes[i].ced_cliente == cedula) {
                    return i;
                }
            }
            return -1;
        }

        void agregarCliente() {
            if (numClientes >= maxClientes) {
                cout << "No se pueden agregar mas clientes\n";
                return;
            }

            int ced_cliente;
            cout << "Cedula del nuevo cliente a ingresar:\n";
            cin >> ced_cliente;

            if (buscarClientePorCedula(ced_cliente) != -1) {
                cout << "Ya existe un cliente con esa cedula.\n";
                return;
            }

            Cliente& cli = clientes[numClientes];
            cout << "Ingrese los datos del nuevo cliente:\n";
            cout << "Nombre: "; cin >> cli.nombre;
            cout << "Apellido: "; cin >> cli.apellido;
            cout << "Email: "; cin >> cli.e_mail;
            cout << "Cantidad de vehiculos rentados: "; cin >> cli.cantidad_vehiculos_rentados;
            cout << "Direccion: "; cin >> cli.direccion;
            cout << "Activo (1 = si, 0 = no): "; cin >> cli.activo;

            numClientes++;
            cout << "Se agrego el cliente con exito.\n";
        }

        void editarClientePorCedula(const int cedula) {
            int index = buscarClientePorCedula(cedula);
            if (index == -1) {
                cout << "No se encontro el cliente con la cedula " << cedula << endl;
                return;
            }

            Cliente& cli = clientes[index];
            int opcion;
            do {
                cout << "\nIngrese que desea editar: \n";
                cout << "1 para nombre\n2 para apellido\n3 para e-mail\n4 para cantidad de vehiculos rentados\n5 para direccion\n";
                cout << "6 para cambiar el estado activo\n0 para volver al menu anterior\n";
                cin >> opcion;

                switch (opcion) {
                    case 1: cout << "Nuevo nombre: "; cin >> cli.nombre; break;
                    case 2: cout << "Nuevo apellido: "; cin >> cli.apellido; break;
                    case 3: cout << "Nuevo e-mail: "; cin >> cli.e_mail; break;
                    case 4: cout << "Nueva cantidad de vehiculos rentados: "; cin >> cli.cantidad_vehiculos_rentados; break;
                    case 5: cout << "Nueva direccion: "; cin >> cli.direccion; break;
                    case 6:
                        cout << "Activo (1 = si, 0 = no): ";
                        int activo;
                        cin >> activo;
                        cli.activo = activo;
                        break;
                    case 0: cout << "Ha terminado de editar.\n"; break;
                    default: cout << "Eleccion invalida.\n"; break;
                }
            } while (opcion != 0);
}

        void eliminarClientePorCedula(const int cedula) {
            int index = buscarClientePorCedula(cedula);
            if (index != -1) {
                for (int i = index; i < numClientes - 1; ++i) {
                    clientes[i] = clientes[i + 1];
                }
                numClientes--;
                cout << "Se elimino el cliente con la cédula " << cedula << endl;
            } else {
                cout << "No se encontro el cliente con la cedula " << cedula << endl;
            }
        }

        void guardarCambiosClientes() const{
            ofstream file("../bin/client.csv");
            file <<"ced_cliente,nombre,apellido,e_mail,cantidad_vehiculos_rentados,direccion,activo\n";
            for (int i = 0; i < numClientes; ++i) {
                const Cliente& cli = clientes[i];
                file << cli.ced_cliente << ',' << cli.nombre << ',' << cli.apellido << ',' << cli.e_mail << ',' 
                    << cli.cantidad_vehiculos_rentados << ',' << cli.direccion << ',' << (cli.activo ? "true" : "false") << '\n';
                }
            file.close();
        }


            void mostrarConsultas() {
            int opcionConsulta;
            do {
                cout << "\nConsultas de informacion sobre clientes, ingrese lo siguiente\n";
                cout << "1 para mostrar informacion de cliente por cedula\n";
                cout << "2 para mostrar clientes registrados\n";
                cout << "3 para mostrar el total de vehiculos rentados\n";
                cout << "0 volver al menu anterior\n";
                cin >> opcionConsulta;

                switch (opcionConsulta) {
                    case 1: {
                        int cedula;
                        cout << "Ingrese la cedula del cliente: ";
                        cin >> cedula;
                        mostrarClientePorCedula(cedula);
                        break;
                    }
                    case 2: {
                        mostrarClientesRegistrados();
                        break;
                    }
                    case 3: {
                        mostrarVehiculosRentadosTotales();
                        break;
                    }
                    case 0:
                        cout << "Volviendo al menu anterior\n";
                        break;
                    default:
                        cout << "Opcion invalida\n";
                        break;
                }
            } while (opcionConsulta != 0);
        }

        void mostrarClientePorCedula(int ced_cliente) const {
            for (int i = 0; i < numClientes; ++i) {
                if (clientes[i].ced_cliente == ced_cliente) {
                    cout << "Cliente encontrado: " << endl;
                    cout << "Cédula: " << clientes[i].ced_cliente << ", Nombre: " << clientes[i].nombre << ", Direccion: " << clientes[i].direccion << "\n";
                    return;
                }
            }
            cout << "Cliente con cedula " << ced_cliente << " no encontrado.\n";
        }

        void mostrarClientesRegistrados() const {
            for (int i = 0; i < numClientes; ++i) {
                cout << "Cliente: " << clientes[i].nombre << ", Cedula: " << clientes[i].ced_cliente << "\n";
            }
        }

        void mostrarVehiculosRentadosTotales() const {
            int totalVehiculosRentados = 0;
            
            for (int i = 0; i < numClientes; ++i) {
                totalVehiculosRentados += clientes[i].cantidad_vehiculos_rentados;
            }
            cout << "Hay un total de " << totalVehiculosRentados << " vehiculos rentados" << endl;
        }


    private:
    Cliente clientes[maxClientes];
    int numClientes;
};