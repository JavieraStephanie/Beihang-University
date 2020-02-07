package taxi;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Vector;
import java.util.concurrent.CopyOnWriteArrayList;

import javax.swing.BorderFactory;
import javax.swing.JCheckBox;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;

class gv {// å¸¸ç”¨å·¥å…·
	public static int MAXNUM = 1000000;

	public static long getTime() {// èŽ·å¾—å½“å‰�ç³»ç»Ÿæ—¶é—´
		// Requires:æ— 
		// Modifies:æ— 
		// Effects:è¿”å›žlongç±»åž‹çš„ä»¥æ¯«ç§’è®¡çš„ç³»ç»Ÿæ—¶é—´
		return System.currentTimeMillis();
	}

	@SuppressWarnings("static-access")
	public static void stay(long time) {
		// Requires:longç±»åž‹çš„ä»¥æ¯«ç§’è®¡çš„ä¼‘çœ æ—¶é—´
		// Modifies:æ— 
		// Effects:ä½¿å½“å‰�çº¿ç¨‹ä¼‘çœ timeçš„æ—¶é—´
		try {
			Thread.currentThread().sleep(time);
		} catch (InterruptedException e) {

		}
	}

	public static void printTime() {
		// Requires:æ— 
		// Modifies:System.out
		// Effects:åœ¨å±�å¹•ä¸Šæ‰“å�°HH:mm:ss:SSSæ ¼å¼�çš„å½“å‰�æ—¶é—´
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss:SSS");
		System.out.println(sdf.format(new Date(getTime())));
	}

	public static String getFormatTime() {
		// Requires:æ— 
		// Modifies:æ— 
		// Effects:è¿”å›žStringç±»åž‹çš„HH:mm:ssæ ¼å¼�çš„æ—¶é—´
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		return sdf.format(new Date(getTime()));
	}
}

class node {// ç»“ç‚¹ä¿¡æ�¯
	int NO;
	int depth;

	public node(int _NO, int _depth) {
		// Requires:intç±»åž‹çš„ç»“ç‚¹å�·,intç±»åž‹çš„æ·±åº¦ä¿¡æ�¯
		// Modifies:åˆ›å»ºä¸€ä¸ªæ–°çš„nodeå¯¹è±¡ï¼Œä¿®æ”¹äº†æ­¤å¯¹è±¡çš„NO,depthå±žæ€§
		// Effects:åˆ›å»ºäº†ä¸€ä¸ªæ–°çš„nodeå¯¹è±¡å¹¶åˆ�å§‹åŒ–
		NO = _NO;
		depth = _depth;
	}
}

class guiInfo {
	public int[][] map;
	int[][] graph = new int[6405][6405];// é‚»æŽ¥çŸ©é˜µ
	int[][] D = new int[6405][6405];// ä¿�å­˜ä»Žiåˆ°jçš„æœ€å°�è·¯å¾„å€¼

	public void initmatrix() {// åˆ�å§‹åŒ–é‚»æŽ¥çŸ©é˜µ
		// Requires:æ— 
		// Modifies:graph[][]
		// Effects:å¯¹é‚»æŽ¥çŸ©é˜µèµ‹åˆ�å€¼
		int MAXNUM = gv.MAXNUM;
		for (int i = 0; i < 6400; i++) {
			for (int j = 0; j < 6400; j++) {
				if (i == j)
					graph[i][j] = 0;
				else
					graph[i][j] = MAXNUM;
			}
		}
		for (int i = 0; i < 80; i++) {
			for (int j = 0; j < 80; j++) {
				if (map[i][j] == 1 || map[i][j] == 3) {
					graph[i * 80 + j][i * 80 + j + 1] = 1;
					graph[i * 80 + j + 1][i * 80 + j] = 1;
				}
				if (map[i][j] == 2 || map[i][j] == 3) {
					graph[i * 80 + j][(i + 1) * 80 + j] = 1;
					graph[(i + 1) * 80 + j][i * 80 + j] = 1;
				}
			}
		}
	}

