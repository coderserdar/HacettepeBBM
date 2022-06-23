import java.util.Vector;
//import javax.swing.JPanel;
import java.awt.*;

import javax.swing.*;

import java.awt.event.*;

public class Operations {
	int i;
	private Point P, Q;
	Point zero = new Point(0,0);
	double[] norm2;
	int  j, k, l, m;
	private double quick, D, x, y, r2;
	private boolean noneInCirc;
	private final boolean DEBUG = false;
	private final int pixelWidth = 0;
	Vector<Line>line = new Vector<Line>();
	//Printing a = new Printing();
	Graphics g;
	//JPanels panel = new JPanels();
	
	
	
	public Operations(Vector<Point> v) {
		super();
		findNorms2(v);
		drawBoundaries(v);
		Printing a = new Printing(line);
	}

	private void drawBoundaries(Vector<Point> v) {
		for ( i = 0 ; i < v.size() ; i++ )
		    surround(i,v);
	}

	private void surround(int i,Vector<Point> v) {
		for ( j = 0 ; j < v.size() ; j++ )
		{
		    for ( k = 0 ; k < v.size() ; k++ )
			if ( trueCircumcircle(v,i,j,k) )
			    for ( m = 0 ; m < v.size() ; m++ ) {
				if ( trueCircumcircle(v,i,j,m) ||
				     trueCircumcircle(v,j,m,i) ||
				     trueCircumcircle(v,m,i,j) )
				    connectAbout(v,i,j,k,m);
			    }
		}
	}

	private double dist2(Point a, Point b) {
		return ( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
	}

	private void findNorms2(Vector<Point> v) {
		
		norm2 = new double[v.size()];
		for ( i = 0 ; i < v.size() ; i++ ) {
		    norm2[i] = dist2(zero,v.elementAt(i));
		}		
	}
	
	  private void connectAbout(Vector<Point> v,int i, int j, int k, int m) {
			P = circumcenter(v,i,j,k);
			Q = circumcenter(v,i,j,m);
			Line l = new Line(P,Q);
			line.add(l);
			//g.drawLine(P.x, P.y, Q.x, Q.y);
			
	  }
	  
	  private boolean trueCircumcircle(Vector<Point> v,int i, int j, int k) {
			noneInCirc = true;
			if ( (v.elementAt(i).x-v.elementAt(k).x)*(v.elementAt(j).y-v.elementAt(k).y)==
			     (v.elementAt(j).x-v.elementAt(k).x)*(v.elementAt(i).y-v.elementAt(k).y) )
			    noneInCirc = false;
			P = circumcenter(v,i,j,k);
			r2 = dist2(P,v.elementAt(i));
			for ( l = 0 ; l < v.size() && noneInCirc ; l++ )
			    if ( l != i && l != j && l != k )
				noneInCirc &= ( dist2(v.elementAt(l),P) >= r2 );
			if ( noneInCirc && DEBUG )
			{
				//g.drawRect(P.x, P.y, 2+pixelWidth, 2+pixelWidth);
			}
			return noneInCirc;
	  }
	  
	  private Point circumcenter(Vector<Point> v,int i, int j, int k) {
	        D = 2*( (v.elementAt(i).x-v.elementAt(k).x)*(v.elementAt(j).y-v.elementAt(k).y)
			- (v.elementAt(j).x-v.elementAt(k).x)*(v.elementAt(i).y-v.elementAt(k).y) );
	        x = ( ( norm2[i]-norm2[k] ) * (v.elementAt(j).y-v.elementAt(k).y)
		      - ( norm2[j]-norm2[k] ) * (v.elementAt(i).y-v.elementAt(k).y) ) / D;
	        y = ( ( norm2[j]-norm2[k] ) * (v.elementAt(i).x-v.elementAt(k).x)
	             -  ( norm2[i]-norm2[k] ) * (v.elementAt(j).x-v.elementAt(k).x) ) / D;
		return new Point( (int) x, (int) y);
	  }

}

