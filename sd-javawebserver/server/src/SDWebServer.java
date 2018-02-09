
import java.io.*;
import java.net.Socket;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.io.BufferedReader;
import java.net.*;
import java.util.Scanner;
import java.text.SimpleDateFormat;

import static java.lang.System.in;

/**
 * Web Server implementation
 */
public class SDWebServer {

    private final static int PORT = 1234;

    // FILEPATH points to root of web server files
    private final static String FILEPATH = "C:/Users/" + System.getProperty("user.name") + "/Desktop/server/www/";
    private final static String SERVERSTRING = "Server: SD Multithreaded WebServer";
    // private static String formdata;

    /**
     * Hash Map with keys/values linked to the type of file requested
     * used to send an apropriate response
     *
     * @param mimeMap
     */
    private static final Map<String, String> mimeMap = new HashMap<String, String>() {{
        put("htm", "text/html");
        put("html", "text/html");
        put("css", "text/css");
        put("jpg", "image/jpg");
        put("jpeg", "image/jpeg");
        put("png", "image/png");
        put("pdf", "application/pdf");
        put("js", "application/js");
    }};

    /**
     * Response Header Construction
     * Writes the header for the response
     *
     * @param code   the HTTP response code
     * @param mime   the Content-Type of the response
     * @param length the length of said content
     * @param out    the stream where the response is written
     * @throws Exception
     */
    private static void respondHeader(String code, String mime, int length, DataOutputStream out) throws Exception {
        System.out.println(" (" + code + ") ");
        out.writeBytes("HTTP/1.0 " + code + " OK\r\n");
        out.writeBytes("Connection: keep-alive\r\n");
        out.writeBytes("Content-Type: " + mimeMap.get(mime) + "\r\n");
        out.writeBytes("Content-Length: " + length + "\r\n");
        out.writeBytes(SERVERSTRING);
        out.writeBytes("\r\n\r\n");
    }

    /**
     * Response Header Construction - POST
     * Returns HTML with the response content in case there's a POST request
     *
     * @param out      the output stream
     * @param formdata the string with the data from the request
     * @throws Exception
     */
    private static void respondHeaderPost(DataOutputStream out, String formdata) throws Exception {

        out.writeBytes("<html><title>[POST] Results</title><body><h1>[POST] Results</h1><br />");

        String var;
        var = formdata.replaceAll("\\r\\n", "<br/>");
        out.writeBytes(var);

        out.writeBytes("</body></html>");
    }

    /**
     * Method to interpret the requests and send the appropriate response
     *
     * @param inString the data read from the socket
     * @param out      the output stream
     * @param in       the buffered reader
     * @throws Exception
     */
    private static void respondContent(String inString, DataOutputStream out, BufferedReader in) throws Exception {
        String method = inString.substring(0, inString.indexOf("/") - 1);
        String file = inString.substring(inString.indexOf("/") + 1, inString.lastIndexOf("/") - 5);

        // Set default file to index.html
        if (file.equals(""))
            file = "index.html";

        String mime = file.substring(file.indexOf(".") + 1);

        // Return if trying to load file outside of web server root
        Path path = Paths.get(FILEPATH, file);
        if (!path.startsWith(FILEPATH)) {
            System.out.println(" (Dropping connection) ");
            return;
        }

        // Return if file contains potentially bad string
        if (file.contains(";") || file.contains("*")) {
            System.out.println(" (Dropping connection)");
            return;
        }

        if (method.equals("GET")) {
            try {
                // Open file
                byte[] fileBytes = null;
                InputStream is = new FileInputStream(FILEPATH + file);
                fileBytes = new byte[is.available()];
                is.read(fileBytes);

                // Send header
                respondHeader("200", mime, fileBytes.length, out);

                // Write content of file
                out.write(fileBytes);

            } catch (FileNotFoundException e) {
                // Try to use status404.html
                try {
                    byte[] fileBytes = null;
                    InputStream is = new FileInputStream(FILEPATH + "status404.html");
                    fileBytes = new byte[is.available()];
                    is.read(fileBytes);
                    respondHeader("404", "html", fileBytes.length, out);
                    out.write(fileBytes);
                } catch (FileNotFoundException e2) {
                    String responseString = "404 File Not Found";
                    respondHeader("404", "html", responseString.length(), out);
                    out.write(responseString.getBytes());
                }
            }
        } else if (method.equals("POST")) {
            byte[] fileBytes;
            InputStream is = new FileInputStream(FILEPATH + file);
            fileBytes = new byte[is.available()];
            char formDATA[] = new char[fileBytes.length];

            in.read(formDATA, 0, fileBytes.length);
            String formdata = new String(formDATA);
            System.out.println("[POST] \n" + formdata);
            //formdata = formdata.substring(formdata.lastIndexOf("BOS_Locale=en") + 16);

            respondHeader("200", mime, fileBytes.length, out);
            respondHeaderPost(out, formdata);

        } else if (method.equals("HEAD")) {
            respondHeader("200", "html", 0, out);
        } else {
            respondHeader("501", "html", 0, out);
        }
    }

