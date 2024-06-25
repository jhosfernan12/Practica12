#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class Producto 
{
public:
    string codigo;
    string descripcion;
    int cantidad;


    Producto() : codigo(""), descripcion(""), cantidad(0) {}

    Producto(string cod, string desc, int cant)
        : codigo(cod), descripcion(desc), cantidad(cant) {}
};

class Inventario
{
private:
    map<string, Producto> productos;

public:
    void agregarProducto(const string& codigo, const string& descripcion, int cantidad) 
    {
        if (productos.find(codigo) != productos.end()) 
        {
            cout << "Producto con el codigo " << codigo << " ya existe." << endl;
            return;
        }
        productos[codigo] = Producto(codigo, descripcion, cantidad);
        cout << "Producto agregado exitosamente." << endl;
    }

    void actualizarCantidad(const string& codigo, int cantidad) 
    {
        auto it = productos.find(codigo);
        if (it != productos.end()) 
        {
            it->second.cantidad = cantidad;
            cout << "Cantidad actualizada exitosamente." << endl;
        } 
        else 
        {
            cout << "Producto no encontrado." << endl;
        }
    }

    void buscarProducto(const string& codigo) const 
    {
        auto it = productos.find(codigo);
        if (it != productos.end()) 
        {
            cout << "Codigo: " << it->second.codigo
                 << ", Descripcion: " << it->second.descripcion
                 << ", Cantidad: " << it->second.cantidad << endl;
        } 
        else 
        {
            cout << "Producto no encontrado." << endl;
        }
    }

    void mostrarProductosOrdenados() const 
    {
        vector<Producto> listaProductos;
        for (const auto& par : productos) 
        {
            listaProductos.push_back(par.second);
        }

        sort(listaProductos.begin(), listaProductos.end(),
             [](const Producto& a, const Producto& b) 
             {
                 return a.descripcion < b.descripcion;
             });

        for (const auto& prod : listaProductos) 
        {
            cout << "Codigo: " << prod.codigo
                 << ", Descripcion: " << prod.descripcion
                 << ", Cantidad: " << prod.cantidad << endl;
        }
    }
};

void mostrarMenu() 
{
    cout << "Menu de Gestion de Inventario" << endl;
    cout << "1. Agregar producto" << endl;
    cout << "2. Actualizar cantidad" << endl;
    cout << "3. Buscar producto" << endl;
    cout << "4. Mostrar productos ordenados por descripcion" << endl;
    cout << "5. Salir" << endl;
}

int main() 
{
    Inventario inventario;
    int opcion;
    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        string codigo, descripcion;
        int cantidad;

        switch (opcion)
        {
            case 1:
                cout << "Ingrese codigo: ";
                cin >> codigo;
                cout << "Ingrese descripcion: ";
                cin.ignore();
                getline(cin, descripcion);
                cout << "Ingrese cantidad: ";
                cin >> cantidad;
                inventario.agregarProducto(codigo, descripcion, cantidad);
                break;
            case 2:
                cout << "Ingrese codigo: ";
                cin >> codigo;
                cout << "Ingrese nueva cantidad: ";
                cin >> cantidad;
                inventario.actualizarCantidad(codigo, cantidad);
                break;
            case 3:
                cout << "Ingrese codigo: ";
                cin >> codigo;
                inventario.buscarProducto(codigo);
                break;
            case 4:
                inventario.mostrarProductosOrdenados();
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    return 0;
}
