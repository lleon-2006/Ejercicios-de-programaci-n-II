#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

// ==================== CLASE PERSONA ====================
class Persona {
protected:
    int id;
    string nombre;
    string apellido;
    string telefono;

public:
    Persona() : id(0), nombre(""), apellido(""), telefono("") {}
    
    Persona(int id, string nombre, string apellido, string telefono)
        : id(id), nombre(nombre), apellido(apellido), telefono(telefono) {}
    
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getTelefono() const { return telefono; }
    string getNombreCompleto() const { return nombre + " " + apellido; }
    
    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setApellido(string apellido) { this->apellido = apellido; }
    void setTelefono(string telefono) { this->telefono = telefono; }
    
    virtual void mostrarInfo() const {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << getNombreCompleto() << endl;
        cout << "Telefono: " << telefono << endl;
    }
    
    virtual ~Persona() {}
};

// ==================== CLASE EMPLEADO ====================
class Empleado : public Persona {
private:
    string cargo;
    double salario;

public:
    Empleado() : Persona(), cargo(""), salario(0.0) {}
    
    Empleado(int id, string nombre, string apellido, string telefono, 
             string cargo, double salario)
        : Persona(id, nombre, apellido, telefono), cargo(cargo), salario(salario) {}
    
    string getCargo() const { return cargo; }
    double getSalario() const { return salario; }
    
    void setCargo(string cargo) { this->cargo = cargo; }
    void setSalario(double salario) { this->salario = salario; }
    
    void actualizarSalario(double nuevoSalario) { salario = nuevoSalario; }
    
    virtual void mostrarInfo() const {
        Persona::mostrarInfo();
        cout << "Cargo: " << cargo << endl;
        cout << "Salario: $" << salario << endl;
    }
    
    friend ostream& operator<<(ostream& os, const Empleado& emp) {
        os << "ID: " << emp.id << " | " << emp.getNombreCompleto() 
           << " | " << emp.cargo << " | $" << emp.salario;
        return os;
    }
    
    ~Empleado() {}
};

// ==================== CLASE PRODUCTO ====================
class Producto {
private:
    int id;
    string nombre;
    string categoria;
    double precio;
    int stock;

public:
    Producto() : id(0), nombre(""), categoria(""), precio(0.0), stock(0) {}
    
    Producto(int id, string nombre, string categoria, double precio, int stock)
        : id(id), nombre(nombre), categoria(categoria), precio(precio), stock(stock) {}
    
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }
    int getStock() const { return stock; }
    
    void setId(int id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setCategoria(string categoria) { this->categoria = categoria; }
    void setPrecio(double precio) { this->precio = precio; }
    void setStock(int stock) { this->stock = stock; }
    
    void actualizarStock(int cantidad) {
        stock += cantidad;
        if (stock < 0) stock = 0;
    }
    
    bool hayStockSuficiente(int cantidad) const {
        return stock >= cantidad;
    }
    
    void mostrarInfo() const {
        cout << "ID: " << id << " | " << nombre << " | Cat: " << categoria;
        cout << " | Precio: $" << precio << " | Stock: " << stock << endl;
    }
    
    bool operator<(const Producto& otro) const {
        return precio < otro.precio;
    }
    
    friend ostream& operator<<(ostream& os, const Producto& prod) {
        os << "ID: " << prod.id << " | " << prod.nombre << " | $";
        os << prod.precio << " | Stock: " << prod.stock;
        return os;
    }
};

// Declaración adelantada de Venta para Cliente
class Venta;

// ==================== CLASE CLIENTE ====================
class Cliente : public Persona {
private:
    string correo;
    vector<Venta*> historialCompras;

public:
    Cliente() : Persona(), correo("") {}
    
    Cliente(int id, string nombre, string apellido, string telefono, string correo)
        : Persona(id, nombre, apellido, telefono), correo(correo) {}
    
    string getCorreo() const { return correo; }
    vector<Venta*>& getHistorialCompras() { return historialCompras; }
    const vector<Venta*>& getHistorialCompras() const { return historialCompras; }
    
    void setCorreo(string correo) { this->correo = correo; }
    
    void agregarCompra(Venta* venta) {
        historialCompras.push_back(venta);
    }
    
    void mostrarHistorial() const;
    
    double calcularTotalGastado() const;
    