    /**
     * Manages the socket connections and gives information to the user
     */
    private static class WorkerRunnable implements Runnable {

        protected Socket socket = null;

        BufferedReader in;
        DataOutputStream out;
        String inString;

        /**
         * Manipulates the socket, reads it and prints some information to the console
         *
         * @param connectionSocket the socket
         * @throws Exception
         */
        public WorkerRunnable(Socket connectionSocket) throws Exception {
            this.socket = connectionSocket;
            this.in = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
            this.out = new DataOutputStream(this.socket.getOutputStream());


            this.inString = this.in.readLine();

            Calendar cal = Calendar.getInstance();
            cal.getTime();
            SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
            String time = "[" + sdf.format(cal.getTime()) + "] ";
            System.out.print(time + this.socket.getInetAddress().toString() + " " + this.inString);
        }

        /**
         * Manages the output of sent response, prints connection state
         */
        public void run() {

            System.out.println();
            System.out.println("[OPEN] Connection accepted: " + socket);

            try {
                if (this.inString != null)
                    respondContent(this.inString, this.out, this.in);

                this.out.flush();
                this.out.close();
                this.in.close();

                System.out.println("[CLOSE] Connection terminated: " + socket);

                System.out.print("--> ");

            } catch (Exception e) {
                System.out.println("Error flushing or closing");
            }

        }

    }

    /**
     * Scanner to read user commands
     *
     * @return scanned input by the user
     */
    private static String read() {

        String scanned;
        Scanner scanIn = new Scanner(in);

        scanned = scanIn.next();
        //scanIn.close();
        return scanned;
    }

    /**
     * Method that instanciates the control of the server
     * according to user interaction
     */
    public static class RunnableOption implements Runnable {
        private int var;
        List<Thread> clients = new ArrayList<Thread>();
        private Thread client;

        /**
         * Sets an option var to control behaviour
         */
        public RunnableOption(int var) {
            this.var = var;
        }

        /**
         * Starts the server by establishing a connection with a socket
         *
         * @throws Exception
         */
        public void start() throws Exception {
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println("[READY] " + serverSocket);

            for (; ; ) {
                try {
                    Socket connectionSocket = serverSocket.accept();
                    client = new Thread(new WorkerRunnable(connectionSocket));
                    client.start();
                    clients.add(client);

                    if (Thread.interrupted()) {
                        System.out.println("Server is stopped....");
                        break;
                    }
                } catch (InterruptedException e) {
                    System.out.println("Interrupt Failed");
                }
            }
        }

        /**
         * Stops the server by killing every active thread
         *
         * @throws Exception
         */
        public void stop() throws Exception {
            System.out.print("--> ");

            if (clients.size() > 0) {
                System.out.println("Killing all threads..");

                for (int i = 0; i < clients.size(); i++) {
                    client.interrupt();
                    System.out.println(clients.get(i).getName() + " .. Check.");
                }
                clients.clear();
                System.out.println("...Done!");
            } else {
                System.out.println("[ERROR] There are no active server threads");
                System.out.print("--> ");
            }
        }

        /**
         * Lists every active thread in the CLI
         *
         * @throws Exception
         */
        public void list() throws Exception {
            if (clients.size() > 0) {
                for (int i = 0; i < clients.size(); i++) {
                    System.out.println(clients.get(i).getName()); // print serverSocket for read Thread
                }
            } else {
                System.out.println("[ERROR] There are no active server threads");
                System.out.print("--> ");
            }

        }

        @Override
        /**
         * Method ran on start to which control is given to the current state of the var
         * variable, accordingly sending the control to the respective method
         */
        public void run() {
            switch (var) {
                case 0:
                    try {
                        start();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    break;
                case 1:
                    try {
                        stop();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    break;
                case 2:
                    try {
                        list();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    break;
            }
        }
    }

    /**
     * CLI interface of the server
     * to each possible action start, list, stop a thread is created to
     * satisfy the user requests
     */
    public static void main(String args[]) throws Exception {

        String option;

        System.out.println();
        System.out.println("/////////////////////////////////////////");
        System.out.println("//// Java WebServer Assignment - SD  ////");
        System.out.println("/////////////////////////////////////////");
        System.out.println();
        System.out.println("Available commands: start, stop, list");
        System.out.println();

        System.out.print("--> ");

        while (true) {
            option = read();

            RunnableOption server;

            switch (option) {
                case "start":
                    server = new RunnableOption(0);
                    Thread t0 = new Thread(server);
                    t0.start();
                    break;

                case "stop":
                    server = new RunnableOption(1);
                    Thread t1 = new Thread(server);
                    t1.start();
                    break;

                case "list":
                    server = new RunnableOption(2);
                    Thread t2 = new Thread(server);
                    t2.start();
                    break;

                default:
                    System.out.println("Command not available");
                    System.out.println("Available commands: start, stop, list");
                    System.out.print("--> ");
                    break;
            }
        }
    }
}
