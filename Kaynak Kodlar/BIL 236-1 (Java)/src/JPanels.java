import java.awt.*; 
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Vector;

import javax.swing.*; 
 
public class JPanels extends JFrame { 
  public static void main(String[] args) { 
    new JPanels(); 
  }
  public JPanels() { 
	    super("Using JPanels with Borders"); 
	    addWindowListener(new WindowAdapter() 
	    {	public void windowClosing(WindowEvent ev) 
			{	dispose();
				System.exit(0);}});
	    Container content = getContentPane(); 
	    content.setBackground(Color.blue); 
	    JPanel drawingArea = new JPanel(); 
	    // Preferred height is irrelevant, since using WEST region 
	    drawingArea.setPreferredSize(new Dimension(800, 600)); 
	    drawingArea.setBorder(BorderFactory.createLineBorder (Color.blue, 2)); 
	    drawingArea.setBackground(Color.white); 
	    content.add(drawingArea, BorderLayout.WEST); 
	    pack();
	    setVisible(true); 
  } 
  public void painting(Graphics g,Point a,Point b)
  {
  	super.paint(g);
  	g.setColor(Color.black);
  	g.drawLine(a.x, a.y, b.x, b.y); 
  	
  	   
  }
}