    virtual void mostrarInfo() const {
        Persona::mostrarInfo();
        cout << "Correo: " << correo << endl;
        cout << "Total compras: " << historialCompras.size() << endl;
        cout << "Total gastado: $" << calcularTotalGastado() << endl;
    }
    
    ~Cliente() {}
};

// ==================== CLASE VENTA ====================
class Venta {
private:
    int id;
    int idCliente;
    string fecha;
    vector<Producto> productosVendidos;
    map<int, int> cantidadesPorProducto;
    double total;

public:
    Venta() : id(0), idCliente(0), fecha(""), total(0.0) {}
    
    Venta(int id, int idCliente, string fecha) 
        : id(id), idCliente(idCliente), fecha(fecha), total(0.0) {}
    
    int getId() const { return id; }
    int getIdCliente() const { return idCliente; }
    string getFecha() const { return fecha; }
    double getTotal() const { return total; }
    const vector<Producto>& getProductosVendidos() const { return productosVendidos; }
    const map<int, int>& getCantidadesPorProducto() const { return cantidadesPorProducto; }
    
    void setId(int id) { this->id = id; }
    void setIdCliente(int idCliente) { this->idCliente = idCliente; }
    void setFecha(string fecha) { this->fecha = fecha; }
    
    void agregarProducto(const Producto& producto, int cantidad) {
        Producto prodVendido = producto;
        prodVendido.setStock(cantidad);
        productosVendidos.push_back(prodVendido);
        cantidadesPorProducto[producto.getId()] = cantidad;
    }
    
    void calcularTotal() {
        total = 0.0;
        for (size_t i = 0; i < productosVendidos.size(); i++) {
            total += productosVendidos[i].getPrecio() * productosVendidos[i].getStock();
        }
    }
    
    void mostrarResumen() const {
        cout << "\n========== VENTA #" << id << " ==========" << endl;
        cout << "Fecha: " << fecha << " | Cliente ID: " << idCliente << endl;
        cout << "----------------------------------------" << endl;
        for (size_t i = 0; i < productosVendidos.size(); i++) {
            cout << productosVendidos[i].getNombre() << " x" << productosVendidos[i].getStock();
            cout << " ($" << productosVendidos[i].getPrecio() << " c/u) = $";
            cout << productosVendidos[i].getPrecio() * productosVendidos[i].getStock() << endl;
        }
        cout << "----------------------------------------" << endl;
        cout << "TOTAL: $" << total << endl;
        cout << "========================================\n" << endl;
    }
    
    int getCantidadProducto(int idProducto) const {
        map<int, int>::const_iterator it = cantidadesPorProducto.find(idProducto);
        if (it != cantidadesPorProducto.end()) {
            return it->second;
        }
        return 0;
    }
};

// Implementación de métodos de Cliente que usan Venta
void Cliente::mostrarHistorial() const {
    if (historialCompras.empty()) {
        cout << "El cliente no tiene compras registradas." << endl;
        return;
    }
    cout << "\n=== HISTORIAL DE " << getNombreCompleto() << " ===" << endl;
    for (size_t i = 0; i < historialCompras.size(); i++) {
        historialCompras[i]->mostrarResumen();
    }
}

double Cliente::calcularTotalGastado() const {
    double total = 0.0;
    for (size_t i = 0; i < historialCompras.size(); i++) {
        total += historialCompras[i]->getTotal();
    }
    return total;
}

// ==================== VARIABLES GLOBALES ====================
vector<Producto> productos;
vector<Cliente> clientes;
vector<Empleado> empleados;
vector<Venta> ventas;
int contadorVentas = 1;

// ==================== FUNCIONES AUXILIARES ====================
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

int leerEntero(string mensaje) {
    int valor;
    cout << mensaje;
    cin >> valor;
    return valor;
}

double leerDouble(string mensaje) {
    double valor;
    cout << mensaje;
    cin >> valor;
    return valor;
}

string leerString(string mensaje) {
    string valor;
    cout << mensaje;
    cin.ignore();
    getline(cin, valor);
    return valor;
}

