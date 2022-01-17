/**
 * @file main.cpp
 * @author Kumara Ritvik Oruganti (okritvik@umd.edu)
 * @brief This program takes input from the user (number of boxes, parts per box and total number of parts to be filled) and calls respective functions to fill them according to the rules.
 * Added equal to zero condition in if statement of fill boxes functions after grading. Lost 1 test case for not adding that >=0 condition.
 * @version 0.1
 * @date 2021-09-27
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <array>

using std::cin;
using std::cout;

/**
 * @brief boxes struct is to store the number of Small, Medium, Large and Extra Large boxes.
 * 
 */
struct boxes{
	unsigned int s;
	unsigned int m;
	unsigned int l;
	unsigned int xl;
};

/**
 * @brief The parts_per_box struct is to store the number of parts that can be filled in a box of Small, Medium, Large and Extra Large.
 * 
 */
struct parts_per_box{
	unsigned int parts_s;
	unsigned int parts_m;
	unsigned int parts_l;
	unsigned int parts_xl;
};

/**
 * @brief This function prompts the user to enter total number of parts that has to be filled in the boxes. If it is negative/string it will reprompt the user to give a proper input. This function calls check_input_validity function.
 * 
 */

void take_total_parts_input();


/**
 * @brief This function prompts the user to enter the number of boxes available for Small, Medium, Large and Extra Large. If the input is not a valid input, it will reprompt the user to input proper values. If the data is valid, the data is stored in the object of box.
 * 
 * @param box reference of boxes structure.
 * 
 */

void take_number_of_boxes_input(boxes& box);

/**
 * @brief This function prompts the user to enter the parts per box of Small, Medium, Large and Extra Large boxes. This function calls check_parts_validity function which takes ppb as a parameter. If the input is not valid, it will reprompt the user to enter valid inputs. This function also calls the check_input_validity function to check the validity of the input given by ther user. If it is not valid, it will reassign the data with new inputs.
 * 
 * @param ppb reference of parts_per_box structure
 */

void take_parts_per_box(parts_per_box& ppb);

/**
 * @brief This function takes a string parameter and checks if the string is an integer or not. If it is an integer, it returns true, otherwise, false.
 * 
 * @param input constant std::string reference
 * @return true 
 * @return false 
 */

bool check_input_validity(const std::string& input);

/**
 * @brief This function checks if the parts entered by the user satisfies the conditions. If they are satisfied, it will return true.
 * 
 * @param ppb constant reference of parts_per_box structure (because we are not supposed to modify any data in this function)
 * @return true 
 * @return false 
 */
bool check_parts_validity(const parts_per_box& ppb);

/**
 * @brief Computes the number of XL boxes that can be filled with the total number of parts.
 * 
 * @param box constant boxes struct reference
 * @param ppb constant parts_per_box struct reference. 
 * @return unsigned int Number of Extra Large boxes that can be filled.
 */
unsigned int fill_xl_boxes(const boxes& box,const parts_per_box& ppb);


/**
 * @brief Computes the number of Large boxes that can be filled with the total number of parts.
 * 
 * @param box constant boxes struct reference
 * @param ppb constant parts_per_box struct reference. 
 * @return unsigned int Number of Large boxes that can be filled.
 */
unsigned int fill_l_boxes(const boxes& box,const parts_per_box& ppb);

/**
 * @brief Computes the number of Medium boxes that can be filled with the total number of parts.
 * 
 * @param box constant boxes struct reference
 * @param ppb constant parts_per_box struct reference. 
 * @return unsigned int Number of Medium boxes that can be filled.
 */
unsigned int fill_m_boxes(const boxes& box,const parts_per_box& ppb);

/**
 * @brief Computes the number of Small boxes that can be filled with the total number of parts.
 * 
 * @param box constant boxes struct reference
 * @param ppb constant parts_per_box struct reference. 
 * @return unsigned int Number of Small boxes that can be filled.
 */
