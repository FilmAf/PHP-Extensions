#include "DvdafFunction.h"
#include "DvdafStr.h"
#include "GetEnv.h"

class CDvdafLogRequestStr :
	public CDvdafFunction
{
public:
	CDvdafLogRequestStr(zval *pReturnValue, const unsigned char *pUserId, const int pUserIdLength, const int pAdvertId TSRMLS_DC);
	virtual ~CDvdafLogRequestStr();
};

PHP_FUNCTION(dvdaf3_logrequeststr)
{
	const unsigned char *lUserId = NULL;
	long lUserIdLength = 0, lAdvertId = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl", &lUserId, &lUserIdLength, &lAdvertId) == FAILURE)
        RETURN_NULL();

	CDvdafLogRequestStr(return_value, lUserId, lUserIdLength, lAdvertId TSRMLS_CC);
}

CDvdafLogRequestStr::CDvdafLogRequestStr(zval *pReturnValue, const unsigned char *pUserId, const int pUserIdLength, const int pAdvertId TSRMLS_DC)
{
	return_value = pReturnValue;

	CStaticStrAnon lUserId(pUserId, pUserIdLength), lReferrerSub, lReferrerDomain, lReferrerPath, lReferrerQuery, lHostSub, lHostPath, lHostQuery;
	const char *p, *q, *p_dot1 = NULL, *p_dot2 = NULL;
	CStr lStr;

	const CStr& lHttpReferrer	= CGetEnv::Str(SC("HTTP_REFERER"	), DVDAF3_SERVER, 0 TSRMLS_CC);
	const CStr& lUserAgent		= CGetEnv::Str(SC("HTTP_USER_AGENT"	), DVDAF3_SERVER, 0 TSRMLS_CC);
	const CStr& lUserAddress	= CGetEnv::Str(SC("REMOTE_ADDR"		), DVDAF3_SERVER, 0 TSRMLS_CC);
	const CStr& lHttpHost		= CGetEnv::Str(SC("HTTP_HOST"		), DVDAF3_SERVER, 0 TSRMLS_CC);
	const CStr& lRequestUri		= CGetEnv::Str(SC("REQUEST_URI"		), DVDAF3_SERVER, 0 TSRMLS_CC);
	const CStr& lScript			= CGetEnv::Str(SC("SCRIPT_NAME"		), DVDAF3_SERVER, 0 TSRMLS_CC);

	if ( (p = reinterpret_cast<const char *>(lHttpReferrer.buffer())) != NULL )
	{
		if ( p[0] == 'h' && p[1] == 't' && p[2] == 't' && p[3] == 'p' && p[4] == ':' && p[5] == '/' && p[6] == '/' )
		{
			for ( lReferrerDomain._Buffer = p = q = p + 7 ; *p && *p != '/' ; p++ ) if ( *p == '.' ) { p_dot2 = p_dot1; p_dot1 = p; };
			if ( p_dot2 )
			{
				if ( p_dot2 - q != 3 || q[0] != 'w' || q[1] != 'w' || q[2] != 'w' )
				{
					lReferrerSub._Buffer = lReferrerDomain._Buffer;
					lReferrerSub._Length  = p_dot2 - lReferrerSub._Buffer;
				}
				lReferrerDomain._Buffer = p_dot2 + 1;
			}
			lReferrerDomain._Length = p - lReferrerDomain._Buffer;
			for ( lReferrerPath._Buffer  = p ; *p && *p != '?' ; p++ ); lReferrerPath._Length  = p - lReferrerPath._Buffer; if ( *p == '?' ) p++;
			for ( lReferrerQuery._Buffer = p ; *p			   ; p++ ); lReferrerQuery._Length = p - lReferrerQuery._Buffer;
		}
		else
		{
			lReferrerPath.set(lHttpReferrer.buffer(), lHttpReferrer.length());
		}
	}
	if ( (p = reinterpret_cast<const char *>(lHttpHost.buffer())) != NULL )
	{
		for ( q = p ; *p && *p != '/' ; p++ ) if ( *p == '.' ) { p_dot2 = p_dot1; p_dot1 = p; };
		if ( p_dot2 && (p_dot2 - q != 3 || q[0] != 'w' || q[1] != 'w' || q[2] != 'w') )
		{
			lHostSub._Buffer = reinterpret_cast<const char *>(lHttpHost.buffer());
			lHostSub._Length = p_dot2 - lHostSub._Buffer;
		}
	}
	if ( (p = reinterpret_cast<const char *>(lRequestUri.buffer())) != NULL )
	{
		for ( lHostPath._Buffer  = p ; *p && *p != '?' ; p++ ); lHostPath._Length  = p - lHostPath._Buffer; if ( *p == '?' ) p++;
		for ( lHostQuery._Buffer = p ; *p			   ; p++ ); lHostQuery._Length = p - lHostQuery._Buffer;
	}

	lStr << SC(
		"INSERT INTO http_request "
			  "(user_id, referrer_domain, referrer_sub, referrer_path, referrer_query, user_agent, "
			   "user_address, host_sub, host_path, host_query, script, advert_id, create_dt) "
		"VALUES "
			  "(");

	if ( lUserId.length()			) lStr << '"' << lUserId		 << '"' << ','; lStr << SC("NULL,");
	if ( lReferrerDomain.length()	) lStr << '"' << lReferrerDomain << '"' << ','; lStr << SC("NULL,");
	if ( lReferrerSub.length()		) lStr << '"' << lReferrerSub	 << '"' << ','; lStr << SC("NULL,");
	if ( lReferrerPath.length()		) lStr << '"' << lReferrerPath	 << '"' << ','; lStr << SC("NULL,");
	if ( lReferrerQuery.length()	) lStr << '"' << lReferrerQuery	 << '"' << ','; lStr << SC("NULL,");
	if ( lUserAgent.length()		) lStr << '"' << lUserAgent		 << '"' << ','; lStr << SC("NULL,");
	if ( lUserAddress.length()		) lStr << '"' << lUserAddress	 << '"' << ','; lStr << SC("NULL,");
	if ( lHostSub.length()			) lStr << '"' << lHostSub		 << '"' << ','; lStr << SC("NULL,");
	if ( lHostPath.length()			) lStr << '"' << lHostPath		 << '"' << ','; lStr << SC("NULL,");
	if ( lHostQuery.length()		) lStr << '"' << lHostQuery		 << '"' << ','; lStr << SC("NULL,");
	if ( lScript.length()			) lStr << '"' << lScript		 << '"' << ','; lStr << SC("NULL,");
	lStr << pAdvertId << SC(", NOW())") << CStr::eTerminator;

	leakAndReturn(lStr);
}

CDvdafLogRequestStr::~CDvdafLogRequestStr()
{
}
