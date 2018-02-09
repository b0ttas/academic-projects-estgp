package edu.estgp.sdis;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class Main {
    /**
     * Starts a server/client according to the given arguments.
     */
    public static void main(String[] args) {
        int PORT = 1234;
        String HOST = "192.168.103.79";
        try {
            String option = "";
            while (!option.equals("exit")) {
                Scanner scanIn = new Scanner(System.in);
                option = scanIn.nextLine();
                switch (option) {
                    case "server":
                        new CalendarServerImpl(PORT);
                        break;
                    case "client":
                        (new CalendarClient(HOST, PORT)).run();
                        break;
                    case "exit":
                        break;
                    default:
                        System.out.println("Available options: type \"server\", \"client\", \"exit\".");
                        break;
                }
            }
            // throw new IllegalArgumentException();
        } catch (ArrayIndexOutOfBoundsException | NumberFormatException e) {
            System.err.println(e);
        } catch (IllegalArgumentException e) {
            System.err.println(e);
        } catch (RemoteException e) {
            System.err.println("Can't connect. (RemoteException)\n" + e);
        } catch (NotBoundException e) {
            System.err.println("Can't connect. (NotBoundException)\n" + e);
        }
    }
}