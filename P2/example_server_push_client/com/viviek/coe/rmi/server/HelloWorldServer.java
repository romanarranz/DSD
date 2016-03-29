package com.vivek.core.rmi.server;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Arrays;

import com.vivek.core.rmi.HelloWorldClientInterface;
import com.vivek.core.rmi.HelloWorldServerInterface;

public class HelloWorldServer implements HelloWorldServerInterface {

	private UserStore userStore = new UserStore();

	public UserStore getUserStore() {
		return userStore;
	}

	public void register(String userName, HelloWorldClientInterface clientObject) {

		this.getUserStore().addUser(userName, clientObject);

		try {
			clientObject.notifyMessage(“Server”, “Welcome ” + userName);
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}

	public String[] getAllUser() throws RemoteException {
		return this.getUserStore().getAllUsers();
	}

	public void sendMessage(String sender, String userName, String message) throws RemoteException {
		HelloWorldClientInterface client = this.getUserStore().getClientByName(userName);
		if (client != null) {
			client.notifyMessage(sender, message);
		}
	}

	public static void main(String[] args) {

		HelloWorldServer server = new HelloWorldServer();

		try {
			HelloWorldServerInterface stub = (HelloWorldServerInterface) UnicastRemoteObject.exportObject(server, 0);
			LocateRegistry.getRegistry().bind(“EchoService”, stub);

			System.out.println(“Server binded object successfully”);

			while (server.userStore.getAllUsers().length == 0) {
				System.out.println(“No Client Registered”);
				Thread.sleep(5000);
			}

			while (true) {
				System.out.println("Users registered : "+ Arrays.toString(server.userStore.getAllUsers()));
				Thread.sleep(15000);
			}
		} catch (RemoteException e) {
			e.printStackTrace();
		} catch (AlreadyBoundException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}