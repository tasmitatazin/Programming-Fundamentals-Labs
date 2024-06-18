#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode); // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode); // register closes

// Customer
void addCustomer(stringstream &lineStream,
                 string mode); // customer wants to join

// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);
void updateCustomers(string mode);
void calculateStats();
double calculateMeanWaitTime();
double calculateStdDevWaitTime();
double calculateMaxWaitTime();
// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList;        // holding the list of customers served
QueueList *singleQueue;     // holding customers in a single virtual queue
double expTimeElapsed;      // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main()
{
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> "; // Prompt for input
  getline(cin, line);

  while (!cin.eof())
  {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register")
    {
      parseRegisterAction(lineStream, mode);
    }
    else if (command == "customer")
    {
      addCustomer(lineStream, mode);
    }
    else
    {
      cout << "Invalid operation" << endl;
    }
    cout << "> "; // Prompt for input
    getline(cin, line);
  }
  calculateStats();
  // You have to make sure all dynamically allocated memory is freed
  // before return 0
  // Delete the queuelists and registers
  // Register *temp = registerList->get_head();
  // Delete all registers
  // while (temp != nullptr)
  // {
  //   Register *next = temp->get_next();
  //   temp->get_queue_list()->empty_queue();
  //   // delete temp->get_queue_list();
  //   temp->set_next(nullptr);
  //   delete temp;
  //   temp = next;
  // }
  delete registerList;
  doneList->empty_queue();
  delete doneList;
  singleQueue->empty_queue();
  delete singleQueue;
  return 0;
}

string getMode()
{
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single")
  {
    cout << "Simulating a single queue ..." << endl;
  }
  else if (mode == "multiple")
  {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode)
{
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed))
  {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream))
  {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items
  double arrival = expTimeElapsed + timeElapsed;
  // check and update system
  expTimeElapsed = arrival;
  updateCustomers(mode);
  Customer *newCustomer = new Customer(arrival, items);
  cout << "A customer entered\n";
  if (mode == "single")
  {
    Register *freeRegister = registerList->get_free_register();
    if (freeRegister != nullptr)
    {
      freeRegister->get_queue_list()->enqueue(newCustomer);
      cout << "Queued a customer with free register " << freeRegister->get_ID() << "\n";
    }
    else
    {
      cout << "No free registers\n";
      singleQueue->enqueue(newCustomer);
    }
  }
  else
  {
    Register *minItemsRegister = registerList->get_min_items_register();
    minItemsRegister->get_queue_list()->enqueue(newCustomer);
    cout << "Queued a customer with quickest register " << minItemsRegister->get_ID() << "\n";
  }
}

void parseRegisterAction(stringstream &lineStream, string mode)
{
  string operation;
  lineStream >> operation;
  if (operation == "open")
  {
    openRegister(lineStream, mode);
  }
  else if (operation == "close")
  {
    closeRegister(lineStream, mode);
  }
  else
  {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode)
{
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed))
  {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream))
  {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue,
  // and there were customers in line, then
  // assign a customer to the new register
  if (registerList->foundRegister(ID))
  {
    cout << "Error: register " << ID << " is already open" << endl;
    return;
  }
  expTimeElapsed += timeElapsed;
  updateCustomers(mode);
  Register *newRegister = new Register(ID, secPerItem, setupTime, expTimeElapsed);
  registerList->enqueue(newRegister);
  cout << "Opened register " << ID << endl;
  if (mode == "single")
  {
    if (singleQueue->get_items() > 0)
    {
      Customer *newCustomer = singleQueue->dequeue();
      newRegister->get_queue_list()->enqueue(newCustomer);
      newCustomer->set_next(nullptr);
      cout << "Queued a customer with free register " << ID << "\n";
    }
  }
}

void closeRegister(stringstream &lineStream, string mode)
{
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed))
  {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream))
  {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message
  if (!registerList->foundRegister(ID))
  {
    cout << "Error: register " << ID << " is not open" << endl;
    return;
  }
  expTimeElapsed += timeElapsed;
  updateCustomers(mode);
  Register *temp = registerList->dequeue(ID);
  temp->get_queue_list()->empty_queue();
  temp->set_next(nullptr);
  delete temp;
  cout << "Closed register " << ID << endl;
}

void updateCustomers(string mode)
{
  if (mode == "single")
  {
    Register *min_time_register = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
    while (min_time_register != nullptr)
    {
      double depa_time = min_time_register->calculateDepartTime();
      if (depa_time == -1 || depa_time > expTimeElapsed)
        break;
      else
      {
        min_time_register->departCustomer(doneList);
        cout << "Departed a customer at register ID " << min_time_register->get_ID() << " at " << depa_time << "\n";
        if (singleQueue->get_head() != nullptr)
        {
          Customer *newCustomer = singleQueue->dequeue();
          newCustomer->set_next(nullptr);
          min_time_register->get_queue_list()->enqueue(newCustomer);
          cout << "Queued a customer with free register " << min_time_register->get_ID() << "\n";
        }
        min_time_register = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
      }
    }
  }
  else
  {
    Register *min_time_register = registerList->calculateMinDepartTimeRegister(expTimeElapsed);

    while (min_time_register != nullptr)
    {
      double depa_time = min_time_register->calculateDepartTime();
      if (depa_time == -1 || depa_time > expTimeElapsed)
        break;
      else
      {
        min_time_register->departCustomer(doneList);
        cout << "Departed a customer at register ID " << min_time_register->get_ID() << " at " << depa_time << "\n";
        min_time_register = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
      }
    }
  }
}

bool getInt(stringstream &lineStream, int &iValue)
{
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail())
  {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue)
{
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail())
  {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream)
{
  string command;
  lineStream >> command;
  if (lineStream.fail())
  {
    return false;
  }
  else
  {
    return true;
  }
}

double calculateMeanWaitTime()
{
  // Calculate the mean wait time of all customers
  // in the doneList
  double mean = 0;
  int count = 0;
  Customer *temp = doneList->get_head();
  while (temp != nullptr)
  {
    mean += temp->get_departureTime() - temp->get_arrivalTime();
    count++;
    temp = temp->get_next();
  }
  return mean / count;
}

double calculateStdDevWaitTime()
{
  // Calculate the standard deviation of wait time
  // of all customers in the doneList
  double mean = calculateMeanWaitTime();
  double std = 0;
  int count = 0;
  Customer *temp = doneList->get_head();
  while (temp != nullptr)
  {
    std += pow(temp->get_departureTime() - temp->get_arrivalTime() - mean, 2);
    count++;
    temp = temp->get_next();
  }
  return sqrt(std / count);
}

double calculateMaxWaitTime()
{
  // Calculate the maximum wait time of all customers
  // in the doneList
  double max = 0;
  Customer *temp = doneList->get_head();
  while (temp != nullptr)
  {
    if (temp->get_departureTime() - temp->get_arrivalTime() > max)
      max = temp->get_departureTime() - temp->get_arrivalTime();
    temp = temp->get_next();
  }
  return max;
}

void calculateStats()
{
  // Calculate and print the mean and standard deviation
  // of the wait time of all customers in the doneList
  cout << "Finished at time " << expTimeElapsed << "\n";
  cout << "Statistics:\n";
  cout << "Maximum wait time: " << calculateMaxWaitTime() << "\n";
  cout << "Average wait time: " << calculateMeanWaitTime() << endl;
  cout << "Standard Deviation of wait time: " << calculateStdDevWaitTime() << endl;
}




