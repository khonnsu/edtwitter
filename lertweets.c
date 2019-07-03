#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	FILE *ent = fopen(arg[1],"r");
	FILE *ops = fopen(arg[2],"r");
	FILE *sai = fopen(arg[3],"w"); 
