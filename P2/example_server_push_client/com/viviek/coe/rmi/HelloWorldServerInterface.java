package com.vivek.core.rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface HelloWorldServerInterface extends Remote {
	public void register(String userName, HelloWorldClientInterface clientObject) throws RemoteException;
	public String[] getAllUser() throws RemoteException;
	public void sendMessage(String sender, String userName, String message) throws RemoteException;
}