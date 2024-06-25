#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Contacto 
{
public:
    string nombre;
    string telefono;
    string email;

    Contacto(const string& nom, const string& tel, const string& em) 
        : nombre(nom), telefono(tel), email(em) {}

    void mostrarContacto() const 
    {
        cout << "Nombre: " << nombre << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Email: " << email << endl;
    }
};

class Agenda 
{
private:
    vector<Contacto> contactos;

public:
    void agregarContacto(const string& nombre, const string& telefono, const string& email) 
    {
        contactos.push_back(Contacto(nombre, telefono, email));
        cout << "Contacto agregado exitosamente." << endl;
    }

    void buscarContacto(const string& nombre) const 
    {
        auto it = find_if(contactos.begin(), contactos.end(),
                          [&nombre](const Contacto& c) { return c.nombre == nombre; });

        if (it != contactos.end()) 
        {
            it->mostrarContacto();
        } 
        else 
        {
            cout << "Contacto no encontrado." << endl;
        }
    }

    void actualizarContacto(const string& nombre, const string& nuevoTelefono, const string& nuevoEmail) 
    {
        auto it = find_if(contactos.begin(), contactos.end(),
                          [&nombre](const Contacto& c) { return c.nombre == nombre; });

        if (it != contactos.end()) 
        {
            it->telefono = nuevoTelefono;
            it->email = nuevoEmail;
            cout << "Contacto actualizado exitosamente." << endl;
        } 
        else 
        {
            cout << "Contacto no encontrado." << endl;
        }
    }

    void mostrarContactosOrdenados() const 
    {
        vector<Contacto> copiaContactos = contactos;
        sort(copiaContactos.begin(), copiaContactos.end(),
             [](const Contacto& a, const Contacto& b) { return a.nombre < b.nombre; });

        for (const auto& contacto : copiaContactos) 
        {
            contacto.mostrarContacto();
            cout << "---------------------" << endl;
        }
    }
};

void mostrarMenu() 
{
    cout << "Menu de Gestion de Contactos" << endl;
    cout << "1. Agregar contacto" << endl;
    cout << "2. Buscar contacto por nombre" << endl;
    cout << "3. Actualizar contacto" << endl;
    cout << "4. Mostrar contactos ordenados alfabeticamente" << endl;
    cout << "5. Salir" << endl;
}

int main() 
{
    Agenda agenda;
    int opcion;
    do 
    {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        string nombre, telefono, email, nuevoTelefono, nuevoEmail;

        switch (opcion) 
        {
            case 1:
                cout << "Ingrese nombre del contacto: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese numero de telefono: ";
                getline(cin, telefono);
                cout << "Ingrese direccion de correo electronico: ";
                getline(cin, email);
                agenda.agregarContacto(nombre, telefono, email);
                break;
            case 2:
                cout << "Ingrese nombre del contacto a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                agenda.buscarContacto(nombre);
                break;
            case 3:
                cout << "Ingrese nombre del contacto a actualizar: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nuevo numero de telefono: ";
                getline(cin, nuevoTelefono);
                cout << "Ingrese nuevo correo electronico: ";
                getline(cin, nuevoEmail);
                agenda.actualizarContacto(nombre, nuevoTelefono, nuevoEmail);
                break;
            case 4:
                cout << "Listado de contactos ordenados alfabeticamente:" << endl;
                agenda.mostrarContactosOrdenados();
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
