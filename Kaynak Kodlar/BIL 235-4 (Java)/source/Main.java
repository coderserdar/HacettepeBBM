import java.util.*;
import java.io.*;

public class Main {
	public static int DEFAULT_STACK_VALUE=100;

	public static void main(String[] args) throws IOException {
		
		Operations o = new Operations();
		BufferedWriter output = new BufferedWriter(new FileWriter("output.txt"));
		Vector<Node> NodeList = new Vector<Node>();
		Vector<Vehicle> VehicleList = new Vector<Vehicle>();
		String DistanceFile = args[0];
		String PackageFile = args[1];
		String TaskFile = args[2];
		String CommandFile = args[3];
		NodeList = o.ReadDistancesFile(DistanceFile);
		o.ReadPackageListFile(PackageFile,NodeList);
		VehicleList = o.ReadTaskListFile(TaskFile);
		
		o.ReadCommandFiles(CommandFile,NodeList,VehicleList,output);
		
		/*
		for(int b = 0 ; b < NodeList.size() ; b++)
		{
			if(NodeList.elementAt(b).EdgeList.size() != 0)
			{
				System.out.println("The node's name is " + NodeList.elementAt(b).getNodeName());
				output.write("The node's name is " + NodeList.elementAt(b).getNodeName());
				output.newLine();
				System.out.println("And their edges and distances are ") ;
				output.write("And their edges and distances are ") ;
				output.newLine();
				for (int c = 0 ; c < NodeList.elementAt(b).EdgeList.size() ; c ++)
				{
					System.out.println(NodeList.elementAt(b).EdgeList.elementAt(c).getSourceNode().getNodeName() + NodeList.elementAt(b).EdgeList.elementAt(c).getDestinationNode().getNodeName() + "  " + NodeList.elementAt(b).EdgeList.elementAt(c).getEdgeDistance());
					output.write(NodeList.elementAt(b).EdgeList.elementAt(c).getSourceNode().getNodeName() + "" + NodeList.elementAt(b).EdgeList.elementAt(c).getDestinationNode().getNodeName() + "  " + NodeList.elementAt(b).EdgeList.elementAt(c).getEdgeDistance());
					output.newLine();
				}
				output.write("And their packages are ") ;
				output.newLine();
				for(int i = 0 ; i < NodeList.elementAt(b).PackageStack.size() ; i++)
				{
					//Package temp = NodeList.elementAt(b).PackageStack.pop();
					output.write(NodeList.elementAt(b).PackageStack.elementAt(i).getPackageName());
					output.newLine();
				}
				
				output.write("And their nodes are ") ;
				output.newLine();
				for(int ib = 0 ; ib < NodeList.elementAt(b).Nodelist.size() ; ib++)
				{
					//Package temp = NodeList.elementAt(b).PackageStack.pop();
					output.write(NodeList.elementAt(b).Nodelist.elementAt(ib).getNodeName());
					output.newLine();
				}
			}
			else
			{
				
			}
		}
		
		for(int c = 0 ; c < VehicleList.size() ; c++)
		{
			output.write("The vehicle's name is " + VehicleList.elementAt(c).getVehicleName());
			output.newLine();
			output.write("And their tasks are ");
			output.newLine();
			for(int d = 0 ; d < VehicleList.elementAt(c).TaskList.size() ; d++)
			{
				output.write(VehicleList.elementAt(c).TaskList.elementAt(d).getSource() + "  " + VehicleList.elementAt(c).TaskList.elementAt(d).getDestination() + "  " + VehicleList.elementAt(c).TaskList.elementAt(d).getPackageNumber() + "  ");
				output.newLine();
			}
		}
		
		*/
		
		output.close();
		
		
	}

}
