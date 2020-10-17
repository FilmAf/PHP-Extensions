#ifndef FIELD_H
#define FIELD_H

#include "Str.h"
#include "AbsArray.h"
#include "Domain.h"

typedef void FDeriveField(); //int pPrimaryField, int pDerivedField);

void deriveTitle();
void deriveDirector();
void derivePublisher();
void deriveCountry();

class CField
{
// Enums
public:
	enum eType
	{
		eField_zz_none					,
		// ------------------------------
		// dvd
		// ------------------------------
		eField_a_dvd_id					,
		eField_a_version_id				,
		eField_a_dvd_title_tmpl			,
		eField_a_bonus_items			,
		eField_a_dvd_notes				,
		eField_a_dvd_title				,
		eField_a_dvd_title_nocase		,
		eField_a_dvd_title_sort			,
		eField_a_url					,
		eField_a_film_rel_year			,
		eField_a_film_rel_year_end		,
		eField_a_director				,
		eField_a_director_nocase		,
		eField_a_publisher				,
		eField_a_publisher_nocase		,
		eField_a_orig_language			,
		eField_a_language_add			,
		eField_a_country				,
		eField_a_country_block			,
		eField_a_film_rating			,
		eField_a_region_mask			,
		eField_a_genre					,
		eField_a_media_type				,
		eField_a_num_titles				,
		eField_a_num_disks				,
		eField_a_source					,
		eField_a_rel_status				,
		eField_a_film_rel_dd			,
		eField_a_dvd_rel_dd				,
		eField_a_dvd_oop_dd				,
		eField_a_imdb_id				,
		eField_a_youtube_id				,
		eField_a_pic_status				,
		eField_a_pic_name				,
		eField_a_pic_count				,
		eField_a_list_price				,
		eField_a_sku					,
		eField_a_upc					,
		eField_a_asin					,
		eField_a_amz_country			,
		eField_a_best_price				,
		eField_a_amz_rank				,
		eField_a_mod_flags				,
		eField_a_migrated_ind			,
		eField_a_dvd_created_tm			,
		eField_a_dvd_updated_tm			,
		eField_a_dvd_updated_by			,
		eField_a_last_justify			,
		eField_a_dvd_verified_tm		,
		eField_a_dvd_verified_by		,
		eField_a_verified_version		,
		eField_a_dvd_edit_id			,
		eField_a_creation_seed			,
		eField_za_edit_id				,
		eField_za_dvd_id				,
		eField_za_request_cd			,
		eField_za_disposition_cd		,
		eField_za_proposer_id			,
		eField_za_proposer_notes		,
		eField_za_proposed_tm			,
		eField_za_updated_tm			,
		eField_za_reviewer_id			,
		eField_za_reviewer_notes		,
		eField_za_reviewed_tm			,
		eField_za_hist_version_id		,
		eField_za_dvd_title_tmpl		,
		eField_za_bonus_items			,
		eField_za_dvd_notes				,
		eField_za_dvd_title				,
		eField_za_film_rel_year			,
		eField_za_film_rel_year_end		,
		eField_za_director				,
		eField_za_publisher				,
		eField_za_orig_language			,
		eField_za_language_add			,
		eField_za_country				,
		eField_za_film_rating			,
		eField_za_region_mask			,
		eField_za_genre					,
		eField_za_media_type			,
		eField_za_num_titles			,
		eField_za_num_disks				,
		eField_za_source				,
		eField_za_rel_status			,
		eField_za_film_rel_dd			,
		eField_za_dvd_rel_dd			,
		eField_za_dvd_oop_dd			,
		eField_za_imdb_id				,
		eField_za_youtube_id			,
		eField_za_list_price			,
		eField_za_sku					,
		eField_za_upc					,
		eField_za_asin					,
		eField_za_amz_country			,
		eField_za_update_justify		,
		eField_za_creation_seed			,
		// ------------------------------
		// film
		// ------------------------------
		eField_f_film_id				,
		eField_f_version_id				,
		eField_f_feature_cd				,
		eField_f_film_title				,
		eField_f_url					,
		eField_f_film_rel_year			,
		eField_f_film_rel_year_end		,
		eField_f_episode_of				,
		eField_f_episode_of_title		,
		eField_f_director				,
		eField_f_cast					,
		eField_f_orig_language			,
		eField_f_language_add			,
		eField_f_aspect_ratio_ori		,
		eField_f_run_time_ori			,
		eField_f_genre					,
		eField_f_film_rel_dd			,
		eField_f_official_site			,
		eField_f_wikipedia				,
		eField_f_imdb_id				,
		eField_f_youtube_id				,
		eField_f_pic_status				,
		eField_f_pic_name				,
		eField_f_pic_count				,
		eField_f_mod_flags				,
		eField_f_film_created_tm		,
		eField_f_film_updated_tm		,
		eField_f_film_updated_by		,
		eField_f_last_justify			,
		eField_f_film_verified_tm		,
		eField_f_film_verified_by		,
		eField_f_verified_version		,
		eField_f_film_edit_id			,
		eField_f_creation_seed			,
		eField_zf_film_edit_id			,
		eField_zf_film_id				,
		eField_zf_request_cd			,
		eField_zf_disposition_cd		,
		eField_zf_proposer_id			,
		eField_zf_proposer_notes		,
		eField_zf_proposed_tm			,
		eField_zf_updated_tm			,
		eField_zf_reviewer_id			,
		eField_zf_reviewer_notes		,
		eField_zf_reviewed_tm			,
		eField_zf_hist_version_id		,
		eField_zf_feature_cd			,
		eField_zf_film_title			,
		eField_zf_film_rel_year			,
		eField_zf_film_rel_year_end		,
		eField_zf_episode_of			,
		eField_zf_director				,
		eField_zf_cast					,
		eField_zf_orig_language			,
		eField_zf_language_add			,
		eField_zf_aspect_ratio_ori		,
		eField_zf_run_time_ori			,
		eField_zf_genre					,
		eField_zf_film_rel_dd			,
		eField_zf_official_site			,
		eField_zf_wikipedia				,
		eField_zf_imdb_id				,
		eField_zf_youtube_id			,
		eField_zf_update_justify		,
		eField_zf_creation_seed			,
		// ------------------------------
		// edition
		// ------------------------------
		eField_e_dvd_id					,
		eField_e_film_id				,
		eField_e_edition_seq			,
		eField_e_alias_of				,
		eField_e_prim_title_seq			,
		eField_e_prim_title				,
		eField_e_editon_notes			,
		eField_e_language_dubbed		,
		eField_e_language_opt			,
		eField_e_subtitles_fixed		,
		eField_e_subtitles_opt			,
		eField_e_sound_system			,
		eField_e_surround_mode			,
		eField_e_video_mode				,
		eField_e_aspect_ratio			,
		eField_e_frame_conversion		,
		eField_e_run_time				,
		eField_e_creation_seed			,
		eField_ze_edit_id				,
		eField_ze_film_id				,
		eField_ze_edition_seq			,
		eField_ze_dvd_id				,
		eField_ze_hist_version_id		,
		eField_ze_alias_of				,
		eField_ze_prim_title_seq		,
		eField_ze_editon_notes			,
		eField_ze_language_dubbed		,
		eField_ze_language_opt			,
		eField_ze_subtitles_fixed		,
		eField_ze_subtitles_opt			,
		eField_ze_sound_system			,
		eField_ze_surround_mode			,
		eField_ze_video_mode			,
		eField_ze_aspect_ratio			,
		eField_ze_frame_conversion		,
		eField_ze_run_time				,
		eField_ze_creation_seed			,
		// ------------------------------
		// edpub
		// ------------------------------
		eField_v_dvd_id					,
		eField_v_pub_id					,
		eField_v_pub_seq				,
		eField_v_sort_order				,
		eField_v_creation_seed			,
		eField_zv_dvd_id				,
		eField_zv_pub_id				,
		eField_zv_pub_seq				,
		eField_zv_sort_order			,
		eField_zv_creation_seed			,
		// ------------------------------
		// eddir
		// ------------------------------
		eField_d_dvd_id					,
		eField_d_person_id				,
		eField_d_dir_seq				,
		eField_d_sort_order				,
		eField_d_creation_seed			,
		eField_zd_dvd_id				,
		eField_zd_person_id				,
		eField_zd_dir_seq				,
		eField_zd_sort_order			,
		eField_zd_creation_seed			,
		// ------------------------------
		// person
		// ------------------------------
		eField_c_person_id				,
		eField_c_version_id				,
		eField_c_alias_of				,
		eField_c_alias_of_name			,
		eField_c_surname				,
		eField_c_given_name				,
		eField_c_surname_first_ind		,
		eField_c_display_name			,
		eField_c_name_nocase			,
		eField_c_url					,
		eField_c_father_id				,
		eField_c_father_name			,
		eField_c_mother_id				,
		eField_c_mother_name			,
		eField_c_country_birth			,
		eField_c_state_birth			,
		eField_c_city_birth				,
		eField_c_date_of_birth			,
		eField_c_date_of_death			,
		eField_c_official_site			,
		eField_c_wikipedia				,
		eField_c_imdb_id				,
		eField_c_youtube_id				,
		eField_c_pic_status				,
		eField_c_pic_name				,
		eField_c_pic_count				,
		eField_c_mod_flags				,
		eField_c_person_created_tm		,
		eField_c_person_updated_tm		,
		eField_c_person_updated_by		,
		eField_c_last_justify			,
		eField_c_person_verified_tm		,
		eField_c_person_verified_by		,
		eField_c_verified_version		,
		eField_c_person_edit_id			,
		eField_c_creation_seed			,
		eField_zc_person_edit_id		,
		eField_zc_person_id				,
		eField_zc_request_cd			,
		eField_zc_disposition_cd		,
		eField_zc_proposer_id			,
		eField_zc_proposer_notes		,
		eField_zc_proposed_tm			,
		eField_zc_updated_tm			,
		eField_zc_reviewer_id			,
		eField_zc_reviewer_notes		,
		eField_zc_reviewed_tm			,
		eField_zc_hist_version_id		,
		eField_zc_alias_of				,
		eField_zc_surname				,
		eField_zc_given_name			,
		eField_zc_surname_first_ind		,
		eField_zc_father_id				,
		eField_zc_mother_id				,
		eField_zc_country_birth			,
		eField_zc_state_birth			,
		eField_zc_city_birth			,
		eField_zc_date_of_birth			,
		eField_zc_date_of_death			,
		eField_zc_official_site			,
		eField_zc_wikipedia				,
		eField_zc_imdb_id				,
		eField_zc_youtube_id			,
		eField_zc_update_justify		,
		eField_zc_creation_seed			,
		// ------------------------------
		// role
		// ------------------------------
		eField_r_film_id				,
		eField_r_person_id				,
		eField_r_person_role			,
		eField_r_seq_num				,
		eField_r_character_name			,
		eField_r_role_type				,
		eField_r_credited_ind			,
		eField_r_role_cmts				,
		eField_r_pic_name				,
		eField_r_sort_order				,
		eField_r_creation_seed			,
		eField_zr_film_edit_id			,
		eField_zr_person_id				,
		eField_zr_person_role			,
		eField_zr_seq_num				,
		eField_zr_film_id				,
		eField_zr_character_name		,
		eField_zr_role_type				,
		eField_zr_credited_ind			,
		eField_zr_role_cmts				,
		eField_zr_pic_name				,
		eField_zr_sort_order			,
		eField_zr_creation_seed			,
		// ------------------------------
		// title
		// ------------------------------
		eField_t_film_id				,
		eField_t_title_seq				,
		eField_t_title					,
		eField_t_title_sort				,
		eField_t_title_search			,
		eField_t_search_article_ind		,
		eField_t_sort_order				,
		eField_t_used_in_edition_ind	,
		eField_t_creation_seed			,
		eField_zt_film_edit_id			,
		eField_zt_title_seq				,
		eField_zt_film_id				,
		eField_zt_title					,
		eField_zt_title_sort			,
		eField_zt_title_search			,
		eField_zt_search_article_ind	,
		eField_zt_sort_order			,
		eField_zt_creation_seed			,
		// ------------------------------
		// pub
		// ------------------------------
		eField_u_pub_id					,
		eField_u_version_id				,
		eField_u_pub_name				,
		eField_u_pub_name_nocase		,
		eField_u_url					,
		eField_u_official_site			,
		eField_u_wikipedia				,
		eField_u_mod_flags				,
		eField_u_pub_created_tm			,
		eField_u_pub_updated_tm			,
		eField_u_pub_updated_by			,
		eField_u_last_justify			,
		eField_u_pub_verified_tm		,
		eField_u_pub_verified_by		,
		eField_u_verified_version		,
		eField_u_pub_edit_id			,
		eField_u_creation_seed			,
		eField_zu_pub_edit_id			,
		eField_zu_pub_id				,
		eField_zu_request_cd			,
		eField_zu_disposition_cd		,
		eField_zu_proposer_id			,
		eField_zu_proposer_notes		,
		eField_zu_proposed_tm			,
		eField_zu_updated_tm			,
		eField_zu_reviewer_id			,
		eField_zu_reviewer_notes		,
		eField_zu_reviewed_tm			,
		eField_zu_hist_version_id		,
		eField_zu_pub_name				,
		eField_zu_official_site			,
		eField_zu_wikipedia				,
		eField_zu_update_justify		,
		eField_zu_creation_seed			,
		// ------------------------------
		// pic
		// ------------------------------
		eField_p_pic_id					,
		eField_p_version_id				,
		eField_p_sub_version_id			,
		eField_p_pic_name				,
		eField_p_pic_type				,
		eField_p_transforms				,
		eField_p_caption				,
		eField_p_copy_holder			,
		eField_p_copy_year				,
		eField_p_suitability_cd			,
		eField_p_pic_dx					,
		eField_p_pic_dy					,
		eField_p_pic_uploaded_tm		,
		eField_p_pic_uploaded_by		,
		eField_p_pic_edited_tm			,
		eField_p_pic_edited_by			,
		eField_p_pic_verified_tm		,
		eField_p_pic_verified_by		,
		eField_p_verified_version		,
		eField_p_pic_edit_id			,
		eField_p_creation_seed			,
		eField_p_img_treatment			,
		eField_p_rot_degrees			,
		eField_p_rot_degrees_x			,
		eField_p_crop_x1				,
		eField_p_crop_x2				,
		eField_p_crop_y1				,
		eField_p_crop_y2				,
		eField_p_crop_fuzz				,
		eField_p_black_pt				,
		eField_p_white_pt				,
		eField_p_gamma					,
		eField_zp_obj_edit_id			,
		eField_zp_obj_id				,
		eField_zp_obj_type				,
		eField_zp_pic_id				,
		eField_zp_pic_edit_id			,
		eField_zp_request_cd			,
		eField_zp_disposition_cd		,
		eField_zp_proposer_id			,
		eField_zp_proposer_notes		,
		eField_zp_proposed_tm			,
		eField_zp_updated_tm			,
		eField_zp_reviewer_id			,
		eField_zp_reviewer_notes		,
		eField_zp_reviewed_tm			,
		eField_zp_uploaded_pic			,
		eField_zp_hist_version_id		,
		eField_zp_hist_sub_version_id	,
		eField_zp_pic_name				,
		eField_zp_pic_type				,
		eField_zp_transforms			,
		eField_zp_caption				,
		eField_zp_copy_holder			,
		eField_zp_copy_year				,
		eField_zp_suitability_cd		,
		eField_zp_pic_dx				,
		eField_zp_pic_dy				,
		eField_zp_creation_seed			,
		eField_zp_img_treatment			,
		eField_zp_rot_degrees			,
		eField_zp_rot_degrees_x			,
		eField_zp_crop_x1				,
		eField_zp_crop_x2				,
		eField_zp_crop_y1				,
		eField_zp_crop_y2				,
		eField_zp_crop_fuzz				,
		eField_zp_black_pt				,
		eField_zp_white_pt				,
		eField_zp_gamma					,
		// ------------------------------
		// price
		// ------------------------------
		eField_pr_upc					,
		eField_pr_price_00				,
		eField_pr_price_01				,
		eField_pr_price_02				,
		eField_pr_price_03				,
		eField_pr_price_04				,
		eField_pr_price_05				,
		eField_pr_price_06				,
		eField_pr_price_07				,
		eField_pr_price_08				,
		eField_pr_price_09				,
		// ------------------------------
		// my_dvd
		// ------------------------------
		eField_b_user_id				,
		eField_b_dvd_id					,
		eField_b_folder					,
		eField_b_sort_text				,
		eField_b_public_ind				,
		eField_b_genre_overwrite		,
		eField_b_pic_overwrite			,
		eField_b_user_film_rating		,
		eField_b_user_dvd_rating		,
		eField_b_comments				,
		eField_b_owned_dd				,
		eField_b_my_dvd_created_tm		,
		eField_b_my_dvd_updated_tm		,
		eField_b_my_dvd_expire_tm		,
		eField_b2_user_id				,
		eField_b2_dvd_id				,
		eField_b2_last_watched_dd		,
		eField_b2_retailer				,
		eField_b2_price_paid			,
		eField_b2_order_dd				,
		eField_b2_order_number			,
		eField_b2_trade_loan			,
		eField_b2_loaned_to				,
		eField_b2_loan_dd				,
		eField_b2_return_dd				,
		eField_b2_asking_price			,
		eField_b2_custom_1				,
		eField_b2_custom_2				,
		eField_b2_custom_3				,
		eField_b2_custom_4				,
		eField_b2_custom_5				,

