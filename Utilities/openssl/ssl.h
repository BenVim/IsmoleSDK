/* ssl/ssl.h */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2007 The OpenSSL Project.  All rights reserved.
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
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * ECC cipher suite support in OpenSSL originally developed by 
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */
/* ====================================================================
 * Copyright 2005 Nokia. All rights reserved.
 *
 * The portions of the attached software ("Contribution") is developed by
 * Nokia Corporation and is licensed pursuant to the OpenSSL open source
 * license.
 *
 * The Contribution, originally written by Mika Kousa and Pasi Eronen of
 * Nokia Corporation, consists of the "PSK" (Pre-Shared Key) ciphersuites
 * support (see RFC 4279) to OpenSSL.
 *
 * No patent licenses or other rights except those expressly stated in
 * the OpenSSL open source license shall be deemed granted or received
 * expressly, by implication, estoppel, or otherwise.
 *
 * No assurances are provided by Nokia that the Contribution does not
 * infringe the patent or other intellectual property rights of any third
 * party or that the license provides you with all the necessary rights
 * to make use of the Contribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. IN
 * ADDITION TO THE DISCLAIMERS INCLUDED IN THE LICENSE, NOKIA
 * SPECIFICALLY DISCLAIMS ANY LIABILITY FOR CLAIMS BROUGHT BY YOU OR ANY
 * OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS OR
 * OTHERWISE.
 */

#ifndef HEADER_SSL_H 
#define HEADER_SSL_H 

#include <openssl/e_os2.h>

#ifndef OPENSSL_NO_COMP
#include <openssl/comp.h>
#endif
#ifndef OPENSSL_NO_BIO
#include <openssl/bio.h>
#endif
#ifndef OPENSSL_NO_DEPRECATED
#ifndef OPENSSL_NO_X509
#include <openssl/x509.h>
#endif
#include <openssl/crypto.h>
#include <openssl/lhash.h>
#include <openssl/buffer.h>
#endif
#include <openssl/pem.h>
#include <openssl/hmac.h>

#include <openssl/kssl.h>
#include <openssl/safestack.h>
#include <openssl/symhacks.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* SSLeay version number for ASN.1 encoding of the session information */
/* Version 0 - initial version
 * Version 1 - added the optional peer certificate
 */
#define SSL_SESSION_ASN1_VERSION 0x0001

/* text strings for the ciphers */
#define SSL_TXT_NULL_WITH_MD5		SSL2_TXT_NULL_WITH_MD5			
#define SSL_TXT_RC4_128_WITH_MD5	SSL2_TXT_RC4_128_WITH_MD5		
#define SSL_TXT_RC4_128_EXPORT40_WITH_MD5 SSL2_TXT_RC4_128_EXPORT40_WITH_MD5	
#define SSL_TXT_RC2_128_CBC_WITH_MD5	SSL2_TXT_RC2_128_CBC_WITH_MD5		
#define SSL_TXT_RC2_128_CBC_EXPORT40_WITH_MD5 SSL2_TXT_RC2_128_CBC_EXPORT40_WITH_MD5	
#define SSL_TXT_IDEA_128_CBC_WITH_MD5	SSL2_TXT_IDEA_128_CBC_WITH_MD5		
#define SSL_TXT_DES_64_CBC_WITH_MD5	SSL2_TXT_DES_64_CBC_WITH_MD5		
#define SSL_TXT_DES_64_CBC_WITH_SHA	SSL2_TXT_DES_64_CBC_WITH_SHA		
#define SSL_TXT_DES_192_EDE3_CBC_WITH_MD5 SSL2_TXT_DES_192_EDE3_CBC_WITH_MD5	
#define SSL_TXT_DES_192_EDE3_CBC_WITH_SHA SSL2_TXT_DES_192_EDE3_CBC_WITH_SHA	

/*    VRS Additional Kerberos5 entries
 */
#define SSL_TXT_KRB5_DES_64_CBC_SHA   SSL3_TXT_KRB5_DES_64_CBC_SHA
#define SSL_TXT_KRB5_DES_192_CBC3_SHA SSL3_TXT_KRB5_DES_192_CBC3_SHA
#define SSL_TXT_KRB5_RC4_128_SHA      SSL3_TXT_KRB5_RC4_128_SHA
#define SSL_TXT_KRB5_IDEA_128_CBC_SHA SSL3_TXT_KRB5_IDEA_128_CBC_SHA
#define SSL_TXT_KRB5_DES_64_CBC_MD5   SSL3_TXT_KRB5_DES_64_CBC_MD5       
#define SSL_TXT_KRB5_DES_192_CBC3_MD5 SSL3_TXT_KRB5_DES_192_CBC3_MD5       
#define SSL_TXT_KRB5_RC4_128_MD5      SSL3_TXT_KRB5_RC4_128_MD5
#define SSL_TXT_KRB5_IDEA_128_CBC_MD5 SSL3_TXT_KRB5_IDEA_128_CBC_MD5 

#define SSL_TXT_KRB5_DES_40_CBC_SHA   SSL3_TXT_KRB5_DES_40_CBC_SHA 
#define SSL_TXT_KRB5_RC2_40_CBC_SHA   SSL3_TXT_KRB5_RC2_40_CBC_SHA 
#define SSL_TXT_KRB5_RC4_40_SHA	      SSL3_TXT_KRB5_RC4_40_SHA
#define SSL_TXT_KRB5_DES_40_CBC_MD5   SSL3_TXT_KRB5_DES_40_CBC_MD5 
#define SSL_TXT_KRB5_RC2_40_CBC_MD5   SSL3_TXT_KRB5_RC2_40_CBC_MD5 
#define SSL_TXT_KRB5_RC4_40_MD5	      SSL3_TXT_KRB5_RC4_40_MD5

#define SSL_TXT_KRB5_DES_40_CBC_SHA   SSL3_TXT_KRB5_DES_40_CBC_SHA
#define SSL_TXT_KRB5_DES_40_CBC_MD5   SSL3_TXT_KRB5_DES_40_CBC_MD5
#define SSL_TXT_KRB5_DES_64_CBC_SHA   SSL3_TXT_KRB5_DES_64_CBC_SHA
#define SSL_TXT_KRB5_DES_64_CBC_MD5   SSL3_TXT_KRB5_DES_64_CBC_MD5
#define SSL_TXT_KRB5_DES_192_CBC3_SHA SSL3_TXT_KRB5_DES_192_CBC3_SHA
#define SSL_TXT_KRB5_DES_192_CBC3_MD5 SSL3_TXT_KRB5_DES_192_CBC3_MD5
#define SSL_MAX_KRB5_PRINCIPAL_LENGTH  256

#define SSL_MAX_SSL_SESSION_ID_LENGTH		32
#define SSL_MAX_SID_CTX_LENGTH			32

#define SSL_MIN_RSA_MODULUS_LENGTH_IN_BYTES	(512/8)
#define SSL_MAX_KEY_ARG_LENGTH			8
#define SSL_MAX_MASTER_KEY_LENGTH		48


/* These are used to specify which ciphers to use and not to use */

#define SSL_TXT_EXP40		"EXPORT40"
#define SSL_TXT_EXP56		"EXPORT56"
#define SSL_TXT_LOW		"LOW"
#define SSL_TXT_MEDIUM		"MEDIUM"
#define SSL_TXT_HIGH		"HIGH"
#define SSL_TXT_FIPS		"FIPS"

#define SSL_TXT_kFZA		"kFZA" /* unused! */
#define	SSL_TXT_aFZA		"aFZA" /* unused! */
#define SSL_TXT_eFZA		"eFZA" /* unused! */
#define SSL_TXT_FZA		"FZA"  /* unused! */

#define	SSL_TXT_aNULL		"aNULL"
#define	SSL_TXT_eNULL		"eNULL"
#define	SSL_TXT_NULL		"NULL"

#define SSL_TXT_kRSA		"kRSA"
#define SSL_TXT_kDHr		"kDHr" /* no such ciphersuites supported! */
#define SSL_TXT_kDHd		"kDHd" /* no such ciphersuites supported! */
#define SSL_TXT_kDH 		"kDH"  /* no such ciphersuites supported! */
#define SSL_TXT_kEDH		"kEDH"
#define SSL_TXT_kKRB5     	"kKRB5"
#define SSL_TXT_kECDHr		"kECDHr"
#define SSL_TXT_kECDHe		"kECDHe"
#define SSL_TXT_kECDH		"kECDH"
#define SSL_TXT_kEECDH		"kEECDH"
#define SSL_TXT_kPSK            "kPSK"
#define SSL_TXT_kGOST		"kGOST"
#define SSL_TXT_kSRP		"kSRP"

#define	SSL_TXT_aRSA		"aRSA"
#define	SSL_TXT_aDSS		"aDSS"
#define	SSL_TXT_aDH		"aDH" /* no such ciphersuites supported! */
#define	SSL_TXT_aECDH		"aECDH"
#define SSL_TXT_aKRB5     	"aKRB5"
#define SSL_TXT_aECDSA		"aECDSA"
#define SSL_TXT_aPSK            "aPSK"
#define SSL_TXT_aGOST94	"aGOST94"
#define SSL_TXT_aGOST01 "aGOST01"
#define SSL_TXT_aGOST  "aGOST"

#define	SSL_TXT_DSS		"DSS"
#define SSL_TXT_DH		"DH"
#define SSL_TXT_EDH		"EDH" /* same as "kEDH:-ADH" */
#define SSL_TXT_ADH		"ADH"
#define SSL_TXT_RSA		"RSA"
#define SSL_TXT_ECDH		"ECDH"
#define SSL_TXT_EECDH		"EECDH" /* same as "kEECDH:-AECDH" */
#define SSL_TXT_AECDH		"AECDH"
#define SSL_TXT_ECDSA		"ECDSA"
#define SSL_TXT_KRB5      	"KRB5"
#define SSL_TXT_PSK             "PSK"
#define SSL_TXT_SRP		"SRP"

#define SSL_TXT_DES		"DES"
#define SSL_TXT_3DES		"3DES"
#define SSL_TXT_RC4		"RC4"
#define SSL_TXT_RC2		"RC2"
#define SSL_TXT_IDEA		"IDEA"
#define SSL_TXT_SEED		"SEED"
#define SSL_TXT_AES128		"AES128"
#define SSL_TXT_AES256		"AES256"
#define SSL_TXT_AES		"AES"
#define SSL_TXT_AES_GCM		"AESGCM"
#define SSL_TXT_CAMELLIA128	"CAMELLIA128"
#define SSL_TXT_CAMELLIA256	"CAMELLIA256"
#define SSL_TXT_CAMELLIA	"CAMELLIA"

#define SSL_TXT_MD5		"MD5"
#define SSL_TXT_SHA1		"SHA1"
#define SSL_TXT_SHA		"SHA" /* same as "SHA1" */
#define SSL_TXT_GOST94		"GOST94" 
#define SSL_TXT_GOST89MAC		"GOST89MAC" 
#define SSL_TXT_SHA256		"SHA256"
#define SSL_TXT_SHA384		"SHA384"

#define SSL_TXT_SSLV2		"SSLv2"
#define SSL_TXT_SSLV3		"SSLv3"
#define SSL_TXT_TLSV1		"TLSv1"
#define SSL_TXT_TLSV1_1		"TLSv1.1"
#define SSL_TXT_TLSV1_2		"TLSv1.2"

#define SSL_TXT_EXP		"EXP"
#define SSL_TXT_EXPORT		"EXPORT"

#define SSL_TXT_ALL		"ALL"

/*
 * COMPLEMENTOF* definitions. These identifiers are used to (de-select)
 * ciphers normally not being used.
 * Example: "RC4" will activate all ciphers using RC4 including ciphers
 * without authentication, which would normally disabled by DEFAULT (due
 * the "!ADH" being part of default). Therefore "RC4:!COMPLEMENTOFDEFAULT"
 * will make sure that it is also disabled in the specific selection.
 * COMPLEMENTOF* identifiers are portable between version, as adjustments
 * to the default cipher setup will also be included here.
 *
 * COMPLEMENTOFDEFAULT does not experience the same special treatment that
 * DEFAULT gets, as only selection is being done and no sorting as needed
 * for DEFAULT.
 */
#define SSL_TXT_CMPALL		"COMPLEMENTOFALL"
#define SSL_TXT_CMPDEF		"COMPLEMENTOFDEFAULT"

/* The following cipher list is used by default.
 * It also is substituted when an application-defined cipher list string
 * starts with 'DEFAULT'. */
#define SSL_DEFAULT_CIPHER_LIST	"ALL:!aNULL:!eNULL:!SSLv2"
/* As of OpenSSL 1.0.0, ssl_create_cipher_list() in ssl/ssl_ciph.c always
 * starts with a reasonable order, and all we have to do for DEFAULT is
 * throwing out anonymous and unencrypted ciphersuites!
 * (The latter are not actually enabled by ALL, but "ALL:RSA" would enable
 * some of them.)
 */

/* Used in SSL_set_shutdown()/SSL_get_shutdown(); */
#define SSL_SENT_SHUTDOWN	1
#define SSL_RECEIVED_SHUTDOWN	2

#ifdef __cplusplus
}
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#if (defined(OPENSSL_NO_RSA) || defined(OPENSSL_NO_MD5)) && !defined(OPENSSL_NO_SSL2)
#define OPENSSL_NO_SSL2
#endif

#define SSL_FILETYPE_ASN1	X509_FILETYPE_ASN1
#define SSL_FILETYPE_PEM	X509_FILETYPE_PEM

/* This is needed to stop compilers complaining about the
 * 'struct ssl_st *' function parameters used to prototype callbacks
 * in SSL_CTX. */
typedef struct ssl_st *ssl_crock_st;
typedef struct tls_session_ticket_ext_st TLS_SESSION_TICKET_EXT;
typedef struct ssl_method_st SSL_METHOD;
typedef struct ssl_cipher_st SSL_CIPHER;
typedef struct ssl_session_st SSL_SESSION;

DECLARE_STACK_OF(SSL_CIPHER)

/* SRTP protection profiles for use with the use_srtp extension (RFC 5764)*/
typedef struct srtp_protection_profile_st
       {
       const char *name;
       unsigned long id;
       } SRTP_PROTECTION_PROFILE;

DECLARE_STACK_OF(SRTP_PROTECTION_PROFILE)

typedef int (*tls_session_ticket_ext_cb_fn)(SSL *s, const unsigned char *data, int len, void *arg);
typedef int (*tls_session_secret_cb_fn)(SSL *s, void *secret, int *secret_len, STACK_OF(SSL_CIPHER) *peer_ciphers, SSL_CIPHER **cipher, void *arg);


#ifndef OPENSSL_NO_SSL_INTERN

/* used to hold info on the particular ciphers used */
struct ssl_cipher_st
	{
	int valid;
	const char *name;		/* text name */
	unsigned long id;		/* id, 4 bytes, first is version */

	/* changed in 0.9.9: these four used to be portions of a single value 'algorithms' */
	unsigned long algorithm_mkey;	/* key exchange algorithm */
	unsigned long algorithm_auth;	/* server authentication */
	unsigned long algorithm_enc;	/* symmetric encryption */
	unsigned long algorithm_mac;	/* symmetric authentication */
	unsigned long algorithm_ssl;	/* (major) protocol version */

	unsigned long algo_strength;	/* strength and export flags */
	unsigned long algorithm2;	/* Extra flags */
	int strength_bits;		/* Number of bits really used */
	int alg_bits;			/* Number of bits for algorithm */
	};


/* Used to hold functions for SSLv2 or SSLv3/TLSv1 functions */
struct ssl_method_st
	{
	int version;
	int (*ssl_new)(SSL *s);
	void (*ssl_clear)(SSL *s);
	void (*ssl_free)(SSL *s);
	int (*ssl_accept)(SSL *s);
	int (*ssl_connect)(SSL *s);
	int (*ssl_read)(SSL *s,void *buf,int len);
	int (*ssl_peek)(SSL *s,void *buf,int len);
	int (*ssl_write)(SSL *s,const void *buf,int len);
	int (*ssl_shutdown)(SSL *s);
	int (*ssl_renegotiate)(SSL *s);
	int (*ssl_renegotiate_check)(SSL *s);
	long (*ssl_get_message)(SSL *s, int st1, int stn, int mt, long
		max, int *ok);
	int (*ssl_read_bytes)(SSL *s, int type, unsigned char *buf, int len, 
		int peek);
	int (*ssl_write_bytes)(SSL *s, int type, const void *buf_, int len);
	int (*ssl_dispatch_alert)(SSL *s);
	long (*ssl_ctrl)(SSL *s,int cmd,long larg,void *parg);
	long (*ssl_ctx_ctrl)(SSL_CTX *ctx,int cmd,long larg,void *parg);
	const SSL_CIPHER *(*get_cipher_by_char)(const unsigned char *ptr);
	int (*put_cipher_by_char)(const SSL_CIPHER *cipher,unsigned char *ptr);
	int (*ssl_pending)(const SSL *s);
	int (*num_ciphers)(void);
	const SSL_CIPHER *(*get_cipher)(unsigned ncipher);
	const struct ssl_method_st *(*get_ssl_method)(int version);
	long (*get_timeout)(void);
	struct ssl3_enc_method *ssl3_enc; /* Extra SSLv3/TLS stuff */
	int (*ssl_version)(void);
	long (*ssl_callback_ctrl)(SSL *s, int cb_id, void (*fp)(void));
	long (*ssl_ctx_callback_ctrl)(SSL_CTX *s, int cb_id, void (*fp)(void));
	};

/* Lets make this into an ASN.1 type structure as follows
 * SSL_SESSION_ID ::= SEQUENCE {
 *	version 		INTEGER,	-- structure version number
 *	SSLversion 		INTEGER,	-- SSL version number
 *	Cipher 			OCTET STRING,	-- the 3 byte cipher ID
 *	Session_ID 		OCTET STRING,	-- the Session ID
 *	Master_key 		OCTET STRING,	-- the master key
 *	KRB5_principal		OCTET STRING	-- optional Kerberos principal
 *	Key_Arg [ 0 ] IMPLICIT	OCTET STRING,	-- the optional Key argument
 *	Time [ 1 ] EXPLICIT	INTEGER,	-- optional Start Time
 *	Timeout [ 2 ] EXPLICIT	INTEGER,	-- optional Timeout ins seconds
 *	Peer [ 3 ] EXPLICIT	X509,		-- optional Peer Certificate
 *	Session_ID_context [ 4 ] EXPLICIT OCTET STRING,   -- the Session ID context
 *	Verify_result [ 5 ] EXPLICIT INTEGER,   -- X509_V_... code for `Peer'
 *	HostName [ 6 ] EXPLICIT OCTET STRING,   -- optional HostName from servername TLS extension 
 *	PSK_identity_hint [ 7 ] EXPLICIT OCTET STRING, -- optional PSK identity hint
 *	PSK_identity [ 8 ] EXPLICIT OCTET STRING,  -- optional PSK identity
 *	Ticket_lifetime_hint [9] EXPLICIT INTEGER, -- server's lifetime hint for session ticket
 *	Ticket [10]             EXPLICIT OCTET STRING, -- session ticket (clients only)
 *	Compression_meth [11]   EXPLICIT OCTET STRING, -- optional compression method
 *	SRP_username [ 12 ] EXPLICIT OCTET STRING -- optional SRP username
 *	}
 * Look in ssl/ssl_asn1.c for more details
 * I'm using EXPLICIT tags so I can read the damn things using asn1parse :-).
 */
struct ssl_session_st
	{
	int ssl_version;	/* what ssl version session info is
				 * being kept in here? */

	/* only really used in SSLv2 */
	unsigned int key_arg_length;
	unsigned char key_arg[SSL_MAX_KEY_ARG_LENGTH];
	int master_key_length;
	unsigned char master_key[SSL_MAX_MASTER_KEY_LENGTH];
	/* session_id - valid? */
	unsigned int session_id_length;
	unsigned char session_id[SSL_MAX_SSL_SESSION_ID_LENGTH];
	/* this is used to determine whether the session is being reused in
	 * the appropriate context. It is up to the application to set this,
	 * via SSL_new */
	unsigned int sid_ctx_length;
	unsigned char sid_ctx[SSL_MAX_SID_CTX_LENGTH];

#ifndef OPENSSL_NO_KRB5
        unsigned int krb5_client_princ_len;
        unsigned char krb5_client_princ[SSL_MAX_KRB5_PRINCIPAL_LENGTH];
#endif /* OPENSSL_NO_KRB5 */
#ifndef OPENSSL_NO_PSK
	char *psk_identity_hint;
	char *psk_identity;
#endif
	int not_resumable;

	/* The cert is the certificate used to establish this connection */
	struct sess_cert_st /* SESS_CERT */ *sess_cert;

	/* This is the cert for the other end.
	 * On clients, it will be the same as sess_cert->peer_key->x509
	 * (the latter is not enough as sess_cert is not retained
	 * in the external representation of sessions, see ssl_asn1.c). */
	X509 *peer;
	/* when app_verify_callback accepts a session where the peer's certificate
	 * is not ok, we must remember the error for session reuse: */
	long verify_result; /* only for servers */

	int references;
	long timeout;
	long time;

	unsigned int compress_meth;	/* Need to lookup the method */

	const SSL_CIPHER *cipher;
	unsigned long cipher_id;	/* when ASN.1 loaded, this
					 * needs to be used to load
					 * the 'cipher' structure */

	STACK_OF(SSL_CIPHER) *ciphers; /* shared ciphers? */

	CRYPTO_EX_DATA ex_data; /* application specific data */

	/* These are used to make removal of session-ids more
	 * efficient and to implement a maximum cache size. */
	struct ssl_session_st *prev,*next;
#ifndef OPENSSL_NO_TLSEXT
	char *tlsext_hostname;
#ifndef OPENSSL_NO_EC
	size_t tlsext_ecpointformatlist_length;
	unsigned char *tlsext_ecpointformatlist; /* peer's list */
	size_t tlsext_ellipticcurvelist_length;
	unsigned char *tlsext_ellipticcurvelist; /* peer's list */
#endif /* OPENSSL_NO_EC */
	/* RFC4507 info */
	unsigned char *tlsext_tick;	/* Session ticket */
	size_t	tlsext_ticklen;		/* Session ticket length */	
	long tlsext_tick_lifetime_hint;	/* Session lifetime hint in seconds */
#endif
#ifndef OPENSSL_NO_SRP
	char *srp_username;
#endif
	};

#endif

#define SSL_OP_MICROSOFT_SESS_ID_BUG			0x00000001L
#define SSL_OP_NETSCAPE_CHALLENGE_BUG			0x00000002L
/* Allow initial connection to servers that don't support RI */
#define SSL_OP_LEGACY_SERVER_CONNECT			0x00000004L
#define SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG		0x00000008L
#define SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG		0x00000010L
#define SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER		0x00000020L
#define SSL_OP_MSIE_SSLV2_RSA_PADDING			0x00000040L /* no effect since 0.9.7h and 0.9.8b */
#define SSL_OP_SSLEAY_080_CLIENT_DH_BUG			0x00000080L
#define SSL_OP_TLS_D5_BUG				0x00000100L
#define SSL_OP_TLS_BLOCK_PADDING_BUG			0x00000200L

/* Disable SSL 3.0/TLS 1.0 CBC vulnerability workaround that was added
 * in OpenSSL 0.9.6d.  Usually (depending on the application protocol)
 * the workaround is not needed.  Unfortunately some broken SSL/TLS
 * implementations cannot handle it at all, which is why we include
 * it in SSL_OP_ALL. */
#define SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS              0x00000800L /* added in 0.9.6e */

/* SSL_OP_ALL: various bug workarounds that should be rather harmless.
 *             This used to be 0x000FFFFFL before 0.9.7. */
#define SSL_OP_ALL					0x80000BFFL

/* DTLS options */
#define SSL_OP_NO_QUERY_MTU                 0x00001000L
/* Turn on Cookie Exchange (on relevant for servers) */
#define SSL_OP_COOKIE_EXCHANGE              0x00002000L
/* Don't use RFC4507 ticket extension */
#define SSL_OP_NO_TICKET	            0x00004000L
/* Use Cisco's "speshul" version of DTLS_BAD_VER (as client)  */
#define SSL_OP_CISCO_ANYCONNECT		    0x00008000L

/* As server, disallow session resumption on renegotiation */
#define SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION	0x00010000L
/* Don't use compression even if supported */
#define SSL_OP_NO_COMPRESSION				0x00020000L
/* Permit unsafe legacy renegotiation */
#define SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION	0x00040000L
/* If set, always create a new key when using tmp_ecdh parameters */
#define SSL_OP_SINGLE_ECDH_USE				0x00080000L
/* If set, always create a new key when using tmp_dh parameters */
#define SSL_OP_SINGLE_DH_USE				0x00100000L
/* Set to always use the tmp_rsa key when doing RSA operations,
 * even when this violates protocol specs */
#define SSL_OP_EPHEMERAL_RSA				0x00200000L
/* Set on servers to choose the cipher according to the server's
 * preferences */
#define SSL_OP_CIPHER_SERVER_PREFERENCE			0x00400000L
/* If set, a server will allow a client to issue a SSLv3.0 version number
 * as latest version supported in the premaster secret, even when TLSv1.0
 * (version 3.1) was announced in the client hello. Normally this is
 * forbidden to prevent version rollback attacks. */
#define SSL_OP_TLS_ROLLBACK_BUG				0x00800000L

#define SSL_OP_NO_SSLv2					0x01000000L
#define SSL_OP_NO_SSLv3					0x02000000L
#define SSL_OP_NO_TLSv1					0x04000000L
#define SSL_OP_NO_TLSv1_2				0x08000000L
#define SSL_OP_NO_TLSv1_1				0x10000000L

/* These next two were never actually used for anything since SSLeay
 * zap so we have some more flags.
 */
/* The next flag deliberately changes the ciphertest, this is a check
 * for the PKCS#1 attack */
#define SSL_OP_PKCS1_CHECK_1				0x0
#define SSL_OP_PKCS1_CHECK_2				0x0

#define SSL_OP_NETSCAPE_CA_DN_BUG			0x20000000L
#define SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG		0x40000000L
/* Make server add server-hello extension from early version of
 * cryptopro draft, when GOST ciphersuite is negotiated. 
 * Required for interoperability with CryptoPro CSP 3.x 
 */
#define SSL_OP_CRYPTOPRO_TLSEXT_BUG			0x80000000L

