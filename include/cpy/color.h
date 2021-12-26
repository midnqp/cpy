#define COLOR(_COLOR, string, ...) "\033[" _COLOR string "\033[0m"

// Use the following.
#define BLK(string, ...) COLOR("30m", string)
#define RED(string, ...) COLOR("31m", string)
#define GRN(string, ...) COLOR("32m", string)
#define YLW(string, ...) COLOR("33m", string)
#define BLU(string, ...) COLOR("34m", string)
#define MGN(string, ...) COLOR("35m", string)
#define CYN(string, ...) COLOR("36m", string)
#define GRY(string, ...) COLOR("37m", string)

#define BLKBG(string, ...) COLOR("40m", string)
#define REDBG(string, ...) COLOR("41m", string)
#define GRNBG(string, ...) COLOR("42m", string)
#define YLWBG(string, ...) COLOR("43m", string)
#define BLUBG(string, ...) COLOR("44m", string)
#define MGNBG(string, ...) COLOR("45m", string)
#define CYNBG(string, ...) COLOR("46m", string)
#define GRYBG(string, ...) COLOR("47m", string)
