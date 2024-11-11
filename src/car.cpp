#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

struct {
        string modelo;
        string marca;
        string placa;
        string color;
        string anio;
        int kilometraje;
        bool rentado;
        string motor;
        int precio_renta;
        int cedula_cliente;
        int fecha_de_entrega;
   } Vehiculo; 

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

getline(row, vehiculo.marca, ',');
getline(row, vehiculo.color, ',');
getline(row, vehiculo.placa, ',');
getline(row, vehiculo.modelo, ',');
getline(row, vehiculo.anio, ',');
getline(row, vehiculo.marca, ',');
getline(row, vehiculo.kilometraje, ',');
getline(row, vehiculo.motor, ',');
getline(row, vehiculo.precio_renta, ',');
getline(row, vehiculo.cedula_cliente, ',');
getline(row, vehiculo.fecha_de_entrega, ',');

numVehiculos++;

 }
file.close;
}

void mostrarVehiculo() const {
    for (int i=0; i<numVehiculos; ++i){
        const Vehiculo& veh = vehiculos[i];

        cout<< i + 1 <<". modelo" << veh.modelo <<", marca"<< veh.marca
        <<", placa: "<<veh.placa<<",color"<<veh.color<<",anio"<<veh.anio<<"kilometraje"
        <<veh.kilometraje<<",renytado"<<veh.rentado <<",motor:"
        <<veh.motor<<", precio renta:"<<veh.precio_renta<<"\n";
    }
}



private:
    Vehiculo vehiculos[maxVehiculos];
    int numVehiculos;
 }
int main() {
    manejoVehiculo gestion;
    gestion.mostrarVehiculo();


return 0;
   }