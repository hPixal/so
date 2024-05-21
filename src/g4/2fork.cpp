#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <vector>

using namespace std;
int main()
{	
	for(int i=0;i<3;i++) { 
		if (fork()!=0){
			cout<<"Sistemas Operativos\n";
			
		}
		
	}
	
	return 0;
}

// std::vector<pid_t> childPIDs;

// int main( int argc, char *argv[] ) {
// 
//     for (int i = 0; i < 3; i++) {
//         pid_t pid = fork();
//         if (pid == 0) {
//             cout << "Soy el proceso hijo" << endl;
//             sleep(1);
//             exit(0);
//         } else {
//             childPIDs.push_back(pid);
//         }
//     }
// 
//     cout << "Sistemas Operativos" ;
//     sleep(10);
// 
//     for (pid_t pid : childPIDs) {
//         waitpid(pid, NULL, 0);
//     }
//     return 0;
// 
// }