// ==================== MENÚ PRODUCTOS ====================
void menuProductos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "======= GESTION DE PRODUCTOS =======" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Modificar producto" << endl;
        cout << "3. Eliminar producto" << endl;
        cout << "4. Listar todos los productos" << endl;
        cout << "5. Buscar por categoria" << endl;
        cout << "6. Buscar por nombre" << endl;
        cout << "7. Filtrar por rango de precios" << endl;
        cout << "8. Productos con stock critico" << endl;
        cout << "9. Producto mas caro y mas barato" << endl;
        cout << "10. Costo total del inventario" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "====================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        if (opcion == 1) {
            int id = leerEntero("ID del producto: ");
            string nombre = leerString("Nombre: ");
            string categoria = leerString("Categoria: ");
            double precio = leerDouble("Precio: $");
            int stock = leerEntero("Stock inicial: ");
            productos.push_back(Producto(id, nombre, categoria, precio, stock));
            cout << "Producto agregado exitosamente!" << endl;
            pausa();
        }
        else if (opcion == 2) {
            int id = leerEntero("ID del producto a modificar: ");
            bool encontrado = false;
            for (size_t i = 0; i < productos.size(); i++) {
                if (productos[i].getId() == id) {
                    cout << "1. Modificar precio" << endl;
                    cout << "2. Modificar stock" << endl;
                    int subop = leerEntero("Seleccione: ");
                    if (subop == 1) {
                        double nuevoPrecio = leerDouble("Nuevo precio: $");
                        productos[i].setPrecio(nuevoPrecio);
                    } else if (subop == 2) {
                        int nuevoStock = leerEntero("Nuevo stock: ");
                        productos[i].setStock(nuevoStock);
                    }
                    encontrado = true;
                    cout << "Producto modificado!" << endl;
                    break;
                }
            }
            if (!encontrado) cout << "Producto no encontrado." << endl;
            pausa();
        }
        else if (opcion == 3) {
            int id = leerEntero("ID del producto a eliminar: ");
            for (size_t i = 0; i < productos.size(); i++) {
                if (productos[i].getId() == id) {
                    productos.erase(productos.begin() + i);
                    cout << "Producto eliminado." << endl;
                    break;
                }
            }
            pausa();
        }
        else if (opcion == 4) {
            cout << "\n=== LISTA DE PRODUCTOS ===" << endl;
            for (size_t i = 0; i < productos.size(); i++) {
                productos[i].mostrarInfo();
            }
            pausa();
        }
        else if (opcion == 5) {
            string cat = leerString("Ingrese categoria: ");
            cout << "\n=== PRODUCTOS EN CATEGORIA: " << cat << " ===" << endl;
            for (size_t i = 0; i < productos.size(); i++) {
                if (productos[i].getCategoria() == cat) {
                    productos[i].mostrarInfo();
                }
            }
            pausa();
        }
        else if (opcion == 6) {
            string nombre = leerString("Ingrese parte del nombre: ");
            cout << "\n=== RESULTADOS DE BUSQUEDA ===" << endl;
            for (size_t i = 0; i < productos.size(); i++) {
                if (productos[i].getNombre().find(nombre) != string::npos) {
                    productos[i].mostrarInfo();
                }
            }
            pausa();
        }
        else if (opcion == 7) {
            double min = leerDouble("Precio minimo: $");
            double max = leerDouble("Precio maximo: $");
            cout << "\n=== PRODUCTOS ENTRE $" << min << " Y $" << max << " ===" << endl;
            for (size_t i = 0; i < productos.size(); i++) {
                double p = productos[i].getPrecio();
                if (p >= min && p <= max) {
                    productos[i].mostrarInfo();
                }
            }
            pausa();
        }
        else if (opcion == 8) {
            int critico = leerEntero("Stock minimo critico: ");
            cout << "\n=== PRODUCTOS CON STOCK CRITICO (<" << critico << ") ===" << endl;
            for (size_t i = 0; i < productos.size(); i++) {
                if (productos[i].getStock() < critico) {
                    productos[i].mostrarInfo();
                }
            }
            pausa();
        }
        else if (opcion == 9) {
            if (!productos.empty()) {
                Producto masCaro = productos[0];
                Producto masBarato = productos[0];
                for (size_t i = 1; i < productos.size(); i++) {
                    if (productos[i].getPrecio() > masCaro.getPrecio()) masCaro = productos[i];
                    if (productos[i].getPrecio() < masBarato.getPrecio()) masBarato = productos[i];
                }
                cout << "\n=== PRODUCTO MAS CARO ===" << endl;
                masCaro.mostrarInfo();
                cout << "\n=== PRODUCTO MAS BARATO ===" << endl;
                masBarato.mostrarInfo();
            }
            pausa();
        }
        else if (opcion == 10) {
            double total = 0.0;
            for (size_t i = 0; i < productos.size(); i++) {
                total += productos[i].getPrecio() * productos[i].getStock();
            }
            cout << "\nCOSTO TOTAL DEL INVENTARIO: $" << total << endl;
            pausa();
        }
    } while (opcion != 0);
}

