#include "PipeWrapper.h"

PipeWrapper::PipeWrapper() {
	m_pipe = nullptr;
}

PipeWrapper::PipeWrapper(std::string command, std::string mode) : PipeWrapper() {
	this->open(command, mode);
}

PipeWrapper::~PipeWrapper() {
	this->close();
}



bool PipeWrapper::isOpen() {
	return m_pipe != nullptr;
}



void PipeWrapper::open(std::string command, std::string mode) {
	this->close();

	m_pipe = popen2(command.c_str(), mode.c_str());
}

void PipeWrapper::close() {
	if (this->isOpen()) {
		pclose2(m_pipe);

		m_pipe = nullptr;
	}
}



void PipeWrapper::flush() {
	if (isOpen()) {
		fflush(m_pipe);
	}
}


PipeWrapper& operator<<(PipeWrapper& pipe, std::string str) {
	if (pipe.isOpen()) {
		fprintf(pipe.m_pipe, "%s", str.c_str());
	}
	return pipe;
}

PipeWrapper& operator<<(PipeWrapper& pipe, double_t number) {
	if (pipe.isOpen()) {
		fprintf(pipe.m_pipe, "%f", number);
	}
	return pipe;
}

PipeWrapper& operator<<(PipeWrapper& pipe, char character) {
	if (pipe.isOpen()) {
		fprintf(pipe.m_pipe, "%c", character);
	}
	return pipe;
}

PipeWrapper& operator<<(PipeWrapper& pipe, PipeWrapper::std_endline manip) {
	if (pipe.isOpen()) {
		fprintf(pipe.m_pipe, "\n");
		pipe.flush();
	}
	return pipe;
}



FILE* PipeWrapper::popen2(const char* command, const char* mode) {
	FILE* pipe;
#if defined(_WIN32) || defined(_WIN64)
	pipe = _popen(command, mode);
#else
	pipe = popen(command, mode);
#endif // defined(_WIN32) || defined(_WIN64)
	return pipe;
}



void PipeWrapper::pclose2(FILE* pipe) {
#if defined(_WIN32) || defined(_WIN64)
	_pclose(pipe);
#else
	pclose(pipe);
#endif // defined(_WIN32) || defined(_WIN64)
}
