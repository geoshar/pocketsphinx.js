/* -*- c-basic-offset:4; indent-tabs-mode: nil -*- */
/* ====================================================================
 * Copyright (c) 2014 Alpha Cephei Inc..  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALPHA CEPHEI INC. ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/**
 * @file ps_search.h User can configure several "search" objects with
 * different grammars and langauge models and switch them in runtime to
 * provide interactive experience for the user.
 */

#ifndef __PS_SEARCH_H__
#define __PS_SEARCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sphinxbase/fsg_model.h>
#include <sphinxbase/ngram_model.h>

/**
 * PocketSphinx search iterator.
 */
typedef struct ps_search_iter_s ps_search_iter_t;


/**
 * Actives search with the provided name.
 *
 * Activates search with the provided name. The search must be added before
 * using either ps_set_fsg(), ps_set_lm() or ps_set_kws().
 *
 * @return 0 on success, 1 on failure
 */
POCKETSPHINX_EXPORT
int ps_set_search(ps_decoder_t *ps, const char *name);

/**
 * Returns name of curent search in decoder
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT 
const char* ps_get_search(ps_decoder_t *ps);

/**
 * Unsets the search and releases related resources.
 *
 * Unsets the search previously added with
 * using either ps_set_fsg(), ps_set_lm() or ps_set_kws().
 *
 * @see ps_set_fsg
 * @see ps_set_lm
 * @see ps_set_kws
 */
POCKETSPHINX_EXPORT
int ps_unset_search(ps_decoder_t *ps, const char *name);

/**
 * Returns iterator over current searches 
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
ps_search_iter_t *ps_search_iter(ps_decoder_t *ps);

/**
 * Updates search iterator to point to the next position.
 * 
 * This function automatically frees the iterator object upon reaching
 * the final entry.
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
ps_search_iter_t *ps_search_iter_next(ps_search_iter_t *itor);

/**
 * Retrieves the name of the search the iterator points to.
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
const char* ps_search_iter_val(ps_search_iter_t *itor);

/**
 * Delete an unfinished search iterator
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
void ps_search_iter_free(ps_search_iter_t *itor);

/**
 * Updates search iterator to point to the next position.
 * 
 * This function automatically frees the iterator object upon reaching
 * the final entry.
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
const char* ps_search_iter_val(ps_search_iter_t *itor);


/**
 * Get the language model set object for this decoder.
 *
 * If N-Gram decoding is not enabled, this will return NULL.  You will
 * need to enable it using ps_set_lmset().
 *
 * @return The language model set object for this decoder.  The
 *         decoder retains ownership of this pointer, so you should
 *         not attempt to free it manually.  Use ngram_model_retain()
 *         if you wish to reuse it elsewhere.
 */
POCKETSPHINX_EXPORT 
ngram_model_t *ps_get_lm(ps_decoder_t *ps, const char *name);

/**
 * Adds new search based on N-gram language model.
 *
 * Associates N-gram search with the provided name. The search can be activated
 * using ps_set_search().
 *
 * @see ps_set_search.
 */ 
POCKETSPHINX_EXPORT
int ps_set_lm(ps_decoder_t *ps, const char *name, ngram_model_t *lm);

/**
 * Adds new search based on N-gram language model.
 *
 * Convenient method to load N-gram model and create a search.
 * 
 * @see ps_set_lm
 */
POCKETSPHINX_EXPORT
int ps_set_lm_file(ps_decoder_t *ps, const char *name, const char *path);

/**
 * Get the finite-state grammar set object for this decoder.
 *
 * If FSG decoding is not enabled, this returns NULL.  Call
 * ps_set_fsgset() to enable it.
 *
 * @return The current FSG set object for this decoder, or
 *         NULL if none is available.
 */
POCKETSPHINX_EXPORT
fsg_model_t *ps_get_fsg(ps_decoder_t *ps, const char *name);

/**
 * Adds new search based on finite state grammar.
 *
 * Associates FSG search with the provided name. The search can be activated
 * using ps_set_search().
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT
int ps_set_fsg(ps_decoder_t *ps, const char *name, fsg_model_t *fsg);

/**
 * Adds new search using JSGF model.
 *
 * Convenient method to load JSGF model and create a search.
 *
 * @see ps_set_fsg
 */
POCKETSPHINX_EXPORT
int ps_set_jsgf_file(ps_decoder_t *ps, const char *name, const char *path);

/**
 * Get the current Key phrase to spot
 *
 * If KWS is not enabled, this returns NULL. Call
 * ps_update_kws() to enable it.
 *
 * @return The current keyphrase to spot
 */
POCKETSPHINX_EXPORT 
const char* ps_get_kws(ps_decoder_t *ps, const char *name);

/**
 * Adds keywords from a file to spotting
 *
 * Associates KWS search with the provided name. The search can be activated
 * using ps_set_search().
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT 
int ps_set_kws(ps_decoder_t *ps, const char *name, const char *keyfile);

/**
 * Adds new keyword to spot
 *
 * Associates KWS search with the provided name. The search can be activated
 * using ps_set_search().
 *
 * @see ps_set_search
 */
POCKETSPHINX_EXPORT 
int ps_set_keyphrase(ps_decoder_t *ps, const char *name, const char *keyphrase);

#ifdef __cplusplus
}
#endif

#endif /* __PS_SEARCH_H__ */
