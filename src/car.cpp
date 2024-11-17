#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

struct Vehiculo {
        string placa;
        string modelo;
        string marca;
        string color;
        int anio;
        int kilometraje;
        bool rentado;
        string motor;
        int precio_renta;
        int cedula_cliente;
        string fecha_de_entrega;
}; 

//hacer la estructura del cliente
struct Cliente {
    int ced_cliente;
    string nombre;
    string apellido;
    string e_mail;
    int cantidad_vehiculos_rentados;
    string direccion;
    bool activo;    
}; 

struct Repuesto {
    string modelo;
    string marca;
    string nombre;
    string modelo_carro;
    int anio_carro;
    float precio;
    bool existencia;
};


const int maxVehiculos = 100;

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

const int maxRepuestos = 100;

class manejoRepuestos {
public:
    manejoRepuestos() : numRepuestos(0) {
        cargarRepuestos();
    }

    void cargarRepuestos() {
        ifstream file("../bin/parts.csv");
        string line;

        getline(file, line);

        while (getline(file, line) && numRepuestos < maxRepuestos) {
            istringstream row(line);
            Repuesto& repuesto = repuestos[numRepuestos];
            string temp;

            getline(row, repuesto.modelo, ',');
            getline(row, repuesto.marca, ',');
            getline(row, repuesto.nombre, ',');
            getline(row, repuesto.modelo_carro, ',');
            getline(row, temp, ',');
            repuesto.anio_carro = (!temp.empty() ? stoi(temp) : 0);
            getline(row, temp, ',');
            repuesto.precio = (!temp.empty() ? stof(temp) : 0.0f);
            getline(row, temp, ',');
            repuesto.existencia = (temp=="true");

            numRepuestos++;
        }

        file.close();
    }

    void mostrarRepuestos() const {
        for (int i = 0; i < numRepuestos; ++i) {
            const Repuesto& rep = repuestos[i];
            cout << i + 1 << ". Nombre: " << rep.nombre << ", Modelo: " << rep.modelo
                << ", Marca: " << rep.marca << ", Modelo de carro: " << rep.modelo_carro
                << ", Anio carro: " << rep.anio_carro << ", Precio: " << rep.precio
                << ", Existencia: " << (rep.existencia ? "disponible":"no disponible") << "\n";
        }
    }

    void agregarRepuesto() {
        if (numRepuestos >= maxRepuestos) {
            cout << "No se pueden agregar mas repuestos\n";
            return;
        }

        Repuesto& rep = repuestos[numRepuestos];
        cout << "Ingrese los datos del nuevo repuesto:\n";
        cout << "Modelo: "; cin >> rep.modelo;
        cout << "Marca: "; cin >> rep.marca;
        cout << "Nombre: "; cin >> rep.nombre;
        cout << "Modelo de carro: "; cin >> rep.modelo_carro;
        cout << "Anio de carro: "; cin >> rep.anio_carro;
        cout << "Precio: "; cin >> rep.precio;
        cout << "Existencia (1 = disponible, 0 = no disponible): "; 
        int existencia;
        cin >> existencia;
        rep.existencia = existencia;

        numRepuestos++;
        cout << "Repuesto agregado\n";
    }

    void editarRepuesto(const string& modelo) {
        int index = buscarRepuestoPorModelo(modelo);
        if (index == -1) {
            cout << "No se encontro el repuesto modelo: " << modelo << endl;
            return;
        }

        Repuesto& rep = repuestos[index];
        int opcion;
        do {
            cout << "\nIngrese informacion a editar para el repuesto\n";
            cout << "1 para modelo\n2 para marca\n3 para nombre\n4 para modelo de carro\n5 para anio de carro\n";
            cout << "6 para precio\n7 para existencia\n0 para volver al menu anterior\n";
            cin >> opcion;

            switch (opcion) {
                case 1: cout << "Nuevo modelo: "; cin >> rep.modelo; break;
                case 2: cout << "Nueva marca: "; cin >> rep.marca; break;
                case 3: cout << "Nuevo nombre: "; cin >> rep.nombre; break;
                case 4: cout << "Nuevo modelo de carro: "; cin >> rep.modelo_carro; break;
                case 5: cout << "Nuevo anio de carro: "; cin >> rep.anio_carro; break;
                case 6: cout << "Nuevo precio: "; cin >> rep.precio; break;
                case 7: 
                    cout << "Existencia (1 = disponible, 0 = no disponible): ";
                    int existencia;
                    cin >> existencia;
                    rep.existencia = existencia == 1;
                    break;
                case 0: cout << "Ha terminado de editar.\n"; break;
                default: cout << "Eleccion invalida.\n"; break;
            }
        } while (opcion != 0);
    }