// ==================== MENÚ CLIENTES ====================
bool clienteTieneCompras(int idCliente) {
    for (size_t i = 0; i < ventas.size(); i++) {
        if (ventas[i].getIdCliente() == idCliente) {
            return true;
        }
    }
    return false;
}

void menuClientes() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "======== GESTION DE CLIENTES ========" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Modificar cliente" << endl;
        cout << "3. Eliminar cliente" << endl;
        cout << "4. Listar todos los clientes" << endl;
        cout << "5. Ver historial de compras" << endl;
        cout << "6. Clientes por monto gastado" << endl;
        cout << "7. Total gastado por cliente" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "=====================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        if (opcion == 1) {
            int id = leerEntero("ID del cliente: ");
            string nombre = leerString("Nombre: ");
            string apellido = leerString("Apellido: ");
            string telefono = leerString("Telefono: ");
            string correo = leerString("Correo: ");
            clientes.push_back(Cliente(id, nombre, apellido, telefono, correo));
            cout << "Cliente agregado exitosamente!" << endl;
            pausa();
        }
        else if (opcion == 2) {
            int id = leerEntero("ID del cliente a modificar: ");
            bool encontrado = false;
            for (size_t i = 0; i < clientes.size(); i++) {
                if (clientes[i].getId() == id) {
                    cout << "1. Modificar telefono" << endl;
                    cout << "2. Modificar correo" << endl;
                    int subop = leerEntero("Seleccione: ");
                    if (subop == 1) {
                        string tel = leerString("Nuevo telefono: ");
                        clientes[i].setTelefono(tel);
                    } else if (subop == 2) {
                        string correo = leerString("Nuevo correo: ");
                        clientes[i].setCorreo(correo);
                    }
                    encontrado = true;
                    cout << "Cliente modificado!" << endl;
                    break;
                }
            }
            if (!encontrado) cout << "Cliente no encontrado." << endl;
            pausa();
        }
        else if (opcion == 3) {
            int id = leerEntero("ID del cliente a eliminar: ");
            if (clienteTieneCompras(id)) {
                cout << "NO SE PUEDE ELIMINAR: El cliente tiene compras registradas." << endl;
            } else {
                for (size_t i = 0; i < clientes.size(); i++) {
                    if (clientes[i].getId() == id) {
                        clientes.erase(clientes.begin() + i);
                        cout << "Cliente eliminado." << endl;
                        break;
                    }
                }
            }
            pausa();
        }
        else if (opcion == 4) {
            cout << "\n=== LISTA DE CLIENTES ===" << endl;
            for (size_t i = 0; i < clientes.size(); i++) {
                clientes[i].mostrarInfo();
                cout << "------------------------" << endl;
            }
            pausa();
        }
        else if (opcion == 5) {
            int id = leerEntero("ID del cliente: ");
            bool encontrado = false;
            for (size_t i = 0; i < clientes.size(); i++) {
                if (clientes[i].getId() == id) {
                    // Asociar ventas al historial del cliente
                    clientes[i].getHistorialCompras().clear();
                    for (size_t j = 0; j < ventas.size(); j++) {
                        if (ventas[j].getIdCliente() == id) {
                            clientes[i].agregarCompra(&ventas[j]);
                        }
                    }
                    clientes[i].mostrarHistorial();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) cout << "Cliente no encontrado." << endl;
            pausa();
        }
        else if (opcion == 6) {
            double montoMin = leerDouble("Monto minimo gastado: $");
            cout << "\n=== CLIENTES QUE HAN GASTADO MAS DE $" << montoMin << " ===" << endl;
            for (size_t i = 0; i < clientes.size(); i++) {
                double total = 0.0;
                for (size_t j = 0; j < ventas.size(); j++) {
                    if (ventas[j].getIdCliente() == clientes[i].getId()) {
                        total += ventas[j].getTotal();
                    }
                }
                if (total >= montoMin) {
                    cout << clientes[i].getNombreCompleto() << " - Total gastado: $" << total << endl;
                }
            }
            pausa();
        }
        else if (opcion == 7) {
            int id = leerEntero("ID del cliente: ");
            double total = 0.0;
            for (size_t i = 0; i < ventas.size(); i++) {
                if (ventas[i].getIdCliente() == id) {
                    total += ventas[i].getTotal();
                }
            }
            cout << "Total gastado por el cliente: $" << total << endl;
            pausa();
        }
    } while (opcion != 0);
}

