/** rekursives Sortieren mit Quicksort Singlethreaded
*  Prof. Dr. Rolf Swik
*/
public class QuickSort extends Object {
	
  public QuickSort() {
	super();

	QuickSortTestFrame.textarea.append("\n -> "+ this ); 
			}

  public  void sort (int[] a, int unten, int oben) {
    int tmp ;
    int i = unten;
    int j = oben;
    int x = a[(unten+oben) / 2];                  // Pivotelement, willkuerlich
    StringBuffer strB = new StringBuffer();
	
    do {
        while (a[i] < x) i++;                     // x fungiert als Bremse
        while (a[j] > x) j--;                     // x fungiert als Bremse
        if ( i<=j )  {
            tmp  = a[i];                          // Hilfsspeicher
            a[i] = a[j];                          // a[i] und
            a[j] = tmp;                           // a[j] werden getauscht
            i++;
            j--;
        }
    } while (i <= j);
                              // alle Elemente der linken Haelfte sind kleiner
                              // als alle Elemente der rechten Haelfte
         
	 strB.append("\n Teilsortierung ->: "+ this + ":  Pivot= "+x+" \n");
	 QuickSortTestFrame.textarea.append("");
     for (int tag=unten;tag<=oben;tag++)  strB.append(" "+a[tag]);
     QuickSortTestFrame.textarea.append(strB.toString() );

    if (unten < j)  sort(a, unten, j);            // sortiere linke Haelfte
    if (i < oben )  sort(a, i, oben );            // sortiere rechte Haelfte
  }

}
