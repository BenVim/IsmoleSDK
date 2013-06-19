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
	 * "handshake_func"980i�v�_�}���P�T���UI(q6u�Z��BJS�_&�
5m��;i[
ѳ�w�C�E�N��[�D��"�����;��2m����3��1�־tN#�Cd͒�����36�Z9
5�aP�MG���/JѮ��E.��h'.��30�Nq?�~�P�� �5C\|�ykj�h)��X�lj!*q�"�>�m*]4ſt_kߤ��0D����+���lc�v�6���4��c�m�c�e�N��e��:X�.N���U�U�A=w�s!|��7܏���rUKJ�{q���p�	E�]��A�h�iוV����R.�wrj�8� ��<![5��{c�f���ه���-��+��9.��}w�	\ī`A8�U�ĶfI>��} ���~�R"��ܲ�����.����/����_-�w8*}>��`����񰲲��.��K��8jO��Ţ5���~l�O�\�?��"�Y��8�K�M=^�G/r�
��l��lo���t����#�#���\P�P�BT�5*������t�9;���/���_���$�>G/��[LYO���!��J�ܑ��ub����;m��|��e*g����P���-8b�4�a���]�%��-aR�3V\��X\�`���R���'�Q�̧���Z�(�}g��g%��퉶��N�h+�;��u�JpV�Y�o���_���uV����бMP\fM�� ( ���l���4f������Δ4��r�^�)�*��CS�����S$g��.�.�;r����J�Ŭ��@tf���R�+���d�������8���4�ؑ�=���!�>�~Jt�_G�&� �Yw����
U��?O)��4ܺT��gg����)0����H�˔2F� J�K�U��InЌƃ���ܷo�ک�=ۛfo�V��@�>/i9�TDř<\�~�Е��$-x�(��$�~�{)���q!��7�1�1ð�R�yr���p�)��'ރٱ��*2��	�gO������� L�YT9�V�3f�B�{yS�������n� +�<$]a.�O��L����hЙ��k_�Zz�z^�����g���6YM�������¢zg}�����S��[���g�9�I�["X///^��y�`ϼ� G���P�˕�7�<�W�)����=���E"���u�������+�6�V��A<��%}U5{Q�ѡ[�0��rFf�k��#��������� 7n��,l�]̳O�=�~A��@i	�S��ŭ`���oޠZ9S�O2a�R�N���ﾄ^)P�Dp�&[`!-��9%E����z��2�/����e[K.R�?�h�:�f�&�0EFTL7��{�JM�r��hR\2Ln_.�����^t��3x5M�:������?�t���G��H��X�)�V�+&x����޷z||�?��nc6���@ m��g�z���vwޑ��mx�n��j�(�Q@����I�M�l�>v[���N.Hv3�ln?)�?P�i�L7�6����#Ƒ�/� ~Q�W;�]����:9t��Լ�12���l<m�[u�]Q4� ���VJi<�- ck��˲r��D@�Ǯ�M>��	�!���/�:;�����Z.>��R��k�I��=�EVbeauu��	��b���/���b+�<�7����a�S��w��RX��mc�\H
�W�ڍ��B��ԱR��ʶ/HՔy�A�,�èC: 9q���e$9ܻ�:��u������
�c��8����L8���H��?�X����j�LF��uhݐo�:��t"�"�;~�ֆ@ʾ��6~X�U��������3�y��=��d�Q�7��<�ց�r�z!�DvQϫ�0T�1&C�#]~�8�\Ĵ�[�.s���֭q5��E,
����/;���5�[ �_� ���z�0���8g���u�tڒ��m��-6��v-K�i)���M?��|Y}��m����>��k�p&O*v�ڍ�a(G�׆�:�����n�̖���Ӭ.ud��-���4g�>��L�6BZ��+���dp�d���������Ş�ʹ���ӄ��'����q���1}gS�L�%�xd`�W5��Ⱥ �A-f���'�jx	���ս���-E�2;�_ir<���D6��i��լ��(E0�����z�𵶣�o����V�C��`@��M�G5^��_�m=:��Z)������>����R�Xi)U4.c0K`Q��tl�+���緢�ʰU��vX�s_�KHB@R�c�F��7Q#f�}�����B��sF��`�6��,�����}q�lM�2L~g�p2ŀO�'s.�L_��e?��i��n!�k:�V�h�ܝ�$,�v���+�t���q~����&��T�f�)MO�#��-�K6��^�),p
�B��2r����61��u"��d+-�����`#�ޥ�-$!�i;�u�H��H�lƱT��C�ؔ�3oy4����y&c��^��֧����'�vON�ǋ���qǹC�֋0X��#���I?�����.�q{�"H��_�,�?�gv� �;h�l�"Qz�gD�:���@�>����8ɅEn#�aH�"K_��v������D���Af՗�ҁR'�a�Ǧ����yY�Fh��Yl�j�
��Z-�i,_^/$��o��ߞ�8�5Hs��v��6�^�%���BzP���4�j5a�R�m�dP$ײN�m�e��\
`tdn���bG(5nZ5�졍x.����>�l~��G�*:��e��G�H
�}�ZϖF��wJC�o�:\��W����R�f�T[�@m�g�y=�ڏ*�Kzƞ^/7�����w�]������`PD8=��:���ߣx��7�7����$U)��
�f���=���5����҃!$ZĶ�����rT�����j��F=i[<�z�zk�7��3�����_tcW�"��M}h���~4)t��V{�V�u)��
M�r�'�F���Z�����`5V��:�4��+�p?R($Yj!�O��UW�XW~�t�0vn�/p%�h���'���%�m���� �b�j��d�o��C���D�@����涘�N��:�_��un��0nH'�^�K��حy���q&1&^V{_�?.St�7Mjv��bb��! ����{�(�W<��ߞ����S��5�;*]��2��>�����H���/ğ��m]a;�-���؄HF$�[r�j~����qX5g+��h+G`���{p=���s��z����_�L��h�M��pk^�}���XT����M�ߙOև�"I��NY;���3��[w/\�,ݬm&�N�m�\�D����7f<�#I!t��WA݃#���]c�e�D��ٞ'&&θ�20f�O�׭\͟�����{��K�?r�<]�т5c8�E��J��*G/��tE��0�߆�*7u�I��"J�z; �#�h�q��|��e�.�$bx�����P8�gC�ٳ;s%�O3uW7]��F.	�Jm[�*�2!�m�<��x�#���5G����W�UefN�7���h��t=P\vu4t�C:���E�57C0M/D3Y(.�v̠�;ʡ;���w���=� �r�N�}�)�$lX��ӵ��T�GZv)��0�é\F�������
��o� �i��<p\���G��/���e���ZXA)�x���`M-u?f�8]�q� �s_�<ލ�a�����C��5�%�ɐ���X��3�PT��c�yXv�M��|Rq�G/��������Nʽ�̝�����5��w<�-�f��{<Z����u��))���i�����%�Ӈ��ȳ3[��a*����/tr�S����6���U�J��o�1ra���Xvć�O'Zc(���3�F�%/�η��ƍ�K��^���Cw�Y�<_ϖ���\H6<�]���D&��<�7O7ஷ�ƾF�0>�R��:����4�zӛH[���@z�O.���3�/��l��.�/�]�eOi��]��;�O������u���픀���ی�ܽ�E��X��6/Jf��_�n��=�n����5����:;�^����dL;z��� r(&�R��Q�C�E*it�l��˻�D����lbib�ֳ��$��Oc��rh��tj��Z�#L�w4!|��#��B��	u�p��=���1~8cK�k���CV�
˴�:	�E�o����/�E�eZ���v=�ba�ǫ��_ ��$��Xh��:�+��*LƝ��L�i�t�X��8+����h�}��Xg�)-���)��F�Y�����P�O�hM���Kһֲ����+���G_��1���iX����S��qǮRg�*W�V�k�d>,j��ToX�~�������0@C����9���_l�-���)���?�L��×�d�4�H�f~��*:�ф����ʠ�!ط7�m%jLU�}�����͞c,���G��W�I/*-�p�5���h��=�^ou/ɦw�m���I��Y�&>�㒙c�^@|E>��'`�S�v7-B���A��t�C'���c[^:�֣�W3���>��X�[CO
����݆�5����Cg�^���9���Cz�	$8G�;C�A�r���F��B����4�3[���VMsO�P	�����R�|�
��j0���L��g/~[[`\����=j�Y�f��QA#ޝFgC�U�qÃ����h�~�H��a➰��5ܚC>4�;��S<2������0V\��62 ,�T�6���|F\[����7��D�O��t��f;��BV���� `�z�ZH�)+]�?�v/�HŎ4~XsP3��@�rzǧ��"�ě��yn�ȲG<��-�SE�J�_���9�ۚ��Ƀ頕Q�,R�}��`�y���X;�y�x2t�;�no7Z����Jt��:��uH<0��*�a%��42���������Tp�mt�j2�&�dx����)(����b�<k�j:�D�YL-9��c���ɩ�Zuk<��R����l���V%�=�̯p��Jp5��Oeb�ɔc���e���'pc&�Q���SVkџ4�r�e���Ct��k֍,M����l6ٌ���E�m��x��� R��6��!8���>�}��<&�As������,�4pWl~,��-���$>]*�Xy�/�|"������2��+66m$�^�H&Qj�
CSBB�d�mՅ��-��^��l��k>/;�G�pq� ��k*P��Y�#c
��7��yG@'�R��Z=�1U�:.��;��;Z��bTͷ��c��+�Z�L6�Ozx�w��n�UU_�n<qv8�c:�n�j[���[3�$��;�^Τm'��?�Wl`�+6�8q9���3�n*Rn������x�<]�m�;�3�f���p�b5����#��Ӊm����UL�IU��u�������wm����~d9ay���qΫ�t�a˼| �Ă��&s8��zqG¼^}�Y��7�/��,~ޭ��[��W������"��%�ǈ��-:�,��3�+!�_3[���8�+z1fEq���8W��5�N�w/j��H����S��l���WaȜ~����O�������1V )�W�&��ռ�m�RѰ������a���u��w5����z�5Zc��*���k0��*��M�9�7q���ݡ[[D���aEYYȑ����$�8��a����z��rs�ԚL�%(\)�jG�9���K�j��;s��N����KM�Y�Gg-���0�ni�y	�sW뼊�t�J���8�닸s�̑{&���M�dN����b�ε��z֪��[�Ԫ�o�B�LN
k���Cq/��1�
�B <}x��
�wi���AN+�g1wã	��c^��M�/�{a����I�$��2�
�s4�&$���Q�u7-=#)�v��z�6��,[���e��S"���Q��cQN��Co���9(�+B[��g�Wwu�q���J%���~���-MZ�<��_Q��x2��EkJ^ MD�lnN͍Olt��[��[�e���
����H2�c`��W�D7Kl�� q��~g�@z���s�R��R;:3��uK�q�y!)�xg�K��Z4*Z����4��qe/Xx���+���>��9<Kz��.�k��;w ���*���`����D����k_�73����\�3~���*D�X���� JR�����W�CT������j	��J�����؇t��&��<�?��]"c���x|6I��b��/�0���6���c�Z��PY���!�c:��cS�Ͷ�w��gk[9lY���Tv=4����b��
Rn�	�7dIw�������%3�['e0��N�'&&���0��?��p����b�!n���M͔@n��_�8��C~��,�#'2����S��E�쏀�3^��o3�o���;g:6e;B%뿇S���W��;�ѡ�ԡ��N�^W�9�1 �/���;��`׃i#��/XJ�V	F ��z�^�O2D-�/p.4�bTşY�7n~�JOM�׮[Of��J�d��5�"�^��i�-�W�d�iXׁ]�6Z��Zq�3�n�Atf!h���'~7F�� i�_D������2300�Jqi\μ�k7�X2+t��TIS�6}��ٜ�#GQ;z��~�))�0����{�s���V}Կ�e��0[����[a܏���q���#��F�یF��w��)��(ߥ3N��1���_�ݚ?�Y���H�m"K�����9����,����|=���X��+FK�I�$:��زH԰�������y�"����zkl�E��o]��J�d���?Eː�!�)-V�nzSR=�I�Ar��x�sz�E�m#���G�j����9��9ŋ�S�ϻ�7�%^f�v�m����ߤ�ɺ��A��蹠!R
%�=�=k�z>�X3x�V��I�p/4�;�Na�rrM7���w��=nj�IO!U�Sk��sk�;LX|Q�p��xӮZW�����baa2q?���}��B�:��8� �T�LE�8g�:���S���c��dIJ$xUu�o��s����X!)M+',4!���/y@E��V�*�=v2RJE�I���:��4��̸��E�Kkhc\�U�����������m���v���X�c��-rY���b�]�M�ƿm���8�`+�F���'�Nz ��Y�'���qN'X���ZM�IW���؝���cSw�ZU��Ғ�Ŷl������D<�GW��j:䈟��ş�Ġ�@(V+J�x[Yu[�#���;����X� 0�u�yU��ݗֆ0;�R1�a���1�&����q�O�C�%Ɩ�1y5�'Z�?4��1з���*����u�����b��Z��n�a]}��IH0�B/*�MQ�1pi�B/T��ɟC/b��S�"��9S[���K�reBa-^&�h�Q������l��FHy,�����_�+X���(�3mS�l���RE~�� �\dPU�!H����0x��8��`��3�3z%��(I��	�<9��ԁ����z�Pzg�����, ���F�bxJiP-�\< ��z����) �>�Y�=1Ϯ܇Tw�n��oη䚚�-Uî`1�2-�^�i8���γN�>�����d5�d�����h��H�.�j:�x����uN�T�)ֻ�g���/�{'0���~|�aQv-Oe�	��e_��ap�<�q�}+�F��}y�p�&-ߋ)���k�j:�-V�2�6���Ϗs�f1�b4��w[�y�}��[������IH,*�"'����3��(5�k���S0�d�מH��Z��g��߳W�#<a�O��C�Ri����� �Q�e�R�=8��M����WrKA[�����II�7�E�+�fOmC.[y-ˇ7��.w##�����)���U@����Z��'��2;���@����CIaL������|F�FHz�^�p ��:�g
^^�9}Cݛ$����r�2m�*RRx6�:�'�K6Ks�P��!��Q�������N_�?iB*#���4�aZd��~�Zُ��F�? ���̃��D��!M�16�pì��$����$6]1����t����?�( ����N'�"�qE��X��_K�O�彅v x��OQrE��K��O�>!,5u����mJ��������T<�rV>���>L)�ş.:FFE�!@���x��Xl�����3�������%�,��
���M��/�$��g�0��]�ݣ�g�� ;]b����C�OV*���Y��oɵ�zZ�z8Rh���?����ΜZ'�F4�p�-Ӆ��%j�-W`?�	B؊4�]���u��Q�v4���um��DV=�|�-%�*�,\LslS��c_^����v�?����9-����A�7 ���Oj�^\ٙy��*�h�+��!_u�5�m˧�a�G�;��
*�1�]�b7��{�_�lus�m)����qD�v;��}����~���u���c��I9����!\�~�>�vف�4���kGG_�Fwv��@A�P�c�^���ۯ��.���J�E���@Oַ�j���=]lY�#m�5���_�uy����y���e��J7rep��?L���6�6��k*�}3��h��X��Q�W]U��f�������BS�%�����8�Ve�sv���*��~�'�\��B�c�+$i��&8�%q����T�cj����ǄC�H;/�B�R((�b9Z�u1�&K�RL�~+��р]Rb��4��ɉ�\�h2w�Wp����V�J���o%�	t3�w���ɇ~�#OB��Nֹo.<δ�>�c1_��t��@�\u��!�4���0Sd,^N�������Ζ�@pe&٧R�}5��k�Yvএ��x�bfu�O��mE���"-y^��o�����w�����q�3�A=�ar[��D��?bFR�wD��t�6�5+hGJ���>��Ned���*��^��NQ�Q '�붨?gV������qX?�����{팰Z�����#�30�i��X��S�.��Γ�<`���#��DJ������v:�� ^�uI��=�S]f�\��SU�+��<���u4�{9i�IɋtRZ�sx~������sg�2z��,�3��O��ɳ��Um6D�l��r�ܠCh<�s]�Ө{*O����'��+��-�*&��V��iIi��q�Q�j�F.0�V��� ��._�<���%~/�zL�"o�UetmB�PIv�͐ ,��[V4�֜�����8o,P����`�~�[��mu{7z��p��% ��
����p�U'}�ٔ
�%�'c,lw���IL�4Q�
{:�LX�ߔх$���Ln�b���4���0���҇���-�b��Y�\��Z0��r�Dn#�_�Hl#0+ۙGj�4��l�j0�|Ҵq����P�4�����ݹ!$�_�U�k�u��.2y.�+��a���c�9֔p��H�%�� �m����1{���h�7+߾^ ��t�/��S���AMj���wD��F/c|:���l��BXғ�R�q��tf�t��v�� �z��$}�����HxO%�V8z�\�h�#��,��ͯ���s�����'��u������iwI4��/�]�x�o��5��t�C�{�EE�d�^�E��I���������b��=atVXH�ZJq
CS��=�O��Y��\��z�g��i�_L፲�RCÝ,ÕD�t��h+�����uNj�N�BrЬ��e�K6$[�fQ&9�ԃ�'b���}�n-\D����~�q�z�<�ݔ13���K[�V�&�|����r3������&뾂R��
�d:�E�wv$eN'�@LM���"H�\9d^$�ֱU���q��TTU%����@.�^	�8�"�Ջ���rpǈ�lN?c�#��b��|�6��E@5G�����B���+�{�3����o{	XYd �δ�&�F��G�TN�ƪ�����.L�*2Zr"��)B0�WY
b��E���ȶ;B����'�w���s�Ow���1�j���I�l�Zf�5������9�_Uc+��um�d.)/9�W��(��+j�� �Un���?��ލ����晈Ӳ�71;"C���]]� k�b`EU%Kȅ�z�%�v��
1���"�eAQDD��5�Ld�JPB��I�ޘ�-�P�V�=�?}'~9��u�3�A.��)_���'�����a��[pC�y����2�F����S���&� �����K���e�'��<,���e)��s�IMd��nP��1RsJ�c�3pX�8�xOC����0����gW�9�	�B�2��7�=��0��i��-�<��@GA�Z���vU&�9�YT�Q��q��A����gT�zه,
$)��޴[��ί�Ձ�s��������n��e�!�	v�G�=�_k'�y�?�X�W�rE>����`*W����j$X�q}��H������R��P�dDNd�FYa3�D�dT?�v����&�} `-����H{��;.u��OL�m 1�9�������M�IV��ˠ��fZ�u�4�\WQ��N�hR�a�$Bֲ6��E�����ap�<��!M���rS؋�
� ��0�`��6r	�qJ/ܪYp컫�ɜzp�1fI>�C��׹;\+i�酉���N����%��s?1�nj���q�%�t͠�)Hߡ5T�r�1SI�S�_@��(�.�$��;�1�Bj;C\T��:ze����G"1�ķ&*R�e��F5�89;`����յh��]��'cG�A����X����U�^Ќ������Q)t����/,{L�0Cu��'8��TT������pC>�3���ʱ(�1�4��
�qu��+��d�'M+r(&J�$�`u��9���֒��l�R�˵Xt��Z����Ҥx�톲--�������w��}�߅�1�y]��l���Z��L�"O,d?;L԰��F�ѣ���- i��c��煯�a�eBG�Ɖ�*p71�qTv�A5��ؒ�����j��p�x�W%xT�vX���s9�39��<�2�{E2Xi�����<1z|�U�N�P���lP�jTj����x����U +4���N';w�d���k��޻����.)e�)3�)�j���s��U���j����E��ҵ�~E�qx�.`�Nړ�o�y�Y��)��e5z3t5����Ò
�Q�C4�V�����
���TMW�� 3łq��[��~�5��y~(5�Ij�y~�O�I]����2���}<���H�`���nY˴hn��1s�"�H8$B ~���ɒ��Al�l��mۆTo��m�X�˯}��{n��S�UT�.�c�h1�Nކ��V��8���z4�b�V�H�m�|�����[�}��ޣ(��Ie1�٩h�x]�N�ğn����l5T�1X����w�)l�뎭Z�������f%%�Yb���h4:9b�<2�-��]��܍G�����C��Aр�Ĥ���D�
��JA^��ZC:!��%��$����%F �C�Ob|����
�ئ1d��V=��I�g�d2�ة�`:19�B����=!��9�5J�#��e�m��GQ[uwz&����K|�=W�It�b�!8�]�@+j��t�e�V3ؔd�W�ݲ�@���h?z~#6ڈ�"3 ���97 �Ä^�P��P*?�e�,N����|�����a&��Q��i�����&O\�S_w�R���z�b�o#����b�H����&�3�Q�A�C�a�S�=��@��Xđ=��S��pX�$�χ��^��}��k0�A���;͓���J3<�ܲ�S�NDO�<�y�a��Bx�ϸ5N�8����[�'lFX7m�;?�\�8y%�{ �������&�P�S�&�QC	�\�ʠ� �ҙ�=��{g��g�L����у��&ޕ��=�u�Ru���='���lx��$����"r��&6�J`�i��t|Ob��f>|��- �:&�&7bX�u��*��@lsrw]f��Æ�`��$���_F D5"�V*K��H?�r�?�N�(��'�"�[.��"���� �Fs�A�[����l�*$�����p�}�f3���*��W^�8�A�?f��X��_J���kU�ޞ^-v���s�)��g[\=��9��B�Q�b�[�L�RS�yG�9��JNA�{q�Ϥ����a����>gM�!�<]�;�fU��:FR!B✣�JlV����Ƒd��b>:�l�
p�%��L�HG�T���3Z���~��w݄��嫏���=�����Q��o<=C���K������1���̿[���%zg�%[jC[�tK@8��P�d�hnm��ȢN9{\pQ� ����_�7>b�	(r�#D��E��e�}I����}r}b�g���W��^�l�市gkc��gg�=7+#��d}Q]�#��~zߏJ�M�mM��ɡ�64�L#R�L���H�j?�,��A�+c�<��g}����hB����;����>2�]5*����r���ߝ.��Pw������V�>�U���Q�ޮ��o"N���\j�<��O����:��Z�~��{���|s]0���y�E���z�����4�?ѝ�&PvV�H���L ��:�����;�Q���/)f����c:4,'��Q�G�YhH�~I����A-����%��B�Bn>����a=oV�iJk����dR^dg���K���h�{e��o��RB�� "�an�1��,JƮV�6��O�B�ܱs��ae�w��E��������\�F�F�l�s�QS'�ɇ�)SL0��؈z��=�	1��wŝH�,>���VSq4���	����n��F9Y[���������IW����@��h����&R��*@oa-[�����.��x�.������aj�	����S#M=�5_=���Y�|uW�݆'g��f���%���R+=�����Ƥ����詟 دV��+�ej���T݄̄��{b�t���9Zr���i������4������e���:�9�UZ[���S09��{29a�s����Җ�8ё���׳��� [jjʖ�5v��t�D�4s�q�LP����}�)no�+��+����mE�,l��Ⱦ�����zL��0&�
�,���4L� �A��h����L^Tiʔï4Q�sR��/���x��v�؝�vȸ�"|���r�҃�p!H�K�zE붨�B�����($�U��pk�T����[�Ʊ��Vp�f`rbF&�1(���VA�z�������s�ʜrPu,��I[�pf&Q�٤� I*��N�|GhL��w�z��K?�6��4<��6A�v���Yrm�V� ��H��G{R-C�w� '��3c��������n�~@��lF�o���U:�w�3�l�d�"�Ai�����j����O�o=�;�'���uۓ�6�{L())�X]�+�RnD�7��/��@m��$��!]�^��������9��v���o���y��Kp�#�`�스Xs�e��+���}k�>����R���� ��d ��]IY�~�/N}<'���g�Ա�0� �/T�����=_*,�&np�x#�jx��&`?��yĻ�v���K�'Yŵoa;�my�s�Q�=Gf/YV�1l�Z�;HT�	b��,Xɾ��s��4>
q�a����X^���2����۪���k#�=$�jp��:�T��3�Q�^�ĭ�ד��Ւ��{Z�%�¤m?R5zd!9�.�_�������}�L�C�n�S�O�j�L�<ˉ|	u������rN���N̍;a��57�N���D�[5�?�To��׳�ޮ���/����朔Y�\ iyʍ����g��o��4� �L�T����Jy��9��~?���jf�QXw����giN<n���q}8$�&�_=/��݄<��qF���T{Ѐ�;�������w'C߳�����7��}��^�P���;�*�۬�&-�؅e':��TE=�a�JvH���wB�ӭ��Y�:GB�2
Y�6�Y�))w�9�f�
;7>`����=�T�G�#n���?
����|�kx�kw]F���}����e�Π�֬���-����{����{f��w�r�]�-�+��0�:]��s���!
R�$ �,-�A/���^����dl����0��n������i�;;�!2E�僴-i%��6�	������vqp��%k�#�&��=o�̰<�4�ow숪S�֍��xmp�YTVS��ވ���u6�.�5�U����]�����抐dP��X*�ߠSU��=��d�yEUՌ�!=Z�M$���j##I��$.��A��L_i��� 6�Ѓ0�cG�P$%"G+��}ְ���~�v�cȐ���Hc��y1�S?#,H)4��v����+��n�_�c�딛7t㾽����ܫ#V�3��x�c��������,g�T��������©���}��f���pn�}��!K*��"�O�*��������gN

a��~Ϊ��O�_�i�"ͅ���&ѝ:o�s�w���6�ۮ�]I��1;t\m�|�}�������li���}�S��BR�R�)p6d��S(��j�Y�v �@���*Q�9'
C�sJ�ܲ�$Ӹ�%�\��}�}O9v.軵I�n�8P�i�V��8��1ʁ�~�~ә,���W�u��~����&��|�����}8��H>Y)}�h����w��:��Ʒ7���~�D�����Z¡O|M��od̩�(���m{C_�eUJAD`�h� P��f�7�q~���\���3|�Y�k!:��+�4��(8��ܾ���uwz6�/~�ҷ=q�Ƅ�}a����H2*��J�Hb�����S���AF���z�cxg����xY n���~;��X�����W�u�л�u�~�)�)��	�M̟6h^=xٷZ*���X�\��54�(���Y��b������K���Oz�N�����T�P��M饶��sf����@#�RX�}͂+"3�fڦ�)u�>(?�OX�tn�;Z�;����$�����yc_DF$ژ��W�dPA�>�JSw#��5��{lL�oL������ƞ>�N��~*m�rh����
���Y���j����r��*�_X�D`�ی?�S1��D���Ee�TIDx)��-&�Zw�K�{��w���̤Vڣ�J����[�mɬZ�qJwp�W��3�}q*��2%>	͌�9�G�����=��O�\x�,��������"f6>Y�P�,:_���G�<����d�/���T_o���[�g�t#/\���r�k����$N�ݐp�gd��.��f�!�]��=	-_�������8-q�IM��\��9 �"�[$��;�_�K�L��X+�� �<hc�&ΛS+���X ���/Y��$�9&Ι�	+O��b�BМ���o?��ƍ�ދ���谬����n���R�&�����$-���=��!�!��+P��bi
qV�37�߆k�!�p!�@�B�W��#�.5�T���]�V��V*�ߛ�7`]�S�� c�R�'<�����Ү��3����/����U�@�nV�E5J�!�˭��_-��m���V=��h��;s/M�[ ��I<T��Up��hc-��p` ���EKOF6g�邚�Y��8'�fBS�cC!
-���`b���i��2�,�ͼ��Gt�U��wx�r�?�p�b(A��'�wX�����^�EO����ND\��~E��tUA+�+���92�[�h���#<�C����\��E((n�Ef�<T�Ɇ��M������&�B��Ej��r�,�(�}��x�+�61���x)�v�I}@i����p�	��45pN�]�r���bQHY�@��M���$҇��Ū����w YK�u�f��ح5���2I�Y'�| P�Z�����*$� ��=0����0���é���-Ќ�\̵�蚑PQ9�Nn����bm@R =NDL�˳�t�ł#;�Rɜ��h���W�D_��5���o�e��A]A?�n+�jJ���\#�q���^(�&��MY���e�OT�ݾ��k�s��.�s�.m����������F�3@�r-�чi�T^LE�X�f�Ί�	�YLQ-�uJ�;q�[h�{l�Yyی�צ7�~M>��Ȋ�8R���t
?���n|_~�~��n����)��R~k��^��'(z��(���� ��L	w�X:��he���I�(�7�Z��W��n���y=N7	~�/��VY�[�l���
�y��=��P]�E��=|������TKjpdr�/�~�~��B�����S9�,d?�(�O�o������J������/x;�ch��aM��=��Jw�� 49�� Ƽ�;��z��$W�O���(*��S�蓭�EOTqR?�0����{yy�2��?Ꙙc?��*�6�1��4`��XƎ����-����,,�HRٺ��ՒTe¢��P�@��i��j���H�A%�f���h�K�F������L�ӄNfU|��7�V���t�N.���e�]����)�8
*`��bw��b�;҆�:�Vw~t����3��!${O#B�����]�ue��J�Zo�Ml�d�tp�S�lbhB^�k� *D��QdAќ��m����<n�nFo��.29譙G�w�C���҂x����pƸ��F)����e����e��꡽��s��>+6��v�|���r��nec�D�q���+%зi�����=���|�෇iM��9�-��7�©�H���s��gHsF�]�������;�-g�3���vϓJ��XQ�g����dee���bWv�?���(�9ݡ:��3��
�P��>W��3忟��ñ��aڳ|�*�g�ُ���:�\B�OS��Ta���3$@f�ԏ��Fa�uT[v�����u������>W�M�OS�	��
s�d&p�xp@6�\������Z�O�p��u�Y�?�M^�&�i�]'�v�dл�##Jk����;�Ό�+��mf�r���������F]�~W����f-����VZ�eA=�!7�.]�v8^��龗}� 5ݍ�
W,f$!�=P�hڤ���g�eR���
/iI�{)k���a�{�v�yp�'
��o�
�V�X.��w �ׇ��֝�C��;�L|3g�������7�;	�wL>��=6�]�:e�fm&�;�����]��r�~-���]�H��a^�e�7����Gx}�&�$J���G�r�$�����U�%�����E�$�-�>/\�Τ��2�[t�NM��F������3Ht��3�xq ;���-֝	���eܾ#)���`q���Yz���i��61�Z��E����0�|�(O�a��@v� �0�Ľ1����gΓ;x̘،�U�Ԯ|��!�7�G�����a�����4�P��:�
0g��&~��ĪV����)�r& ʁ�qKID��e�W3��L�qs���e[�M:lec�)��^���N[���-�y�1���	�4�A�*�m��~�n0ɼ�����_8EE�k�AH�/�j��ݏ���;�!�D�i.̌�%ֲ8�:P+>a�k&���1Z%MU*ё�5��#�����[gYY�6?[\n��8&!,���}蜻�Og��qE�,%�vh��Ĥ1� 糆��t �U
�&f��*ٜ�>�[O�2�k�8� J�L%���Fi
#�CL"p�*]�����f����~�6�\lG7��]}nR��^��zmoZ�F�Z:�Z��Ů�'E�U���>%ۭ��:G�ĪBo}��]���m�S۞�,6{(E�v˴0��Ҹ��)���9R��M����=��"�߫7��8.�xJ7��C�v����
��Sֈ�����g� �Ę�*�L<��#?����\$�(�K�����FbM)�|f{w��dP Ga��(�F�5o����o23����اF7����w�w�X�Q���l�#}����šJ���,�����;~9��g����[U��vIJe�H-����8��f�MN���OB��X�(����	R��f�z7�-���k��A@�
�o6.9w��WUo�F��0�����>�t���(��������/�ۻE��O��;����l�+t������i��*^(sPD��!Z��X��]M������2]i�,~oZ���Hd����eE[mw_�bΛ�=d<�ǐ��*t����H��ђ�#Pc.tI�>=��+��N�8H��	D����Of�8|�l%��r[u�zU��z�n�@�߅^\�v��mrϨC�����E�ߟ�	�'�)'7>ı�J7l�EO[�:E�0oNo�ۭ�&������>��o1` 4@&&U�;f��yb9M��zu���g�j�ק[�O�nt��COL-|�*�s�h��g��:2��8�8�.��88���*��Z.ъ?=�A%g�GV�N]�t+Lr	fI�P�	�Y�+5tlw��%���i��P�.g~ (�O6����k��ݷ���sMƋ�O�#&wM�.��ӿ��
u�nwī�_�uj�Dh��|B�X��O���C��{ѿ�oVL�P�O!|�	���	Sb
/��d��I*!ӹ�۞ =�;Yh:��[��ѩ�$-�ͭ�K���\7�~��Y�.v��RV4IP�g%�/����W����k|�dӨ�NJȶ��@/N`�}�9�ڜ��zGmrI&Z��UѠD)չc�Q)'�.GLu�;o�j@�l��=�BWt�8$���W�W�le6�ܚl�~��=3`�,"NU��("~}[��7�v	�dT���ʃQH�bs�s��h�W�+SS�qEө��]~G�1�Z!��S�/5@4���m�e,u��+�o?�΍��Q�ބ����)V���$�(��~�=��~�}{R[�{����i�.�	�D�{gT�Ƨrx�4�6pm?	�z{��z�ǲ|Q ŧ�i�|�~�$��� :�欣�lo��Y9���a7C���|�x�z>Ћ෻�tm?�b5ze��Q�� ��tG#8�^�l�ޝ@C%n��r���	7Z��*�"X$��&��I�ASR�<U�*��z�*e�{I�cS����Q	R8a��a����t��4��/�х腟y��|�2-r�b�[�<���n�`�%G�l
�olA�ro��AZA���u��l��Vَ�L��G�/�+�Nq|*;��>�{��5m�ۏ��*Ѯ�=|q�������H�u�$����B��(�o�����"��_ku[��(�P�+b�h�3�(k1{"�܆+%J��u�V˖+"etg�7v��)�$�n�ū��8o�r�E���{���zgx8U@�ʗ{hwq�X�{:V^]�]~���X^3�說���I(�mxE�!:�1�9W?����7}�����8�w��W�Ȧ@ �=��}�+�=�^�NnM��5I��� op�t����]�W�Ν�j�H�՝�lǽ�"��7DN!�4��l*p2��3
��^I_��׋��J��a���4܃�"�nb�zUA�f�9,l.XBj;h˯�W*���W�W�6��O��٬�X%��m�XOTK�mh��3����(�|Vsl֨l����)�/��=�־��'sA9��'�~�7�;�Ew�Y}�d�k�Q9��˽=���t��@�DT ��1
���.1b���u��K|י�M1�5qh$�{��p�m�������mE}�߃�T��#�L[�a�,��3�>ۘZR'�^aq���W,�y�2�g<�H�R|[����ɗG�_���7����z�^��N�Լ:�f���؀^��e.�p(�`6(Y�Qx2�������$z��y[?��iV�рƉ�sP��3F�av���}gE}�Y�d �qMn�yl���}ޙ�d���hd�K�6�RZ̨�BFt�����U�U\k�Y�����t�[�&�pS蔮�.n�^6�g�Xm��g�^����9}�e�i�=L�9� h�[΢^_:<=����;�]�����=�a������VF�jզ�����^Ww���vR=�<�0�Q�:I�	�ޯ�R��ئ$�)���P-JJ33�J����&Yt
Vʪ�g�:����L}Ҧ9��A3Fؚeԡ=V*_m���Ặ�ʺ���\�Qͨ�����>�-�i���>d�w<��f���x�]�Ni9kC��`��)���"��d�W�9B�t�:�d͌|,���sF��]�N����\�s����sgl������s�]�O�w�%�۶>QL���������&��*%�[��#"����	.�ޛ'�����7�QhƆw%�G���Tu�Z�^E�>�s�@jӷ��k&�5Sj!@�¿��0HP�� Q$U�����qJ?����^0�s�K�:f��������=�ֵ�����Ǖ�W)Pң9����=�]	����)<U6�3v�俲�ߞ�g'����N\k�l�]�Z�m������=�k�uɵ�FEg��g�V\M#�m�8~�{�6�ܭ�W��>�94�=_y/��=�=V���G}X4Z��e���ږ�@c�#��aQ� zW�"��W
��2'Ex�ZU���{#�������g����$G ��.#s��"w0E.�Y�������[����B���Kժ'��ƕ�r�;�����}��F��a��M%�D|rl*�A��MU��;. Z���.ٛ�����v�%�.f�H��1�~�h8f�g�,�\k��^��y�Ѕ��/(�0.fP�Դ]c0��N-�l�R��/t 2�\7ٺLkvH��ڣ���N�y��������h�c��I?����3�ј�gyK�͇��QhC��>��C�Da�u]6~�GF�S���=��82��<� q���ȳ�DN��Ŗ>�x���|
RQ�F��J^K��
6����/|�Uy�p���	����7�x诺j�C�����)P?�AK�X�gi��{�q}�=L�d����6��o���cY�ކw[��~�p���g�q�ۋ҃ӡ tW�@u-sݫ��{8��κj�D#��|Q��G�dqMd'K�؍� ��%ui}t���#i���R���Ϛ��b.oܠ�찢��yZ�:��#���
�'�TFP�*��-'>1:l���vj�@�#�P(�n(��c��`�� �[>�����kě'�Y�޷(��72���{G�0�D�&%����Ũ�2�7ʏơ�M�73A���lG���6���R�f��E�0�a�R��!b�敢�3n1���U�I4|%vk��4�@\7rɂk��+�D��9�r�gb� �#�Or��ʠ��������K�.?hQ���������R��H���$C��Iw����h�
�\2��')���}���>ǲ��4 ����_��_PM̟����Ҋ#�Xd���i
�@����^!��ln(v ���1�g��+2�k��W 3HMk�Ն�S:ǺH*���<倁��#��bl��o+ (#7:��r<>��/>�t���f�65����0$�M ��� ��T���GR\�.��m��PUM�@n�g�:�UL/:D���ޚc�;>,h�=v�!�3l���'��D��f��W��-�5�������*�'��u$S��T/���R�el4�.n܋��5�7�ysr��,h����2$�߭�g�f\��x�^�U'�B����<:b�n��J�x����~�>}��f!��:CD�.���Iʢ�2B�!=���!�Mf�T����CB�.+*O*�bqݝ��9 N���"�܉��ם�R�]�������'aK����k���n��>0��,o�n�%r?L�@&*��
�w
����<���^Ħz�&���cY`q����!T���ݿ<����E����0� ���޷�78V4~\(�����$Ȝ3'��A�����Y\�NH#�=�gʊßD5r�B���$a���Ex�)v�����<2
��f%�V�C��p���;jF������ M�/��E�P�Y�Z}SA8E�	����%�8��x�bJ�,�p�k���D��� 1��=Z��0��wE�hBf6�dO��+�J�z���m�]��)��D)��K]�^��F��s�[fU4���_��-s�A��V�8L��w�|#�0ڋ��蝺�Q`t�1�����霚���9��[9�����xMϣ�23���lz0Sr��S"�W?�Š��ػ�"J>ሔ&��!��VM���{�m���=�'Vj��gx�"�!v9xDL�O�[������bFV�R�GE&��h��c�!�x\1�Mh���z7&�����~��Ĳ��>	ͷ���h�'��}v��A��Ϣ�óGs4��7W+	�Q�ew��4Va[�ȁJcb���	/�#/�0�$�g���D]��x_�S�Uv��ؑ^�A���g$C� ĕ'2j�|��j�2�y:3_Y!z;P��@Z�M��%�`��/��,wMS�u���Y|�-�O}�o��0p���:���j��?ܛX4�|��������f�+��hk$�tuO�$�7�H� I&��K�q�������dć}a������b��Aa��~���/_�%@���f��JZ�Z�����T�2=�h�3��2d5���xb����-;�����{�c'�tv^�����Z�Ҁ�t� ���AlQ� ��kb��2>����V�վ�u����z��1�a���85{▙�U��[�ǼXd�BW)����
��e���I��ՅJ
E[�����l�Ɍ��x��@��k��).¦%Aq�k��'�D؃��nY���Y1�LN1�1��[�VQ����Ń~����Յ���>~2D���0p�Q�4�[>S-Q�9�U{3�H]�χ>&�m%��;
��C�ʪ��D�a��{x%s%�81�-٬X�bF�8;O���p�ަ�)� ��'�L��{����rY�_�p�����Tt%~�Lkg�k��:�x��W��;jg��.�6�����3%-����T5��A���~��Q��P�_����'�I�N:��s�(4�г 3�$�Q�p�rpc����E��M!V8�쇝������{�^���%���7��)� ������#I-�j���J�CR�A�����d��ݦ�*�Z��:7�V��[Y�g�m�����.�u�	�T2zƏ�j�{65�-�ަ?'�#�CE%`5}[1����!#��,�B_�"*ڱ�Bh�vLa|9�:�K�0^e��w\�D��+�]�s!F'��v�3Y'|�:;�ǣ���H��ɖ���h�ui0��ӝ�,��ж�ʻ$��T�k���z��c/Y?�rMt�$�����R�1��B�r]H��O�I+YzX�F� �-q�A��@�HT�֦Ƥ�� %��'nbetW�tl���B��K��rR*��{]���6��r����)jŝD�%���| t��W�TjH%Y�G&3.՘�I�'3�hk���B��4����d}L�WH�q�D|�����R�E����������x������v��t�)��">�wE�[;�T�_�1�tq	c+�@��y��3h,�}��a�~������	c��:��5�܁ݟ3��Ϡ���F�>�U&����}�tGbFZ���;�����6U�;�Ӄ�2#��v��Y���z�o�`�F�2�Q���l<�5�\��oՏ?���(S��	BsD���0U?�d-�G�B����*:���ɗ�+00��u���
?	~Zߞm��w��l�2����n�%7�E*~8n���f�=)h�����»�����j���++3�������@Ŭqt��/9 ��)Rʫ���v���&�������~l�ls�*�y�ʢ�� `Fx����+`@������d���$;�]������F�uf4��@�-~��~D�AzW�=ȼ�Q�	�l U��A���a.�:K�����K!��v+C��]�5{��y��������4���Xe~1.N�;��;������@�-|<DF^�x��k����yʢH�ϙ�\Qܔ�����	s�}9��)H����Z���X,����`3'�L��k���7��5�	q��e��	ᅠ1�\���Rp8�ի~�[��T��o�!��gM���s�����0��2���-8YT�l��4Zl�K��=C���#q�-��"��I<���|?�S�Xa��H�_�e�yb�S��P0%�Y^I2k �AQd����`�c�Gul�ܵ�?�8&1j���x˷���4s�����cN�>PI��ѣ���˦�J��]/�y�����3����02i� *q�%j�?�B�F�F#��?���4������M��<�Z>b'��:�l�}e:��n�'.^��iW3��SCK��7��6����
�[��}E�5(-i��Sc�{Ԝ��%���,�I� ����!ϵ��`����j������ۿ���kg7x4W|#z��b��E`�`�D���`�hp	0�m%0+�b:��2��l�EaQg�3}��qD�	p�Q�f�jl��l���_ �n��\��m�<,��/�����ﾓ�Z!(t���|h���DXI'o"�+�W��{�l��oČ�b*����	���YK�"�l�"T���ۢ�T9д>�+$�!Jb�a���}��+3 �<�����)3��"4KG�G�h��Q��kp��Ѣq�x����&�W��:�)Ӏ��8�#u|�e�f��@+��]����v��w����l�2��q�������&�	A�/��9F��9�nY�k|DJ5>�m6F���Ab�J����-$?�T���-�Ʃ�se#�4���^V��H����'F�C$�e���))r)��u��!���un�kt��9䛇G����Tww��YW:�����.�4�MYՑ�ĥ3r���4�Dp}d�:5XR�Ө�X���G�,`��W���9���|ݸ5|_	u��(s�})�c��Z쐫�`8�>�J{&1T�J`��g�W��ު�:{���|i݊ink�ߏ�����ªĢǍp���Iů7�'1���`����ly���-�ִu|��u�g�XV .�p���C���UZ�r&Y{��k}Ĵ��E�y� UJ�6Cf�L>��L��ҧɅ.?��<gZ1[#@tUw�aZ$��:�]�@n�W�^.upwP/�M:;���j�.>/�v|1�LN�+�(G8h��.���7 �7����h=B}�NmZX�$�f��P'=(ɶ�鵮���w���_�2R�!x��>o� ����yh$�zwl�)�#4�WL�P8��đ�,�o���}hm�m:��}�L��wd��u��iW�ɛ���_~ִ�!ڿ��o��Ԅ�ӯ4#�S<��22s�i�a^��h=u%����+�3�I8�� ����� �$X����j�FF��JA�W#ߓ�%�Q�ܖ�lzj,'��9U��qe,�4�Ĩ�v9��F/�և�ih���ih�5�"tf�.f� �LѰ��IQ)�<2�Xh�'�F�UA���í����!|WW�<)��}s���п|���-Л�m��/�U�Y%���	�Xi<��q�6�q��i�T%�m?G�nx��nįȟ�c��*&50�:::=w�`<��o����F=^�
Ѭsj|lu%�&�>���e1p�!2�5�W1�Gϖ�������!&������6;�uǨZ�V�C0�*�ֺ�9L2�v+M��]ά/����\�y�� ���6�w|�m�!��1����1�P��OD�����
�n/(K��E�#v2j}r�J�x�@z�k�<��qL��.�;�WG��;�To�]��9�P�e�R�Ё2�\�ad9؁��~�W��H_��������0�kZ��t�j��#ߟp�jyR��&��fG3��q�D#3�S�92B
�N�/�V�)}\Y��]6��T��f@��R��jo�l��se�(��:�U�ZƑ���<�䅺�yW���tq�7{;Ĥ��K*&}>r��{o�/K�z?-2p)����U��As��1}����Ab�'1�27�f�Y�A�p�}������ �.2IQ�4��\Q3U�H��v�5��=�9U7k'���_K��#5���r��*�,�j�.X��C�I\�W<�Ѱ^8e���^�(J�>�}d�����&�h}�
�����Nua�Z��:�1pbJ˩	��$%�v�!�x�?�o�F�r�q�zaH(����r"�Ԃ+W�w�yP�5143���ީݺ%U�$�H��E�3�*�C�E��c�ZYiy#f�6YB}:�~2�¨� /�B8���6ɿdM�A�s?�'��o@ԉ�v��� ?B����jZٯ���XM��+AY-m�GB�1�i��L~O�}�B:�5�*�Z����p�]'A�������,���ޫas�Nm'Ը��������Xk��l��������0�	��ٝ3D�:���[��0��뉝�i��O�g���$��q9D�~ �V�x��b���2���Īb�UcJ��4G�m��h�uv�~��X�Bk��z6^��/e��w<^�ż�TK�}�75�uϬxʖ���x�4��$�����Z�|��!��ݍ���|�&9���Mo`�E�c�F�4��V
�&�T�ڵ~f����+��+噧F�˘���m��?�bF-ЙUh�����3��/]پM����'?����|0�����QQu>p֫Xir�|�:�R�T�O��ȶ`�F�1�wè�!����(�:_�$﹢+�	� ��E��}�q�xJ�m���������^�T�]�K����ī_�:n��+�~��s�L�Mm��dc�7��|����ߺ�k�������ݳ���v�`F��R��4O��ZL�l���9�baa���z�>�9u�[�l��k�a0�o�ѩ\���Z��\b�^!��h�ؿ�I�:z���q+=���ڐ�>p�;�*��ʣ�D;��\�8W'7��pD�΁T�9fj�7�x=xe����������p�+��-�QSg:�ɎN���q��9��N�����c�^�T��Z!�sJ)�e�l�ڡ1F��oKQ���r�VK[�v`�����k�&o��?�7�}�J�W���)A)񬟻u��!�>Z�xk���R� M��z��
u�S��@�Gw�[�1XkQ�y�~�j�X/� :���P�y�R�����!������;3a��V�
!�E�#���n��5��	�27Qg0#8C����äI2Ls#�]��|Og�Å�C�e� ��p��R4G�e=� ��%��M+���1|/)�C�b�k�:w����A�!1j���xJ"e.6��˕X�\)7
=�8F��By5!�;c�NR5FTp� ?˴t������ux���:{���O>� =��D��,����g6/mk��{������C�w��¢Bda�s�N�'�<@����� �$ӆ8IF#d��"ݼ��Д���i� �H�����9��@H\�Yh����F�E![�l�($�*����CҔP��˃�s���e)�jD�Rc���%���y�y6� c�B@(��uYC�k���z=c59�>>V'Ĵ№�h�^�D�滋�����**���5�;]�T�J%�4A�:�j��G�{��d:r�Fc���IҌR��!*W)U�$�v��/�r�N�Gse��Cԇ]��a����y�^v���£����c�i�,��ڂ��ĉ&'��Z-W����)v�np�279�x�Ϧm;��p�������k7w�v�����je��Q*cl޼����Ǹ��;yh�S���s$i�����ܵ�����|���q����+hLN�R�1��Ҥ��3�$MY^Y����;���'�-����a߾}��%/a��팏���J!G@�ۦ��̠�F:M�e[\�ǟ�Z���x����S0Ʈ���8�����M�w�T��k�A�<�2�s?� /D���6�� �PR��R����B��9'��^���J%u�!$.
���]]m�<ϳ�8�|߷�v�c�a��V+�V�i�$�Z��RJ�tI��}oj�1��T�q��岖�@`��R��N,$�V;��M��vD�r�*��0zN�_w	ܺaD�C���k��a߿x�
�!�<���~N<�_���yɵ�9�+�0�A�kP�0Y%5v�*=sH{�/X�Zg$c=2?%��a�.Xךp�;,E \�j�L@��tǨu��jv��9#F}+\�P�(yY#BczC2���X�f�YΠ�����Y#&k�.g��"P�|M�) W��C��aS+�)%QB�֎n/e�3���	�Em%�+9KI@�8B�g�U� z����9'�TW�������o=����8�����Z++�s/�x��\�����
��!9�S�R1�h�{�N�ɉq���zQ
��H�{��	H�OJ<��K�q��C���sh����AHotX�(�!Z�2��,�*�@҇,^��E�Ƀ��s���c��Y �2��q�b������AUք��Ŵ�6�ER��,����2L���]N%)��4�k��L��U�O�R&��ڏ��#���	�>�$AI��'���o�R�E��c��05����z=*����R}�,�6��z�~jh���=a���ڳ����\��H�F�f�s<�ȓ�@")�<~���9�:H���I�p�E�Q*W趖����69Ccb2W�\^b���|�d����j��z�j�����enBH�A��cϰq�^6m�̫_�j���۸��;8o�6�?g7G���^elb�7��'��gC>��[�������䁧���J)���0�hcYXn���brr���fff���K���+���D�u#`E`�Y��ɣ���H)(E%N.w��ɧX�R��������A�e�y�w�3i���|uw��n��1�f@$$A�Hq�X�UĮ�!m���-#��ڠ"viQ"D�
�  `���i;=���Wef�y���{��}.�{`��鞮�/�9�;��]#,��q�M'��z�awŲ�M��?ŤkӴ���Zڨ��DЯ�e�zRW ��i������R� ��&�� �}���8g\h�+S�� ��+�n�k�E�RJI�x�iF��=�*!@1b�`�q�cۆTII�� #��I�v{m}��c����A�Ri	2�%�,s=�ݎv�RF�Wm*2�U����XK���j FH��^%`����)$��J�Q��J"Jz�bϰГ����|""�M�����kW�TJ%9	vD�:C˒U�KA@�Ŏ�b�)�"���* ҧ������KO��v�>9�ӕLԟє_)�LM���_�d7�Y�Hڬ��6=�t�Q�(�		�ko�R1��P������3�e��u	��P�P0A��$L�q�_D.�s� |��Z�G;������t�TJ����V��|��K��
���U
7P���N~"L�B�\֌t�a�6 	�j��]*��
N��je��u�mXO������q���2�hsp�UA�	�=��< �6�	uk�S�)@��-��0����WP��]�sr��`(G�X� /A� ��V;�'9�.LÀmp��<	1TDj'��C'$n�Dk��I�Pk��O[La�KX8�r�
\��*v>�8���v{�,HI�fv���>��ϣѩ�u]���@8���b|tS[�1?7�����2X��-�&����?=���qL�c��-
%�A�f�����<fg�bb����o���(�X\\����Q(��}���,������?}bS�/��ݨaŸ����0-���´,|�/����U<y�!X���
��x��Ǳpk?~�m��>�-S`���	�S(�D�سg/:��G�bll��U��^cy���)T�߃봰Q_���@ζ���k�¹�'����{� ���ﾌ/=���3�_�!$���a�J�D�~BtO��f�w�gr�<��A)v>זa��{�!�(Ƙ��D�P�o�/\�e�s��$B����p�,�J�� a�) ��8!�e	J)�Ǡ��\*{�粵�u�1�
�|��R��G�(N���R��m�':N�xA!����2!|�Pm
��js��ׅQ��/-��d_Cқ�Få�tޘ�O��ɫ���4RŒ4���)�6��I�
���.���HsH@	��{2��%(��,0��%�dԀ(�&� ����t�b�D�yňA�Nɐ�Rx��|H�=?��e�X#�e\�c4�F(C�"�%YF�P��XA�s:">A_fn�~T	r�g"VD�/}d��&<�)8g���r&B��h=/�$j�����i@1PE��R CJa)���P�� B@� �/|�o������Ǐ�w��[��KJJ��,�P��fk����n���_���sa�^���Xd�%����`���uP*�Q��K���0�k7��et�mQo4��tA�@��(�����6ڀ]��0m�[P��ӡB�����RF��ފ� �l"P�:��@�ӄY֓Vk|xk�� ����V��n�;h����;4S��q��N)�
��JN��^����1(��c��!JI87�� �`�4,.�p�������t�v�BJ��*� �����z����"�`���9ض}nޝ��    IDAT�C��`�FGA��&��K(���3!���q���X_[��dA9��`]�O<�$��>����SX[]���(����h�Q���r0U*bcq��>���v`����8N��;���"!��o�08>��3ؽk'���o���__Ń��C�ߋ.��V�G�É�B�����3x������QG(�_�	8��1��	ƴ�^7rS$���i�Ӭ����.c�>3���]���&�x��A�,��ƜY(sLV�8�sk2��P��ċ��4T�Y�(���: ��(<?�$L�r�'sv��8�v(c`�id D�s�p`��-������P�(��$ R0F��=�q3gۡeYJ��Pa�|>�3F�R�m[�nr�-�R:*8��*T~�,��~����[�z����v��+�7:QZfr$kDBj�4��5 �3�]ܲ�ޗ�kBݿEhE&B=�qWz���ߨL�#�6;5����R43}Ǧ9�Դ�G:$��u�� n�E4�""��_ }A�0D��>䉐��H2�I�Y_�Nɴ�ƾ"�Y� ��$�2P��Q�I/A�d��'��x%��}��`3i/~�h���~X�m>br"���	*�.�Ǡ����X��+���yZ��x4�5��/�\$�2�B����탄��7ꗈ  �R�8���K/�������3g�˗j�a�L�S) �ˡ��@���%�Bj|Bd�0D�i`A�[���P���B@bxd-6��UX�<��kzwRB��(L�@�6�Zo y �W���t�����  :5�2��"�mA�"`����c���!$��`�x�
'*@1�F+9��GG )qyn��!�Q��1�	��&B��I�ks���#�y ̀"��ب�P�i��.z��so@�:�fU�(�<TA�K4j�:+ gbe��-�-�GA(��z���ю��##p]<�߷}+Vk�{�ݰL�za���  <���7�A�^Gζ1�m�?��_z	���r�
 ���q�����:5�h�[��?|�����2x~��N1JI�W@���$Z��n݊����^y�e�|�]|�/�{�cbb@�2�ꫯ������CG������066��QB�EfD�����]���uH�`zڞ_^ë��b���?�Lpt��:8�V�M�vNC>�^���!-�d�b��4� i!��T?�,%L�@#�8G(t��U�m����]��䯋u�Pm���{fvv�q��.��R%�AJ�2�6[-+����i�hx%����%�JY� ��\��%��\���R�0���'k  x���p�̽Gv\�һ{e��U���;��ǒ>�ǅ)]T��AF�q���d��ǩ���H�EIF0{J? Yw�Ha��>��O��V�B�{�̖!�f�oI�7C��� M�z�b*]��;��
$h�R��`z����Cũ������SuA�>�L��Q/�4d���)!)�Oi�8(dr�;@Ɩ�	R��w@��^��Q�d��u�R´-L<��&M�Q��N���1�ƨT�T
&%��<f���{( �aX6l�D�{�-E���J�%2@��cs33kΜ���#��[����z]�Fm�&р�Hm�%Z�����ڝʃ���R���Z*bi�&��� C����n�������ykH�����0MT�9x�:�n�`Q(B@��2��=4�!v?�"��"�� . ;>��TI��;h�r��O��	<kX��y_;�Q��a�?�Y�` ������x�b��`�{1���`�%إ2J��5������=�\���b���Jp<��!`��:>�V�� Q����"<׃�u�/� �ԾB����V1w�&LˆR
{vn���Ս�mC���%��������p��i<���<O<���O�w�uj�D`||+���\9K�F>:w�~�M���' ���>�e�R
Ԗn����qx�J)�x�	;z�?�<����:5�cG��g��h�����&��Ǣ)��;:B �s+�R�z]�=N��n��0Ԉ	e&�߼��Wo�j�Q��}$�ܑ�~�6���0$��r�骱b��D���`�@� �@��F;�t���`X�M��O�4�D��A*)�~!:4��.�Ҥ�B*�z�E��R��筜�����:33T���A� �9Q"i��3.8SRqN\�3z��a[�0M34.97���0��3�'L�W���Ca�H�T����E�յ��/�|i���c�0��#��x�Dۭ"%��9G$��	���8N-y̮'QyPQ��Y� ���(� ��ǀ$	��p}����%�{z?���Y��u�,is�%��-��k�6Ͽ�O����ˤ�J���%�G��!����6ʪO͝5�UɪDf%�	ʜ��I�s���e���	�AHԜ�ر0~��Q�$E4����q1˱Q�9P̅  ͘ɨ���Q�G�@0^���@����axt ��A%*vHR�J��?�
)�T��y��O� ��B�h�'�5;��}���cǦO���%�IE��4�R����ll4���i�3�0a�,���X����q>�e
��y��G��Wqׁ����Gs�5g��Z���cѾ*��2p��"n6%�=aN���Y�J	
JQʙ@�C0��'�^��0#�4��0�0��u��\E���[wB�.�G�S`��»|�bqb6j+�*b�T���p�H�i|��+�~���s���h�ձ�j�5t�RH!P(W08<���"JŢ���\�[u�K��eaj�6ܘ�ի���	rn°r(k���FGGP.�a�X^��Ѩcbb�~�Y����x�'+LOo��'߁���h6122������#�/h6�~��ױ�2����y�5�2H!��8B(*#㐑	���8����m�ͷ��w�?�O}�I�����Q�T  �f3� $��	��6�����nJ�D�2����>8���jǡ#�}�}A�0e
�ةPؖ��+U��ɳ��ŋ'?�pɂ!���=���hb*!�w�0���רKN02�uZn%��x0�C��P�

$g��J��[�_����-..H)I
*�` �Q�׎R��>oll�r��!��D�	j8[II�C ����(%�$�Pe0��TD)��&H�s�ju���̿8Z)>�~��z	s\F�Q������+B�H�54V��"�W+G��X��hΠWE$�$��q��hT,M����@}�N@�BRS �4'���2�{����� �]����"�OP�c��q3)cY�T�+�6*�V�>�X*�P��ԤL����ܐ�?�M��C�R�#�u"TH��9*q�Ld�}�M�;�d�#"D�(ͮ���� Q�T�5
6�D��cy��R���r)��N^G�N�|�5[�2�9�DR��3H*ô�O}���7޸4:>1t��Sm۽����N\�ti��������R#(
h�;��� �(!�:�,[�V��t�f���ظ�+.P�BA	���E�@2�R��6ί71F���n j��t�C���W���~���BM:$�g�@TR�$�`�&��|fi���K0�Qo�hw����[k5�G��c���۩�j��2T�ލ���`pu�^"l�����x��C�4��Ѕ�t����������[�� |��6Zm��qA�={v�̙3�.@I�#��} �u�޻�F���c[A���yα�����1�8q?�яpcf[�l��z���{��s��&�:*CC��V�.c���$3n��o�͏�$p�݇@ n#R57@(�`uL�"�e�w~��q�]waue>�  ������d�sZh���mo�u� J�0MP�D����_���z�.��<LU�"�0��ixR�F���PU^�[��'���}{F��������r.ڞ��w[��Q���I���)daw@ T�b�ց9Z�JJPBU��)K���������1WX\Zp]� ?`Y3B�cL;��^�gv�,�~(!�&{i�2�~�C)Q�2%u� ��3�z?��r�&[�X��^�1���-[���¶}_$l)�Ju3;}�.�?�whd�CI\���3J����nM�������64n �ǥ��N�����'Ց��B������ĵ�`�^O�4cF��>��M���U�*W���~7�x��ߴ ��x�O�j�# I5u2�\*�!q��C�Tߧ��d���,)jb�G�<dt?�d�R�ʏD鐪=���/�(��ߪ��+E�.g��P%LC�3	 `Eβ#NJVߨ�	I⎕3FL��{X(�8�e����GzgO��Z[[�9����c����V��Z�E��F� }L'_.�P�7`�6�G���s`�> �  W��:���X\Z����BN1>Z��k`�!��5�6�P��]��P�@���M�3��/��a�� 9KK �P`��	�(�ξ�=�<��F?�D\�"Ș��~���ۘ�1,�*�v�g��c��Ʀ�[|��)mT�7�I*C4	V�\Eu�n�x��Є���fϛ�lۊ��A!? Ӵ��6(j53�c�O�dp��G��Z���:ƪe���e-{����eYX\X@eh���q��o�](၇^~�eLm�˶����66����C��R�����x������}�|�(���`ee�c��޶�՛Ip�Ғ2,/��?}� ���>�`����q)$�o^C���M�|߇��8x� >�v��d@�C�A� n�A���N��0@ �m�9�jup~�޼z������c "�T�f�G�h�
����o/����wc���'�Q0�FυCZ�����(>����!������^g�U 7"��hw: (D�F*�~ͬb`�KC���)�2�7�:�]���~�X[�Yݞ˃ `J)jۖ)���BT�!ճ�T�4�-��/��b���HJ���	$�	mV2�v{=^� �#��)��(��s3���;E�m���	@tR_�ؗXX3JYR�c��Ȑ>�I�N����V���.y1�=���=� H���g���F�&��'��+�>�!,5;#)�>KH⺇L 6��Yo��&@��d��U���2�xё�1�R}i�a��d���H��`@����@EA�2�ݐ��>D���D��6�(�X�M@Z�cy�^�(^J7B*�P@D�+EO�"g�Y�޻ؒ=C���;��N�����N�N��9p��^J(}��7˷n̎���mo������h���P@!_����p�Q�ȡ���2L�0���M \�
r�}X<�>		E(�@ar�~��oj+n�/b��0#�l�� �@��}��~>���r;�F��3���\��-�V&"��Ϡ��~<���@"W6n��~�]D���V��h�롻c��5l���p{�6��y`�_���/~�� �VK�@�Z���Q�f}n�A���by��Ѳ�L�N|�H�@(E�z�%�b���z��r�����T0[�L��Kx��'
���5�\,����x�w �@e` Ǐ�+�����e4�M੧������n#��c}eSc�XYYC�ۉ\�,��j�ԥK)�r�V����Xy��y�>�s6</H�{1��RX_�	�uP�;�w��v���Өt�u���l�t�Z�c�&��&.^�����	��O��[��3$H�ˍ��T��T�$B��pE]�YW�.�$��k�����K���h�@�`���p;uv��Q�"�{���6��m0�6>��<���f&�N[�v:m|x}���n�g~�=��..�g._5�筍�&s�]�| �c����r٭5�f����	!�Tjp���!���yF��)jE8OUp��D/N���JFaH�b�J��9 ػcJ�g���R�9X.����|>!T�T&���HsFA	��N��mh�3�kWJ�n���D��>(b����M�m"$�"�l���UL�4�'!����?�L���O��uP̀L��$��U	�:�*B�B�oNƙ�;�K�}�~2�E�L���xgڐ�ۤ~��iH*{�H�Q��wE�E9�jʨS߬�Oy*Q\����/�t}�[Aʄג q�c�c���(�a�69�0�U��׾��'Ж���PB�Ȏ
��� ����8�|�X�w��n ��^[�v���P�z��ѣ[Ϝ<9��R�R�N$B�8��̍�<�##X����\��aA� �v��!�L^�+�����F�蔇�xs��6x��
�Rp�F��+g�����t���'*~a�ɱa�[w�����]?		�/v��4��M ��!�<��7iJ!$ͮ�N��sW�~�w��:���@ȏL�݋K�^����@wy�pD��E�����@�P�?']�Iwk��A��Ї|A�PJU����u�� �1�a�}���>���C�\���"��� ��rزeΞ9�-[�`���8}����p��|��'1==���v��ŋ���`X6�'Ɛ�z�v+bs�C�����7���� ,�s�� ���ǭ���/=���q�~?�7M7@�Q�﹨O�80���t�>�kK��.��u�2(B���gpz~���|��/��82J39Q�K(��0
!��JENdDA*��-L��&��Go�/�8��B[F
x�r�a�����,A�:���Ɣ"\����j9�=���^���3�A�eP��@�X^����&�V����Jq~n�\YX
W��X��V����K��5�={��߿��"���������F��'D��0Je$�R
@���jYR) l�9���Z�(���T��Rah��zkT)|�5���S�q<�Z�������vPd6rv.:�#Ă�0=���!zNM�QC���qM�3�R9U�<� �I���uA���h�U*c#}�8wh �FXԤdMj��t�}/� �)[���̸�2��}�ě�q��Je&�د_m�Oŉ~'D����x�Ef<:!3p}�q}�`'M���Q�̥�Un��3+��5�������؄1i8bD#�6H%�5��vR��8H*�̩n0-�e\rΣ�Y䠬@��x(�C�6Y+��| (�<_<�����/������}��u=�t�����ӧg|����w��q���|��e�F�y���wQ��\.#���RIp��p�������X__��� �@���I\�Z��Z�f�#�i)j�N)`x
��Kp�Jw��
@y�3��!��B�����"���G�?zTC��A��Y�F=娵{���ͦQ]��v��܀�PC�;=��*ܹ�\�[Xo��/X���h���̄�ڭu�:��qH)a�fҌ)%�I���g�a��4�Oo���W���p�m�CB`��-x��p��u���⣋�q�� ��c����/��c�!���'���/㽓'��O �=��^y	w�}��&022���fo��1)Q(����Cۧ1�e
�/�0�D�g��Qě����>��Gq��#(�s�a("�}P��6�E�i�T�ik�UGmu�NR�J�����o�����s_
����� *s n�~i=�*:P�����'�����W��_9������.`��d���ꝚR��`�N���!D�+s���sgq��I����+	]�XXG���Z#]�G;�l�ڼ�"�0�"*�Q����m�i
 �˩r��wO�;7�l�r\����R��"~�f�eK)	7��������!Im!�q.H?XѲ�/b��M,���"��B���aRض�u���bӔ?��h��-m#�>��i&��I~))�$�0��"]vd���9��E���H����ͦˑLb_�V���!C���E���^�5B�2!�C���0����h_/�M�C��J������͈�#"�K���9x:F*5bL�e*�%t}�*��Ϸ����4O��#AOd� 6xꋛN�2��@��+f���8���;���d|B@�RB�V����ꗿ�p.���瞉N�c���f.�)�é    IDAT??�����F��j���f�"�ӌȀ�"h�1��s�!�0D�u1R�þq�Ïa����h�w�n݂W�p��A�'�l���#��R��ecY�����=��@(n���A��OpEB�" l?|�;{"603b��Ox/C���^����śضm�bݞ�X&�&�9p��@H�N��ht���Ʊ�рz�d�6z��\��h��p�p]WCM��A�z����9| �z�a���`��� RHض��;w�w�Ɨ��%����ְujT��m�6T�U|p��x�qLmق��z
��� �Zyۂ�m�֍k�~�vl߁juS�ch4p]O7( &)�������#f#	h������ڻXXZ�=�c|t4ip�&�1�0�X_B�U��+�q�N���eC��Õ�x��x�W�g���T�(�Y�x5E�TE�T��a��@I����g�8���C��_�|��c;_�Y�mg/��׾�:����{�Z���G�a���_���� r�� R������(j��D��T*=�~��{�BQ,j�M[*!�v��7�M�����1�� �sY�m��j��`z5M�TgH��:�cZ�)L�E�4M� *n�0SB���u���~�4@(J�,�,Z(������42.t$���#Ҕ�Gc�|�@��p$�����}�! $ͫX�k��ɞd��67YG��8s��,�Oi����l��N*+�K�dzG.S�Qd�Ŀ�(�����x��m��mD����L�q|G��R�I�E2k���!2@�Q��A����B��F52�@�?�$w(6]�H���Lګ7^#HF��cI�*5w�������%���sfh�X��o�j����>���= ��w�,�����Ͼr�<X)��m+�km�H��L鰕b>�v��\>����>�a��<X�!����aaQBO�@�
C����,`���nؕ�!(��(N��0��7��g�N��CM�O$��!P�J)�f�����~qh3�2���1U�H\j�(�꽘��sx�Ľ��挃�l��Q�f�j���BWIL��b��u=�3g��6L+���auu�R9!.�a��^g�_���(V����/��O<ƴ�������s7������v4����Hu�|�P|����}w�ul����4�o���o���<�4�UL�U���a���(adxs��X[_C�\F�Z����x�����؈8#��*�0�����|x��܇=��c��)�JE\g�+��:��Ӭ%Ҩ�mC(���7��^�����F'�o���֟4�\�����P�^�j=7��
RJ-�� ���,�
x��u�����V��$� �J�E���1fBK()�c�l��չ%����X����W���ݘن��N��7�޵����G��˰M�PP"D�vqn�P�N�M?�Ԗ��@��u6Z�38�U�k;�(��Ϟo�ۖ_fR��4��3C�ܾsC)��33�$��)�8W��2%�$���s�ǵC�!�f@�Qm�ʸ2 �P�� �9N|_��$Ķm���	g"S�<�G��l1VQ3�bӗ��OR	���ĈA5�����'��C���KIҐDw�4#	!tsO�E��Yl�N�$ҧg�i�>�$�	� �A�Fi��K"Mטwj �"I���
w0J��H2��*Q"lO�=�d�+%��P 2C����J"�@(���/���h���,#%�/���(����D>J��#YkH�%�MbL����Q%��2Z=A�Mb�ͻ���@*�4���>���_�|��������]�`���l�X�������y����~h����#����楓���V�1��j  �CPJ�q�ݕ����KX)U����{A a�K:2�/@�D_)��	NY�p�0/}t���H�#���Q� f��H)�|�$�:�m�7���V��2���,�����91J��Z�E��1�a�60y� 陸���2%�u�C��A�2�BJ02:�(*4Tl�u��� ��޶�� T��(!�:\�:�g��^|��>y���8���c�J�Z�bzz�Ν���(�����!
�<��݋��Q��s��|���\��o����w���Ց	Lo�����F�r�B�͍:��2p��U��ﾻ��=�b������bqi�P�2���@�rƇ���r(�((�L9ۂ��1{s��z�B�������{�h���O
>��,�;�f{i��L���#��#�uH1o+˰J��������19T�l��Z�E��öL}HeU-2U+()�?��7єؽs�sx���?����΀���o���q�[o����!]����j���:(�<�/F�RR�P�THAn�
E��2L��*bǛj��R��c�Z���h5��S�eLJ�DaH�^�PP0LC0JcL&����\
!�R�� �a��'����"�H�U�d�Si��$��`���/�'{��ҽ�w�D�:0�"�TWNx;iX6�6�Dln T:L�]�9@E��x���#�&'0��3O��!�����7շ���@@�����>z�͇�e��ܝ�F;Y��f#�4ABJ���ƣ2�-��&(>%�DI ��Q��X ��A�P��{F�Q�(�!&TF��&F�J��%��Q�} IW���� �Rz~P�d"�DA�/O��T��w��p���[��zyd|�������qn����=�Ў�k3����m�ii6��P3�������a�6�P ���iw04X�Ab���ܕKz7���'z�8C����"�r	�/5'ڭp�ԇetXvo^]A���ri@O�
���R��:НJ%��v�&@�6I�4��	��K���aF+��*��:���	!@�sA�A���;��m"�}�!���Fg��J�m����PR�4-\�5ʴ��!a QB�bm}�NՑaX��������ի�}�W��{�P,����+طg
�5�M6�+&���G��~��|�Ә�_@�p{.\�C���������?�cC%,���ps�:>8}
�����(Qx��I9��e��-t��0�R�f�<|?���~|�65*ൺ������'�]��/7���B�J��ǃ���ut���q��ݵ'�62KJ)�r��籏o�C!@%�v�\��a�Ktia�t;�B�'?��ei�����������C�N�F�Ŗ��GU�j ̢�?���ǧW1�e+:�&:Ng.��o|�A�J�<w��������;�p�-8��x�e�4�X�����u{�4��mcR%�ͨ���Ä���!�|�	cL���2��,+��h�z�!��F�Z�&t�)�>� �}���(
�����F;$r�+�H�>i 0ciX`&,��aS����>��<O�,��}I{�~=}�D�H����a�q����d���Ќ�_*p�N}(Ȧ®6�l���J&Yq�@�]~Gk����āI��F�hT@i"��L��>2]d��2Ùߓ����w�b���LV�$S���[FI�Q@2~J�2A!"����~1oAB2I"<ts"d�)Uj8�ߟ趉b!UZPB!!b?��Ǆ���'�"� �����7_z����>����Z��t_|�����~�G�����\������>�|~n��9���߿�0�R���Z�i�X(�.;z-�z�Ba���cpe	]#�E��t@��*�p�����7�A�@B�E.�e�e0\�|peO>T�����,�
�'�C)�[�+(�D��#(o�ѹ}(�r; ��/�+�[��k �j�&���V����0@yz+�{���������"�̙�����(T���D�4A	���Ḙ.�, EQ(T���Xè�v ���kp:���'�rH�3��c`p o�s��P,��jc��
JEl�W102ð&''`M0F��va<�C{��ns;����_�|��_D!���{�~���1��c�������G��`�(l�j	�W�baa�wM�X(�4����m�����_3������Ǟ�����DD����ezk�1���{���IY��H���֣1����qW5�Ҩћ���ʥ����"�m��WkC9.Ln!$�&������z�,��j����� W`����D�� �J��M\�x��/�R��iBI�DxcaU?Q����.��*�zH�����o����d7W{pC�zC�Z��;�G�l�lqy��>'ĔN�˥�TQ�!e�)�$
��_.�v�c�������{��+]z���i��s�s<��vʘ�����"�M��!�pm�lT���13B&��6m|*UY"Z<!gDG�!/�Ld$y)����*<(�����GݦѾ3O�OJ�7��]ƱQ��ʲ9	/}j���G��YVJA
�9�}�4�SW*�kI�+��0%����Dl$��`�K�H�H:�	J��R�������i�ybi��I�0A���G&@�Gh�L�����Ǆ�2���3J�Hm��gA�K'�1�xk~cuy�u��������z���w�;�+���#?�P>��[����[wl/�<����!Y�)np]C�
p�P*���<�	�Ρ�n��j!o�  lc
��T�Y^A~�.�_�¨�ȏ�Aݘ`$�B�i�1�|�
-^��f�䃇A)�'�^�����:�|BQ&��+(�,����2
�B&#@��� L�O����0*����=�Q��!��;��,t���/B�Z�62���(����	%�-�k���׾�5L���	���111�[��=�1��E�� � ��78��e]x��N��Z��F�	�Ä�V�n�ò
�vc����ڵ��Y�߻��+��2:H��ݻ�ΝC�Z���"�����P��Ӭ��{�af�&������=8�ȃ���}?����A\�p]�	�Q�� X^Yһ9)Q�Vq��,v�څ��W���6$
�4Ѽ�@������ÿ�׽�a��f��0�cG������M���E�U*�c��A�]���\�L�fnХ��Ioy�R�r�0�Z�C)	W�1�g讬P��!0M��q��G���j���k@�(ſ���c�#Q����i�px�����#� <o!B��E���P��G���_<5�%�V�����2#�����Hy� %H���@)��r����1C��SAq%)�*C:8X麞��0������;Ί��V#^@�SJ�e��R�tb(W$��� L��E�|J@t���輳pNv�NHw$K��\e�$��%��&S��G�f��R���7#�͔��P�f��L]���,,-"6]��g,�U3l6e��!R����>B%�G1Q�d��9ck݌up�5IV5���-}h�����Qb�l2`�;�;F
�#�D�M UD�L����JB
};&d���	d�T)�8	%�����d}����BJȹ��|��=R)��֜���jN����/�ڡ���>��{9�+��o���ޅ0۶��vap��r������y;�sX������UB�b0���ƭ�(��	�rep����H��PI	n���K�޷��<^����Z���"ē'�œC{Н��n����C��ð&F� L���@u� ���_�7N-�0y*rk�D���$p�[)�rӏ?��S8p���Y�Ɨ2�)��p����ϟ�?�yލ��+0�V`n�=���9�i[S�̃sa��v���?Ƒ�w�ģ���-p�0{���@X<�Q������P`��D���Re�2x���G����ƭ[���>������Ӑ��O��cx��iL���:T��_��Wq���v�;��f����\.���I�~۶���<� N}p9���K0���wٙg����x�G�a|�dx�֦�H�x���@�ޘaׯ^f�W.����n �qa2�Bխ�#�8��J%��\T���C��Y�L�4D�a*���!n,���w�dWy'�{�97U��a�'*�(�� 	$0����k>��鳽��y���z��k���5k0k�	&� �BHH�4�M����*�t������%��g45ݷn������B��`Lԏ�-�o<�;>�B��B��E��q|���&G����71���_���q��;����|=C���}�q�v�U��_ң�z�ǀRXYX����"s�P�2d��q۶��6��L��k0��&"�Bp��"�$����{���+˙�z��@'��jh�07͐�A�Z�f�A�2���3�A-��Q8	��qΠOA��x�0� ��C��&nfRs!J��;Py� "���|�7-K��S�l�_�"4�eb֝b��݇�֕4��U�@�g��F]�I��T"ՊmN�	��ڛn'��L���iZ�Z�H�!*�M���"�S� �t�ki��rF-#����)�Th5���($��
�����63��L�	赟�W�5� +�+�c�^��{��E0gO>��	��.����=!;��ţ�Zc���6��/��h=e���bmuk����Aʈ��!�:�P�s���L��B������*�v��iD�艫�1^X%��٣�)������R��w���S.��1�iu(	rס�:>�����3;���H9QЩ.%P�b�K�����-��ֿ�L�a�#��㿏o}�+(��ƕ�����/Fcy˫�-��>�ְ,��:d�&;j����B��q�9=���S`qֽϼx '�,`i��0[�s�Z��j�
�$����V�Ha)%,��>�x����z
aF�+R�r2��bl|['�p�#�W\�*t�_�"�\r��p��Q1�q��N�a~n7��d�� |%#+�+����cD,����Z1E���ru�����S��������f��`<����ځ��4�����q�����b�L��E��=�n�P;&���Q�4�iqU�pb��P�\L�:6x�0>�7w �+��<�kg�~�
|�O~�E�թCx����G�o�c��A|��~}��/NcjY᏾�\�G^p���e9 ,-�p����T��,%�=OD�&L+�)��3�W�sE�\?
��\��l&��\�&	�s�@L5	o1�?�JF��5i?ٙ��R�u��W�L�9'���o��vdo"��Կ�MLZ��6���i���	~-�a���M�v�l�����6{����!1ꆸ�>$�c-j�%�W�:@S�}�Y�8�5�����ع�	D�R㐘�@��1 O� �Ş,r�	���2��.���Z�����g9�Bpp!�?y���a���i0��e�"�&L˂iٰ,�e��-����o۲���fZ��Mӄm���D��Pi�\��E��S� �_�0�����ٺkG����G��;o���w�g�����}�i�dE#�6���P,�Z9���۱ˋ8~�8��*��cc`�au}L�kUع���*sgѳs8،���a2���蘶�f�ǰSh:�ʾcxύ�E^(xYK�^� ��<��}PȀ\?1|c@}0	_��>|�H��[�e�
��B���M+Íݻ�0a˛n��(��R3_b�E8�����g�K���?���5`���'#�ׇ��l-��]��J}�^<��i�n#%[�J����aX�����eEp�ӏ=�0�ͨ�T'gG���E�mǩ�3�ܺN�7��.FFF�я�>��O�رcصk<σ�!J}��l�����0�w��|����뮽o~�;��O��'��e0�<���E�<888��~7��f\r��x|�����E�8��q���6n��f���vO�|�v��h`�Qg�f�遇lz�IV[X&�Z�cf�e�|�x����GT�7�B��ع=dJ+#c���\=��Ib	�3�Yl�������8�z#��|�^�|F��?��[�bH�J    IDAT����p��<\_����ϑ�%��5�C�U���o����gp�~����p�,�Jzuu��W�y(%@�j՜���� �ˮQ��s�1��Q`����25���t�z��d\��)Ps�u|�G�/�@�� `ZiZ�T��l��U.T�
��l�'��P76�8fB�޵�ah{�#��&�x��ڲ����k�(�:����PG$��0#Z'��"�;״��yl�HE�D�����x�d��D�f�M@������9������ǽ)i�FsgIwH�[�	֒82 ��h�!Y�
�Z ��b�k�e<�	J�Xb�c*�j%�v���i���v�N�W:A�׌��zg@n�����=�^2��8& ֨V�p��N����Ʒ���ˈ-��V��!_ȧ�	��/��}�6H)Q�VP��  �Fkkk�_\ �UP��E�߇������92"����&�8�bL���,5�8���:�;|0Mh?�3V�Ե;�]���������&�> �8;=�?��C`�IG�(U�-&gd��!'T��~�m��#����И�2	3�?�{��1r?������ñ�g���wb���Wo�57܀l6/�����
��Ku�J��2p2y,��!B�	��q��A8N.a��>f�i���i�JEx��Ņ9��J~B��j0�}��p�䩄L)��{��?8��maumJk�������bht^xN�<�\.�Z�70�'����m�:y7�r#�tW|n�������g̓��s�4u�Pj�Ғ7�����$��/����_����}���(/�O��w8�N�{ɗ)�Q��w0:�E�A�u��_�i%0���X�J,��-�y�6��_{g|���S��|�g߂�U|{�i�w��x�5��K/Ǟ�//���?>�O�i�)�~�-���^�ٙ9^*���O�HR�B? ��1�OU*U�s��2�X�)�P�0�`\	.�!�
��v�XVX,�R��rΥi����ʈ4c1��Y��V����kiy�,����D�WLXn��C��*Vw�$W�,e˛��s|b%�qb<"�4Wʉ�dS��)$G	IW9F0ڟ�#QJE��R���=K;��:���]&��Fx5;!�W���Oh}6k�&��Ú�Jq�B�!��X[��)���1o�.���͌�(g���Z��1c���f�Xk;�s����P�&B�zOp���=-����� `�LÀ�@Äi0-#R��lہe�-O�V���#��R��� �&`�� �?v���֝;.����'�wR�gΞx�'�|�[�..,N��WBι(���֭8}�V���6�V^{_O�-���0;;h�l.�\.���~�r9�O�~�%X�$�j����"ݨ�X�k.4E�1˶cFf�l�4���~�".�hWd�����q�5W���A���Kv4V ����<_ϡ8��n:�QT\���.v�SS�T��E�67��fg �j���a��񣇞���}8��A�����'q�[��`/��j��W.!�� �B��Ƕ-���䇻ܯN&�ťe��۶〜:L�j=�̓a�/�c����@?�gf14�'[h�b<��֭���=��OcǶm�V*PJ�0m�n���q<��3x��n��y����q�����?������O?
�3�A�Z��|�I��^xN?��;v��S�lD�//	cX9v_���[����UE��2"uR���|��?v�$����/�Py,;?L8����ň^�4ԫF�dJ�R�Xʩw������?��8Y��G�Y�a�p�)�݇_��~pR	$��7ߍ�vO���� ����R.�O �G�z5��b>�`��_ϥ���w�������#������ZZZ58i=80P-e�~>��^Õ�X�44IǶM��BȦ�#���D�i���h���	�Ri�Ѱ �������L���ި�'�-�S�
�k��0�!�U\H���f��6S>Y+��௟*�t�C��?��8kO�t0�S���>5c��QE
��N�݆��ז�>�yS7l+L������u�4��&"6�"��O����K�ZЎ&��`M5!��h�X��[���D]��s�>�͆�Z�N0�f���w�$��)d-�uT�֚�n:��@r��o"���� ����}��غs�@�@_V�!���g{�����tۭ#�|���v�����a��[ނ-��3N�EG�����Y,�,�R�B�!���Po4P�|�3��x���(�bH0��8r1ZbX�,R�ME�V��r��Sgq��i�m@k72���r�S�^�� S��w>��=>��ض�O�dR��2@ٲ�СL1��ѻ�,<�,�==�:�G�`�s/���?���nCa�G�|���2���F��o�13;���5H�!��a�FԁB?��]��fZ��������+��r���`���'.��
g�+غu�K+��.#�����z�����/b�ZA�q��F(��".��*,.,�s_�:</@���ϼ'�����'1<ԇ��
�Z�ERJ�R��-�-�!�|ţ+�rp���ؗ��U{��` ���YY`_���w~﷝�|⏭�?�O�-���l���P2�9�j�Ѿ�bp|L�2����n��W^ep�oR�� D�*��g�. c��]��O��8��ֽ���ށ�v!�y7 ga�� r}n���a�ʥ����V�N��O9Π��q�v�4�[_��R���)�������d�0�T�q� W���+Θf�i�Hc�-�а,+����z�aHF��j�ȑ�@Z�����Ti�ޞRcltt])E���,(
�D�"7�ͷG	���ob�w������m�)	4�I	�m<�suN�M2�&�%���B�J)L��)1K�M`�6"K�:�Vu4I���D%%�@��wo�*'�k����:W����s�`-T��H4��oDQ�I��5���[�ƱD�ߛQ���gNm$���R(B�-�����x1�����ZVq$�y���U5 �Б���������7\5	bD�C�V_|j��3�i���>^��p��Kx��c��i��}�:5�ވ��B� A�01>b���W�,..`nq���S'��F�0� �20;�D�ݡ�D@��n(K0��m|�{O�@B�� �F����xU@x��#�㏿x?�a���GP.�B�)S	#$�a8&�� jG#�7eHa��E<x���\s=ʣ���?��ͫG��vab�'^�j�U�8~zK+� ��	�4a�&)1�7���1��Z�o�r�^����4��<z�e0ӄ�Iiݼ�1��.�`�i`��4�F%��RJ��J�2:�{�xK�:�!@Q����Q��}���'��o߉��C����{��O���������y�������(����D�W8�b���}������%��'���S�|���������"�
2�0MaD?^�r�R��. �*���m�F�)m^��+�ޛ�y��8o�B>�=7�՚��?�Z�p��A|�?�m�e�C;��"�dcj�0�\��X0MJB��*8g���xí7�B^��E�c���4MH�P���r�P���PQ�<T�1RZ�0� �׌q��:rK�5I�(�d�������H�0�pM �4b��R+]VpCY���ק@��;�v�f0T��&�{I�w�Ѫg1^�G�@�.l	�=�N���*���)�m(����R1�al�4�1�}��ͺ�&���9m�K�MVcS�t��%T	R`<b�<*�-�ft�HX�Ic�QJ��J5k��٩��%4a$��A�Xţ���G)�ͯ΢���{0��F!1��:mJ�7B2�J@��0��xz�P,f&�m-�PJ�r�O��;u��j�@?ܺ��e�t�0^|��:q
�+������Xz�=�s����.�WV@ ,����p#���03YTߓ0�%����D�m;�Ct�H��<����p��# �CnT�q�FP>|
������Y��S:�S3�s�8�b��
�v�V�!76�p!� "�� ��{����0r�vL�p��n����@��h�o�@oY��z���Zk~ 22N��&wl�z]��M�1��s7���G�� �ܔ1�9�̙XNc#C�>;���(�� ��w�.A�G�~&6��R*��j��/�N����wߏJ����>��mo���!���� UrqFFFq�e�u��gL Dh�����W�ӿ����;�c%Л@����Cʰ+�@���%�<N����E� �nE�c�ZkMa��YH��J�">��?q��K����F5����/a�� >��0�������l���֭�e�?z�����|���g�����8}^�u��%���KضkR��?�x� ��6�r��Z����`��� Ði�avh��Bn��������h4\ÐE:hh%U̡"�ؙ`tht=���q쯦i&Ɣ:��&��ES-D��A��q#b�#��������v�D ͟�T�t#�Qwz=�\�ι�;ǍG��`��J��X��h�j��f�OR�)�($6G/��Q�8��/J���+�$G�����%����V}����X��Ɇ*ů��"�p^t��)]"�dj_	$�Ij�N�򀐤�������o4 �N��8
�z�<��3�/���-�㘂s�4ܗ^<8���|�4"(8����^h��?�����܆�J~@I�P�Ќ��=�0��Ѓ��E8��0r��<��3� ������ѨbK�$��;n×����UPm	ڭ�x5`�,�[���g�G�m��o��}�^�	�0�u:}����`xƠd���Hb�^}{.�75�lOo�����B�7^��o߁�����A�RP2D�6�s�.:ocC}(�s(��YYA�4�2�/�p����d!��3����!>������q ��z'k�!8Ǚ�ix�088 �qp��In=5�R"gYx�e�cij
�N��a��H���[����8|��{���Ԫ���+�}rߺ�.#���yi���r'J�{����/bqa
J)�z�04��C[aZ�x51u�+y"�*�R�h��Q���V[������0
�K3X[�Ce}^��D�(ĻT�%��8 ����$Jb����������l�2��[�ʘ)�쪋}fa�4xL�`L�ZY�%�z��Z��?}7�x�(&�J�:���I���X,�w�f´�R�_jh4��V���d;NF�Bk�I+� ��{�ި�jլ7�FT�i�H�8�-"G2�l���k�\�#b)C��g�u������k_�pA�xӸWw(���o@�Q�&�/.6�ti3]�&�Z���6.�8���f��LL��Y<�Ԭc���Y�n&�]�N�3o�W�Ļ����92���LOL�hS$����L�R��I��[R��SG-���匴QF�w%��*�V��_oh�h��z��l^k�m�촢�&��VJ��:xM> �^�~����Z��_t�e�Ji���jKK��ų��\䇼���byK��$��x�880�ro/n�1�����϶SL_R_SIGNATURE_ALGORITHMS_ERROR		 360
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
