/*
 * ============================================================================
 *
 *       Filename:  qes_sequtil.h
 *
 *    Description:  Sequence utility functions
 *        License:  GPLv3+
 *         Author:  Kevin Murray, spam@kdmurray.id.au
 *
 * ============================================================================
 */

#ifndef QES_SEQUTIL_H
#define QES_SEQUTIL_H

#include <qes_util.h>


extern char qes_sequtil_translate_codon(const char *codon);
extern char *qes_sequtil_revcomp(const char *seq, size_t len);
extern void qes_sequtil_revcomp_inplace(char *seq, size_t len);

#endif /* QES_SEQUTIL_H */
