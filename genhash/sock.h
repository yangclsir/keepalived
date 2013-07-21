/*
 * Soft:        Perform a GET query to a remote HTTP/HTTPS server.
 *              Set a timer to compute global remote server response
 *              time.
 *
 * Part:        sock.c include file.
 *
 * Version:     $Id: sock.h,v 1.1.16 2009/02/14 03:25:07 acassen Exp $
 *
 * Authors:     Alexandre Cassen, <acassen@linux-vs.org>
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; without even the implied warranty of
 *              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *              See the GNU General Public License for more details.
 *
 *              This program is free software; you can redistribute it and/or
 *              modify it under the terms of the GNU General Public License
 *              as published by the Free Software Foundation; either version
 *              2 of the License, or (at your option) any later version.
 *
 * Copyright (C) 2001-2012 Alexandre Cassen, <acassen@gmail.com>
 */

#ifndef _SOCK_H
#define _SOCK_H

/* system includes */
#include <openssl/ssl.h>

#include <openssl/md5.h>
#ifdef FEAT_SHA1
# include <openssl/sha.h>
#endif

/* available hashes enumeration */
enum feat_hashes {
	hash_first,
	hash_md5 = hash_first,
#ifdef FEAT_SHA1
	hash_sha1,
#endif
	hash_guard,
	hash_default = hash_md5,
};

/* Engine socket pool element structure */
typedef struct {
	int fd;
	SSL *ssl;
	BIO *bio;
	enum feat_hashes hash;
	union {
		MD5_CTX md5;
#ifdef FEAT_SHA1
		SHA_CTX sha;
#endif
	} context;
	int status;
	int lock;
	char *buffer;
	char *extracted;
	int size;
	int total_size;
} SOCK;

/* global vars exported */
extern SOCK *sock;

/* Prototypes */
extern void free_sock(SOCK *);
extern void init_sock(void);

#endif
