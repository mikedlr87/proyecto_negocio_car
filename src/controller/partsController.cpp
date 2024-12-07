#include<iostream>
#include <../model/parts.cpp>

using namespace std;

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