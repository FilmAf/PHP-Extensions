#include "Domain.h"
#include "Dictionary.h"

bool validateCsv() { return true; };
bool validateImdb() { return true; };
bool validateUpc() { return true; };

//CDomain::CDomain(void)
//{
//}

//CDomain::~CDomain(void)
//{
//}

#define DOMAIN__(domain,height,width,maxlen,min,max,dict,format,fval,parm) {\
	{SS("eDomain_" # domain)}	,\
	CDomain::eDomain_ ## domain	,\
	height						,\
	width						,\
	maxlen						,\
	format						,\
	min							,\
	max							,\
	dict						,\
	fval						,\
	parm						}

#define DOMAINx_CHAR	(CDomain::eDecode | CDomain::eDataTypeChar)
#define DOMAINx_INT		(CDomain::eDecode | CDomain::eDataTypeInt )
#define DOMAIN_cCHAR	(					CDomain::eDataTypeChar | CDomain::eCommaSeparated)
#define DOMAIN_sCHAR	(					CDomain::eDataTypeChar | CDomain::eSpaceSeparated)
#define DOMAINxcCHAR	(CDomain::eDecode | CDomain::eDataTypeChar | CDomain::eCommaSeparated)
#define DOMAINxsCHAR	(CDomain::eDecode | CDomain::eDataTypeChar | CDomain::eSpaceSeparated)
#define DOMAIN__CHAR	CDomain::eDataTypeChar
#define DOMAIN__INT		CDomain::eDataTypeInt
#define DOMAIN__DOUB	CDomain::eDataTypeDouble
#define DOMAIN__DATE	CDomain::eDataTypeDate
#define DOMAIN__DAT_	(CDomain::eDataTypeDate  | CDomain::eAllowZeroDD	)
#define DOMAIN__DA__	(CDomain::eDataTypeDate  | CDomain::eAllowZeroMMDD	)
#define DOMAIN__TIME	CDomain::eDataTypeTime

const CDomain::t_domain CDomain::gp_domain[CDomain::eDomain_total_types] = {
DOMAIN__(none					,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,CDomain::eDataTypeNone),
DOMAIN__(datetime				,1	,16	,16		,1999	,2020	,CDictionary::eDict_none			,CDomain::eFormat_z_time			,0,DOMAIN__DATE),
DOMAIN__(aspect_ratio			,1	,8	,8		,1		,5		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(gamma					,1	,5	,5		,0		,3		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(money					,1	,10	,10		,0		,10000	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(money_null				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(rot_degree				,1	,5	,8		,-360	,360	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(time_interval			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DOUB),
DOMAIN__(click_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(advert_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(article_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(edit_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(human_check			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_counter			,1	,10	,10		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(obj_id					,1	,7	,7		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT|CDomain::eInputSearch),
DOMAIN__(pic_id					,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(runtime				,1	,8	,8		,1		,600	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(seq_num				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT|CDomain::eInputHidden),
DOMAIN__(version_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(genre_cd				,1	,32	,1		,0		,0		,CDictionary::eDict_genre			,CDomain::eFormat_a_genre			,0,DOMAINx_INT),
DOMAIN__(genre_cd_2				,1	,15	,1		,0		,0		,CDictionary::eDict_genre			,CDomain::eFormat_b_genre			,0,DOMAINx_INT),
DOMAIN__(num_pixels				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(black_pt				,1	,5	,5		,0		,90		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(crop_fuzz				,1	,5	,5		,0		,100	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(crop_pixel				,1	,5	,5		,0		,2000	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_counter_small		,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_disks				,1	,4	,4		,1		,1000	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_pics				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_seconds			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(num_titles				,1	,4	,4		,0		,1000	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(region_mask			,1	,32	,1		,0		,0		,CDictionary::eDict_region			,CDomain::eFormat_z_region			,0,DOMAIN__INT|CDomain::eInputDropDown),
DOMAIN__(rot_pixel				,1	,5	,5		,-100	,100	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(seq_num_small			,1	,7	,7		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(sort_category			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(sort_order				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(white_pt				,1	,5	,5		,10		,100	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(year					,1	,4	,4		,1880	,2020	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(star_rating			,1	,1	,1		,-1		,9		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(vendor_id				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__INT),
DOMAIN__(cast_list				,1	,1	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(edition_notes			,5	,60	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(article				,1	,1	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(email_text				,1	,1	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(explain_explanation	,1	,1	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(sql					,1	,1	,8000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(comments				,5	,70	,4000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(dvd_title				,8	,60	,2000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(dvd_title_nocase		,1	,1	,2000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pub_name_nocase		,1	,1	,100	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(advert_html			,1	,1	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(bonus_items			,3	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(caption				,4	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(dvd_notes				,6	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(dvd_title_tmpl			,6	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(episode_of_title		,1	,1	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(film_title				,5	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(proposer_notes			,4	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(reviewer_notes			,4	,60	,1000	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(microblog				,1	,1	,600	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(director_list			,1	,32	,500	,0		,20		,CDictionary::eDict_none			,CDomain::eFormat_default/**/		,validateCsv,DOMAIN_cCHAR),
DOMAIN__(director_list_nocase	,1	,1	,500	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(email_list				,1	,1	,500	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(imdb_id_list			,1	,10	,500	,0		,62		,CDictionary::eDict_none			,CDomain::eFormat_a_imdb_id			,validateImdb,DOMAIN_sCHAR),
DOMAIN__(url					,1	,40	,255	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(name_long				,1	,30	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(email_subject			,1	,1	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(film_title_single		,1	,30	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(film_title_alternate	,1	,40	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(film_title_single_sort	,1	,30	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(folder					,1	,20	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(justify_wide			,7	,60	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(justify_narrow			,7	,40	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(role_cmts				,1	,30	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(transforms				,1	,1	,200	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(publisher_list			,1	,32	,128	,0		,10		,CDictionary::eDict_none			,CDomain::eFormat_default/**/		,validateCsv,DOMAIN_cCHAR),
DOMAIN__(publisher_list_nocase	,1	,1	,128	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(sku_list				,1	,16	,128	,0		,4		,CDictionary::eDict_none			,CDomain::eFormat_z_vector			,validateCsv,DOMAIN_cCHAR),
DOMAIN__(upc_list				,1	,16	,128	,0		,4		,CDictionary::eDict_none			,CDomain::eFormat_z_upc				,validateUpc,DOMAIN_sCHAR),
DOMAIN__(url_small				,1	,1	,128	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(copyright				,1	,32	,100	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(name					,1	,30	,100	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pinned					,1	,1	,100	,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(city					,1	,32	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(country_birth			,1	,40	,1		,0		,0		,CDictionary::eDict_birth_country	,CDomain::eFormat_z_decode_int		,0,DOMAINx_INT),
DOMAIN__(email					,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(email_header			,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(explain_keyword		,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(genre_list				,1	,32	,64		,0		,0		,CDictionary::eDict_genre			,CDomain::eFormat_z_genre			,validateCsv,DOMAINxsCHAR),
DOMAIN__(filename				,1	,20	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(host					,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pic_name_longer		,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(short_descr			,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(user_name				,1	,1	,64		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(password_hash			,1	,1	,36		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(seed					,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(sort_text				,1	,20	,36		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(country				,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(country_list			,1	,15	,32		,0		,5		,CDictionary::eDict_dvd_country		,CDomain::eFormat_z_country			,validateCsv,DOMAINxcCHAR),
DOMAIN__(country_list_2			,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(custom_text			,1	,20	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(email_purpose			,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(external_id			,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(field_name				,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(group_name				,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(language_list			,1	,20	,32		,0		,10		,CDictionary::eDict_language		,CDomain::eFormat_z_language		,validateCsv,DOMAINxcCHAR),
DOMAIN__(loaned_to				,1	,20	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(mod_flags				,1	,10	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(object_type			,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(retailer				,1	,20	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(state					,1	,32	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(terminal_id			,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(user_id				,1	,20	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(vendor_sku				,1	,1	,32		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pic_name_long			,1	,1	,24		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(advert_format			,1	,1	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(advert_location		,1	,1	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(asin					,1	,16	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(order_number			,1	,20	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pic_name				,1	,16	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(upc					,1	,1	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_z_upc				,0,DOMAIN__CHAR),
DOMAIN__(youtube_id				,1	,10	,16		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(dvd_rel_dd				,1	,10	,10		,1990	,2020	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DATE),
DOMAIN__(film_rating			,1	,32	,8		,0		,0		,CDictionary::eDict_film_rating		,CDomain::eFormat_z_decode_int		,0,DOMAINx_INT),
DOMAIN__(film_rel_dd			,1	,10	,10		,1880	,2020	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DATE),
DOMAIN__(imdb_id				,1	,8	,8		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(text_dd				,1	,10	,10		,1800	,2020	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DATE),
DOMAIN__(user_date				,1	,10	,10		,1950	,2020	,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__DA__),
DOMAIN__(vendor_cd				,1	,1	,8		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(country_block			,1	,1	,3		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(pane					,1	,1	,2		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(action					,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(advert_type			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(allow_deny				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(amz_country			,1	,32	,1		,0		,0		,CDictionary::eDict_amz_country		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(blog_location			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(bool_check				,1	,1	,1		,0		,0		,CDictionary::eDict_yes_no			,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputCheckBox),
DOMAIN__(bool_ddlb				,1	,1	,1		,0		,0		,CDictionary::eDict_yes_no			,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(bool_pub_ind			,1	,32	,1		,0		,0		,CDictionary::eDict_public			,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(civil_status			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(contributor_cd			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(disposition_cd			,1	,1	,1		,0		,0		,CDictionary::eDict_disposition		,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(dvd_source				,1	,32	,1		,0		,0		,CDictionary::eDict_source			,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(feature_cd				,1	,32	,1		,0		,0		,CDictionary::eDict_feature_cd		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(frame_conversion		,1	,20	,1		,0		,0		,CDictionary::eDict_frame_conversion,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(gender					,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAIN__CHAR),
DOMAIN__(img_treatment			,1	,32	,1		,0		,0		,CDictionary::eDict_img_treatment	,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputRadio),
DOMAIN__(media_type				,1	,32	,1		,0		,0		,CDictionary::eDict_media_type		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(membership_cd			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(moderator_cd			,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(obj_type				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(pic_source				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(pic_type				,1	,32	,1		,0		,0		,CDictionary::eDict_pic_code		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(pic_type_2				,1	,32	,1		,0		,0		,CDictionary::eDict_pic_type		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputRadio),
DOMAIN__(rel_status_cd			,1	,32	,1		,0		,0		,CDictionary::eDict_release_status	,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(request_cd_dvd			,1	,1	,1		,0		,0		,CDictionary::eDict_request_dvd		,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(request_cd_film		,1	,1	,1		,0		,0		,CDictionary::eDict_request_film	,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(request_cd_person		,1	,1	,1		,0		,0		,CDictionary::eDict_request_person	,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(request_cd_pub			,1	,1	,1		,0		,0		,CDictionary::eDict_request_pub		,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(request_cd_pic			,1	,1	,1		,0		,0		,CDictionary::eDict_request_pic		,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(person_role			,1	,16	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(role_type				,1	,1	,1		,0		,0		,CDictionary::eDict_none			,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(sound_system			,1	,20	,1		,0		,0		,CDictionary::eDict_sound_system	,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(suitability_cd			,1	,32	,1		,0		,0		,CDictionary::eDict_img_suitability	,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputRadio),
DOMAIN__(surround_mode			,1	,20	,1		,0		,0		,CDictionary::eDict_surround_mode	,CDomain::eFormat_default			,0,DOMAINx_CHAR),
DOMAIN__(trade_loan_cd			,1	,32	,1		,0		,0		,CDictionary::eDict_trade_loan		,CDomain::eFormat_default			,0,DOMAINx_CHAR|CDomain::eInputDropDown),
DOMAIN__(video_mode				,1	,20	,1		,0		,0		,CDictionary::eDict_video_mode		,CDomain::eFormat_default			,0,DOMAINx_CHAR)};

//DOMAIN__(zz_check				,1	,1	,1		,0		,0		,0,c_format_z_check			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_row_sort_del		,1	,1	,1		,0		,0		,0,c_format_z_row_sort_del	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xa_pic					,1	,1	,1		,0		,0		,0,c_format_z_pic				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_pic					,1	,1	,1		,0		,0		,0,c_format_z_pic				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xc_pic					,1	,1	,1		,0		,0		,0,c_format_z_pic				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xa_vid					,1	,1	,1		,0		,0		,0,c_format_z_vid				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_vid					,1	,1	,1		,0		,0		,0,c_format_z_vid				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xc_vid					,1	,1	,1		,0		,0		,0,c_format_z_vid				,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_title_matrix		,1	,1	,1		,0		,0		,0,c_format_z_title_matrix	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_director_matrix		,1	,1	,1		,0		,0		,0,c_format_z_director_matrix	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_cast_matrix			,1	,1	,1		,0		,0		,0,c_format_z_cast_matrix		,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_crew_matrix			,1	,1	,1		,0		,0		,0,c_format_z_crew_matrix		,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_dvd_pub_matrix		,1	,1	,1		,0		,0		,0,c_format_z_dvd_pub_matrix	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xf_dvd_dir_matrix		,1	,1	,1		,0		,0		,0,c_format_z_dvd_dir_matrix	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xc_display_name		,1	,1	,1		,0		,0		,0,c_format_z_display_name	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(xr_role_dir			,1	,16	,1		,0		,0		,CDictionary::eDict_role_dir		,0							,0,CDomain::eInputDropDown,DOMAINx_CHAR),
//DOMAIN__(xr_role_cast			,1	,16	,1		,0		,0		,CDictionary::eDict_role_cast		,0							,0,CDomain::eInputDropDown,DOMAINx_CHAR),
//DOMAIN__(xr_role_crew			,1	,16	,1		,0		,0		,CDictionary::eDict_role_crew		,0							,0,CDomain::eInputDropDown,DOMAINx_CHAR),

//DOMAIN__(zz_dvd_publisher		,1	,1	,1		,0		,0		,0,c_format_z_dvd_publisher	,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_links				,1	,1	,1		,0		,0		,0,c_format_z_links			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_row_number			,1	,1	,1		,0		,0		,0,c_format_z_row_number		,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_screening			,1	,1	,1		,0		,0		,0,c_format_z_release_dd		,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_text				,1	,1	,1		,0		,0		,0,c_format_z_text			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_title				,1	,1	,1		,0		,0		,0,c_format_z_title			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_title_2				,1	,1	,1		,0		,0		,0,c_format_z_title_2			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_cart				,1	,1	,1		,0		,0		,0,c_format_z_cart			,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_price_comparison	,1	,1	,1		,0		,0		,0,c_format_z_price_comp		,0,CDomain::eInputNone,DOMAIN__CHAR),
//DOMAIN__(zz_best_price			,1	,1	,1		,0		,0		,0,c_format_z_best_price		,0,CDomain::eInputNone,DOMAIN__CHAR)};
