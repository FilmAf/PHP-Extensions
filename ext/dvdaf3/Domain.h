#ifndef DOMAIN_H
#define DOMAIN_H

#include "Dictionary.h"

typedef bool FValidateField();//CStr pStr, CStr pSource, CStr &pError, bool b_html);

bool validateCsv();
bool validateImdb();
bool validateUpc();

class CDomain
{
//public:
//	CDomain(void);
//	virtual ~CDomain(void);

// Enums
public:
	enum eType
	{
		eDomain_none					,
		eDomain_datetime				,
		eDomain_aspect_ratio			,
		eDomain_gamma					,
		eDomain_money					,
		eDomain_money_null				,
		eDomain_rot_degree				,
		eDomain_time_interval			,
		eDomain_click_id				,
		eDomain_advert_id				,
		eDomain_article_id				,
		eDomain_edit_id					,
		eDomain_human_check				,
		eDomain_num_counter				,
		eDomain_obj_id					,
		eDomain_pic_id					,
		eDomain_runtime					,
		eDomain_seq_num					,
		eDomain_version_id				,
		eDomain_genre_cd				,
		eDomain_genre_cd_2				,
		eDomain_num_pixels				,
		eDomain_black_pt				,
		eDomain_crop_fuzz				,
		eDomain_crop_pixel				,
		eDomain_num_counter_small		,
		eDomain_num_disks				,
		eDomain_num_pics				,
		eDomain_num_seconds				,
		eDomain_num_titles				,
		eDomain_region_mask				,
		eDomain_rot_pixel				,
		eDomain_seq_num_small			,
		eDomain_sort_category			,
		eDomain_sort_order				,
		eDomain_white_pt				,
		eDomain_year					,
		eDomain_star_rating				,
		eDomain_vendor_id				,
		eDomain_cast_list				,
		eDomain_edition_notes			,
		eDomain_article					,
		eDomain_email_text				,
		eDomain_explain_explanation		,
		eDomain_sql						,
		eDomain_comments				,
		eDomain_dvd_title				,
		eDomain_dvd_title_nocase		,
		eDomain_pub_name_nocase			,
		eDomain_advert_html				,
		eDomain_bonus_items				,
		eDomain_caption					,
		eDomain_dvd_notes				,
		eDomain_dvd_title_tmpl			,
		eDomain_episode_of_title		,
		eDomain_film_title				,
		eDomain_proposer_notes			,
		eDomain_reviewer_notes			,
		eDomain_microblog				,
		eDomain_director_list			,
		eDomain_director_list_nocase	,
		eDomain_email_list				,
		eDomain_imdb_id_list			,
		eDomain_url						,
		eDomain_name_long				,
		eDomain_email_subject			,
		eDomain_film_title_single		,
		eDomain_film_title_alternate	,
		eDomain_film_title_single_sort	,
		eDomain_folder					,
		eDomain_justify_wide			,
		eDomain_justify_narrow			,
		eDomain_role_cmts				,
		eDomain_transforms				,
		eDomain_publisher_list			,
		eDomain_publisher_list_nocase	,
		eDomain_sku_list				,
		eDomain_upc_list				,
		eDomain_url_small				,
		eDomain_copyright				,
		eDomain_name					,
		eDomain_pinned					,
		eDomain_city					,
		eDomain_country_birth			,
		eDomain_email					,
		eDomain_email_header			,
		eDomain_explain_keyword			,
		eDomain_genre_list				,
		eDomain_filename				,
		eDomain_host					,
		eDomain_pic_name_longer			,
		eDomain_short_descr				,
		eDomain_user_name				,
		eDomain_password_hash			,
		eDomain_seed					,
		eDomain_sort_text				,
		eDomain_country					,
		eDomain_country_list			,
		eDomain_country_list_2			,
		eDomain_custom_text				,
		eDomain_email_purpose			,
		eDomain_external_id				,
		eDomain_field_name				,
		eDomain_group_name				,
		eDomain_language_list			,
		eDomain_loaned_to				,
		eDomain_mod_flags				,
		eDomain_object_type				,
		eDomain_retailer				,
		eDomain_state					,
		eDomain_terminal_id				,
		eDomain_user_id					,
		eDomain_vendor_sku				,
		eDomain_pic_name_long			,
		eDomain_advert_format			,
		eDomain_advert_location			,
		eDomain_asin					,
		eDomain_order_number			,
		eDomain_pic_name				,
		eDomain_upc						,
		eDomain_youtube_id				,
		eDomain_dvd_rel_dd				,
		eDomain_film_rating				,
		eDomain_film_rel_dd				,
		eDomain_imdb_id					,
		eDomain_text_dd					,
		eDomain_user_date				,
		eDomain_vendor_cd				,
		eDomain_country_block			,
		eDomain_pane					,
		eDomain_action					,
		eDomain_advert_type				,
		eDomain_allow_deny				,
		eDomain_amz_country				,
		eDomain_blog_location			,
		eDomain_bool_check				,
		eDomain_bool_ddlb				,
		eDomain_bool_pub_ind			,
		eDomain_civil_status			,
		eDomain_contributor_cd			,
		eDomain_disposition_cd			,
		eDomain_dvd_source				,
		eDomain_feature_cd				,
		eDomain_frame_conversion		,
		eDomain_gender					,
		eDomain_img_treatment			,
		eDomain_media_type				,
		eDomain_membership_cd			,
		eDomain_moderator_cd			,
		eDomain_obj_type				,
		eDomain_pic_source				,
		eDomain_pic_type				,
		eDomain_pic_type_2				,
		eDomain_rel_status_cd			,
		eDomain_request_cd_dvd			,
		eDomain_request_cd_film			,
		eDomain_request_cd_person		,
		eDomain_request_cd_pub			,
		eDomain_request_cd_pic			,
		eDomain_person_role				,
		eDomain_role_type				,
		eDomain_sound_system			,
		eDomain_suitability_cd			,
		eDomain_surround_mode			,
		eDomain_trade_loan_cd			,
		eDomain_video_mode				,
		// Count
		eDomain_total_types				,
	};

