#include<iostream>
#include<../model/vehicle.cpp>

using namespace std;

class manejoVehiculo{
public:

    manejoVehiculo():numVehiculos (0){
        cargarVehiculos();
    }

    void cargarVehiculos(){
        ifstream file("../bin/vehicle.csv");
        string line;

        getline(file,line);

            while (getline(file,line) && numVehiculos < maxVehiculos){
            istringstream row(line);
            Vehiculo& vehiculo = vehiculos[numVehiculos];
            string temp;

            getline(row, vehiculo.modelo, ',');
            getline(row, vehiculo.marca, ',');
            getline(row, vehiculo.placa, ',');
            getline(row, vehiculo.color, ',');
            getline(row, temp, ',');
            vehiculo.anio = (!temp.empty() ? stoi(temp) : 0);
            getline(row, temp, ',');
            vehiculo.kilometraje = (!temp.empty() ? stoi(temp) : 0);
            //booleano
            getline(row, temp, ',');
            vehiculo.rentado = (temp=="true");
            getline(row, vehiculo.motor, ',');
            getline(row, temp, ',');
            vehiculo.precio_renta = (!temp.empty() ? stoi(temp) : 0);
            getline(row, temp, ',');
            vehiculo.cedula_cliente = (!temp.empty() ? stoi(temp) : 0);
            getline(row, vehiculo.fecha_de_entrega, ',');

            numVehiculos++;
            }

        file.close();
    }

    void mostrarVehiculo() const {
        for (int i=0; i<numVehiculos; ++i){
            const Vehiculo& veh = vehiculos[i];
            cout<< i + 1 <<". Modelo: " << veh.modelo <<", Marca: "<< veh.marca
            <<", Placa: "<<veh.placa<<", Color: "<<veh.color<<", Anio: "<<veh.anio<<", Kilometraje: "
            <<veh.kilometraje<<", Rentado:" <<(veh.rentado ? "si":"no")<<", Motor: "
            <<veh.motor<<", Precio renta: "<<veh.precio_renta <<" , Fecha de entrega:" <<veh.fecha_de_entrega<<"\n";
        }
    }

        int buscarVehiculoPorPlaca(const string& placa) const {
        for (int i = 0; i < numVehiculos; ++i) {
            if (vehiculos[i].placa == placa) {
                return i;
            }
        }
        return -1;
    }

    void eliminarVehiculoPorPlaca(const string& placa) {
        int index = buscarVehiculoPorPlaca(placa);
        if (index != -1) {
            for (int i = index; i < numVehiculos - 1; ++i) {
                vehiculos[i] = vehiculos[i + 1];
            }
            numVehiculos--;
            cout << "Se elimino el vehiculo de placa\n " << placa;
        } else {
            cout << "No se encontro el vehiculo de placa\n " << placa;
        }
    }

    void editarVehiculoPorPlaca(const string& placa) {
        int index = buscarVehiculoPorPlaca(placa);
        if (index == -1) {
            cout << "No se encontro el vehiculo de placa\n " << placa;
            return;
        }

        Vehiculo& veh = vehiculos[index];
        int opcion;
        do {
            cout << "\nIngrese que desea editar: \n";
            cout << "1 para modelo\n2 para marca\n3 para color\n4 para anio\n5 para kilometraje\n";
            cout << "6 para rentado\n7 para motor\n8 para precio de renta\n9 para cedula del cliente\n10 para la fecha de entrega\n";
            cout << "0 Para ir al menu anterior\n";
            cin >> opcion;

            switch (opcion) {
                case 1: cout << "Nuevo modelo: "; cin >> veh.modelo; break;
                case 2: cout << "Nueva marca: "; cin >> veh.marca; break;
                case 3: cout << "Nuevo color: "; cin >> veh.color; break;
                case 4: cout << "Nuevo anio: "; cin >> veh.anio; break;
                case 5: cout << "Nuevo kilometraje: "; cin >> veh.kilometraje; break;
                case 6:
                    cout << "Rentado (1 = si, 0 = no): ";
                    int rentado;
                    cin >> rentado;
                    veh.rentado = rentado;
                    break;
                case 7: cout << "Nuevo motor: "; cin >> veh.motor; break;
                case 8: cout << "Nuevo precio de renta: "; cin >> veh.precio_renta; break;
                case 9: cout << "Nueva cedula del cliente: "; cin >> veh.cedula_cliente; break;
                case 10: cout << "Nueva fecha de entrega: "; cin >> veh.fecha_de_entrega; break;
                case 0: cout << "Ha terminado de editar.\n"; break;
                default: cout << "Eleccion invalida.\n";
            }
        } while (opcion != 0);
    }

