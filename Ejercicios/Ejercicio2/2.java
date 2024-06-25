import java.util.*;

class Evento 
{
    String nombre;
    String fecha;
    List<String> asistentes;

    public Evento(String nom, String fec) 
  {
        nombre = nom;
        fecha = fec;
        asistentes = new ArrayList<>();
    }

    public void agregarAsistente(String asistente)
  {
        asistentes.add(asistente);
        Collections.sort(asistentes);
    }

    public void mostrarAsistentes() 
  {
        for (String asistente : asistentes)
          {
            System.out.println(asistente);
        }
    }
}

class Organizador
  {
    List<Evento> eventos;

    public Organizador()
    {
        eventos = new ArrayList<>();
    }

    public void agregarEvento(String nombre, String fecha) 
    {
        boolean existe = eventos.stream().anyMatch(evento -> evento.nombre.equals(nombre));
        if (existe)
        {
            System.out.println("Evento con el nombre " + nombre + " ya existe.");
            return;
        }
        eventos.add(new Evento(nombre, fecha));
        System.out.println("Evento agregado exitosamente.");
    }

    public void agregarAsistente(String nombreEvento, String asistente)
    {
        Optional<Evento> evento = eventos.stream().filter(e -> e.nombre.equals(nombreEvento)).findFirst();
        if (evento.isPresent()) 
        {
            evento.get().agregarAsistente(asistente);
            System.out.println("Asistente agregado exitosamente.");
        } 
        else 
        {
            System.out.println("Evento no encontrado.");
        }
    }

    public void mostrarAsistentes(String nombreEvento)
    {
        Optional<Evento> evento = eventos.stream().filter(e -> e.nombre.equals(nombreEvento)).findFirst();
        if (evento.isPresent()) 
        {
            evento.get().mostrarAsistentes();
        } 
        else
        {
            System.out.println("Evento no encontrado.");
        }
    }

    public void buscarEventosPorFecha(String fecha)
    {
        boolean encontrado = false;
        for (Evento evento : eventos) 
        {
            if (evento.fecha.equals(fecha)) 
            {
                System.out.println("Evento: " + evento.nombre);
                encontrado = true;
            }
        }
        if (!encontrado) 
        {
            System.out.println("No se encontraron eventos en la fecha " + fecha);
        }
    }
}

public class Main {
    public static void mostrarMenu()
  {
        System.out.println("Menu de Gestion de Eventos");
        System.out.println("1. Agregar evento");
        System.out.println("2. Agregar asistente a evento");
        System.out.println("3. Mostrar asistentes de un evento");
        System.out.println("4. Buscar eventos por fecha");
        System.out.println("5. Salir");
    }

    public static void main(String[] args)
  {
        Organizador organizador = new Organizador();
        Scanner scanner = new Scanner(System.in);
        int opcion;

        do {
            mostrarMenu();
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();

            scanner.nextLine(); 
            String nombre, fecha, asistente;

            switch (opcion) {
                case 1:
                    System.out.print("Ingrese nombre del evento: ");
                    nombre = scanner.nextLine();
                    System.out.print("Ingrese fecha del evento: ");
                    fecha = scanner.nextLine();
                    organizador.agregarEvento(nombre, fecha);
                    break;
                case 2:
                    System.out.print("Ingrese nombre del evento: ");
                    nombre = scanner.nextLine();
                    System.out.print("Ingrese nombre del asistente: ");
                    asistente = scanner.nextLine();
                    organizador.agregarAsistente(nombre, asistente);
                    break;
                case 3:
                    System.out.print("Ingrese nombre del evento: ");
                    nombre = scanner.nextLine();
                    organizador.mostrarAsistentes(nombre);
                    break;
                case 4:
                    System.out.print("Ingrese fecha del evento (YYYY-MM-DD): ");
                    fecha = scanner.nextLine();
                    organizador.buscarEventosPorFecha(fecha);
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
