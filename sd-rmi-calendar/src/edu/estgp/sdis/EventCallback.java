package edu.estgp.sdis;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface EventCallback extends Remote {

    /**
     * the server calls this method to send a notification to a client's user when an event starts
     *
     * @param e the triggering event
     * @throws RemoteException
     */

    void call(Event e) throws RemoteException;

}
