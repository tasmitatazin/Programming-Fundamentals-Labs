#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList()
{
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList()
{
  // Delete all registers in the list
  // You will have to loop through the list and delete each register
  Register *temp = head;
  while (temp != nullptr)
  {
    Register *next = temp->get_next();
    delete temp;
    temp = next;
  }
}

Register *RegisterList::get_head()
{
  return head;
}

int RegisterList::get_size()
{
  // return number of registers
  return size;
}

Register *RegisterList::get_min_items_register()
{
  // loop all registers to find the register with least number of items
  Register *temp = head;
  int min = 2147483647;
  while (temp != nullptr)
  {
    int temp_cnt = temp->get_queue_list()->get_items();
    if (temp_cnt < min)
    {
      min = temp_cnt;
    }
    temp = temp->get_next();
  }
  temp = head;
  while (temp != nullptr)
  {
    if (temp->get_queue_list()->get_items() == min)
    {
      return temp;
    }
    temp = temp->get_next();
  }
  return nullptr;
}

Register *RegisterList::get_free_register()
{
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register *temp = head;
  while (temp != nullptr)
  {
    if (temp->get_queue_list()->get_head() == nullptr)
    {
      return temp;
    }
    temp = temp->get_next();
  }
  return nullptr;
}

void RegisterList::enqueue(Register *newRegister)
{
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size
  if (head == nullptr)
  {
    head = newRegister;
  }
  else
  {
    Register *temp = head;
    while (temp->get_next() != nullptr)
    {
      temp = temp->get_next();
    }
    temp->set_next(newRegister);
  }
  size++;
}

bool RegisterList::foundRegister(int ID)
{
  // look for a register with the given ID
  // return true if found, false otherwise
  Register *temp = head;
  while (temp != nullptr)
  {
    if (temp->get_ID() == ID)
    {
      return true;
    }
    temp = temp->get_next();
  }
  return false;
}

Register *RegisterList::dequeue(int ID)
{
  // dequeue the register with given ID

  // return the dequeued register
  // return nullptr if register was not found
  if (head == nullptr)
  {
    return nullptr;
  }
  else if (head->get_ID() == ID)
  {
    Register *temp = head;
    head = head->get_next();
    size--;
    return temp;
  }
  else
  {
    Register *temp = head;
    while (temp->get_next() != nullptr)
    {
      if (temp->get_next()->get_ID() == ID)
      {
        Register *temp2 = temp->get_next();
        temp->set_next(temp->get_next()->get_next());
        size--;
        return temp2;
      }
      temp = temp->get_next();
    }
    return nullptr;
  }
}

Register *RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed)
{
  int min_val = 2147483647;
  Register *min = nullptr;
  Register *temp = head;
  while (temp != nullptr)
  {
    if (temp->get_queue_list()->get_head() != nullptr)
    {
      double tempDepartTime = temp->calculateDepartTime();
      if (tempDepartTime < min_val)
      {
        min_val = tempDepartTime;
        min = temp;
      }
    }
    temp = temp->get_next();
  }
  return min;
}

void RegisterList::print()
{
  Register *temp = head;
  while (temp != nullptr)
  {
    temp->print();
    temp = temp->get_next();
  }
}
