#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Cliente {
    string nombre;
    string ci;
    bool esVIP;
};

struct Reserva {
    string tipoHabitacion;
    string nombre;
    string ci;
    string fecha;
    float precioFinal;
};

unordered_map<string, Cliente> baseClientes;
map<pair<string, string>, int> disponibilidad; // (tipoHabitacion, fecha) -> habitaciones disponibles
vector<Reserva> historial;

const float precioBase = 100.0; // Precio por noche (ejemplo)
const int cupoPorTipo = 3;

void cargarClientesVIP() {
    ifstream file("clientes_vip.csv");
    string nombre, ci;
    while (getline(file, nombre, ',') && getline(file, ci)) {
        baseClientes[ci] = {nombre, ci, true};
    }
    file.close();
}

void guardarClientesVIP() {
    ofstream file("clientes_vip.csv");
    for (auto& [ci, cliente] : baseClientes) {
        if (cliente.esVIP)
            file << cliente.nombre << "," << ci << "\n";
    }
    file.close();
}

bool esDisponible(string tipo, string fecha) {
    return disponibilidad[{tipo, fecha}] < cupoPorTipo;
}

float calcularPrecio(string ci) {
    return baseClientes.count(ci) && baseClientes[ci].esVIP ? precioBase * 0.85f : precioBase;
}

void hacerReserva() {
    Reserva r;
    cout << "Tipo de habitación (Premium/Suite/Super VIP): ";
    getline(cin, r.tipoHabitacion);
    cout << "Nombre: ";
    getline(cin, r.nombre);
    cout << "CI: ";
    getline(cin, r.ci);
    cout << "Fecha (YYYY-MM-DD): ";
    getline(cin, r.fecha);

    if (!esDisponible(r.tipoHabitacion, r.fecha)) {
        cout << "❌ No hay habitaciones disponibles para esa fecha.\n";
        return;
    }

    r.precioFinal = calcularPrecio(r.ci);
    historial.push_back(r);
    disponibilidad[{r.tipoHabitacion, r.fecha}]++;

    ofstream out("reservas.csv", ios::app);
    out << r.tipoHabitacion << "," << r.nombre << "," << r.ci << "," << r.fecha << "," << fixed << setprecision(2) << r.precioFinal << "\n";
    out.close();

    cout << "✅ Reserva confirmada. Precio final: $" << r.precioFinal << "\n";
}

int main() {
    cargarClientesVIP();

    int opcion;
    do {
        cout << "\n=== SISTEMA DE RESERVAS ===\n";
        cout << "1. Hacer reserva\n";
        cout << "2. Agregar cliente VIP\n";
        cout << "3. Eliminar cliente VIP\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            hacerReserva();
        } else if (opcion == 2) {
            Cliente nuevo;
            cout << "Nombre: "; getline(cin, nuevo.nombre);
            cout << "CI: "; getline(cin, nuevo.ci);
            nuevo.esVIP = true;
            baseClientes[nuevo.ci] = nuevo;
            guardarClientesVIP();
            cout << "✅ Cliente VIP agregado.\n";
        } else if (opcion == 3) {
            string ci;
            cout << "CI del cliente a eliminar: "; getline(cin, ci);
            if (baseClientes.erase(ci)) {
                guardarClientesVIP();
                cout << "✅ Cliente eliminado.\n";
            } else {
                cout << "❌ Cliente no encontrado.\n";
            }
        }

    } while (opcion != 4);

    return 0;
}
