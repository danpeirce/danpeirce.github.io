import processing.core.*; 
import processing.xml.*; 

import org.gwoptics.graphics.graph2D.Graph2D; 
import org.gwoptics.graphics.graph2D.traces.Blank2DTrace; 

import java.applet.*; 
import java.awt.Dimension; 
import java.awt.Frame; 
import java.awt.event.MouseEvent; 
import java.awt.event.KeyEvent; 
import java.awt.event.FocusEvent; 
import java.awt.Image; 
import java.io.*; 
import java.net.*; 
import java.text.*; 
import java.util.*; 
import java.util.zip.*; 
import java.util.regex.*; 

public class random_scatter_plot extends PApplet {

/*
  ScatterPlot
  
  Example showing how to use blank2DCanvas to quickly create a simple scatter plot.
*/




  class Point2D{
    public float X,Y;
    public Point2D(float x, float y){X=x;Y=y;}
  }

  class ScatterTrace extends Blank2DTrace{
    private ArrayList _data;
    private float pSize = 0.08f;
    
    public ScatterTrace(){
      _data = new ArrayList();
    }
    
    public void addPoint(float x, float y){_data.add(new Point2D(x,y));}
  
    private void drawPoint(Point2D p, PGraphics canvas){
      canvas.pushStyle();
      canvas.stroke(255,0,0);
      canvas.line(p.X-pSize,p.Y,p.X+pSize,p.Y);
      canvas.line(p.X,p.Y-pSize,p.X,p.Y+pSize);      
      canvas.popStyle();
    }
    
    public void TraceDraw(PGraphics canvas) {
      if(_data != null){            
        for (int i = 0;i < _data.size(); i++) {
          drawPoint((Point2D)_data.get(i),canvas);	          
        }
      }
    }
  }
  
  ScatterTrace sTrace;
  Graph2D g;
  	
  public void setup(){
    size(600,500);
    
    sTrace  = new ScatterTrace();
    
    g = new Graph2D(this, 400,400, true);
    g.setAxisColour(0, 0, 0);
    g.setFontColour(0, 0, 0);
    		
    g.position.y = 50;
    g.position.x = 100;
    		
    g.setYAxisTickSpacing(1f);
    g.setXAxisTickSpacing(1f);
    
    g.setXAxisMinorTicks(1);
    g.setYAxisMinorTicks(1);
    
    g.setYAxisMin(0f);
    g.setYAxisMax(10f);
    		
    g.setXAxisMin(0f);
    g.setXAxisMax(10f);
    g.setXAxisLabelAccuracy(0);
    
    g.addTrace(sTrace);
    		
    for(int i=0;i<10;i++){
      sTrace.addPoint(random(0,10),random(0,10));
    }
  }
  	
  public void draw(){
    background(255);
    g.draw();
  }

  static public void main(String args[]) {
    PApplet.main(new String[] { "--bgcolor=#ECE9D8", "random_scatter_plot" });
  }
}
