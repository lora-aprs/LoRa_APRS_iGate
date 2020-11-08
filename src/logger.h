#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <Arduino.h>

class Logger
{
public:
	enum debug_level_t {
		DEBUG_LEVEL_NONE,		// No debug output
		DEBUG_LEVEL_ERROR,		// Critical errors
		DEBUG_LEVEL_WARN,		// Error conditions but not critical
		DEBUG_LEVEL_INFO,		// Information messages
		DEBUG_LEVEL_DEBUG,		// Extra information - default level (if not changed)
		DEBUG_LEVEL_VERBOSE,	// More information than the usual
		DEBUG_LEVELS_SIZE
	};

	static Logger & instance()
    {
       static Logger _instance;
       return _instance;
    }

	~Logger() {}

	void setSerial(const HardwareSerial & serial = Serial);
	void setDebugLevel(debug_level_t level);

	// print always:
	void printA(const String & text, const char * file, uint32_t line);		// always
	void printE(const String & text, const char * file, uint32_t line);		// error
	void printlnA(const String & text, const char * file, uint32_t line);	// always with new line
	void printlnE(const String & text, const char * file, uint32_t line);	// error with new line

	// depending on verbose level:
	void printV(const String & text, const char * file, uint32_t line);		// verbose
	void printD(const String & text, const char * file, uint32_t line);		// debug
	void printI(const String & text, const char * file, uint32_t line);		// information
	void printW(const String & text, const char * file, uint32_t line);		// warning

	void printlnV(const String & text, const char * file, uint32_t line);	// verbose with new line
	void printlnD(const String & text, const char * file, uint32_t line);	// debug with new line
	void printlnI(const String & text, const char * file, uint32_t line);	// information with new line
	void printlnW(const String & text, const char * file, uint32_t line);	// warning with new line

private:
	HardwareSerial & _serial;
	debug_level_t _level;
	bool _printIsNewline;

	void printStartColor(debug_level_t level);
	void printHeader(debug_level_t level, const char * file, uint32_t line, bool isln);
	void printEndColor(debug_level_t level);
	char levelToChar(debug_level_t level);

	Logger();
	Logger(const Logger &);
	Logger & operator = (const Logger &);
};

#define logPrintA(text)		Logger::instance().printA(text, __FILE__, __LINE__)
#define logPrintE(text)		Logger::instance().printE(text, __FILE__, __LINE__)
#define logPrintlnA(text)	Logger::instance().printlnA(text, __FILE__, __LINE__)
#define logPrintlnE(text)	Logger::instance().printlnE(text, __FILE__, __LINE__)
#define logPrintV(text)		Logger::instance().printV(text, __FILE__, __LINE__)
#define logPrintD(text)		Logger::instance().printD(text, __FILE__, __LINE__)
#define logPrintI(text)		Logger::instance().printI(text, __FILE__, __LINE__)
#define logPrintW(text)		Logger::instance().printW(text, __FILE__, __LINE__)
#define logPrintlnV(text)	Logger::instance().printlnV(text, __FILE__, __LINE__)
#define logPrintlnD(text)	Logger::instance().printlnD(text, __FILE__, __LINE__)
#define logPrintlnI(text)	Logger::instance().printlnI(text, __FILE__, __LINE__)
#define logPrintlnW(text)	Logger::instance().printlnW(text, __FILE__, __LINE__)

#endif
