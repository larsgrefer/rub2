/** Testprogramm zum sequentiellen Quicksort
*  mit Frames und Eventsteuerung
*  Prof. Dr. Rolf Swik
*/
import java.io.*;
import java.util.*;
import java.lang.*;
import java.awt.*;
import java.awt.event.*;

public class QuickSortTestFrame extends Frame
	implements WindowListener, ActionListener {
	static TextArea textarea ;
	TextField zeile ;
	Panel panel1; Button auswahl ,start;
	int[] a ; File file;
	public QuickSortTestFrame() throws IOException {
		super("Singlethreaded Quicksort");
		panel1 = new Panel();
 		textarea = new TextArea( 32, 80);
 		zeile = new TextField();
 		auswahl = new Button("Auswahl"); start = new Button("Start"); 
		this.addWindowListener(this); zeile.addActionListener(this);
		auswahl.addActionListener(this); start.addActionListener(this);
		textarea.setFont(new Font("Helvetica", Font.PLAIN, 12));
		textarea.setEditable(false); zeile.setEditable(true);
		panel1.add( auswahl); panel1.add( start); this.add("North", panel1); 
		this.add("Center", textarea); this.add("South", zeile);
		this.pack(); this.setVisible(true);
   		}
    // Die Methoden von WindowListener
      	public void windowClosing(WindowEvent e) {
	      this.setVisible(false); this.dispose(); System.exit(0);
     		}
  	public void windowOpened(WindowEvent e) {}
	public void windowClosed(WindowEvent e) {}
	public void windowIconified(WindowEvent e) {}
	public void windowDeiconified(WindowEvent e) {}
	public void windowActivated(WindowEvent e) {}  
	public void windowDeactivated(WindowEvent e) {}
    // Die  Methoden von ActionListener
	public void actionPerformed(ActionEvent e)  {
	     StringTokenizer st ;
 	     try {
		if ( (e.getSource()).equals(start) ) {
  			
			QuickSort quicksort = new QuickSort();
 			quicksort.sort(a,0,a.length-1);
  				
  			StringBuffer strB = new StringBuffer();
			strB.append("\n Sortiert mit QuickSort:\n");
  			for(int i=0;i<a.length;i++) strB.append(" "+a[i]);
  			strB.append("\n Fertig!\n");
			textarea.append( strB.toString() );
  				}
		else  { if ( (e.getSource()).equals(auswahl) ) {
			FileDialog dateiselekt = new FileDialog (this, "Dateiauswahl",FileDialog.LOAD);
			dateiselekt.setVisible(true);
			String dirname = dateiselekt.getDirectory();
			String filename = dateiselekt.getFile();
			file = new File(dirname+filename);
			dateiselekt.dispose(); 
			FileInputStream in = new FileInputStream(file);
			BufferedReader input = new BufferedReader(new FileReader( file ));
			textarea.append("Einlesen der Folge \n");
			String str = input.readLine();
			StringBuffer strB = new StringBuffer();
			while (str != null) {
				strB.append(str); textarea.append(str+"\n");
				str = input.readLine();
      					}
			st = new StringTokenizer( strB.toString() );

				}
			else  {
				String str = zeile.getText();
				st = new StringTokenizer( str); 
				}    	
    		 	a= new int[st.countTokens()];
			for (int i=0; i<a.length; i++) a[i]= java.lang.Integer.parseInt(st.nextToken());
			textarea.append("Unsortiertes Feld ok, warte auf Start ! \n");
			}
		}
		catch (Exception ex) { 
			zeile.setText(ex.toString());
				}
		}

    public static void main(String[] args) throws Exception {
       try {Frame qst = new QuickSortTestFrame();}
        catch (IOException iex) {System.err.println(iex);}
    }
}
  


