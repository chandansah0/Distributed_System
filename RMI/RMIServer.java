import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

// Create server
public class RMIServer {
    public static void main(String[] args) {
        try {
            // Create an instance of the remote object
            RemoteInterfaceImpl obj = new RemoteInterfaceImpl();

            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("RemoteInterface", obj);

            System.out.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}