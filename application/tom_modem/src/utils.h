#ifndef _UTILS_H
#define _UTILS_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <sys/select.h>
#include <errno.h>
#include "modem_types.h"
#include "extlib/pdu.h"
#include "time.h"

extern PROFILE_T s_profile;
extern FDS_T s_fds;

#define dbg_msg(fmt, args...) do { \
    if (s_profile.debug) { \
    fprintf(stderr, "[DBG]" fmt, ##args); \
    fprintf(stderr, "\n"); \
	fflush(stderr); \
    } \
} while(0)

#define err_msg(fmt, args...) do { \
    if (1) { \
    fprintf(stderr, "[ERR]"  fmt , ##args); \
    fprintf(stderr, "\n"); \
	fflush(stderr); \
    } \
} while(0)

#define get_sms_index(line) \
    ({ \
        const char *index_str = (line) + 7; \
        const char *first_comma = strchr(index_str, ','); \
        int sms_index = -1; \
        if (first_comma) { \
            char temp[(size_t)(first_comma - index_str) + 1]; \
            memcpy(temp, index_str, first_comma - index_str); \
            temp[(size_t)(first_comma - index_str)] = '\0'; \
            sms_index = atoi(temp); \
        } \
        sms_index; \
    })

#define user_msg(fmt, args...) (fprintf(stdout, fmt , ##args))



int match_option(char *option_name);

int match_operation(char *operation_name);


int decode_pdu(SMS_T *sms);


int tty_read_keyword(FILE *fdi, char *output, int len, char *key_word, int soft_timeout);

int tty_read(FILE *fdi, char *output, int len, int soft_timeout);

int dump_sms(SMS_T *sms);

int destroy_sms(SMS_T *sms);

int display_sms_in_json(SMS_T **sms,int num);
#endif
