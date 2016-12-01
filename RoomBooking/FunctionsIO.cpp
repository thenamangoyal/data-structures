#include "FunctionsIO.h"
using namespace std;

void print_operations(){
	cout<<"Please select the operation you wish to perform"<<endl;
	cout<<"1. Add room, lab, or lecture hall to the system"<<endl;
	cout<<"2. Remove a room, lab, or lecture hall from the system"<<endl;
	cout<<"3. Book a room, lab, or lecture hall"<<endl;
	cout<<"4. Minimum number of rooms required to accommodate given number of persons"<<endl;
	cout<<"5. Find the smallest lecture hall that can accommodate the given number of students"<<endl;
	cout<<"6. Find the lab with least equipment density and add new equipment"<<endl;
	cout<<"7. Find a room nearest to the given location"<<endl;
	cout<<"8. Book or Unbook a room, lab, and lecture hall"<<endl;
	cout<<"9. Print details of the given room, lab, and lecture hall"<<endl;
	cout<<"10. Save and Exit"<<endl;
	cout<<"0. Reset current state"<<endl;
}

void read_input(vector<room*>& room_list, vector<lab*>& lab_list, vector<lec*>& lec_list){


int function_to_call;
cout<<"=============================="<<endl;
cout<<"Welcome to Room Booking System"<<endl;
cout<<"=============================="<<endl;
print_operations();


while (cin>>function_to_call && function_to_call !=10){
	cout<<endl<<"Performing operation "<<function_to_call<<"."<<endl;
	switch (function_to_call) {
		
		case 0: {
			reset_state(true);
			for(int i_0=0; i_0 < room_list.size(); i_0++){
				delete room_list[i_0];
			}
			room_list.clear();

			for(int j_0=0; j_0 < lab_list.size(); j_0++){
				delete lab_list[j_0];
			}
			lab_list.clear();

			for(int k_0=0; k_0 < lec_list.size(); k_0++){
				delete lec_list[k_0];
			}
			lec_list.clear();

			read_state(room_list, lab_list, lec_list);
			cout<<"System Reset Successfull."<<endl;
			cout<<"Operation 0 Completed."<<endl<<endl;
			break;
		}
		case 1:
		{
		int i_type_1;
		cout<<"Select the type: Room/Lab/Lecture Hall"<<endl;
		cout<<"0: Room\t 1: Lab\t 2: Lecture Hall"<<endl;
		cin>>i_type_1;
		cout<<"Enter the name:"<<endl;
		string i_name_1;
		cin>>i_name_1;
		cout<<"Enter the area:"<<endl;;
 		double i_area;
 		cin>>i_area;
 		cout<<"Enter the no of doors:"<<endl;
 		int i_doors;
 		cin>>i_doors;
 		cout<<"Enter the coordinate x:"<<endl;
 		int i_x_1;
 		cin>>i_x_1;
 		cout<<"Enter the coordinate y:"<<endl;
 		int i_y_1;
 		cin>>i_y_1;
	 	if (i_type_1==0){
	 		room* i_room = new room(i_name_1, i_area, i_doors, i_x_1, i_y_1);
	 		room_list.push_back(i_room);
	 		cout<<"Following Room was added successfully."<<endl;
	 		cout<<*(room_list.back());

	 	}
	 	else if (i_type_1==1){
	 		cout<<"Enter the number of computers:"<<endl;
	 		int i_nocomp;
	 		cin>>i_nocomp;
	 		lab* i_lab = new lab(i_name_1, i_area, i_doors, i_x_1, i_y_1, i_nocomp);
	 		lab_list.push_back(i_lab);
	 		cout<<"Following Lab was added successfully."<<endl;
	 		cout<<*(lab_list.back());
	 	}
	 	else if (i_type_1==2){
	 		cout<<"Enter the number of chairs:"<<endl;
	 		int i_nochairs;
	 		cin>>i_nochairs;
	 		lec* i_lec = new lec(i_name_1, i_area, i_doors, i_x_1, i_y_1, i_nochairs);
	 		lec_list.push_back(i_lec);
	 		cout<<"Following Lecture Hall was added successfully."<<endl;
	 		cout<<*(lec_list.back());
	 	}
	 	else {
	 		cout<<"Invalid argument type for addition."<<endl;
	 	}
	 	cout<<"Operation 1 Completed."<<endl<<endl;
		break;
		}


		case 2:
		{
		cout<<"Select the type: Room/Lab/Lecture Hall"<<endl;
		cout<<"0: Room\t 1: Lab\t 2: Lecture Hall"<<endl;
		int i_type_2;
		cin>>i_type_2;
		cout<<"Enter the name:"<<endl;
		string i_name_2;
 		cin>>i_name_2;
	 	if (i_type_2==0){
	 		int to_delete_21 = search_list<room*>(room_list,i_name_2);
	 		if (to_delete_21>=0){
	 			cout<<"Deleting "<<(room_list[to_delete_21]->getname())<<endl;
	 			delete_list<room*>(room_list, to_delete_21);

	 		}
	 		else{
	 			cout<<"No Room found to delete."<<endl;
	 		}
	 	}
	 	else if (i_type_2==1){
	 		int to_delete_22 = search_list<lab*>(lab_list,i_name_2);
	 		if (to_delete_22>=0){
	 			cout<<"Deleting "<<(lab_list[to_delete_22]->getname())<<endl;
	 			delete_list<lab*>(lab_list, to_delete_22);
	 		}
	 		else{
	 			cout<<"No Lab found to delete."<<endl;
	 		}
	 	}
	 	else if (i_type_2==2){
	 		int to_delete_23 = search_list<lec*>(lec_list,i_name_2);
	 		if (to_delete_23>=0){
	 			cout<<"Deleting "<<(lec_list[to_delete_23]->getname())<<endl;
	 			delete_list<lec*>(lec_list, to_delete_23);
	 		}
	 		else{
	 			cout<<"No Lecture Hall found to delete."<<endl;
	 		}
	 	}
	 	else {
	 		cout<<"Invalid argument type for deletion."<<endl;
	 	}
	 	cout<<"Operation 2 Completed."<<endl<<endl;
		break;
		}

		case 3:
		{
		cout<<"Select the type: Room/Lab/Lecture Hall"<<endl;
		cout<<"0: Room\t 1: Lab\t 2: Lecture Hall"<<endl;
		int i_type_3;
		cin>>i_type_3;
		cout<<"Enter the name:"<<endl;
		string i_name_3;
 		cin>>i_name_3;
 		
 		if (i_type_3==0){
	 		int to_book_31 = search_list<room*>(room_list,i_name_3);
	 		if (to_book_31>=0){
	 			if (room_list[to_book_31]->getbooking()){
	 				cout<<"Unable to book Room. "<<(room_list[to_book_31]->getname())<<" is already booked." <<endl;
	 			}
	 			else {
	 				room_list[to_book_31]->book();
	 				cout<<(room_list[to_book_31]->getname())<<" is booked successfully." <<endl;
	 			}
	 		}
	 		else{
	 			cout<<"No Room found to book."<<endl;
	 		}
	 	}
	 	else if (i_type_3==1){
	 		int to_book_32 = search_list<lab*>(lab_list,i_name_3);
	 		if (to_book_32>=0){
	 			if (lab_list[to_book_32]->getbooking()){
	 				cout<<"Unable to book Lab. "<<(lab_list[to_book_32]->getname())<<" is already booked." <<endl;
	 			}
	 			else {
	 				lab_list[to_book_32]->book();
	 				cout<<(lab_list[to_book_32]->getname())<<" is booked successfully." <<endl;
	 			}
	 		}
	 		else{
	 			cout<<"No Lab found to book."<<endl;
	 		}
	 	}
	 	else if (i_type_3==2){
	 		int to_book_33 = search_list<lec*>(lec_list,i_name_3);
	 		if (to_book_33>=0){
	 			if (lec_list[to_book_33]->getbooking()){
	 				cout<<"Unable to book Lecture Hall. "<<(lec_list[to_book_33]->getname())<<" is already booked." <<endl;

	 			}
	 			else {
	 				lec_list[to_book_33]->book();
	 				cout<<(lec_list[to_book_33]->getname())<<" is booked successfully." <<endl;
	 			}
	 		}
	 		else{
	 			cout<<"No Lecture Hall found to book."<<endl;
	 		}
	 	}
	 	else {
	 		cout<<"Invalid argument type for booking."<<endl;
	 	}
		
	 	cout<<"Operation 3 Completed."<<endl<<endl;
		break;
	}

		case 4:
		{
		cout<<"Enter the number of persons to accommodate"<<endl;
		int i_no_person;
		cin>>i_no_person;
		cout<<"Select whether to search only from available Rooms"<<endl;
		cout<<"1: Yes\t 0:No"<<endl;
		int i_only_available_int;
		cin>>i_only_available_int;
		bool i_only_available_bool = ((i_only_available_int == 0) ? false: true);
		vector<int> rooms_required = min_room_given_person (room_list, i_no_person, i_only_available_bool);
		if (rooms_required.empty()){
			cout<<"Insufficient rooms to accommodate "<<i_no_person<<" persons."<<endl;
		}
		else {
		cout<<"Required no of rooms to accommodate "<<i_no_person<<" are: "<<rooms_required.size()<<endl;
		cout<<"The details of required rooms are as follows:"<<endl;
		for (int i=0; i<rooms_required.size();i++){
			cout<<*room_list[(rooms_required[i])];
		}
	}
		
		cout<<"Operation 4 Completed."<<endl<<endl;
		break;
	}

		case 5:
		{
		cout<<"Enter the number of students to accommodate"<<endl;
		int i_no_student;
		cin>>i_no_student;
		cout<<"Select whether to search only from available Lecture Halls"<<endl;
		cout<<"1: Yes\t 0:No"<<endl;
		int i_only_available_int;
		cin>>i_only_available_int;
		bool i_only_available_bool = ((i_only_available_int == 0) ? false: true);
		int lec_hall = smallest_lec_given_student (lec_list, i_no_student, i_only_available_bool);
		if (lec_hall >= 0){
		cout<<"Found Lecture Hall "<<(lec_list[lec_hall]->getname())<<" to accommodate "<<i_no_student<<" students. The details are as follows:"<<endl;
		cout<<*lec_list[lec_hall];
		}
		else {

		cout<<"No Lecture Hall found to accommodate "<<i_no_student<<" students."<<endl;
	}
		
		cout<<"Operation 5 Completed."<<endl<<endl;
		break;
	}
		
		case 6:
		{

		
		int least_lab = least_equip_dens_lab(lab_list);

		if (least_lab>= 0){
			cout<<"Least equipment Lab is: "<<(lab_list[least_lab]->getname())<<" with "<<(lab_list[least_lab]->getnocomp()) <<" computers."<<endl;
			cout<<"Select whether to add more equipments to "<<(lab_list[least_lab]->getname())<<endl;
			cout<<"1: Yes\t 0: No"<<endl;
			int whether_to_add_equip;
			cin>>whether_to_add_equip;
			if (whether_to_add_equip == 1){
			cout<<"Enter the number of equiments to add."<<endl;
			int i_equip_to_add;
			cin>>i_equip_to_add;
			int total_equip;
			total_equip = i_equip_to_add + lab_list[least_lab]->getnocomp();
			lab_list[least_lab]->setnocomp(total_equip);
			cout<<"Added "<<i_equip_to_add<<" equipments to lab. "<<(lab_list[least_lab]->getname())<<" now contains "<<(lab_list[least_lab]->getnocomp())<<" computers."<<endl;
			}
			
		}
		else {
			cout<<"No Lab found."<<endl;
		}
		
		cout<<"Operation 6 Completed."<<endl<<endl;
		break;
	}

		case 7:
		{
		cout<<"Enter the coordinate x"<<endl;
		int i_x_7;
		cin>>i_x_7;		
		cout<<"Enter the coordinate y"<<endl;
		int i_y_7;
		cin>>i_y_7;
		int nearest_room = find_nearest_room<room*>(room_list,i_x_7,i_y_7);
		if (nearest_room >= 0) {
			cout<<"The nearest room to x: "<<i_x_7<<" and y: "<<i_y_7<<" is "<<(room_list[nearest_room]->getname())<<endl;
			cout<<*(room_list[nearest_room]);
		}
		else {
			cout<<"No Room found near to "<<i_x_7<<" "<<i_y_7<<endl;
		}
		
		cout<<"Operation 7 Completed."<<endl<<endl;
		break;
	}

		case 8:
		{		
		cout<<"Select whether to book or unbook"<<endl;
		cout<<"1: Book\t 2: Unbook"<<endl;
		int to_book_or_unbook;
		cin>>to_book_or_unbook;
		cout<<"Select the type: Room/Lab/Lecture Hall"<<endl;
		cout<<"0: Room\t 1: Lab\t 2: Lecture Hall"<<endl;
		int i_type_8;
		cin>>i_type_8;
		cout<<"Enter the name:"<<endl;
		string i_name_8;
 		cin>>i_name_8;
 		if (to_book_or_unbook == 1) {
	 		if (i_type_8==0){
		 		int to_book_81 = search_list<room*>(room_list,i_name_8);
		 		if (to_book_81>=0){
		 			if (room_list[to_book_81]->getbooking()){
		 				cout<<"Unable to book Room. "<<(room_list[to_book_81]->getname())<<" is already booked."<<endl;
		 			}
		 			else {
		 				room_list[to_book_81]->book();
		 				cout<<(room_list[to_book_81]->getname())<<" is booked successfully." <<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find Room to book."<<endl;
		 		}
		 	}
		 	else if (i_type_8==1){
		 		int to_book_82 = search_list<lab*>(lab_list,i_name_8);
		 		if (to_book_82>=0){
		 			if (lab_list[to_book_82]->getbooking()){
		 				cout<<"Unable to book Lab. "<< (lab_list[to_book_82]->getname())<<" is already booked."<<endl;
		 			}
		 			else {
		 				lab_list[to_book_82]->book();
		 				cout<<(lab_list[to_book_82]->getname())<<" is booked successfully." <<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find lab to book"<<endl;
		 		}
		 	}
		 	else if (i_type_8==2){
		 		int to_book_83 = search_list<lec*>(lec_list,i_name_8);
		 		if (to_book_83>=0){
		 			if (lec_list[to_book_83]->getbooking()){
		 				cout<<"Unable to book Lecture Hall. "<<(lec_list[to_book_83]->getname())<<" is already booked."<<endl;
		 			}
		 			else {
		 				lec_list[to_book_83]->book();
		 				cout<<(lec_list[to_book_83]->getname())<<" is booked successfully." <<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find Lecture Hall to book"<<endl;
		 		}
		 	}
		 	else {
		 		cout<<"Invalid argument type for booking."<<endl;
		 	}
		 }

		 else if (to_book_or_unbook == 2) {
	 		if (i_type_8==0){
		 		int to_unbook_81 = search_list<room*>(room_list,i_name_8);
		 		if (to_unbook_81>=0){
		 			if (room_list[to_unbook_81]->getbooking()){
		 				room_list[to_unbook_81]->unbook();
		 				cout<<(room_list[to_unbook_81]->getname())<<" is unbooked successfully." <<endl;
		 				
		 			}
		 			else {
		 				cout<<"Unable to unbook Room. "<<(room_list[to_unbook_81]->getname()) <<" is already unbooked."<<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find Room to unbook."<<endl;
		 		}
		 	}
		 	else if (i_type_8==1){
		 		int to_unbook_82 = search_list<lab*>(lab_list,i_name_8);
		 		if (to_unbook_82>=0){
		 			if (lab_list[to_unbook_82]->getbooking()){
		 				lab_list[to_unbook_82]->unbook();
		 				cout<<(lab_list[to_unbook_82]->getname())<<" is unbooked successfully." <<endl;
		 			}
		 			else {
		 				cout<<"Unable to unbook Lab. "<<(lab_list[to_unbook_82]->getname())<<" is already unbooked."<<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find Lab to unbook."<<endl;
		 		}
		 	}
		 	else if (i_type_8==2){
		 		int to_unbook_83 = search_list<lec*>(lec_list,i_name_8);
		 		if (to_unbook_83>=0){
		 			if (lec_list[to_unbook_83]->getbooking()){
		 				lec_list[to_unbook_83]->unbook();
		 				cout<<(lec_list[to_unbook_83]->getname())<<" is unbooked successfully." <<endl;
		 			}
		 			else {
		 				cout<<"Unable to unbook Lecture Hall. "<<(lec_list[to_unbook_83]->getname())<<" is already unbooked."<<endl;
		 			}
		 		}
		 		else{
		 			cout<<"Unable to find Lecture Hall to book."<<endl;
		 		}
		 	}
		 	else {
		 		cout<<"Invalid argument type for unbooking."<<endl;
		 	}
		 }
		
		cout<<"Operation 8 Completed."<<endl<<endl;
		break;
	}

		case 9:
		{
		cout<<"Select the type: Room/Lab/Lecture Hall"<<endl;
		cout<<"0: Room\t 1: Lab\t 2: Lecture Hall"<<endl;
		int i_type_9;
		cin>>i_type_9;
		cout<<"Enter the name:"<<endl;
		string i_name_9;
 		cin>>i_name_9;
	 	if (i_type_9==0){
	 		int to_print = search_list<room*>(room_list,i_name_9);
	 		if (to_print >=0){
	 			room_list[to_print]->print();
	 		}
	 		else{
	 			cout<<"No Room found to print."<<endl;
	 		}
	 	}
	 	else if (i_type_9==1){
	 		int to_print = search_list<lab*>(lab_list,i_name_9);
	 		if (to_print>=0){
	 			lab_list[to_print]->print();
	 		}
	 		else{
	 			cout<<"No Lab found to print."<<endl;
	 		}
	 	}
	 	else if (i_type_9==2){
	 		int to_print = search_list<lec*>(lec_list,i_name_9);
	 		if (to_print>=0){
	 			lec_list[to_print]->print();
	 		}
	 		else{
	 			cout<<"No Lecture Hall found to print."<<endl;
	 		}
	 	}
	 	else {
	 		cout<<"Invalid argument type for printing details."<<endl;
	 	}
	 	cout<<"Operation 9 Completed."<<endl<<endl;
		break;
		}



		default:{
			cout<<"Invalid opration."<<endl<<endl;
		break;
		}
		
	}
	
	//cout<<"Press Enter to continue.."<<endl;
	//cin.ignore();
	//string con_temp;
	//getline(cin,con_temp);
	
	print_operations();
	
}
save_state(room_list, lab_list, lec_list);
cout<<"Saved successfully and exiting."<<endl;

}