#include <iostream> 
#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8
#include "table.hpp"
#include <fstream>
#include <chrono>
#include <ctime>
            
using namespace std;

float get_tax_amt(float amt, float rate){
    return amt * (rate/100);
}

void input_err(){
    cout << "invalid input value please restart programm and enter correct details" << endl;
    exit(42);
}

int main() 
{   
    time_t curr_time;
	tm * curr_tm;
	char datetime_string[100];
	
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	
	strftime(datetime_string, 50, "%B %d %T %Y", curr_tm);


    cout << "\n\n\n";
    cout << "       ******************** BILLING MANAGEMENT SYSTEM ********************        " << endl;
    cout << "********************* [ CREATED BY BHAWANI SHANKAR MAHAWAR ] *********************" << endl;
    cout << "****************************** " << datetime_string << " ******************************" << endl << endl << endl;
    
    TextTable t( '-', '|', '+' );
    TextTable t1( '-', '|', '+' );
    TextTable t2( '-', '|', '+' );

    string customer_name, billing_address, customer_gstin, item_name, last_row;

    float quantity=0.0, price=0.0, sgst_rate=0.0, cgst_rate=0.0, igst_rate=0.0, actual_amt=0.0, 
        sgst_amt=0.0, cgst_amt=0.0, igst_amt=0.0, total_amt=0.0, total_tax_rate=0.0, total_tax_amt=0.0;

    int last_row_value=0;

    cout << "Enter customer name: "; 
    getline(cin, customer_name);
    cout << "Enter billing address: "; 
    getline(cin, billing_address);
    cout << "Enter customer gstin: "; 
    getline(cin, customer_gstin);
    cout << "Enter item name: "; 
    getline(cin, item_name);
    cout << "Enter quantity: "; 
    cin >> quantity;
    if(cin.fail()){
        input_err();
    }
    cout << "Enter price: "; 
    cin >> price;
    if(cin.fail()){
        input_err();
    }
    cout << "Enter sgst rate: "; 
    cin >> sgst_rate;
    if(cin.fail()){
        input_err();
    }
    cout << "Enter cgst rate: "; 
    cin >> cgst_rate;
    if(cin.fail()){
        input_err();
    }
    cout << "Enter igst rate: "; 
    cin >> igst_rate;
    if(cin.fail()){
        input_err();
    }

    actual_amt = price * quantity;
    total_tax_rate = sgst_rate + cgst_rate + igst_rate;
    total_tax_amt = get_tax_amt(actual_amt, total_tax_rate);
    total_amt = actual_amt + total_tax_amt;
    sgst_amt = get_tax_amt(actual_amt, sgst_rate);
    cgst_amt = get_tax_amt(actual_amt, cgst_rate);
    igst_amt = get_tax_amt(actual_amt, igst_rate);

    // float to string convert
    string quantity_str =  to_string(quantity);
    string price_str =  to_string(price);
    string actual_amt_str =  to_string(actual_amt);
    string sgst_rate_str =  to_string(sgst_rate);
    string sgst_amt_str =  to_string(sgst_amt);
    string cgst_rate_str =  to_string(cgst_rate);
    string cgst_amt_str =  to_string(cgst_amt);
    string igst_rate_str =  to_string(igst_rate);
    string igst_amt_str =  to_string(igst_amt);
    string total_tax_rate_str =  to_string(total_tax_rate);
    string total_tax_amt_str =  to_string(total_tax_amt);
    string total_amt_str =  to_string(total_amt);

    t.add( "Customer name" );
    t.add( "Billing address" );
    t.add( "Customer gstin" );
    t.add( "Item name" );
    t.endOfRow();

    t.add( customer_name );
    t.add( billing_address );
    t.add( customer_gstin );
    t.add( item_name );
    t.endOfRow();

    // t.setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << t;

    t1.add( "Quantity" );
    t1.add( "Price" );
    t1.add( "Actual amount" );
    t1.endOfRow();

    t1.add( quantity_str );
    t1.add( price_str );
    t1.add( actual_amt_str );
    t1.endOfRow();

    // t1.setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << t1;

    t2.add( "SGST rate" );
    t2.add( "SGST amt" );
    t2.add( "CGST rate" );
    t2.add( "CGST amt" );
    t2.add( "IGST rate" );
    t2.add( "IGST amt" );
    t2.add( "Total tax rate" );
    t2.add( "Total tax amount" );
    t2.add( "Total amount" );
    t2.endOfRow();

    t2.add( sgst_rate_str );
    t2.add( sgst_amt_str );
    t2.add( cgst_rate_str );
    t2.add( cgst_amt_str );
    t2.add( igst_rate_str );
    t2.add( igst_amt_str );
    t2.add( total_tax_rate_str );
    t2.add( total_tax_amt_str );
    t2.add( total_amt_str );
    t2.endOfRow();

    cout << t2;

    // asking for save bill
    char ask;
    cout << "Do you want to change save this bill. y/n ";
    cin >> ask;

    if(ask == 'y'){
        // getting last row
        ifstream last_row_file_read("last_row");
        last_row_file_read >> last_row;
        last_row_file_read.close();

        // convert last row into integer
        last_row_value = atoi(last_row.c_str());

        // Create an output filestream object
        ofstream myFile("bills.csv", ios_base::app);

        if(last_row_value==0){
            // send header to the stream
            myFile << "Invoice no.,Customer name,Billing address,Customer GSTIN,Item name,Quantity,Price,Actual amount,SGST rate,SGST amount,CGST rate,CGST amount,IGST rate,IGST amount,Total tax rate, Total tax amount,Total amount,Date-time\n";
        }

        // Send data to the stream`
        myFile << ++last_row_value << "," << customer_name << "," << billing_address << "," << customer_gstin << "," << item_name << ","
            << quantity << "," << price << "," << actual_amt << "," << sgst_rate << "," << sgst_amt << ","
            << cgst_rate << "," << cgst_amt << "," << igst_rate << "," << igst_amt << "," << total_tax_rate << ","
            << total_tax_amt << "," << total_amt << "," << datetime_string << endl;
        
        // wiritng last row value
        ofstream last_row_file_write("last_row");
        last_row_file_write << last_row_value;
        last_row_file_write.close();
        
        // Close the file
        myFile.close();

        cout << "Bill saved successfully......\n";
    }else{
        cout << "Process completed......\n";
    }

    return 0;
} 
