#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{

  int num_exec_thread, num_max_thread, thread_num_int, stride_size;
  string thread_num_str, num_exec_thread_str, stride_size_str,syscall, num_max_thread_str;

	#ifdef __MIC__
		cout << "Running on Intel(R) Xeon(tm) Phi" << endl;
	#else
		cout << "Running on HOST" << endl;
	#endif

  cout << "Numero de threads max" << endl;
	cin >> num_max_thread;
  num_max_thread_str = to_string(num_max_thread);
  cout << "Numero de execucoes para cada thread" << endl;
  cin >> num_exec_thread;
  num_exec_thread_str = to_string(num_exec_thread);
  cout << "Stride size" << endl;
  cin >> stride_size;
  stride_size_str = to_string(stride_size);

  cout << "Executando ..." << '\n';

  for(int i=0; i < num_max_thread; i++){
  	thread_num_int = i + 1;
  	thread_num_str = to_string(thread_num_int);
  	syscall = "./FST " + stride_size_str + " ../data/prefixes-24.txt ../data/randomAddrs.txt 1 " \
  										+ thread_num_str + " " + num_exec_thread_str + " >> resultado.txt";
  	const char *run_program = syscall.c_str();
  	system(run_program);
    cout << "thread " + thread_num_str + " de " + num_max_thread_str << '\n';
  }
  for(int i=0; i < num_max_thread; i++){
  	thread_num_int = i + 1;
  	thread_num_str = to_string(thread_num_int);
  	syscall = "./FST " + stride_size_str + " ../data/prefixes-32.txt ../data/randomAddrs.txt 1 " \
  										+ thread_num_str + " " + num_exec_thread_str + " >> resultado.txt";
  	const char *run_program = syscall.c_str();
  	system(run_program);
    cout << "thread " + thread_num_str + " de " + num_max_thread_str << '\n';
  }
  cout << "Fim das execucoes" << '\n';

	return 0;
}
