extern "C" {

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)

#include "SAPI.h"

int safe_exec_(int type, char *cmd, zval *array, zval *return_value TSRMLS_DC);

} /* END extern "C" */

PHP_FUNCTION(dvdaf3_exec)
{
	zval *lOutput = NULL, *lReturnValue = NULL;
	char *lCmd = NULL;
	long lCmdLength = 0;
	int lArg = ZEND_NUM_ARGS();

	if (zend_parse_parameters(lArg TSRMLS_CC, "s|zz", &lCmd, &lCmdLength, &lOutput, &lReturnValue) == FAILURE)
        RETURN_NULL();

	switch (lArg)
	{
	case 1:
		::safe_exec_(0, lCmd, NULL, return_value TSRMLS_CC);
		break;
	case 2:
		::safe_exec_(2, lCmd, lOutput, return_value TSRMLS_CC);
		break;
	case 3:
		Z_TYPE_P(lReturnValue) = IS_LONG;
		Z_LVAL_P(lReturnValue) = ::safe_exec_(2, lCmd, lOutput, return_value TSRMLS_CC);
		break;
	}
}

extern "C" {
/// <summary>
/// Executes a small set of defined commands bypassing the safe mode restrictions
/// </summary>
/// <param name="type">0: only last line of output is returned; 1: all lines printed and last lined returned; 2: all lines saved to given array</param>
/// <param name="cmd">Command to be executed.</param>
/// <param name="array">Array where to return the output.</param>
/// <param name="return_value">Exit code of the command executed.</param>
/// <returns></returns>
int safe_exec_(int type, char *cmd, zval *array, zval *return_value TSRMLS_DC)
{
	int			t, l, buflen = 0, output=1, pclose_return = 0;
	php_stream	*stream = NULL;
	char		*buf, *d=NULL;
	FILE		*fp;

	#if PHP_SIGCHILD
		void (*sig_handler)();
	#endif

	buf = (char *)emalloc(EXEC_INPUT_BUF);
	if ( ! buf )
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to emalloc %d bytes for exec buffer", EXEC_INPUT_BUF);
		return -1;
	}
	buflen = EXEC_INPUT_BUF;

	#if PHP_SIGCHILD
		sig_handler = signal(SIGCHLD, SIG_DFL);
	#endif
	#ifdef PHP_WIN32
		fp = VCWD_POPEN(cmd, "rb"); /* Not able to link in Windows, unless this is a C module */
	#else
		fp = VCWD_POPEN(cmd, "r");
	#endif
	if ( !fp )
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to fork [%s]", cmd);
		efree(buf);
		#if PHP_SIGCHILD
			signal (SIGCHLD, sig_handler);
		#endif
		return -1;
	}
	buf[0] = '\0';
	if ( type == 2 )
	{
		if ( Z_TYPE_P(array) != IS_ARRAY )
		{
            zval_dtor(array);
			array_init(array);
		}
	}

	/* we register the resource so that case of an aborted connection the 
		* fd gets pclosed
		*/

	stream = php_stream_fopen_from_pipe(fp, "rb");

	l=0;
	while ( !feof(fp) || l != 0 )
	{
		l = 0;
		/* Read a line or fill the buffer, whichever comes first */
		do
		{
			if ( buflen <= (l+1) )
			{
				buf = (char *)erealloc(buf, buflen + EXEC_INPUT_BUF);
				if ( buf == NULL )
				{
					php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unable to erealloc %d bytes for exec buffer", 
							buflen + EXEC_INPUT_BUF);
					#if PHP_SIGCHILD
						signal (SIGCHLD, sig_handler);
					#endif
					return -1;
				}
				buflen += EXEC_INPUT_BUF;
			}
			if ( fgets(&(buf[l]), buflen - l, fp) == NULL ) break; /* eof */
			l += strlen(&(buf[l]));
		} while ( (l > 0) && (buf[l-1] != '\n') );

		if ( feof(fp) && (l == 0) ) break;

	
		if (type == 1)
		{
			if (output) PUTS(buf);
			sapi_flush(TSRMLS_C);
		}
		else if (type == 2)
		{
			/* strip trailing whitespaces */	
			l = strlen(buf);
			t = l;
			while (l-- && isspace(((unsigned char *)buf)[l]));
			if (l < t)
				buf[l + 1] = '\0';
			add_next_index_string(array, buf, 1);
		}
	}

	/* strip trailing spaces */
	l = strlen(buf);
	t = l;
	while (l && isspace(((unsigned char *)buf)[l - 1]))
	{
		l--;
	}
	if (l < t) buf[l] = '\0';

	/* Return last line from the shell command */
	RETVAL_STRINGL(buf, l, 1);

	pclose_return = php_stream_close(stream); 

	#if PHP_SIGCHILD
		signal (SIGCHLD, sig_handler);
	#endif
	if (d) {
		efree(d);
	}
	efree(buf);
	return pclose_return;
}
} /* END extern "C" */
