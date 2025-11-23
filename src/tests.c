#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "pthread_groups.h"
#include <unistd.h>

typedef void* ( *target )( void *);

void* test_func(void* arg){
	int * val_arg = (int*)arg;
	pthread_t self_id = pthread_self();
	printf("I'm executed inside the %lu thread\n",self_id);
	printf("Received this arg %d\n",*val_arg);
	return NULL;
}


int main(int args, char* argv[]){
	printf("Main started\n");
	target t_targets[3];
	int* my_args[3] = {(int*)11,(int*)24,(int*)63};
	void ** my_target_args = (void**) my_args;
	t_targets[0] = &test_func;
	t_targets[1] = &test_func;
	t_targets[2] = &test_func;
	struct ThreadGroup* tg = create_thread_group(t_targets,my_target_args,3);
	unsigned int size = tg->size;
	printf("Tg size %u\n",size);
	join_thread_group(tg);
/**/
	printf("End of main\n");
	return 0;
}