/* Allow SSL_write(..., n) to return r with 0 < r < n (i.e. report success
 * when just a single record has been written): */
#define SSL_MODE_ENABLE_PARTIAL_WRITE       0x00000001L
/* Make it possible to retry SSL_write() with changed buffer location
 * (buffer contents must stay the same!); this is not the default to avoid
 * the misconception that non-blocking SSL_write() behaves like
 * non-blocking write(): */
#define SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER 0x00000002L
/* Never bother the application with retries if the transport
 * is blocking: */
#define SSL_MODE_AUTO_RETRY 0x00000004L
/* Don't attempt to automatically build certificate chain */
#define SSL_MODE_NO_AUTO_CHAIN 0x00000008L
/* Save RAM by releasing read and write buffers when they're empty. (SSL3 and
 * TLS only.)  "Released" buffers are put onto a free-list in the context
 * or just freed (depending on the context's setting for freelist_max_len). */
#define SSL_MODE_RELEASE_BUFFERS 0x00000010L

/* Note: SSL[_CTX]_set_{options,mode} use |= op on the previous value,
 * they cannot be used to clear bits. */

#define SSL_CTX_set_options(ctx,op) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_OPTIONS,(op),NULL)
#define SSL_CTX_clear_options(ctx,op) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_CLEAR_OPTIONS,(op),NULL)
#define SSL_CTX_get_options(ctx) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_OPTIONS,0,NULL)
#define SSL_set_options(ssl,op) \
	SSL_ctrl((ssl),SSL_CTRL_OPTIONS,(op),NULL)
#define SSL_clear_options(ssl,op) \
	SSL_ctrl((ssl),SSL_CTRL_CLEAR_OPTIONS,(op),NULL)
#define SSL_get_options(ssl) \
        SSL_ctrl((ssl),SSL_CTRL_OPTIONS,0,NULL)

#define SSL_CTX_set_mode(ctx,op) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_MODE,(op),NULL)
#define SSL_CTX_clear_mode(ctx,op) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_CLEAR_MODE,(op),NULL)
#define SSL_CTX_get_mode(ctx) \
	SSL_CTX_ctrl((ctx),SSL_CTRL_MODE,0,NULL)
#define SSL_clear_mode(ssl,op) \
	SSL_ctrl((ssl),SSL_CTRL_CLEAR_MODE,(op),NULL)
#define SSL_set_mode(ssl,op) \
	SSL_ctrl((ssl),SSL_CTRL_MODE,(op),NULL)
#define SSL_get_mode(ssl) \
        SSL_ctrl((ssl),SSL_CTRL_MODE,0,NULL)
#define SSL_set_mtu(ssl, mtu) \
        SSL_ctrl((ssl),SSL_CTRL_SET_MTU,(mtu),NULL)

#define SSL_get_secure_renegotiation_support(ssl) \
	SSL_ctrl((ssl), SSL_CTRL_GET_RI_SUPPORT, 0, NULL)

#ifndef OPENSSL_NO_HEARTBEATS
#define SSL_heartbeat(ssl) \
        SSL_ctrl((ssl),SSL_CTRL_TLS_EXT_SEND_HEARTBEAT,0,NULL)
#endif

void SSL_CTX_set_msg_callback(SSL_CTX *ctx, void (*cb)(int write_p, int version, int content_type, const void *buf, size_t len, SSL *ssl, void *arg));
void SSL_set_msg_callback(SSL *ssl, void (*cb)(int write_p, int version, int content_type, const void *buf, size_t len, SSL *ssl, void *arg));
#define SSL_CTX_set_msg_callback_arg(ctx, arg) SSL_CTX_ctrl((ctx), SSL_CTRL_SET_MSG_CALLBACK_ARG, 0, (arg))
#define SSL_set_msg_callback_arg(ssl, arg) SSL_ctrl((ssl), SSL_CTRL_SET_MSG_CALLBACK_ARG, 0, (arg))

#ifndef OPENSSL_NO_SRP

#ifndef OPENSSL_NO_SSL_INTERN

typedef struct srp_ctx_st
	{
	/* param for all the callbacks */
	void *SRP_cb_arg;
	/* set client Hello login callback */
	int (*TLS_ext_srp_username_callback)(SSL *, int *, void *);
	/* set SRP N/g param callback for verification */
	int (*SRP_verify_param_callback)(SSL *, void *);
	/* set SRP client passwd callback */
	char *(*SRP_give_srp_client_pwd_callback)(SSL *, void *);

	char *login;
	BIGNUM *N,*g,*s,*B,*A;
	BIGNUM *a,*b,*v;
	char *info;
	int strength;

	unsigned long srp_Mask;
	} SRP_CTX;

#endif

/* see tls_srp.c */
int SSL_SRP_CTX_init(SSL *s);
int SSL_CTX_SRP_CTX_init(SSL_CTX *ctx);
int SSL_SRP_CTX_free(SSL *ctx);
int SSL_CTX_SRP_CTX_free(SSL_CTX *ctx);
int SSL_srp_server_param_with_username(SSL *s, int *ad);
int SRP_generate_server_master_secret(SSL *s,unsigned char *master_key);
int SRP_Calc_A_param(SSL *s);
int SRP_generate_client_master_secret(SSL *s,unsigned char *master_key);

#endif

#if defined(OPENSSL_SYS_MSDOS) && !defined(OPENSSL_SYS_WIN32)
#define SSL_MAX_CERT_LIST_DEFAULT 1024*30 /* 30k max cert list :-) */
#else
#define SSL_MAX_CERT_LIST_DEFAULT 1024*100 /* 100k max cert list :-) */
#endif

#define SSL_SESSION_CACHE_MAX_SIZE_DEFAULT	(1024*20)

/* This callback type is used inside SSL_CTX, SSL, and in the functions that set
 * them. It is used to override the generation of SSL/TLS session IDs in a
 * server. Return value should be zero on an error, non-zero to proceed. Also,
 * callbacks should themselves check if the id they generate is unique otherwise
 * the SSL handshake will fail with an error - callbacks can do this using the
 * 'ssl' value they're passed by;
 *      SSL_has_matching_session_id(ssl, id, *id_len)
 * The length value passed in is set at the maximum size the session ID can be.
 * In SSLv2 this is 16 bytes, whereas SSLv3/TLSv1 it is 32 bytes. The callback
 * can alter this length to be less if desired, but under SSLv2 session IDs are
 * supposed to be fixed at 16 bytes so the id will be padded after the callback
 * returns in this case. It is also an error for the callback to set the size to
 * zero. */
typedef int (*GEN_SESSION_CB)(const SSL *ssl, unsigned char *id,
				unsigned int *id_len);

typedef struct ssl_comp_st SSL_COMP;

#ifndef OPENSSL_NO_SSL_INTERN

struct ssl_comp_st
	{
	int id;
	const char *name;
#ifndef OPENSSL_NO_COMP
	COMP_METHOD *method;
#else
	char *method;
#endif
	};

DECLARE_STACK_OF(SSL_COMP)
DECLARE_LHASH_OF(SSL_SESSION);

struct ssl_ctx_st
	{
	const SSL_METHOD *method;

	STACK_OF(SSL_CIPHER) *cipher_list;
	/* same as above but sorted for lookup */
	STACK_OF(SSL_CIPHER) *cipher_list_by_id;

	struct x509_store_st /* X509_STORE */ *cert_store;
	LHASH_OF(SSL_SESSION) *sessions;
	/* Most session-ids that will be cached, default is
	 * SSL_SESSION_CACHE_MAX_SIZE_DEFAULT. 0 is unlimited. */
	unsigned long session_cache_size;
	struct ssl_session_st *session_cache_head;
	struct ssl_session_st *session_cache_tail;

	/* This can have one of 2 values, ored together,
	 * SSL_SESS_CACHE_CLIENT,
	 * SSL_SESS_CACHE_SERVER,
	 * Default is SSL_SESSION_CACHE_SERVER, which means only
	 * SSL_accept which cache SSL_SESSIONS. */
	int session_cache_mode;

	/* If timeout is not 0, it is the default timeout value set
	 * when SSL_new() is called.  This has been put in to make
	 * life easier to set things up */
	long session_timeout;

	/* If this callback is not null, it will be called each
	 * time a session id is added to the cache.  If this function
	 * returns 1, it means that the callback will do a
	 * SSL_SESSION_free() when it has finished using it.  Otherwise,
	 * on 0, it means the callback has finished with it.
	 * If remove_session_cb is not null, it will be called when
	 * a session-id is removed from the cache.  After the call,
	 * OpenSSL will SSL_SESSION_free() it. */
	int (*new_session_cb)(struct ssl_st *ssl,SSL_SESSION *sess);
	void (*remove_session_cb)(struct ssl_ctx_st *ctx,SSL_SESSION *sess);
	SSL_SESSION *(*get_session_cb)(struct ssl_st *ssl,
		unsigned char *data,int len,int *copy);

	struct
		{
		int sess_connect;	/* SSL new conn - started */
		int sess_connect_renegotiate;/* SSL reneg - requested */
		int sess_connect_good;	/* SSL new conne/reneg - finished */
		int sess_accept;	/* SSL new accept - started */
		int sess_accept_renegotiate;/* SSL reneg - requested */
		int sess_accept_good;	/* SSL accept/reneg - finished */
		int sess_miss;		/* session lookup misses  */
		int sess_timeout;	/* reuse attempt on timeouted session */
		int sess_cache_full;	/* session removed due to full cache */
		int sess_hit;		/* session reuse actually done */
		int sess_cb_hit;	/* session-id that was not
					 * in the cache was
					 * passed back via the callback.  This
					 * indicates that the application is
					 * supplying session-id's from other
					 * processes - spooky :-) */
		} stats;

	int references;

	/* if defined, these override the X509_verify_cert() calls */
	int (*app_verify_callback)(X509_STORE_CTX *, void *);
	void *app_verify_arg;
	/* before OpenSSL 0.9.7, 'app_verify_arg' was ignored
	 * ('app_verify_callback' was called with just one argument) */

	/* Default password callback. */
	pem_password_cb *default_passwd_callback;

	/* Default password callback user data. */
	void *default_passwd_callback_userdata;

	/* get client cert callback */
	int (*client_cert_cb)(SSL *ssl, X509 **x509, EVP_PKEY **pkey);

    /* cookie generate callback */
    int (*app_gen_cookie_cb)(SSL *ssl, unsigned char *cookie, 
        unsigned int *cookie_len);

    /* verify cookie callback */
    int (*app_verify_cookie_cb)(SSL *ssl, unsigned char *cookie, 
        unsigned int cookie_len);

	CRYPTO_EX_DATA ex_data;

	const EVP_MD *rsa_md5;/* For SSLv2 - name is 'ssl2-md5' */
	const EVP_MD *md5;	/* For SSLv3/TLSv1 'ssl3-md5' */
	const EVP_MD *sha1;   /* For SSLv3/TLSv1 'ssl3->sha1' */

	STACK_OF(X509) *extra_certs;
	STACK_OF(SSL_COMP) *comp_methods; /* stack of SSL_COMP, SSLv3/TLSv1 */


	/* Default values used when no per-SSL value is defined follow */

	void (*info_callback)(const SSL *ssl,int type,int val); /* used if SSL's info_callback is NULL */

	/* what we put in client cert requests */
	STACK_OF(X509_NAME) *client_CA;


	/* Default values to use in SSL structures follow (these are copied by SSL_new) */

	unsigned long options;
	unsigned long mode;
	long max_cert_list;

	struct cert_st /* CERT */ *cert;
	int read_ahead;

	/* callback that allows applications to peek at protocol messages */
	void (*msg_callback)(int write_p, int version, int content_type, const void *buf, size_t len, SSL *ssl, void *arg);
	void *msg_callback_arg;

	int verify_mode;
	unsigned int sid_ctx_length;
	unsigned char sid_ctx[SSL_MAX_SID_CTX_LENGTH];
	int (*default_verify_callback)(int ok,X509_STORE_CTX *ctx); /* called 'verify_callback' in the SSL */

	/* Default generate session ID callback. */
	GEN_SESSION_CB generate_session_id;

	X509_VERIFY_PARAM *param;

#if 0
	int purpose;		/* Purpose setting */
	int trust;		/* Trust setting */
#endif

	int quiet_shutdown;

	/* Maximum amount of data to send in one fragment.
	 * actual record size can be more than this due to
	 * padding and MAC overheads.
	 */
	unsigned int max_send_fragment;

#ifndef OPENSSL_ENGINE
	/* Engine to pass requests for client certs to
	 */
	ENGINE *client_cert_engine;
#endif

#ifndef OPENSSL_NO_TLSEXT
	/* TLS extensions servername callback */
	int (*tlsext_servername_callback)(SSL*, int *, void *);
	void *tlsext_servername_arg;
	/* RFC 4507 session ticket keys */
	unsigned char tlsext_tick_key_name[16];
	unsigned char tlsext_tick_hmac_key[16];
	unsigned char tlsext_tick_aes_key[16];
	/* Callback to support customisation of ticket key setting */
	int (*tlsext_ticket_key_cb)(SSL *ssl,
					unsigned char *name, unsigned char *iv,
					EVP_CIPHER_CTX *ectx,
 					HMAC_CTX *hctx, int enc);

	/* certificate status request info */
	/* Callback for status request */
	int (*tlsext_status_cb)(SSL *ssl, void *arg);
	void *tlsext_status_arg;
	/* draft-rescorla-tls-opaque-prf-input-00.txt information */
	int (*tlsext_opaque_prf_input_callback)(SSL *, void *peerinput, size_t len, void *arg);
	void *tlsext_opaque_prf_input_callback_arg;
#endif

#ifndef OPENSSL_NO_PSK
	char *psk_identity_hint;
	unsigned int (*psk_client_callback)(SSL *ssl, const char *hint, char *identity,
		unsigned int max_identity_len, unsigned char *psk,
		unsigned int max_psk_len);
	unsigned int (*psk_server_callback)(SSL *ssl, const char *identity,
		unsigned char *psk, unsigned int max_psk_len);
#endif

#ifndef OPENSSL_NO_BUF_FREELISTS
#define SSL_MAX_BUF_FREELIST_LEN_DEFAULT 32
	unsigned int freelist_max_len;
	struct ssl3_buf_freelist_st *wbuf_freelist;
	struct ssl3_buf_freelist_st *rbuf_freelist;
#endif
#ifndef OPENSSL_NO_SRP
	SRP_CTX srp_ctx; /* ctx for SRP authentication */
#endif

#ifndef OPENSSL_NO_TLSEXT
# ifndef OPENSSL_NO_NEXTPROTONEG
	/* Next protocol negotiation information */
	/* (for experimental NPN extension). */

	/* For a server, this contains a callback function by which the set of
	 * advertised protocols can be provided. */
	int (*next_protos_advertised_cb)(SSL *s, const unsigned char **buf,
			                 unsigned int *len, void *arg);
	void *next_protos_advertised_cb_arg;
	/* For a client, this contains a callback function that selects the
	 * next protocol from the list provided by the server. */
	int (*next_proto_select_cb)(SSL *s, unsigned char **out,
				    unsigned char *outlen,
				    const unsigned char *in,
				    unsigned int inlen,
				    void *arg);
	void *next_proto_select_cb_arg;
# endif
        /* SRTP profiles we are willing to do from RFC 5764 */
        STACK_OF(SRTP_PROTECTION_PROFILE) *srtp_profiles;  
#endif
	};

#endif

#define SSL_SESS_CACHE_OFF			0x0000
#define SSL_SESS_CACHE_CLIENT			0x0001
#define SSL_SESS_CACHE_SERVER			0x0002
#define SSL_SESS_CACHE_BOTH	(SSL_SESS_CACHE_CLIENT|SSL_SESS_CACHE_SERVER)
#define SSL_SESS_CACHE_NO_AUTO_CLEAR		0x0080
/* enough comments already ... see SSL_CTX_set_session_cache_mode(3) */
#define SSL_SESS_CACHE_NO_INTERNAL_LOOKUP	0x0100
#define SSL_SESS_CACHE_NO_INTERNAL_STORE	0x0200
#define SSL_SESS_CACHE_NO_INTERNAL \
	(SSL_SESS_CACHE_NO_INTERNAL_LOOKUP|SSL_SESS_CACHE_NO_INTERNAL_STORE)

LHASH_OF(SSL_SESSION) *SSL_CTX_sessions(SSL_CTX *ctx);
#define SSL_CTX_sess_number(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_NUMBER,0,NULL)
#define SSL_CTX_sess_connect(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_CONNECT,0,NULL)
#define SSL_CTX_sess_connect_good(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_CONNECT_GOOD,0,NULL)
#define SSL_CTX_sess_connect_renegotiate(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_CONNECT_RENEGOTIATE,0,NULL)
#define SSL_CTX_sess_accept(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_ACCEPT,0,NULL)
#define SSL_CTX_sess_accept_renegotiate(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_ACCEPT_RENEGOTIATE,0,NULL)
#define SSL_CTX_sess_accept_good(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_ACCEPT_GOOD,0,NULL)
#define SSL_CTX_sess_hits(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_HIT,0,NULL)
#define SSL_CTX_sess_cb_hits(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_CB_HIT,0,NULL)
#define SSL_CTX_sess_misses(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_MISSES,0,NULL)
#define SSL_CTX_sess_timeouts(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_TIMEOUTS,0,NULL)
#define SSL_CTX_sess_cache_full(ctx) \
	SSL_CTX_ctrl(ctx,SSL_CTRL_SESS_CACHE_FULL,0,NULL)

void SSL_CTX_sess_set_new_cb(SSL_CTX *ctx, int (*new_session_cb)(struct ssl_st *ssl,SSL_SESSION *sess));
int (*SSL_CTX_sess_get_new_cb(SSL_CTX *ctx))(struct ssl_st *ssl, SSL_SESSION *sess);
void SSL_CTX_sess_set_remove_cb(SSL_CTX *ctx, void (*remove_session_cb)(struct ssl_ctx_st *ctx,SSL_SESSION *sess));
void (*SSL_CTX_sess_get_remove_cb(SSL_CTX *ctx))(struct ssl_ctx_st *ctx, SSL_SESSION *sess);
void SSL_CTX_sess_set_get_cb(SSL_CTX *ctx, SSL_SESSION *(*get_session_cb)(struct ssl_st *ssl, unsigned char *data,int len,int *copy));
SSL_SESSION *(*SSL_CTX_sess_get_get_cb(SSL_CTX *ctx))(struct ssl_st *ssl, unsigned char *Data, int len, int *copy);
void SSL_CTX_set_info_callback(SSL_CTX *ctx, void (*cb)(const SSL *ssl,int type,int val));
void (*SSL_CTX_get_info_callback(SSL_CTX *ctx))(const SSL *ssl,int type,int val);
void SSL_CTX_set_client_cert_cb(SSL_CTX *ctx, int (*client_cert_cb)(SSL *ssl, X509 **x509, EVP_PKEY **pkey));
int (*SSL_CTX_get_client_cert_cb(SSL_CTX *ctx))(SSL *ssl, X509 **x509, EVP_PKEY **pkey);
#ifndef OPENSSL_NO_ENGINE
int SSL_CTX_set_client_cert_engine(SSL_CTX *ctx, ENGINE *e);
#endif
void SSL_CTX_set_cookie_generate_cb(SSL_CTX *ctx, int (*app_gen_cookie_cb)(SSL *ssl, unsigned char *cookie, unsigned int *cookie_len));
void SSL_CTX_set_cookie_verify_cb(SSL_CTX *ctx, int (*app_verify_cookie_cb)(SSL *ssl, unsigned char *cookie, unsigned int cookie_len));
#ifndef OPENSSL_NO_NEXTPROTONEG
void SSL_CTX_set_next_protos_advertised_cb(SSL_CTX *s,
					   int (*cb) (SSL *ssl,
						      const unsigned char **out,
						      unsigned int *outlen,
						      void *arg),
					   void *arg);
void SSL_CTX_set_next_proto_select_cb(SSL_CTX *s,
				      int (*cb) (SSL *ssl,
						 unsigned char **out,
						 unsigned char *outlen,
						 const unsigned char *in,
						 unsigned int inlen,
						 void *arg),
				      void *arg);

int SSL_select_next_proto(unsigned char **out, unsigned char *outlen,
			  const unsigned char *in, unsigned int inlen,
			  const unsigned char *client, unsigned int client_len);
void SSL_get0_next_proto_negotiated(const SSL *s,
				    const unsigned char **data, unsigned *len);

#define OPENSSL_NPN_UNSUPPORTED	0
#define OPENSSL_NPN_NEGOTIATED	1
#define OPENSSL_NPN_NO_OVERLAP	2
#endif

#ifndef OPENSSL_NO_PSK
/* the maximum length of the buffer given to callbacks containing the
 * resulting identity/psk */
#define PSK_MAX_IDENTITY_LEN 128
#define PSK_MAX_PSK_LEN 256
void SSL_CTX_set_psk_client_callback(SSL_CTX *ctx, 
	unsigned int (*psk_client_callback)(SSL *ssl, const char *hint, 
		char *identity, unsigned int max_identity_len, unsigned char *psk,
		unsigned int max_psk_len));
void SSL_set_psk_client_callback(SSL *ssl, 
	unsigned int (*psk_client_callback)(SSL *ssl, const char *hint, 
		char *identity, unsigned int max_identity_len, unsigned char *psk,
		unsigned int max_psk_len));
void SSL_CTX_set_psk_server_callback(SSL_CTX *ctx, 
	unsigned int (*psk_server_callback)(SSL *ssl, const char *identity,
		unsigned char *psk, unsigned int max_psk_len));
void SSL_set_psk_server_callback(SSL *ssl,
	unsigned int (*psk_server_callback)(SSL *ssl, const char *identity,
		unsigned char *psk, unsigned int max_psk_len));
int SSL_CTX_use_psk_identity_hint(SSL_CTX *ctx, const char *identity_hint);
int SSL_use_psk_identity_hint(SSL *s, const char *identity_hint);
const char *SSL_get_psk_identity_hint(const SSL *s);
const char *SSL_get_psk_identity(const SSL *s);
#endif

#define SSL_NOTHING	1
#define SSL_WRITING	2
#define SSL_READING	3
#define SSL_X509_LOOKUP	4

/* These will only be used when doing non-blocking IO */
#define SSL_want_nothing(s)	(SSL_want(s) == SSL_NOTHING)
#define SSL_want_read(s)	(SSL_want(s) == SSL_READING)
#define SSL_want_write(s)	(SSL_want(s) == SSL_WRITING)
#define SSL_want_x509_lookup(s)	(SSL_want(s) == SSL_X509_LOOKUP)

#define SSL_MAC_FLAG_READ_MAC_STREAM 1
#define SSL_MAC_FLAG_WRITE_MAC_STREAM 2

#ifndef OPENSSL_NO_SSL_INTERN