	public void pointbfs(int root) {// å�•ç‚¹å¹¿åº¦ä¼˜å…ˆæ�œç´¢
		// Requires:intç±»åž‹çš„ç‚¹å�·root
		// Modifies:D[][],System.out
		// Effects:å¯¹æ•´ä¸ªåœ°å›¾è¿›è¡Œå¹¿åº¦ä¼˜å…ˆæ�œç´¢ï¼ŒèŽ·å¾—ä»»æ„�ç‚¹åˆ°rootä¹‹é—´çš„æœ€çŸ­è·¯ä¿¡æ�¯ï¼Œå‚¨å­˜åœ¨D[][]ä¸­
		int[] offset = new int[] { 0, 1, -1, 80, -80 };
		Vector<node> queue = new Vector<node>();
		boolean[] view = new boolean[6405];
		for (int i = 0; i < 6400; i++) {
			for (int j = 0; j < 6400; j++) {
				if (i == j) {
					D[i][j] = 0;
				} else {
					D[i][j] = graph[i][j];// èµ‹åˆ�å€¼
				}
			}
		}
		int x = root;// å¼€å§‹è¿›è¡Œå�•ç‚¹bfs
		for (int i = 0; i < 6400; i++)
			view[i] = false;
		queue.add(new node(x, 0));
		while (queue.size() > 0) {
			node n = queue.get(0);
			view[n.NO] = true;
			for (int i = 1; i <= 4; i++) {
				int next = n.NO + offset[i];
				if (next >= 0 && next < 6400 && view[next] == false && graph[n.NO][next] == 1) {
					view[next] = true;
					queue.add(new node(next, n.depth + 1));// åŠ å…¥é��åŽ†é˜Ÿåˆ—
					D[x][next] = n.depth + 1;
					D[next][x] = n.depth + 1;
				}
			}
			queue.remove(0);// é€€å‡ºé˜Ÿåˆ—
		}
		// æ£€æµ‹å­¤ç«‹ç‚¹
		int count = 0;
		for (int i = 0; i < 6400; i++) {
			if (D[i][x] == gv.MAXNUM) {
				count++;
			}
		}
		if (count > 0) {
			System.out.println("åœ°å›¾å¹¶ä¸�æ˜¯è¿žé€šçš„,ç¨‹åº�é€€å‡º");
			System.exit(1);
		}
	}

	public int distance(int x1, int y1, int x2, int y2) {// ä½¿ç”¨bfsè®¡ç®—ä¸¤ç‚¹ä¹‹é—´çš„è·�ç¦»
		pointbfs(x1 * 80 + y1);
		return D[x1 * 80 + y1][x2 * 80 + y2];
	}
}

class guitaxi {
	public int x = 1;
	public int y = 1;
	public int status = -1;
	public int type = 0;// 0æ˜¯æ™®é€šå‡ºç§Ÿè½¦ï¼Œ1æ˜¯ç‰¹æ®Šè½¦
}

class guigv {
	public static guiInfo m = new guiInfo();// åœ°å›¾å¤‡ä»½
	public static CopyOnWriteArrayList<guitaxi> taxilist = new CopyOnWriteArrayList<guitaxi>();// å‡ºç§Ÿè½¦åˆ—è¡¨
	public static CopyOnWriteArrayList<Point> srclist = new CopyOnWriteArrayList<Point>();// å‡ºå�‘ç‚¹åˆ—è¡¨
	public static HashMap<String, Integer> flowmap = new HashMap<String, Integer>();// å½“å‰�æµ�é‡�
	public static HashMap<String, Integer> memflowmap = new HashMap<String, Integer>();// ä¹‹å‰�ç»Ÿè®¡çš„æµ�é‡�
	/* GUI */
	public static JPanel drawboard;
	public static int[][] colormap;
	public static int[][] lightmap;
	public static boolean redraw = false;
	public static int xoffset = 0;
	public static int yoffset = 0;
	public static int oldxoffset = 0;
	public static int oldyoffset = 0;
	public static int mousex = 0;
	public static int mousey = 0;
	public static double percent = 1.0;
	public static boolean drawstr = false;
	public static boolean drawflow = false;// æ˜¯å�¦ç»˜åˆ¶æµ�é‡�ä¿¡æ�¯

