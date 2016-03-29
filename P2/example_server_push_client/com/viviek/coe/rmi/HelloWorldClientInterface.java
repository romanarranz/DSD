package com.vivek.core.rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface HelloWorldClientInterface extends Remote {
	public void notifyMessage(String sender, String message) throws RemoteException;
}