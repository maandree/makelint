/* See LICENSE file for copyright and license details. */
#include <libsimple.h>
#include <libsimple-arg.h>

#define EXIT_STYLE         1
#define EXIT_WARNING       2
#define EXIT_UNSPECIFIED   3
#define EXIT_NONCONFIRMING 4
#define EXIT_UNDEFINED     5
#define EXIT_CRITICAL      6
#define EXIT_ERROR         7


#define LIST_WARNING_CLASSES(X)\
	X(WC_MAKEFILE, "makefile", INFORM)\
	X(WC_EXTRA_MAKEFILE, "extra-makefile", WARN)\
	X(WC_CMDLINE, "cmdline", WARN)\
	X(WC_TEXT, "text", WARN)


enum action {
	IGNORE,
	INFORM,
	WARN
};

enum warning_class {
#define X(ENUM, NAME, ACTION) ENUM,
	LIST_WARNING_CLASSES(X)
#undef X
	NUM_WARNING_CLASS
};

struct warning_class_data {
	const char *name;
	enum action action;
};

struct line {
	char *data;
	size_t len;
	const char *path;
	size_t lineno;
};


extern int exit_status;


/* ui.c */
extern struct warning_class_data warning_classes[];
void xprintwarningf(enum warning_class class, int severity, const char *fmt, ...);
#define printinfof(CLASS, ...) xprintwarningf(CLASS, EXIT_STYLE, __VA_ARGS__)
#define warnf_warning(CLASS, ...) xprintwarningf(CLASS, EXIT_WARNING, __VA_ARGS__)
#define warnf_unspecified(CLASS, ...) xprintwarningf(CLASS, EXIT_UNSPECIFIED, __VA_ARGS__)
#define warnf_undefined(CLASS, ...) xprintwarningf(CLASS, EXIT_UNDEFINED, __VA_ARGS__)
void printerrorf(const char *fmt, ...);