	private static String Key(int x1, int y1, int x2, int y2) {// ç”Ÿæˆ�å”¯ä¸€çš„Key
		return "" + x1 + "," + y1 + "," + x2 + "," + y2;
	}

	public static void AddFlow(int x1, int y1, int x2, int y2) {// å¢žåŠ ä¸€ä¸ªé�“è·¯æµ�é‡�
		synchronized (guigv.flowmap) {
			// æŸ¥è¯¢ä¹‹å‰�çš„æµ�é‡�æ•°é‡�
			int count = 0;
			count = guigv.flowmap.get(Key(x1, y1, x2, y2)) == null ? 0 : guigv.flowmap.get(Key(x1, y1, x2, y2));
			// æ·»åŠ æµ�é‡�
			guigv.flowmap.put(Key(x1, y1, x2, y2), count + 1);
			guigv.flowmap.put(Key(x2, y2, x1, y1), count + 1);
		}
	}

	public static int GetFlow(int x1, int y1, int x2, int y2) {// æŸ¥è¯¢æµ�é‡�ä¿¡æ�¯
		synchronized (guigv.memflowmap) {
			return guigv.memflowmap.get(Key(x1, y1, x2, y2)) == null ? 0 : guigv.memflowmap.get(Key(x1, y1, x2, y2));
		}
	}

	@SuppressWarnings("unchecked")
	public static void ClearFlow() {// æ¸…ç©ºæµ�é‡�ä¿¡æ�¯
		synchronized (guigv.flowmap) {
			synchronized (guigv.memflowmap) {
				guigv.memflowmap = (HashMap<String, Integer>) guigv.flowmap.clone();
				guigv.flowmap = new HashMap<String, Integer>();

			}
		}
	}
}

class DrawBoard extends JPanel {// ç»˜å›¾æ�¿ç±»
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2D = (Graphics2D) g;
		brush.draw(g2D);
	}
}

class myform extends JFrame {// æˆ‘çš„çª—ä½“ç¨‹åº�
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int left = 100;
	private int top = 100;
	private int width = 630;
	private int height = 600;

