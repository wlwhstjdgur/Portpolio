#ifndef MYMSG_H
#define MYMSG_H
#define MSG_TYPE_CALC 1
#define MSG_TYPE_RSLT 2
#define MSG_SIZE_CALC (sizeof(MsgSnd) - sizeof(long))
#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))
using namespace std;

struct MsgSnd {
    long mtype;
    char msg1[2048];
    char msg2[2048];
};
typedef struct MsgSnd MsgSnd;

struct MsgRslt {
    long mtype;
    int rslt;
};
typedef struct MsgRslt MsgRslt;
#endif //! MYMSG_H