// ==================== MENÚ EMPLEADOS ====================
void menuEmpleados() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "======== GESTION DE EMPLEADOS ========" << endl;
        cout << "1. Agregar empleado" << endl;
        cout << "2. Modificar empleado" << endl;
        cout << "3. Eliminar empleado" << endl;
        cout << "4. Listar todos los empleados" << endl;
        cout << "5. Estadisticas de salarios" << endl;
        cout << "6. Conteo por cargo" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "======================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        if (opcion == 1) {
            int id = leerEntero("ID del empleado: ");
            string nombre = leerString("Nombre: ");
            string apellido = leerString("Apellido: ");
            string telefono = leerString("Telefono: ");
            string cargo = leerString("Cargo: ");
            double salario = leerDouble("Salario: $");
            empleados.push_back(Empleado(id, nombre, apellido, telefono, cargo, salario));
            cout << "Empleado agregado exitosamente!" << endl;
            pausa();
        }
        else if (opcion == 2) {
            int id = leerEntero("ID del empleado a modificar: ");
            bool encontrado = false;
            for (size_t i = 0; i < empleados.size(); i++) {
                if (empleados[i].getId() == id) {
                    cout << "1. Modificar cargo" << endl;
                    cout << "2. Actualizar salario" << endl;
                    int subop = leerEntero("Seleccione: ");
                    if (subop == 1) {
                        string cargo = leerString("Nuevo cargo: ");
                        empleados[i].setCargo(cargo);
                    } else if (subop == 2) {
                        double salario = leerDouble("Nuevo salario: $");
                        empleados[i].actualizarSalario(salario);
                    }
                    encontrado = true;
                    cout << "Empleado modificado!" << endl;
                    break;
                }
            }
            if (!encontrado) cout << "Empleado no encontrado." << endl;
            pausa();
        }
        else if (opcion == 3) {
            int id = leerEntero("ID del empleado a eliminar: ");
            for (size_t i = 0; i < empleados.size(); i++) {
                if (empleados[i].getId() == id) {
                    empleados.erase(empleados.begin() + i);
                    cout << "Empleado eliminado." << endl;
                    break;
                }
            }
            pausa();
        }
        else if (opcion == 4) {
            cout << "\n=== LISTA DE EMPLEADOS ===" << endl;
            for (size_t i = 0; i < empleados.size(); i++) {
                cout << empleados[i] << endl;
            }
            pausa();
        }
        else if (opcion == 5) {
            if (!empleados.empty()) {
                double suma = 0.0;
                Empleado mejorPagado = empleados[0];
                for (size_t i = 0; i < empleados.size(); i++) {
                    suma += empleados[i].getSalario();
                    if (empleados[i].getSalario() > mejorPagado.getSalario()) {
                        mejorPagado = empleados[i];
                    }
                }
                cout << "\n=== ESTADISTICAS DE SALARIOS ===" << endl;
                cout << "Salario promedio: $" << (suma / empleados.size()) << endl;
                cout << "Empleado con mayor salario: " << mejorPagado.getNombreCompleto();
                cout << " ($" << mejorPagado.getSalario() << ")" << endl;
            }
            pausa();
        }
        else if (opcion == 6) {
            map<string, int> conteoCargos;
            for (size_t i = 0; i < empleados.size(); i++) {
                conteoCargos[empleados[i].getCargo()]++;
            }
            cout << "\n=== EMPLEADOS POR CARGO ===" << endl;
            for (map<string, int>::iterator it = conteoCargos.begin(); 
                 it != conteoCargos.end(); ++it) {
                cout << it->first << ": " << it->second << " empleado(s)" << endl;
            }
            pausa();
        }
    } while (opcion != 0);
}

