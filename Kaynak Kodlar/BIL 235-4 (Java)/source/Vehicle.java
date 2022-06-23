import java.util.*;

public class Vehicle {
	
	public String VehicleName ;
	public Vector<State> StateList ;
	public Stack<Package> VehiclePackages ;
	public Vector <Task> TaskList ;
	public Vector <Node> VehiclePath ;
	
	public Vehicle(String vehicleName, Vector<State> stateList,
			Stack<Package> vehiclePackages, Vector<Task> taskList) {
		super();
		VehicleName = vehicleName;
		StateList = stateList;
		VehiclePackages = vehiclePackages;
		TaskList = taskList;
	}

	public String getVehicleName() {
		return VehicleName;
	}

	public void setVehicleName(String vehicleName) {
		VehicleName = vehicleName;
	}

	public Vector<State> getStateList() {
		return StateList;
	}

	public void setStateList(Vector<State> stateList) {
		StateList = stateList;
	}

	public Stack<Package> getVehiclePackages() {
		return VehiclePackages;
	}

	public void setVehiclePackages(Stack<Package> vehiclePackages) {
		VehiclePackages = vehiclePackages;
	}

	public Vector<Task> getTaskList() {
		return TaskList;
	}

	public void setTaskList(Vector<Task> taskList) {
		TaskList = taskList;
	}

}
