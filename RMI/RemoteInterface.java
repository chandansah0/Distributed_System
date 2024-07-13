import java.rmi.Remote;
import java.rmi.RemoteException;

// Define remote interface
public interface RemoteInterface extends Remote {
    String sayHello() throws RemoteException;
}