unsigned int fill_s_boxes(const boxes& box,const parts_per_box& ppb);

/**
 * @brief The variable parts is static because it is shared across the multiple functions and the datatype is int because we have to check the condition for variable becoming negative.
 * 
 */
static int parts;

/**
 * @brief This main function calls the other functions to take inputs, compute, and displays the information required.
 * 
 * @return int 
 */
int main(){
	boxes box;
	parts_per_box ppb;

	take_total_parts_input(); //prompts the user to input the total number of parts.
	// cout << "The computed parts after checking is: " << parts << "\n";
	take_number_of_boxes_input(box); //prompts the user to input the number of boxes (Small, Medium, Large and Extra Large)
	// cout << "The number of boxes are: \n" << " s: " << box.s << "\n m: " << box.m << "\n l: " << box.l << "\n xl: " << box.xl << "\n";
	take_parts_per_box(ppb); //promps the user to input the number of parts that can be inserted in each of Small/Medium/Large/Extra Large boxes.
	// cout << "The number of parts per box are: \n" << " s: " << ppb.parts_s << "\n m: " << ppb.parts_m << "\n l: " << ppb.parts_l << "\n xl: " << ppb.parts_xl << "\n";
	cout << "\n";
	cout << "Boxes that can be built with "<<parts<<" pegs:\n";
	cout << "-------------------------------------------------\n";

	cout << "XL box (" << box.xl <<" * "<<ppb.parts_xl<<" max): "<< fill_xl_boxes(box,ppb) << " -- remaining parts: " << parts << "\n"; //Prints number of XL boxes that are filled
	cout << "L box (" << box.l <<" * "<<ppb.parts_l<<" max): "<< fill_l_boxes(box,ppb) << " -- remaining parts: " << parts << "\n"; // Prints number of L boxes that are filled
	cout << "M box (" << box.m <<" * "<<ppb.parts_m<<" max): "<< fill_m_boxes(box,ppb) << " -- remaining parts: " << parts << "\n"; // Prints number of M boxes that are filled
	cout << "S box (" << box.s <<" * "<<ppb.parts_s<<" max): "<< fill_s_boxes(box,ppb) << " -- remaining parts: " << parts << "\n"; // Prints number of S boxes that are filled
	cout << "Parts not in boxes: " << parts << "\n"; // Prints the left over parts. 
	return 0;
}


void take_total_parts_input(){
	std::string input;
	while(1){
		cin.clear(); //Clears the cin object
		cout << "How many parts in total? ";
		cin >> input;
		if(check_input_validity(input)){ //Checks if the input is valid or not
			parts = std::atoi(input.c_str()); //Converts the string to integer.
			if(parts>0){ //if the input is greater than zero, then comes out of loop
				break;
			}
		}
		else{ //Shows the error and asks the user to re-enter the input
			cout << "Error: Please enter a positive integer\n";
		}
	}

}

void take_number_of_boxes_input(boxes& box){

	std::array<std::string,4> sarr; //String array to take 4 inputs from the user
	while(1){
		cin.clear(); //clears the cin object
		cout << "How many boxes for S/M/L/XL? ";
		for(size_t i{}; i<sarr.size();i++){ //Prompts the user to input boxes for S/M/L/XL
			cin >> sarr.at(i);
		}
		if(check_input_validity(sarr[0]) && check_input_validity(sarr[1]) && check_input_validity(sarr[2]) && check_input_validity(sarr[3])){
			//Checks if all the four inputs are valid.
			box.s = std::atoi(sarr.at(0).c_str());
			box.m = std::atoi(sarr.at(1).c_str());
			box.l = std::atoi(sarr.at(2).c_str());
			box.xl = std::atoi(sarr.at(3).c_str());
			if(box.s>0 && box.m>0 && box.l>0 && box.xl>0){ //Checks if the inputs are greater than 0
				break;
			}
		}
		else{// Prompts the error and asks the user to input the values again.
			cout << "Error: Please enter positive integers\n";
		}
	}

}