// ==================== MENÚ VENTAS ====================
void menuVentas() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "========== GESTION DE VENTAS ==========" << endl;
        cout << "1. Registrar nueva venta" << endl;
        cout << "2. Eliminar venta" << endl;
        cout << "3. Listar todas las ventas" << endl;
        cout << "4. Filtrar ventas por cliente" << endl;
        cout << "5. Estadisticas de ventas" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "=======================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        if (opcion == 1) {
            if (clientes.empty() || productos.empty()) {
                cout << "Debe haber al menos un cliente y un producto registrados." << endl;
                pausa();
                continue;
            }
            
            cout << "\n=== CLIENTES DISPONIBLES ===" << endl;
            for (size_t i = 0; i < clientes.size(); i++) {
                cout << "ID: " << clientes[i].getId() << " - " << clientes[i].getNombreCompleto() << endl;
            }
            int idCliente = leerEntero("ID del cliente: ");
            
            bool clienteExiste = false;
            for (size_t i = 0; i < clientes.size(); i++) {
                if (clientes[i].getId() == idCliente) {
                    clienteExiste = true;
                    break;
                }
            }
            if (!clienteExiste) {
                cout << "Cliente no encontrado." << endl;
                pausa();
                continue;
            }
            
            string fecha = leerString("Fecha (DD/MM/AAAA): ");
            Venta nuevaVenta(contadorVentas++, idCliente, fecha);
            
            char continuar;
            do {
                cout << "\n=== PRODUCTOS DISPONIBLES ===" << endl;
                for (size_t i = 0; i < productos.size(); i++) {
                    cout << "ID: " << productos[i].getId() << " | " << productos[i].getNombre();
                    cout << " | $" << productos[i].getPrecio() << " | Stock: " << productos[i].getStock() << endl;
                }
                
                int idProd = leerEntero("ID del producto: ");
                int indiceProd = -1;
                for (size_t i = 0; i < productos.size(); i++) {
                    if (productos[i].getId() == idProd) {
                        indiceProd = i;
                        break;
                    }
                }
                
                if (indiceProd == -1) {
                    cout << "Producto no encontrado." << endl;
                    continue;
                }
                
                int cantidad = leerEntero("Cantidad: ");
                if (!productos[indiceProd].hayStockSuficiente(cantidad)) {
                    cout << "Stock insuficiente! Stock disponible: " << productos[indiceProd].getStock() << endl;
                    continue;
                }
                
                productos[indiceProd].actualizarStock(-cantidad);
                nuevaVenta.agregarProducto(productos[indiceProd], cantidad);
                
                cout << "Producto agregado al carrito. Desea agregar otro? (s/n): ";
                cin >> continuar;
            } while (continuar == 's' || continuar == 'S');
            
            nuevaVenta.calcularTotal();
            ventas.push_back(nuevaVenta);
            
            cout << "\n=== VENTA REGISTRADA ===" << endl;
            nuevaVenta.mostrarResumen();
            pausa();
        }
        else if (opcion == 2) {
            int id = leerEntero("ID de la venta a eliminar: ");
            for (size_t i = 0; i < ventas.size(); i++) {
                if (ventas[i].getId() == id) {
                    // Devolver stock
                    const vector<Producto>& prods = ventas[i].getProductosVendidos();
                    for (size_t j = 0; j < prods.size(); j++) {
                        for (size_t k = 0; k < productos.size(); k++) {
                            if (productos[k].getId() == prods[j].getId()) {
                                productos[k].actualizarStock(prods[j].getStock());
                                break;
                            }
                        }
                    }
                    ventas.erase(ventas.begin() + i);
                    cout << "Venta eliminada y stock restaurado." << endl;
                    break;
                }
            }
            pausa();
        }
        else if (opcion == 3) {
            cout << "\n=== TODAS LAS VENTAS ===" << endl;
            for (size_t i = 0; i < ventas.size(); i++) {
                ventas[i].mostrarResumen();
            }
            pausa();
        }
        else if (opcion == 4) {
            int idCliente = leerEntero("ID del cliente: ");
            cout << "\n=== VENTAS DEL CLIENTE ID " << idCliente << " ===" << endl;
            for (size_t i = 0; i < ventas.size(); i++) {
                if (ventas[i].getIdCliente() == idCliente) {
                    ventas[i].mostrarResumen();
                }
            }
            pausa();
        }
        else if (opcion == 5) {
            if (ventas.empty()) {
                cout << "No hay ventas registradas." << endl;
                pausa();
                continue;
            }
            
            // Total vendido por categoría
            map<string, double> ventasPorCategoria;
            // Producto más vendido
            map<int, int> cantidadPorProducto;
            // Cliente que más compra
            map<int, double> totalPorCliente;
            
            for (size_t i = 0; i < ventas.size(); i++) {
                const vector<Producto>& prods = ventas[i].getProductosVendidos();
                for (size_t j = 0; j < prods.size(); j++) {
                    string cat = prods[j].getCategoria();
                    double subtotal = prods[j].getPrecio() * prods[j].getStock();
                    ventasPorCategoria[cat] += subtotal;
                    cantidadPorProducto[prods[j].getId()] += prods[j].getStock();
                }
                totalPorCliente[ventas[i].getIdCliente()] += ventas[i].getTotal();
            }
            
            cout << "\n=== TOTAL VENDIDO POR CATEGORIA ===" << endl;
            for (map<string, double>::iterator it = ventasPorCategoria.begin(); 
                 it != ventasPorCategoria.end(); ++it) {
                cout << it->first << ": $" << it->second << endl;
            }
            
            cout << "\n=== PRODUCTO MAS VENDIDO ===" << endl;
            int idMasVendido = -1;
            int maxCantidad = 0;
            for (map<int, int>::iterator it = cantidadPorProducto.begin(); 
                 it != cantidadPorProducto.end(); ++it) {
                if (it->second > maxCantidad) {
                    maxCantidad = it->second;
                    idMasVendido = it->first;
                }
            }
            if (idMasVendido != -1) {
                for (size_t i = 0; i < productos.size(); i++) {
                    if (productos[i].getId() == idMasVendido) {
                        cout << productos[i].getNombre() << " - " << maxCantidad << " unidades" << endl;
                        break;
                    }
                }
            }
            
            cout << "\n=== CLIENTE QUE MAS COMPRA (POR MONTO) ===" << endl;
            int idMejorCliente = -1;
            double maxTotal = 0.0;
            for (map<int, double>::iterator it = totalPorCliente.begin(); 
                 it != totalPorCliente.end(); ++it) {
                if (it->second > maxTotal) {
                    maxTotal = it->second;
                    idMejorCliente = it->first;
                }
            }
            if (idMejorCliente != -1) {
                for (size_t i = 0; i < clientes.size(); i++) {
                    if (clientes[i].getId() == idMejorCliente) {
                        cout << clientes[i].getNombreCompleto() << " - Total: $" << maxTotal << endl;
                        break;
                    }
                }
            }
            pausa();
        }
    } while (opcion != 0);
}