		// Special Formatting
		eField_zz_a_director			,
		eField_zz_a_publisher			,
		eField_zz_a_genre				,

		// Count
		eField_total_types
	};
	enum eFormat // select 0 one or more
	{
		eFormat_default					,
		eFormat_dvd_director			,
		eFormat_dvd_publisher			,
		eFormat_dvd_effective_genre		,
		eFormat_dvd_region_mask			,
		eFormat_dvd_genre				,
		eFormat_my_dvd_genre			,
//		eFormat_upc						,
		// Count
		eField_total_formats
	};
	enum eParm // select 0 one or more
	{
		eDbOnEmptyMask			= 0x0000007, // .... .... .... .111
			eDbNullOnEmpty		= 0x0000001, // .... .... .... ...1
			eDbDashOnEmpty		= 0x0000002, // .... .... .... ..1.
			eDbMinus1OnEmpty	= 0x0000003, // .... .... .... ..11
			eDbZeroOnEmpty		= 0x0000004, // .... .... .... .1..
	};
	enum eRegion
	{
		eRegion_0					= 1,
		eRegion_1					= 2,
		eRegion_2					= 4,
		eRegion_3					= 8,
		eRegion_4					= 16,
		eRegion_5					= 32,
		eRegion_6					= 64,
		eRegion_A					= 128,
		eRegion_B					= 256,
		eRegion_C					= 512
	};

// Interface
public:
	friend class CContext;

public:
	static void InitTableRange();
	static int					GetFieldId(unsigned char c1, unsigned char c2, const unsigned char *pFieldAlias, const int pFieldAliasLength);
	static const CStaticStr&	GetLabel(const int pFieldId)		{ return gp_field[pFieldId]._Label; }
	static const CStaticStr&	GetColumn(const int pFieldId)		{ return gp_field[pFieldId]._Column; }
	static int					getDomainId(const int pFieldId)		{ return CField::gp_field[pFieldId]._DomainId; }
	static CDomain::eParm		getSeparator(const int pFieldId)	{ return CDomain::getSeparator(getDomainId(pFieldId)); }
	static CDomain::eParm		getDataType(const int pFieldId)		{ return CDomain::getDataType(getDomainId(pFieldId)); }
	static bool					isDecoded(const int pFieldId)		{ return CDomain::isDecoded(getDomainId(pFieldId)); }
	static CField::eParm		getDbOnEmpty(const int pFieldId)	{ return static_cast<CField::eParm>(CField::gp_field[pFieldId]._Parm & CField::eDbOnEmptyMask); }
	static CDictionary::eType	getDictionary(const int pFieldId)	{ return CDomain::getDictionary(getDomainId(pFieldId)); }

// Private Variables and Structures
private:
	typedef struct {
		CField::eType				_FieldId;				// this is a check that should point back to its own index
		int							_TableId;
		int							_DomainId;
		CStaticStr					_Column;				// database column name
		CStaticStr					_Alias;					// result set column name
		CStaticStr					_Input;					// form input field id
		CStaticStr					_Label;
		CField::eFormat				_Format;
		CStaticStr					_Default;
		unsigned int				_Parm;
		FDeriveField				*_CalcDerived;			// function that initializes derived field
		int							_DerivedFieldId;		// derived field id
	}	t_field;

// Private Member Variables
private:
	static const t_field gp_field[eField_total_types];

#ifdef WIN32TEST
public:
	static int _getFieldId(int pFieldId) { return gp_field[pFieldId]._FieldId; }
#endif	/* WIN32TEST */
};