	public myform() {
		super();
		/* è®¾ç½®æŒ‰é’®å±žæ€§ */
		// button1
		JButton button1 = new JButton();// åˆ›å»ºä¸€ä¸ªæŒ‰é’®
		button1.setBounds(10, 515, 100, 40);// è®¾ç½®æŒ‰é’®çš„ä½�ç½®
		button1.setText("é‡�ç½®");// è®¾ç½®æŒ‰é’®çš„æ ‡é¢˜
		button1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				guigv.xoffset = 0;
				guigv.yoffset = 0;
				guigv.oldxoffset = 0;
				guigv.oldyoffset = 0;
				guigv.percent = 1.0;
				guigv.drawboard.repaint();
			}
		});
		// button2
		JButton button2 = new JButton();// åˆ›å»ºä¸€ä¸ªæŒ‰é’®
		button2.setBounds(120, 515, 100, 40);// è®¾ç½®æŒ‰é’®çš„ä½�ç½®
		button2.setText("æ”¾å¤§");// è®¾ç½®æŒ‰é’®çš„æ ‡é¢˜
		button2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				guigv.percent += 0.1;
				guigv.drawboard.repaint();
			}
		});
		// button3
		JButton button3 = new JButton();// åˆ›å»ºä¸€ä¸ªæŒ‰é’®
		button3.setBounds(230, 515, 100, 40);// è®¾ç½®æŒ‰é’®çš„ä½�ç½®
		button3.setText("ç¼©å°�");// è®¾ç½®æŒ‰é’®çš„æ ‡é¢˜
		button3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (guigv.percent > 0.1)
					guigv.percent -= 0.1;
				guigv.drawboard.repaint();
			}
		});
		// button4
		JButton button4 = new JButton();
		button4.setBounds(340, 515, 100, 40);
		button4.setText("æ¸…é™¤è½¨è¿¹");
		button4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// æ¸…é™¤colormap
				for (int i = 0; i < 85; i++) {
					for (int j = 0; j < 85; j++) {
						guigv.colormap[i][j] = 0;
					}
				}
				guigv.drawboard.repaint();
			}
		});
		/* è®¾ç½®å¤�é€‰æ¡†å±žæ€§ */
		JCheckBox check1 = new JCheckBox("æ˜¾ç¤ºä½�ç½®");
		check1.setBounds(450, 515, 80, 40);
		check1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				guigv.drawstr = check1.isSelected();
				guigv.drawboard.repaint();
			}
		});
		JCheckBox check2 = new JCheckBox("æ˜¾ç¤ºæµ�é‡�");
		check2.setBounds(530, 515, 80, 40);
		check2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				guigv.drawflow = check2.isSelected();
				guigv.drawboard.repaint();
			}
		});
		/* è®¾ç½®ç»˜å›¾åŒºå±žæ€§ */
		DrawBoard drawboard = new DrawBoard();// åˆ›å»ºæ–°çš„ç»˜å›¾æ�¿
		drawboard.setBounds(10, 10, 500, 500);// è®¾ç½®å¤§å°�
		drawboard.setBorder(BorderFactory.createLineBorder(Color.black, 1));// è®¾ç½®è¾¹æ¡†
		drawboard.setOpaque(true);
		drawboard.addMouseListener(new MouseListener() {
			public void mousePressed(MouseEvent e) {// æŒ‰ä¸‹é¼ æ ‡
				guigv.redraw = true;
				guigv.mousex = e.getX();
				guigv.mousey = e.getY();
			}

			public void mouseReleased(MouseEvent e) {// æ�¾å¼€é¼ æ ‡
				guigv.oldxoffset = guigv.xoffset;
				guigv.oldyoffset = guigv.yoffset;
				guigv.redraw = false;
			}

			@Override
			public void mouseClicked(MouseEvent e) {
			}

			@Override
			public void mouseEntered(MouseEvent e) {
			}

			@Override
			public void mouseExited(MouseEvent e) {
			}
		});
		drawboard.addMouseMotionListener(new MouseMotionAdapter() {// æ·»åŠ é¼ æ ‡æ‹–åŠ¨
			public void mouseDragged(MouseEvent e) {
				if (guigv.redraw == true) {
					guigv.xoffset = guigv.oldxoffset + e.getX() - guigv.mousex;
					guigv.yoffset = guigv.oldyoffset + e.getY() - guigv.mousey;
					guigv.drawboard.repaint();
				}
			}
		});
		drawboard.addMouseWheelListener(new MouseWheelListener() {// æ·»åŠ é¼ æ ‡æ»šè½®
			public void mouseWheelMoved(MouseWheelEvent e) {
				if (e.getWheelRotation() == 1) {// æ»‘è½®å�‘å‰�
					if (guigv.percent > 0.1)
						guigv.percent -= 0.1;
					guigv.drawboard.repaint();
				} else if (e.getWheelRotation() == -1) {// æ»‘è½®å�‘å�Ž
					guigv.percent += 0.1;
					guigv.drawboard.repaint();
				}
			}
		});
		guigv.drawboard = drawboard;// èŽ·å¾—ä¸€ä»½drawboardçš„å¼•ç”¨

		/* è®¾ç½®çª—ä½“å±žæ€§ */
		setTitle("å®žæ—¶æŸ¥çœ‹");// è®¾ç½®çª—ä½“æ ‡é¢˜
		setLayout(null);// ä½¿ç”¨ç»�å¯¹å¸ƒå±€
		setBounds(left, top, width, height);// è®¾ç½®çª—ä½“ä½�ç½®å¤§å°�

		/* æ·»åŠ æŽ§ä»¶ï¼Œæ˜¾ç¤ºçª—ä½“ */
		Container c = getContentPane();// èŽ·å¾—ä¸€ä¸ªå®¹å™¨
		c.add(button1);// æ·»åŠ button1
		c.add(button2);
		c.add(button3);
		c.add(button4);
		c.add(check1);
		c.add(check2);
		c.add(drawboard);
		setVisible(true);// ä½¿çª—ä½“å�¯è§�
		setAlwaysOnTop(true);// è®¾ç½®çª—ä½“ç½®é¡¶
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);// è®¾ç½®é»˜è®¤å…³é—­æ–¹å¼�
	}
}

