#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	int cores = 0;
	int i;
	char cpus_test[10];
	cpu_set_t mask;
	CPU_ZERO(&mask);
	for (i=1; i<argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 'n') {
			cores = atoi (argv[i+1]);
		}
		if(argv[i][0] == '-' && argv[i][1] == 'c') {
			strcpy(cpus_test,argv[i+1]);
			printf("cpus_test:%s\n",cpus_test);
			int cpu_len = strlen(cpus_test);
			printf("len...:%d\n",cpu_len);

			for (int n=0; n<cpu_len; n++) {
				printf("%c\n",cpus_test[n]);
			}
			
			if(cpus_test[1]=='-'){
				int start = cpus_test[0]-'0';
				printf("start:%d\n",start);
				int end = cpus_test[2]-'0';
				printf("end:%d\n",end);
				for(int j=start; j<=end; j++){
    					//cpumask_set_cpu(j, &mask);
					printf("set %d cpu\n",j);
					CPU_SET(j, &mask);
				}
				break;
			}
			
			int k=0;
			while(k < cpu_len)
			{
				//cpumask_set_cpu(k, &mask);
				printf("set %d cpu\n",k);
				CPU_SET(k, &mask);
				break;
				if(k+1 < cpu_len && cpus_test[k+1]==',') {
				        k++;
				        continue;
				}
			}
		}
	}
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
		printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
		return -1; 
	}   
	
	/*if (!cores) {
		FILE *fp = fopen ("/proc/cpuinfo", "r");
		while (!feof (fp)) {
			char buffer[4096];
			if (!fgets (buffer, sizeof (buffer), fp)) {
				break;
			}
			if (strncmp (buffer, "processor\t:", 11) == 0) {
				cores++;
			}
		}
	}*/

	for (i = 0; i < CPU_SETSIZE; i++) {
     		if (CPU_ISSET(i, &mask)) {
			printf("CPU %d is set\n", i);
	        } else {
        		printf("CPU %d is not set\n", i);
	        }
	}	
	//printf ("Burning %u cores...\n", cores);
	/*for (i=0; i<cores; i++) {
		if (fork () == 0) {
			while (1) ;
		}
	}
	for (i=0; i<cores; i++) {
		wait (NULL);
	}*/
	while (1) {}

	return 0;
}