    void eliminarRepuesto(const string& modelo) {
        int index = buscarRepuestoPorModelo(modelo);
        if (index != -1) {
            for (int i = index; i < numRepuestos - 1; ++i) {
                repuestos[i] = repuestos[i + 1];
            }
            numRepuestos--;
            cout << "Se elimino el repuesto modelo: " << modelo << endl;
        } else {
            cout << "No se encontro el repuesto modelo: " << modelo << endl;
        }
    }

    void guardarCambiosRepuestos() const {
        ofstream file("../bin/parts.csv");
        file << "modelo,marca,nombre,modelo_carro,anio_carro,precio,existencia\n";
        for (int i = 0; i < numRepuestos; ++i) {
            const Repuesto& rep = repuestos[i];
            file << rep.modelo << ',' << rep.marca << ',' << rep.nombre << ',' << rep.modelo_carro
                << ',' << rep.anio_carro << ',' << rep.precio << ',' << (rep.existencia ? "true":"false") << '\n';
        }
        file.close();
    }

    void mostrarConsultas() {
    int opcionConsulta;
    do {
        cout << "\nConsultar informacion necesaria de los repuestos,ingresar lo siguiente\n";
        cout << "1 para la informacion de un repuesto por su modelo\n";
        cout << "2 para mostrar repuestos disponibles\n";
        cout << "3 para mostrar repuestos para ciertos vehiculos\n";
        cout << "0 para volver al menu anterior\n";
        cin >> opcionConsulta;

        switch (opcionConsulta) {
            case 1: {
                string modelo;
                cout << "Ingrese el modelo del repuesto: ";
                cin >> modelo;
                mostrarRepuestoPorModelo(modelo);
                break;
            }
            case 2: {
                mostrarRepuestosDisponibles();
                break;
            }
            case 3: {
                mostrarRepuestosVehiculo();
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

    void mostrarRepuestoPorModelo(const string& modelo) const {
        for (int i = 0; i < numRepuestos; ++i) {
            if (repuestos[i].modelo == modelo) {
                cout << "Repuesto encontrado: " << endl;
                cout << "Nombre: " << repuestos[i].nombre << ", Modelo: " << repuestos[i].modelo << ", Marca: " << repuestos[i].marca << "\n";
                return;
            }
        }
        cout << "Repuesto " << modelo << " no encontrado.\n";
    }

    void mostrarRepuestosDisponibles() const {
        for (int i = 0; i < numRepuestos; ++i) {
            if (repuestos[i].existencia) {
                cout << "Repuesto disponible: " << repuestos[i].nombre << ", Modelo: " << repuestos[i].modelo << ", Marca: " << repuestos[i].marca << "\n";
            }
        }
    }

    void mostrarRepuestosVehiculo() const {
        bool encontrado = false;
        for (int i = 0; i < numRepuestos; ++i) {
            cout << "Repuesto modelo: " << repuestos[i].modelo
                << ", nombre: " << repuestos[i].nombre
                << ", modelo del carro: " << repuestos[i].modelo_carro << endl;
            encontrado = true;
        }

        if (!encontrado) {
            cout << "No se encontraron repuestos.\n";
        }
    }



private:
    int buscarRepuestoPorModelo(const string& modelo) const {
        for (int i = 0; i < numRepuestos; ++i) {
            if (repuestos[i].modelo == modelo) {
                return i;
            }
        }
        return -1;
    }

    Repuesto repuestos[maxRepuestos];
    int numRepuestos;
};


int main() {
    manejoVehiculo gestionVehiculo;
    manejoClientes gestionClientes;
    manejoRepuestos gestionRepuesto;

    int eleccion;

    do {
        cout << "\ningrese 1 para el menu vehiculos:";
        cout << "\ningrese 2 para el menu clientes";
        cout << "\ningrese 3 para el menu repuestos";
        cout << "\ningrese 0 para salir del programa\n";
        cin >> eleccion;

        if (eleccion == 1) {
            int opcionVehiculo;
            do {
                cout << "\nque desea hacer con los vehiculos";
                cout << "\ningrese 1 para mostrar vehiculos";
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

    return 0;
}