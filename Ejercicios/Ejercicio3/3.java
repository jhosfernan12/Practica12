import java.util.*;

class Contacto 
{
    String nombre;
    String telefono;
    String email;

    public Contacto(String nom, String tel, String em)
  {
        nombre = nom;
        telefono = tel;
        email = em;
    }

    public void mostrarContacto() 
  {
        System.out.println("Nombre: " + nombre);
        System.out.println("Telefono: " + telefono);
        System.out.println("Email: " + email);
    }
}

class Agenda
  {
    List<Contacto> contactos;

    public Agenda() {
        contactos = new ArrayList<>();
    }

    public void agregarContacto(String nombre, String telefono, String email) {
        contactos.add(new Contacto(nombre, telefono, email));
        System.out.println("Contacto agregado exitosamente.");
    }

    public void buscarContacto(String nombre) {
        Optional<Contacto> contacto = contactos.stream().filter(c -> c.nombre.equals(nombre)).findFirst();
        if (contacto.isPresent()) {
            contacto.get().mostrarContacto();
        } else {
            System.out.println("Contacto no encontrado.");
        }
    }

    public void actualizarContacto(String nombre, String nuevoTelefono, String nuevoEmail) {
        Optional<Contacto> contacto = contactos.stream().filter(c -> c.nombre.equals(nombre)).findFirst();
        if (contacto.isPresent()) {
            contacto.get().telefono = nuevoTelefono;
            contacto.get().email = nuevoEmail;
            System.out.println("Contacto actualizado exitosamente.");
        } else {
            System.out.println("Contacto no encontrado.");
        }
    }

    public void mostrarContactosOrdenados() {
        List<Contacto> copiaContactos = new ArrayList<>(contactos);
        copiaContactos.sort(Comparator.comparing(c -> c.nombre));

        for (Contacto contacto : copiaContactos) {
            contacto.mostrarContacto();
            System.out.println("---------------------");
        }
    }
}

public class Main {
    public static void mostrarMenu() {
        System.out.println("Menu de Gestion de Contactos");
        System.out.println("1. Agregar contacto");
        System.out.println("2. Buscar contacto por nombre");
        System.out.println("3. Actualizar contacto");
        System.out.println("4. Mostrar contactos ordenados alfabeticamente");
        System.out.println("5. Salir");
    }

    public static void main(String[] args) {
        Agenda agenda = new Agenda();
        Scanner scanner = new Scanner(System.in);
        int opcion;

        do {
            mostrarMenu();
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();

            scanner.nextLine(); // Consume newline after reading int

            String nombre, telefono, email, nuevoTelefono, nuevoEmail;

            switch (opcion) {
                case 1:
                    System.out.print("Ingrese nombre del contacto: ");
                    nombre = scanner.nextLine();
                    System.out.print("Ingrese numero de telefono: ");
                    telefono = scanner.nextLine();
                    System.out.print("Ingrese direccion de correo electronico: ");
                    email = scanner.nextLine();
                    agenda.agregarContacto(nombre, telefono, email);
                    break;
                case 2:
                    System.out.print("Ingrese nombre del contacto a buscar: ");
                    nombre = scanner.nextLine();
                    agenda.buscarContacto(nombre);
                    break;
                case 3:
                    System.out.print("Ingrese nombre del contacto a actualizar: ");
                    nombre = scanner.nextLine();
                    System.out.print("Ingrese nuevo numero de telefono: ");
                    nuevoTelefono = scanner.nextLine();
                    System.out.print("Ingrese nuevo correo electronico: ");
                    nuevoEmail = scanner.nextLine();
                    agenda.actualizarContacto(nombre, nuevoTelefono, nuevoEmail);
                    break;
                case 4:
                    System.out.println("Listado de contactos ordenados alfabeticamente:");
                    agenda.mostrarContactosOrdenados();
                    break;
                case 5:
                    System.out.println("Saliendo...");
                    break;
                default:
                    System.out.println("Opcion no valida. Intente nuevamente.");
            }
        } while (opcion != 5);

        scanner.close();
    }
}
