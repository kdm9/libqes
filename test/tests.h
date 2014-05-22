/*
 * ============================================================================
 *
 *       Filename:  tests.h
 *
 *    Description:  Tests for kmlib
 *
 *        Version:  1.0
 *        Created:  04/05/14 15:48:16
 *       Revision:  none
 *        License:  GPLv3+
 *       Compiler:  gcc
 *
 *         Author:  Kevin Murray, spam@kdmurray.id.au
 *
 * ============================================================================
 */

#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>

/* TinyTest */
#include "tinytest.h"
#include "tinytest_macros.h"
#include "testdata.h"

#define	KM_DEFAULT_ERR_FN errnil
#define KM_EXIT_FN (void)
#include <kmutil.h>


/* Test replacement functions */

/* Use to avoid calling zfopen except when testing zfopen */

#define	our_zfopen(var, pth, mde) do {             \
    (var) = calloc(1, sizeof(*(var)));              \
    (var)->fp = KM_ZOPEN(pth, mde);                \
    if ((var)->fp == NULL) {                        \
        free((var));                                \
        (var) = NULL;                               \
        break; /* from do {} while,  i.e return*/   \
    }                                               \
    KM_ZBUFFER((var)->fp, KM_FILEBUFFER_LEN);       \
    (var)->buffer = malloc(KM_FILEBUFFER_LEN);      \
    (var)->bufiter = (var)->buffer;                 \
    (var)->bufend = (var)->buffer + KM_FILEBUFFER_LEN;  \
    (var)->eof = 0;                                 \
    (var)->feof = 1;                                \
    (var)->filepos = 0;                             \
    (var)->mode = zfile_guess_mode(mde);           \
    (var)->path = strndup(pth, KM_MAX_FN_LEN);      \
    __zfile_fill_buffer(var);                       \
    } while(0)


#define our_create_seqfile(var, fn, mode) do {          \
    (var) = calloc(1, sizeof(seqfile_t));               \
    our_zfopen(((var)->zf), fn, mode);                  \
    if ((var)->zf == NULL) { free((var)); var = NULL; } \
    } while (0)

#define	our_zfclose(f) do { \
    if ((f) != NULL) {        \
        KM_ZCLOSE((f)->fp);   \
        free((f)->path);      \
        free((f)->buffer);    \
        (f)->buffer = NULL;   \
        (f)->bufiter = NULL;  \
        (f)->bufend = NULL;   \
        free(f); (f) = NULL;  \
    }} while(0)

#define our_destroy_seqfile(sf) do {        \
    if(sf != NULL) {                        \
        our_zfclose(sf->zf);                \
        free(sf);                           \
        sf = NULL;                          \
    }} while (0)

/* List of tests format is:
   { name, fn, flags, testcase_setup_t *ptr, void * for testcase_setup_t }
 */
/* test_util tests */
void test_km_calloc(void *);
void test_km_malloc(void *);
void test_km_realloc(void *);
void test_km_free(void *);
void test_kmroundup32(void *);
void test_kmroundup64(void *);
extern struct testcase_t util_tests[];

/* test_match tests */
void test_hamming(void *);
void test_hamming_max(void *);
extern struct testcase_t match_tests[];

/* test_zfile tests */
void test_zfopen(void *);
void test_zfclose(void *);
void test_zfreadline(void *);
void test_zfreadline_realloc(void *);
void test_zfile_guess_mode (void *);
void test_zfpeek (void *);
void test_zfrewind (void *);
void test_zfgetuntil (void *);
void test_zfile_ok (void *ptr);
extern struct testcase_t zfile_tests[];

/* test_seqfile tests */
void test_create_seqfile (void *);
void test_seqfile_guess_format (void *ptr);
void test_destroy_seqfile (void *ptr);
extern struct testcase_t seqfile_tests[];

#endif /* TESTS_H */
