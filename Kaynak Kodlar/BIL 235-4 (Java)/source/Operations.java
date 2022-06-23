import java.util.*;
import java.io.*;
import java.util.PriorityQueue;
import java.util.Collections;
import java.util.Vector;

public class Operations {
	
	public Operations()
	{
		
	}//constructor of the operation class
	
	public Vector<Node> ReadDistancesFile(String FileName) throws IOException , FileNotFoundException
	{
		char Name[] = {'A','B','C','D','E','F','G','H','I','J'};
		Vector<Node> NodeList = new Vector<Node>();
		int i = 0 ;
		int counter = 0 ;
		int distance ;
		String line , dist = new String();
		for(int b = 0 ; b < 10 ; b++)
		{
			Vector<Edge> edgelist = new Vector<Edge>();
			Vector<Node> nodelist = new Vector<Node>();
			Stack<Package> packagelist = new Stack<Package>();
			Node temp = new Node(Name[b],edgelist,nodelist,packagelist,Integer.MAX_VALUE,b);
			NodeList.addElement(temp);
		}
		BufferedReader input = new BufferedReader(new FileReader(FileName));
		BufferedWriter output = new BufferedWriter(new FileWriter("output.txt"));
		while((line = input.readLine()) != null)
		{
			StringTokenizer token = new StringTokenizer(line);
			counter = token.countTokens();
			if((counter < 3) || (counter > 10))
			{
				System.out.println("This input file is not suitable for the simulation..\n");
				break ;
			}
			else
			{
				counter = 0 ;
				while(token.hasMoreTokens())
				{
					dist = token.nextToken();
					distance = Integer.parseInt(dist);
					if((distance == 0) || (distance == -1))
					{
						
					}
					else
					{
						for(int counter2 = 0 ; counter2 < NodeList.size() ; counter2 ++)
						{
							if(counter == NodeList.elementAt(counter2).getNodeNumber())
							{
								for(int counter3 = 0 ; counter3 < NodeList.size() ; counter3 ++)
								{
									if(i == NodeList.elementAt(counter3).getNodeNumber())
									{
										Edge edge = new Edge(NodeList.elementAt(counter3),NodeList.elementAt(counter2),distance);
										//String tempname = new String();
										//tempname.concat();
										NodeList.elementAt(counter3).Nodelist.addElement(NodeList.elementAt(counter2));
										NodeList.elementAt(counter3).EdgeList.addElement(edge);
										//NodeList.elementAt(counter2).EdgeList.addElement(edge);
									}
								}
							}
						}
							
					}//end of the else
					counter++ ;
				}
			}
			i++ ;
		}
		/*
		for(int b = 0 ; b < i ; b++)
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
		}
		*/
		input.close();
		output.close();
		return NodeList ;
		
	}//end of the reading the distances and the names of the nodes from the distance input file..
	
	
	public void ReadPackageListFile(String FileName , Vector<Node> NodeList) throws IOException , FileNotFoundException
	{
		String line , number ,temp = new String();
		int counter = 0 , real , counter2 = 0;
		BufferedReader input = new BufferedReader(new FileReader(FileName));
		while((line = input.readLine()) != null)
		{
			StringTokenizer token = new StringTokenizer(line);
			counter = token.countTokens();
			number = token.nextToken() ;
			real = Integer.parseInt(number);
			if(counter != real + 1)
			{
				break ;
			}
			else
			{
				for(int a = 0 ; a < real ; a++)
				{
					temp = token.nextToken() ;
					Package nodePackage = new Package(temp);
					NodeList.elementAt(counter2).PackageStack.push(nodePackage);
				}
			}
			counter2 ++ ;
		}
		
	}//end of the read packages from the package input file
	
