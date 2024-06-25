#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Evento 
{
public:
    string nombre;
    string fecha;
    vector<string> asistentes;

    Evento(string nom, string fec) : nombre(nom), fecha(fec) {}

    void agregarAsistente(const string& asistente)
     {
        asistentes.push_back(asistente);
        sort(asistentes.begin(), asistentes.end());
    }

    void mostrarAsistentes() const 
    {
        for (const auto& asistente : asistentes) 
        {
            cout << asistente << endl;
        }
    }
};

class Organizador 
{
private:
    vector<Evento> eventos;

public:
    void agregarEvento(const string& nombre, const string& fecha) 
    {
        auto it = find_if(eventos.begin(), eventos.end(),
        [&nombre](const Evento& evento) { return evento.nombre == nombre; });

        if (it != eventos.end()) {
            cout << "Evento con el nombre " << nombre << " ya existe." << endl;
            return;
        }

        eventos.push_back(Evento(nombre, fecha));
        cout << "Evento agregado exitosamente." << endl;
    }

    void agregarAsistente(const string& nombreEvento, const string& asistente) 
    {
        auto it = find_if(eventos.begin(), eventos.end(),
                          [&nombreEvento](const Evento& evento) { return evento.nombre == nombreEvento; });

        if (it != eventos.end()) 
        {
            it->agregarAsistente(asistente);
            cout << "Asistente agregado exitosamente." << endl;
        }
         else 
        {
            cout << "Evento no encontrado." << endl;
        }
    }

    void mostrarAsistentes(const string& nombreEvento) const 
    {
        auto it = find_if(eventos.begin(), eventos.end(),
                          [&nombreEvento](const Evento& evento) { return evento.nombre == nombreEvento; });

        if (it != eventos.end()) 
        {
            it->mostrarAsistentes();
        } 
        else 
        {
            cout << "Evento no encontrado." << endl;
        }
    }

    void buscarEventosPorFecha(const string& fecha) const 
    {
        bool encontrado = false;
        for (const auto& evento : eventos)
         {
            if (evento.fecha == fecha) 
            {
                cout << "Evento: " << evento.nombre << endl;
                encontrado = true;
            }
        }
        if (!encontrado) 
        {
            cout << "No se encontraron eventos en la fecha " << fecha << endl;
        }
    }
};

void mostrarMenu() 
{
    cout << "Menu de Gestion de Eventos" << endl;
    cout << "1. Agregar evento" << endl;
    cout << "2. Agregar asistente a evento" << endl;
    cout << "3. Mostrar asistentes de un evento" << endl;
    cout << "4. Buscar eventos por fecha" << endl;
    cout << "5. Salir" << endl;
}

int main() 
{
    Organizador organizador;
    int opcion;
    do 
    {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        string nombre, fecha, asistente;

        switch (opcion)
         {
            case 1:
                cout << "Ingrese nombre del evento: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese fecha del evento: ";
                getline(cin, fecha);
                organizador.agregarEvento(nombre, fecha);
                break;
            case 2:
                cout << "Ingrese nombre del evento: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese nombre del asistente: ";
                getline(cin, asistente);
                organizador.agregarAsistente(nombre, asistente);
                break;
            case 3:
                cout << "Ingrese nombre del evento: ";
                cin.ignore();
                getline(cin, nombre);
                organizador.mostrarAsistentes(nombre);
                break;
            case 4:
                cout << "Ingrese fecha del evento (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fecha);
                organizador.buscarEventosPorFecha(fecha);
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
