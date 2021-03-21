#include "sylee.hpp"
using namespace std;

void read_ls(list<string> &ls_list) {
    struct stat fileInfo;
    DIR *dirp;
    struct dirent *dirInfo;

    dirp = opendir("./Practices");
    while ((dirInfo = readdir(dirp)) != NULL) {
        if (dirInfo->d_name[0] == '.')
            ;
        else
            ls_list.push_back(dirInfo->d_name);
    }
    closedir(dirp);
}

void readfile(const char *pathName, string &str1, string &str2, int time) {

    // char *pathName = "./read.txt";
    char buf[1];
    char c;
    int fd = 0, rsize = 0, enter = 0;
    list<char> list_full;
    // list<char> list_cur;
    // list<char> list_next;
    list<char>::iterator it;

    fd = open(pathName, O_RDONLY, 0644);
    rsize = read(fd, buf, 1);

    //---------- 1 글자씩 읽어서 list_full 에 저장 ---------
    do {
        list_full.push_back(buf[0]);
        memset(buf, '\0', sizeof(buf));
        rsize = read(fd, buf, 1);
    } while (rsize > 0);

    int size = list_full.size();
    char arr_full[size];
    int i = -1;

    //----------- list_full을 arr_full로 옮김 -------------
    for (it = list_full.begin(); it != list_full.end();) {
        arr_full[++i] = *(it++);
    }

    // ---------- cur와 next를 저장 ------------------------
    int index = 0;
    i = 0;
    int save = 0;
    time += 1;
    while (time > 0) {
        char arr_cur[256] = {
            '\0',
        };
        char arr_next[256] = {
            '\0',
        };
        i = 0;
        int cur_len = 0, next_len = 0;
        index = save;
        while (index < size) {
            if (arr_full[index] == '\n') {
                index++;
                break;
            } else {
                arr_cur[i] = arr_full[index];
                i++;
                index++;
                save++;
                cur_len++;
            }
        }
        save = index;
        i = 0;
        while (index < size) {
            if (arr_full[index] == '\n') {
                index++;
                break;
            } else {
                arr_next[i] = arr_full[index];
                i++;
                index++;
                next_len++;
            }
        }

        // list<char> list_cur(arr_cur, arr_cur + cur_len);
        // list<char> list_next(arr_next, arr_next + next_len);
        if (time == 1) {
            for (int i = 0; i < cur_len; i++) {
                str1.push_back(arr_cur[i]);
            }
            for (int i = 0; i < next_len; i++) {
                str2.push_back(arr_next[i]);
            }
        }
        time--;
    }
}

void strsnd(string snd1, string snd2) {
    key_t mykey = ftok("mymsgkey", 1);
    int msqid = msgget(mykey, 0);

    if (msqid != -1) {
        MsgSnd msgSnd;
        MsgRslt msgRslt;

        int i = 0;
        memset(&msgSnd, 0x00, sizeof(MsgSnd));
        msgSnd.mtype = MSG_TYPE_CALC;
        string::iterator it;
        for (it = snd1.begin(); it != snd1.end(); ++it) {
            msgSnd.msg1[i++] = *it;
        }
        i = 0;
        for (it = snd2.begin(); it != snd2.end(); ++it) {
            msgSnd.msg2[i++] = *it;
        }
        msgsnd(msqid, &msgSnd, MSG_SIZE_CALC, 0);
    }
}