void take_parts_per_box(parts_per_box& ppb){
	std::array<std::string,4> sarr;
	while(1){
		cin.clear();
		cout << "How many parts per box for S/M/L/XL? ";
		for(size_t i{}; i<sarr.size();i++){ //Takes the input from user and stores in the string array.
			cin >> sarr.at(i);
		}
		if(check_input_validity(sarr[0]) && check_input_validity(sarr[1]) && check_input_validity(sarr[2]) && check_input_validity(sarr[3])){
			//Checks if the inputs are valid integers.
			ppb.parts_s = std::atoi(sarr.at(0).c_str());
			ppb.parts_m = std::atoi(sarr.at(1).c_str());
			ppb.parts_l = std::atoi(sarr.at(2).c_str());
			ppb.parts_xl = std::atoi(sarr.at(3).c_str());
			if(check_parts_validity(ppb)){ //Calls the function to check if the entered inputs are in ascending order
				break;
			}
			else{ //Prompts the user to enter integers in ascending order.
				cout << "Error: Please enter positive integers in ascending order\n";
			}
		}
		else{ // Prompts the user to enter integers in ascending order.
			cout << "Error: Please enter positive integers in ascending order\n";
		}
	}
}

unsigned int fill_xl_boxes(const boxes& box,const parts_per_box& ppb){
	unsigned int counter=0; //Counter to count number of boxes filled.
	// cout<< "Parts in func "<<parts<<"\n";
	// cout<< "xl in func "<<box.xl<<" "<< ppb.parts_xl<<"\n";
	unsigned int ppxl = ppb.parts_xl;
	//Logic to compute the number of boxes that can be filled with the given condition.
	for(unsigned int i=1; i<=box.xl;i++){
		if(parts - (int)(i*ppxl) >= 0){
			counter++;
		}
		else{
			break;
		}
	}
	parts = parts - counter*ppxl;
	return counter;
}
unsigned int fill_l_boxes(const boxes& box,const parts_per_box& ppb){
	unsigned int counter=0; //Counter to count number of boxes filled.
	unsigned int ppl = ppb.parts_l;
	//Logic to compute the number of boxes that can be filled with the given condition.
	for(unsigned int i=1; i<=box.l;i++){
		if((parts-(int)(i*ppl)) >= 0){
			counter++;
		}
		else{
			break;
		}
	}
	parts = parts-counter*ppl;
	return counter;
}
unsigned int fill_m_boxes(const boxes& box,const parts_per_box& ppb){
	unsigned int counter=0; //Counter to count number of boxes filled.
	unsigned int ppm = ppb.parts_m;
	//Logic to compute the number of boxes that can be filled with the given condition.
	for(unsigned int i=1; i<=box.m;i++){
		if((parts-(int)(i*ppm)) >= 0){
			counter++;
		}
		else{
			break;
		}
	}
	parts = parts-counter*ppm;
	return counter;
}
unsigned int fill_s_boxes(const boxes& box,const parts_per_box& ppb){
	unsigned int counter=0; //Counter to count number of boxes filled.
	unsigned int pps = ppb.parts_s;
	//Logic to compute the number of boxes that can be filled with the given condition.
	for(unsigned int i=1; i<=box.m;i++){
		if((parts-(int)(i*pps)) >= 0){
			counter++;
		}
		else{
			break;
		}
	}
	parts = parts-counter*pps;
	return counter;
}

bool check_input_validity(const std::string& input){

	return input.find_first_not_of( "0123456789" ) == std::string::npos; //returns false if there is any character that is other than 0123456789.

}

bool check_parts_validity(const parts_per_box& ppb){
	if(ppb.parts_s>0 && ppb.parts_m >0 && ppb.parts_l>0 && ppb.parts_xl>0){
		if((ppb.parts_s<ppb.parts_m) && (ppb.parts_m<ppb.parts_l) && (ppb.parts_l<ppb.parts_xl)){ //checks if the parts per box data is in ascending order or not
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}