import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class WordCount extends Thread implements Runnable{

	private long lines, words, chars;

	private String file;

	private WordCountValues wcValues;
	
	public WordCount(String file) {
		this(file, null);
	}

	public WordCount(String file, WordCountValues wcValues) {
		this.file = file;
		this.wcValues = wcValues;
	}

	@Override
	public void run() {
		try {
			Process p = Runtime.getRuntime().exec(new String[]{ "wc", file});
			BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
			
			String answer = br.readLine();
			
			StringTokenizer tokenizer = new StringTokenizer(answer);

			lines = Long.valueOf(tokenizer.nextToken()).longValue();
			words = Long.valueOf(tokenizer.nextToken()).longValue();
			chars = Long.valueOf(tokenizer.nextToken()).longValue();

			if(wcValues != null){
				Main.addWC(this);
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	
	public long getLines() {
		return lines;
	}

	public long getWords() {
		return words;
	}

	public long getChars() {
		return chars;
	}

	public String getFilename(){
		return file;
	}
	
}
