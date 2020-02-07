package jProfiler;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class ThreadDemo {
	    private static final String DEATH_TAG = "exit";
		private static BlockingQueue<String> taskList = new LinkedBlockingQueue<String>();

		public static void main(String[] args)throws Exception {
			ExecutorService es = Executors.newCachedThreadPool();

			// ����һ�����߳�,ʹ���������н����ַ���, ���������DEATH_TAG, ��һֱ���д���
			es.submit(new Runnable() {

				@Override
				public void run() {
					while (true) {
						String s = null;
						try {
							s = taskList.take();
							if (DEATH_TAG.equals(s)) {
								System.out.println("bye");
								break;
							}
							System.out.println(s);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}
				}
			});
//			taskList.put(DEATH_TAG);
			es.shutdown();
		}
	}


