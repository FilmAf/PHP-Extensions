PHP_ARG_ENABLE(dvdaf3, whether to enable dvdaf3 support,
[  --enable-dvdaf3           Enable dvdaf3 support])

if test "$PHP_DVDAF3" != "no"; then
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++, 1, PHP5CPP_SHARED_LIBADD)
  PHP_NEW_EXTENSION(dvdaf3,
	dvdaf.cpp			\
	AbsArray.cpp			\
	Context.cpp			\
	DataArray.cpp			\
	Data.cpp			\
	Dictionary.cpp			\
	Domain.cpp			\
	DvdafDb2TextArea.cpp		\
	DvdafDecode.cpp			\
	DvdafEncodeRegion.cpp		\
	DvdafExec.cpp			\
	DvdafFunction.cpp		\
	DvdafGetBrowserField.cpp	\
	DvdafGetBrowserRow.cpp		\
	DvdafGetFieldColumn.cpp		\
	DvdafGetFieldDefault.cpp	\
	DvdafGetFieldId.cpp		\
	DvdafGetFieldLabel.cpp		\
	DvdafGetFieldSeparator.cpp	\
	DvdafGetTableId.cpp		\
	DvdafGetValue.cpp		\
	DvdafItod.cpp			\
	DvdafLogRequestStr.cpp		\
	DvdafStarDescription.cpp	\
	DvdafStr.cpp			\
	DvdafStrLen.cpp			\
	DvdafSubStr.cpp			\
	DvdafTextArea2Db.cpp		\
	DvdafTranslateString.cpp	\
	Field.cpp			\
	GetEnv.cpp			\
	HtmlStr.cpp			\
	PhpAdaptor.cpp			\
	PhpArray.cpp			\
	PhpValue.cpp			\
	Snippet.cpp			\
	SnippetDvd.cpp			\
	SnippetDvdMulti.cpp		\
	SnippetDvdOne.cpp		\
	SnippetDvdPrn.cpp		\
	SnippetDvdUpc.cpp		\
	SnippetDvdWho.cpp		\
	SnippetField.cpp		\
	SnippetPriceOne.cpp		\
	SnippetPriceMulti.cpp		\
	SnippetRow.cpp			\
	StaticStr.cpp			\
	Str.cpp				\
	Tbl.cpp				\
	UnicodeStr.cpp			\
	Vendor.cpp			\
	, $ext_shared)
fi
