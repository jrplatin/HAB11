#include <assert.h>
#include <string.h>
using namespace std;

enum MSG_TYPE {
  SND,
  RCV
};

class Message {
  public:
    int timestamp;
    char message[200];
    MSG_TYPE type;
    Message(int, char[], MSG_TYPE);
};

Message::Message (int ts, char msg[], MSG_TYPE mt)
{
  timestamp = ts;
  strcpy(message, msg);
  type = mt;
}

//Below are the test for constructor of Message class. Errors are thrown if any tests fail.
// static void testMessageClass()
// {
//   Message* m = new Message(1485717297, "TEST", RCV);
//   assert(m->timestamp == 1485717297);
//   assert(m->message[0] == 'T');
//   assert(m->message[1] == 'E');
//   assert(m->message[2] == 'S');
//   assert(m->message[3] == 'T');
//   assert(m->type == RCV);
// }

// int main() 
// {
//     // testMessageClass();
// }