#endif	/* FIELD_H */

/*
desc dvd;
+------------------+------------------+------+-----+---------+-------+
| Field            | Type             | Null | Key | Default | Extra |
+------------------+------------------+------+-----+---------+-------+
| dvd_id           | int(11)          | NO   | PRI | 0       |       |
| version_id       | int(11)          | NO   |     | 0       |       |
| dvd_title        | varchar(2000)    | NO   |     |         |       |
| dvd_title_nocase | varchar(2000)    | NO   | MUL |         |       |
| film_rel_year    | smallint(6)      | NO   |     | 0       |       |
| director         | varchar(500)     | NO   |     | -       |       |
| director_nocase  | varchar(500)     | NO   |     | -       |       |
| publisher        | varchar(128)     | NO   |     | -       |       |
| publisher_nocase | varchar(128)     | NO   |     | -       |       |
| orig_language    | varchar(32)      | NO   |     | -       |       |
| country          | varchar(32)      | NO   |     | -       |       |
| country_block    | varchar(32)      | NO   |     | -       |       |
| region_mask      | smallint(6)      | NO   |     | 0       |       |
| genre            | mediumint(9)     | NO   |     | 99999   |       |
| lock_mask        | int(10) unsigned | NO   |     | 0       |       |
| media_type       | char(1)          | NO   |     | D       |       |
| num_titles       | smallint(6)      | NO   |     | 1       |       |
| num_disks        | smallint(6)      | NO   |     | 1       |       |
| source           | char(1)          | NO   |     | A       |       |
| rel_status       | char(1)          | NO   |     | -       |       |
| film_rel_dd      | varchar(8)       | NO   |     | -       |       |
| dvd_rel_dd       | varchar(8)       | NO   | MUL | -       |       |
| dvd_oop_dd       | varchar(8)       | NO   |     | -       |       |
| imdb_id          | varchar(500)     | NO   |     | -       |       |
| pic_status       | char(1)          | NO   |     | -       |       |
| pic_name         | varchar(16)      | NO   |     | -       |       |
| pic_count        | smallint(6)      | NO   |     | 0       |       |
| film_rating      | tinyint(4)       | NO   |     | -1      |       |
| dvd_rating       | tinyint(4)       | NO   |     | -1      |       |
| film_votes       | int(11)          | NO   |     | 0       |       |
| dvd_votes        | int(11)          | NO   |     | 0       |       |
| list_price       | decimal(8,2)     | NO   |     | 0.00    |       |
| sku              | varchar(128)     | NO   |     | -       |       |
| upc              | varchar(128)     | NO   |     | -       |       |
| asin             | varchar(16)      | NO   |     | -       |       |
| amz_country      | char(1)          | NO   |     | -       |       |
| best_price       | decimal(8,2)     | NO   |     | 0.00    |       |
| amz_rank         | int(11)          | NO   |     | 9999999 |       |
| dvd_created_tm   | datetime         | NO   | MUL |         |       |
| dvd_updated_tm   | datetime         | NO   |     |         |       |
| dvd_updated_by   | varchar(32)      | NO   |     | -       |       |
| dvd_id_merged    | int(11)          | NO   |     | 0       |       |
| update_justify   | varchar(200)     | NO   |     | -       |       |
| dvd_verified_tm  | datetime         | YES  |     | NULL    |       |
| dvd_verified_by  | varchar(32)      | NO   |     | -       |       |
| verified_version | int(11)          | NO   |     | -1      |       |
| dvd_edit_id      | int(11)          | NO   |     | 0       |       |
| creation_seed    | varchar(36)      | NO   |     | -       |       |
+------------------+------------------+------+-----+---------+-------+

desc my_dvd;
+-------------------+---------------+------+-----+---------+-------+
| Field             | Type          | Null | Key | Default | Extra |
+-------------------+---------------+------+-----+---------+-------+
| user_id           | varchar(32)   | NO   | PRI | -       |       |
| dvd_id            | int(11)       | NO   | PRI | 0       |       |
| folder            | varchar(200)  | NO   |     | -       |       |
| sort_text         | varchar(36)   | NO   |     | -       |       |
| public_ind        | char(1)       | NO   |     | Y       |       |
| genre_overwrite   | mediumint(9)  | NO   |     | 99999   |       |
| pic_overwrite     | varchar(16)   | NO   | MUL | -       |       |
| user_film_rating  | tinyint(4)    | NO   |     | -1      |       |
| user_dvd_rating   | tinyint(4)    | NO   |     | -1      |       |
| comments          | varchar(4000) | YES  |     | NULL    |       |
| owned_dd          | varchar(8)    | NO   |     | -       |       |
| my_dvd_created_tm | datetime      | NO   |     |         |       |
| my_dvd_updated_tm | datetime      | NO   |     |         |       |
| my_dvd_expire_tm  | datetime      | YES  |     | NULL    |       |
+-------------------+---------------+------+-----+---------+-------+

 desc my_dvd_2;
+-----------------+--------------+------+-----+---------+-------+
| Field           | Type         | Null | Key | Default | Extra |
+-----------------+--------------+------+-----+---------+-------+
| user_id         | varchar(32)  | NO   | PRI | -       |       |
| dvd_id          | int(11)      | NO   | PRI | 0       |       |
| last_watched_dd | varchar(8)   | NO   |     | -       |       |
| retailer        | varchar(32)  | NO   |     | -       |       |
| price_paid      | decimal(8,2) | NO   |     | -1.00   |       |
| order_dd        | varchar(8)   | NO   |     | -       |       |
| order_number    | varchar(16)  | NO   |     | -       |       |
| trade_loan      | char(1)      | NO   |     | -       |       |
| loaned_to       | varchar(32)  | NO   |     | -       |       |
| loan_dd         | varchar(8)   | NO   |     | -       |       |
| return_dd       | varchar(8)   | NO   |     | -       |       |
| asking_price    | decimal(8,2) | NO   |     | -1.00   |       |
| custom_1        | varchar(32)  | NO   |     | -       |       |
| custom_2        | varchar(32)  | NO   |     | -       |       |
| custom_3        | varchar(32)  | NO   |     | -       |       |
| custom_4        | varchar(32)  | NO   |     | -       |       |
| custom_5        | varchar(32)  | NO   |     | -       |       |
+-----------------+--------------+------+-----+---------+-------+

SELECT a.dvd_id, a.pic_status, a.pic_name, a.pic_count, b.pic_overwrite, a.dvd_title, a.film_rel_year, b.comments, b.user_film_rating, b.user_dvd_rating, a.genre, b.genre_overwrite, a.region_mask, a.dvd_rel_dd, '' folder, a.media_type, a.source, a.imdb_id, a.asin, a.amz_country, a.list_price, a.director, a.publisher, a.country, a.rel_status, a.best_price FROM my_dvd b JOIN dvd a ON b.dvd_id = a.dvd_id WHERE b.user_id = 'ash' and b.folder = 'owned/hd-dvd' ORDER BY IF(b.sort_text='-',a.dvd_title_nocase,CONCAT('/ ',LOWER(b.sort_text),SUBSTRING(a.dvd_title_nocase,2))), a.film_rel_year, a.director_nocase, a.dvd_id LIMIT 2;
+--------+------------+-----------+-----------+---------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+-----------------------------------------------------------------+------------+-------------+------------+--------------------------------------------------------------------------------------------------------------------+-------------------+---------+------------+------------+
| dvd_id | pic_status | pic_name  | pic_count | pic_overwrite | dvd_title                                                                                                                                                                                                                                                                                                                                                                                                                                       | film_rel_year | comments | user_film_rating | user_dvd_rating | genre | genre_overwrite | region_mask | dvd_rel_dd | folder | media_type | source | imdb_id                                                         | asin       | amz_country | list_price | director                                                                                                           | publisher         | country | rel_status | best_price |
+--------+------------+-----------+-----------+---------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+-----------------------------------------------------------------+------------+-------------+------------+--------------------------------------------------------------------------------------------------------------------+-------------------+---------+------------+------------+
|  85255 | Y          | 085255-d0 |         2 | -             | 12 Monkeys<br />( Twelve Monkeys )<br />+ Hamster Factor and Other Tales of Twelve Monkeys, The (Documentary) (1997)                                                                                                                                                                                                                                                                                                                            |          1995 | -        |               -1 |              -1 | 70250 |           99999 |           1 | 20061024   |        | H          | A      | 0114746 0116479                                                 | B000HT3Q14 | -           |      29.98 | Terry Gilliam,Keith Fulton,Louis Pepe                                                                              | Universal Studios | ,us,    | O          |       0.00 |
|  85905 | Y          | 085905-d0 |         1 | -             | Adventures of Robin Hood, The<br />+ Freddie Rich and His Orchestra (Short) (1938)<br />+ Katnip Kollege (Short) (High Definition) (1938)<br />+ Rabbit Hood (Short) (High Definition) (1949)<br />+ Robin Hood Daffy (Short) (High Definition) (1958)<br />+ Cavalcade of Archery (Short) (1946)<br />+ Cruise of the Zaca (Short) (1952)<br />+ Welcome to Sherwood! The Story of &#39;The Adventures of Robin Hood&#39; (Documentary) (2003) |          1938 | NULL     |               -1 |              -1 | 10400 |           99999 |           1 | 20060926   |        | H          | A      | 0029843 0187021 0030314 0041779 0052139 0350692 0044523 0385330 | B000I0RR76 | -           |      28.98 | Michael Curtiz,William Keighley,Lloyd French,Cal Dalton,Cal Howard,Chuck Jones,Howard Hill,Errol Flynn,Jeff Kurtti | Warner Home Video | ,us,    | O          |       0.00 |
+--------+------------+-----------+-----------+---------------+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+-----------------------------------------------------------------+------------+-------------+------------+--------------------------------------------------------------------------------------------------------------------+-------------------+---------+------------+------------+

<tr id='r_1' class='dvd_row0'><td class='dvd_chk'><input type='checkbox' id='cb_0085255' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0085255' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd20.png' height='22' width='24' alt='Prices not available' /><br /></td><td class='dvd_pic' width='1%'><a id='a_0085255' imgsel='1' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0085255'><img id='zo_0085255' src='http://dv1.us/p0/255/085255-d0.gif' height='90' width='63' alt='' /><br />0085255</a></td><td class='dvd_tit'>12 Monkeys (1995) -- HD DVD<br />( Twelve Monkeys )<br />+ Hamster Factor and Other Tales of Twelve Monkeys, The (Documentary) (1997)<div class='dvd_gen'><a class='dvd_gen' href='http://www.filmaf.edu/search.html?genre=scifi-apocalyptic'>Sci-Fi / Apocalyptic</a></div></td><td class='dvd_imdb'><a class='dvd_amz' href='http://www.filmaf.edu/rt.php?vd=amz0085255' target='amz'>amz</a><br /><a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085255-0' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085255-1' target='imdb'>imdb</a><br />MSRP: 29.98</td><td class='dvd_dir'><a class='dvd_dir' href='http://www.filmaf.edu/gd/terry-gilliam'>Terry Gilliam</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/keith-fulton'>Keith Fulton</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/louis-pepe'>Louis Pepe</a></td><td class='dvd_pub'><a class='dvd_pub' href='http://www.filmaf.edu/search.html?pub=Universal%20Studios'>Universal Studios</a><div class='dvd_ctry'>U.S.</div><div class='dvd_rst'>Out of print</div></td></tr>
<tr id='r_2' class='dvd_row1'><td class='dvd_chk'><input type='checkbox' id='cb_0085905' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0085905' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd20.png' height='22' width='24' alt='Prices not available' /><br /></td><td class='dvd_pic' width='1%'><a id='a_0085905' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0085905'><img id='zo_0085905' src='http://dv1.us/p0/905/085905-d0.gif' height='90' width='63' alt='' /><br />0085905</a></td><td class='dvd_tit'><div id='tf_85905_sav' style='visibility:hidden;position:absolute;top:0;left:0'>Adventures of Robin Hood, The (1938) -- HD DVD<br />+ Freddie Rich and His Orchestra (Short) (1938)<br />+ Katnip Kollege (Short) (High Definition) (1938)<br />+ Rabbit Hood (Short) (High Definition) (1949)<br />+ Robin Hood Daffy (Short) (High Definition) (1958)<br />+ Cavalcade of Archery (Short) (1946)<br />+ Cruise of the Zaca (Short) (1952)<br />+ Welcome to Sherwood! The Story of &#39;The Adventures of Robin Hood&#39; (Documentary) (2003)</div><div id='tf_85905'>Adventures of Robin Hood, The (1938) -- HD DVD<br />+ Freddie Rich and His Orchestra (Short) (1938)<br />+ Katnip Kollege (Short) (High Definition) (1938)<br />+ Rabbit Hood (Short) (High Definition) (1949)<br />+ Robin Hood Daffy (Short) (High Definition) (1958)<br /><a class='dvd_more' href='javascript:void(Dom.flipHidden("tf_85905"))'>more...</a></div><div class='dvd_gen'><a class='dvd_gen' href='http://www.filmaf.edu/search.html?genre=action-epic'>Action-Adventure / Epic</a></div></td><td class='dvd_imdb'><a class='dvd_amz' href='http://www.filmaf.edu/rt.php?vd=amz0085905' target='amz'>amz</a><br /><a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-0' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-1' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-2' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-3' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-4' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-5' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-6' target='imdb'>imdb</a> <a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0085905-7' target='imdb'>imdb</a><br />MSRP: 28.98</td><td class='dvd_dir'><a class='dvd_dir' href='http://www.filmaf.edu/gd/michael-curtiz'>Michael Curtiz</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/william-keighley'>William Keighley</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/lloyd-french'>Lloyd French</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/cal-dalton'>Cal Dalton</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/cal-howard'>Cal Howard</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/chuck-jones'>Chuck Jones</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/howard-hill'>Howard Hill</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/errol-flynn'>Errol Flynn</a>,<br /><a class='dvd_dir' href='http://www.filmaf.edu/gd/jeff-kurtti'>Jeff Kurtti</a></td><td class='dvd_pub'><a class='dvd_pub' href='http://www.filmaf.edu/search.html?pub=Warner%20Home%20Video'>Warner Home Video</a><div class='dvd_ctry'>U.S.</div><div class='dvd_rst'>Out of print</div></td></tr>

 SELECT a.dvd_id, a.pic_status, a.pic_name, a.pic_count, b.pic_overwrite, a.dvd_title, a.film_rel_year, b.comments, b.user_film_rating, b.user_dvd_rating, a.genre, b.genre_overwrite, a.region_mask, a.dvd_rel_dd, '' folder, a.media_type, a.source, a.imdb_id, a.asin, a.amz_country, a.list_price, a.director, a.publisher, a.country, a.rel_status, a.best_price FROM my_dvd b JOIN dvd a ON b.dvd_id = a.dvd_id WHERE b.user_id = 'ash' and b.folder = 'owned' ORDER BY IF(b.sort_text='-',a.dvd_title_nocase,CONCAT('/ ',LOWER(b.sort_text),SUBSTRING(a.dvd_title_nocase,2))), a.film_rel_year, a.director_nocase, a.dvd_id LIMIT 4;
+--------+------------+-----------+-----------+---------------+-----------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+---------+------------+-------------+------------+----------------------+---------------------------+---------+------------+------------+
| dvd_id | pic_status | pic_name  | pic_count | pic_overwrite | dvd_title                                                 | film_rel_year | comments | user_film_rating | user_dvd_rating | genre | genre_overwrite | region_mask | dvd_rel_dd | folder | media_type | source | imdb_id | asin       | amz_country | list_price | director             | publisher                 | country | rel_status | best_price |
+--------+------------+-----------+-----------+---------------+-----------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+---------+------------+-------------+------------+----------------------+---------------------------+---------+------------+------------+
|  35643 | Y          | 035643-d0 |         1 | -             | Auberge espagnole, L&#39;<br />( Spanish Apartment, The ) |          2002 | -        |               -1 |              -1 | 20999 |           99999 |           2 | 20031223   |        | D          | A      | 0283900 | B0000C9JFO | -           |       9.98 | Cédric Klapisch     | 20th Century Fox          | ,us,    | C          |       6.95 |
|  47121 | Y          | 047121-d0 |         1 | -             | Balance, La<br />( Nark, The )                            |          1982 | -        |               -1 |              -1 | 28150 |           99999 |           2 | 20040727   |        | D          | A      | 0083611 | B00026L754 | -           |      19.95 | Bob Swaim            | Home Vision Entertainment | ,us,    | C          |      15.94 |
|  23797 | Y          | 023797-d0 |         3 | -             | Barton Fink                                               |          1991 | NULL     |               -1 |              -1 | 20100 |           99999 |           2 | 20030520   |        | D          | A      | 0101410 | B00008RH3J | -           |       9.98 | Joel Coen,Ethan Coen | 20th Century Fox          | ,us,    | C          |       6.95 |
|  22097 | Y          | 022097-d0 |         1 | -             | Basquiat                                                  |          1996 | -        |               -1 |              -1 | 28200 |           99999 |           2 | 20020903   |        | D          | A      | 0115632 | B000065V3Y | -           |      19.99 | Julian Schnabel      | Miramax,Buena Vista       | ,us,    | C          |      16.88 |
+--------+------------+-----------+-----------+---------------+-----------------------------------------------------------+---------------+----------+------------------+-----------------+-------+-----------------+-------------+------------+--------+------------+--------+---------+------------+-------------+------------+----------------------+---------------------------+---------+------------+------------+

<tr id='r_4' class='dvd_row1'><td class='dvd_chk'><input type='checkbox' id='cb_0022097' onclick='DvdList.check(this);' /><br /><img src='http://dv1.us/d1/00/bc00.png' id='ic_0022097' height='22' width='24' alt='Add or remove from cart' /><br /><img src='http://dv1.us/d1/00/bd00.png' id='id_0022097' height='22' width='24' alt='Compare prices' /><br /></td><td class='dvd_pic' width='1%'><a id='a_0022097' class='dvd_pic' href='http://www.filmaf.edu/price-one.html?dvd=0022097'><img id='zo_0022097' src='http://dv1.us/p0/097/022097-d0.gif' height='90' width='63' alt='' /><br />0022097</a></td><td class='dvd_tit'>Basquiat (1996)<div class='dvd_gen'><a class='dvd_gen' href='http://www.filmaf.edu/search.html?genre=drama-docudrama'>Drama / Docudrama</a></div></td><td class='dvd_imdb'><a class='dvd_amz' href='http://www.filmaf.edu/rt.php?vd=amz0022097' target='amz'>amz</a><br /><a class='dvd_imdb' href='http://www.filmaf.edu/rt.php?vd=imd0022097-0' target='imdb'>imdb</a><br />MSRP: 19.99</td><td class='dvd_dir'><a class='dvd_dir' href='http://www.filmaf.edu/gd/julian-schnabel'>Julian Schnabel</a></td><td class='dvd_pub'><a class='dvd_pub' href='http://www.filmaf.edu/search.html?pub=Miramax'>Miramax</a>,<br /><a class='dvd_pub' href='http://www.filmaf.edu/search.html?pub=Buena%20Vista'>Buena Vista</a><div class='dvd_ctry'>U.S.</div></td></tr>
*/