    void agregarVehiculo() {
        if (numVehiculos >= maxVehiculos) {
            cout << "No se pueden agregar mas vehiculos\n";
            return;
        }

            string placa;
            cout << "Placa del nuevo vehiculo:\n";
            cin >> placa;

            if (buscarVehiculoPorPlaca(placa) != -1) {
                cout << "El vehiculo con esta placa ya existe.\n";
                return;
            }

        Vehiculo& veh = vehiculos[numVehiculos];
        cout << "Ingrese los datos del nuevo vehiculo:\n";
        cout << "Modelo: "; cin >> veh.modelo;
        cout << "Marca: "; cin >> veh.marca;
        cout << "Color: "; cin >> veh.color;
        cout << "Anio: "; cin >> veh.anio;
        cout << "Kilometraje: "; cin >> veh.kilometraje;
        cout << "Rentado (1 = si, 0 = no): ";
        int rentado;
        cin >> rentado;
        veh.rentado = rentado;
        cout << "Motor: "; cin >> veh.motor;
        cout << "Precio de renta: "; cin >> veh.precio_renta;
        cout << "Cedula del cliente: "; cin >> veh.cedula_cliente;
        cout << "Fecha de entrega: "; cin >> veh.fecha_de_entrega;
        numVehiculos++;
        cout << "Vehiculo agregado con exito.\n";
    }
    
    void guardarCambiosVehiculos() const{
        ofstream file("../bin/vehicle.csv");
        file <<"modelo,marca,placa,color,anio,kilometraje,rentado,motor,precio_renta,ced_cliente,fecha_entrega\n";
        for (int i=0; i<numVehiculos; ++i){
            const Vehiculo& veh = vehiculos[i];
            file << veh.modelo <<','<< veh.marca
            <<','<<veh.placa<<','<<veh.color<<','<<veh.anio<<','
            <<veh.kilometraje<<','<<(veh.rentado ? "true":"false")<<','
            <<veh.motor<<','<<veh.precio_renta <<','<<veh.cedula_cliente <<',' <<veh.fecha_de_entrega<<'\n';
        }
        file.close();
    }


    void mostrarConsultas() {
    int opcionConsulta;
    do {
        cout << "\nElija una consulta de informacion que necesite:\n";
        cout << "1 para informacion de un vehiculo insertando su placa \n";
        cout << "2 para mostrar modelos disponibles \n";
        cout << "3 para mostrar precios de vehiculos \n";
        cout << "0 para volver al menu anterior\n";
        cin >> opcionConsulta;

        switch (opcionConsulta) {
            case 1: {
                string placa;
                cout << "Ingrese la placa del vehiculo: ";
                cin >> placa;
                mostrarVehiculoPorPlaca(placa);
                break;
            }
            case 2: {
                mostrarModelosDisponibles();
                break;
            }
            case 3: {
                mostrarPrecioVehiculo();
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

    void mostrarVehiculoPorPlaca(const string& placa) const {
        for (int i = 0; i < numVehiculos; ++i) {
            if (vehiculos[i].placa == placa) {
                cout << "La informacion del vehiculo segun su matricula es la siguiente " << endl;
                cout << "Placa: " << vehiculos[i].placa << ", Modelo: " << vehiculos[i].modelo << ", Marca: " << vehiculos[i].marca << "\n";
                return;
            }
        }
        cout << "Vehículo con placa " << placa << " no encontrado.\n";
    }

    void mostrarModelosDisponibles() const {
        for (int i = 0; i < numVehiculos; ++i) {
            if (vehiculos[i].rentado) {
                cout << "Modelo disponible: " << vehiculos[i].modelo << ", Marca: " << vehiculos[i].marca << "\n";
            }
        }
    }

        void mostrarPrecioVehiculo() const {
        for (int i=0; i<numVehiculos; ++i){
            const Vehiculo& veh = vehiculos[i];
            cout<< i + 1 <<", marca: "<<veh.marca<< ", precio renta: "<<veh.precio_renta<< ", placa: "<<veh.placa<<"\n";
        }
    }

private:
    Vehiculo vehiculos[maxVehiculos];
    int numVehiculos;
};

const int maxClientes = 100;