#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Constants.h"
#include "Commons.h"
#include "StaticStr.h"
#include "Str.h"

class CDictionary
{
// Enums
public:
	enum eType
	{
		eDict_none				= 0,
		eDict_amz_country		= DVDAF3_DICT_AMZ_COUNTRY		,
		eDict_dvd_country		= DVDAF3_DICT_DVD_COUNTRY		,
		eDict_disposition		= DVDAF3_DICT_DISPOSITION		,
		eDict_expire_reason		= DVDAF3_DICT_EXPIRE_REASON		,
		eDict_feature_cd		= DVDAF3_DICT_FEATURE_CD		,
		eDict_frame_conversion	= DVDAF3_DICT_FRAME_CONVERSION	,
		eDict_img_suitability	= DVDAF3_DICT_IMG_SUITABILITY	,
		eDict_img_treatment		= DVDAF3_DICT_IMG_TREATMENT		,
		eDict_language			= DVDAF3_DICT_LANGUAGE			,
		eDict_media_type		= DVDAF3_DICT_MEDIA_TYPE		,
		eDict_pic_code			= DVDAF3_DICT_PIC_CODE			,
		eDict_pic_type			= DVDAF3_DICT_PIC_TYPE			,
		eDict_public			= DVDAF3_DICT_PUBLIC			,
		eDict_film_rating		= DVDAF3_DICT_FILM_RATING		,
		eDict_region			= DVDAF3_DICT_REGION			,
		eDict_release_status	= DVDAF3_DICT_RELEASE_STATUS	,
		eDict_request_dvd		= DVDAF3_DICT_REQUEST_DVD		,
		eDict_request_film		= DVDAF3_DICT_REQUEST_FILM		,
		eDict_request_person	= DVDAF3_DICT_REQUEST_PERSON	,
		eDict_request_pub		= DVDAF3_DICT_REQUEST_PUB		,
		eDict_request_pic		= DVDAF3_DICT_REQUEST_PIC		,
		eDict_person_role		= DVDAF3_DICT_PERSON_ROLE		,
		eDict_role_dir			= DVDAF3_DICT_ROLE_DIR			,
		eDict_role_cast			= DVDAF3_DICT_ROLE_CAST			,
		eDict_role_crew			= DVDAF3_DICT_ROLE_CREW			,
		eDict_sound_system		= DVDAF3_DICT_SOUND_SYSTEM		,
		eDict_source			= DVDAF3_DICT_SOURCE			,
		eDict_surround_mode		= DVDAF3_DICT_SURROUND_MODE		,
		eDict_trade_loan		= DVDAF3_DICT_TRADE_LOAN		,
		eDict_video_mode		= DVDAF3_DICT_VIDEO_MODE		,
		eDict_yes_no			= DVDAF3_DICT_YES_NO			,
		eDict_genre				= DVDAF3_DICT_GENRE				,
		eDict_genre_lower		= DVDAF3_DICT_GENRE_LOWER		,
		eDict_birth_country		= DVDAF3_DICT_BIRTH_COUNTRY		,
		// Count
		eDict_total_types
	};

	enum eEncode {
		eEncode_char1			,
		eEncode_char2			,
		eEncode_char3			,
		eEncode_char4			,
		eEncode_int
	};

// Private Variables and Structures
private:
	enum eSort {
		eDictSort_unsorted		= 0,
		eDictSort_sorted		= 1
	};

	typedef struct
	{
		unsigned int			_Code;
		const CStaticStr		_Decode;
	}	t_option;

	typedef struct
	{
		const CStaticStr		_Name;
		eType					_SelfIndex;
		const t_option*			_Options;
		int						_TotalOptions;
		CDictionary::eSort		_Sort;
		CDictionary::eEncode	_Encode;
		int						_Default;
	}	t_dict;

// Private Member Variables
private:
	const t_dict*				_data;
														static const t_dict __none				;
	static const t_option ___amz_country		[];		static const t_dict __amz_country		;
	static const t_option ___dvd_country		[];		static const t_dict __dvd_country		;
	static const t_option ___disposition		[];		static const t_dict __disposition		;
	static const t_option ___expire_reason		[];		static const t_dict __expire_reason		;
	static const t_option ___feature_cd			[];		static const t_dict __feature_cd		;
	static const t_option ___frame_conversion	[];		static const t_dict __frame_conversion	;
	static const t_option ___img_suitability	[];		static const t_dict __img_suitability	;
	static const t_option ___img_treatment		[];		static const t_dict __img_treatment		;
	static const t_option ___language			[];		static const t_dict __language			;
	static const t_option ___media_type			[];		static const t_dict __media_type		;
	static const t_option ___pic_code			[];		static const t_dict __pic_code			;
	static const t_option ___pic_type			[];		static const t_dict __pic_type			;
	static const t_option ___public				[];		static const t_dict __public			;
	static const t_option ___film_rating		[];		static const t_dict __film_rating		;
	static const t_option ___region				[];		static const t_dict __region			;
	static const t_option ___release_status		[];		static const t_dict __release_status	;
	static const t_option ___request_dvd		[];		static const t_dict __request_dvd		;
	static const t_option ___request_film		[];		static const t_dict __request_film		;
	static const t_option ___request_person		[];		static const t_dict __request_person	;
	static const t_option ___request_pub		[];		static const t_dict __request_pub		;
	static const t_option ___request_pic		[];		static const t_dict __request_pic		;
	static const t_option ___person_role		[];		static const t_dict __person_role		;
	static const t_option ___role_dir			[];		static const t_dict __role_dir			;
	static const t_option ___role_cast			[];		static const t_dict __role_cast			;
	static const t_option ___role_crew			[];		static const t_dict __role_crew			;
	static const t_option ___sound_system		[];		static const t_dict __sound_system		;
	static const t_option ___source				[];		static const t_dict __source			;
	static const t_option ___surround_mode		[];		static const t_dict __surround_mode		;
	static const t_option ___trade_loan			[];		static const t_dict __trade_loan		;
	static const t_option ___video_mode			[];		static const t_dict __video_mode		;
	static const t_option ___yes_no				[];		static const t_dict __yes_no			;
	static const t_option ___genre				[];		static const t_dict __genre				;
	static const t_option ___genre_lower		[];		static const t_dict __genre_lower		;
	static const t_option ___birth_country		[];		static const t_dict __birth_country		;
								
