#ifndef _PIPE_WRAPPER_H
#define _PIPE_WRAPPER_H

#include <cstdio>
#include <string>


/**
 * A wrapper around C-style pipes.
 * Works the same as standard C++ streams.
 */
class PipeWrapper final {
private: 
	using std_ostream = std::basic_ostream<char, std::char_traits<char>>;
	using std_endline = std_ostream & (*)(std_ostream&);
public:
	/**
	 * Constructs an empty pipe. Should be opened later.
	 */
	PipeWrapper();

	/**
	 * Opens a pipe.
	 *
	 * Only "w" mode is supported for now.
	 *
	 * \param command A command that opens a file.
	 * \param mode A mode to open a file.
	 */
	PipeWrapper(std::string command, std::string mode);

	/**
	 * Closes the pipe.
	 */
	~PipeWrapper();

	/**
	 * Checks if the pipe is opened.
	 * 
	 * \return true if pipe is opened, false otherwise.
	 */
	bool isOpen();

	/**
	 * Opens a pipe.
	 *
	 * Only "w" mode is supported for now.
	 *
	 * \param command A command that opens a file.
	 * \param mode A mode to open a file.
	 */
	void open(std::string command, std::string mode);

	/**
	 * Closes the pipe.
	 */
	void close();

	/**
	 * Flushes the contents of the pipe.
	 */
	void flush();

	/**
	 * Prints a string to a pipe.
	 * 
	 * \param pipe A pipe to print.
	 * \param str A string to print to a pipe.
	 * \return Updates pipe object.
	 */
	friend PipeWrapper& operator<<(PipeWrapper& pipe, std::string str);

	/**
	 * Prints a number to a pipe.
	 *
	 * \param pipe A pipe to print.
	 * \param number A number to print to a pipe.
	 * \return Updated pipe object.
	 */
	friend PipeWrapper& operator<<(PipeWrapper& pipe, double_t number);

	/**
	 * Prints a symbol to a pipe.
	 *
	 * \param pipe A pipe to print.
	 * \param char A symbol to print to a pipe.
	 * \return Updated pipe object.
	 */
	friend PipeWrapper& operator<<(PipeWrapper& pipe, char symbol);

	/**
	 * Allows to use std::endl manipulator.
	 * Pipe stream is flushed after std::endl usage.
	 *
	 * \param pipe A pipe to print.
	 * \param manip std::endl.
	 * \return Updated pipe object.
	 */
	friend PipeWrapper& operator<<(PipeWrapper& pipe, std_endline manip);

private:
	FILE* m_pipe;

	// Wrapper around _popen or popen from <cstdio>.
	static FILE* popen2(const char* command, const char* mode);
	// Wrapper around _pclose or pclose from <cstdio>.
	static void pclose2(FILE* pipe);
};

#endif // !_PIPE_WRAPPER_H
