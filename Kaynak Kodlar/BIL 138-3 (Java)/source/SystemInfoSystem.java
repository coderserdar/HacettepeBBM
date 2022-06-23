import java.util.*;
import vehicle.*;
import person.*;
import trip.*;
import bbmlib.BbmReader;

public class SystemInfoSystem {
		private ArrayList Buslist=new ArrayList();
		private ArrayList Trainlist=new ArrayList();
		private ArrayList Passengerlist=new ArrayList();
		private ArrayList Machinistlist=new ArrayList();
		private ArrayList Driverlist=new ArrayList();
		private ArrayList Stationlist=new ArrayList();
		private ArrayList BusTriplist=new ArrayList();
		private ArrayList TrainTriplist=new ArrayList();

		
		
		public void addTrain(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String name=strReader.readString();
			String age=strReader.readString();
			String speed=strReader.readString();
			String type=strReader.readString();
			String capacityforbed=strReader.readString();
			String capacityforberth=strReader.readString();
			Train t=new Train(age,speed,name,type,capacityforbed,capacityforberth);
			Iterator it=Trainlist.iterator();
			while(it.hasNext()){
				if(it.equals(t.getName()))
					System.out.println("this train already exists");
				it.next();
			}
			Trainlist.add(t);
			}//addTrain
		
		public void addBus(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String plate=strReader.readString();
			String age=strReader.readString();
			String speed=strReader.readString();
			String capacity=strReader.readString();
			
			Bus b=new Bus(age,speed,plate,capacity);
			Iterator it=Buslist.iterator();
			while(it.hasNext()){
				if(it.equals(b.getPlate()))
					System.out.println("this bus already exists");
				it.next();
			}
			Buslist.add(b);
		}//addBus
		
		public void addPassenger(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String id=strReader.readString();
			String name=strReader.readString();
			String gender=strReader.readString();
			String age=strReader.readString();
			String phone=strReader.readString();
			
			Passenger pas=new Passenger(id,name,gender,age,phone);
			Iterator it=Buslist.iterator();
			while(it.hasNext()){
				if(it.equals(pas.getId()))
					System.out.println("this passenger already exists");
				it.next();
			}
			Passengerlist.add(pas);
			
		}//addPassenger
		
		public Passenger findPassenger(String number){
				for(int i=0;i<Passengerlist.size();i++){
					Passenger pas=(Passenger) Passengerlist.get(i);
					if(pas.getId().equals(number))
						return pas;
				}//for
				return null;
		}//findPassenger
		
		
		/*public void deletePassenger(String number){
			Passenger pas=findPassenger(number);
			Passengerlist.remove(pas);
			
		}//deletePassenger
		*/

		public void addMachinist(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String corpid=strReader.readString();
			String name=strReader.readString();
			String gender=strReader.readString();
			String age=strReader.readString();
			String years=strReader.readString();
			Machinist mac=new Machinist(corpid,name,gender,age,years);
			Iterator it=Machinistlist.iterator();
			while(it.hasNext()){
				if(it.equals(mac.getCorpid()))
					System.out.println("this machinist already exists");
				it.next();
			}
			Machinistlist.add(mac);
		}//addMachinist
		
		public void addDriver(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String corpid=strReader.readString();
			String name=strReader.readString();
			String gender=strReader.readString();
			String age=strReader.readString();
			String license=strReader.readString();
			String years=strReader.readString();
			Driver dri=new Driver(corpid,name,gender,age,license,years);
			Iterator it=Machinistlist.iterator();
			while(it.hasNext()){
				if(it.equals(dri.getCorpid()))
					System.out.println("this driver already exists");
				it.next();
			}
			Driverlist.add(dri);
		}//addDriver
		
		public void addBusTrip(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String tripno=strReader.readString();
			String depstaname=strReader.readString();
			String arrstaname=strReader.readString();
			String deptime=strReader.readString();
			String drivercorid=strReader.readString();
			String busplate=strReader.readString();
			BusTrip bustrip=new BusTrip(tripno,depstaname,arrstaname,deptime,drivercorid,busplate);
			Iterator it=BusTriplist.iterator();
			while(it.hasNext()){
				if(it.equals(bustrip.getTripno()))
					System.out.println("this bustrip already exists");
				it.next();
			}
			Driverlist.add(bustrip);
		
		}//addBusTrip
		
		public BusTrip findBusTrip(String number){
			for(int i=0;i<BusTriplist.size();i++){
				BusTrip bustrip=(BusTrip) BusTriplist.get(i);
				if(bustrip.getTripno().equals(number))
					return bustrip;
			}//for
			return null;
		}//findBusTrip
	
	
		/*public void deleteBusTrip(String number){
		BusTrip bustrip=findBusTrip(number);
		BusTriplist.remove(bustrip);
		
		}//deleteBusTrip
		*/
		
		public void addTrainTrip(String inputFileName){
			BbmReader fileReader = BbmReader.getFileReader(inputFileName);
			String line=fileReader.readLine();			
			BbmReader strReader = BbmReader.getStringReader(line);
			String tripno=strReader.readString();
			String depstaname=strReader.readString();
			String arrstaname=strReader.readString();
			String deptime=strReader.readString();
			String machinistcorid=strReader.readString();
			String trainname=strReader.readString();
			TrainTrip traintrip=new TrainTrip(tripno,depstaname,arrstaname,deptime,machinistcorid,trainname);
			Iterator it=BusTriplist.iterator();
			while(it.hasNext()){
				if(it.equals(traintrip.getTripno()))
					System.out.println("this traintrip already exists");
				it.next();
			}
			Driverlist.add(traintrip);
		
		}//addBusTrip
		
		public TrainTrip findTrainTrip(String number){
			for(int i=0;i<TrainTriplist.size();i++){
				TrainTrip traintrip=(TrainTrip) TrainTriplist.get(i);
				if(traintrip.getTripno().equals(number))
					return traintrip;
			}//for
			return null;
		}//findTrainTrip
	
	
		/*public void deleteTrainTrip(String number){
		TrainTrip traintrip=findTrainTrip(number);
		TrainTriplist.remove(traintrip);
		
		}//deleteTrainTrip
		*/
	
		//stationu okulda yap
		
		
		
		
}//class