struct ssl_st
	{
	/* protocol version
	 * (one of SSL2_VERSION, SSL3_VERSION, TLS1_VERSION, DTLS1_VERSION)
	 */
	int version;
	int type; /* SSL_ST_CONNECT or SSL_ST_ACCEPT */

	const SSL_METHOD *method; /* SSLv3 */

	/* There are 2 BIO's even though they are normally both the
	 * same.  This is so data can be read and written to different
	 * handlers */

#ifndef OPENSSL_NO_BIO
	BIO *rbio; /* used by SSL_read */
	BIO *wbio; /* used by SSL_write */
	BIO *bbio; /* used during session-id reuse to concatenate
		    * messages */
#else
	char *rbio; /* used by SSL_read */
	char *wbio; /* used by SSL_write */
	char *bbio;
#endif
	/* This holds a variable that indicates what we were doing
	 * when a 0 or -1 is returned.  This is needed for
	 * non-blocking IO so we know what request needs re-doing when
	 * in SSL_accept or SSL_connect */
	int rwstate;

	/* true when we are actually in SSL_accept() or SSL_connect() */
	int in_handshake;
	int (*handshake_func)(SSL *);

	/* Imagine that here's a boolean member "init" that is
	 * switched as soon as SSL_set_{accept/connect}_state
	 * is called for the first time, so that "state" and
	 * "handshake_func"980iĞvñ_ü}µÍPğ¸TÃË¨UI(q6uÏZ¦‹BJSé_&
5m†ÿ;i[
Ñ³ÓwŒCãENõÊ[ä‡D‘É"¤Œí§£;Ùß2mÿï”¥3¯Ñ1ŒÖ¾tN#×CdÍ’æ»õüÀÓ36¬Z9
5aP˜MGŠ‰/JÑ®¬E.¦Çh'.ÒÕ30…Nq?²~ğPá ä5C\|ykjŒh)ˆó»£X–lj!*qá‘"Ô>‘m*]4Å¿t_kß¤»¤0DµÑé‘+€´¤lc‰v6 ¡Ç4¤ÜcmácÎe²Nş”eˆË:XÚ.N§½¸U•U´A=wòs!|üÊ7Ü§¬³rUKJ»{q¹Œ™pß	EÖ]¸ÔA×h–i×•V…¶æˆøR.ºwrjä8Ø Ğî¤<![5Š {cf—’Ù‡ğŸİ-ÂÉ+´“9.»€}w¤	\Ä«`A8÷UÒÄ¶fI>©§} …úÈ~R"²ã¿Ü²•ëÇŞè.­äÒÒ/»ğùÑ_-äw8*}>äÚ`‘ÿñ°²²şï.´÷Kç8jO†€Å¢5›‰ş~lñO•\Ÿ?¤ì¬"îY¿†8”KµM=^’G/rÔ
ùlÓëloáÑë‰tòÚİİ#Ú#¹²º\P¯PŠBT‰5*…½ÉÕüŸtó9;ÏáÁ/‡‚Â_ì’Îç$Í>G/Şï£ƒ¯[LYO¸£ğ´!åÿJëÜ‘Û¡ubœ¦‰÷;m²‰|ãïe*gİô²ĞPö‰û-8bá4Êaüÿˆ]î¬%Üå-aR³3V\Á‚X\¬`ãş§RŸ¦˜'èQïÌ§‡¾èZÙ(}gùşg%“±í‰¶ö‡N„h+è;èïu½JpVY›o¥Îá_ÏÉÂuV­®ÿÅĞ±MP\fMçü ( ñ¥¨lëµû4fĞÕ““¢ÅÎ”4ÕÅrı^„)¯*ˆçCS‰Œ¿›ÙS$g™¢.º.µ;rš×ÕÖJşÅ¬â…Ñ@tf¹¾×R‹+Â”‘’¸dåƒ˜ûœË®ú8òîÿ4—Ø‘Î=“ÈÂ!€>¦~Jtë_G®&¡ íYwëïçÑ
UÛÉ?O)´ä4ÜºTâÓggéş)0Ÿ‘ŸúHµË”2FÇ J¹K´UòÚInĞŒÆƒ§¯ÓÜ·o¦Ú©ò=Û›foşVüë@ø>/i9–TDÅ™<\¶~ğĞ•¨å$-xş(£‡$Œ~¹{)ÜÇõq!« 7à1œ1Ã°ÜRüyr—ßõpÍ)èç'ŞƒÙ±¨æ*2ÿ	ígO…ŒüğèêÁ LİYT9ÃVÈ3fºB{ySëÁï²Êénß +Ü<$]a.ÄOÌŞL¾•úÕhĞ™¼k_âZz¢z^Èù’ÏgáæÃ6YMüÁ¤ëéÈÚÂ¢zg}…§³æãS[Çòg¢9ôIŠ["X///^ğÕyâ`Ï¼À G±¶î»PÎË•î7¤<ÿWú)öªóù=˜Ÿ³E"ØÇúu´ûş«ßíÆ+Ù6İVõËA<·ë%}U5{QÊÑ¡[”0ŸrFfİkş¢#¿çòçò…¡·áóº 7níÓ,lé˜]Ì³OÃ=†~A‘ä@i	İS¤úÅ­`ê“ı²oŞ Z9SÆO2a©RòN¥âµï¾„^)PÁDp±&[`!-†‰9%Eäü…£zœµ2©/©ßâãe[K.RÍ?Ùhê:úfË&²0EFTL7¸Ú{ŠJM™r®¨hR\2Ln_.êÛÛÛã^t–Á3x5MäŠ:÷“ˆ¨à«?Ötœ¯¥G´ÑH·—X¡)˜V¸+&x¨ªæäŞ·z||”?ÂÔnc6ã“æ@ m¿¯gËz¤ŞåvwŞ‘œùmxÿnŞ¦j±(ĞQ@¡££ÃIŠMÄl’>v[ë‘N.Hv3õln?)®?PÍiˆL7ã6Ãèëí#Æ‘Â“‡/ğ® ~QàW;¬]Äø½:9t²ÄÔ¼Û12ëıál<m»[uä½]Q4¬ áıVJi<Û- ckÓË²r”îD@é¬Ç®ÔM>ø•	×!—““/‚:;”íİü‚Z.>ÕÿRäËkíI»À=ŠEVbeauuç˜Ü	´åb¥Êâ/ºÆb+¥<É7Ÿ•°®aâS‡ÙwÒÇRXù•mc·\H
¼W‹Ú˜·BÓÕÔ±R¾ëÊ¶/HÕ”y½A€,é‡Ã¨C: 9qáÁÕe$9Ü»§:™‡uÁ±Ûõíó³
Ïcı8Ïõû›L8‘÷ÃHçÁ?ŒXŸ¿õjüLF˜uhİoó:àüt"¦"Û;~ğÖ†@Ê¾òç6~X­U¨êôàÄœÃı3èyş±=‰‹d‰QÎ7‰·<—ÖõrÏz!ÏDvQÏ«à»0Tâ‰1&Cƒ#]~î8›\Ä´é[€.säĞ÷Ö­q5ñşE,
“®³±/Í¾Œ¢5ù[ ®_É Áæ‰Øz—0£åÎ8g÷ôíuútÚ’ü’m™‘-6®åŠv-K‡i)½«’M?–÷|Y}¬òm¹™‘ó>ÚÚkp&O*vÒÚıa(G¹×†ı:üñóÁ¤nÎÌ–ìÖöÓ¬.udÙâŸ-—üš4g™>¼†LÆ6BZªÊ+ù‰ÍdpÚd™­¯ØğÓÿ¾’ÅÃÍ´¸¥¡Ó„ìÜ'âğğ¡qı–š1}gS»L¼%¿xd`ÜW5ŸúÈº ‡A-fÖĞá'Ájx	ØĞÕÕ½àûË-E›2;_ir<Ûõ¦D6‰ØiµÊÕ¬ü’(E0§‡‡ó¨¬çz³ğµ¶££o«ø¯ëV“CŞö`@¾ÍMêG5^ŸÖ_­m=:üŸZ)‡§À‰íï>ª©›„R£Xi)U4.c0K`Q®ıtlú+Áõİç·¢ÀÊ°U¿çvX™s_í¸KHB@RˆcìFÁö7Q#fº}¯²ßÂßBƒ‚sFùó`³6Ä,ïçÁ¹›}q¹lM2L~gŠp2Å€OÂ's.†L_Ñçe?”i£Ån!‡k:¿VôhÜÓ$,§vï™’Ô+µtîãÈq~º”ÅÈ&š“TÁfÉ)MO#·Ù-™K6¤‘^õ),p
éBáÊ2r¿“ş“61ŸÒu"áûd+-„ı©À`#ÔŞ¥”-$!©i;ˆu£H°ìH«lÆ±T«üC¹Ø”è†3oy4Ñïùìy&c©×^ê×Ö§Óöƒ»'ƒvONªÇ‹îÉá·qÇ¹CÖ‹0X‹Ó#âÓİI?¶´‘÷–.Öq{”"H¹Š_–,†?Ôgvæ ÷;hä¸lï"QzígD¢:´œ½@Ÿ>©ºô—8É…En#šaHÇ"K_îÒvœôœ¬ºÂDı¹¶AfÕ—çÒR'ÖaÇ¦ãû¹ÇyY…Fh£îªYlğ¡j¸
ÑıZ-¨i,_^/$ˆoêÉßé8°5Hséóv’6©^ª%ÀÓ÷BzP¯ªè¦4Õj5a”RªmædP$×²N²m¶e¦Ê\
`tdnÂÂÛbG(5nZ5èì¡x.–«íïƒ>Úl~“¶Gâ*:Ùóe™G„H
…}›ZÏ–FÆéwJCºo•:\õÿW­¡¨ïRµf„T[ò@mÛgäy=³Ú*šKzÆ^/7‰£‘¿˜w˜]Á€şÊæÎ`PD8=šÎ:êÌ÷ß£xì¤å«7 7‚ª…$U)Îş
Õfäù‰=ôÓ­5ä†ÇÔåÒƒ!$ZÄ¶½æşÚrTƒ»şŒj„¨F=i[<£z¶zkâ7Š¡3Á®®¡À_tcWµ"´‡M}hÖ†â~4)t®åV{³Vòu)µ£
MÕrë'®F×ÓöZª¢ıâÛ`5Vôº:ï4¿·+p?R($Yj!¤OÎñ²UWÍXW~«t¦0vn“/p%¯h¼ï’“ˆ­'—¸®%üm•¸ƒÜ ®bjç¦ôd¬oÛ‹Cö¦ÛD»@üÜí›æ¶˜´NÉâ:Ò_Èğun›˜0nH'^àKç÷Ø­y›ÏÄq&1&^V{_®?.Stò7Mjvøìbb­»! û–·É{Ó(W<Ùóßƒ¯ŸüS€Ÿ5ì›;*]Åï2ßÜ>®úíÜäH¸§ø/ÄŸµøm]a;­-´ÿ†Ø„HF$Á[rÙj~ùÊúqX5g+’Èh+G`õ¦ {p=÷«ç—sƒôzı¦‹¿_©LÀ³h¾Mƒpk^}ü•îXT¾©•úM‰ß™OÖ‡›"IòüNY;§¡3’‘[w/\°,İ¬m&™N½mû\©Dƒ¿‡î‡7f<ö#I!t‚«WAİƒ#šÆí]cûe¤D“¤Ù'&&Î¸İ20f“OÂ×­\ÍŸ¦ã×ß{¹—Kœ?rœ<]ñÑ‚5c8æEªêJ„Ò*G/äåtE©Ç0Ùß†Ò*7u¢I™ã"Jîz; ‹#õhŠq¤Ç|®àeó‡.é$bxş³ÚòP8»gC¸Ù³;s%à¡O3uW7]ÔÇF.	ãJm[–*ù2!ïmÄ<¨ëx¥#´ïÁ5GØİçüWUefNÎ7‹¬Öh×Åt=P\vu4t¯C:ÂÏçEÜ57C0M/D3Y(.øvÌ Ñ;Ê¡;şäîwÈŞü=… ÂrÃN}ê¨)$lXşÛÓµ¥TòGZv)ÊÆ0ç—Ã©\FâìÂú®„İ
Òûo‡ Ñi…ö<p\ÉößG¼ú/ñí¡úe‰¶±ZXA)ßx‹ô`M-u?f‚8]Øqµ Ês_—<Ş“a¸ªÄöÀC´•5á%ÈÉÿ“ŞX£¬3¯PTÁîc®yXvšM£ò°|RqÂ„ùG/µ¹Ã©¢¡Ì÷NÊ½‚Ì·£‰ò‚5©ìw<›-¡f¦«{<Z¬š¨†uãÊ))¨ŒiÊÇ£%•Ó‡·£È³3[ªûa*šøäş/trÆS¯°»º6€œ»UˆJ¶Åo­1ra—„÷XvÄ‡«O'Zc(ıÎë3 FÛ%/‹Î·÷¸ÆñK­ú^Ûãñ…CwşY<_Ï–¯ˆ÷\H6<…]óäŒD&£¯< 7O7à®·à¡Æ¾Fêš0>…RĞí:ÕîŒœ¸ÜÙ4îzÓ›H[‘Ìñ@zƒO.òÈò¾º3’/’¤l¡õ.î/ä]àeOi‹Å]ãñ†;¬OªóÀ—©°u‰¨ˆí”€¤™ÃÛŒìÜ½›E£½XÚêš6/Jf—ç_»nÉ×=ünÊã¯Š°5±¤ºŸ:;Î^±¹ÄÄdL;zïüë r(&ˆR¥ÖQC¤E*itÎlÊüË»ÚD¶¨¹èlbibäÖ³§ı$šùOcáÄrh—€tjõ±Z#Lœw4!|Áú#¦¸BùŸ	uêp¬¤=¬î ×1~8cK¸k÷¸CVÎ
Ë´ :	òEşoƒ­õ–/²E’eZ¦¿—v=×baŞÇ«‹_ ·é$””XhúÇ:Õ+ü*LÆï±L¸i©tXÈÙ8+¯éñh™}±ÆXgÈ)-îö™)÷‘F€Y˜¡®ÌóPÎOğhMÊñÛKÒ»Ö²ª‡ô¨+¥ÃŞG_°í1ÆÜÿiXº´åS–òqÇ®Rg¡*W‡VÌk˜d>,j¹ªToXš~ğéîáŸ0@CÁƒ·æ9İÆï§_lã-×Üü)ˆÙ?šLŞÕÃ—ó¿dô4´H×f~âè*:¸Ñ„—£õ™Ê š!Ø·7¦m%jLU°}‹¡¿öçÍc,”·şG›£WôI/*-òpå5¹µıhƒ·=Œ^ou/É¦w±mºÊIÔÈYğ&>Çã’™cü^@|E>¸µ'`¿S³v7-B‹â¿A‰ç–täC'úüî½c[^:ÅÖ£ÿW3·¡±>¤£Xš[CO
°øÆÓİ†—5¼óàŠCgª^çãÛ9¶×şCzë	$8GÔ;CßA¼r²â½óFîûBİßö¹4ñ“«3[Ñ€¡VMsO·P	ÿ·ù•Rë|‘
şj0¿¯ßLŞg/~[[`\‰¶³=j”Yî§fûıQA#ŞFgCœU×qÃƒùóå‹Åhš~­HéÂaâ°·‡5ÜšC>4Ï;Š–S<2­Ööãî0V\ë62 ,©TÊ6ôÃ¿|F\[”º¹Ÿ7‹¿D‹Oª½t¼f;ô¹BVëØäÊ `ÏzºZHÆ)+]ß?ƒv/¥HÅ4~XsP3×å@ârzÇ§ˆ“" Ä›¹—yn°È²G<ìÃ-ëSEÄJ_Ô¤…9½ÛšÔ©Éƒé •Q‹,RÃ}õÉ`½y›ŒõX;æyÃx2t€;Îno7ZŞÍÚÚJt³²:ôğuH<0·Ï*Óa%æî42®¨ª˜¶©Ë×ùTpÛmtåj2ª&dxô¶èˆ)(öÅÎÚb‡<kîj:±DÈYL-9ÈÏc¶æÑÉ©äZuk<¡ÚRñ û„ŸlÃÆñV%Ó=àÌ¯pø“Jp5²¦OebøÉ”cãœ·ªeŸ×ñ«'pc&¿Q„»¹SVkÑŸ4âªr‹e·„ãCtíÙkÖ,Mòèˆ©l6ÙŒŠ›İE£mÑíxÍø RÌ¿6ú«!8¹ŠÌ>Î}——<&As¿¹Äù”Ó,é4pWl~,Üš- éÁ$>]*ÒXy¶/„|"“®ŸÙÔÉ2‰ò+66m$ã^®H&Qjê
CSBBÛdšmÕ…¤¥-ññ^¹«lÚk>/;ŠGãpq„ ±ˆk*Pü¡Y†#c
ş7 yG@'ÜRŞ¦Z=œ1U–:.¿š;¬½;Zëğ¹bTÍ·¼‹côÎ+¯ZL6öOzx€wÛÚnƒUU_Õn<qv8İc:´n‘j[€¹„[3Å$Îı;Ş^Î¤m'û¶?‚Wl`±+6¹8q9‘±•3ßn*Rnø‘«‰¿€x•<]¼m“;ù3×f§çÆp¼b5à¾™ª#Ñï‡Ó‰mŠğãòULÇIU¬±uåªÿ¹€‘¸wm©šæå~d9ay¹‹±qÎ«‰t‰aË¼| ×Ä‚¾‡&s8Ó†zqGÂ¼^}ÁYÙâ7Û/Îß,~Ş­òõ[æ‹÷W¿¬äï”¾¾õ¾"¼™%°Çˆƒ¡-:÷,÷3‚+!­_3[ˆ¶Ú8ˆ+z1fEq¤¾Õ8WÌÒ5¶N™w/j¾ì†HşÂıëS”é¾lïèçWaÈœ~úÁ–¬Oƒö¥úƒ©Ô1V )æWã&ìšÃÕ¼…mãRÑ°¬û˜£şÓaÁû»uÏÖw5ğÓzÑ5ZcÕë¾*¶şşk0ö*ˆM¥9¢7q˜ÈÑİ¡[[DŸØì aEYYÈ‘ª®èü$ê8ìşaœµ¼ãz»ürs•ÔšLü%(\)İjG¡9÷‹¯KßjÁÊ;s¨ÄNÅõ“£KM¤YîGg-ÿ†±0ıniëy	ñsWë¼ŠÎt–J¿ûĞ8–ë‹¸sÖÌ‘{&©µËMÓdN—ññböÎµ…šzÖªªµ[ÔÔªõo»B›LN
k†º®Cq/™œ1£
ĞB <}x“è
­wiŸäAN+Ÿg1wÃ£	†›c^×şMĞ/í{a‹¥º•I–$Îó2Ì
ås4°&$Ñ§Qçu7-=#)Øv‘¬z¥6÷§,[–®âe«éS"•ŸêQßícQN¾¬Co£­†9(†+B[ö‹g…WwuÎqéÆÂJ%üèã¶~÷ëÙ-MZÌ<¤Ú_Q€x2ÌÓEkJ^ MDÚlnNÍOlt½«[›¡[®e×şÍ
Êæ‰àÆH2¸c`ª’WŞD7Kløü q¥É~gº@zÕ÷¬sÁRÖ£R;:3“äuKâqøy!)İxg³KŒœZ4*Z¶ú•¢4˜Şqe/Xx¦ªš+ÒÏñ>ğ¬ù9<Kzÿå.k‰›;w ¨“Ì*™¶ï­`™¹ãÅDƒ—»Èk_ï73öÍÎŒ\¹3~¯¨Á*D¾Xîêñİ JRÚüÌÕÔW˜CTª½ºû™àj	¾J¨ğçî¶Ø‡tÎù&É<ò?áÄ]"cÃÅÎx|6I˜²b·/Ü0ä÷Ø6ÌÎücğZôøPY¹Òô!¨c:¢—cSâÍ¶¶wÏÓgk[9lY°ù¢Tv=4Õı‹´bäØ
RnÂ	£7dIw¥§·µ…–%3–['e0…¶NÕ'&&ş½ì0“Ú?³Æp÷™†ÌbÑ!nÀæê‘MÍ”@nÕäš_8ÑæC~üß,À#'2“¦“µSªÂEóì€÷3^·ìo3¦o˜‚;g:6e;B%ë¿‡SõØÙWµé;ÒÑ¡œÔ¡¿æN^W…9è1 °/²²²;¼–`×ƒi#¿Ã/XJ«V	F ğˆz¬^çO2D-›/p.4òbTÅŸY°7n~§JOM²×®[Of¢¬Jùd¤¬5Å"¶^ö—iß-«W¥düiX×]6ZŒïZqÓ3¢nAtf!h©µ‡'~7Fà‡ i®_D½ëµÒÊ×ç”2300ÖJqi\Î¼ğk7ÊX2+t«†TIS‚6}‚›ÙœÂ#GQ;z¢~²))¡0ÓÛÂìŸ{›s ÂËV}Ô¿€e›Â0[Øõ“˜[aÜ øqˆì#×FéÛŒF¾›w¤Û) Ó(ß¥3NéÙ1öª_úİš?ïY÷Åñ†Hßm"K¸Úä…ãë9ëÀ‰û,ºåèâ¢|=ù×ÑXş+FKİIï¼$:æ½Ø²HÔ°ğğ™³«ößy¡"üÍÓñzklE°•o]ÇJÇd½ã†ø?EË“!¶)-VÎnzSR=’IŒArÛxÁszúEm#´ÕçGèjÎ×çã9¢ş9Å‹ÃS•Ï»ï7†%^f¨v÷m˜ŞÎÓß¤ïÉºßÚAªè¹ !R
%É=Š=kÓz>†X3xæV¨á™I£p/4ß;‘NaârrM7™êêw¬Ù=nj‹IO!UÌSkÔêskğ;LX|QëpÕÌxÓ®ZWÇáÇÙøbaa2q?ä÷¶}èºB¿:½ğ8¨ øTÌLEÇ8g: ›¯S¹øÏcœ¯dIJ$xUuoßäs¡ÚØÏX!)M+',4!“î/y@EêÅVõ*=v2RJE²I½êÅ:½Î4û¬Ì¸¾éEKkhc\¾Uˆ÷Ÿõ³»¦¸ùÙm ×ÖvèåØX”c‡œ-rYÚÆœbƒ]ŞM¹Æ¿mÿ¸8”`+FÖĞÄ'íNz ·äYı'½‘ÌqN'Xëç‹àZMÀIWç¿üØÿîècSwÖZU¡ÅÒ’ıÅ¶láÏÄÔ„D<‚GW£j:äˆŸ´‘ÅŸ®Ä ×@(V+Jx[Yu[ê#»ƒ;÷’­úXï 0¼uyU¬ïİ—Ö†0;ÌR1ùaãÀÚ1†&ğˆËíqóO³Cı%Æ–÷1y5'Zğ?4 Ö1Ğ·¼Úõ*¸ûŠµuÀ÷²¤™b«²Z€êƒn©a]}Ÿ¤IH0·B/*¢MQ”1pi´B/TÁœÉŸC/bŠÈS’"„ú9S[¶àKÕreBa-^&ŸhÏQıòùş™–lŞFHy,›¹Êå_Ÿ+Xú(îœ3mS™l®¸RE~‹¬ ‰\dPU“!H‹‰¼ş0xÄÈ8Š¹`ƒŠ3à3z%¹(Iüï	§<9´ÍÔõ—êí³z®Pzg®”‚™’, ğ‹FbxJiP-Û\< åæz¥ä¾ñ€ï) Î>ËY¾=1Ï®Ü‡Tw¬næoÎ·äššÉ-UÃ®`1¹2-Ş^Çi8ÂÁñÎ³N¢>‘îÇªd5Àd©±ˆİÛhñ˜ÑHÈ.ğj:Éxáü”ßuNÿTË)Ö»´gµî‚/á{'0ïø~|ÍaQv-Oe‡	âúe_˜Úapş<ªqÜ}+ÛF›í}y¯pÉ&-ß‹)Úäükÿj:ø-VÚ26µïÎÏsóf1şb4ş¹w[óyõ}³Ó[¯óÑòŞÌIH,*ù"'ƒ¿íú3…(5Æk™„™S0Ïdä‰×H¥ê€ZÀ¦góıß³W#<a×O§ÜCËRiáàõËë ãQçe¾R£=8’ÆM¹–‘›WrKA[ùôÆãÅII‘7²Eë+µfOmC.[y-Ë‡7¼Š.w##ã§òÄõ)ùŞáU@¤¨ïZ°Õ'²ù2;·­ü@¯³·ÊCIaL£‘š±´ö|FîFHzŸ^¡p ´Í:‡g
^^Ş9}Cİ›$ºÄòòrÉ2mİ*RRx6ë´:÷'K6KsóPŸÎ!õúQúá²»³åN_â?iB*#…š…4‹aZd£~âZÙô¹F? èä‹ÒÌƒµ¼DÂİ!MÂ16ÂpÃ¬¸©$‡§ô$6]1ÿ §ÅtÉåÓê?š( ¬ãåêN'â"şqEƒˆX›¹_Kï¥Oøå½…v xÒôOQrEÓ×K¬¢OÚ>!,5uÅ‡®ÀmJÛòòÀàáàçT<ÛrV>†ª>L)¿ÅŸ.:FFEä!@”½éx³¦Xlš”±ø3Ÿ•ÓÌÎü%Ó,ì²ò
˜“˜Mˆ¥/$âÎgı0ÿî–]ªİ£ógª» ;]bı©ìÅC›OV*ëñçY±‚oÉµ¿zZÏz8Rh½·æ?‚»“ÎœZ'«F4’pï±-Ó…×%j’-W`?Š	BØŠ4ª]·¶Éu³ÍQÍv4…‚™umƒÏDV=Ï|-%”*õ,\LslSƒßc_^ÄæÈõvù?ÔÅÅ9-ºëëï”A7 µÀOjë^\Ù™y£á¶*šhğ+Ñµ!_uô5ËmË§Êa¬G­;–æ¾
*ª1èµ]»b7—õ{Á_ÏlusÍm)À± ğ´±qD¿v;Ì}£ÒÓå~ŞÖïu©´Õc…°I9¦Öñ‹!\û~¶>¾vÙû4ğò÷kGG_øFwvù@AìPµcë—^«Š‡Û¯ã‚.ÜØÚJ·E¢¥ç‰@OÖ·jÀĞî=]lY‰#mğ‘”5´ˆ¢_©uy³ÀŸÉyí§æÛe‰æJ7repıä?L›Ğ×6¶6‚Òk*†}3ÿÓhÓæºXÕèQ¾W]U…¼fæ’§ÿ ›ÅBSü%‡–¶¨8ÛVe¹svÂÿ‰*ãƒõ~Š'«\ëğBêcå+$iÿß&8%qÎâÕôT…cjŒÔıêÇ„C©Hî‹€;/«BŠR((Èb9ZÔu1³&KÜRL­~+”ÎÑ€]RbÔÔ4ÊşÉ‰á\°h2wÍWp¦ÁÚÜVJ¨˜ªo%ÿ	t3Èw—ºÓÉ‡~ù#OBö¹NÖ¹o.<Î´‚>îc1_Œ t’Ã@â\u­ı!©4æÿ®0Sd,^N‘¥î¤ˆ÷»Î–¨@pe&Ù§R—}5§Ëk­Yvà¦ÿòšx¬bfu§OŒÊmE“ˆü"-y^± oÔò€Àò¸Òw…÷ÚÛËqÁ3¤A=»ar[ƒèD†á?bFR”wD°†tü6¯5+hGJÖíì>­´Nedæô‘*¥Û^ŒáNQ¤Q '¢ë¶¨?gVêô¹Š¬qX?½êÙÊÊ{íŒ°Z•“üù’#‰30Øi›ìXÊ’SĞ.ŞóÎ“£<`’Š‹#ÀüDJš…™Ö ¯v:²Æ ^—uIéó=›S]f•\‡â¡SUê+Ÿ—<­çËu4{9iŞIÉ‹tRZ“sx~¥¸…áàsg—2zı«,û3ÃİO§­É³«ŞUm6Dÿl«ãr¬Ü Ch<×s]²Ó¨{*O¬Ÿ‘Ê'ÂÏ+âì-ˆ*&ŒŒViIi²¢qèQê j³F.0ãVÚÑÉ –û._<Ìõö%~/ízL‚"o•UetmBõPIv‰Í ,‘ï[V4ïÖœ©â¿ü¹8o,P…ÁŸĞ`ü~À[ß mu{7zøşp¥´% †Ã
³»Áíp¡U'}–Ù”
ù%Â'c,lw“Öò¶ILõ4QÚ
{:ıLXåß”Ñ…$²ØçLnæbïë4úêí0ÇÄ›Ò‡¥ü²-çbÖŞY•\’ÉZ0Ã½rÒDn#€_ÔHl#0+Û™Gj’4†Ælßj0¶|Ò´qâÖÚúP—4İ¸²îİ¹!$À_ÍU›kÜu¦Ø.2y.Ÿ+úßa½¯·c´9Ö”p´ïªH°%Şå ·mŒÁüô1{‡hÑ7+ß¾^ ¤‡tå/ÚğSÈàæAMj½ºÂwD¬ŠF/c|:£ ÂlÕÛBXÒ“ÈR„qş­tføtåãv¹Ä æz­ª$}õ¾Å÷öHxO%àV8z‚\Õh¶#¦,½ÍÍ¯Š€—s¥çüîÛ'¿óuÑû‚³îäiwI4½Ê/Ú]·x¢o¯ñ5—ó¬tºCç{÷EE•dù^ÆEŒçIî¤ëÄÖóŒŠÀı¯b‡¤=atVXHZJq
CSß=óO¾ÂYòÂ\ÆİzÆgìƒià_Lá²äRCÃ,Ã•Dçt¾©h+„åÔôïuNjıN´BrĞ¬‚†e«K6$[ëfQ&9–Ôƒ»'bôª»}ñn-\Dñíğâ~†q‹z…<é¬İ”13ÍìûK[¹Vç&¸|ãÑÊğr3°†ÑÆõ‰&ë¾‚RìÄ
d:’E’wv$eN'û@LMéû‹"Hê¿\9d^$âÖ±UãÎ•qéòTTU%¸ö™@.©^	‘8×"°Õ‹©İrpÇˆÏlN?c©#³ÀbËı|„6¾ÆE@5G¨·ŞìôB±£©+ç{Ñ3»„…Åo{	XYd ÇÎ´‘&—FæÓGŞTNŞÆª•ˆÊÊú.L–*2Zr"Óî)B0úWY
b§¸E’µ¡È¶;B±šæû'¾w®ã‹sÑOw¾ä¢Î1éjæÃ™I¤lÃZf¾5•£‚‚©æ9ë_Uc+ÖÌum™d.)/9¢WÏ(´å+j«ğ üUn×ÛÏ?ñ»Şÿ«ìéæ™ˆÓ²è‹71;"C®†õ]]§ k–b`EU%KÈ…¹z%³v°€
1„‚"–eAQDD„´5ÎLd­JPB‚ªIÏŞ˜-¥P³V³=ô?}'~9òóuÉ3¾A.·á)_óğ™Ó'îíúƒ¢a™ã‡[pC‘y…»©ö2·F’… ÊSş¿¥&Í ãûèàïK÷é©òeô'ßî<,¶Á€e) šs›IMdĞënPÈô1RsJ¤c 3pX®8ñxOC§ø‰Ã0É³¶¦gWÿ9¡	ÊBš2€É7ø=ÅÖ0¤™iğè’-ƒ<‘©@GAüZúÎùvU&à9ÿYTüQû‡qÈüAôû¤ôgT‡zÙ‡,
$)®¿Ş´[‚¯Î¯£Õ¡sÑÜİçøÎãn™e–!â©	vÜGÊ=®_k'„y—?œX’W¬rE>»ºà«²`*W‡âà…j$X’q}÷ğH›©Åı³ÀR¸ÈPŸdDNdÜFYa3¤DdT?Óv¿ª¨&Ã} `-şáü¹H{˜ä;.uÏÍOL¥m 19ığæéú‰ÂMÛIV”ğË „èfZÏuò4—\WQÇúNıhRŸa®$BÖ²6ÄôEùµ“£øapã•<ßË!MòärSØ‹†
ı ÎÍ0·`úŒ6r	ïqJ/ÜªYpì»«§Éœzpû1fI>•Céú×¹;\+išé…‰£ª‡NãóòÙ%­Äs?1ãnj¿œ®q%øtÍ Å)Hß¡5T¯rè1SIÜS¿_@ßä(.˜$Ñø;ó1¤Bj;C\TÉİ:ze “áG"1âÄ·&*RÛeëÒF5˜89;`¡ œÚÕµh„€]Éß'cG¤A°¼¥ÇX†»®ÍUÅ^ĞŒı„ªñœˆQ)t•ÇÜ/,{Lî0Cu“‰'8ªÌTTÕÿèäÚÆpC>¶3ÿœÊ±(à1‡4€€
¢qu½‚+ƒådå'M+r(&J $¬`uôÏ9æ™ùÄÖ’¥ôlÙRéËµXt‰ÃZ‹ÈñƒÒ¤xæí†²--Úö€ÌÆÆúwé„é}ÿß…œ1îy]œİl³ğãZËÍLñ¢±"O,d?;LÔ°ŒõFåÑ£™ú- iîˆ­ùc„Öç…¯ÕaõeBGæ…Æ‰Ü*p71ÔqTvîA5ÂØ’ÿ¼´ßŞjìp»xğW%xT²vXÃÕİs9Æ39„ã<î2ö{E2Xi—Ïºıõ<1z|ÏUÍN’PÖÿÔlP°jTj´¢²ûxã…ìá…U +4ÄŞøN';wÒdÅ¦«køİŞ»Š¬ ò.)eß)3ÿ)jÿ½ÄsàÅU÷£ÜjÀ¹ÈúEŒ„ÒµÅ~Eàqxª.`—NÚ“Êo®yÃY§Ë)Èøe5z3t5ğ…˜ªÃ’
ÜQÛC4ÅV²ùüŒ×
Ñ§©TMWª² 3Å‚qØéŒ[åí­~î5šÛy~(5ØIjîy~†OµI]óõØÂ2ÛÍË}<¼¦½H‹`şønYË´hn¤èš1s¨"¤H8$B ~¡›¥É’™AlîlíımÛ†ToóïmĞXËË¯}°{n¤‹S”UTë½.¥cÌh1ÖNŞ†ÈïV’ó8ŒçÒz4èbñVHímŸ|ƒÔüéÃ[¢}»ŞŞ£(šÿIe1ÛÙ©h‚x]¢Nç‹ÄŸn„ÀÊÂl5Të1Xƒø‘ÁwÉ)lãë­Z¦öö¹ÅôÑf%%ºYbõÎúh4:9bà<2‡-¹€]¹‡ÜG÷¦®ÁÎCÀãAÑ€óÄ¤àÆÄD‰
†šJA^ùŸZC:!´«%çÂ$„ŸÔÌ%F ¡CÛOb|û·İ
ÚØ¦1d”öV=˜Ièg”d2ûØ©Ú`:19ÔB£æóø=!¿“9ï5Jê#¹¤eî™m‘ÑGQ[uwz&™¤ÏÍK|ë=WşItèbÊ!8÷]ï‡@+jïŠtùe‰V3Ø”dºWÜİ²–@¡ôºh?z~#6Úˆ¡"3 ÛÒĞ97 ›Ã„^¸P’¸P*?ıe›,N™­ª®|ŠÛÉøÇa&¿İQÌèi¥ÚÁÒ&O\¡S_wøRµ¥ zçbÂo#´èû–bëHªŠÇÒ&½3‹QµA£C½aSĞ=”µ@îëXÄ‘=ÜS¡êpXø$ Ï‡±—^¿Í}èÁk0İA‰Êû;Í“¶ñëJ3<‡Ü²ŞSÚNDO«<õy³a¼šBxÅÏ¸5N‰8Œ[„'lFX7mæŸ;?‚\ä—8y%º{ ì¼ÄöÂ§ğõ©&ßP“S„&­QC	“\ªÊ Ì ÌÒ™ï=­ô{gû„gùLüİ¦¥Ñƒªú&Ş•™Ø=u…RuŸÙû='«Ïlxÿğ$ÿ‹®è"rª&6•J`îiüæt|Ob¸Ãf>|Ş- Á:&•&7bX†uŠ»*ÙÆ@lsrw]fªùÃ†ª`Ö$¥«Ì_F D5"ÃV*KÁÿH?­r¥?N­(•é'µ"¯[.æå"ˆéöº ºFsâA†[õ¯â»ÔlĞ*$›¹ŠÅp“}¥f3™—Ñ*ÿ¥W^è8Aç?fÁÎXçë_JªşkUµŞ^-v‡´î¿s‹)àŸg[\=íü9±ğBøQüb[ÄLğRSâyG9ƒ˜JNA¡{qçÏ¤şïÀÍa¯ûğÅ>gMé!°<]¸;‰fUŠÁ:FR!Bâœ£ÎJlV–¢ÄÆÆ‘dÉüb>:Êlä
pÉ%’®LĞHG·T­±¼3ZÉóõ~µwİ„ˆşå«„ææ=¶ÇÏÆQ¯Öo<=C½†ØKŸª–£§ê1í´©•óÌ¿[³Ôñ%zgé%[jC[¹tK@8ş¹PúdÛhnm¨°È¢N9{\pQñ ©íûÑ_ƒ7>bÅ	(rç#DâãEØÈe«}I­½ÎÁ}r}b¤gù ‹WäÆ^ûlõå¸‚gkcİ÷ggû=7+#…×d}Q]ô#¿~zßJ³MåmMÒã É¡Ú64ùL#R‡LºÇÇHÍj?Ù,òçA­+c™<®·g}Æöõ”hB°à»çš;·¶¶è¢>2‚]5*µ¯˜¢rê Şıß.—”Pw¤¥¥’ŠV®>ïU“œËQêŞ®íØo"N—ã€÷\jÖ<©ñO•ãş :ƒZ€~—œ{‹à“|s]0½ã‰ÍyêEÔŠŠz…ùô›ç4Ô?Ñó&PvV„HÔÓáL ûæ:²ÚÏı¯;ÅQ¬ˆî/)f’˜·c:4,'øúQG•YhHÆ~I²¡£‡A-–äõî¦%ŞäB²Bn>¢™£Ša=oVæiJkÇä‚ÙÊdR^dg¼øäKµ¹Åh¼{eì‚o•»RBÒı "µan·1õ“,JÆ®V¾6…°OõBÜÜ±sòËaeìwç§êE‘­Óõµ÷\ÖFÍF½lÑsÂQS'İÉ‡)SL0—îØˆzÏı=±	1ŒwÅH‹,>º‚ìVSq4ôÉÚ	‡ÀËìn°¼F9Y[¼äêÿø‚’›IW´é€Òç@ˆ‰hœ¦×ø&R¬«*@oa-[¿ôùôÓ.©äxµ.²Ÿ“¯¥¦aj×	ÁíáS#M=5_=Çù¡Yù|uWöİ†'g¾÷f¼°ÿ%æíéR+=«’’²İÆ¤½çú¤è©Ÿ Ø¯VÚó–¿+°ej°ñÆTÌ„İ„ø—{bütô£‹9Zræ¶Éi‘Òú®¾İ4ÃùìşÏÊeÌû¬:ú9æUZ[·ëS09£½{29a¯sêüÇİÒ–8Ñ‘«ß×³·ğÕ [jjÊ–5v±t¶D™4sqLPÙèìç}…Â˜)no‡+¶ñ+Àø¬ĞmE­,l•´È¾Àõ£±zLı0&Ï
ú,ßŒí—4Lõ ²AúµhŸÌÀíL^TiÊ”Ã¯4Qí®«sR¿ì/íºÿˆxÂõvìØıvÈ¸®"|±ãørÇÒƒîp!HµKôzEë¶¨B¦éÇ€Ô($¡UºÆpk£T¤ô¥Á[êÆ±÷ùVpËf`rbF&ô1(ü¹¤VA—z°—­³şÿsŠÊœrPu,áÊI[ôpf&Q‡Ù¤— I*„½Nš|GhL¦w»z²ÕK?Î6®¦4<çÚ6AÕvü³„YrmÊVÅ ÖÈHÛàG{R-Cçwó '“š3cäÇÿÒâÍÃønÅ~@élF«oöÛU:µw3ëµl¿dÅ"çAiŠ¿¹»§j·÷ŸŸOËo=‰;“'ƒŞáuÛ“å6º{L())€X]Ü+ä¥RnDê7ÈÒ/Ïç@m“¸$Ğï!]ã^ôúˆ“şƒÈ±9éçvìÀÆo»ıˆyè­ÅKp¼#ê`ÎìŠ¤Xsìe¦ñ+É÷•}k›>©«üàR‰®®ä ú–d ƒî]IY€~æ/N}<'ßä‹g†Ô±Ñ0› Â/T•üÚÑ=_*,²&npãx#¸jxÓÿ&`?îá­yÄ»´vÌøİKÊ'YÅµoa;§my½s¦Q¸=Gf/YVê1lùZÙ;HTÀ	bÅó,XÉ¾›‡sÕç4>
qÜaÓîêĞX^¢‡ã2¯ûÛªı¢îk#ß=$Ôjp×Ï:’T®İ3ğœQæ^°Ä­§×“ØİÕ’¥„{Z‘%ÎÂ¤m?R5zd!9Ñ.²_õˆşˆ‹Š¯}æLÉC‰n›S’O§jÚLµ<Ë‰|	u–‹ªöşrN±áÁNÌ;a·Á57üN£øÄDÜ[5Õ?ÃToÀó×³·Ş®Š…/Šº´ æœ”YÓ\ iyÊ˜ÄØögİ‚oôğ4¡ ŠLäTèúÈÈJy“õ9–ù~?‡©¼jf©QXw­¿àgiN<nñšìËq}8$‹&º_=/·°İ„<‚ qF»øØT{Ğ€Ã;ïıÍçğÀ×w'Cß³ø®Ÿ„7“ó}£Ş^»P´Ï×;³*÷Û¬°&-¬Ø…e':­Âˆ½TE=¢aâJvH¡»ñ»ˆwBÖÓ­„ÖY€:GBŠ2
Yå6Yæº))wÃ9ëf±
;7>`ÎÀ§=“T G#nºüÀ?
Á´Şˆ|Ókxœkw]F©öÃ} ®ñÓeÎ ‹Ö¬‰õæ-ßüÇÈ{ü€øŸ{f›÷w‰r„]´-Ç+Úï0’:] s‰•!
RÒ$ Ë,-˜A/•¥ì^¦ÍòÉdlÖÁÓÙ0½çn©Î»ş†¦i€;;Œ!2Eåƒ´-i%Áè6›	¨··Ó×ë¾vqpÈñ%kŒ#Š&‚º=oÃÌ°<ö4èowìˆªSáÖë¸ÖxmpáYTVS©³Şˆı†ôu6Î.ò5‰UµŒüî„ñ]Ûõò™ÜÇæŠdP¼ó±X*Œß SUÌé=¶£dšyEUÕŒ‘!=Z¹M$ùûæj##I”è$.–÷AâŠÂL_iŞã‹ë 6äĞƒ0‚cGÕP$%"G+¯¤}Ö°úô–~óŠvÊcÈ¼¤î™HcÏñy1ÿS?#,H)4²óvâÀ¤‚+ßñnç_­cìë”›7tã¾½ã¤çİë‰Ü«#V÷3Ş×x¡c«°˜Åñ©ü€,gTÈãıËÆÂó½ÚÂ©ÏÙÓ}çÆf„Èpn³}¿»!K*š”"ËO®*‘üƒËÿÍĞÓgN

aéÙ~Îª©ãO³_Ñiñ"Í…¦÷®&Ñ:oÍsØw‡áÛ6èÛ®ú]Iæù1;t\mû|Æ}ïĞ”şº‰ıliìÃÑ}ÒS©BR’R¤)p6d­ÑS(³¯j˜Yñv Ï@–ªç*Q¨9'
CÙsJ¢Ü²ƒ$Ó¸‘%˜\Ÿï}ÿ}O9v.è»µI×n‹8P–i˜V¥ı8Ïç1Ê“~ôƒ~Ó™,­²ãWâuì~±ûÆü&Íé|¿¸®²}8ßèH>Y)}hü¤ê½w®ğ:ÚıÆ·7µğÂ~ÛD¼¨€±ÜZÂ¡O|M…ÓodÌ©¸(¬ Ôm{C_ÑeUJAD`­hÿ P‚›f7®q~²‡\“óê€3|ŠY‡k!:Î§+„4ŠÚ(8¡ßÜ¾·œ½uwz6˜/~ÙÒ·=qÛÆ„}aù¢¦H2*©£JÍHb÷Øè¼ÒÒSÂİ€AF¼ÿ®z­cxg«©ÓƒxY n³ø›~;êèXÙ÷Ôâ±ÃWµu“Ğ»áuèª~)Æ)·Õ	·MÌŸ6h^=xÙ·Z*ØıàXè\ûô54(òÆÀYÀè±b¢ã´üÿ†KıíšOzøN¨˜à–ŠTPª…Mé¥¶¶ÍsfÈåú@#RX¶}Í‚+"3ËfÚ¦‘)uü>(?ŞOX©tnë;Z¢;²Á Ô$‡›»×yc_DF$Ú˜…—WÛdPAÀ>£JSw#éê5µ™{lLöoL¦ìà¯´Æ>ğNœ­~*m”rhşÙıÈ
¾ÁY°®‰jé¹ôÄr½œ*½_XéD`ŒÛŒ?£S1ıÉD§ªÙEe»TIDx)ŸÎ-&¬ZÂŸwÆK¼{õ”w–ˆÌ¤VÚ£¬Jöõ’[ÌmÉ¬ZqJwpôWÖÖ3ì}q* õ2%>	ÍŒÍ9‰G›£ÿ’´=ÀæOï\xÜ,ÕõŒ®ÔÁûï"f6>YñPÖ,:_û­ıGÙ<ÀÂîêdı/‚ÀçT_o¾ªË[Ïg†t#/\Á£rñkŒêïï¿$NÛİp¦gd¡µ.ïÌfß!¨]¿=	-_ŒŸİËüƒÉ8-qÖIM»µ\ğÕ9 ş"’[$—Ã;é_†KâLŸÜX+ÇÍ Ì<hc—&Î›S+í¬“®X ¿¶“/YÑÃ$Ù9&Î™èœ	+OÈñb·BĞœúôŞo?ˆŸÆ§Ş‹¿”¹è°¬øû‚ÁnªªÉRŠ&š™ÊÑ$-†‹=³ !û!³Ü+P’°bi
qVø37«ß†k§!ép!@âŠBóW¦Ô#¯.5âT…¹—]ç›V²ÚV*–ß›¡7`]S‡ó c²R'<ªû¾äç™Ò®Éô3¿Ÿù/üÏ×åU…@¬nVÔE5J¡!ğË­±«_-¸úm¾õùV=À¹håî;s/M¡[ µçI<T¶ÊUp†hc-¼¥p` èÿ½EKOF6gé‚šëY•»8'ıfBSÉcC!
-¸ñß`b¦ø³i÷ñ2Ş,ê«Í¼çó’GtßU¶Ëwxûr¶?Èp¥b(Aµ‘'ğwXÂÃé÷ù^”EOæØğãND\ªÆ~EÛãtUA+Š+ÓÂÚ92 [­hæˆë#<ÙC…‡ÈÁ\åüE((nEfı<T¥É†·MŒÀûæà‘&ûBò€ÂEj¬Èrã,Ş(Ñ}¿àxÎ+¸61şºïx)ñv¸I}@iüñšÆĞpó	Š†45pNÇ]İrú‡ŠbQHY©@ô¾MË½$Ò‡÷ëÅª£•óãw YK˜uÓfÊÿØ­5±Ÿ™2I¦Y'¹| PåZ ”Û‹Ø*$Ğ îì˜=0êÈáÈ0ÉØÃ©¼„›-ĞŒó\Ìµ¾èš‘PQ9æNnå‘ı£bm@R =NDLóË³‡t—Å‚#;ÓRÉœ€¹hÀ Wï‚D_¾ÿ5çÁoÇeŸŠA]A?Ôn+éjJŠïç\#qàõ^(…&½øMYüÕÂŠ£e€OTàİ¾àîk›sóĞ.sÖ.mÌ‚ŸŠ­Ÿ³ÌåËF¶3@ør-…Ñ‡i¾T^LEßXÀfóÎŠ³	æYLQ-ÇuJ­;q[h¢{lãYyÛŒÆ×¦7œ~M>øñÈŠÌ8R¤¶t
?ª©n|_~Ï~®ÔnŸ‡İõ)ÀƒR~k•×^Š…'(zçá(¢…À ±ãL	wôX:ôçhe¤ûI£(´7üZ”‘WøÃnéøÛy=N7	~Œ/ÆİVYó[ùl³»ã
óyª»=Äç›P]ÊEœÄ=|÷…ñ¡ÄùTKjpdrÃ/¶~û~õå¯BÀ¾ùŠ÷S9§,d?Ñ(’Oáo÷”¬Æ÷JîÍ¡î¡¨ /x;ŞchÌÄaMÚå=î‰ÆJw’º 49æÆ Æ¼ö;š“zœÇ$WêOŸšª(*¾€S•è“­ÙEOTqR?0ƒ—¡Œ{yy¯2ñÏ?ê™˜c?éÀ*ğ6Ê1¿å4`…íXÆ¢¹×ñ-˜šúå,,¾HRÙº¢àÕ’TeÂ¢ÜèP@´i›œjú¼™H©A%f¤ĞÂhã»K’Fâï¿”÷ÙLÌÓ„NfU|üö7çVïˆïñtìN.îª¸eí‹]İôŸ)Î8
*`çïbw¹‰b“;Ò†Ğ:“Vw~t­ºÎì¾3ıáš!${O#BÂõõüå]¤ueÓJûZoêMlŞdëtpáSílbhB^¼kÂ *D‡¥QdAÑœêm¤úƒ–<núnFoîô.29è­™Gıw•CèÁÂÒ‚x€äâ×pÆ¸á•ßF)·Øøå¨e„‡øºe³ãê¡½½ûséÒ>+6 ßvı|®ãür¼ånec¿Dßq‹Ÿ³+%Ğ·i˜—ñ«×ı=šãÓÂ›|³à·‡iM¿ı9ã-ÑÙ7Â©’H´ü€s”gHsF¶]ååş¾àş;ğ-gì¨3¥ˆ”vÏ“Jõ¯XQñg¯¨½ÁdeeğÕÑbWvà¦? é(§9İ¡:¿ù3âß
ğP¶´>W‰³3å¿Ÿ¤Ã±êÜaÚ³|ô*¼gë“Ù‘Ùİ:Î\BOSÊò¡Ta¤¶•3$@f²Ô°ŠFaşuT[vóÏäÃÁu®ªÌô‰ÀÈ>W©M‘OS¬	òÌ
sàd&p½xp@6Û\Æ÷²ªöŒZ—OÕpˆâ¤u–Y¯?›M^â&şi]'üvÙdĞ»×##JkĞêËô;ŸÎŒ+®©mfÉrŠ«¼»ÀÈ¥¬¯F]‰~W©Ê²¡f-ßùêíVZûeA=Š!7Å.]¥v8^ªšé¾—}Ä 5İ«
W,f$!±=PëhÚ¤«ºıgâ°eRÚ‚ª
/iIœ{)k¿”Âa…{¡v¹ypï'
¿Çoì
¦VÊX.ìÈw Ñ×‡ÀÖæ€CöÙ;±L|3gÅÑ‘²—›7ü;	şwL>­¿=6Ú]¦:eÂfm&¼;§¶·ñê]ëÙrŒ~-Ù¦]²Hõ„a^ñe—7ˆˆ‘áGx}¢&Ï$J ÎäGírÊ$›½´ú¬UÅ%¨½·•úEİ$Ñ-û>/\¶Î¤À²2Ò[t÷NMúñFäìş¯åÃ3Ht©Ñ3¬xq ;©üã-Ö	Š²eÜ¾#)Şø¦`qôµÎYz¨èıi›61ŸZò şE‘”ù™0ä³|ä(OòaÁ¶@v³ °0ÖÄ½1´”àŸgÎ“;xÌ˜ØŒéU”Ô®|‡õ!ä7ÓGş°íèßaÆøÈÎÜ4ßP‚á:à
0gƒØ&~ôùÄªV‡¥ã)¬r& ÊÈqKID”¸e±W3³òL®qsê‚ße[î—M:lec‹)èÇ^‘½í—N[÷åìª-µyÇ1“ğŠ	¨4ÀAš*”m¡œ~ïn0É¼Ò¶†‰º_8EE£k÷AHâ/‡j—¬İİõÎ;²!§D˜i.ÌŒî%Ö²8÷:P+>a·k&ËÃ¯1Z%MU*Ñ‘¦5¢ó#²ÀŸœş[gYY¦6?[\nÅò8&!,úöÛ}èœ»¯Og–ÃqE,%ÎvhÎıÄ¤1Û ç³†óÅt ÑU
•&fê*ÙœØ>„[O¯2”k¹8ª J¢L%¡€¥Fi
#üCL"pâ*]İãòö°fû±•è–~¸6«\lG7Çî¦]}nRƒœ^Şó–zmoZ‡F’Z:æZ®¤Å®Ş'EUˆû>%Û­Åş:GòÄªBo}© ]áù»mãSÛû,6{(E¼vË´0ÏÃÒ¸²Ê)ÈÇ9R³â©Mİôø=¦„"ãß«7îÿ8.°xJ7†›CŠvÄ÷
Õ¢SÖˆ›ª¨û”g‰ áÄ˜®*»L<“‘#?¶¥­¸\$Û(šK¥èãçÇFbM)–|f{wìÔdP Gaîâ„(îFé®5oœÜáÙo23Ã“€ïØ§F7ü»Šw§wXïQŸëÕlÄ#}«ÄÏèÅ¡Jâá,ŠûÌÅË;~9‹§g«¥Â’š[Uü½vIJe²H-¿˜ü¾8à‡f’MNì— OBáÜXœ(¹Œ‚¯	R”†fôz7é-ÏÖûkÏÈA@¼
o6.9wÏáWUoÏFâŞ0±çıÖê>tÓ×Ö(œ¸ıÚ¿Ûéë/ÕÛ»EüëOúÕ;Œ¯˜lü+t¬Œ‡ÙÊi‚ß*^(sPDˆÍ!Z²ó¯X‡]M©ÿ˜ÍÈ2]iª,~oZ¦çşHdÉÈşÕeE[mw_˜bÎ›²=d<”Çû³*t°Ù…¥HÉıÑ’¯#Pc.tIı>=êª+®—N¬8Hòÿ	D²çßÁOfâ8|·l%¥ær[uÕzUßìzƒn¾@üß…^\ßv†„mrÏ¨CèÎé‚EàßŸ¾	Ğ'ÿ)'7>Ä±ÌJ7lÈEO[Ü:EÛ0oNoõÛ­Ô&«øàú¸>ûo1` 4@&&Uë;f¿¿yb9MååzuÉùºg¦j¯×§[”OæntÄúCOL-|Ğ*ësˆh¶îgŠì–:2ıŸ8¶8ß.ÍØ88¸´„*èğªZ.ÑŠ?=ïA%g«GVˆN]§t+Lr	fI÷PÃ	´YÌ+5tlwŸ´%ÿÔÓiÄÔPÊ.g~ (ÑO6ĞÁÛkÂİ·¯àËsMÆ‹âOÔ#&wMÈ.ŸšÓ¿¾•
uÎnwÄ«­_ÂujñDhºñ|BåXîåO‡İÚC¿®{Ñ¿ÌoVLÍP‘O!|ï	ôßë¸	Sb
/ÍödüšI*!Ó¹‹Û =«;Yh:öğ©[„•Ñ©ª$-—Í­ÜK®òò\7¨~§îYü.v“ŠRV4IPÕg%¸/Öû°ÓW¬Ëàêk|ˆdÓ¨÷NJÈ¶ÒÀ@/N`â}ç‹9‰Úœ–ÃzGmrI&ZğˆUÑ D)Õ¹c÷Q)'à.GLuÓ;o‘j@ál£­=ÙBWt8$’üW§Wºle6µÜšlØ~›ô=3`,"NU÷º("~}[¸ò7¦v	ÑdT‹˜şÊƒQHbsÃs€Åhó¨¼Wš+SS¿qEÓ©À£]~Gç1•Z!™¨S–/5@4’èømİe,u‹‹+‚o?ÆÎÊÅQˆŞ„š«õ)VŠ•ò$³(íí~¿=óË~‰}{R[Ã{÷Ëéïió.Ñ	ÂDã’{gTíÆ§rxó4Ï6pm?	Úz{‡ºzäÇ²|Q Å§»i˜|Ú~Ø$àé‰ê :¦æ¬£»loºšY9µ¹ìa7C¡±ò|ìxúz>Ğ‹à·»Øtm?b5ze¡„QîÌ •ì—tG#8µ^ÛlÚŞ@C%nšìr¶°óŸ	7Z®è*¨"X$«º&ÖñIASR€<U¦*²Ûz÷*eÄ{IùcSûõÏÌQ	R8aİóa¿´¥átµú4Ñè/¿Ñ…è…Ÿy‡˜|Ê2-r™bı[ÿ<ÏË×nÈ`ó%G±l
ÓolA¤roîá¯AZAŠöãu›ÿl‹šVÙ‚L™öG¶/‘+şNq|*;¡ä¯>ê{³–5mËÛ°ê*Ñ®Ñ=|q¬ªö¨›ÊóHßuÅ$Ùó±˜ÀÀB®¨(Ào³©ıû‹"¹˜_ku[–Ğ(P…+bhŠ3¿(k1{"¤Ü†+%JËÌuøVË–+"eï—¤tgØ7vÉã)á$‘nì†Å«‰Ó8oórãEÑÛÀ{ïÃñzgx8U@¬Ê—{hwqXº{:V^]¢]~ÑÕıX^3ôï¥¯Š•ò‚I(ämxEğ!:Ö1ƒ9W?¹ÈÆÒ7}»Â‰îûî´8¦w††W‘È¦@ í=Æî}·+¢=’^©NnM­ó5IæÏ op¾tµß®Ñ]ÖWç—Îıj¿HÉÕ´lÇ½Ñ"‡¶7DN!Ç4Ï×l*p2¤ç3
³Õ^I_†±×‹ùóJüåaõôŞ4ÜƒÓ" nb¼zUAôfí9,l.XBj;hË¯÷W*º—”WëWÏ6±¸Oê»ÀÙ¬¨X%ùóm›XOTKËmhÏî3èäîÉ(Í|VslÖ¨l©ÇÉÎ)÷/àË=ÚÖ¾Áö'sA9Ë'ê~«7ù;÷Ew¯Y}‡d€kÎQ9ËÔË½=öĞétãá@¼DT Œ1
×ô.1b­ªˆušÅK|×™ÄM15qh$‹{‚Îp©m¬«¿‹¾•ÂmE}æ§ßƒ T‡òµ#ÅL[¥aç,š˜3ï>Û˜ZR'^aqëñ—W,ˆyæ2Íg<ì‰HüR|[ö·ÿ·É—GÎ_“Øı7Ÿü—z©^ªçNãÔ¼:àf‚©ŠØ€^ğÂ°e.p(…`6(Y˜Qx2Ç÷éíâõÍ$zìîy[?äìiV—Ñ€Æ‰ğsPß3FÊav‘¢É}gE}ÕY„d õqMnÉylã±ñ}Ş™·dÚâúhd¤K§6óRZÌ¨¢BFtñô–ÕUÃU\kYšƒ‡óùtö[“&ãpSè”®ª.n²^6Êg«XmÕœgÏ^µ÷ŠÛ9}Âe•i‡=L–9ˆ h±[Î¢^_:<=è¬ËÚ;ª]¶ ‘ù†=”aç½ôÿğÒVF¦jÕ¦ñ¶°±¤^Ww¾ÄŞvR=·<Ñ0ÂQ‡:Iâ	©Ş¯›R¨êØ¦$Í)¡ºŞP-JJ33óJ—¥àò µ&Yt
VÊª³gØ:†öĞï½L}Ò¦9´”A3FØšeÔ¡=V*_mŸ¹šáº¶ë”ÊºÎÔ†\®QÍ¨Í”¡ï¯Û>¦-Ãi¯´>d£w<œˆf®¸ÑxŠ] Ni9kCî`êÈ)ÅÍÊ"±dÆWø9B—t™:›dÍŒ|,‹ÔÅsF¿Ú]’NÈÍæ\‰sÅÊ‰ˆsglù¯ÂÿÔäsš]íOŞw©%ÏÛ¶>QL™Äö£ÿ¸¸°&ÿ•*%ƒ[ÇÛ#"©…Óô	.—Ş›'©ˆ“©à7„QhÆ†w%£G“’µTuîZ¨^E>ùs‹@jÓ·‚ïk&Ù5Sj!@òÂ¿˜¹0HPÄÛ Q$U°“ŒÈqJ?ŠÑë”í^0õsåK’:f¶´ÏÚêËÍÖ=½ÖµºñÚòÖÇ•úW)PÒ£9„‡ƒ±=‹]	§Ôìê)<U6ß3v¹ä¿²šßŠg'££ÔN\k·lì]×ZşmğÇæôŸ=»k…uÉµÜFEgæ÷gäV\M#Ümá8~ğ{ˆ6ŞÜ­íWÛè‰>Î94ß=_y/®¬=½=V³ G}X4ZÄ¨e°ñÊÚ–§@c¸#Ø™aQ zWˆ"ÔîW
´ø2'Ex«ZU—„Ï{#ğÔÑĞÜÀgŠğÔç€$G „Ò.#s ç"w0E.®Y‡‚®ãöÃÓ[õ¹™„Bº‘ªKÕª'÷İÆ•érç;‰—ıæË}‡­F¡Àa‚¦M%ùD|rl*ÑAÇÀMU‡Î;. Z…ûó.Ù›àĞğğıvÀ%.fÄHïñ²š1Ç~¡h8fŸgİ,–\köˆ^™Ÿy’Ğ…ûŸ/(â0.fP²Ô´]c0Ÿ‚N-…lÁR­¿/t 2Ù\7ÙºLkvHõãÚ£åŸ×ÔN»y¥îÒ÷•ÁëhŠcÙˆI?×°ªê3ƒÑ˜ígyKÒÍ‡‚´QhC¸–>‘¾C‘Da¹u]6~ÚGF‹S¦©è=äÎ82Óå¾<¨ q†Î¦È³àDN†ÓÅ–>ëx÷ÁÃ|
RQ¥F’¨J^KÓî
6ãÕÑŸ/|ÙUyÅp€¤‘	Şë›ÿŞ7îxè¯ºjáC´ŠšŠù)P?íAKXğgi€{«q}õ=LØd›¯İ¿6ãÁo…ô×cY×Ş†w[ÇĞ~­p²™gˆqêÛ‹Â›ÒƒÓ¡ tW¤@u-sİ«¦ƒ{8ÓşÎºj‹D#™¿|Qô†ë³GödqMd'K¡Øš ¹å%ui}t™Šò#i°¬ÿR€ò¥Ïšóš­µb.oÜ Êì°¢ÀyZÏ:—Œ#ô»
ı'úTFPİ*¬Â-'>1:l§¦¸vjò@‹#ÇP(ªn(œÏcƒš`ü ¬[>¼ú„”kÄ›'ÛY‹Ş·(Ùà72·öŞ{Gó½0äD‘&%©ğŒ¸Å¨Ú2ğ7ÊÆ¡“Mã73AƒÇÆlG‘®¶6›¼®RÄfşáE‹0ÜaîRÕü!béæ•¢•3n1şÁÕU¶I4|%vk·‚4”@\7rÉ‚k¿‡+¬D˜9ƒrÀgb Ì#ÆOråèÊ ê¾Ä˜ŒÈæàüKü.?hQ‹°çâøßö“R¯ëHı–İ$Cƒ€IwÀ£ Üh›
 \2Ìò')Ä÷¸}›¥É>Ç²ÎÈ4 ºÀ½¢_©Ú_PMÌŸñêÚÍÒŠ#§Xdı‹°i
è@ğ«ü£òœ^!Êln(v ´ª½1´g®š+2ùk¥„W 3HMk”Õ†‘S:ÇºH*Ÿƒ¤<å€äÄ#¼öbl„ôo+ (#7:°õr<>ú•/>ßtú°²fÉ65ãÎÇ0$ì²M šü® ›‚T¾ÀGR\¼.Ÿím²ŸPUMÂ@nĞg˜:ĞUL/:Dˆî×Şšcõ;>,h£=vì¤!ˆ3l¼üÖ'ïúD€ÈfŒÃWáé- 5ıÆ‡„ÕúÄ*ú'‰u$SŸ“T/êŠ„R¥el4ä.nÜ‹ˆß5‹7¯ysrúÎ,h±š—”2$õß­×gÅf\¿xº^˜U'ËB—ª˜Ş<:bÉn¶ÛJßxÔ¿ŞË~¯>î¹}–Ğf!ÉÚ:CD .ßõ IÊ¢Ñ2BŒ!=šÒ€!¹Mf›T¼ºóCBÁ.+*O*£bqİãÊ9 NúÃê"ÖÜ‰Ç÷×çRÎ]³ìªı·çé'aKğÓı´kèıÛnÑÃ>0×ì,oÍnµ%r?LÔ@&*¥ã
ğw
ÏÓÛí<óçÄ^Ä¦z»&úÛ³cY`qìŞ¤Ù!T¢¥ªİ¿<¬™Ò®E†ÅÔı0‡ „ ãŞ·Î78V4~\(«ƒ ˜Å$Èœ3'¿ÇAìºüµ¤‡Y\äNH#é=¦gÊŠÃŸD5rßB­Ùù$a—›ĞExÔ)v‚ÿšÂ<2
ÉÜf%úV‚Cœ®pùëÈ;jFö¤¢¿Íî M/”’EP›YúZ}SA8E•	£çøà%‡8›ñxÊbJÇ,ép•k§¨D ¬Î 1äã=Zæ0àwEŒhBf6ùdO»Ë+—Jåz·‰m¹]—©)‘˜D)‘²K]Ë^âğF”s—[fU4šâˆ_Ùà-sÇAÕÇV8LÌßw÷|#˜0Ú‹¥…èºêQ`tª1§ô¦›¢éœš‰…Ô9çæ[9„÷²Â±xMÏ£ã23ˆ¶¢lz0SrÈŞS"W?¥Å ²Ø»ö"J>áˆ”&¢±!ªüVMİù {ëm¾ğ°Ò=è™'VjÛÉgxÏ"Ï!v9xDLİO[¿›³ö¯bFV–R”GE&²ï°h‘cÔ!­x\1êMh’âÇz7&ş’ÿœ¥~ˆ¿Ä²Äø>	Í·•¨ïh™'ú}vêÀAõáÏ¢ÍÃ³Gs4¤Õ7W+	ŸQÍew„›4Va[¨ÈJcb£«¨	/Ñ#/ó0”$g‹©D]Â÷x_ØSªUv¹¼Ø‘^»A™ùëg$CŠ Ä•'2jˆ|‰·jš2Øy:3_Y!z;PÊÀ@ZÈM¦Ó%Ê`’©/Ûú,wMS¨u÷±ÏY|Û-¿O}»o¯ğ0p‰®:õó“øj—¿?Ü›X4|ÙÛÇ¨àÈé·fâ§+¤Æhk$”tuO•$¯7ñHó I&ÑËKŒqòâøŠ¿ÅûdÄ‡}aığŒÇææ›bƒëAaù§~ÙÔÇ/_Í%@åüÿf¤ÓJZ€Z…­³ Tµ2=Æh×3ÌØ2d5À›xbÂÀˆ…-;™€İæÖ{Àc'„tv^£üË—„ZıÒ€t¥ ²®òAlQì Ïkbõı2>£®İñVÎÕ¾÷u•£‹Üz…1‹aÏú85{â–™“U°¦[¬Ç¼Xd•BW)ü÷
“£e×å´ûIµªÕ…J
E[•êßê©lÏÉŒ£§xÄï@úŞkñİ).Â¦%AqÕk—æ'ÂDØƒÛ´nY¬ÿŠY1LN1´1¬÷[VQ¯­ñ•ÍÅƒ~÷‘ÿ®Õ…¥ >~2D³µß0pšQÁ4†[>S-Q9×U{3¥H]ëÏ‡>&¼m%Õß;
ñÏCÁÊªÊç…Dƒa¤õ{x%s%Ë81†-Ù¬XçbFø8;OõÚßpÎŞ¦Ã)£ Ÿğ'ñ¿L‚ë {é®ãùërYŸ_Âp„…ºşîTt%~ÆLkgŞkµ×:Úx€íŸW•À;jg‹ò.í6ŸÒÆôì§3%-õŠ­£T5ËÓAô¡ò~àòQû¹P“_±µ…‹'ÖIŠN:Ìás(4âĞ³ 3Ÿ$ñQÑpÜrpcˆ“ÁáE­M!V8Áì‡¡í÷ÜğÏ{Æ^ÑÜÚ%­µé7¢å)å  ¨ùŸì#I-‰j²”åƒJõCRÒAõ·íóà°dÓÜİ¦ú*§Z·«:7ïVöÅ[YgåmÅÍüÙÂ‘Ğ.­uæ	ùT2zÆéj”{65±-ÚŞ¦?'º#ë©CE%`5}[1¬·¹Ï!#öè,µB_¼"*Ú±€Bh‹vLa|9Î:ÊKû0^e—°w\İD«¿+¿]–s!F'Åvõ3Y'|ü:;°Ç£¯ºûHÌ¨É–ÄÂıh°ui0‚şÓ¨,¡’Ğ¶ĞÊ»$³™Tşk‹†‡zÜöc/Y?¤rMt°$û™—÷Rù1ŠÌBÆr]HÕOæI+YzX»Fª €-qúAäâ@€HTéÖ¦Æ¤–’ %Ïƒ'nbetWôtlÙå“ÿB¤®KçœõrR*î†{]¦ÕÂ6çÔrıöËä¢)jÅDÒ%¾§Ú| tåÇW“TjH%YõG&3.Õ˜ÄI’'3hk”§èB¸û4»°Òd}LğWHªq¹D|±‰Â×RÂE‰¼”ŸˆøÓâ€ÏxÙÓæä“éùvÊét)±·">wEÚ[;“Tˆ_ß1¶tq	c+û@¼éyø®3h,æ}©ŸaŸ~‘”¾ÖÃÙ	cÊ°:«Ğ5òÜİŸ3ŠÇÏ –££FÔ>¨U&•Ö×}òtGbFZãØ”;ç´¹“6Uê;é“Óƒ„2#Šãµv¼‘Y©ÿñzéo‘`²Fê2±QÖì‘—l<å5¾\üìoÕ?ñÆ×(SŸ	BsDœáÍ0U?d-®GòBçËù³*:¢‡®É—¿+00ş•uƒ¤
?	~Zßm€ÕwÄÕl´2ñ¬öàšnĞ%7¤E*~8néóÎfÔ=)h«ááùïÂ»ÉìæóÉj±¡Ì++3¼ğÙÇöß@Å¬qt‡/9 ïŸï)RÊ«şãúv¸«ñ³&„›¦ºûÂØì~lñlsˆ*yÙÊ¢„Ô `Fxõª§È+`@‡ßóÀÿšdˆ¡”$;§]Š¼•³ïÖFæuf4ĞÜ@†-~¾~DëAzW¨=È¼÷Qâ	ûl Uµ¼AŸ’Æa.Ÿ:K­ÿìÏK!“÷v+C×óˆ]“5{£¥yûêÕÃë¹Éšö4¼±üXe~1.Nó;ƒº;¹óÄù¦¶@ø-|<DF^ïxƒãœkŸÿ˜úyÊ¢H–Ï™¹\QÜ”ƒÁ¯³í¿•	sê}9³ş)HÆè³ûøZ’°ÓX,‚¯›¦`3'­L¶åkô•ß7ÚÇ5¦	q²ÎeŠâ¡	á… 1ƒ\‡ö­Rp8õÕ«~¿[»¼T¤¡oÈ!¦ŠgMÒÎs¼Š÷˜½0‚Ü2¶ßÁ-8YTùlíê4Zl‹KªÛ=CöÇ#q-îı"³öI<—åÃ|?‹S¾Xa¢êH‹_Áe‘ybËS²¢P0%¡Y^I2k âAQdø¨¤Ğ`¬c­Gul¿Üµù?Æ8&1j›ºÀxË·Œ×ô4s¾±ĞÅßcNä>PIüå¢Ñ£„¼²Ë¦ºJÒë]/Åy£”ƒº3ÌÏáî02iª *q·%j?šBôFÃF#¯“?‚ˆŒ4Âøô´„ÚM»<ÏZ>b'õ»:l¢}e:ê±Än'.^“ì³iW3³ÁSCKÁ»7ú6ö»‡ê
Á[»Ä}Eä5(-i€™Scè{Ôœ³İ%¾ığ,ßI‚ ñÓ«êª!Ïµ€•`ÍÚñj£íøÀ÷¢Û¿ÒØâkg7x4W|#zÿübÇÖE`ƒ`¤D©÷«`Áhp	0Öm%0+™b:×ş2Êúl‰EaQg´3}¡‰qD–	pQôf¤jl‰l¶›™_ äŸnø×\ĞŸm—<,şû/«Š‹Ããï¾“ÛZ!(tª û|h¡ª¦DXI'o"Ã+âWõ®{ælÕç‰oÄŒØb*êÂèø	ã±ÜYK±"ålŞ"TÇ¸´Û¢÷T9Ğ´>…+$á!Jb­aù¨ç}²–+3 •<âÀĞö‰)3’ı"4KGóGøh…Q›kp¨¼Ñ¢q©xÆÅÏî&ÍW¯Û:Ÿ)Ó€­Š8©#u|İe•f¸Ê@+ÖĞ]¡÷ŠÌv«ıwè–À´ôlù2¦ÔqÀëıÎüĞÑ&›	AÌ/•Ì9F¡…9nYşk|DJ5>Ím6F´’ÌAbéJ½íÈ§-$?óT¾ÉÅ-æÆ©Ése#™4†Šñ^V£‡HïòÒ'F‰C$¾e± Õ))r)®ãuˆì!ºûÀun±kt¼ª9ä›‡G‘±şŞTww¼èYW:¬º™.º4»MYÕ‘îÄ¥3r¢ÆŞ4éDp}d¼:5XR¹Ó¨ŸXé¦ëGŞ,`¤¢W××ù9·ïâ|İ¸5|_	u…ê(sÒ})ıc†ÍZì«¨`8¥>ˆJ{&1T®J`õgÛWâ—Şªù:{±·´|iİŠinkÌßç¬¬¢çÂªÄ¢Çp›»IÅ¯7Ä'1«»ò`·È÷ã¼lyÄÔè-óÖ´u|´ãuágâXV .«p“¿üC¿¹ÎUZÆr&Y{ék}Ä´ºEy– UJ´6Cf–L>óÒL‹ÒÒ§É….?²û<gZ1[#@tUw»aZ$—¤:¤]©@nÓW^.upwP/ÄM:;¹ñ›Èj£.>/©v|1ìLN+Ì(G8h«Á.’øş7 ã7¿—Áşh=B}£NmZX…$ğ¾f£ƒP'=(É¶ä›éµ®÷§©wèÃË_Ç2Rğ˜!xô¢>oî ¥‹ÚÏyh$Ázwlß)š#4¾WLäP8„øÄ‘‹,úoÜü´}hmçm:™±}ŞLˆ€wdªêuòÑiWıÉ›ÔÍß_~Ö´¸!Ú¿ØÃo€ÉÔ„ÕÂ‚Ó¯4#’S<‘·22s­i³a^ÏÅh=u%¹Œóê+÷3µI8ä´à ½óˆäà ı$XŒü‡ÁjÆFFÇÿJAÅW#ß“‡%òœ—QÜ–¥lzj,'Á„9UªÉqe,¨4¯Ä¨šv9õF/¶Ö‡‚ih·òšihº5Ï"tf÷.fÙ ğLÑ°ĞòIQ)ë<2ÅXhş'×FÃUA‡ë”Ã­˜­ıî!|WW¯<)»¼}s²êïĞ¿|ª»’-Ğ›ômŒ/UŞY%–„Â	ì‰XiÂ<µ¾q6¡qÙıiñT%ím?Gnx´ÁnÄ¯ÈŸİcğÌ*&50¡:::=wş`<ÛÉo€øßF=^¿
Ñ¬sj|lu%è&>”’e1pÜ!2ğ5îW1ĞGÏ–»¸öÖıŸ!&ü¶‚—ğ6;˜uÇ¨Z¸VŒC0¶*ò’ÖºÏ9L2æv+M¹¢]Î¬/ÑøŒª\âyå” ·ˆòª6Òw|¢mÁ!Š­1ÎÈôˆïµ1ŠPüâOD§¶·Î
—n/(K—™EÆ#v2j}rçJÕxÕ@z¥k‡<ÂÜqL¶¶.æ;šWGüÕ;øTo¶]şÁ9íP»eÖR×Ğ2áŸ\»ad9Ø÷ı~WÆÛH_‡®¯ùö€‘0£kZÀùtàjÂÄ#ßŸpÊjyR¹ë&ÒÚfG3¥¼qµD#3ãSš92B
N¡/‘V)}\YüË]6«¤TôÎf@©ÁRÍ’joıléÙseÕ(ºú:€U÷ZÆ‘ª‡Ê<Ùä…ºÀyWóÿtqŞ7{;Ä¤¦ËK*&}>rã˜Ş{oë/K§z?-2p)øšàÙUØûAsÑé¤1}³ë“úğAbş'1»27ÒfÌY˜AÅp²}¹­Îıò ›.2IQ„4™û\Q3UØH¨ÈvÛ5¤Ç=ï9U7k'›Œ_KåÅ#5»ëäŠrèÂ*»,øjÉ.X‡óC I\W<ñ«Ñ°^8e¬À÷^¦(J„>­}d£ˆÁ‡&âh}µ
²™’¢NuaëZö:”1pbJË©	’¢$%şvÜ!šx?„o®F­r÷q±zaH(„ËÁ‡r"”Ô‚+W·wØyP•5143õ›˜Ş©İº%U£$²HáóE—3Û*ÓCİEè‚cÃZYiy#fî6YB}:…~2ãÂ¨Û /íB8ğç“6É¿dMæAğ¥›s?¤'³×o@Ô‰Ğv•ÉÛ ?B‰ßÈjZÙ¯ù ãXMüƒ+AY-m‰GBÆ1ÁiãÕL~OŒ}„B:”5*¢Z³İÀ®pè]'Aüìúí÷ğÃ,ïäŞŞ«asàNm'Ô¸ææ§ÿ“‡êä›XkàÛl¯ÜÄÕë÷ŒÎ0ª	ñôÙ3D£:››[•ã0¢ãë‰êiÂš¸ƒOÚgÔâà$ Ğq9Dè~ ĞV£xØÁb©ƒ›2¶‰¡ÄªbôUcJÒÌ4G¢mËåh©uv…~¯¸XìBk—Ïz6^Ñä­/e£õw<^úÅ¼æTKğœ}õ75ëuÏ¬xÊ–ø½âx¢4œ©$·•‡°¥Zç|§•!¨İÕ²ò|ù&9Ùş¿Mo`ÊEŒc™F™4ú¼V
º&¨T½Úµ~fÊÏÒÑ+¸‹+å™§F•Ë˜×åämŸ‰? bF-Ğ™Uh›ƒÁ‚Ï3Ëã/]Ù¾M™Ãû³'?øœ¦º|0Ãà›‹QQu>pÖ«XirÏ|í¤:ÛRTëOÜãÈ¶`àFæ1ó¾wÃ¨Š!ø¹”¹(à:_ô$ï¹¢+©	ÿ º€Eÿ¢}ÜqÏxJ²mÛšÍ¦§…®ü^‚Tú]šK§˜ßÄ«_û:n½é+Ü~ç·ÙsöL–MmØÂdc’7¼á|şóŸãëßº›k®ÚÇüìÎÎİ³‹ÕÕv`F¹Rš¤4O’ôZLÎlÀ‹ª9Òbaa‘••z½>§9uê[¶låÚk¯a0›o±Ñ©\¶¹İZ¥İ\bĞ^!‰ûhëØ¿ÿIî:zœóq+=’¾ÆÚÂ>pí;*×õÊ£D;Êâ\8W'7¢‚pD´ÎTµ9fj7İx=xe´“¹¾„¸ÂõÏËp÷+‚Œ-…QSg:ÉÉNà““q†Æ9‡°N¨À³¾ïcŒ^¹TÒÆZ!…sJ)—e™lµÚ¡1Fø¾oKQ¤¶r¬VK[­v`§œÒkó&oÌÜ?è7ö}JW­”•)A)ñ¬Ÿ»uıà!œ>ZŒxk¶µ€R˜ M¢z·ë
u‘SâÎ@ïGw…[Ç1XkQç½y³~ˆjİX/£ :¬ÑÍP‰yˆRˆµ–«¶!Š³·Ãş‚;3aêœ¸Vñ
!°E¢#¬á×nôº5ÄÃ	‹27Qg0#8CÉÉå³ãÃ¤I2Ls#Ì]Ìù|Og Ã…”C²e‘ ¬åpÅ÷R4Gße= òë%ÖÖM+ö¢1|/)ŸC†bÍk:w‘ÈÀ³A™!1jÁ¬ãxJ"e.6§Ë•X“\)7
=â8Fù©By5!¨;cºNR5FTp” ?Ë´tÖş“”œ ux§Î:{÷ôÓO>± =™ŠD”²,³Ş÷íg6/mkíŞ{ÎÖññÉÊCÜwüôÂ¢Bda²sçNñ€'<@ŒÕñı „$Ó†8IF#dªÛ"İ¼…Ğ”€€œi¥ àH»Ëö¸Ë9›æ@H\¦Yh®®ñ¢×FéE![¶l‚($ˆ*Øõö©CÒ”PßïËƒòs¸¦Áe)•jD¹RcàŒµ%›îõy¤y6ì có‘B@(¬uYC–k­éôz=c59Ì>>V'Ä´â„–‹hø^©D’æ»‹ò•Æİö**²Ôê5–;]”T”J%’4AŠ:Æjã„ÅGå‰{¾d:r‚FcœËÇIÒŒR !*W)Uê$ıv®/Õr™N·Gseé¹CÔ‡]»ÎaÿÃ÷°yç^vìØ…Â£ççúóci,äÚ‚ü÷Ä‰&'ûZ-W¼‹Â€±É)vïnpó­·279Çx³Ï¦m;¹ìªpÇİ÷÷ûœ½k7wÜvÓµç†ãŠjeéôQ*clŞ¼™—¿òÇ¸óÎ;yhÿS¹ös$iÌìÆíìÜµ‹·¼å­Ü|óÍÜq÷¼øš+hLNåRî1°¼Ò¤×Ë3ê$MY^YåôÒÍ;±Àñ'ó-™aß¾}¼ä%/aûöíŒçäJ!G@¿Û¦³ºÌ ÛF:Mše[\æ®ÇŸ„ZÄÙ§xäáÃôS0Æ®›úÃ8¤ğÕµÏMw¿Tİ÷kA <¯2™s?Š /D ¥6¿æ çœPR¥¥R´šôãŒBÌĞ9'„®^«¦•J%uÎ!$.
ÃÔó”]]m•<Ï³•8Î|ß·ùv‘cßaêÕV+ªV«iš$ªZ«¥RJ’tIõû}ojª1ÈÒTÆq¬Êå²–Ã@`ÿéR€ÇN,$ÍV;®M£µvDÆrë*ìõ0zN³_w	ÜºaD·C×úÎkıàaß¿xˆ
ƒ!´<ì¯»~N<‚_ûıÑyÉµ×9·+í0ıAÙkPú0Y%5v­*=sH{Ø/X÷Zg$c=2?%Ö’aµ.X×špë;,E \×jîL@çµtÇ¨u¸¾jvëˆ9#F}+\PÁ(yY#BczC2¥¿Xãf“YÎ çç±ÖßY#&k¿.gÉÇ"P£|Mœ) Wœ¾C›šaS+ï)%QB…Ön/eµ3È×Ã	œEm%‡+9KI@Ù8BçŒg­Uü z™ÿ¸À9'…TW¾à…—ú½¿o=ÖêãÜ8…ú±ƒ—Z++İs/ºxû—\²óğ¡Ãô
£“!9ÌSŠR1İhà{İN‡É‰qßÇó¼¼zQ
µºHê{´Œ	H’OJ<ŞôKËqÎáCì¼æ¬sh±´ÚAHotXã(…!Zµ2ÁÌ,Î*¬@Ò‡,^›EåÉƒû¾sˆ cóĞY ’2åñq¾böö¼§ºØAUÖ„…¬Å´ñ¦6åERÒÏ,«Ûå2Lî†º]N%)©Ö4Æk¹¯LÁ¸UO¹R&ÆéÚš¨#€©‰	“>½$AI…'—¹ë¶o¡R‡EòäcûÙ05ÉàÁôz=*¥ƒŠR}œ,îŒ6Ÿ±z•~jh¯®ä=a›ËïÚ³‡î¿¥\®ä H½Fšfó³s<úÈ“¨@")·<~š¨¶9ç:HÉÄäIœpîE—Q*Wè¶–™˜œ¢69Ccb2W\^bû¶í|ÃdÑÀçøj‡ñz•j¹œ·‰ÖenBH’AŸ…cÏ°qû^6mÚÌ«_ıj¾şõÛ¸ãÎ;8o÷6Î?g7GŸ¦×^elb’7¾ñ'ùìgC>ûÅ[¸öªËĞÆñä§‰“„J)¢İé0ÄhcYXn²ºÚbrr’™™fff¸ô²K¹êÊ+™œœDëu#`E`ĞYÊòÉ£´›‹H)(E%N.w¹ãÉ§XÌRöîÚüÿóöA’e×yàwÍ3i«²²|uwµ÷n¼í1àf@$$A†HqÅXÇUÄ®´!mÄşØ-#¸±Ú "viQ"D
€  `¼Ÿi;=í««ºËWef¥y™Ïİ{÷Ç}.«{`öé®ì´/ï9ç;ŸÁ]#,¯Ôq…M'„zŸawÅ²®M¶”?Å¤kÓ´¢÷ZÚ¨’ƒDĞ¯€eÛzRW ‘€i²­†‚Rª ¥Š&òù ğ}Öíö8g\h…+S¾Ğ ˜Û+ğn·k‹EŸRJIôx–iF¨ô=Ÿ*!@1bÂ`×q¸cÛ†TII”” #ÉûIòv{m}£¶c¼×õôAıRi	2ë%‚,s=£İvÒRFÅWm*2³U™‚ÛÏXK›ŠÌj FH…›^%`ª”Ì)$³Jé¦Q¥úJ"Jz¼bÏ°Ğ“û›’|""ªMÍ–ûñkW‘TJ%9	vDô:CË’UâKA@¢ÅÊbç)·"ŞÉÇ* Ò§¤»­ÌéÏKOÑäv´>9ÛÓ•LÔŸÑ”_)¤LM’èò£_‘d7ÍY®HÚ¬èà6=ŸtåQ(µ		Òko…R1ÊüPÀéùàŒ€3¦e¡çu	¡ÄP‚P0A¤©$L€q°_D.ûs® |ßµZãG;º²´ôãt…TJ÷¼„’V³å|óÍK£ã
ØÒÇU
7P­ë¬÷N~"LÓB¹\ÖŒtÎa¶6 	Çj³]*„’
N·ƒjeåƒuæmXOİ Ûí¢Ñî‚qÂ˜”Ã2ŠhspÈUA˜	ø=¨Æ< …6¦	ukõS‘)@ìŸ- æ‚0°«¨WPêÂ]ºsr—¾`(GĞX¤ /A‰  ÍV;Ù'9İ.LÃ€mp¬ó<	1TDj' ÀC'$n™DköÇIô†Pkµ°O[Laî£KX8ûr–
\úè*v>û8„ğáv{©,HI˜fv¾©ô>­˜Ï£Ñ©Ãu]Ô××@8‡Óíb|tS[¦1?7‡ı„ 2X‰Ì-¦&†ñò«?=‡õ¹qLcşÖ-
%„A€f«ƒ§Ÿı<fg¯bb­ë×oÀÊÙ(‹X\\ÂñãÇQ(À÷}˜…®,®£±¼‚Ï?}bS½/”¡İ¨aÅ¸‘©í0-Ÿıì¯Â´,|ã/¿¥•U<yâ!XÅÍÚ
Šƒxö©Ç±pk?~õmìØ>-S`˜»	ƒS(ËD×Ø³g/:ˆ£GbllÃÃU˜¦^cy¾¯ù)Tï½ßƒë´°Q_…ÓÚ@Î¶¡¤ÄkïŸÂ¹'íÁüş{é “ø³ï¾Œ/=¼ïÚ3˜_ó!$ç‡ÑaJÈDà~BtO½fáwìgr…<¸ÁA)v>×–aØó{®!Š(Æ˜Š£D¹PòoÍ/\×eœs©”$BâûÓ×pÏ,•J’ aŒ) ¤Û8!–e	J)ÚÇ ”¢\*{ç²µõu›1®
…|“ÇRşçGÿ(NÙúüRíê¾mÃ':N—xA!é«õ÷2!|ÇPm
Çjs•ì×…Q£Ü/-ËÁd_CÒ› FÃ¥„tŞ˜‘O‰ÖÉ«şª–4RÅ’4™™ª)’6š¼IÜ
í ½.¢€ñHsH@	‹È{2‘¹%(ˆÊ,0¢ş%î•dÔ€(ñ&¢ –óÑÌt¬bòDöyÅˆA¼NÉıRx½Ÿ|H¢=?¥”e’X#¦e\¬c4€F(Câ"˜%YFÆP„ĞXA©s:">A_fn¢~T	rg"VDõ/}dŠ&<Î)8gÈçär&B©¹h=/Ğ$jƒ£ËÏi@1PEÀ”R CJa)˜ÒÏPüÒ B@‚ /|÷oßûµ¯üãÇßwÿ¾[óóKJJ™×,¤P·æfk®Û…‘n®ô›_© ×saİ^æò¹Xd—%”‚í»€ç`½¾ÑuP*äQ÷µKœå÷0²k7ÔêetÚmQo4°átAÙ@ôÁ(ªÀƒ•´6Ú€]á¦ö0m€[P£Ó¡BşŒéÈRF´€ŞŠî ­l"Pœ:Şİ@·Ó„YÖ“Vk|xk†« ™•V²Ën·;h·Ú« ;4S•ñqÄõN)Ê
ùŒJN®ˆ^§ƒÑ1(˜Œc©Õ!JI87¡¼ ¤`Â4,.×pµéÀÈçÑêtúvBJªĞ*© ¹œ¿×Åz½Êú"ª`”Âé9Ø¶}nŞ®À    IDATœC­¶`ÆFGA©Î&¨”K(áÛ3!¦†Çq×ñÃX_[ídA9Çà`]øO<ù$¦É>”øàƒSX[]ÅØè(––—ğhéQ¢Ñr0U*bcq¯>‹ıûv`ßöíè8Nßó;ıÆÚ"!¨o…08>óì3Ø½k'¾õÍoáßş__Åƒ÷ÅC÷ß‹.®×Vğ©GïÃ‰îB±ÇÕë3xõõ·‘ËçQG(_ü	8°Œ1˜¦	Æ´»^7rS$ù©Ûi¢Ó¬ë…£.c¸>3‹—Î]€šÚ&xúÓAÕ,ÒöÆœY(sLV‹8ºsk2ø¾PÄ‹Öè4TïYâ(¨Èù: ·«(<?„$Lår–'sv×í8¡v(c`Œid Dåsùp` ä-¯­å—–ŠPŠ(¥ç†$ R0F˜ì¹=Ãq3gÛ¡eYJƒŸPa’|>ç3F•R€m[¡nr¶-”R:*8‰”*T~‘,€¯~ı»µö[¿zúèŞñv§×+×7:QZfr$kDBj‹4à·5 ñ3‰]Ü²£Ş—§kBİ¿EhE&B=£qWzÙßß¨L#É6;5ˆŸ‘‚R43}Ç¦9ñÔ´ÚG:$™¥uÜÌ nàE4¡""ªÄ_ }A„0Dûë>ä‰„¨H2¢IÎY_ñ¦NÉ´€Æ¾"òYˆ …æ§$³2P©‹QÆI/Aádÿã'›÷x%–¹}òÙ`3i/~Ïh¢äÈ~XÙm>br"¡‘Œ	*ï.âÇ ™ï¥”X¦‹+Œ•àyZ„€x4Ü5¥‘/‹\$²2âB¢¤Äáíƒ„‚ó7ê—ˆ  ”Râ8÷ÆK/ùôç¿ğÈÙ3gäµË—j†aüLÕS) ŸË¡İî@ÅÅ%„Bj|Bd¬0DÁi`AÍ[ó°ÆÇP„ÛëB@bxd-6å•UX¹<ÖÖkzwRBâÁ(LÃ@Ñ6±Zo y íWŠ¸ıt…ÄğÏÚ  :5Ğ2‘"ĞmAÉ"`ÊÂğŞc¸öú!$Àº`¹x¹
'*@1µF+9ğÇGG )qyníö!ïµQ®ö1à	†±&BÈñI¸ksæ¾ç#ìy Ì€"€çºØ¨ÕP†iğİ.z®so@™:ÍfU‘( <TAK4j«:+ gbeµ-“-”GA(…çz€ÓÑ‚Ã##p]<ò¼ß·}+VkÜ{ïİ°Lõza¢Ûé  <ˆÿü7ßA£^GÎ¶1½mì?€—_z	““¸rå
 ‚ÑÑq¼ÿÎëØ:5å»hÔ[øÏ?|ÿâ÷¶Â2x~€ÍN1JIÔW@ÅĞÈ$Z­¶nİŠßÿçÿ^yåeœ|÷]|ï/â{cbb@Î2ğê«¯ãÅ×ßÁşCGğàƒâøñ»066–˜QBàEfD”²¤Éò]íšõuHÀ`zÚ_^Ã«§ÎbÕÈÉ?õLpt×î°:8ˆV«MİvNC>Î^»‰±!-ÃdœbÃñ4 i!¾¡T?×,%LÃ@#ï8G(tºˆU–m†‚Š]ûôä¯‹u±PmËêõ{fvvĞqË÷.¥ R%¥AJ©2”6[-+ŸÏû†iˆhx%†Á¥Á%¥JYÔ ±Ğ\•Š%ßó\îù•RÃ0´ÓÜ'k  x®çûpæÌ½Gv\£Ò»{e½™U…ÌŞ;ÖÆÇ’>ÅÇ…)]TëæAFŒqš°Ád²ïÇ©“š¨HÇEIF0{J? Yw˜Ha ³>²÷O¨öV“B¤{şÌ–!¾f´oIï7CŒ¸ı M¥z‰b*] ÷;Åú
$hñRëÃ`z­‘ÑïCÅ©’©‘¤SuA¼>áLàQ/Î4d¯¢Õ)!)ùOiÆ8(drÚ;@Æ–õ	R‘Öw@‘Ø^ë÷Q¦dÏäu§RÂ´-L<¼Å&M±Q”–N’ŒÜ1ãÆ¨T†T
&%“•<f—µÍ{( ÏaX6lËDì{¹-E¤”Jú%2@¥Àcs33kÎœ¹üĞ#î[šŸïöz]—Fm&Ñ€€Hmš%Z¦ßóàûÚÊƒî–¤RÈù¶Z*biö&èÔÓ C¹áäÖnÂ™ÂìÒÊ¸ykHŸ¼…€À0MTŠ9xî:‚nÆ`Q(B@‰”2´º=4Ú!v?’"…ş"Éˆ . ;>ŒÁTIşì;hórûîO˜Ù	<kXØèy_;ÈQŠñ‘a¼?¿Y¨` ìÁÊàû²x®b©é`è®{1÷³`¹%Ø¥2Jƒí5 º®•³À=\®¤ûbıÚä‡Jp<¯ïŠ!`œ£:>‚V³ Q­âêÜ"<×ƒÛu/– ¥Ô¾B ¶¾®V1wó&LË†R
{vnÇüâÕ…mC•å%¸İßû¾ııpæÌi<ñøğ<O<ñşôOşwİujµD`||+«ëğ\9KóF>:wß~éMüæÓ' ¤Œ¬>ûeR
Ô–nŠÁáqxJ)xü	;zÏ?ÿ<ÿñ«Ø:5cGãƒÓg±Úhá÷ş«ÿ&‚ùÇ¢)ßÑ;:B  s+¤Rğz]¸=N«n«0Ôˆ	e&®ß¼…“WoàjËQ‡ï}$øÜ‘ã~Á6£”ˆ0$Üär½éª±bìšD«İÂ`Ş@ø Ä@³íF;İtÊ¡ô`X…M×ĞO¹4•DÁÎA*)Ã~!:4ëÍ.ìÒ¤äŒB*™zÙE¤¹R±àç­œ»°°¿:33T«ÕóAğ ğ9Q"i†Œ3.8SRqN\Ï3z½a[–0M34.97¤’0€€3©'L¡WÑÙÉCa˜HØTÕêçşEÈÕµú•/ß|ißö‘c0×õ#•Éxì¨DÛ­"%Œ9G$µ£	ôïÑ8N-yÌ®'QyPQÁ—Y¤ ÆåÓ(• ªŒÇ€$	ù•p}¼óøß%°{z?ÈıÿYãôu‘,is“%âÅ-Šêk½6Ï¿ªO•ÕàË¤³Jú‚ìº%÷G‚Œ!ûèÿ³6ÊªOÍ5ùUÉªDf%’	ÊœîİIôsšÈ×eÂˆ¸š	¢AHÔœªØ±0~‘ºQ£$E4Ô»ŠÈq1Ë±Q‘9PÌ…  Í˜É¨‰¤ŒQØG¹@0^µà‡@· ×íaxt †ÉA%*vHR J®õ?’
)ˆTƒúy§ÿO† €B±hö'¼5;»´}Ïîê¡cÇ¦O½ûÎ%å¦IEİ¾4„R¦™„àll4µ›œi€3Ã0a¯, øàX½ôÏášq>°e
ìäy½Gñá©Wq×ı˜ŸGsƒ5gšZõªƒcÑ¾*ÔÜ2péÒ"n6%î=aN÷Y´J	
JQÊ™@àC0»§'Ñ^®€0#“4¨¿0Ì0ĞìuÑó\Eôœº[wBŠ.ÆG‡S`¦¬Â»|•bqb6j+˜*b°T‚ãúpİHæi|ğü+~ÓÊÃs»€h­Õ±Şj÷5t”RH!P(W08<†ÆÊ"JÅ¢–öõ\ä[uäKåˆĞeajë6Ü˜›Õ«ƒ¢–	rnÂ°r(kâåêFGGP.•aåX^¯¡Ñ¨cbbÏ~úY¼õÖÛxâ‰'+LOoÃû'ßïûØh6122‚¡‘¬¬­#—/h6»~üÃ×±µ2€÷…çy·5”2H!°º8B(*#ã‘	Õøø8¾ò•¯À²müÍ·¾…wß?ƒO}êIüÓÿò÷Q©T  Íf3ú $šø	º6ÚÍœÖÜnJˆDÉ2¿°„×>8‡›àjÇ¡#á}×}AÁ0e
ºØ©PØ–…¦+UÏóÉ³÷ìÅ‹'?ÄpÉ‚!”¨·=¸Îhb*!áwÛ0¬âÏ×¨KN02úuZn%Ğìx0òCîúP¤

$gçÂJ©Ô[˜_´¯ÍÌ-..H)I
*„` €QÚ×Rêû>ollär¶†!””D§	j8[II´C ƒ’Š€(%¥$ŒPe0®”TD)ù‹&HƒsÚju›—¯Ì¿8Z)>Ã~Äïz	s\FÅQğŒı©¯+BH—54V¾Ç"âW+G»èX÷hÎ WE$ò$ˆïqáhT,M›†˜—@}¾N@BRS š4'›Üò2Ó{ÂØôóÛ î]ÁŒŠ"ÃOP‰cæÏq3)cYªTı+™6*áV¨>ŞX*ÊP…Ô¤L©ú¸ÙÜ¾?ÇMˆŠC¿Ró#¯u"THÈÍ9*qŠLd”}õMã;„d¼#"D…(Í®•ÙÛÅ Q TÀ5
6ÇDÕÂ†ãcy¥‰R©„r)²¯N^GäN‘|Ç5[2Â9ÿDRÀŸ3H*Ã´ŒO}úèÉ7Ş¸4:>1tşƒSmÛ½çÑ»÷N\»ti²Œ•ºƒ”R#(
hµ;˜œœ ç(!è´:°,[“V­›tf½ÊØ¸îš+.PçBA	¡¹šE@2”R”‹6Î¯71Fê¨×ë¨n j¡ŸtŸCåşî•WñÅÏ~¦Á¡BM:$ìg™@TR$”`Ù&æšº|fiş¦›K0ÆQo¹hw”£Èß[k5øG¯¯câğÃÛ©ÅjÁê2TŞàåç`pu¡^"lŸÚòô“xó›ßC¹4Æ¨Ğ…Ût°°¶¹©¹‰İ«ã[Ñë´ |ƒå6Zm”ŒqA€={vãÌ™3è¹.@I²#œŞ} uìŞ»‚FÇÅÁc[AÁğÕyÎ±ººŠ±±1œ8q?úÑpcf[¶lïz¸û{ğüsßç&õ:*CCØàVæ.c°$3n³‹oşÍÀ$pÿİ‡@ n#R57@(Å`uLó"–eáw~û·q÷]waue>ô  š˜÷¢»ò˜dÕsZhÖ×ĞmoÀu» JÁ0MPÓD§×Ã÷_ÖêØzä.ñë<LUª"Š0’ÁixR†F©üPU^™[¥»'ó¸¹ŞÆ}{FÁ‰€®‡¡r.ÚëƒÇw[ÈËQà§èâI„·Æ)daw@ Tàb¡Ö9Z–JJPBU”Ğ)K¥’ºœ™˜½1WX\Zp]Ï ?`Y3BµcL;‚^·gvÇ,Š~(!„&{i¥2è~âC)Q”2%uÁ ¾ï3ïz?Á¯rÑ&[ÆX×é^¿1¿ñı-[ÆöØÂ¶}_$l)–Ju3;}Í.×?‹whdÔCI\ìõß3J£¯¾nM§¾øö„ä64n ¢Ç¥™¢N¦ÆÔä'Õ‘§ÆBÙüìßÑÄµ`³^Oı4cF£ç>’ÙM§“ûUÿ*Wİö³~7¿x’ß´ Çë–x„OÔj“# I5u2–\*‘!q¦èCìTß§Ìød¥–Ú,)jbÎGü<dt?ˆd¹R¥ÊDéª=â×ß/¢(óøßª˜Ô+Eâ.g¯“P%LC€3	 `EÎ²#NJVß¨Ï	Iâ•3FLÃø{X(8¹eËø£GzgO¼Z[[ë9½ŞÌÁcÇö×ÖVÛõZ­Eõ²FÛ }L'_.•P¯7`Û6†G†‘·s`Ñ> ¼  W˜:¼éíX\ZÆĞØ¤BN1>ZÅìµk`Å!Ôë5¬6šPŒ§]ª’P@Á¶ÑM¼3»Š/­®aï 9KK ¨P`÷Ö	Œ(æÎ¾ƒ=÷<¬¿F?€D\½"È˜‚ ~®ªÂÛ˜”1,è*vÇg¡çcÖÁÆ¦‘[|•‰)mTÔ7ÕI*C4	V®\Eu×nï•x¾Ğ„ÂüêšfÏ›¶lÛŠÛA!? Ó´†®6(j53†cªOödp–•G«ë ZÄüò:Æªe¸İŠe-{›˜˜€eYX\X@ehçÁqŒo](á‡^~åeLmÛË¶±åò´66°²²‚C‡¡R©àÈáÃxùå—ñ»¿û»ğ}¥|”(¬¯¯`ee£c£˜Ş¶Õ›Ip†Ò’2,/­ã?}ë ¸÷È>`Èş÷Šq)$–o^Cø¨M|ß‡ïû8xğ >Œv»d@èCšAˆ n×A³¾ŠN³0@ äm9Ñjup~îŞ¼z…¿ş™ßÓcÂ "¡Täf§Gœh×
¾¯¦¶o/½ü¯”wcëø¦'†Q0FÏ…CZ‡‘Â(>Œ‚Ğë!ô»Ñàã€^g†U 7"»íhw: (D¨F*Ë~Í¬b`²KCûï¦)Ì2ó7ü:®]Ÿ˜¹~½X[¯YİËƒ `J)jÛ–)©”’BTº!Õ³±TŠ4›-»/øÅbÁçŠHJ©Œ”	$¾	mV2’v{=^ø €#û¶)Ëä(æÎs3£ãÛ;E§m·Úí	@tR_ìØ—XX3JYRôcúºÈ>£I±N€´ÈÇVÀ„¤.y1»=ò‰=¥ H†´ gš’ŒF&»Ò'Ÿë§+>â!,5;#)û>KHâº‡L 6ÁñYo„ş&@“Üd¦ˆUñô¯2‘xÑ‘™1ŸR}iÈaúód’H™ñ`@¡²™ä@EAÃ2öİ’È>Dˆ›‹DµŸ6™(•X¦M@Zàcy¤^ˆ(^J7B*ÈP@DÊ+EOŒ"gÛYŞ»Ø’=CŸˆ³;“ÍN¿ä€ÄõNÊN«Õ9päè^J(}ó¥—Î7Ë·nÌ½ûmo¿úêß÷ƒhâîP@!_€”pÎQ˜È¡İêÀ2LÀ0 ¤‚M \¿
r÷}X<û>		E(¼@arÿ~ğÓoj+nÌ/b½¾0#élõ‡Â æ@§–}œ¿~>Ò„‚r;ÉFüÆ3¡×\ƒ¬-‚V&"²ÌÏ »¡~<¢Öõ@"W6nå€~Ì]D·°°VÇähÒë¡»c‚5l„‘ãp{â6ôØy`Î_¼Œñ/~Íâ œVKó@±Z¯£€Q†f}nÏA·³by®×Ñ²¹L¸N|°H©@(Eè»zÒ%¥b¿€z½r¥‰âÀ”T0[¶Láâ¥KxòÉ'
µµ5¡\,áÈáÃxçw „@e` ÇÃ+¯¾Š¥åe4›Mà©§ÂŸÿùŸ£İn#—Ëc}eSc£XYYC·Û‰\ù,ìÚjİÔ¥K)ärÖVøÿâÛXyæyü>äs6</Hà{1­•RX_º	ßuPÛ;¯wéív»ïõÓ¨tšu´ëèlÔtá§Zªcš&êõ&.^¿æ‘	ñ…üO‚[…¡3$H´Ë–ƒTéä¶Tâ$BêpE]¸YW».Ş$¿ık£³º€±KœæĞh÷@É`¿ùŒp;uváÎQ„"ğ{èÕà6òÕm0ó6>üğ<¤ßåf&İN[­v:m|x}‡®ón·g~à»=—¯..—g._5æç­&sº]ê| ºcûöµrÙ­5ùf³™‚€	!¥Tjpšß†!«×ëyF©â”)jE8OUp”ÉD/N¨¢„JFaHˆb„JòÉ9 Ø»cJg„¸åR¡9X.‡…¼‰|>!TÒT&„­¨HsFA	‹şNàõmh¹3ÆkWJ˜n¢©DŒú>(bÀˆ¶©MÌm"$€"“l—ãULÛ4ñ'!ÉßĞˆ?éLƒ ‹O“şuPÌ€LØù$¶ÙU	¡:ç*B’BÙoî£²NÆ™‰;ÎK}Î~2ÓE¨L•ª¿xgÚ¾Û¤~ııiH*{ßH©Q„ÈwEÅE9’jÊ¨Sß¬õOy*Q\ôóâ×/¡t}‘[AÊ„×’ q’cÄcŠßÎ(¸aÀ69ã0¢U¹×¾­ó'Ğ–üğÃPBàÈ
ù¥« ¤”ªë8İ|±XØwøğn ò­×^[ºvéÒÜPµzàÀÑ£[Ïœ<9£”R”RÿN$B¥8çÀÌğ<£##X­ÕÀ\¾ aAÃ ¹v¸ï!ÔL^×+–á…òğFòè”‡±xsëÍ6x‘ 
ŒRpÓFÇÃ+g®â÷ş‘t»ÑÎ'*~aˆÉ±a„[w‚–«·ã]?		­/vº¸4»‹M ””!ô<¹ò7iJ!$Í®‡N»…sWç ~ówàœ:‡é÷@ÈLîİ‹K—^„”€›@wy†pDèõE§Õ§Ó@®PÒ?']ÇIwkÑïA½Ğ‡|AˆPJU±ÑêÀuÚƒ Œ1„aˆ}ûöãƒ>À‰ÇC¹\ÆÂâ"öìİ ÈårØ²eÎ9ƒ-[¶`Ïîİ8}êæææpúÌ|êÉ'1==»vãâÅ‹¸ÿş`X6Æ'Æ¿zİv+bsËCØÿÀøá7Ÿƒò¼ä ,äsğÜ ù×ßÇ­›·ğ•/=ƒ©‰qø~?ğ7M7@«Qƒï¹¨O 80‘ú tâ>škK¨­.ÀëuØ2(Bñöûgpz~şà|ğÙ/†÷82J39QÑK(¡’0
!©’JENdDA*’³-LïØ&ÿæGo±/8‚B[F
xçr†a¢Öìéğ•¾,Aà:ûûöÆ”"\œ¿¾‚j9=ÁåÙ^ãşé3ûAÌeP±š@…X^ßÀµÅ&ÆV–ùÒÒJq~nÖ\YX
Wæ—ĞX«©V³¥º®K¤Æ5å¾={–ìß¿¦”"“í•ÕÕÂÂââàF³™'D‡ÿ0Je$±R
@†´ÙjYR) lÛ9ç’¢¥ZÏ(ªÍÂT¨‘Rah¨êzkT)|²5À¡½SÊq<¹Zïú…œéäòvPd6rv.:Æ#Ä‚¦0=¨öñ!zNM÷QCÃÿ‰qMô3ÂR9U‘<æ ÌIãâãuA¼¾ÉhãU*c#}Æ8wh ¨FXÔ¤dMj²št’}/³ ›)[™°ŸÌ¸¯2©‰}ÖÄ›‚qâÁJe&ñØ¯_mæOÅ‰~'D™™¤‘xçEf<:!3p}ÿq}ç`'Mı‰ÑQ‚Ì¥µUnò3+Ûø5‘ˆô©¢ˆåØ„1i8bD#â6H%’5ƒŠvR¥È8H*…Ì©n0-Óe\rÎ£İYä ¬@¤–x(©C»6Y+şÒ| (ñ<_<ÿï¼ÿù/ù‘‘±±á}‡ïu=¯tã¯şêæùÓ§g|üñıÛwí½qıúú|¶²eıFòy˜¦©wQŒ¡\.#ŒöÉRIpÓÂp¯…Õù´ªãX__ÇØÀ ¥@Š‰©I\—Z–Z«fä#ò…–i)j¸N)`x
—ëKpÚJwˆş
@yô3òÓ!© BÄäøèÂ"¾õÆGÈ?zTC‹ŒAYÛF=å¨µ{˜®àÍ¦Q]ıÆvï†ïÜ€¡PC™;=°¡*Ü¹ğ\Œ[Xo¶‘/X¨·Ûh´šàÌ„Ú­uŠ:ëŞqH)ašfÒŒ)%£IÒˆÄgÎaûô4¶OoÁù‹Wàöºp»mËCB`ëÖ-xíµ×pıúuŒâ£‹Ñqä­‚ ÀñcÇğŸşò/ñØc!—Ëá±'ğÒË/ã½“'ñä“O =‚—^y	wß}†Ç&022‚áêfoÎá1)Q(±¾¾CÛ§1¶e
ó—/Ã0­Dòg›¦QÄ›ïœÅòÊ>÷éGq÷±#(äsÂa("ã}Pöœ6ÏEÏi£T†ik§UGmu½NR¦Jƒ£±ÑÆo¾‡öğ¨¼÷s_
íÜ˜Ü *s n–~i=î*:P‰†ú Æ'ÆåëìÓWğÙ_9Œé±„‹Ğ.`±æd”çıêšRÃà`¦NŠ©”!Dˆ+s«øÚsgqÿşIŒ†É+	]ÜXXG­ ¾Z#]§G;Çl·Ú¼çº"ƒ0”"*ÔQÀÁô¶m–i
 ŸË©r©äwOŸ;7Ùlµr\‡ş€¢R‚½"~°f«eK)	7Œ‚˜–¥¢¦!Im!Šq.H?XÑ²Ä/bÀ˜M,›’Á"ŠÅB˜Ïç¤aRØ¶™uˆ‰âbÓ”?óÓhº-m#˜>´i&€¦I~))$†0„è"]vd˜¤9ˆšE¢ô¾Hö—©Í¦Ë‘Lb_ìVú²!C¤‹E‰Î^¶5BŸ2!×C¦½Ì0ŞÏÈáh_/‘MËC¼±J’âŸáÄÍˆì#"ÕKˆª 9x:F*5bL•e*¤%t}Ñ*ÂôÏ·ÿ¤™È4O©˜#AOdï 6xê‹›Nö2…ò£@¥+f¦¢³8ˆì×;õ‹ød|B@RBœVËí…Îüê—¿üp.—Ë»ç‰N§cıè¹çf.)øÃ©    IDAT??¿÷àÁ©F­Öj·Ûşfä"ÓŒÈ€Å"h¤1Ïçsú!Â0DÏu1RÈÃ¾qŞÃaşÚŒƒhwŒnİ‚W—p­ÖA³'Àl–²í#ı‹R§¸ecY–±¸¾=ƒƒ@(nÿ¨•AÚÃOpEBè" l?|ë;{"603böõOx/CË±²^‡»ÿüÅ›Ø¶m¹bİøX&å&Š9pÛÈ@H…N·›ht»˜´Æ±±Ñ€zçdš6zİì\œ›h¶Úpƒp]WCMÑëA€z­…å9| õz–a Õî`°£× RHØ¶;wâwŞÆ—¾ô%¸½ÖÖÖ°ujT¨°mÛ6T«U|pêxüqLmÙ‚§z
ÿæş µZyÛ‚ßmàÖk¸~ıvlßjuS“ch4p]O7( &)ğ¾ğ«øßşà#f#	h‡Á¥•¼üÚ»XXZÁ=Çc|t4ipâ&€10ÑX_B§U‡+q†N«¡–eC§×Ã•óxõâxâWÂgï¾ßÈTâ(¿Yí’x5E¡TE£T»æaˆÒ@IÎñ­ßÇgŸ8ˆÈĞC†˜_ë¤|•ò®c;_ÊYò•²mg/ŞÀ×¾ı:¾ÿğé{ÑZ¹ùGÏa¹îà_ÿÖÃù r¦ RèÕïàê­ (jËëD¡¬T*=å‡~ÉÎ{ÍBQ,jäM[*!Âv»Ã7šM»ÏûŒ1¥„ œsYêm›šjÌ…`z5M¥TgHí€:cZ¦)LÎEÔ4M¡ *n¥0SB„¤Ûu¸”’~ò4@(J¨,æ,Z(äËÛÄäÂ42.t$±Úé#Ò”€Gcí|ä@Óîp$°‰Àı}†! $Í«X­kªÒÉdâô67YGáÄ8sª,¤Oi†¥êlŠİN*+¥K¾dzG.SòQdÓÄ¿™(Œ…¨ÔËx³âmÃÑmD½¨˜’L¼q|G·áR“I€E2k…Ä×!2@âQƒA”’õBÅûF52ë@ú?‡$w(6]ŠHŠÆÁLÚ«7^#HFÒŒcIí‘*5w‚š„®ú‚«%şşõsfh X´æoŞj¼ñãÏ>õ¹Ï= ¥§wî,ÜıÀƒ»Ï¾r¦<X)»çm+«kmÙî¤®HÙëLé°•b>‚v§ƒ\>×óáù>¸aÂõ<Xœ!·¸ˆ®aaQBOç„@„
C““ÈÏ,`ÂÈnØ•Ô!(œƒ(N€Õ0‡ó7–±gÿNÀ»CMçO$ê§Â!P¾J)üfßşàÈô~qh3¡2»ö1U‚H\jº(ıê½˜ıÁsxøÄ½†ÇæŒƒ‡l‹QŠf«jÙğ„BWILŒbñÊu=é3g»İ6L+‡ëauuåR9!.…a¨ç^gÎ_ÀäØ(VÖøŞó/âÓO<Æ´ç¾µ¯¿”÷Üs7şú¯ÿ­–v4œŸŸÇHuù|”P|úé§ñ½ï}wİulËÂôô4¶o›ÆÛo¿ƒÏ<ó4µULUñúë¯aÿƒ(adxsóËX[_C©\FµZÅÌõëxâÑñçã£Øˆ8#·ñ*Á0¿ÜÄòÚ|xñöÜ‡=»¶cÏÖ)”JE\gÂ+©à:†¸Ó¬%Ò¨¼mC(‰¹›7±¶^Çù›‹ğF'äoü³ÿÖŸ4ƒ\İÆËèûP‰^’j=7¢
RJ-‡ü åÁ²,—
xıôu¼øÚìßVÉ$ü ÀJÃE†™³1fBK() c±lÛÄÕ¹%üÃù§XìØøî›WñĞñİ˜Ù†ÿñ·N ”7ğŞµ¾÷ğGÿêË°M¡PP"Dàvqn¦PN»M?ÀÔ–©ö@¾Øu6Z38ŒUÑk;‚(ø§Ïo·Û–_fRùÄ4éù3CìÜ¾sC)«33Ã$¶À)‹8W’€2%„$½Ës¶ÇµCœ!Õf@”QmÿÊ¸2 Pö¨ Š9N|_®$Ä¶m’Ïç	g"Sè<½Gœßl1VQ3ÀbÓ—˜ÉOR	ÉÆæÄˆA5Œˆƒ’ñ©'™êCşÉõKIÒDwæ4#	!tsOæE•ùYl¥N‡$Ò§gŒiâ>$Œ	Ä £A“Fi¤‰K"M×˜wj ¤"I‰÷
w0JÚ—H2*Q"lOŠ=¤d©+%úå‚P 2C”ŠèÂJ"ô@(¨ˆ™/³¼ƒhŠ×å,#%Œ/—Äà(²‰¦ŠD>Jıã#YkH%‘MbLõ’™ÏQ%¶Å2Z=AMbúÍ»™¿×@*Ã4ùı>¼ûÍ_º|áìÙùáÑÑò]Ü`éÖül±Xœ¼÷¡‡÷œyÿı¹û~húàáÃ#¯¾üÒæ¥“öá‘­VŒ1¬×j  ªCPJÑqòİ•†¡ŞšKX)U°¼º¶{A aÈK:2/@D_)Àˆ	NY”p¥0/}t¿ş¬H¬#“÷”Q» fÛÚH)| $à:€mâµ7ÏãıV¹á2ˆ”à,²¦ıŸø91J±°ZÃE»‚1Îa·60yà ï§“»ƒ2%èußC»ÕA¹2¢BJ02:š(*4TlÂuäòƒğ½ ó˜Ş¶Äà TËà(!è:\¹:ƒgş^|ãŞ>y¥¾ÿ8šªcäJ¢Z­bzzçÎÃèè(–––±¿!
ù<öîİ‹‘ÑQüİsÏá|ùËğ\»¶oÅßıİwñùÏÕ‘	LoİÀïÂÆF¥r…BœÍ:Êå2põêU”¸ï¾»ñ½ï=b‘ßñ‰bqi½PÍ2¯œ¹@¦rÆ‡«Èår(‹((°L9Û‚³1{sï½÷z„BŒãø¾ìß{àhõŠO
>¹í,ë;©f{iá’ÔL®®×#×#ÜuH1o+Ë°Jñ¿şÙ÷ğ¿ü“û19TÀlİÃZÓE·çÃ¶L}HeU-2U+()ñ?ÿÑ7Ñ”Ø½sósxÿü¦?û¶íÚÎ€¿ø“oâÕ×qø[oà¿ÿ§!]Ğë¢ÙjáÜÌ:(ç<¡/F©RR’P„THAnÒ
EèÊ2LÁ°*bÇ›jª¤RããcíZ£Ûh5ó™èSÅeLJ¡DaH^ÏPP0LC0JcL&“£Êä\
!˜Râ  œa¤ã'Œ˜¦Ë"½HÅUÂd’Siàú$º`±ô´/Û'{ı¥Ò½èwŠD:0¥"ıTWNx;iX6æ6ÓDln T:Lô]˜9@Eœ¿x¤±#à&'0óø3OãÆ!ªøŠÆä7Õ·ÊÜì@@ıš€¤>z›Í‡’e†ÊÜÒF;Y†ÿf#«4ABJšÆÿÆ£2‰-É&(>%ŠDI “¡Q×êX ’•A¬Pñç{FÏQŠ(Ç!&TFˆŸ&F–Jõ%ÚõQ¦} IWùš Ê ¤Rz~PŠd"üDAĞ/O¡¬TŠÛwí¹pöÜÂ[¯¼zyd|¬²ÿğ¡ñ¿úÿqnÛÎÓ÷=ôĞ¹k3«ƒÃÕm¦ii6õ¦P3¢™êÍÖÖ×aÛ6ÂP Ÿ·Ğiw04XAb¬ÃÜ•Kz7® ¸'zÿ8CÎäà…"¬r	®/5'Ú­pËÔ‡etXvo^]A«¶ri@Oè
 …ĞRÀÕ:ĞJ%àÈvÀ&@Ï6IÌ4üïƒ„À	şãKçá—ÆaF+‹äˆ*£İ:¹£±	!@×sA÷AãÒì;¼†m"ì}¼!¡¾ÛFg½†J©m´ë€çóPRÂ4-\¿5Ê´‰!a QBŒbm}NÕ‘aX¦‰¶” ”àêÕ«ğ}·Wñö{çP,–ñş™+Ø·g
ù5ŒM6+&ÄÁ£Gá…~„Ï|æÓ˜Ÿ_@†p{.\ÏC½¶‚£‡öãÿø?ÿcC%,‚¥psö:>8}
»÷Âúê(QxÿäI9´¶eÁ¶-t­Ò0¥RÍf<|?¾ÿı~|ñ…65*àµºä¾ûööïİ'Ï]ùˆ/7´¾ºBÈJÛ¡Çƒ³¶Ùut—¢ØqÿÃİµ'Ü62KJ)ûr½ûç±oÂC!@%v—\›aóKtiat;•B‘'?”Êei›½¾ÔÀïÿÛ ¾ÑCõNˆFÛÅ–œÕGUÑj Ì¢?ı‹âÇ§W1¹e+:­&:Ng.ßÂo|öAäJœ<w¯œ¼Œòğşø;çpï-8ñàx­e¬4ºX¨¹àœÂu{è4»‚mcR%µÍ¨‚¶Ã„”„„!‹|ÿ	cL† 2”°,+œ›h÷z®!•ÒF´Zâ&t¨)Ñ>„ ğ}êÂê(
ªòùœÔF;$rÔ+Hæ¦>i 0ciX`&,‹€aS¤ÍÑ>ù˜<Oò,òîµò}I{É~=}ÀDæH²Ùôıaòqó‘ÆõÊd§Ÿæ†ĞŒƒ_*pÊN}(È¦Â®6ùlº˜ÔJ&Yq×@¢]~Gk™‰èÛÄI«“FÌhT@i"ûì³L›­>2]d™£2Ã™ß“÷”ÄÓwªbˆ«´LVä$SôãÁ[FI€Q@2~J¥2A!"ĞÍ‰~1oAB2I"<ts"dê®)Uj8¤ßŸè¶‰b!UZPB!!b?„äÇ„¨Èê'Œ"¿ ¥Äíö‚7_zåâı>²÷æÙZ«Ùt_|îû§ı·~ó‘ƒGŒ¼øƒ\º÷¡‡öî>°|~n®Å9¯øß¿ˆ0R©ŒµZ–i¢X(è.;z-µz¹Ba¢Ïcpe	]#‡EØét@¬¤*•p¿‰ÒÈº7—A£@B‚E.±e§e0\®|peO>TÂÔà¸öÑ,¿
‡'·C)[Ë+(ìœDñá#(o×Ñ¹}(…r; ÇÙ/á¹+Š[¡Úk „j÷&ÆõŞVÎï•‘0@yz+Ê{÷ ş£ç°ÿıüŸ"çÌ™ÀüûçÊ(T±£ÓDÎ4A	°òEÌ­.Â, EQ(T ˆ¶XeÌ€çv ÕÖ×kp:Œ'»rH3çÎc`p o½s P, ÕjcöÖ
JElÔW102Ã°&''`M0FÑíva<ßC{£†ns;·âë_ÿ|åË_D!ŸÇá{ñµ¯~ÿ÷ÿ1ªÃc®àı“ïâÑGÁÀ`„(lÔj	„W©baa»wM£X(À4¹óÎÛmÿ¸şö«_3ÿÕş¡û…Çò·×÷‰DDŒ®åÕezkş1Ôáİ{ÔÖñIY †H¦ƒÛÖ£1¡‰ÜñqW5ºÒ¨Ñ›‹óôÊ¥ØúÂ"ém´ˆWkC9.Ln!$–&·Ñêøˆºzù,ÛÆj³…‚ó W`½ÕÃôDèó JÀ²M\¼xøç/£RƒÓiBIDxcaU?Qƒâå÷.¢ã*äzH«ˆÿıëoàîƒÛÁd7W{pC”zCZº;ÕG‡l†lqy±à>'Ä”N¯Ë¥TQ„!e”)©$
ù¼_.½v§céí÷™–ûÅ{şÈ+]z¾ÏĞi›œsÉs<Œ›vÊ˜¢„Ê‚ş"“MÁ¦!pmålTùÑœ13B&÷6m|*UY"Z<!gDGÓ!/ÛLd$y)õ™Ï*<(²Ë²ÉßGİ¦Ñ¾3O¹OJÙ7ùô]Æ±Qª¾Ê²9	/}jÙ×ıG’ØYVJA
Ò9œ}Î4³SW*kI–+ªß0%’Œ›İDl$ Š`ÓKH‰H:–	J“¤RŠ¨ˆ§ßÿ´i‹ybiŸ’I´0A ¤“G&@‚Gh€Lƒ ¢ÄÇ„ 2²ìè3J¼Hm¤ÙgAüK'”1ºxk~cuy¹uèøñ­ï¾öúµúz½÷ÂwŸ;õ+ŸıÌ#?¼P>ùæ[¿ÿ¾ı[wl/<ù¾’Ê!Y·)np]C•
pÆP*—Ñó<†	ËÎ¡Õn£Õj!oç  lc
ë«èTÑY^A~×.í_­Â¨¹ÈAİ˜`$‰B†iƒ1–|È
-^Äó§fñäƒ‡A)'®^™ÃÌÌŞ:ÿ|BQ&¹™+(­,àñßù2
…B&#@¯ˆç LàO¾ûêÖ0*ŒÀÈ=œQÅ‡!À;Œ‹,t±ãÙ/BµZØ62ˆÒØ(¼™ş	%°-Šk¯½‰×¾ú5Lÿóÿ	ã¡ä´111Š[õº=•1ÓEËó Â ¦78ÂĞe]x‹N»ƒZ½F³	ÊÃ„­V·nÍÃ²
¸vc¶ƒ’ÚµğòµYìß»ËË+¯£2:Hİïİ»çÎCµZÅÂÂ"öîİÏóP¨¢Ó¬ãş{afæ&®ÍÌâàş=8ñÈƒø“¯}?şñ‹¸÷ØA\¼p]»	ßQ¬€ X^YÒ»9)Q­VqãÆ,víÚ…í»¶áÂ‡WÀ˜ù6$
Ü4Ñ¼µ@¾ù¯›ÿÃ¿ø×½œaÃæfº¦0¾cG·ï…”œ²şÛÙMúğE¨U*„c­½AÏ]¹À¯\½L—fnĞ¥‹—IoyÅR…r”0ä‰ZÈC)	W´1½gè®¬P¥À!0M€qˆĞG»àÖj÷¸k@”(Å¿ùÓïc½#Q¡Ú×Ái×px‹ßşÂ#½ <o!BØÔE³ÕÂPÕÄGñ×ñ_<5%ÇVû—¼õ2#„£ÓéĞHyó» %H¨ı@)“ŒrÙëö©1CêóSAq%)¥*C:8XéºÇÃ0¤ñÊ“ÑÎ;ÎŠ£V#^@SJ•eš‚Rªtb(W$•úÒ Lƒ€EÄ|J@tôª‘è¼³pNvêNHw$K¤˜\eñ$•Ä%¨û&Sİì„GÎfÙùRõí‚Ñ7#“Í”¼ÛPğŸfİò“L]ú¡ø,,-"6]„Óg,˜U3l6e”¨!R›³ş>B%ÆG1QdŸ‰9ckİŒup¢5IV5ªÏÀ-}húÇ÷‘Qbô…l2`Ğ;í·;F
ñ#ÎDœM UD€L•öÖÎJB
};&d´†–	dŒT)Á8	%¤Ğ‚¤Ûd}ğ÷ºˆBJÈ¹“Ü|êóŸ=R)ÖÖÖœ¹«×jNŸ¹ğÙ/ıÚ¡ÿÇÚ>ıî{9¼+ŸËoÔëÉŞ…0Û¶ÑëvapÁrëëëˆôéy;ƒsX†Æ†«UB b0ó³ğÇÆ­«(ìØ	©rep²€âèHŸèPI	nØà‰KœŞ·˜¹<^¼¼æZƒƒà"Ä“'îÅ“C{Ğ»ÖnÂŸ€òCà‘Ã°&F L¿´”@uÛ Á»ï_À7N-¢0y*rk¢D“ò”$pó[)ìrÓ?Œî™S8pÿ½·YÿÆ—2·)Ğópá›ßÇÿÏŸ?şyŞú…+0×V`n¥=×Àí®9Øi[SÓÌƒsa İvğÜó?Æ‘ãwáÄ£À¶-pÎ0{ó—×@X<ÚQ™¦‰ù…ˆP`½ÖD»±Re”2x£Gâí·ßÆ­[·àû>öíÛÁ°ÃÓ¡OÿÊcxûäiLŒ¢:TÁ§_ıêWqüßıvï;€—f°¸´ˆ\.§ŸÛIº~Û¶Á…<ò N}p9Ûú©K0ƒøè­wÙ™gÏòÜx¾Gúa|•dxêÖ¦é¹Hàx¹±²@¯Ş˜a×¯^fóW.“Æâ‘n Ùqa2ÅBÕ­û#¨8ı–J%àõ\T§Çå±CûüYÂLË4DŸa*ôáû!n,ÿ¼½w˜dWy'ü{Ï97Uî®Îaº'*Ì(Š 	$0Á†İÅk>ìÏé³½û¬y¼ØÏz±×kã¸Æë5k0k°	&‰ ’BHHå4ÒMîéœ*İtÎùş¸·ªî­®%¯á©g45İ·nİô¾ç÷şB¥ı`LÔ¬-ğ¹o<ˆ;>ŒB¡©BøÕE¼å²q|â£ÿÛ&Gğßÿ×71¿¼_ùà›qëÕ;ğŸ»ß|=C“øÒ}‡qÍv®UÒç_Ò£ŸzøÇ€RXYXæ¡’’’"sŸP…2dïqÛ¶¤ç6˜àL¹®k0Î´&"ÒBp¥”"†$ƒ€õ—{ë®ëË+Ë™Èz®ù@'Ûæjhè07ÍÓA°Z­f„AÈ2ğ˜ß3ºA-¯âQ8	Îç‚qÎ OAìé•x»0¶ ¤ÏCÊû&nfRs!J¬‹;Py "±âí| 7-K°ÍSlè_ "4‹ebÖbíéİ‡îÖ•4§ºUš@g‰ïF]×IíÏT"ÕŠmN·	”Ú›n'ÅáL„È²iZ¤ZÍHÒ!*äM÷Ñä¸"©SŒ ŞtókiÿÛrF-#®‚”‘)Th5¢²Ù($¥¸
Á¹©63Á…LÑ	èµŸøW³5• +Ë+µc‡^šÛ{õ¶E0gO>üè	¯á.¿ı§ß=!;¸ÿÅ£Zc•µ²6£/ÚÎh=eôöôbmukë¬­¯AÊˆÁ†!êµ:ÂPsƒ‹³L«¾B‡ö˜ÙƒÃ*õvğ„iD™è‰«Ê1^X%üèÙ£€)¬‚³¯ˆRŠÛwÀî„S.ÀÙ1’iu(	r×¡Ü:>ñ•°–É3;ŞôH9QĞ©.%PàbèŠKÁ¢²ş-“Ö¿ÄL‹aí¥#¸ëã¿o}á+(ÿÒÆ•¿ô«àø/FcyË«è-åáº>´Ö°,ÕÊ:dØ&;j­À¸B±Œqœ9=…©ÓS`qÖ½Ï¼x 'Î,`i¹Ó0[–s†ZÃÃj¥
©$¦§§áV£Ha)%,ËÂ>ğx§z
aF+RÂr2È÷bl|['Çpè¥#ÃW\¶*tñ_ø"ö\r†‡pâØQ1Øq² N¸a~n7½éd³Â |%#+ø+ë¸÷ÎïšÀcD,ıœÔçZ1EŸÎÃru¾·ïóSÿô÷öÿü£ÿfñã`<ù¥ÛÙÚÓä4Š¬€¾qôõÁÉbí²L¸ŸEçÕ=ŒnŸP;&‚¡QÕ4çiqUˆpb¶ŠPé\LÈ:6xò0>ö7w “+Âó<¸kgñ~æ
|ñO~ãEÕ©CxÇƒøé«GÑo¬cïÎA|åÏ~}ÿ¬/NcjYá¾ğ\»G^pÑù¡e9 ,-­pÏõâÆT‘„,%ó=OD™&L+­)šÏ3ÍWœsEÑ\?
¯å\¤l&ë†\¨&	Šs®@L5	o1Ä?ÏJFß®5i?Ù™™é‚Ròu˜¶WòLÆ9'ÖòÕoÚî²vdo"º Ô¿¥MLZ“ù6ŸëiıŸÚ	~-»a°Ô·M vÁlÉÛÃÍß6{Å°¶£!1ê†¸§>$Şc-jÚ%³W’:@S¬}ÌYÂ8‰5Ÿ‘¬¦Ø¹Ï	D„Rã˜£@”Ê1 O¤ Å,rŠ	˜ñç2ÎÚ.Í÷Z–Î”Ëâg9çBpp!â?yô†€a˜¦€i0ŒèeÑ"Ö&LË‚iÙ°,–eÁ±-˜İúoÛ²àÄÿfZÑßMÓ„m›†ˆDŒíPi¯\€ØE¯¹S¯ ˆ_Â0øç÷ŸÙºkGÿäÎıG€;oÿö¡wğg®¿êúë†}ğ¡i¥dE#ò6ÕñÍP,–Z9×ÄÎÛ±Ë‹8~â8ªµ*êãcc`Œau}LÔkUØ¹äÒù*sgÑ³s8ØŒÃÊça2ÁŒèè˜¶“fûÇ°Sh:øÊ¾cxÏ—E^(xYKÇ^¼ ù<Šï}PÈ€\?1|c@}0	_ıŞ>|ïH…­[¡eĞ
¾æBÄŞñM+Ãİ»Ö0aË›nÄò(‚‚R3_b–E8ûèãøŞgÿKı¸æ¯?¡ñ5`öÄ²'#ß×‡…¥l-– ]‰ÕJ}¥^<µÿi¸n#%[ÓJ‚“ƒaX˜™™´†eEpúÓ=0Í¨ëT'gGÄEçmÇ©©3˜ÜºN¡7’º.FFFğÑş>ùÉOâØ±cØµk<Ïƒ’!J}ƒğlÁ“Ïî‡ï0w¿ı|öŸ¾Šë®½o~ë;ñàO„Ã'Ëe0¿<‡ĞÀEä<888ˆ‡~7¿ùf\rÙÅx|ßÓÈ¹—E„8°ïqö“Ç6n¹şfß÷½vOß|¨všìh`½Qg§f§é‡lzâIV[X&¹Z…cf±eô|ğx¬ÓöØGTô7İB ìØ¹=dJ+#c³½×\=ô¢Ib	œ3œYl ŞğÁ…ˆò8Ãz#Àï|ê^Ú|F¸†?ı[ábH€J    IDAT†ŸûÚpøô<\_Á¶¢‡Ï‘©%ìİ5CÓUüâûo„Öÿûgpß~—¼¯îºp›,”Jzuu‘ÖWÖy(%@•jÕœ›ÍÊ ğªË®QÏs‰1¦çQ`çºÉ†¡25µœşt¼zç·d\±È)PsÎu|ÿGÜ/Æ@ü `ZiZ­T¬ñlÇûU.Tš
¬÷l“'›ŞP76­8fBï¤ŞµŞah{ô#šó&ãx“ŸÚ²÷Õëçk«(†:¯­öŠPG$ßÄ0#Z'Çè"Ä;×´‹Îyl“HEëD³Äûºƒx˜dèôˆD§fM@ŒÈèæø»9–ˆàüöæšÇ½)iFsgIwHë[³	Ö’82 ¥ìh‘!YÒ
˜Z é€b­k°e<Ä	JñXb©c*‚j%©v“”–iÀ÷‚vN‚W:Aç ×Œ°×zg@n£îú™©=—^2–É8& Ö¨V—pç÷N½áúëÆ·ïÚÑËˆ-¾¬Vàœ!_È§Û	Òè/—±}Û6H)Q­VP­Õ  Fkkk˜_\ ¯UP˜EĞß‡ù™ùˆ„Ê92"—‰˜Ô&„8¹bL«¡Ô,5ã8¸ïø:;|0Mh?„3VÂÔµ;ñ]µÅÛö»·®Ÿ&ş> ë8;=‡?ûÊC`àIGÁ(Uç-&gdàÒ!'Tù¡~·mÁâ#‚¤ŸĞ˜Á2	3?{îú1r?û¸í¿§”Ã±ıgğÔíwböïÿWoÂ57Ü€l6/Á‡ë„’
«‹KuëJÁ´2p2y,ÌÎ!B†	ß÷qàÀA8N.aÃÙ>f–iáäéi”JEx®‡Å…9¸õJ~B¨Õj0ï}ïûpòä©„L)º¸{ÇÑ?8ˆŒmaumJkŒá¦®Æşábht^xNœ<‰\.‡Z­70Ñ'—ËÁ¶mœ:y7İr#ÂtW|n¿†ª‹¯şıgÍƒ§sÓ4uüPj‘Ò’7àû¿$şä/ÿÈşƒ_şûáÏ}™û§(/öO §w8²N¥{É—)şQ ™w0:¾E†Aßuõ×_i%0Á£ÓX¨J,­»-ÏyÛ6ğ×_{g|¶®àSÿé|øgß‚ÓU|{ßiœwÁÅxÃ5×â’K/Ç‹//Œà‹?>‰OçiÀ)ã·~ş-¸ñÂ^ˆÙ™9^*©§¯OéHRÊB? ·Ş1±OU*U›s¦Ç2X¦)ÃP¦0¤`\	.¤!š
éØvàXVX,¼R¡èrÎ¥i¡à¼åÍÊˆ4c1 YÊ÷VƒéÕÕkiyÉ,÷×ÑÆDºWLXnûæC¡Ã*VwÄ$W—,eË›îÛs|b%ûqb<"ÿ4WÊ‰ÕdSö—)$G	IW9F0ÚŸ¦#QJER¬ö¡=K;’˜:‹„Ö]&º¥Fx5;!ŒWßÔÌOh}6kã&ÍïÃšæJqîBÓ!ùİX[Ò¥)¶„æ1o¹.ÆÑÊÍŒ‡(g¡®ÄZ¯¨1cÄÄfŞXk;ÍsÉóP€&BzOpàÑ=-„ˆˆá’ `˜LÃ€•@Ã„i0-#R¬˜lÛeš-O‚VŸ¨¹#§RãÕæ ¼&`‚« Î?vğÈüÖ;.¼ô’Ñ'ŞwRógÎxæ‰'Ş|Û[·..,N¯­WBÎ¹(²ÅÄÖ­8}êV––á6ÜV^{_OÂ-§§§0;;hl.‡\.‡¾¾~är9¦O¢~É%Xó$‚j¢…Ã"İ¨éXğk.4E«1Ë¶cFfÇl˜4–Å~ü".¹hWdìù¸òºËqş5W¢”ÍA×‘ëKv4V ¦ğÇÿ<_Ï¡8˜…n:¬QT\‰•Œ.vÅSS€TˆòE 67¹¼fg ¥j±…›aîùñ£‡ÃĞÏ}8òàAøÿı‹'q±[ÇØ`/ÜÚj”ÂW.!äÒ •B¡Ç¶-ØïÈä‡»Ü¯N&‡Å¥eø¾Û¶ã€œ:LÓj=“ÍƒaÌ/­cµÚÀà@?¦gf14º'[h­b<ÏÃÖ­“˜=‹§OcÇ¶m¨V*PJÂ0mnÅøØq<öä3x×Ûn…çy¸ñú«qâÔüşÇ?ÿüÛÅóO?
ƒ3„A€ZµŠ|¡IëÂ^xN?;v ØS„lDÙ//	cX9v_üìß[¿õ±ßUEÛÑ2"uRÓòÃ|Úâ?vê$øÛß‹/ÁPy,;?L8 ÂĞõÅˆ^à¢4Ô«F‡dJÒR¢XÊ©wÿ›÷ùû‰?µ¢8YšG˜YªaËp–)ğİ‡_Âç~pR	$şú7ß«vOÀüÉü ÎàR.—O ÊG¥z5®b>‹`­‚_Ï¥øÉówãÀ³ùûù#ãÃêøáÜZZZ58i=80P-eó~>“å^Ã•‚Xè‚44IÇ¶MŒ˜BÈ¦ñ#¦µÒDŒiÁ¹ªh­ó®ç	£RiâÑ° –øµÆŠä‚L×ê£Ş¨Û'·-ëS³
ákªÿ0‚!¨U\H˜âĞfÃô6S>Y+•Şà¯Ÿ*”tCÂï?ÍÙ8kOşt0ôSÚÿæº>5c×íQE
‚èNÔİ†÷¤×–æ>yS7l+LˆºÏÏ©…u¢4¦Ó&"6ó"è”çO‹“ÀÆKšZĞ&ò`M5!ÅõhºX¤“[©óD]¢Îs×>îÍ†’ZÄN0ÕfïÇËw–$˜¢)d- uT„Öš–n:²î@r€¨o"ıĞéÎ ¤’ú©}Øºsû@ï@_V†!„àõg{âäâÒİtÛ­#¹|²ÙvŞú·aï•—ãæ[Ş‚-“°3NÜEGšïÑáä²Y,¯,£R­B†!ÖÖÖPo4P÷|³3 Åx¥ÖÀ(êbH0²™8r1ZbX™,R¥ME´VÈärøêSgqäØim@k72èéˆrÂSº^Ô× SâËw>‚Ï=>ÌØ¶úOŞdR‚Å2@Ù²ÖĞ¡L1„Ñ»û,<ù,ò==:ÚG€`Ús/Æı÷?‰ÛnCa¸G¾|†îù2®¨œFèÂoÔ13;‡•Õ5Hé!—³ašFÔB?ÄÎ]ÀÊfZŒòŒ“ÃÜÜÖ×+ÈçrÈäò`İı'.Æà
g–+Øºu‹K+¨®.#ôı˜ızÁùçãáƒ/bºZAÖq µF(ØÙ".½ü*,.,ás_ú:</@øøĞÏ¼'ÅßşÍ'1<Ô‡µõ
µZÛERJ‰R©„-è-ä!¥|Å£+ËrpøÁ‡Ø—¿öU{¥Ñ` ¡ú˜YY`_¹ûëw~ï·Ï|â­û?óO‚-Ÿ¼™l¾õ€P2Ü9üjæÑ¾ïbp|Lå2¹ÔÕĞnİÕW^epÍoRÒó DÛ*™g. c›˜]®ãO¿ü8©ñÖ½øìÇŞËv!ày7 gaÍ¼ r}n£Ïõa™Ê¥ÂÀƒçVÁN¦¬O9Î µÚqşv¥4†[_­²R¡è¦)…º¯·¿‘ËdÓ0¥TšqÎ WŒ˜‚+Î˜fœiÆHcº-¯Ğ°,+ì¨ö–zê†aHF¤›j€È‘š@ZÇÔçæêTi…ŞRcltt])E¯‡å,(
öDŒ"7ÖÍ·G	É¥òob­wŠ¤á¥m„)	4·I	ôm<·suNÔM2—&·%“ÓÁBÔJ)L³ó)1K§M`ã6"K¾:Vu4I´ÊD%%Ú@ĞŞwoÛ*'¿k¿ôŸÔ:W­ÜİŒs`-T²…H4÷oDQšI¬5®é€Õ[ĞÆ±Dòß›QÎÍØgNm$©İÌR(Bä-Á‡àÍ‹x1ßÀ‚µ„ZVq$Åyã¯ËèU5 ºĞ‘ë›Ÿ™­éØÂŞ7\5	bDÄC·V_|jßã3¦iš½å>^©ÔpäĞKxğşcêÔiÜï}˜:5·Şˆ’çB‰ AÄ01>bùÔWª,..`nqáÚìS'À†F°0¿ °20;ÒDÆİ¡åD@èûn(K0œñm|æ{O‚@B€˜ ÜFôû­ xU@xøÉ#Ïã¿x?Â‘óaİì‚ˆGP.¤B«)S	#$­a8&¬ò jG#Û7eHa¼ÅE<x÷á\s=Ê£ı˜ı?ŸÇÍ«Gğ®Ëvab '^j¬Uê8~zK+Ğ ˜–	Ã4aš&)1Ø7ˆÁ±1¸ZßoÓr°^©áôô4²¹<zËe0Ó„ŠIiİ¼Â1ÌÌ. `–i`êÌ4¼F%õ³RJô”JØ2:Š{xK:¸!@Q³ˆŞÁQ¼ç}ïÃñ'ğõoß‰†çC†Ÿûà{ğÀOÆìì†† µ†ëy©‡”Öııı(÷¢˜ËDúW8ûbŒÁö}õëü‹ÿü%û®'²şêSå|ì—Á¹ûïş¨š"³
2½0MaD?^Şr‹R¤². „*ÄøömÚFë)m^ëó+ÿŞ›Üy‘8o„B>=7‹Õš»?‰Z pİîA|ê£?…m£eÔC;Û¯"Šdcjù0¸\†íX0MJBø*8g¸çñ“xÃ­7…B^ïêE¾c×ÎĞ4MH¥P«ÖÉr¬P†’ÂPQ†<Tš1RZ‘0­ Í×ŒqÃÓ:rK£5I©(ãd‚¡ÁêèğHÅ0ùpM İ4bÄŸR+]VpCY¦Æê×§@ÓÙ;Šv¤f0Tª€&ˆ{IwóÑªg1^ùGä@–.l	È=ÎNôüÔ*›Âç)€m(ÁÉâÉR1¿al°41õ}ó¡Íº£&ˆÎ×9m„KèœMVcSÙt‰%T	R`<bá<*¤-›ftŒHX»Ic­QJÌÑJ5k¬õÙ©ãÖ%4a$¢®AêXÅ£ŸˆG)Í¯Î¢„ñè{0ÆãF!1æĞ:mJ¢7B2ÿJ@×Æ0°çŸxzªP,f&·m-«PJËr§Oœš;uüäjÿ@?Üº‹å¥e¼tà0^|şœ:q
«+«‚°¥‡XzŠ=ØsÁ…¨».–WV@ ,¯® Ñp#Øæ¥Ã03YTß“0­%œš®D€m;‘CtåHØù<¾ü£§pğÅ# “CnTğ›qèFP>|
û›¯ãäÙY„ËS:ŠS3é‰sÎ8”b³‚
ÃvÔVà!76Ùp!¼ "Ùƒ àé{Œà‚Ë0rÑvLşp½—n…àÀğ@®¼h¶oÆ@oYÇÆzµ†õZk~ 22NŒò™&wlƒz]ıëMÓ1÷Üs7´”˜GÁ± ¥Ü”1Å9ÇÌ™XNc#C˜>;‹õå(¦› ¥°wÇ.A€GŸ~&6‰©R*ì½òjüê/ÿNÁwßJµ†¡ş>¼ómoÁßÿ!®‡Œã UrqFFFqÙeÁuë¯‚gL Dh¬¯â®ÿõWìÓ¿şëÆÁ;ïc%Ğ›@¡ĞÇÉCÊ°+²@Äã”%Æ<NÔñïEş İnE£cãZkMa²ÀYH¸Jå">ñÙ?qÿúKŸóú‡F5™øúƒ/a×ä >ö¡0³ÜÀüš¥¬lÜÊÄÖ­¶eâ»?z¿üñÏà|şøÄg¾‹¸ãè8}^úu¬Õ%¾ÿÈKØ¶kR¾ã?íxö ŸØ6ærÙØZºÁ¥Ô`¬™õ Ãi¥avh†ŒBn˜ü€¹Ç†h4\ÃE:hh%UÌ¡"íØ™`tht=—Éùqì¯¦i&Æ”:­´&Ï÷ES-DôÚA€–q#bŒ#£ô›³Ùã£vëD ÍŸÑT÷t#ËQwz=á\şÎ¹ë;ÇG»ù`íÂJ°ûXÇöhãj–èœfÔORñ)($6G/ƒ‚Q‚8˜Ü/J¬–›+û$G’¶š İ%’›¿ÓV}°ïÏX…ĞÉ†*Å¯à"Ûp^tÊÊ)]"Ódj_	$¤IjºN¶ò€¤ª¦š‘ºšşo4 ÔN–Ú8
 z½<÷ä3§/¹êò-¶ã˜‚s—4Ü—^<8Íæ|Ã4"(8±¾¶Ş^h©â?¥„”åì˜Ü†õJ~@I…P†ĞŒ=¹0°Ğƒõ¥E8Üà0r´Œ<Ó°3Â €ı‹¡Ñ¨bKí$şË;nÃ—¾÷ÜõUPm	Ú­¡x5`õ,È[ÄñãgğG÷müüoÁ¿}Ã^ì	æ0u:}ƒ¨À`xÆ dĞËÉHbĞ^}{.75…lOo««·âÀB“7^…¹oß‹ãòó·AËRP2DÖ6°sË.:ocC}(æs(äó˜YYA4ò…2¶/ğpüä‰÷Üd!ÕÓ3ˆ»ïù!>ÿŸ¶“q µìz'k­!8Ç™©ixš088 ÛqpêÔIn=5R"gYxëe—cij
§N‚a­íHÜøæ[ğ¿ñë8|ì¾{Ïı¨Ôª¸öª+°}rßºã.#»¡yiÂğ·Ür'J÷{¹â¬¯/bqa
J)”z†04ºƒC[aZ™x51u“+y"Ö*úRúhÔ×Q«­¢V[ÅúÚ–§±0
ËK3X[Ce}^—¦D©(Ä»Tê%­£8 ”’…¡$JbŒÑø¶½ı¼íÊólÛ2ŒÙ[†Ê˜)ãìª‹}faÛ4xL´`L ZYÃ%Ûz°°ZÃÇ?}7xá(&ËJğ¼:¾÷èI›­£X,â–wŞfÂ´ÂR¹_jh4¦ãV­ÓĞd;NFŒBk¥I+ ğ™ç{¢Ş¨•jÕ¬7êFTüi¥Hé8-"G2¥lÛúúkù\Ş#b)C™ègÀuÜ÷ü„åŞk_ÙpAÄxÓ¸Ww(àİÀo@¥QÎ&ï/.6³ti3]×&€Z¤¼î¯6.Ñ8Äü“f³ÙLL‰İY<¦Ô¬c¦‘şYn&ò]‚Nè¾3oÃWí„Ä»¬ü“¯92™›ĞLOLòhS$ºşLĞR“âI¬À[RŠ˜SG-´€µåŒ´QFÙw%‰¤*áVˆ£_oh„hÓÑzû‚l^kºm‘ì´¢ı&¥´VJê×:xM> İ^œ~äÀáùZµæ_tÅeãJi™ËåjKKµå…Å³‘«\ä‡¼¼¼­byKâÕ$Ûèx¥880„ro/nŒ1óŒ¡Ï¶SL_R_SIGNATURE_ALGORITHMS_ERROR		 360
#define SSL_R_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE	 220
#define SSL_R_SRP_A_CALC				 361
#define SSL_R_SRTP_COULD_NOT_ALLOCATE_PROFILES		 362
#define SSL_R_SRTP_PROTECTION_PROFILE_LIST_TOO_LONG	 363
#define SSL_R_SRTP_UNKNOWN_PROTECTION_PROFILE		 364
#define SSL_R_SSL23_DOING_SESSION_ID_REUSE		 221
#define SSL_R_SSL2_CONNECTION_ID_TOO_LONG		 299
#define SSL_R_SSL3_EXT_INVALID_ECPOINTFORMAT		 321
#define SSL_R_SSL3_EXT_INVALID_SERVERNAME		 319
#define SSL_R_SSL3_EXT_INVALID_SERVERNAME_TYPE		 320
#define SSL_R_SSL3_SESSION_ID_TOO_LONG			 300
#define SSL_R_SSL3_SESSION_ID_TOO_SHORT			 222
#define SSL_R_SSLV3_ALERT_BAD_CERTIFICATE		 1042
#define SSL_R_SSLV3_ALERT_BAD_RECORD_MAC		 1020
#define SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED		 1045
#define SSL_R_SSLV3_ALERT_CERTIFICATE_REVOKED		 1044
#define SSL_R_SSLV3_ALERT_CERTIFICATE_UNKNOWN		 1046
#define SSL_R_SSLV3_ALERT_DECOMPRESSION_FAILURE		 1030
#define SSL_R_SSLV3_ALERT_HANDSHAKE_FAILURE		 1040
#define SSL_R_SSLV3_ALERT_ILLEGAL_PARAMETER		 1047
#define SSL_R_SSLV3_ALERT_NO_CERTIFICATE		 1041
#define SSL_R_SSLV3_ALERT_UNEXPECTED_MESSAGE		 1010
#define SSL_R_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE	 1043
#define SSL_R_SSL_CTX_HAS_NO_DEFAULT_SSL_VERSION	 228
#define SSL_R_SSL_HANDSHAKE_FAILURE			 229
#define SSL_R_SSL_LIBRARY_HAS_NO_CIPHERS		 230
#define SSL_R_SSL_SESSION_ID_CALLBACK_FAILED		 301
#define SSL_R_SSL_SESSION_ID_CONFLICT			 302
#define SSL_R_SSL_SESSION_ID_CONTEXT_TOO_LONG		 273
#define SSL_R_SSL_SESSION_ID_HAS_BAD_LENGTH		 303
#define SSL_R_SSL_SESSION_ID_IS_DIFFERENT		 231
#define SSL_R_TLSV1_ALERT_ACCESS_DENIED			 1049
#define SSL_R_TLSV1_ALERT_DECODE_ERROR			 1050
#define SSL_R_TLSV1_ALERT_DECRYPTION_FAILED		 1021
#define SSL_R_TLSV1_ALERT_DECRYPT_ERROR			 1051
#define SSL_R_TLSV1_ALERT_EXPORT_RESTRICTION		 1060
#define SSL_R_TLSV1_ALERT_INSUFFICIENT_SECURITY		 1071
#define SSL_R_TLSV1_ALERT_INTERNAL_ERROR		 1080
#define SSL_R_TLSV1_ALERT_NO_RENEGOTIATION		 1100
#define SSL_R_TLSV1_ALERT_PROTOCOL_VERSION		 1070
#define SSL_R_TLSV1_ALERT_RECORD_OVERFLOW		 1022
#define SSL_R_TLSV1_ALERT_UNKNOWN_CA			 1048
#define SSL_R_TLSV1_ALERT_USER_CANCELLED		 1090
#define SSL_R_TLSV1_BAD_CERTIFICATE_HASH_VALUE		 1114
#define SSL_R_TLSV1_BAD_CERTIFICATE_STATUS_RESPONSE	 1113
#define SSL_R_TLSV1_CERTIFICATE_UNOBTAINABLE		 1111
#define SSL_R_TLSV1_UNRECOGNIZED_NAME			 1112
#define SSL_R_TLSV1_UNSUPPORTED_EXTENSION		 1110
#define SSL_R_TLS_CLIENT_CERT_REQ_WITH_ANON_CIPHER	 232
#define SSL_R_TLS_HEARTBEAT_PEER_DOESNT_ACCEPT		 365
#define SSL_R_TLS_HEARTBEAT_PENDING			 366
#define SSL_R_TLS_ILLEGAL_EXPORTER_LABEL		 367
#define SSL_R_TLS_INVALID_ECPOINTFORMAT_LIST		 157
#define SSL_R_TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST 233
#define SSL_R_TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG	 234
#define SSL_R_TRIED_TO_USE_UNSUPPORTED_CIPHER		 235
#define SSL_R_UNABLE_TO_DECODE_DH_CERTS			 236
#define SSL_R_UNABLE_TO_DECODE_ECDH_CERTS		 313
#define SSL_R_UNABLE_TO_EXTRACT_PUBLIC_KEY		 237
#define SSL_R_UNABLE_TO_FIND_DH_PARAMETERS		 238
#define SSL_R_UNABLE_TO_FIND_ECDH_PARAMETERS		 314
#define SSL_R_UNABLE_TO_FIND_PUBLIC_KEY_PARAMETERS	 239
#define SSL_R_UNABLE_TO_FIND_SSL_METHOD			 240
#define SSL_R_UNABLE_TO_LOAD_SSL2_MD5_ROUTINES		 241
#define SSL_R_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES		 242
#define SSL_R_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES		 243
#define SSL_R_UNEXPECTED_MESSAGE			 244
#define SSL_R_UNEXPECTED_RECORD				 245
#define SSL_R_UNINITIALIZED				 276
#define SSL_R_UNKNOWN_ALERT_TYPE			 246
#define SSL_R_UNKNOWN_CERTIFICATE_TYPE			 247
#define SSL_R_UNKNOWN_CIPHER_RETURNED			 248
#define SSL_R_UNKNOWN_CIPHER_TYPE			 249
#define SSL_R_UNKNOWN_DIGEST				 368
#define SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE			 250
#define SSL_R_UNKNOWN_PKEY_TYPE				 251
#define SSL_R_UNKNOWN_PROTOCOL				 252
#define SSL_R_UNKNOWN_REMOTE_ERROR_TYPE			 253
#define SSL_R_UNKNOWN_SSL_VERSION			 254
#define SSL_R_UNKNOWN_STATE				 255
#define SSL_R_UNSAFE_LEGACY_RENEGOTIATION_DISABLED	 338
#define SSL_R_UNSUPPORTED_CIPHER			 256
#define SSL_R_UNSUPPORTED_COMPRESSION_ALGORITHM		 257
#define SSL_R_UNSUPPORTED_DIGEST_TYPE			 326
#define SSL_R_UNSUPPORTED_ELLIPTIC_CURVE		 315
#define SSL_R_UNSUPPORTED_PROTOCOL			 258
#define SSL_R_UNSUPPORTED_SSL_VERSION			 259
#define SSL_R_UNSUPPORTED_STATUS_TYPE			 329
#define SSL_R_USE_SRTP_NOT_NEGOTIATED			 369
#define SSL_R_WRITE_BIO_NOT_SET				 260
#define SSL_R_WRONG_CIPHER_RETURNED			 261
#define SSL_R_WRONG_MESSAGE_TYPE			 262
#define SSL_R_WRONG_NUMBER_OF_KEY_BITS			 263
#define SSL_R_WRONG_SIGNATURE_LENGTH			 264
#define SSL_R_WRONG_SIGNATURE_SIZE			 265
#define SSL_R_WRONG_SIGNATURE_TYPE			 370
#define SSL_R_WRONG_SSL_VERSION				 266
#define SSL_R_WRONG_VERSION_NUMBER			 267
#define SSL_R_X509_LIB					 268
#define SSL_R_X509_VERIFICATION_SETUP_PROBLEMS		 269

#ifdef  __cplusplus
}
#endif
#endif
