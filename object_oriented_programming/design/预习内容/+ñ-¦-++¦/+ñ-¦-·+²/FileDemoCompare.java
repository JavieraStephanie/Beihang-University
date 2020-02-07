package jProfiler;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileDemoCompare {
		static int count=1000;
		public static void main( String[] args ) throws IOException {
		BufferedWriter fw=new BufferedWriter(new FileWriter("d:\\testfile.txt"));
		for(int i=0;i<count*10;i++)    //count=10000,
			fw.write(String.valueOf(i)+"\r\n");//д������
		fw.close();
		BufferedReader fr=new BufferedReader(new FileReader("d:\\testfile.txt"));
		while(fr.read()!=-1);
		fr.close();
		}
	}

