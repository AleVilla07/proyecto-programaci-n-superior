# Proyecto de Sistema de Reservas HOTEL UCB

Este proyecto es una solución de reservas de habitaciones para el HOTEL UCB, con integración de una página web (HTML + JS) y un sistema en C++ para gestión de clientes VIP y reservas.

---

## 📁 Archivos incluidos

### 🌐 Archivos Web
- `index.html` → Página principal del hotel.
- `formulario.html` → Formulario para realizar reservas (con envío por correo).
- `agradecimiento.html` → Página mostrada luego de enviar la reserva.
- `reservas.html` → Selector de tipo de habitación.
- `admin.html` → Página para añadir o eliminar clientes VIP (genera `instrucciones.txt`).
- `style.css` → Estilos globales.
- `scripts.js` → Funciones opcionales JS.

### 💻 Archivos C++
- `sistema_reservas_vip.cpp` → Programa que permite hacer reservas, calcula descuento y verifica disponibilidad.
- `procesar_instrucciones.cpp` → Programa que lee `instrucciones.txt` generado por `admin.html` y actualiza `clientes_vip.csv`.
- `clientes_vip.csv` → Base de datos de clientes VIP.
- `reservas.csv` → Registro de reservas confirmadas.
- `instrucciones.txt` → Archivo generado desde `admin.html` para agregar/eliminar clientes VIP.

---

## 🧠 ¿Cómo funciona?

1. El usuario reserva desde el sitio web (`formulario.html`).
2. El formulario guarda datos que se pueden procesar desde el programa C++.
3. Los administradores gestionan clientes VIP desde `admin.html`, lo cual genera `instrucciones.txt`.
4. El programa `procesar_instrucciones` actualiza la base `clientes_vip.csv`.
5. El programa `sistema_reservas_vip` permite hacer reservas en consola, valida si el cliente es VIP, y controla la disponibilidad.

---

## ⚙️ Compilación`  



Requiere `g++` (GCC).

### Compilar el sistema de reservas:
```bash
g++ sistema_reservas.cpp
./reservas
```

### Compilar el sistema de reservas para clientes vip:
```bash
g++ sistema_reservas_vip.cpp
./reservas_vip
```


### Compilar el gestor de instrucciones desde la web:
```bash
g++ procesar_instrucciones.cpp -o instrucciones
./instrucciones
```

---

## 📌 Notas

- El descuento del 15% se aplica automáticamente si el cliente está en `clientes_vip.csv`.
- Hay un máximo de **3 habitaciones por tipo por fecha**.
- Asegúrate de que los archivos `.csv` estén en la misma carpeta que los ejecutables.

---

## 👨‍💻 Autores
Alejandro Villafuerte-David Perez – Proyecto de Programación Superior
