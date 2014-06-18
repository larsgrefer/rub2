import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * TCP Echo-Server Single Threaded:
 * RB, Prof. Dr. Rolf Swik
 */

public class EchoServer {
	protected int portNo = 3333;
	protected ServerSocket clientConnect;

	public EchoServer(int port) throws IllegalArgumentException {
		if (port <= 0)
			throw new IllegalArgumentException(
					"Falsche Port Nr. in EchoServer Constructor.");
		System.out.println("Server socket auf Port " + port);
		try {
			clientConnect = new ServerSocket(port);
		} catch (IOException e) {
			System.err.println("Fehler bei Socket auf Port " + port);
			System.exit(1);
		}
		this.portNo = port;
	}

	public static void main(String argv[]) {
		int port = 3333;
		if (argv.length > 0) {
			try {
				port = Integer.parseInt(argv[0]);
			} catch (NumberFormatException e) {
			}
		}
		EchoServer server = new EchoServer(port);
		System.out.println("EchoServer laeuft auf Port " + port + "...");
		server.listen();
	}

	public void listen() {
		// Listen to port for client connection requests.
		try {
			while (true) {
				System.out.println("Warte auf Klienten...");
				Socket clientReq = clientConnect.accept();
				System.out.println("Verbindung mit Klient " + clientReq);
				serviceClient(clientReq);
			}
		} catch (IOException e) {
			System.err.println("IO exception bei  listen/accept.");
			System.exit(1);
		}
	}

	public void serviceClient(Socket clientConn) {
		try {
			BufferedReader inStream =
					new BufferedReader(new InputStreamReader(clientConn.getInputStream()));
			PrintWriter pout = new PrintWriter(clientConn.getOutputStream(), true);
			String cmd = inStream.readLine();
			System.out.println("Daten vom Klient: " + cmd);
			pout.println(cmd);
			clientConn.close();
			System.out.println("Verbindung geschlossen...");
		} catch (IOException e) {
			System.err.println("EchoServer: " + e);
		}
	}

	public synchronized void finalize() {
		System.out.println("Schliesse EchoServer auf Port " + portNo);
		try {
			clientConnect.close();
		} catch (IOException e) {
			System.err.println("EchoServer: " + e);
			System.exit(1);
		}
	}
}
