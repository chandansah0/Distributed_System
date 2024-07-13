import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

// Create client
public class RMIClient {
    public static void main(String[] args) {
        try {
            // Get a reference to the remote object from the registry
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            RemoteInterface stub = (RemoteInterface) registry.lookup("RemoteInterface");

            // Invoke the remote method
            String response = stub.sayHello();
            System.out.println("Response from server: " + response);
        } catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
    }
}