// ==================== MENÚ REPORTES ====================
void menuReportes() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "======= REPORTES Y ESTADISTICAS =======" << endl;
        cout << "1. Productos agrupados por categoria" << endl;
        cout << "2. Promedio de precios por categoria" << endl;
        cout << "3. Ventas por cliente (mapa)" << endl;
        cout << "4. Costo total del inventario" << endl;
        cout << "5. Resumen general" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "=======================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        if (opcion == 1) {
            map<string, vector<Producto> > productosPorCategoria;
            for (size_t i = 0; i < productos.size(); i++) {
                productosPorCategoria[productos[i].getCategoria()].push_back(productos[i]);
            }
            
            cout << "\n=== PRODUCTOS POR CATEGORIA ===" << endl;
            for (map<string, vector<Producto> >::iterator it = productosPorCategoria.begin();
                 it != productosPorCategoria.end(); ++it) {
                cout << "\n--- " << it->first << " (" << it->second.size() << " productos) ---" << endl;
                for (size_t j = 0; j < it->second.size(); j++) {
                    cout << "  " << it->second[j].getNombre() << " - $" << it->second[j].getPrecio() << endl;
                }
            }
            pausa();
        }
        else if (opcion == 2) {
            map<string, vector<Producto> > productosPorCategoria;
            for (size_t i = 0; i < productos.size(); i++) {
                productosPorCategoria[productos[i].getCategoria()].push_back(productos[i]);
            }
            
            cout << "\n=== PROMEDIO DE PRECIOS POR CATEGORIA ===" << endl;
            for (map<string, vector<Producto> >::iterator it = productosPorCategoria.begin();
                 it != productosPorCategoria.end(); ++it) {
                double suma = 0.0;
                for (size_t j = 0; j < it->second.size(); j++) {
                    suma += it->second[j].getPrecio();
                }
                double promedio = suma / it->second.size();
                cout << it->first << ": $" << promedio << endl;
            }
            pausa();
        }
        else if (opcion == 3) {
            map<int, vector<Venta> > ventasPorCliente;
            for (size_t i = 0; i < ventas.size(); i++) {
                ventasPorCliente[ventas[i].getIdCliente()].push_back(ventas[i]);
            }
            
            cout << "\n=== VENTAS POR CLIENTE ===" << endl;
            for (map<int, vector<Venta> >::iterator it = ventasPorCliente.begin();
                 it != ventasPorCliente.end(); ++it) {
                // Buscar nombre del cliente
                string nombreCliente = "Desconocido";
                for (size_t j = 0; j < clientes.size(); j++) {
                    if (clientes[j].getId() == it->first) {
                        nombreCliente = clientes[j].getNombreCompleto();
                        break;
                    }
                }
                cout << "\nCliente: " << nombreCliente << " (ID: " << it->first << ")";
                cout << " - " << it->second.size() << " venta(s)" << endl;
                
                double totalCliente = 0.0;
                for (size_t j = 0; j < it->second.size(); j++) {
                    totalCliente += it->second[j].getTotal();
                }
                cout << "Total gastado: $" << totalCliente << endl;
            }
            pausa();
        }
        else if (opcion == 4) {
            double total = 0.0;
            for (size_t i = 0; i < productos.size(); i++) {
                total += productos[i].getPrecio() * productos[i].getStock();
            }
            cout << "\nCOSTO TOTAL DEL INVENTARIO: $" << total << endl;
            pausa();
        }
        else if (opcion == 5) {
            cout << "\n========== RESUMEN GENERAL ==========" << endl;
            cout << "Total de productos: " << productos.size() << endl;
            cout << "Total de clientes: " << clientes.size() << endl;
            cout << "Total de empleados: " << empleados.size() << endl;
            cout << "Total de ventas: " << ventas.size() << endl;
            
            double totalVentas = 0.0;
            for (size_t i = 0; i < ventas.size(); i++) {
                totalVentas += ventas[i].getTotal();
            }
            cout << "Ingresos totales por ventas: $" << totalVentas << endl;
            cout << "=====================================" << endl;
            pausa();
        }
    } while (opcion != 0);
}

