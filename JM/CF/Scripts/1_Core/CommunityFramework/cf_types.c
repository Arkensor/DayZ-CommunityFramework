// Enum for LogLevel
// Must be set in 1_Core to be accessed by the WorkbenchPlugin!
enum LogLevel {
	TRACE, 		// Logs at beginning of each method
	DEBUG,		// Debug info within conditionals etc...
	INFO,		// Helpful info within conditionals etc... (likely more user friendly)
	WARNING,	// Warnings back to the user. unlikely to be mission critical
	ERROR		// oof
};