	public Vector <Vehicle> ReadTaskListFile(String FileName) throws IOException , FileNotFoundException
	{
		int i = 0 ;
		Vector <Vehicle> VehicleList = new Vector<Vehicle>();
		int number , packagenumber ;
		String line , name , num , source , dest = new String();
		Stack <Package> vehiclepackages = new Stack<Package>();
		BufferedReader input = new BufferedReader(new FileReader(FileName));
		while((line = input.readLine()) != null)
		{
			StringTokenizer token = new StringTokenizer(line);
			name = token.nextToken() ;
			num = token.nextToken() ;
			number = Integer.parseInt(num);
			Vector <State> statelist = new Vector<State>();
			Vector <Task> tasklist = new Vector<Task>();
			Vector <Node> shortest = new Vector<Node>();
			Vehicle temp = new Vehicle(name , statelist , vehiclepackages , tasklist) ;
			VehicleList.addElement(temp);
			for(int counter2 = 0 ; counter2 < number ; counter2++)
			{
				line = input.readLine() ;
				//System.out.println(line);
				StringTokenizer token2 = new StringTokenizer(line);
				source = token2.nextToken() ;
				dest = token2.nextToken() ;
				num = token2.nextToken() ;
				packagenumber = Integer.parseInt(num);
				Task temp2 = new Task(source , dest , shortest , packagenumber);
				VehicleList.elementAt(i).TaskList.addElement(temp2);				
			}
			
			i++ ;
		}
				
		return VehicleList;		
		
	}//end of the reading tasks from the task input file
	
	public void ReadCommandFiles(String FileName,Vector<Node> NodeList,Vector<Vehicle> VehicleList,BufferedWriter output) throws IOException , FileNotFoundException
	{
		String line , number , command , source , dest , vehicle , time = new String();
		int real , realtime;
		BufferedReader input = new BufferedReader(new FileReader(FileName));
		while((line = input.readLine()) != null)
		{
			StringTokenizer token = new StringTokenizer(line);
			command = token.nextToken() ;
			if(command.equals("get_graph_info"))
			{
				number = token.nextToken();
				real = Integer.parseInt(number);
				GetGraphInfo(NodeList,VehicleList,real,output);
			}//if the command is about getting the information of the graph
			
			else if(command.equals("print_shortest_path"))
			{
				source = token.nextToken() ; 
				dest = token.nextToken() ;
				PrintShortestPath2(source,dest,NodeList,output);
				//PrintShortestPath(source,dest,NodeList,output);
			}//if the command is printing the shortest path by the source to the destination
			
			else if(command.equals("print_vehicle_package_lists"))
			{
				time = token.nextToken() ;
				realtime = Integer.parseInt(time);
				PrintVehiclePackageLists(NodeList,VehicleList,realtime,output);
			}//if the command is printing the packages of the vehicles
			
			else if(command.equals("print_node_package_lists"))
			{
				time = token.nextToken() ;
				realtime = Integer.parseInt(time);
				//PrintNodePackageLists(NodeList,VehicleList,realtime,output);
			}//if the command is printing the packages of the nodes
			
			else if(command.equals("print_vehicle_state"))
			{
				vehicle = token.nextToken() ;
				time = token.nextToken() ;
				realtime = Integer.parseInt(time);
				//PrintVehicleState(VehicleList,NodeList,vehicle,realtime,output);
			}//if the command is printing the state of the vehicle
			
			else
			{
				output.write("This is not a suitable command for this simulation.");
				output.newLine();
			}//if the command is not in a suitable format for that experiment
			
		}//end of while
	}//end of the reading commands from the command file




