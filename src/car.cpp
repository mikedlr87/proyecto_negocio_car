#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

struct Vehiculo{
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
struct Cliente{
    int cedula;
    string nombre;
    string apellido;
    string email;
    
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

(getline(file,line));

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
private:
    Vehiculo vehiculos[maxVehiculos];
    int numVehiculos;
 };
int main() {
    manejoVehiculo gestion;
    gestion.mostrarVehiculo();


return 0;
   }