// ==================== MENÚ PRINCIPAL ====================
int main() {
    // Datos de ejemplo para pruebas
    productos.push_back(Producto(1, "Laptop HP", "Computadoras", 800.0, 5));
    productos.push_back(Producto(2, "Mouse Logitech", "Perifericos", 25.0, 20));
    productos.push_back(Producto(3, "Teclado Mecanico", "Perifericos", 75.0, 8));
    productos.push_back(Producto(4, "Monitor Dell", "Monitores", 200.0, 3));
    productos.push_back(Producto(5, "Impresora Epson", "Impresoras", 150.0, 2));
    
    clientes.push_back(Cliente(1, "Juan", "Perez", "123456789", "juan@email.com"));
    clientes.push_back(Cliente(2, "Maria", "Gomez", "987654321", "maria@email.com"));
    
    empleados.push_back(Empleado(1, "Carlos", "Lopez", "111222333", "Vendedor", 1200.0));
    empleados.push_back(Empleado(2, "Ana", "Martinez", "444555666", "Gerente", 2500.0));
    
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n";
        cout << "========================================" << endl;
        cout << "    MINI-ERP PARA MIPYME - SOLUCIONES S.A." << endl;
        cout << "========================================" << endl;
        cout << "1. Gestion de Productos" << endl;
        cout << "2. Gestion de Clientes" << endl;
        cout << "3. Gestion de Empleados" << endl;
        cout << "4. Gestion de Ventas" << endl;
        cout << "5. Reportes y Estadisticas" << endl;
        cout << "0. Salir" << endl;
        cout << "========================================" << endl;
        opcion = leerEntero("Seleccione una opcion: ");
        
        switch (opcion) {
            case 1: menuProductos(); break;
            case 2: menuClientes(); break;
            case 3: menuEmpleados(); break;
            case 4: menuVentas(); break;
            case 5: menuReportes(); break;
            case 0: cout << "Gracias por usar el sistema. Hasta luego!" << endl; break;
            default: cout << "Opcion invalida." << endl; pausa();
        }
    } while (opcion != 0);
    
    return 0;
}