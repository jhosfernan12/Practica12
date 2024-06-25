import java.util.*;

class Producto {
    String codigo;
    String descripcion;
    int cantidad;

    public Producto(String cod, String desc, int cant) {
        codigo = cod;
        descripcion = desc;
        cantidad = cant;
    }
}

class Inventario {
    private Map<String, Producto> productos = new HashMap<>();

    public void agregarProducto(String codigo, String descripcion, int cantidad) {
        if (productos.containsKey(codigo)) {
            System.out.println("Producto con el codigo " + codigo + " ya existe.");
            return;
        }
        productos.put(codigo, new Producto(codigo, descripcion, cantidad));
        System.out.println("Producto agregado exitosamente.");
    }

    public void actualizarCantidad(String codigo, int cantidad) {
        if (productos.containsKey(codigo)) {
            productos.get(codigo).cantidad = cantidad;
            System.out.println("Cantidad actualizada exitosamente.");
        } else {
            System.out.println("Producto no encontrado.");
        }
    }

    public void buscarProducto(String codigo) {
        if (productos.containsKey(codigo)) {
            Producto prod = productos.get(codigo);
            System.out.println("Codigo: " + prod.codigo +
                               ", Descripcion: " + prod.descripcion +
                               ", Cantidad: " + prod.cantidad);
        } else {
            System.out.println("Producto no encontrado.");
        }
    }

    public void mostrarProductosOrdenados() {
        List<Producto> listaProductos = new ArrayList<>(productos.values());

        listaProductos.sort(Comparator.comparing(p -> p.descripcion));

        for (Producto prod : listaProductos) {
            System.out.println("Codigo: " + prod.codigo +
                               ", Descripcion: " + prod.descripcion +
                               ", Cantidad: " + prod.cantidad);
        }
    }
}

public class Main {
    public static void mostrarMenu() {
        System.out.println("Menu de Gestion de Inventario");
        System.out.println("1. Agregar producto");
        System.out.println("2. Actualizar cantidad");
        System.out.println("3. Buscar producto");
        System.out.println("4. Mostrar productos ordenados por descripcion");
        System.out.println("5. Salir");
    }

    public static void main(String[] args) {
        Inventario inventario = new Inventario();
        Scanner scanner = new Scanner(System.in);
        int opcion;

        do {
            mostrarMenu();
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();

            String codigo, descripcion;
            int cantidad;

            switch (opcion) {
                case 1:
                    System.out.print("Ingrese codigo: ");
                    codigo = scanner.next();
                    scanner.nextLine(); // consume newline
                    System.out.print("Ingrese descripcion: ");
                    descripcion = scanner.nextLine();
                    System.out.print("Ingrese cantidad: ");
                    cantidad = scanner.nextInt();
                    inventario.agregarProducto(codigo, descripcion, cantidad);
                    break;
                case 2:
                    System.out.print("Ingrese codigo: ");
                    codigo = scanner.next();
                    System.out.print("Ingrese nueva cantidad: ");
                    cantidad = scanner.nextInt();
                    inventario.actualizarCantidad(codigo, cantidad);
                    break;
                case 3:
                    System.out.print("Ingrese codigo: ");
                    codigo = scanner.next();
                    inventario.buscarProducto(codigo);
                    break;
                case 4:
                    inventario.mostrarProductosOrdenados();
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
