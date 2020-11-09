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
		line = strtok(line, "\n");
		function = strtok_r(line, " ", &saveptr);
		value = strtok_r(NULL, " ", &saveptr);
		if(strcmp(function, "insertNode") == 0 || strcmp(function, "deleteNode") == 0) {
			if(value == NULL) {
				continue;
			}
			int val = atoi(value);
			if(strcmp(function, "insertNode") == 0) {
				// insert node
				pthread_rwlock_wrlock(&lock);
				root=insertNode(root,val);
				pthread_rwlock_unlock(&lock);
				printf("[%s]insertNode %s\n",clientCommands,value);
			} else if(strcmp(function, "deleteNode") == 0) {
				// delete node
				pthread_rwlock_wrlock(&lock);
				root=deleteNode(root,val);
				pthread_rwlock_unlock(&lock);
				printf("[%s]deleteNode %s\n",clientCommands,value);
			}
		} else if(strcmp(function, "countNodes") == 0) {
			// count nodes
			pthread_rwlock_rdlock(&lock);
			printf("[%s]countNodes = %d\n",clientCommands,countNodes(root));
			pthread_rwlock_unlock(&lock);
		} else if(strcmp(function, "sumSubtree") == 0) {
			// sum nodes
			pthread_rwlock_rdlock(&lock);
			printf("[%s]sumSubtree = %d\n",clientCommands,sumSubtree(root));
			pthread_rwlock_unlock(&lock);
		}
	}
	fclose(pToFile);

	return NULL;
}

