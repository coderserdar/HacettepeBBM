import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.Vector;
 
public class Printing extends JFrame 
{
	JPanel  pan  = new myPan();
	Vector<Line> as = new Vector<Line>();
	 
public Printing(Vector<Line> l)
{
	addWindowListener(new WindowAdapter() 
    {	public void windowClosing(WindowEvent ev) 
		{	dispose();
			System.exit(0);}});
 	setBounds(10,10,800,600);
	getContentPane().add(pan,BorderLayout.CENTER);
	setVisible(true);
}
  
public class myPan extends JPanel
{
  Point f1,f2;
  
public myPan()
{
	Point f1,f2;
}

public void painting(Graphics g,Vector<Line> l)
{
	super.paint(g);
	g.setColor(Color.black);
	for(int i=0;i<l.size();i++){
		g.drawLine(l.elementAt(i).a.x,l.elementAt(i).a.y,l.elementAt(i).b.x,l.elementAt(i).b.y); 
	}
	   
}

}
}