	public void GetGraphInfo(Vector<Node> NodeList,Vector<Vehicle> vehicleList, int real, BufferedWriter output) throws IOException 
	{
		int i = 0 , counter , decision;
		output.write("get_graph_info " + real);
		output.newLine();
		for(i = 0 ; i < NodeList.size() ; i++)
		{
			for(counter = 0 ; counter < NodeList.elementAt(i).EdgeList.size() ; counter++)
			{
				Edge temp = new Edge(NodeList.elementAt(i).EdgeList.elementAt(counter).DestinationNode , NodeList.elementAt(i).EdgeList.elementAt(counter).SourceNode , NodeList.elementAt(i).EdgeList.elementAt(counter).EdgeDistance);
				//output.write(temp.getSourceNode().getNodeName() + " " + temp.getDestinationNode().getNodeName() + " " + temp.getEdgeDistance());
				//output.newLine() ;
				decision = Search(temp,NodeList,i);
				if(decision == 1)
				{
					
				}
				else
				{
					output.write(NodeList.elementAt(i).EdgeList.elementAt(counter).SourceNode.getNodeName() + " " + NodeList.elementAt(i).EdgeList.elementAt(counter).DestinationNode.getNodeName() + " " + NodeList.elementAt(i).EdgeList.elementAt(counter).getEdgeDistance());
					output.newLine();
				}
			}
		}
		
		
	}//this function is used to give the edges of the graph informations

	public int Search(Edge temp, Vector<Node> nodeList, int i) {
		int counter , counter2 ;
		int control = 0 ;
		for(counter = 0 ; counter < i ; counter++)
		{
			for(counter2 = 0 ; counter2 < nodeList.elementAt(counter).EdgeList.size() ; counter2++)
			{
				if(nodeList.elementAt(counter).EdgeList.elementAt(counter2).getSourceNode().equals(temp.getSourceNode()) )
				{
					if(nodeList.elementAt(counter).EdgeList.elementAt(counter2).getDestinationNode().equals(temp.getDestinationNode()) )
					{
						if(nodeList.elementAt(counter).EdgeList.elementAt(counter2).getEdgeDistance() == temp.getEdgeDistance())
						{
							control = 1 ;
							break ;
						}
					}
					
				}
			}
		}
		
		return control ;
	}// this function is used to search an edge in graph if that is defined before...
	
	/*
	public Vector<Node> findTheShortestPath(Node source , Node destination)
	{
		Vector<Node> searchNodes = new Vector<Node>();
		Vector<Node> pathNodes = new Vector<Node>();
		Vector<Path> probablePaths = new Vector<Path>();
	}
	*/
	
	public void PrintVehicleState(Vector<Vehicle> vehicleList, Vector<Node> nodeList , String vehicle ,int realtime, BufferedWriter output) throws IOException
	{
		output.write("print_vehicle_state " + vehicle + " " + realtime);
		output.newLine() ;
		Vector <Vehicle> tempVehicleList = vehicleList ;
		Vector<Node> tempNodeList = nodeList ;
		int control = 0 ;
		tempVehicleList = processAll(tempNodeList,tempVehicleList,realtime);
		if(realtime == 0)
		{
			for(int a = 0 ; a < tempVehicleList.size() ; a ++)
			{
				if(vehicle.equals(tempVehicleList.elementAt(a).getVehicleName()))
				{
					control = 1 ;
					output.write(vehicle + " " + tempVehicleList.elementAt(a).TaskList.elementAt(0).Source + " " + realtime);
					output.newLine() ;
				}
			}
		}
		
		else
		{
			for(int a = 0 ; a < tempVehicleList.size() ; a ++)
			{
				if(vehicle.equals(tempVehicleList.elementAt(a).getVehicleName()))
				{
					control = 1 ;
					if(tempVehicleList.elementAt(a).StateList.elementAt(realtime).getStateEdge() != null)
					{
						output.write(vehicle + " " + tempVehicleList.elementAt(a).StateList.elementAt(realtime).getStateEdge().getSourceNode().getNodeName() + " " + tempVehicleList.elementAt(a).StateList.elementAt(realtime).getStateEdge().getDestinationNode().getNodeName()  + " " + realtime);
						output.newLine() ;
					}
					else
					{
						output.write(vehicle + " " + tempVehicleList.elementAt(a).StateList.elementAt(realtime).getStateNode().getNodeName() +  " " + realtime);
						output.newLine() ;
					}
				}
			}
		}
		
	}
	