class brush {// ç”»ç¬”
	public static int[][] colormap = new int[85][85];

	public static void draw(Graphics2D g) {
		boolean drawcolor = true;
		int factor = (int) (35 * guigv.percent);
		int width = (int) (20 * guigv.percent);
		int xoffset = -5;
		int yoffset = 3;
		// æ£€ç´¢ä¸€é��å‡ºç§Ÿè½¦ä½�ç½®ä¿¡æ�¯ï¼Œå°†æœ‰å‡ºç§Ÿè½¦çš„ä½�ç½®æ ‡ä¸Š1
		int[][] taximap = new int[85][85];
		// èŽ·å¾—colormapçš„å¼•ç”¨
		guigv.colormap = colormap;
		// è®¾ç½®å‡ºç§Ÿè½¦ä½�ç½®
		for (int i = 0; i < 80; i++)
			for (int j = 0; j < 80; j++) {
				taximap[i][j] = -1;
			}
		for (int i = 0; i < guigv.taxilist.size(); i++) {
			guitaxi gt = guigv.taxilist.get(i);
			if (gt.status > -1) {
				// System.out.println("####"+gt.x+" "+gt.y);
				// åŠ å…¥å¯¹typeçš„åˆ¤æ–­,å¦‚æžœtype=1ï¼Œåˆ™taximap=4
				if (gt.type == 1) {
					taximap[gt.x][gt.y] = 4;
				} else {
					taximap[gt.x][gt.y] = gt.status;
				}
				if (gt.status == 1) {
					colormap[gt.x][gt.y] = 1;// è·¯çº¿æŸ“è‰²
				}
			}
		}
		// synchronized (guigv.m.taxilist) {
		// for (taxiInfo i : guigv.m.taxilist) {
		// taximap[i.nowPoint.x][i.nowPoint.y] = 1;
		// if (i.state == STATE.WILL || i.state == STATE.RUNNING) {
		// taximap[i.nowPoint.x][i.nowPoint.y] = 2;
		// colormap[i.nowPoint.x][i.nowPoint.y] = 1;// è·¯çº¿æŸ“è‰²
		// }
		// }
		// }
		// ...

		for (int i = 0; i < 80; i++) {
			for (int j = 0; j < 80; j++) {
				if (j < 10) {
					xoffset = -5;
					yoffset = 3;
				} else {
					xoffset = -7;
					yoffset = 3;
				}
				g.setStroke(new BasicStroke(2));
				g.setFont(new Font("Arial", Font.PLAIN, (int) (10 * guigv.percent)));
				if (guigv.m.map[i][j] == 2 || guigv.m.map[i][j] == 3) {
					if (drawcolor && colormap[i][j] == 1 && colormap[i + 1][j] == 1)
						g.setColor(Color.RED);
					else
						g.setColor(Color.BLACK);
					int memj = (int) ((j * factor + guigv.xoffset) * guigv.percent);
					g.drawLine(memj, (int) ((i * factor + guigv.yoffset) * guigv.percent), memj,
							(int) (((i + 1) * factor + guigv.yoffset) * guigv.percent));
					// ç»˜åˆ¶é�“è·¯æµ�é‡�
					if (guigv.drawflow) {
						g.setColor(Color.BLUE);
						g.drawString("" + guigv.GetFlow(i, j, i + 1, j), memj,
								(int) (((i + 0.5) * factor + guigv.yoffset) * guigv.percent));
					}
				}
				if (guigv.m.map[i][j] == 1 || guigv.m.map[i][j] == 3) {
					if (drawcolor && colormap[i][j] == 1 && colormap[i][j + 1] == 1)
						g.setColor(Color.RED);
					else
						g.setColor(Color.BLACK);
					int memi = (int) ((i * factor + guigv.yoffset) * guigv.percent);
					g.drawLine((int) ((j * factor + guigv.xoffset) * guigv.percent), memi,
							(int) (((j + 1) * factor + guigv.xoffset) * guigv.percent), memi);
					// ç»˜åˆ¶é�“è·¯æµ�é‡�
					if (guigv.drawflow) {
						g.setColor(Color.BLUE);
						g.drawString("" + guigv.GetFlow(i, j, i, j + 1),
								(int) (((j + 0.5) * factor + guigv.xoffset) * guigv.percent), memi);
					}
				}
				int targetWidth;
				// åŠ å…¥å¯¹typeçš„åˆ¤æ–­
				if (taximap[i][j] == 4) {
					g.setColor(Color.MAGENTA);
					targetWidth = 2;
				} else if (taximap[i][j] == 3) {
					g.setColor(Color.GREEN);
					targetWidth = 2;
				} else if (taximap[i][j] == 2) {
					g.setColor(Color.RED);
					targetWidth = 2;
				} else if (taximap[i][j] == 1) {
					g.setColor(Color.BLUE);
					targetWidth = 2;
				} else if (taximap[i][j] == 0) {
					g.setColor(Color.YELLOW);
					targetWidth = 2;
				} else {
					g.setColor(Color.BLACK);
					targetWidth = 1;
				}
				int cleft = (int) ((j * factor - width / 2 + guigv.xoffset) * guigv.percent);
				int ctop = (int) ((i * factor - width / 2 + guigv.yoffset) * guigv.percent);
				int cwidth = (int) (width * guigv.percent) * targetWidth;
				if (targetWidth > 1) {
					cleft = cleft - (int) (cwidth / 4);
					ctop = ctop - (int) (cwidth / 4);
				}
				// g.fillOval((int)((j*factor-width/2+guigv.xoffset)*guigv.percent),(int)((i*factor-width/2+guigv.yoffset)*guigv.percent),(int)(width*guigv.percent)*targetWidth,(int)(width*guigv.percent)*targetWidth);
				g.fillOval(cleft, ctop, cwidth, cwidth);// ç»˜åˆ¶ç‚¹
				// ç»˜åˆ¶çº¢ç»¿ç�¯
				if (guigv.lightmap[i][j] == 1) {// ä¸œè¥¿æ–¹å�‘ä¸ºç»¿ç�¯
					g.setColor(Color.GREEN);
					g.fillRect(cleft - cwidth / 4, ctop + cwidth / 4, cwidth / 2, cwidth / 8);
					g.setColor(Color.RED);
					g.fillRect(cleft + cwidth / 8, ctop - cwidth / 4, cwidth / 8, cwidth / 2);
				} else if (guigv.lightmap[i][j] == 2) {// ä¸œè¥¿æ–¹å�‘ä¸ºçº¢ç�¯
					g.setColor(Color.RED);
					g.fillRect(cleft - cwidth / 4, ctop + cwidth / 4, cwidth / 2, cwidth / 8);
					g.setColor(Color.GREEN);
					g.fillRect(cleft + cwidth / 8, ctop - cwidth / 4, cwidth / 8, cwidth / 2);
				}
				// æ ‡è®°srclistä¸­çš„ç‚¹
				for (Point p : guigv.srclist) {
					g.setColor(Color.RED);
					int x = p.x;
					int y = p.y;
					g.drawLine((int) (((y - 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x - 2) * factor + guigv.yoffset) * guigv.percent),
							(int) (((y + 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x - 2) * factor + guigv.yoffset) * guigv.percent));
					g.drawLine((int) (((y + 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x - 2) * factor + guigv.yoffset) * guigv.percent),
							(int) (((y + 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x + 2) * factor + guigv.yoffset) * guigv.percent));
					g.drawLine((int) (((y + 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x + 2) * factor + guigv.yoffset) * guigv.percent),
							(int) (((y - 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x + 2) * factor + guigv.yoffset) * guigv.percent));
					g.drawLine((int) (((y - 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x + 2) * factor + guigv.yoffset) * guigv.percent),
							(int) (((y - 2) * factor + guigv.xoffset) * guigv.percent),
							(int) (((x - 2) * factor + guigv.yoffset) * guigv.percent));
				}
				if (guigv.drawstr == true) {
					g.setColor(Color.WHITE);
					g.setFont(new Font("Arial", Font.PLAIN, (int) (8 * guigv.percent)));
					g.drawString("" + i + "," + j, (int) ((j * factor + xoffset + guigv.xoffset) * guigv.percent),
							(int) ((i * factor + yoffset + guigv.yoffset) * guigv.percent));
				}

			}
		}
	}
}

