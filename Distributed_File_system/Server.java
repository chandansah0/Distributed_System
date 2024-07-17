// Lab:4 Date: 2081/04/02 //
// Title: Implementation of distributed file sytsem (DFS)
// Objectives;
// 1. To understand the concept of DFS
// 2. To implement DFS for storing and retrieving files

// Server.java

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Server {

    private static final int PORT = 8080;
    private static final Logger LOGGER = Logger.getLogger(Server.class.getName());

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is listening on port " + PORT);

            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("New client connected");

                new ServerThread(socket).start();
            }
        } catch (IOException ex) {
            LOGGER.log(Level.SEVERE, "Server exception: " + ex.getMessage(), ex);
        }
    }
}

class ServerThread extends Thread {

    private final Socket socket;

    public ServerThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try (
                InputStream input = socket.getInputStream(); BufferedReader reader = new BufferedReader(new InputStreamReader(input)); OutputStream output = socket.getOutputStream()) {
            String command = reader.readLine();

            if ("UPLOAD".equalsIgnoreCase(command)) {
                String fileName = reader.readLine();
                try (FileOutputStream fileOutput = new FileOutputStream(fileName)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = input.read(buffer)) != -1) {
                        fileOutput.write(buffer, 0, bytesRead);
                    }
                }
                System.out.println("File " + fileName + " uploaded successfully");
            } else if ("DOWNLOAD".equalsIgnoreCase(command)) {
                String fileName = reader.readLine();
                File file = new File(fileName);
                try (FileInputStream fileInput = new FileInputStream(file)) {
                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = fileInput.read(buffer)) != -1) {
                        output.write(buffer, 0, bytesRead);
                    }
                }
                System.out.println("File " + fileName + " sent successfully");
            }

        } catch (IOException ex) {
            Logger.getLogger(ServerThread.class.getName()).log(Level.SEVERE, "ServerThread exception: " + ex.getMessage(), ex);
        } finally {
            try {
                socket.close();
            } catch (IOException ex) {
                Logger.getLogger(ServerThread.class.getName()).log(Level.SEVERE, "Could not close socket", ex);
            }
        }
    }
}



//To run this code 
//step1: Open Terminal
//step2: javac Server.java
//step3: java Server
//step4: Display Server is listening on port 8080