	static CDictionary	_Dict[CDictionary::eDict_total_types];

// Constructors and Destructor
public:
	CDictionary(const CDictionary::t_dict &pDict)	{ _data = &pDict; }

// Private Methods
private:
	const CStaticStr& decode(unsigned int x, CDictionary::eEncode pEncode) const;

// Interface
public:
	static CDictionary& getDict(CDictionary::eType lType)
	{
		if (lType > 0 && lType < CDictionary::eDict_total_types)
			return _Dict[lType];
		return _Dict[eDict_none];
	}

	const CStaticStr&	 getName() const			  { return _data ? _data->_Name : CStaticStr::empty; }
	eType				 selfIndex() const			  { return _data ? _data->_SelfIndex : CDictionary::eDict_none; }
	int					 length() const				  { return _data ? _data->_TotalOptions : 0; }
	CDictionary::eSort	 getSortType() const		  { return _data ? _data->_Sort : CDictionary::eDictSort_unsorted; }
	CDictionary::eEncode getEncodeType() const		  { return _data ? _data->_Encode : CDictionary::eEncode_int; }
	int					 getDefault() const			  { return _data ? _data->_Default : 0; }
	unsigned int		 getCode(int i) const		  { ASSERT(i >= 0 && i < length()); return (_data->_Options + i)->_Code; }
	const CStaticStr&	 getText(int i) const		  { ASSERT(i >= 0 && i < length()); return (_data->_Options + i)->_Decode; }
	bool				 isSorted() const			  { return getSortType() == CDictionary::eDictSort_sorted; }
	bool				 isValid() const			  { return selfIndex() != 0; }
	CStr&				 AppendDefault(CStr &pStr) const { return AppendIntCode(pStr, getDefault()); }
	CStr&				 AppendIntCode(CStr &pStr, unsigned int i) const;
	int					 intToStr(unsigned char *pBuffer, unsigned int i) const;
	unsigned int		 strToInt(const CStaticStr& s) const;

	const CStaticStr& decode(int x) const { return decode(x,CDictionary::eEncode_int); }
	const CStaticStr& decode(unsigned char c0) const { return decode((unsigned int)c0,CDictionary::eEncode_char1); }
	const CStaticStr& decode(unsigned char c0, unsigned char c1) const { return decode(CHAR2_TO_INT(c0,c1),CDictionary::eEncode_char2); }
	const CStaticStr& decode(unsigned char c0, unsigned char c1, unsigned char c2) const { return decode(CHAR3_TO_INT(c0,c1,c2),CDictionary::eEncode_char3); }
	const CStaticStr& decode(unsigned char c0, unsigned char c1, unsigned char c2, unsigned char c3) const { return decode(CHAR4_TO_INT(c0,c1,c2,c3),CDictionary::eEncode_char4); }
	const CStaticStr& decode(CStr& s) const;
	const CStaticStr& decode(const CStaticStr& s) const;

// Public Member Variables
public:
	static CDictionary _none			;
	static CDictionary _amz_country		;
	static CDictionary _dvd_country		;
	static CDictionary _disposition		;
	static CDictionary _expire_reason	;
	static CDictionary _feature_cd		;
	static CDictionary _frame_conversion;
	static CDictionary _img_suitability	;
	static CDictionary _img_treatment	;
	static CDictionary _language		;
	static CDictionary _media_type		;
	static CDictionary _pic_code		;
	static CDictionary _pic_type		;
	static CDictionary _public			;
	static CDictionary _film_rating		;
	static CDictionary _region			;
	static CDictionary _release_status	;
	static CDictionary _request_dvd		;
	static CDictionary _request_film	;
	static CDictionary _request_person	;
	static CDictionary _request_pub		;
	static CDictionary _request_pic		;
	static CDictionary _person_role		;
	static CDictionary _role_dir		;
	static CDictionary _role_cast		;
	static CDictionary _role_crew		;
	static CDictionary _sound_system	;
	static CDictionary _source			;
	static CDictionary _surround_mode	;
	static CDictionary _trade_loan		;
	static CDictionary _video_mode		;
	static CDictionary _yes_no			;
	static CDictionary _genre			;
	static CDictionary _genre_lower		;
	static CDictionary _birth_country	;
};

#endif	/* DICTIONARY_H */
