#ifndef PHP_DVDAF_H
#define PHP_DVDAF_H

#define PHP_DVDAF3_EXTENSION_NAME		"dvdaf3"
#define PHP_DVDAF3_EXTENSION_VERSION	"3.0"

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#pragma warning(disable:4273)
#include "php.h"
#pragma warning(default:4273)

PHP_MINIT_FUNCTION(dvdaf3);
PHP_MINFO_FUNCTION(dvdaf3);

PHP_FUNCTION(dvdaf3_getvalue);
PHP_FUNCTION(dvdaf3_translatestring);
PHP_FUNCTION(dvdaf3_strlen);
PHP_FUNCTION(dvdaf3_substr);
PHP_FUNCTION(dvdaf3_textarea2db);
PHP_FUNCTION(dvdaf3_db2textarea);
PHP_FUNCTION(dvdaf3_itod);
PHP_FUNCTION(dvdaf3_decode);
PHP_FUNCTION(dvdaf3_getbrowserfield);
PHP_FUNCTION(dvdaf3_getbrowserow);
//PHP_FUNCTION(dvdaf3_validateinput);
//PHP_FUNCTION(dvdaf3_validateinput2);
PHP_FUNCTION(dvdaf3_logrequeststr);
PHP_FUNCTION(dvdaf3_exec);
PHP_FUNCTION(dvdaf3_stardescription);
PHP_FUNCTION(dvdaf3_encoderegion);
PHP_FUNCTION(dvdaf3_gettableid);
PHP_FUNCTION(dvdaf3_getfieldid);
PHP_FUNCTION(dvdaf3_getfieldcolumn);
PHP_FUNCTION(dvdaf3_getfielddefault);
PHP_FUNCTION(dvdaf3_getfieldlabel);
PHP_FUNCTION(dvdaf3_getfieldseparator);

extern zend_module_entry dvdaf3_module_entry;
#define phpext_dvdaf3_ptr &dvdaf3_module_entry

#endif	/* PHP_DVDAF_H */

/*
Instructions to create a function callable from PHP

	File dvdaf3.h
		PHP_FUNCTION(hello_world);
	File dvdaf3.cpp
		static function_entry dvdaf3_functions[] = {
			PHP_FE(hello_world, NULL)
	File hello_world.cc
		PHP_FUNCTION(hello_world)
		{
			RETURN_STRING("Hello World", 1);
		}

Pitfalls:
	-	tsrm_ls is only defined fro multithreaded environments use TSRMLS_D
		and TSRMLS_C for funtions with no other parametersise TSRMLS_DC and
		TSRMLS_CC for funtions with multiple parameters (it includes the comma)

	-	use zval** in preference to zval* when using convert_to_string_ex
		or some other function the modifies/converts the zval.


*/
