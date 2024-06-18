#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer *customer) { head = customer; }

QueueList::~QueueList()
{
  // delete all customers in the queue
  // Customer *temp = this->head;
  // Customer *next = temp->get_next();
  // while (temp != nullptr)
  // {
  //   delete temp;
  //   temp = next;
  //   if (next != nullptr)
  //     next = next->get_next();
  // }
  // head = nullptr;
}

Customer *QueueList::get_head() { return this->head; }

void QueueList::enqueue(Customer *customer)
{
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  if (this->head == nullptr)
  {
    this->head = customer;
  }
  else
  {
    Customer *temp = this->head;
    while (temp->get_next() != nullptr)
    {
      temp = temp->get_next();
    }
    temp->set_next(customer);
  }
}

Customer *QueueList::dequeue()
{
  // remove a customer from the head of the queue
  // and return a pointer to it
  Customer *ret = this->head;
  this->head = this->head->get_next();
  return ret;
}

int QueueList::get_items()
{
  // count total number of items each customer in the queue has
  int count = 0;
  Customer *temp = head;
  // if (temp == nullptr)
  // {
  //   return 0;
  // }
  while (temp != nullptr)
  {
    count += temp->get_numOfItems();
    temp = temp->get_next();
  }
  return count;
}

bool QueueList::empty_queue()
{
  // if the queue is empty, return false
  // if the queue is not empty, delete all customers
  // and return true
  if (this->head == nullptr)
    return false;
  else
  {
    Customer *temp = this->head;
    Customer *next = temp->get_next();
    while (temp != nullptr)
    {
      delete temp;
      temp = next;
      if (next != nullptr)
        next = next->get_next();
    }
    head = nullptr;
    return true;
  }
}

void QueueList::print()
{
  // print customers in a queue
  Customer *temp = head;
  while (temp != nullptr)
  {
    temp->print();
    temp = temp->get_next();
  }
}
