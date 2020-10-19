#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#include "pcre.h"
#include <stdio.h>
#include <string.h>
#include <pcre2.h>

#define MAXSTR 80

char *pattern_match(const char *pattern_str, const char *subject_str)
{  
	char buf[MAXSTR];
    int global_sz = snprintf(buf, MAXSTR, " `%s` : `%s`\n", pattern_str, subject_str);
    char *res = malloc(sizeof(char) * (global_sz + 1 + MAXSTR));
    strncpy(res, buf, global_sz);



    pcre2_code *re;
    PCRE2_SPTR pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    pattern = (PCRE2_SPTR)pattern_str;
    subject = (PCRE2_SPTR)subject_str;
    subject_length = (PCRE2_SIZE)strlen((char *)subject);

#ifdef UTF
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_UCP, &errnum, &erroffs, NULL);
#else
    re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &errnum, &erroffs, NULL);
#endif

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));
        snprintf(res + global_sz, MAXSTR, " PCRE2 compilation failed at offset %d: %s\n", (int)erroffs,
               buffer);
        return res;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
            case PCRE2_ERROR_NOMATCH:
                snprintf(res + global_sz, MAXSTR, " No match\n");
                break;
            default:
                snprintf(res + global_sz, MAXSTR, " Matching error %d\n", rc);
                break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return res;
    }

    ovector = pcre2_get_ovector_pointer(match_data);


    for (i = 0; i < rc; i++)
    {
        int sz = snprintf(buf, MAXSTR, " %2ld: %.*s\n", ovector[2 * i],
                          (int) (ovector[2 * i + 1] - ovector[2 * i]),
                          subject + ovector[2 * i]);
        res = realloc(res, sizeof(char) * (sz + global_sz + 1));
        strncpy(res + global_sz, buf, sz);
        global_sz += sz;
    }
    res[global_sz] = '\0';

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return res;
}
