
# pragma once

# include <iostream>

# include <sys/wait.h>
# include <unistd.h>

template <typename Container, typename T>
inline void test_push_pop_back(std::ofstream& fd)
{
	fd << std::endl << "-------------- PUSH/POP BACK ----------------" << std::endl;

	// push empty

	Container c;

	fd << "\'Push back\' test 1: " << c.empty() << " " << c.size() << " ";
	c.push_back(T(42));
	fd << *c.begin() << " " << bool(*c.end() != *c.begin()) << " " << c.size() << " " << c.capacity() << std::endl;

	// non empty

	fd << "\'Push back\' test 2: " << c.empty() << " " << c.size() << " ";
	c.push_back(T(42));
	fd << *c.end() << " " << bool(*c.end() != *c.begin()) << " " << c.size() << " " << c.capacity() << std::endl;

	// push until size == cap and then push

	fd << "\'Push back\' test 3: " << c.empty() << " " << c.size() << " ";
	for (size_t i = -1 ; i < c.capacity() ; i++)
		c.push_back(T(42));
	fd << *c.end() << " " << bool(*c.end() != *c.begin()) << " " << c.size() << " " << c.capacity() << std::endl;

	// pop empty

	Container r;

	fd << "\'Pop back\' test 1: ";

	pid_t pid = fork();
	if (pid == pid_t())
	{
		r.pop_back();
		exit(42); // If success will reach this line
	}
	else if (pid < pid_t())
		std::cerr << "Syscall fork failed for misterious reasons ..."
		<< "[Check the memory avalaible in your device]" << std::endl;
	int wstatus;
	while (waitpid(pid, &wstatus, 0) >= 0);
	fd << (WIFEXITED(wstatus) ? WEXITSTATUS(wstatus) : WIFSIGNALED(wstatus)) << std::endl;

	// pop until empty

	for (size_t i = 12 ; i > size_t() ; i--)
		r.push_back(T(i));
	while (!r.empty())
		r.pop_back();
	fd << "\'Pop back\' test 2: " << r.size() << " " << bool(r.begin() == r.end()) << std::endl;
}
