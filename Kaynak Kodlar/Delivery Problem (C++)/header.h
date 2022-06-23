#define inp "list.inp"
#define out "list.out"
#define max_city 10
#define max_string 20

typedef struct Cargo* Cargop;
typedef struct Cargo{
	int id;
	char *sender;
	char *recipient;
	char *content;
};
typedef struct Order* Orderp;
typedef struct Order{
	Cargop Cargoor;
	char **stationlist;
	Orderp next;
};
typedef struct Ship* Shipp;
typedef struct Ship{
	Cargop Cargoor;
	char **stationlist;
	char *laststation;
	Shipp next;
};
typedef struct Delivery* Deliveryp;
typedef struct Delivery{
	Cargop Cargoor;
	Shipp Ship;
	char *date;
};


void newCargo(FILE *,Orderp *);
void sendCargo(Orderp * orderlist,Shipp *,int );
void addShiplist(Shipp *,Orderp *,char **);
void deleteOrderlist(Orderp *);
void addDeliverylist(Shipp *,Deliveryp *);
void deleteShiplist(int, Shipp *);
void proceedCargo(int,Shipp *,Deliveryp *);
void deleteDelivery(int,Deliveryp *);
void list_order(Orderp *,FILE *);
void list_ship(Shipp *,FILE *);
void list_delivery(Deliveryp *,FILE *);
