package com.vivek.core.rmi.server;

import java.util.HashMap;

import com.vivek.core.rmi.HelloWorldClientInterface;

public class UserStore {

	private HashMap userStore = new HashMap();

	public HelloWorldClientInterface getClientByName(String name) {
		return this.userStore.get(name);
	}

	public String[] getAllUsers() {
		return this.userStore.keySet().toArray(new String[0]);
	}

	public void addUser(String user, HelloWorldClientInterface client) {
		this.userStore.put(user, client);
	}
}