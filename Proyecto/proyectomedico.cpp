#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

// Clase base abstracta para datos medicos
class DatoMedico 
{
protected:
    string fecha;
    int idPaciente;

public:
    DatoMedico(const string& f, int id) : fecha(f), idPaciente(id) {}

    int getIdPaciente() const
    {
        return idPaciente;
    }

    virtual void mostrarDetalles() const = 0;
    virtual void guardar(ofstream& out) const = 0;
    virtual ~DatoMedico() {}
};

// Clase derivada para registro de pacientes
class RegistroPaciente : public DatoMedico 
{
private:
    string nombre;
    int edad;

public:
    RegistroPaciente(const string& f, int id, const string& nom, int ed): DatoMedico(f, id), nombre(nom), edad(ed) {}

    void mostrarDetalles() const override 
    {
        cout << "Registro del Paciente:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Nombre: " << nombre << "\nEdad: " << edad << "\n";
    }

    void guardar(ofstream& out) const override
    {
        out << "RegistroPaciente " << fecha << " " << idPaciente << " " << nombre << " " << edad << "\n";
    }

    static RegistroPaciente* cargar(ifstream& in)
    {
        string fecha, nombre;
        int id, edad;
        in >> fecha >> id >> nombre >> edad;
        return new RegistroPaciente(fecha, id, nombre, edad);
    }
};

// Clase derivada para resultado de examenes
class ResultadoExamen : public DatoMedico 
{
private:
    string tipoExamen;
    string resultado;

public:
    ResultadoExamen(const string& f, int id, const string& tipo, const string& res): DatoMedico(f, id), tipoExamen(tipo), resultado(res) {}

    void mostrarDetalles() const override 
    {
        cout << "Resultado de Examen:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Tipo de Examen: " << tipoExamen << "\nResultado: " << resultado << "\n";
    }

    void guardar(ofstream& out) const override
    {
        out << "ResultadoExamen " << fecha << " " << idPaciente << " " << tipoExamen << " " << resultado << "\n";
    }

    static ResultadoExamen* cargar(ifstream& in)
    {
        string fecha, tipoExamen, resultado;
        int id;
        in >> fecha >> id >> tipoExamen;
        in.ignore();
        getline(in, resultado);
        return new ResultadoExamen(fecha, id, tipoExamen, resultado);
    }
};

// Clase derivada para historial clinico
class HistorialClinico : public DatoMedico 
{
private:
    string descripcion;

public:
    HistorialClinico(const string& f, int id, const string& desc): DatoMedico(f, id), descripcion(desc) {}

    void mostrarDetalles() const override 
    {
        cout << "Historial Clinico:\n";
        cout << "Fecha: " << fecha << "\nID Paciente: " << idPaciente << "\n";
        cout << "Descripcion: " << descripcion << "\n";
    }

    void guardar(ofstream& out) const override
    {
        out << "HistorialClinico " << fecha << " " << idPaciente << " " << descripcion << "\n";
    }

    static HistorialClinico* cargar(ifstream& in)
    {
        string fecha, descripcion;
        int id;
        in >> fecha >> id;
        in.ignore();
        getline(in, descripcion);
        return new HistorialClinico(fecha, id, descripcion);
    }
};

// Clase template para manejar registros medicos
template <typename T>
class RegistroMedico 
{
private:
    vector<T*> datos;

    void ordenarPorId()  
    {
        sort(datos.begin(), datos.end(), [](T* a, T* b)  // Sort para el ordenamiento por ID
        {
            return a->getIdPaciente() < b->getIdPaciente();
        });
    }

public:
    RegistroMedico() {}

    bool agregarDato(T* dato) 
    {
        if (buscarDato(dato->getIdPaciente()) != nullptr) 
        {
            cerr << "Error: Ya existe un dato con el ID " << dato->getIdPaciente() << ". No se puede agregar.\n";
            return false;
        }

        datos.push_back(dato);
        ordenarPorId();
        return true;
    }

    bool eliminarDato(int id) 
    {
        auto it = remove_if(datos.begin(), datos.end(), [id](T* dato)
         {
            if (dato->getIdPaciente() == id) 
            {
                delete dato;
                return true;
            }
            return false;
        });

        if (it != datos.end()) 
        {
            datos.erase(it, datos.end());
            return true;
        }
        return false;
    }

    T* buscarDato(int id) const 
    {
        for (const auto& dato : datos)
        {
            if (dato->getIdPaciente() == id) 
            {
                return dato;
            }
        }
        return nullptr;
    }

    void listarDatos() const 
    {
        for (const auto& dato : datos) 
        {
            dato->mostrarDetalles();
            cout << "==============================\n";
        }
    }

    void guardarEnArchivo(const string& nombreArchivo) const
    {
        ofstream out(nombreArchivo);
        for (const auto& dato : datos)
        {
            dato->guardar(out);
        }
        out.close();
        cout << "Datos guardados en " << nombreArchivo << ".\n";
    }

