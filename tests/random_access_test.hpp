
# pragma once

# include <iostream>

# include <sys/wait.h>
# include <unistd.h>

template <typename Container, typename T>
inline void test_random_access(std::ofstream& fd)
{
	fd << std::endl << "-------------- RANDOM ACCESS ----------------" << std::endl;

	// TEST: at

	Container c(size_t(42));

	for (size_t i = 0 ; i < 42 ; i++)
		c.at(i) = T(i);
	fd << "\'At\' test 1: " << std::endl << "{ ";
	for (size_t i = 0 ; i < 42 ; i++)
	{
		c.at(i) = c.at(i) << T(1 & i);
		fd << c.at(i) << static_cast<std::string>(i == 41 ? "" : " ");
	}
	fd << " }" << std::endl;

	fd << "\'At\' test 2: ";
	try {
		c.at(42) = T();
		fd << "ERROR" << std::endl;
	} catch (...) { fd << "SUCCESS" << std::endl; }
	

	// TEST: operator[]

	c.clear();

	for (size_t i = 0 ; i < 42 ; i++)
		c[i] = T(i);
	fd << "\'operator[]\' test 1: " << std::endl << "{ ";
	for (size_t i = 0 ; i < 42 ; i++)
	{
		c[i] = c[i] << T(1 & i);
		fd << c[i] << static_cast<std::string>(i == 41 ? "" : " ");
	}
	fd << " }" << std::endl;

	fd << "\'operator[]\' test 2: ";
	pid_t pid = fork();
	if (pid == 0)
	{
		c[0xffff] = T();
		exit(EXIT_FAILURE); // Will never execute this line.
	}
	else if (pid < 0)
		std::cerr << "Syscall fork failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;

	int wstatus;
	while (waitpid(pid, &wstatus, 0) >= 0);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV)
		fd << "ALL OK" << std::endl;
	else
		fd << "ERROR" << std::endl;

	// NOTE: Some containers wont segfault if the operator at overflow with this test.
	fd << "\'operator[]\' test 3: ";
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		c[42] = T();
		exit(EXIT_FAILURE); // Will never execute this line.
	}
	else if (pid2 < 0)
		std::cerr << "Syscall \'fork\' failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;

	int wstatus2;
	while (waitpid(pid2, &wstatus2, 0) >= 0);
	if (WIFSIGNALED(wstatus2) && WTERMSIG(wstatus2) == SIGSEGV)
		fd << "SEGFAULT" << std::endl;
	else
		fd << "DON'T SEGFAULT" << std::endl;
}