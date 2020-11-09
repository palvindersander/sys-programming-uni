#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <pthread.h>
#include "bst.h"
#include "bst.c"

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


void* ServeClient(char *clientCommands){

	// TODO: Open the client command file and read commands line by line

	// TODO: match and execute commands

	// TODO: Handle command: "insertNode <some unsigned int value>"
	// print: "[ClientName]insertNode <SomeNumber>\n"
	// e.g. "[client1_commands]insertNode 1\n"

	// TODO: Handle command: "deleteNode <some unsigned int value>"
	// print: "[ClientName]deleteNode <SomeNumber>\n"
	// e.g. "[client1_commands]deleteNode 1\n"

	// TODO: Handle command: "countNodes"
	// print: "[ClientName]countNodes = <SomeNumber>\n"
	// e.g. "[client1_commands]countNodes 1\n"


	// TODO: Handle command: "sumSubtree"
	// print: "[ClientName]sumSubtree = <SomeNumber>\n"
	// e.g. "[client1_commands]sumSubtree 1\n"

	FILE *pToFile = fopen(clientCommands,"r");
	if(pToFile == NULL){
		return NULL;
	}
	char input[512];
	while(fgets(input,512,pToFile)) {
		// process line
		char* line = input;
		char *saveptr;
		char *function, *value;
		function = strtok_r(line, " ", &saveptr);
		if(function == "insertNode" || function == "deleteNode") {
			value = strtok_r(NULL, " ", &saveptr);
			if(value == NULL) {
				continue;
			}
			int val = atoi(value);
			if(function == "insertNode") {
				// insert node
				pthread_rwlock_wrlock(&lock);
				insertNode(root,val);
				pthread_rwlock_unlock(&lock);
				printf("[%d]insertNode %d\n",clientCommands,value);
			} else if(function == "deleteNode") {
				// delete node
				pthread_rwlock_wrlock(&lock);
				deleteNode(root,val);
				pthread_rwlock_unlock(&lock);
				printf("[%d]deleteNode %d\n",clientCommands,value);
			}
		} else if(function == "countNodes") {
			// count nodes
			pthread_rwlock_rdlock(&lock);
			countNodes(root);
			pthread_rwlock_unlock(&lock);
		} else if(function == "sumSubtree") {
			// sum nodes
			pthread_rwlock_rdlock(&lock);
			sumSubtree(root);
			pthread_rwlock_unlock(&lock);
		}
	}
	fclose(pToFile);

	return NULL;
}

