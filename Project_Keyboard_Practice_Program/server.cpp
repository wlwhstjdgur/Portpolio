#include "mymsg.hpp"
#include <iostream>
#include <list>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
using namespace std;

void signalHandler(int signum);
double right_percent(string input, string file);
void msgrcv();

int msqid;

int main(int argc, char const *argv[]) {
    signal(SIGINT, signalHandler);
    while (1)
        msgrcv();
    return 0;
}

void msgrcv() {
    key_t mykey = 0;
    MsgSnd msgSnd;
    MsgRslt msgRslt;
    string rcv1, rcv2;
    mykey = ftok("mymsgkey", 1);
    msqid = msgget(mykey, IPC_CREAT | 0600);
    // signal(SIGINT, signalHandler);

    puts("Wait	...");
    memset(&msgSnd, 0x00, sizeof(MsgSnd));
    msgrcv(msqid, &msgSnd, MSG_SIZE_CALC, MSG_TYPE_CALC, 0);
    for (int i = 0; i < 256; ++i) {
        if (msgSnd.msg1[i] == '\0')
            break;
        else
            rcv1.push_back(msgSnd.msg1[i]);
    }
    for (int i = 0; i < 256; ++i) {
        if (msgSnd.msg2[i] == '\0')
            break;
        else
            rcv2.push_back(msgSnd.msg2[i]);
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << right_percent(rcv1, rcv2) << "%" << endl;
    fflush(stdout);
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}

double right_percent(string input, string file) {
    string::iterator iter1;
    string::iterator iter2;
    int right_cnt = 0;
    int size = 0;
    iter1 = input.begin();
    iter2 = file.begin();
    while (1) {
        if (iter1 == input.end() || iter2 == file.end()) {
            for (iter2 = file.begin(); iter2 != file.end(); ++iter2) {
                size++;
            }
            cout << endl;
            return (double)right_cnt / (double)size *
                   100; // (맞는글자수/파일 글자수)*100 해서 백분율출력
            break;
        } else if (*iter1 == *iter2) {
            right_cnt++;
        }

        ++iter1;
        ++iter2;
    }
}
