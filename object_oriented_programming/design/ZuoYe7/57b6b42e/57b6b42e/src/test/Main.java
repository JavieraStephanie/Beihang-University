package test;

import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Scanner;
class mapInfo{
	int[][] map=new int[80][80];
	public void readmap(String path){//读入地图信息
		//Requires:String类型的地图路径,System.in
		//Modifies:System.out,map[][]
		//Effects:从文件中读入地图信息，储存在map[][]中
		Scanner scan=null;
		File file=new File(path);
		if(file.exists()==false){
			System.out.println("地图文件不存在,程序退出");
			System.exit(1);
			return;
		}
		try {
			scan = new Scanner(new File(path));
		} catch (FileNotFoundException e) {
			
		}
		for(int i=0;i<80;i++){
			String[] strArray = null;
			try{
				strArray=scan.nextLine().split("");
			}catch(Exception e){
				System.out.println("地图文件信息有误，程序退出");
				System.exit(1);
			}
			for(int j=0;j<80;j++){
				try{
					this.map[i][j]=Integer.parseInt(strArray[j]);
				}catch(Exception e){
					System.out.println("地图文件信息有误，程序退出");
					System.exit(1);
				}
			}
		}
		scan.close();
	}
}
public class Main {
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		InputHandler input = new InputHandler();
		TaxiGUI gui=new TaxiGUI();
		mapInfo mi=new mapInfo();
		int[] sourcesi = new int[1000];
	    int[] sourcesj = new int[1000];
	    int[] destinationsi = new int[1000];
	    int[] destinationsj = new int[1000];
	    Timestamp[] time = new Timestamp[1000];
	    int i=0;
	    
	    while(i<2)
	    {
	    	input.InputValidation(i);
	    	i++;
	    }
		
		sourcesi=input.getSourcei();
		sourcesj=input.getSourcej();
		destinationsi=input.getDestinationi();
		destinationsj=input.getDestinationj();
		time=input.getTime();
		
		mi.readmap("map.txt");//在这里设置地图文件路径
		gui.LoadMap(mi.map, 80);
		
		gui.RequestTaxi(new Point(sourcesi[i], sourcesj[i]), new Point(destinationsi[i], destinationsj[i]));
		/*
		gui.SetTaxiStatus(1, new Point(1,1), 1);
		gv.stay(1000);//暂停1s
		gui.SetTaxiStatus(1, new Point(1,2), 1);
		gv.stay(1000);
		gui.SetTaxiStatus(1, new Point(1,3), 1);
		gv.stay(1000);
		gui.SetTaxiStatus(1, new Point(2,3), 1);
		gv.stay(1000);
		gui.SetTaxiStatus(1, new Point(2,4), 1);
		gv.stay(1000);
		gui.SetTaxiStatus(1, new Point(3,4), 1);
		gv.stay(1000);
		gui.SetTaxiStatus(1, new Point(3,5), 1);*/
		
	}

}