	public void PrintNodePackageLists(Vector<Node> nodeList, Vector<Vehicle> vehicleList, int realtime, BufferedWriter output) throws IOException , EmptyStackException
	{
		Vector<Vehicle> tempVehicleList = vehicleList;
		Vector<Node> tempNodeList = nodeList ;
		/*
		for(int a = 0 ; a < tempNodeList.size() ; a ++)
		{
			for(int b = 0 ; b < tempNodeList.elementAt(a).PackageStack.size() ; b++)
			{
				//System.out.println(tempNodeList.elementAt(a).PackageStack.elementAt(b).getPackageName());
			}
		}
		*/
		tempNodeList = processAll2(tempNodeList,tempVehicleList,realtime);
		output.write("print_node_package_lists " + realtime);
		output.newLine() ;
		for(int a = 0 ; a < tempNodeList.size() ; a++)
		{
			output.write(tempNodeList.elementAt(a).getNodeName() + " ");
			if(tempNodeList.elementAt(a).PackageStack.size() == 0)
			{
				output.newLine() ;
			}
			else
			{
				for(int b = 0 ; b < tempNodeList.elementAt(a).PackageStack.size()-1 ; b++)
				{
					output.write(tempNodeList.elementAt(a).PackageStack.elementAt(b) + ", ");
				}
				output.write(tempNodeList.elementAt(a).PackageStack.elementAt((tempNodeList.elementAt(a).PackageStack.size()-1)).getPackageName());
				output.newLine() ;
			}
		}
		
	}//this function is used to print the packages of the nodes

	public void PrintVehiclePackageLists(Vector<Node> nodeList, Vector<Vehicle> vehicleList ,int realtime, BufferedWriter output) throws IOException , EmptyStackException
	{
		Vector<Vehicle> tempVehicleList = vehicleList;
		Vector<Node> tempNodeList = nodeList ;
		/*
		for(int a = 0 ; a < tempNodeList.size() ; a ++)
		{
			for(int b = 0 ; b < tempNodeList.elementAt(a).PackageStack.size() ; b++)
			{
				System.out.println(tempNodeList.elementAt(a).PackageStack.elementAt(b).getPackageName());
			}
		}
		*/
		tempVehicleList = processAll(tempNodeList,tempVehicleList,realtime);
		output.write("print_vehicle_package_lists " + realtime);
		output.newLine() ;
		for(int a = 0 ; a < tempVehicleList.size() ; a++)
		{
			output.write(tempVehicleList.elementAt(a).getVehicleName() + " ");
			if(tempVehicleList.elementAt(a).VehiclePackages.size() == 0)
			{
				output.newLine() ;
			}
			else
			{
				for(int b = 0 ; b < tempVehicleList.elementAt(a).VehiclePackages.size()-1 ; b++)
				{
					output.write(tempVehicleList.elementAt(a).VehiclePackages.elementAt(b) + ", ");
				}
				output.write(tempVehicleList.elementAt(a).VehiclePackages.elementAt((tempVehicleList.elementAt(a).VehiclePackages.size()-1)).getPackageName());
				output.newLine() ;
			}
		}
		
	}//this function is used to print the packages of the vehicles

