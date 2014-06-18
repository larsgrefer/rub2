import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * TCP Echo-Client:
 * RB, Prof. Dr. Rolf Swik
 */

public class EchoClient {
	protected Socket serverConn;

	public EchoClient(String host, int port)
			throws IllegalArgumentException {
		try {
			System.out.println("Versuche Verbindung zu " + host + " " + port);
			serverConn = new Socket(host, port);
		} catch (UnknownHostException e) {
			throw new IllegalArgumentException("Host-Name !");
		} catch (IOException e) {
			System.err.println("EchoClient: " + e);
			System.exit(1);
		}
		System.out.println("Socket eingerichtet: " + serverConn);
	}

	public static void main(String argv[]) {
		if (argv.length < 1) {
			System.out.println("Usage: java EchoClient host [port]");
			System.exit(1);
		}
		String host = argv[0];
		int port = 3333;
		try {
			port = Integer.parseInt(argv[1]);
		} catch (NumberFormatException e) {
		}
		EchoClient client = new EchoClient(host, port);
		client.sendCommands();
	}

	public void sendCommands() {
		try {
			String result, cmd;
			PrintWriter pout = new PrintWriter(serverConn.getOutputStream(), true);
			BufferedReader din = new BufferedReader(new InputStreamReader(serverConn.getInputStream()));
			BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("Verbindung zum Server erfolgt, bitte Eingabezeile: ");
			cmd = input.readLine();
			pout.println(cmd);
			while ((result = din.readLine()) != null) {
				System.out.println("Antwort vom Server: " + result);
			}
			serverConn.close();
			System.out.println("Verbindung geschlossen...");
		} catch (IOException e) {
			System.err.println("EchoClient: " + e);
		}
	}

	public synchronized void finalize() {
		System.out.println("Schliesse EchoClient...");
		try {
			serverConn.close();
		} catch (IOException e) {
			System.err.println("EchoClient: " + e);
			System.exit(1);
		}
	}
}
