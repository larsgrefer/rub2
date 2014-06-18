/** Portscanner sequentiell
 *  Prof. Dr. Rolf Swik
 */

import java.io.IOException;
import java.net.Socket;

public class PortScan {

	public static void main(String[] args) {
		String host = args[0];
		int pa = java.lang.Integer.parseInt(args[1]);
		int pe = java.lang.Integer.parseInt(args[2]);
		for (int port = pa; port <= pe; port++) {
			try {
				Socket s = new Socket(host, port);
				System.out.println(host + " hoert auf Port " + port);
				s.close();
			} catch (IOException e) {
			}
		}
	}
}