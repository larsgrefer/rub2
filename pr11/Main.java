public class Main {
	
	static WordCountValues wcValues = new WordCountValues();
	
	public static void main(String[] args) {
	
		WordCount[] threads = new WordCount[args.length];
		
		for(int i = 0; i < args.length; i++){
			WordCount t = new WordCount(args[i], wcValues);
			t.start();
			
			threads[i] = t;
		}
		
		
		for(WordCount t : threads){
			try {
				t.join();
			} catch (InterruptedException e) {
				System.err.println(e.getMessage());
			}
		}
		
		printWC(wcValues.lines, wcValues.words, wcValues.chars, "Insgesamt");
	}

	static void addWC(WordCount wc){
		
		synchronized(wcValues){
			wcValues.lines += wc.getLines();
			wcValues.words += wc.getWords();
			wcValues.chars += wc.getChars();
		}
		
		printWC(wc.getLines(), wc.getWords(), wc.getChars(), wc.getFilename());
	}
	
	static void printWC(long l, long w, long c, String f) {
		
		synchronized(wcValues){
			System.out.printf("%d %d %d %s%n", l, w, c, f);
		}
	}
}
