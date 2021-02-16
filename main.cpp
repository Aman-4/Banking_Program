//
// Author: Aman Anand, UIC, Spring 2021
// Assignment: Project 2 (Part 1)
//

//g++ -g -Wall main.cpp -o main

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//
// checkArrays function
//
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more
// extensive checks to make sure the data was input correctly.
//
// NOTE: this function is required as part of assignment.
//

void checkArrays(int accounts[], double balances[], int N)
    {
       cout << std::fixed; // setup for output of the form .xx
       cout << std::setprecision(2);

       cout << "** Checking arrays..." << endl;
       cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
       cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
    }

//
// search function 
//
// Given an array of N accounts in ascending order, searches for
// the account that matches "acct". If found, the index of that
// account is returned; if not found -1 is returned.
//

int search(int accounts[], int N, int acct)
    {
    
        for (int i = 0; i < N; ++i)
        {

            if (acct == accounts[i])
            {
                return i;
            }
         }
        return -1;  // not found
    }

//
// maxBalance function 
//
// Given an array of N balances, searches for the highest balances
// and returns the index of this balance. If there's a tie, the
// first (smaller) index is returned. Assumes N > 0.
//

int maxBalance(double balances[], int N)
{
   double max;
   max = balances[0];
   int i;
   int max_index = 0;
   for (i = 1; i < N; ++i)
   {
      if (balances[i] > max)
      {
         max_index = i;
         max = balances[i];
      }
   }
   return max_index;
}

int main()
{    
    
   // Step 1 - defining the file name and opening the file 
   string filename;
   cout << "** Welcome to UIC Bank v2.0 **" << endl;
   cout << "Enter bank filename> ";
   cin >> filename;
   cout << endl;
   
   ifstream infile;
   infile.open(filename);
   
   if (!infile.good()) // checking if the file is valid, if not an error message will be outputted.
   {
      cout << "** Inputting account data..." << endl;
      cout << "**Error: unable to open input file '" << filename << "'" << endl;
      return 0;  
   } 
    
   int num_array;
   cout << "** Inputting account data..." << endl;
//    cout << "** Checking arrays..." << endl;
   infile >> num_array;
   
   int *acc_array = new int[num_array];
   double *balance_array = new double[num_array];
   
   for (int i = 0; i < num_array; ++i)
   {
       infile >> acc_array[i];
       infile >> balance_array[i];
   }
// loop N times and store input directly from the file into the array
   infile.close();
    
   checkArrays(acc_array, balance_array, num_array);
    
   string command;
   cout << "** Processing user commands..." << endl;
   
    // when "x" is pressed it exits the loop 
   while (command != "x")
   {
       cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
       cin >> command;
       // depositing
       if (command == "+")
       {
           int number;
           double amount;
           cin >> number;
           cin >> amount;
           
           int index = search(acc_array, num_array, number);
           // use same index to add values in balances array
           if (index != -1)
           {
               balance_array[index] += amount;
               cout << "Account " << acc_array[index] << ": balance $" << balance_array[index] << endl; 
           }
           
           else
           {
               cout << "** Invalid account, transaction ignored" << endl;
           }
       }
       
       //withdrawing
       else if (command == "-")
       {    
           int number;
           double amount;
           cin >> number;
           cin >> amount;
           int index = search(acc_array, num_array, number);

           // use same index to add values in balances array
           if (index != -1)
           {
               balance_array[index] -= amount;
               cout << "Account " << acc_array[index] << ": balance $" << balance_array[index] << endl; 
           }
           
           else
           {
               cout << "** Invalid account, transaction ignored" << endl;
           }
       }

       
       else if (command == "?")
       {   
           int number;
           cin >> number;
           int index = search(acc_array, num_array, number);
           
           if (index != -1)
           {
               cout << "Account " << acc_array[index] << ": balance $" << balance_array[index] << endl; 
           }
           
           else
           {
               cout << "** Invalid account, transaction ignored" << endl;
           }
       }
       
       else if (command == "^")
       {
           // call maxbalance and then use the index returned to do what you're supposed to do
           int max_value;
           max_value = maxBalance(balance_array, num_array);
           cout << "Account " << acc_array[max_value] << ": balance $" << balance_array[max_value] << endl; 
       }
       
       else if (command == "*")
       {
           int low;
           int high;
           cin >> low;
           cin >> high;
            
           for (int i = 0; i < num_array; ++i)
           {
               if (low <= acc_array[i] && acc_array[i] <= high)
               {
                   cout << "Account " << acc_array[i] << ": balance $" << balance_array[i] << endl;
               }
           }
       
        }
       
        // List of all accounts with negative balances
        else if (command == "<")
        {  
            
            for (int i = 0; i < num_array; ++i)
            {
                if (balance_array[i] < 0)
                {
                    cout << "Account " << acc_array[i] << ": balance $" << balance_array[i] << endl;
                }
            }
        }
       
        // List of all accounts with positive balances
        else if (command == "$")
        {  
            double sum;
            sum = 0.0;
            for (int i = 0; i < num_array; ++i)
            {
                if (balance_array[i] > 0)
                {
                    sum += balance_array[i];
                }
            }
            
            cout << "Total deposits: $" << sum << endl;
        }
       
        else if (command == "add")
        {
            //Adding accounts
            int acc_num = acc_array[num_array-1] + 1;
            // pointers to new variable 
            int *temp_acc;
            temp_acc = new int[num_array + 1];
            double *temp_bal;
            temp_bal = new double[num_array + 1];
            for (int i = 0; i < num_array; ++i)
            {
                // copying the elements of the old arrays to the new ones 
                temp_acc[i] = acc_array[i];  
                temp_bal[i] = balance_array[i];
            }   
                // fill in last index of the new arrays (maxvalue + 1)
                temp_acc[num_array] = (acc_num);
                temp_bal[num_array] = 0.0;
                
                delete[] acc_array;
                delete[] balance_array;
                
                acc_array = temp_acc;
                balance_array = temp_bal;
                num_array = num_array + 1;
                
                cout << "Added account " << temp_acc[num_array-1] << ": balance $" << temp_bal[num_array-1] << endl;
        }
           
        else if (command == "del")
        {
            //Deleting accounts
            
            int acct_info;
            cin >> acct_info;
            int index = search(acc_array, num_array, acct_info);
            if (index != -1)
            {
                for (int i = index + 1; i < num_array; ++i)
                {
                    // copying the elements of the old arrays to the new ones 
                    acc_array[i-1] = acc_array[i];  
                    balance_array[i-1] = balance_array[i];
                }   
                
                num_array = num_array - 1;
                
                cout << "Deleted account " << acct_info << endl;
            } 
            
            else
            {
                cout <<  "** Invalid account, transaction ignored" << endl;
            }
        }
       
            else if (command != "x")
            {
                cout << "** Invalid command, try again..." << endl;
            }
    
     }
       
        

    
//    Step 4 - sending values to the outfile 
       cout << "** Saving account data..." << endl;
       cout << "** Done **" << endl;
  
   ofstream outfile;
   outfile.open(filename);
   outfile << fixed;
   outfile << setprecision(2);
//    if (!outfile.good()) 
//    {
//       cout << "**Error: unable to open input file '" << filename << "'" << endl;
//       return 0;  
//    }
   
   outfile << num_array << endl;
   for (int i = 0; i < num_array; ++i) 
   {
       outfile << acc_array[i] << " " << balance_array[i] << endl;
   }
   outfile.close();
    
   delete[] acc_array;
   delete[] balance_array; 
       
   return 0;
   }
       
       