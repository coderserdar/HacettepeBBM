#include<stdio.h>
#include "header.h"
#include<stdlib.h>
#include<string.h>

void newCargo(FILE *input,Orderp *orderlist){
	Cargop cargo=(Cargop)malloc(sizeof(struct Cargo));
	cargo->sender=(char*)malloc(20);
	cargo->recipient=(char*)malloc(20);
	cargo->content=(char*)malloc(20);
	
	fscanf(input,"%d %s %s %s",&cargo->id,cargo->sender,cargo->recipient,cargo->content);
	
	Orderp newnode;
	newnode->Cargoor=cargo;
	newnode->stationlist=(char**)calloc(20,10);
	
	int i;
	for(i=0;i<max_city;i++){
		fscanf(input,"%s",newnode->stationlist[i]);
		if(newnode->stationlist[i]==NULL)
			break;
	}
	newnode->next=NULL;
	if(orderlist==NULL)
		*orderlist=newnode;
	else{
		Orderp temp;
		for(temp=*orderlist;temp->next!=NULL;temp=temp->next)
			temp->next=newnode;
	}
}

void sendCargo(Orderp *orderlist,Shipp *shiplist,int number){
	int i;
	for(i=0;i<number;i++){
		addShiplist(&(*shiplist),(*orderlist)->Cargoor,(*orderlist)->stationlist);
		deleteOrderlist(orderlist);
	}
}

void addShiplist(Shipp *shiplist,Orderp *orderlist,char **stationlist){
	int i;
	Shipp newnode;
	newnode->Cargoor=(Cargop)malloc(sizeof(struct Cargo));
	newnode->Cargoor->sender=(char*)malloc(20);
	newnode->Cargoor->recipient=(char*)malloc(20);
	newnode->Cargoor->content=(char*)malloc(20);
	newnode->stationlist=(char**)calloc(20,10);
	
	newnode->Cargoor->id=(*orderlist)->Cargoor->id;
	strcpy(newnode->Cargoor->sender,(*orderlist)->Cargoor->sender);
	strcpy(newnode->Cargoor->recipient,(*orderlist)->Cargoor->recipient);
	strcpy(newnode->Cargoor->content,(*orderlist)->Cargoor->content);
	
	for(i=0;i<max_city;i++){
		strcpy(newnode->stationlist[i],(*orderlist)->stationlist[i]);
		strcpy(newnode->laststation,newnode->stationlist[0]);
	}
	newnode->next=NULL;
	if(shiplist==NULL)
		*shiplist=newnode;
	else{
		Shipp temp;
		for(temp=*shiplist;temp->next!=NULL;temp=temp->next)
			temp->next=newnode;
	}
}

void deleteOrderlist(Orderp *orderlist){
	Orderp temp=*orderlist;
	if(*orderlist){
		*orderlist=(*orderlist)->next;
		free(temp);
	}
}

void proceedCargo(int number,Shipp *shiplist,Deliveryp *deliverylist){
	int i;
	for(i=0;i<number;i++){
		if(shiplist[i]->next)
			strcpy(shiplist[i]->laststation,*(shiplist[i]->stationlist+1));
		else{
			addDeliverylist(&shiplist[i],*deliverylist);
			deleteShiplist(i,*shiplist);
		}
	}
}

void addDeliverylist(Shipp *shippp,Deliveryp *deliverylist){
	Deliveryp temp=*deliverylist;
	if(temp==NULL)
		(*deliverylist)->Ship=shippp;
	else{
		while(temp->Ship->next)
			temp->Ship=temp->Ship->next;
		temp->Ship->next=shippp;
	}
}

void deleteShiplist(int i,Shipp *shiplist){
	shiplist[i-1]->next=shiplist[i+1];
	free(shiplist[i]);
}

void deleteDelivery(int number,Deliveryp *deliverylist){
	int i;
	Deliveryp temp=deliverylist[0];
	for(i=1;i<number&&temp;i++){
		free(temp);
		temp=deliverylist[i];
	}
}

void list_order(Orderp *orderlist,FILE *output){
	Orderp temp=*orderlist;
	while(temp){
		fprintf(output,"%d %s %s %s",&temp->Cargoor->id,temp->Cargoor->sender,temp->Cargoor->recipient,temp->Cargoor->content);
		char **p=temp->stationlist;
		while(p){
			fprintf(output,"%s",p);
			p++;
		}
		temp=temp->next;
	}
}

void list_ship(Shipp *shiplist,FILE *output){
	Shipp temp=*shiplist;
	while(temp){
		fprintf(output,"%d %s %s %s %s",&temp->Cargoor->id,temp->Cargoor->sender,temp->Cargoor->recipient,temp->Cargoor->content,temp->laststation);
		char **p=temp->stationlist;
		while(p){
			fprintf(output,"%s",p);
			p++;
		}
		temp=temp->next;
	}
}

void list_delivery(Deliveryp *deliverylist,FILE *output){
	Deliveryp temp=*deliverylist;
	while(temp){
		fprintf(output,"%d %s %s %s %s %s",&(temp->Cargoor->id),temp->Cargoor->sender,temp->Cargoor->recipient,temp->Cargoor->content,temp->Ship->laststation,temp->date);
		char **p=temp->Ship->stationlist;
		while(p){
			fprintf(output,"%s",p);
			p++;
		}
		temp->Ship=temp->Ship->next;
	}
}


int main(void){
	FILE *input;
	FILE *output;
	Orderp olist;
	Shipp  slist;
	Deliveryp dlist;
	
	if(!(input=fopen(inp,"r"))){
		printf("input file cant open");
		return -1;
	}
	else if(!(output=fopen(out,"w"))){
		printf("output file cant open");
		return 0;
	}
	
	char *test;
	fscanf(input,"%s",test);
	while(!feof(input)){
		if(strcmp(test,"NEW_CARGO"))
			newCargo(input,&olist);
		else if(strcmp(test,"SEND_CARGO")){
			int number;
			fscanf(input,"%d",&number);
			sendCargo(&olist,&slist,number);
		}
		else if(strcmp(test,"PROCEED_CARGO")){	
			int number;
			fscanf(input,"%d",&number);
			proceedCargo(number,&slist,&dlist);
		}
		else if(strcmp(test,"DELETE_DELIVERY")){
			int number;
			fscanf(input,"%d",&number);
			deleteDelivery(number,&dlist);
		}
		else if(strcmp(test,"LIST_ORDER"))
			list_order(&olist,output);
		
		else if(strcmp(test,"LIST_SHIP"))
			list_ship(&slist,output);
		
		else if(strcmp(test,"LIST_DELIVERY"))
			list_delivery(&dlist,output);
		
	}
	fclose(input);
	fclose(output);
	return 0;
}