    void cargarDesdeArchivo(const string& nombreArchivo)
    {
        ifstream in(nombreArchivo);
        string tipo;
        while (in >> tipo)
        {
            if (tipo == "RegistroPaciente")
            {
                datos.push_back(RegistroPaciente::cargar(in));
            }
            else if (tipo == "ResultadoExamen")
            {
                datos.push_back(ResultadoExamen::cargar(in));
            }
            else if (tipo == "HistorialClinico")
            {
                datos.push_back(HistorialClinico::cargar(in));
            }
            else
            {
                cerr << "Tipo de dato desconocido encontrado en el archivo\n";
            }
        }
        in.close();
        cout << "Datos cargados desde " << nombreArchivo << ".\n";
    }

    ~RegistroMedico() 
    {
        for (auto& dato : datos) 
        {
            delete dato;
        }
    }
};

void mostrarMenu() 
{
    cout << "================MENU================\n";
    cout << "1. Listar todos los datos\n";
    cout << "2. Buscar dato por ID\n";
    cout << "3. Eliminar dato por ID\n";
    cout << "4. Agregar nuevo dato\n";
    cout << "5. Guardar datos en archivo\n";
    cout << "6. Cargar datos desde archivo\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

void agregarNuevoDato(RegistroMedico<DatoMedico>& registro) 
{
    int tipoDato;
    cout << "Seleccione el tipo de dato a agregar:\n";
    cout << "1. Registro de Paciente\n";
    cout << "2. Resultado de Examen\n";
    cout << "3. Historial Clinico\n";

    cout << "Seleccione una opcion: ";
    cin >> tipoDato;

    string fecha;
    int idPaciente;
    cout << "Ingrese la fecha (DD-MM-AAAA): ";
    cin >> fecha;
    cout << "Ingrese el ID del paciente: ";
    cin >> idPaciente;

    if (tipoDato == 1) 
    {
        string nombre;
        int edad;
        cout << "Ingrese el nombre del paciente: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese la edad del paciente: ";
        cin >> edad;
        registro.agregarDato(new RegistroPaciente(fecha, idPaciente, nombre, edad));

    } 
    else if (tipoDato == 2) 
    {
        string tipoExamen, resultado;
        cout << "Ingrese el tipo de examen: ";
        cin.ignore();
        getline(cin, tipoExamen);
        cout << "Ingrese el resultado del examen: ";
        getline(cin, resultado);
        registro.agregarDato(new ResultadoExamen(fecha, idPaciente, tipoExamen, resultado));

    }
    else if (tipoDato == 3) 
    {
        string descripcion;
        cout << "Ingrese la descripcion del historial clinico: ";
        cin.ignore();
        getline(cin, descripcion);
        registro.agregarDato(new HistorialClinico(fecha, idPaciente, descripcion));
    }
}

int main() 
{
    RegistroMedico<DatoMedico> registro;
    registro.agregarDato(new RegistroPaciente("08-06-2005", 1, "Jorge Vasquez", 30));
    registro.agregarDato(new ResultadoExamen("04-09-2026", 2, "Sangre", "Normal"));
    registro.agregarDato(new HistorialClinico("10-12-2025", 3, "Paciente con historial de catatonia"));

    int opcion;
    do 
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) 
        {
            case 1:
                cout << "Listado de datos medicos:\n";
                cout << "============================\n";
                registro.listarDatos();
                break;
            case 2: 
            {
                int idABuscar;
                cout << "Ingrese el ID del paciente a buscar: ";
                cin >> idABuscar;
                DatoMedico* encontrado = registro.buscarDato(idABuscar);
                if (encontrado) 
                {
                    cout << "Dato medico encontrado con ID " << idABuscar << ":\n";
                     cout << "===========DATO("<< idABuscar <<")==========" << endl;
                    encontrado->mostrarDetalles();
                    cout << "============================" << endl;
                } 
                else 
                {
                    cout << "No se encontro dato medico con el ID: " << idABuscar << "\n";
                }
                break;
            }
            case 3: 
            {
                int idAEliminar;
                cout << "Ingrese el ID del paciente a eliminar: ";
                cin >> idAEliminar;
                if (registro.eliminarDato(idAEliminar)) 
                {
                    cout << "Dato medico con ID " << idAEliminar << " eliminado.\n";
                } 
                else 
                {
                    cout << "No se encontro dato medico con el ID: " << idAEliminar << ".\n";
                }
                break;
            }
            case 4:
                agregarNuevoDato(registro);
                break;
            case 5:
            {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo para guardar: ";
                cin >> nombreArchivo;
                registro.guardarEnArchivo(nombreArchivo);
                break;
            }
            case 6:
            {
                string nombreArchivo;
                cout << "Ingrese el nombre del archivo para cargar: ";
                cin >> nombreArchivo;
                registro.cargarDesdeArchivo(nombreArchivo);
                break;
            }
            case 7:
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Opcion invalida \n";
        }

    } while (opcion != 7);

    return 0;
}