	enum eFormat
	{
		eFormat_default					,
		eFormat_a_cast					,
		eFormat_a_director				,
		eFormat_a_dvd_id				,
		eFormat_a_dvd_publisher			,
		eFormat_a_genre					,
		eFormat_a_imdb_id				,
		eFormat_a_sku_price				,
		eFormat_a_writer				,
		eFormat_b_genre					,
		eFormat_z_best_price			,
		eFormat_z_cart					,
		eFormat_z_cast_matrix			,
		eFormat_z_check					,
		eFormat_z_country				,
		eFormat_z_crew_matrix			,
		eFormat_z_decode_int			,
		eFormat_z_director_matrix		,
		eFormat_z_display_name			,
		eFormat_z_dvd_dir_matrix		,
		eFormat_z_dvd_pub_matrix		,
		eFormat_z_dvd_publisher			,
		eFormat_z_expire_dd				,
		eFormat_z_genre					,
		eFormat_z_language				,
		eFormat_z_links					,
		eFormat_z_pic					,
		eFormat_z_price_comp			,
		eFormat_z_region				,
		eFormat_z_release_dd			,
		eFormat_z_row_number			,
		eFormat_z_row_sort_del			,
		eFormat_z_stars_dvd				,
		eFormat_z_stars_film			,
		eFormat_z_text					,
		eFormat_z_time					,
		eFormat_z_title					,
		eFormat_z_title_2				,
		eFormat_z_title_matrix			,
		eFormat_z_upc					,
		eFormat_z_vector				,
		eFormat_z_vid
	};

