import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class RemoteInterfaceImpl extends UnicastRemoteObject implements RemoteInterface {
    // Constructor
    protected RemoteInterfaceImpl() throws RemoteException {
        super();
    }

    // Implementation of the remote method
    public String sayHello() throws RemoteException {
        return "Hello, Remote World!";
    }
}