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
    int ced_cliente;
    string nombre;
    string apellido;
    string e_mail;
    int cantidad_vehiculos_rentados;
    string direccion;
    string activo;

    
   }; 

   void guardarCambios(){
    manejoVehiculo.guardarCambioVehiculo();
   }

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
//funciones para mostrar consultas
  void mostrarPrecioVehiculo() const {
    for (int i=0; i<numVehiculos; ++i){
        const Vehiculo& veh = vehiculos[i];
        cout<< i + 1 <<", marca: "<<veh.marca<< ", precio renta: "<<veh.precio_renta<< ", placa: "<<veh.placa<<"\n";
    }
  }
void guardarCambiosVehiculos() const{
      ofstream file("../bin/vehicle.csv");
    file <<"modelo,marca,placa,color,anio,kilometraje,rentado,motor,precio_renta,ced_cliente,fecha_entrega\n";
    for (int i=0; i<numVehiculos; ++i){
        const Vehiculo& veh = vehiculos[i];
        file << veh.modelo <<','<< veh.marca
        <<','<<veh.placa<<','<<veh.color<<','<<veh.anio<<','
        <<veh.kilometraje<<','<<(veh.rentado ? "true":"false")<<','
        <<veh.motor<<','<<veh.precio_renta <<',' <<veh.fecha_de_entrega<<'\n';
    }
}






private:
    Vehiculo vehiculos[maxVehiculos];
    int numVehiculos;
 };

const int maxClientes = 100;
class manejoCliente{
public:

manejoClientes():numClientes (0){
cargarClientes();

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
cliente.cliente.cantidad_vehiculos_rentados = (!temp.empty() ? stoi(temp) : 0);
getline(row, cliente.direccion, ',');
getline(row, cliente.activo, ',');

}






};


int main() {
        manejoVehiculo gestion;
    //    manejoRepuestos gestonRepuestos

        int eleccion;

            do {
                cout<< "\ningrese 1 si quiere mostrar los vehiculos: \ningrese 2 si mostrar los clientes\ningrese 3 si ver los repuestos ";
                cin>> eleccion;
                if (eleccion == 1){
                    gestion.mostrarVehiculo();
                } else {
                    cout << "\nNo lo es";
                }

                if (eleccion == 2){
                    // gestion.mostrarClientes();
                } else {
                    cout << "\nNo lo es";
                }

                if (eleccion == 3){
                    // gestionRepuestos.mostrarRepuestos();
                } else {
                    cout << "\nNo lo es";
                }
                
         /*       
                    do {
                }  while ();

*/

            }   while (eleccion != 0);



    
return 0;
   }
 