	enum eParm // select 0 one or more
	{
		eInputMask			= 0x000000FF,
			eInputNone		= 0			,
			eInputDropDown	= 'D'		,
			eInputRadio		= 'R'		,
			eInputCheckBox	= 'X'		,
			eInputSearch	= 'S'		,
			eInputHidden	= 'H'		,
		eDataTypeMask		= 0x00000700,	// .... .... .111 ....
			eDataTypeChar	= 0x00000000,	// .... .... .000 ....
			eDataTypeInt	= 0x00000100,	// .... .... .001 ....
			eDataTypeDouble	= 0x00000200,	// .... .... .010 ....
			eDataTypeDate	= 0x00000300,	// .... .... .011 ....
			eDataTypeTime	= 0x00000400,	// .... .... .100 ....
			eDataTypeNone	= 0x00000500,	// .... .... .101 ....
		eDecode				= 0x00000800,	// .... .... 1... ....
		eAllowZeroDD		= 0x00008000,	// .... 1... .... ....
		eAllowZeroMMDD		= 0x00010000,	// ...1 .... .... ....
		eSeparatedMask		= 0x00060000,	// .11. .... .... ....
			eTabSeparated	= 0x00020000,	// ..1. .... .... ....
			eCommaSeparated	= 0x00040000,	// .1.. .... .... ....
			eSpaceSeparated	= 0x00060000	// .11. .... .... ....
	};

// Interface
public:
	static const CStaticStr&	getDomainName(int lDomainId)	{ return CDomain::gp_domain[lDomainId]._DomainName; }
	static int					getInputHeight(int lDomainId)	{ return CDomain::gp_domain[lDomainId]._InputHeight; }
	static int					getInputWidth(int lDomainId)	{ return CDomain::gp_domain[lDomainId]._InputWidth; }
	static int					getMaxLength(int lDomainId)		{ return CDomain::gp_domain[lDomainId]._MaxLength; }
//	static CDomain::eFormat		getFormat(int lDomainId)		{ return CDomain::gp_domain[lDomainId]._Format; }
	static int					getMin(int lDomainId)			{ return CDomain::gp_domain[lDomainId]._Min; }
	static int					getMax(int lDomainId)			{ return CDomain::gp_domain[lDomainId]._Max; }
	static CDictionary::eType	getDictionary(int lDomainId)	{ return CDomain::gp_domain[lDomainId]._Dictionary; }
	static FValidateField*		getValidate(int lDomainId)		{ return CDomain::gp_domain[lDomainId]._Validate; }
	static unsigned int			getParm(int lDomainId)			{ return CDomain::gp_domain[lDomainId]._Parm; }
	static CDomain::eParm		getInputType(int lDomainId)		{ return static_cast<CDomain::eParm>(CDomain::gp_domain[lDomainId]._Parm & CDomain::eInputMask); }
	static CDomain::eParm		getDataType(int lDomainId)		{ return static_cast<CDomain::eParm>(CDomain::gp_domain[lDomainId]._Parm & CDomain::eDataTypeMask); }
	static CDomain::eParm		getSeparator(int lDomainId)		{ return static_cast<CDomain::eParm>(CDomain::gp_domain[lDomainId]._Parm & CDomain::eSeparatedMask); }
	static bool					isDecoded(int lDomainId)		{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eDecode); }
	static bool					allowZeroDD(int lDomainId)		{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eAllowZeroDD); }
	static bool					allowZeroMMDD(int lDomainId)	{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eAllowZeroMMDD); }
	static bool					isTabSeparated(int lDomainId)	{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eTabSeparated); }
	static bool					isCommaSeparated(int lDomainId)	{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eCommaSeparated); }
	static bool					isSpaceSeparated(int lDomainId)	{ return 0 != (CDomain::gp_domain[lDomainId]._Parm & CDomain::eSpaceSeparated); }

// Private Variables and Structures
private:
	typedef struct {
		CStaticStr			_DomainName;
		int					_DomainId;		// this is a check that should point back to its own index
		int					_InputHeight;
		int					_InputWidth;
		int					_MaxLength;
		CDomain::eFormat	_Format;		// a value from m_format
		int					_Min;			// used for validation of int, double and date years
		int					_Max;			// used for validation of int, double, date years and string length
		CDictionary::eType	_Dictionary;
		FValidateField		*_Validate;
		unsigned int		_Parm;
	}	t_domain;

	static const t_domain gp_domain[eDomain_total_types];
};

#endif	/* DOMAIN_H */

// ------------------------------
// special formatting
// ------------------------------
//c_domain_zz_check				,
//c_domain_zz_row_sort_del		,
//c_domain_xa_pic				,
//c_domain_xf_pic				,
//c_domain_xc_pic				,
//c_domain_xa_vid				,
//c_domain_xf_vid				,
//c_domain_xc_vid				,
//c_domain_xf_title_matrix		,
//c_domain_xf_director_matrix	,
//c_domain_xf_cast_matrix		,
//c_domain_xf_crew_matrix		,
//c_domain_xf_dvd_pub_matrix	,
//c_domain_xf_dvd_dir_matrix	,
//c_domain_xc_display_name		,
//c_domain_xr_role_dir			,
//c_domain_xr_role_cast			,
//c_domain_xr_role_crew			,

//c_domain_zz_dvd_publisher		,
//c_domain_zz_links				,
//c_domain_zz_row_number		,
//c_domain_zz_screening			,
//c_domain_zz_text				,
//c_domain_zz_title				,
//c_domain_zz_title_2			,
//c_domain_zz_cart				,
//c_domain_zz_price_comparison	,
//c_domain_zz_best_price