	public Vector<Vehicle> processAll(Vector<Node> nodeList, Vector<Vehicle> vehicleList,int realtime)
	{
		int initialize = 0 , initialvalue = 0 ;
		int temppath = 0 ;
		int path = 0 ;
		int increment = 5 ;
		int counter , counter2 , counter3 = 0 , counter4 = 0 , counter5 = 0 ;
		Vector<Node> shortpath ;
		Node a = null , b = null;
		
		for(int i = 0 ; i < vehicleList.size() ; i++)
		{
			initialize(nodeList , vehicleList , initialize , i);
			vehicleList.elementAt(i).VehiclePath = organize(nodeList , vehicleList , counter3 , counter4) ;
		}
		
		for(counter = 0 ; counter < realtime ; counter++)
		{
			path = path + increment ;
			for(counter2 = 0 ; counter2 < vehicleList.size() ; counter2 ++)
			{
				
				if(counter5 + 1 >= (vehicleList.elementAt(counter2).VehiclePath.size() - 1))
				{
					State temp2 = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(vehicleList.elementAt(counter2).VehiclePath.size()-1),0);
					vehicleList.elementAt(counter2).StateList.addElement(temp2);
					for(int d = 0 ; d < nodeList.size() ; d++)
					{
						if(vehicleList.elementAt(counter2).VehiclePath.elementAt(vehicleList.elementAt(counter2).VehiclePath.size()-1).getNodeName() == nodeList.elementAt(d).getNodeName())
						{
							for(int e = 0 ; e < vehicleList.elementAt(counter2).VehiclePackages.size() ; e++)
							{
								Package ab = vehicleList.elementAt(counter2).VehiclePackages.pop() ;
								//System.out.println(ab.getPackageName() + "  " + vehicleList.elementAt(counter2).getVehicleName()) ;
								nodeList.elementAt(d).PackageStack.push(ab);
							}
						}
					}
					initialize = initialize + 1 ;
					if(initialize >= vehicleList.elementAt(counter2).TaskList.size())
					{
						
					}
					else
					{
						initialize = initialize + 1 ;
						if(initialize >= vehicleList.elementAt(counter2).TaskList.size())
						{
							
						}
						else
						{
							initialize(nodeList , vehicleList , initialize, counter2);
							vehicleList.elementAt(counter2).VehiclePath = organize(nodeList , vehicleList , counter2 , counter4 + 1) ;
						}
					}
				}
				else
				{
					a = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5) ;
					b = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5 + 1) ;
				}
				
				
				for(int k = 0 ; k < vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.size() ; k++)
				{
					if((vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getSourceNode() == a) && (vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getDestinationNode() == b))
					{
						temppath = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getEdgeDistance() ;
						if (path != temppath)
						{
							State temp = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k) , path) ;
							vehicleList.elementAt(counter2).StateList.addElement(temp);
						}
						else
						{
							State temp2 = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getDestinationNode() , 0) ;
							vehicleList.elementAt(counter2).StateList.addElement(temp2);
							path = 0 ;
							counter5 ++ ;
						}
						break ;
					}
				}
										
			}
		}
		return vehicleList ;
	}//this function is used to process the events by the given time...
	
	
	public Vector<Node> processAll2(Vector<Node> nodeList, Vector<Vehicle> vehicleList,int realtime)
	{
		int initialize = 0 , initialvalue = 0 ;
		int temppath = 0 ;
		int path = 0 ;
		int increment = 5 ;
		int counter , counter2 , counter3 = 0 , counter4 = 0 , counter5 = 0 ;
		Vector<Node> shortpath ;
		Node a = null , b = null;
		
		for(int i = 0 ; i < vehicleList.size() ; i++)
		{
			initialize(nodeList , vehicleList , initialize , i);
			vehicleList.elementAt(i).VehiclePath = organize(nodeList , vehicleList , counter3 , counter4) ;
		}
		
		for(counter = 0 ; counter < realtime ; counter++)
		{
			
			for(counter2 = 0 ; counter2 < vehicleList.size() ; counter2 ++)
			{
				path = path + increment ;
				
				if(counter5 + 1 >= (vehicleList.elementAt(counter2).VehiclePath.size() - 1))
				{
					State temp2 = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(vehicleList.elementAt(counter2).VehiclePath.size()-1),0);
					vehicleList.elementAt(counter2).StateList.addElement(temp2);
					for(int d = 0 ; d < nodeList.size() ; d++)
					{
						if(vehicleList.elementAt(counter2).VehiclePath.elementAt(vehicleList.elementAt(counter2).VehiclePath.size()-1).getNodeName() == nodeList.elementAt(d).getNodeName())
						{
							for(int e = 0 ; e < vehicleList.elementAt(counter2).VehiclePackages.size() ; e++)
							{
								Package ab = vehicleList.elementAt(counter2).VehiclePackages.pop() ;
								nodeList.elementAt(d).PackageStack.push(ab);
							}
						}
					}
					initialize = initialize + 1 ;
					if(initialize >= vehicleList.elementAt(counter2).TaskList.size())
					{
						
					}
					else
					{
						initialize = initialize + 1 ;
						if(initialize >= vehicleList.elementAt(counter2).TaskList.size())
						{
							
						}
						else
						{
							initialize(nodeList , vehicleList , initialize, counter2);
							vehicleList.elementAt(counter2).VehiclePath = organize(nodeList , vehicleList , counter2 , counter4 + 1) ;
						}
					}
				}
				else
				{
					a = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5) ;
					b = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5 + 1) ;
				}
				
				
				for(int k = 0 ; k < vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.size() ; k++)
				{
					if((vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getSourceNode() == a) && (vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getDestinationNode() == b))
					{
						temppath = vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getEdgeDistance() ;
						if (path != temppath)
						{
							State temp = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k) , path) ;
							vehicleList.elementAt(counter2).StateList.addElement(temp);
						}
						else
						{
							State temp2 = new State(vehicleList.elementAt(counter2).VehiclePath.elementAt(counter5).EdgeList.elementAt(k).getDestinationNode() , 0) ;
							vehicleList.elementAt(counter2).StateList.addElement(temp2);
							path = 0 ;
							counter5 ++ ;
						}
						break ;
					}
				}
				
				

							
			}
		}
		return nodeList ;
	}
	
	public Vector<Node> organize(Vector<Node> nodeList, Vector<Vehicle> vehicleList , int counter3 , int counter4)
	{
		String source,dest ;
		Vector<Node> temppath = new Vector<Node>();
		source = vehicleList.elementAt(counter3).TaskList.elementAt(counter4).getSource() ;
		dest = vehicleList.elementAt(counter3).TaskList.elementAt(counter4).getDestination() ;
		for(int b = 0 ; b < nodeList.size() ; b++)
		{
			if(source.charAt(0) == nodeList.elementAt(b).getNodeName())
			{
				computePaths(nodeList.elementAt(b));
			}
		}
		for(int c = 0 ; c < nodeList.size() ; c++)
		{
			if(dest.charAt(0) == nodeList.elementAt(c).getNodeName())
			{
				 temppath = getShortestPathTo(nodeList.elementAt(c));
			}
		}
		return temppath ;
	}

	private void initialize(Vector<Node> nodeList, Vector<Vehicle> vehicleList , int initialize , int element)
	{
		int j , counter2 , control = 0;
		int counter = vehicleList.elementAt(element).TaskList.elementAt(initialize).getPackageNumber();
		//System.out.print(counter + "  ");
		String source = vehicleList.elementAt(element).TaskList.elementAt(initialize).getSource() ;
		//System.out.println(source);
		for (j = 0 ; j < nodeList.size() ; j++)
		{
			if(source.charAt(0) == nodeList.elementAt(j).getNodeName())
			{
				control = 1 ;
				for(counter2 = 0 ; counter2 < counter ; counter2++)
				{
					Package a = nodeList.elementAt(j).PackageStack.pop() ;
					//System.out.println(a.getPackageName() + " ASadsds  " );
					vehicleList.elementAt(element).VehiclePackages.push(a);
				}
			}
		}
		
		if(control != 1)
		{
			System.out.println("This is not a suitable node name...");
		}
		
	}//this function is used to initialize the elements

	private void PrintShortestPath2(String source, String dest,
			Vector<Node> NodeList, BufferedWriter output) throws IOException {
		Node first = null , target = null ;
		int i ;
		int j ;
		output.write("print_shortest_path " + source + " " + dest);
		
		MyStack aStack= new MyStack(Main.DEFAULT_STACK_VALUE);/*DEFAULT_STACK_VALUE is default stack value*/
		MyStackElement ele=null;
		for(i = 0 ; i < NodeList.size() ; i++)
		{
			if(source.charAt(0) == NodeList.elementAt(i).getNodeName())
			{
				first = NodeList.elementAt(i);
				//System.out.println(first.getNodeNumber() + "  "  + first.getNodeName() );
				//computePaths(NodeList.elementAt(i));
				break ;
				//System.out.println(NodeList.elementAt(i).getNodeName());
			}
		}
		
		for(j = 0 ; j < NodeList.size() ; j++)
		{
			if(dest.charAt(0) == NodeList.elementAt(j).getNodeName())
			{
				target = NodeList.elementAt(j);
				//System.out.println(target.getNodeNumber() + "  "  + target.getNodeName() );
				break ;
				//System.out.println(NodeList.elementAt(j).getNodeName());
			}
		}
		int theShortesDistance=-1;
		MyStackElement resultElement =null;
		if(first.NodeName!=target.NodeName){
			for(i = 0 ; i < first.Nodelist.size() ; i++){
				int dist=100000;
				for(j=0; j< first.EdgeList.size();j++)
				{/*find distance of nodes*/
					if(first.EdgeList.get(j).DestinationNode.NodeName==first.Nodelist.get(i).NodeName)
					{
						dist=first.EdgeList.get(j).EdgeDistance;
						break;
					}
				}
				
				if(target.NodeName==first.Nodelist.elementAt(i).NodeName){
					if(theShortesDistance<0||dist<theShortesDistance)
					{
						theShortesDistance=dist;
						resultElement=new MyStackElement(first.NodeName+""+first.Nodelist.elementAt(i).NodeName,dist,first.Nodelist.elementAt(i));
					}
						
				}
				else{
					
						aStack.push(new MyStackElement(first.NodeName+""+first.Nodelist.elementAt(i).NodeName,dist,first.Nodelist.elementAt(i)));	
					
					
				}
				
			}
			while(aStack.top!=-1)
			{
				ele=aStack.pop();
				int dist=100000;
				for(i = 0 ; i < ele.getCurrent().Nodelist.size() ; i++){
					for(j=0; j< ele.getCurrent().EdgeList.size();j++)
					{/*find distance of nodes*/
						if(ele.getCurrent().EdgeList.get(j).DestinationNode.NodeName==ele.getCurrent().Nodelist.get(i).NodeName)
						{
							dist=ele.getCurrent().EdgeList.get(j).EdgeDistance;
							break;
						}
					}
					
					if(target.NodeName==ele.getCurrent().Nodelist.elementAt(i).NodeName){
						if(theShortesDistance<0||ele.getDistance()+dist<theShortesDistance)
						{
							theShortesDistance=ele.getDistance()+dist;
							resultElement=new MyStackElement(ele.getPath()+""+ele.getCurrent().Nodelist.elementAt(i).NodeName,ele.getDistance()+dist,ele.getCurrent().Nodelist.elementAt(i));
						}
					}
					else{
						if(!ele.getPath().contains(ele.getCurrent().NodeName+""))
						{
							aStack.push(new MyStackElement(ele.getPath()+""+ele.getCurrent().Nodelist.elementAt(i).NodeName,ele.getDistance()+dist,ele.getCurrent().Nodelist.elementAt(i)));
					
						}
					}

				}
				
			}
			
		}
		output.newLine() ;
		if(resultElement!=null){
			for(i=0;i<resultElement.getPath().length();i++)
				output.write(""+resultElement.getPath().charAt(i)+" ");
			 output.write(""+resultElement.getDistance());
			 output.newLine() ;	 
		}
		
		
	}

	public void PrintShortestPath(String source, String dest , Vector<Node> NodeList , BufferedWriter output) throws IOException
	{
		Node first = null , target = null ;
		int i ;
		int j ;
		output.write("print_shortest_path " + source + " " + dest);
		output.newLine() ;
		for(i = 0 ; i < NodeList.size() ; i++)
		{
			if(source.charAt(0) == NodeList.elementAt(i).getNodeName())
			{
				first = NodeList.elementAt(i);
				//System.out.println(first.getNodeNumber() + "  "  + first.getNodeName() );
				//computePaths(NodeList.elementAt(i));
				break ;
				//System.out.println(NodeList.elementAt(i).getNodeName());
			}
		}
		
		for(j = 0 ; j < NodeList.size() ; j++)
		{
			if(dest.charAt(0) == NodeList.elementAt(j).getNodeName())
			{
				target = NodeList.elementAt(j);
				//System.out.println(target.getNodeNumber() + "  "  + target.getNodeName() );
				break ;
				//System.out.println(NodeList.elementAt(j).getNodeName());
			}
		}
		//System.out.println();
		computePaths(first);
		Vector<Node> path = getShortestPathTo(target);
	    for(int k = 0 ; k < path.size() ; k++)
	    {
	    	//System.out.print(path.elementAt(k).getNodeName() + " ");
	    	output.write(path.elementAt(k).getNodeName() + " ");
	    }
	    //System.out.print(path.elementAt(path.size()-1).getNodeLength());
	    output.write(path.elementAt(path.size()-1).getNodeLength());
	    //System.out.print(target.getNodeLength());
	    //System.out.println();
	    output.newLine() ;
	    
	}//this function is used to print the shortest path to the output file
	
	
	public void computePaths(Node source)
    {
		int i = 0 ;
		Vector<Edge> edges ;
		Vector<Node> tempnodes = new Vector<Node>() ;
        source.setNodeLength(0);
        PriorityQueue<Node> NodeQueue = new PriorityQueue<Node>();
        NodeQueue.add(source);
        tempnodes.addElement(source);
		while (!NodeQueue.isEmpty()) {
		    Node u = NodeQueue.poll();
		    	edges = u.getEdgeList() ;
	            Edge a = findMinimumEdge(edges , tempnodes);
	            tempnodes.addElement(a.getDestinationNode());
	            //System.out.println(a.getDestinationNode().getNodeName() + "efwef");
	            for (i = 0 ; i < edges.size() ; i++)
	            {
	            	Edge e = edges.elementAt(i);
	                Node v = e.getDestinationNode();
	                int weight = e.getEdgeDistance();
	                int distanceThroughU = u.getNodeLength() + weight;
					if (distanceThroughU < v.getNodeLength()) {
					    NodeQueue.remove(v);
			
					    v.setNodeLength(distanceThroughU);
					    //System.out.println(v.getNodeLength());
					    v.previous = u;
					    //System.out.println(v.previous.getNodeName());
					    NodeQueue.add(v);
			
					}
	
	            }
	    }
    }//this function is used to compute the paths by the given argument..


    public Edge findMinimumEdge(Vector<Edge> edges, Vector<Node> tempnodes)
    {
		int i = 0 , j ;
		int min = Integer.MAX_VALUE ;
		
		for(i = 0 ; i < edges.size() ; i++)
		{
			if(edges.elementAt(i).getEdgeDistance() < min)
			{
				min = edges.elementAt(i).getEdgeDistance() ;
				//System.out.println(edges.elementAt(i).getEdgeDistance());
			}
		}
		
		for(j = 0 ; j < edges.size() ; j++)
		{
			if(min == edges.elementAt(j).getEdgeDistance())
			{
				return edges.elementAt(j);
			}
		}
	
		return null ;
	}

	public static Vector<Node> getShortestPathTo(Node target)
    {
        Vector<Node> path = new Vector<Node>();
        for (Node Node = target; Node != null; Node = Node.previous)
            path.addElement(Node);

        Collections.reverse(path);
        return path;
    }
	
}//end of the operation class

