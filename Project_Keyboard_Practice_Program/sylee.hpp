#ifndef __SYLEE_H__
#define __SYLEE_H__
#include "mymsg.hpp"
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
void read_ls(list<string> &ls_list);
void readfile(const char *pathName, string &str1, string &str2, int time);
void strsnd(string snd1, string snd2);
double right_percent(string input, string file);
#endif
