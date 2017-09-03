#ifndef MESSAGETYPES_H
#define MESSAGETYPES_H

#include <string>
using namespace std;

enum message_type
{
	msg_MeetAtMax,
	msg_MaxYes,
	msg_MaxNo,
};

inline string MsgToStr(int msg)
{
  switch (msg)
  {
  case msg_MeetAtMax:
    
    return "MeetAtMax"; 

  case msg_MaxYes:
    
    return "msg_MaxYes";

  default:

    return "Not recognized!";
  }
}

#endif