class processform extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JProgressBar progressBar = new JProgressBar();
	JLabel label1 = new JLabel("BFSè¿›åº¦", SwingConstants.CENTER);

	public processform() {
		super();
		// å°†è¿›åº¦æ�¡è®¾ç½®åœ¨çª—ä½“æœ€åŒ—é�¢
		getContentPane().add(progressBar, BorderLayout.NORTH);
		getContentPane().add(label1, BorderLayout.CENTER);
		progressBar.setMinimum(0);
		progressBar.setMaximum(100);
		progressBar.setStringPainted(true);
		// è®¾ç½®çª—ä½“å�„ç§�å±žæ€§æ–¹æ³•
		setBounds(100, 100, 100, 100);
		setAlwaysOnTop(true);// è®¾ç½®çª—ä½“ç½®é¡¶
		setVisible(true);
	}
}

class debugform extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	JTextArea text1 = new JTextArea();

	public debugform() {
		super();
		getContentPane().add(text1);
		setBounds(0, 100, 500, 100);
		setAlwaysOnTop(true);
		setVisible(true);
	}
}

class TaxiGUI {// GUIæŽ¥å�£ç±»
	public void LoadMap(int[][] map, int size) {
		guigv.m.map = new int[size + 5][size + 5];
		guigv.lightmap = new int[size + 5][size + 5];// åˆ�å§‹åŒ–çº¢ç»¿ç�¯
		// å¤�åˆ¶åœ°å›¾
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				guigv.m.map[i][j] = map[i][j];
			}
		}
		// å¼€å§‹ç»˜åˆ¶åœ°å›¾,å¹¶æ¯�100msåˆ·æ–°
		new myform();
		Thread th = new Thread(new Runnable() {
			public void run() {
				int timewindow = 200;// æ—¶é—´çª—è®¾ç½®ä¸º200ms
				int timecount = 0;// è®¡æ—¶
				while (true) {
					gv.stay(100);
					timecount += 100;
					if (timecount > timewindow) {
						timecount = 0;
						// é‡�æ–°è®°å½•æµ�é‡�ä¿¡æ�¯
						guigv.ClearFlow();
					}
					guigv.drawboard.repaint();
				}
			}
		});
		th.start();
		guigv.m.initmatrix();// åˆ�å§‹åŒ–é‚»æŽ¥çŸ©é˜µ
	}

	public void SetTaxiStatus(int index, Point point, int status) {
		guitaxi gt = guigv.taxilist.get(index);
		guigv.AddFlow(gt.x, gt.y, point.x, point.y);// ç»Ÿè®¡æµ�é‡�
		gt.x = point.x;
		gt.y = point.y;
		gt.status = status;
	}

	public void SetTaxiType(int index, int type) {
		guitaxi gt = guigv.taxilist.get(index);
		gt.type = type;
	}

	public void RequestTaxi(Point src, Point dst) {
		// å°†srcå‘¨å›´æ ‡çº¢
		guigv.srclist.add(src);
		// è®¡ç®—æœ€çŸ­è·¯å¾„çš„å€¼,é€šè¿‡ä¸€ä¸ªçª—å�£å¼¹å‡º
		int distance = guigv.m.distance(src.x, src.y, dst.x, dst.y);
		debugform form1 = new debugform();
		form1.text1.setText("ä»Ž(" + src.x + "," + src.y + ")åˆ°(" + dst.x + "," + dst.y + ")çš„æœ€çŸ­è·¯å¾„é•¿åº¦æ˜¯" + distance);
	}

	public void SetLightStatus(Point p, int status) {// è®¾ç½®çº¢ç»¿ç�¯ status 0 æ²¡æœ‰çº¢ç»¿ç�¯ 1
														// ä¸œè¥¿æ–¹å�‘ä¸ºç»¿ç�¯ 2 ä¸œè¥¿æ–¹å�‘ä¸ºçº¢ç�¯
		guigv.lightmap[p.x][p.y] = status;
	}

	public void SetRoadStatus(Point p1, Point p2, int status) {// status 0å…³é—­ 1æ‰“å¼€
		synchronized (guigv.m.map) {
			int di = p1.x - p2.x;
			int dj = p1.y - p2.y;
			Point p = null;
			if (di == 0) {// åœ¨å�Œä¸€æ°´å¹³çº¿ä¸Š
				if (dj == 1) {// p2-p1
					p = p2;
				} else if (dj == -1) {// p1-p2
					p = p1;
				} else {
					return;
				}
				if (status == 0) {// å…³é—­
					if (guigv.m.map[p.x][p.y] == 3) {
						guigv.m.map[p.x][p.y] = 2;
					} else if (guigv.m.map[p.x][p.y] == 1) {
						guigv.m.map[p.x][p.y] = 0;
					}
				} else if (status == 1) {// æ‰“å¼€
					if (guigv.m.map[p.x][p.y] == 2) {
						guigv.m.map[p.x][p.y] = 3;
					} else if (guigv.m.map[p.x][p.y] == 0) {
						guigv.m.map[p.x][p.y] = 1;
					}
				}
			} else if (dj == 0) {// åœ¨å�Œä¸€ç«–ç›´çº¿ä¸Š
				if (di == 1) {// p2-p1
					p = p2;
				} else if (di == -1) {// p1-p2
					p = p1;
				} else {
					return;
				}
				if (status == 0) {// å…³é—­
					if (guigv.m.map[p.x][p.y] == 3) {
						guigv.m.map[p.x][p.y] = 1;
					} else if (guigv.m.map[p.x][p.y] == 2) {
						guigv.m.map[p.x][p.y] = 0;
					}
				} else if (status == 1) {// æ‰“å¼€
					if (guigv.m.map[p.x][p.y] == 1) {
						guigv.m.map[p.x][p.y] = 3;
					} else if (guigv.m.map[p.x][p.y] == 0) {
						guigv.m.map[p.x][p.y] = 2;
					}
				}
			}
			return;
		}
	}

	public TaxiGUI() {
		// åˆ�å§‹åŒ–taxilist
		for (int i = 0; i < 30; i++) {
			guitaxi gt = new guitaxi();
			guigv.taxilist.add(gt);
			SetTaxiType(i, 1);
		}
		for (int i = 0; i < 70; i++) {
			guitaxi gt = new guitaxi();
			guigv.taxilist.add(gt);
			SetTaxiType(i, 2);
		}
	}
}