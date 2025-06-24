#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

struct Cliente {
    string nombre;
    string ci;
    bool esVIP;
};

unordered_map<string, Cliente> baseClientes;

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

void procesarInstrucciones(const string& filename) {
    ifstream file(filename);
    string linea;
    while (getline(file, linea)) {
        if (linea.rfind("AGREGAR,", 0) == 0) {
            size_t pos1 = linea.find(",", 8);
            if (pos1 != string::npos) {
                string nombre = linea.substr(8, pos1 - 8);
                string ci = linea.substr(pos1 + 1);
                baseClientes[ci] = {nombre, ci, true};
                cout << "✅ Cliente agregado: " << nombre << " (" << ci << ")\n";
            }
        } else if (linea.rfind("ELIMINAR,", 0) == 0) {
            string ci = linea.substr(9);
            if (baseClientes.erase(ci))
                cout << "🗑️ Cliente eliminado: " << ci << "\n";
            else
                cout << "⚠️ Cliente no encontrado: " << ci << "\n";
        }
    }
    file.close();
    guardarClientesVIP();
    // Limpiar archivo
    ofstream clearfile(filename);
    clearfile.close();
}

int main() {
    cargarClientesVIP();
    procesarInstrucciones("instrucciones.txt");
    cout << "✅ Instrucciones procesadas.\n";
    return 0;
}
