// Lab:4 Date: 2081/04/02 //
// Client.java

import java.io.*;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Client {

    private static final String SERVER_ADDRESS = "127.0.0.1";
    private static final int SERVER_PORT = 8080;
    private static final Logger LOGGER = Logger.getLogger(Client.class.getName());

    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT); OutputStream output = socket.getOutputStream(); PrintWriter writer = new PrintWriter(output, true); InputStream input = socket.getInputStream(); BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in))) {

            System.out.print("Enter command (UPLOAD/DOWNLOAD): ");
            String command = consoleReader.readLine();
            writer.println(command);

            System.out.print("Enter file name: ");
            String fileName = consoleReader.readLine();
            writer.println(fileName);

            if ("UPLOAD".equalsIgnoreCase(command)) {
                File file = new File(fileName);
                try (FileInputStream fileInput = new FileInputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = fileInput.read(buffer)) != -1) {
                        output.write(buffer, 0, bytesRead);
                    }
                }
                System.out.println("File " + fileName + " uploaded successfully");
            } else if ("DOWNLOAD".equalsIgnoreCase(command)) {
                try (FileOutputStream fileOutput = new FileOutputStream(fileName)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = input.read(buffer)) != -1) {
                        fileOutput.write(buffer, 0, bytesRead);
                    }
                }
                System.out.println("File " + fileName + " downloaded successfully");
            }
        } catch (IOException ex) {
            LOGGER.log(Level.SEVERE, "Client exception: " + ex.getMessage(), ex);
        }
    }
}


//To run this code 
//step1: Open Terminal
//step2: javac Client.java
//step3: java Client
//step4:Choose command (Eg. upload)
//step4: enter file_name
//step6:display file_name uploaded successfully