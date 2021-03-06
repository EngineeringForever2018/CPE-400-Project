#include "Router.h"
#include "Packet.h"
#include <iostream>
#include <list>
using namespace std;

Router::Router() {};

bool Router::add_packet(Packet packet)
{
    if(packet_queue.size() < 7) //check the size of the queue to see if we can add packets or not
    {
       packet_queue.push(packet);
       return true;
    }

    else if(packet_queue.size() >= 7 && packet_queue.size() < 10) //router is getting congested, set flag
    {
        set_flag(1);
        cout << "router flag value after set flag: " << get_flag() << endl;
        packet_queue.push(packet);
        return true;
    }
    
    // Our current implementation makes it so that the queues never reach 10 

    // if the queue is full and the router is the final destination, clear the queue and ack the receival of the packets 
    else if(packet_queue.size() >= 10 && (packet.getDestination() == this -> ID)) 
    {
      cout << "At least ten packets received from " << packet.getSource() << endl;
      int packets = packet_queue.size();
      for(int i = 0; i < packets; i++)
      {
        packet_queue.pop();
      }
      set_flag(0);
      cout << "Packets in destination router (should be 0) " << packet_queue.size() << endl;
      return false;
    }
    
    // if its not the destination router, clear half the buffer queue
    else if(packet_queue.size() >= 10)
    {  
      
       //clears half of the buffer queue
       for (int i = 0; i < 5; i++)
       {
          //removing the newest packets
          packet_queue.pop();
       }
       cout << "Buffer queue full, clearing queue" << endl;
       set_flag(0);
       return false;
    }

    return false;
}

int Router::getPacketTotal()
{
    return packet_queue.size();
}

void Router::remove_packet()
{
    packet_queue.pop();
}

Packet Router::getPacket()
{
    return packet_queue.front();
}
void Router::print_queue()
{
    while(!packet_queue.empty())
    {
      cout << packet_queue.front().getHeader() << " ";
      packet_queue.pop();
    }
    cout << "*" << endl;
} 

void Router::set_flag(bool buffer_flag) 
{
   this -> buffer_flag = buffer_flag;
}

bool Router::get_flag()
{
   return this -> buffer_flag;
}

int Router::getID() 
{
  return ID;
}

void Router::setID(int ID) 
{
   this -> ID = ID;
}

void Router::depop()
{
  int packets = getPacketTotal();
  for(int i = 0; i < packets; i++)
  {
     packet_queue.pop();
  }
      
  set_flag(0);
}
