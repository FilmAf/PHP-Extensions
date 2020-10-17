/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_VFIELD_C_H
#define DVDAF_VFIELD_C_H

/*
 *	To add a field:
 *
 *	1) Add it to the typedef enum m_field ("vfield-c.h")
 *	2) Add it to gp_field[] ("field-globals.h")
 *
 */

/* ========================================================================== */

typedef enum {
	c_field_a_dvd_id				,
	c_field_a_version_id			,
	c_field_a_dvd_title				,
	c_field_a_dvd_title_nocase		,
	c_field_a_film_rel_year			,
	c_field_a_director				,
	c_field_a_director_nocase		,
	c_field_a_publisher				,
	c_field_a_publisher_nocase		,
	c_field_a_orig_language			,
	c_field_a_country				,
	c_field_a_country_block			,
	c_field_a_region_mask			,
	c_field_a_genre					,
	c_field_a_lock_mask				,
	c_field_a_media_type			,
	c_field_a_num_titles			,
	c_field_a_num_disks				,
	c_field_a_source				,
	c_field_a_rel_status			,
	c_field_a_film_rel_dd			,
	c_field_a_dvd_rel_dd			,
	c_field_a_dvd_oop_dd			,
	c_field_a_imdb_id				,
	c_field_a_pic_status			,
	c_field_a_pic_name				,
	c_field_a_pic_count				,
	c_field_a_film_rating			,
	c_field_a_dvd_rating			,
	c_field_a_film_votes			,
	c_field_a_dvd_votes				,
	c_field_a_list_price			,
	c_field_a_sku					,
	c_field_a_upc					,
	c_field_a_asin					,
	c_field_a_amz_country			,
	c_field_a_best_price			,
	c_field_a_dvd_created_tm		,
	c_field_a_dvd_updated_tm		,
	c_field_a_dvd_updated_by		,
	c_field_a_dvd_id_merged			,
	c_field_a_last_justify			,
	c_field_a_dvd_verified_by		,
	c_field_a_dvd_verified_tm		,
	c_field_a_verified_version		,

	c_field_w_user_id				,
	c_field_w_status_cd				,
	c_field_w_expire_dd				,
	c_field_w_expire_reason			,
	c_field_w_user_name				,
	c_field_w_user_title			,
	c_field_w_option_bits1			,
	c_field_w_option_bits2			,
	c_field_w_option_bits3			,
	c_field_w_page_size				,
	c_field_w_password_hash			,
	c_field_w_password_public		,
	c_field_w_retailer_id			,
	c_field_w_agree_accept_dt		,
	c_field_w_num_edits				,
	c_field_w_num_new				,
	c_field_w_num_reviews			,
	c_field_w_num_posts				,
	c_field_w_user_group			,
	c_field_w_group_begin_dt		,
	c_field_w_group_end_dt			,
	c_field_w_font_screen			,
	c_field_w_font_screen_small		,
	c_field_w_font_printer			,
	c_field_w_font_printer_small	,
	c_field_w_updated_tm			,
	c_field_w_created_dt			,

	c_field_e_user_id				,
	c_field_e_folder_id				,
	c_field_e_folder_name			,
	c_field_e_folder_level			,
	c_field_e_parent_id				,
	c_field_e_view_folder_id		,
	c_field_e_view_criteria			,
	c_field_e_title					,
	c_field_e_homepage				,
	c_field_e_description			,
	c_field_e_keywords				,
	c_field_e_home_alone			,
	c_field_e_report_name			,
	c_field_e_template				,
	c_field_e_title_bits			,
	c_field_e_allow_comment			,
	c_field_e_num_views				,
	c_field_e_votes_folder			,
	c_field_e_public_ind			,
	c_field_e_synchronize_ind		,
	c_field_e_sort_order			,
	c_field_e_created_dt			,
	c_field_e_updated_tm			,

	c_field_b_user_id				,
	c_field_b_dvd_id				,
	c_field_b_folder				,
	c_field_b_sort_text				,
	c_field_b_public_ind			,
	c_field_b_genre_overwrite		,
	c_field_b_pic_overwrite			,
	c_field_b_user_film_rating		,
	c_field_b_user_dvd_rating		,
	c_field_b_comments				,
	c_field_b_owned_dd				,
	c_field_b_my_dvd_created_tm		,
	c_field_b_my_dvd_updated_tm		,
	c_field_b_my_dvd_expire_tm		,

	c_field_b2_user_id				,
	c_field_b2_dvd_id				,
	c_field_b2_last_watched_dd		,
	c_field_b2_retailer				,
	c_field_b2_price_paid			,
	c_field_b2_order_dd				,
	c_field_b2_order_number			,
	c_field_b2_trade_loan			,
	c_field_b2_loaned_to			,
	c_field_b2_loan_dd				,
	c_field_b2_return_dd			,
	c_field_b2_asking_price			,
	c_field_b2_custom_1				,
	c_field_b2_custom_2				,
	c_field_b2_custom_3				,
	c_field_b2_custom_4				,
	c_field_b2_custom_5				,

	c_field_p_pic_name				,
	c_field_p_version_id			,
	c_field_p_sub_version_id		,
	c_field_p_pic_type				,
	c_field_p_transforms			,
	c_field_p_caption				,
	c_field_p_copy_holder			,
	c_field_p_copy_year				,
	c_field_p_suitability_cd		,
	c_field_p_pic_dx				,
	c_field_p_pic_dy				,
	c_field_p_pic_uploaded_tm		,
	c_field_p_pic_uploaded_by		,
	c_field_p_pic_edited_tm			,
	c_field_p_pic_edited_by			,
	c_field_p_pic_verified_tm		,
	c_field_p_pic_verified_by		,
	c_field_p_verified_version		,
	c_field_p_creation_seed			,
	c_field_p_img_treatment			,
	c_field_p_rot_degrees			,
	c_field_p_rot_degrees_x			,
	c_field_p_crop_x1				,
	c_field_p_crop_x2				,
	c_field_p_crop_y1				,
	c_field_p_crop_y2				,
	c_field_p_crop_fuzz				,
	c_field_p_black_pt				,
	c_field_p_white_pt				,
	c_field_p_gamma					,

	c_field_za_edit_id				,
	c_field_za_dvd_id				,
	c_field_za_request_cd			,
	c_field_za_disposition_cd		,
	c_field_za_proposer_id			,
	c_field_za_proposer_notes		,
	c_field_za_proposed_tm			,
	c_field_za_updated_tm			,
	c_field_za_reviewer_id			,
	c_field_za_reviewer_notes		,
	c_field_za_reviewed_tm			,
//	c_field_za_pic_filename			,
	c_field_za_hist_version_id		,
	c_field_za_dvd_title			,
	c_field_za_film_rel_year		,
	c_field_za_director				,
	c_field_za_publisher			,
	c_field_za_orig_language		,
	c_field_za_country				,
	c_field_za_region_mask			,
	c_field_za_genre				,
	c_field_za_media_type			,
	c_field_za_num_titles			,
	c_field_za_num_disks			,
	c_field_za_source			,
	c_field_za_rel_status			,
	c_field_za_film_rel_dd			,
	c_field_za_dvd_rel_dd			,
	c_field_za_dvd_oop_dd			,
	c_field_za_imdb_id				,
	c_field_za_list_price			,
	c_field_za_sku					,
	c_field_za_upc					,
	c_field_za_asin					,
	c_field_za_amz_country			,
	c_field_za_update_justify		,

	c_field_zp_pic_edit_id			,
	c_field_zp_pic_name				,
	c_field_zp_request_cd			,
	c_field_zp_disposition_cd		,
	c_field_zp_proposer_id			,
	c_field_zp_proposer_notes		,
	c_field_zp_proposed_tm			,
	c_field_zp_updated_tm			,
	c_field_zp_reviewer_id			,
	c_field_zp_reviewer_notes		,
	c_field_zp_reviewed_tm			,
	c_field_zp_uploaded_pic			,
	c_field_zp_hist_version_id		,
	c_field_zp_hist_subversion_id	,
	c_field_zp_pic_type				,
	c_field_zp_transforms			,
	c_field_zp_caption				,
	c_field_zp_copy_holder			,
	c_field_zp_copy_year			,
	c_field_zp_suitability_cd		,
	c_field_zp_pic_dx				,
	c_field_zp_pic_dy				,
	c_field_zp_creation_seed		,
	c_field_zp_img_treatment		,
	c_field_zp_rot_degrees			,
	c_field_zp_rot_degrees_x		,
	c_field_zp_crop_x1				,
	c_field_zp_crop_x2				,
	c_field_zp_crop_y1				,
	c_field_zp_crop_y2				,
	c_field_zp_crop_fuzz			,
	c_field_zp_black_pt				,
	c_field_zp_white_pt				,
	c_field_zp_gamma				,

	c_field_pr_upc					,
	c_field_pr_price_00				,
	c_field_pr_price_01				,
	c_field_pr_price_02				,
	c_field_pr_price_03				,
	c_field_pr_price_04				,
	c_field_pr_price_05				,
	c_field_pr_price_06				,
	c_field_pr_price_07				,
	c_field_pr_price_08				,
	c_field_pr_price_09				,

	c_field_zz_check				,
	c_field_zz_dvd_publisher		,
//	c_field_zz_expire_dd			,
	c_field_zz_links				,
	c_field_zz_med_pic				,
	c_field_zz_pda_pic				,
	c_field_zz_row_number			,
	c_field_zz_screening			,
	c_field_zz_small_pic			,
	c_field_zz_text					,
	c_field_zz_title				,
	c_field_zz_title_2				,
	c_field_zz_cart					,
	c_field_zz_price_comparison		,
	c_field_zz_best_price			,

	c_tot_field						,
	c_last_table_field				= c_field_zz_check
} m_field;

typedef enum {
	c_table_no_table			,
	c_table_dvd					,	// c_field_a_
	c_table_dvdaf_user			,	// c_field_w_
	c_table_folder				,	// c_field_e_
	c_table_my_dvd				,	// c_field_b_
	c_table_my_dvd2				,	// c_field_b2_
	c_table_pic					,	// c_field_p_
	c_table_dvd_submit			,	// c_field_za_
	c_table_pic_submit			,	// c_field_zp_
	c_table_price				,	// c_field_pr_
	c_tot_table						// used for certain static buffers must be at least gn_table_count
} m_table;

typedef enum {
	c_region_0					= 1,
	c_region_1					= 2,
	c_region_2					= 4,
	c_region_3					= 8,
	c_region_4					= 16,
	c_region_5					= 32,
	c_region_6					= 64,
	c_region_A					= 128,
	c_region_B					= 256,
	c_region_C					= 512,
	c_tot_region
} m_region;

/* ========================================================================== */

// Used by t_field.uparm (special formatting)
#define FIELD_TYPE_MASK				0x000000FF	// .... .... 1111 1111 [0..255]

// Used by t_field.uparm (minimal additional data requirements for dvdaf_getbrowserfield)
#define FIELD_NEED_DVD_ID			0x00000100	// .... ...1 .... ....
#define FIELD_NEED_ROW_NO			0x00000200	// .... ..1. .... ....
#define FIELD_NEED_VIEW_USER		0x00000400	// .... .1.. .... ....

// Used by t_field.uparm (how to relate the field to database columns)
#define FIELD_DB_MASK				0x00007000	// .111 .... .... ....
#define FIELD_DB_NAME				0x00000000	// .... .... .... .... // 1 database field, same as t_field.p_column
#define FIELD_DB_ALIAS				0x00001000	// ...1 .... .... .... // database field name aliased by (t_field.c_table1 + t_field.c_table2 + "_" + t_field.p_column)
#define FIELD_COMPOSED				0x00002000	// ..1. .... .... .... // composed of fileds as specified in a t_field_type[] list in t_field.pn_field_ids

// Used by t_field.uparm (user definable labels -- to be implemented)
#define FIELD_CUSTOM				0x00008000	// 1... .... .... ....

// Used by t_field.uparm (data validation and decoding)
#define FIELD_DATATYPE_MASK			0x00070000	// .... .... .... .111
#define FIELD__CHAR					0x00000000	// .... .... .... .000
#define FIELD__INT					0x00010000	// .... .... .... .001
#define FIELD__DOUBLE				0x00020000	// .... .... .... .010
#define FIELD__DATE					0x00030000	// .... .... .... .011
#define FIELD__TIME					0x00040000	// .... .... .... .100
#define FIELD_DECODE				0x00080000	// .... .... .... 1...

// Used by t_field.uparm (data validation and presentation)
#define FIELD_DB_ON_EMPTY_MASK		0x00700000	// .... .... .111 ....
#define FIELD_DB_NULL_ON_EMPTY		0x00100000	// .... .... ...1 ....
#define FIELD_DB_DASH_ON_EMPTY		0x00200000	// .... .... ..1. ....
#define FIELD_DB_MINUS1_ON_EMPTY	0x00300000	// .... .... ..11 ....
#define FIELD_DB_ZERO_ON_EMPTY		0x00400000	// .... .... .1.. ....

#define FIELD_ALLOW_ZERO_DD			0x00800000	// .... .... 1... ....
#define FIELD_ALLOW_ZERO_MMDD		0x01000000	// .... ...1 .... ....

#define FIELD_TAB_SEPATED			0x02000000	// .... ..1. .... ....
#define FIELD_COMMA_SEPATED			0x04000000	// .... .1.. .... ....
#define FIELD_SPACE_SEPATED			0x08000000	// .... 1... .... ....

/* ========================================================================== */

// formatting styles (1st LOWORD)
#define DVDAF1_STYLE_MASK			0x00000007	// .... .... .... .111	// defines css family to be applied to field or label
#define DVDAF1_STYLE_SCREEN			0x00000000	// .... .... .... ....	// use css for normal screen output
#define DVDAF1_STYLE_PRINTER		0x00000001	// .... .... .... ...1	// use css for for printing output
#define DVDAF1_STYLE_ONE			0x00000002	// .... .... .... ..1.	// use css for one title per page output
#define DVDAF1_STYLE_NONE			0x00000003	// .... .... .... ..11	// do not use css for this field or label

#define DVDAF1_SFIELD_MASK			0x00000038	// .... .... ..11 1...
#define DVDAF1_SFIELD_LOWKEY		0x00000008	// .... .... .... 1...
#define DVDAF1_SFIELD_COMMENTS		0x00000010	// .... .... ...1 ....
#define DVDAF1_SFIELD_HIGHLIGHT		0x00000018	// .... .... ...1 1...
#define DVDAF1_SFIELD_NONE			0x00000038	// .... .... ..11 1...

#define DVDAF1_SSUBFL_MASK			0x000001C0	// .... ...1 11.. ....
#define DVDAF1_SSUBFL_NONE			0x000001C0	// .... ...1 11.. ....

#define DVDAF1_SLABEL_MASK			0x00000E00	// .... 111. .... ....
#define DVDAF1_SLABEL_NONE			0x00000E00	// .... 111. .... ....

#define DVDAF1_SLINK_MASK			0x00007000	// .111 .... .... ....
#define DVDAF1_SLINK_VENDOR			0x00001000	// ...1 .... .... ....
#define DVDAF1_SLINK_PICTURE		0x00002000	// ..1. .... .... ....
#define DVDAF1_SLINK_NONE			0x00004000	// ..11 .... .... ....
#define DVDAF1_NOT_VISIBLE			0x00008000	// 1... .... .... ....

// formatting styles (1st HIWORD)
#define DVDAF1_TABLE_TD				0x00010000	// .... .... .... ...1	// field is wrapped in <td></td>
#define DVDAF1_TABLE_TR				0x00020000	// .... .... .... ..1.	// field is wrapped in <tr></tr>
#define DVDAF1_TABLE_NOWRAP			0x00040000	// .... .... .... .1..	// defines " nowrap='nowrap'" in a <td> element
#define DVDAF1_FIELD_NAME			0x00080000	// .... .... .... 1...	// label is present
#define DVDAF1_FIELD_NAME_TD		0x00100000	// .... .... ...1 ....	// label is wrapped in a second set of <td></td> (requires DVDAF1_TABLE_TD)

#define DVDAF1_HOZ_MASK				0x00E00000	// .... .... 111. ....
#define DVDAF1_HOZ_LEFT				0x00200000	// .... .... 001. ....
#define DVDAF1_HOZ_CENTER			0x00400000	// .... .... 010. ....
#define DVDAF1_HOZ_RIGHT			0x00600000	// .... .... 011. ....
#define DVDAF1_HOZ_JUSTIFY			0x00800000	// .... .... 100. ....

#define DVDAF1_VER_MASK				0x03000000	// .... ..11 .... ....
#define DVDAF1_VER_TOP				0x01000000	// .... ..01 .... ....
#define DVDAF1_VER_MIDDLE			0x02000000	// .... ..10 .... ....
#define DVDAF1_VER_BOTTOM			0x03000000	// .... ..11 .... ....

#define DVDAF1_SMALL				0x04000000	// .... .1.. .... ....
#define DVDAF1_BOLD					0x08000000	// .... 1... .... ....
#define DVDAF1_LABEL_BR				0x10000000	// ...1 .... .... ....
#define DVDAF1_FIELD_BR				0x20000000	// ..1. .... .... ....
#define DVDAF1_EXTRA_BR				0x40000000	// .1.. .... .... ....
#define DVDAF1_ALLOW_2BR			0x80000000	// 1... .... .... ....

// formatting styles (2nd LOWORD)
#define DVDAF2_WIDTH_MASK			0x000003FF	// .... ..11 1111 1111	// [0..1023] values
#define DVDAF2_WIDTH_1				0x00000001	// .... .... .... ...1	// multiplier
#define DVDAF2_WIDTH_PERC			0x00000400	// .... .1.. .... ....

#define DVDAF2_COLSPAN_MASK			0x0000F800	// 1111 1... .... ....	// [1..32] defines " colspan='X'" in a <td> element
#define DVDAF2_COLSPAN_1			0x00000800	// .... 1... .... ....	// defines " colspan='X'" in a <td> element

// formatting styles (2nd HIWORD)
#define DVDAF2_ROWSPAN_MASK			0x000F0000	// .... .... .... 1111	// [1..16] defines " rowspan='X'" in a <td> element
#define DVDAF2_ROWSPAN_1			0x00010000	// .... .... .... ...1	// defines " rowspan='X'" in a <td> element

#define DVDAF2_TABLE_TD_BEG			0x00100000	// .... .... ...1 ....	// field begins a column <td>, but does not close it </td>
#define DVDAF2_TABLE_TD_END			0x00200000	// .... .... ..1. ....	// field closes a column </td>
#define DVDAF2_TABLE_TR_BEG			0x00400000	// .... .... .1.. ....	// field begins a row <tr>, but does not close it </tr> (<td> will need to be specified separatly)
#define DVDAF2_TABLE_TR_END			0x00800000	// .... .... 1... ....	// field closes a row </tr> (</td> will need to be specified separatly)
#define DVDAF2_TRUNC_PDA			0x01000000	// .... ...1 .... ....	// truncate title, director and studio for PDA output

#define DVDAF2_SEPARATOR_MARK		0x02000000	// .... ..1. .... ....
#define DVDAF2_SEPARATOR_BR			0x00000000	// .... .... .... ....
#define DVDAF2_SEPARATOR_COMMA		0x02000000	// .... ..1. .... ....
// #define							0x04000000	// .... .1.. .... ....
#define DVDAF2_SORT_ONLY			0x08000000	// .... 1... .... ....
#define DVDAF2_CONTRAST_ROW			0x10000000	// ...1 .... .... ....
#define DVDAF2_TABLE_HEADER			0x20000000	// ..1. .... .... ....
#define DVDAF2_ALLOW_EXTRA			0x40000000	// .1.. .... .... ....
#define DVDAF2_ECHO					0x80000000	// 1... .... .... .... 

// formatting styles (3rd LOWORD)
#define DVDAF3_TOOLTIP				0x00000001	// .... .... .... ...1 
#define DVDAF3_LINK					0x00000002	// .... .... .... ..1. 
#define DVDAF3_NO_STYLE_TR			0x00000004	// .... .... .... .1..	// do not use css style in <tr> if one exists
#define DVDAF3_NO_STYLE_TD			0x00000008	// .... .... .... 1...	// do not use css style in <td> if one exists (would still use it for a <td> specific to a label)
#define DVDAF3_NO_STYLE				0x00000010	// .... .... ...1 ....	// do not use css style in <span> if one exists
#define DVDAF3_NO_STYLE_LB			0x00000020	// .... .... ..1. ....
#define DVDAF3_POSSESSIVE			0x00000040	// .... .... .1.. ....
#define DVDAF3_NBSP2_ON_EMPTY		0x00000080	// .... .... 1... ....	// &nbsp; for label and value when empty
#define DVDAF3_OPTION_MASK			0x00000F00	// .... 1111 .... ....
#define DVDAF3_OPTION_1				0x00000100	// .... ...1 .... ....
#define DVDAF3_OPTION_2				0x00000200	// .... ...1 .... ....
#define DVDAF3_SHOW_RELEASE_DT		0x00001000	// ...1 .... .... ....
#define DVDAF3_NO_COMMENT			0x00002000	// ..1. .... .... ....
#define DVDAF3_EBAY_LINK			0x00004000	// .1.. .... .... ....
#define DVDAF3_NO_UPC_ADD			0x00008000	// 1... .... .... ....

// formatting styles (3rd HIWORD)
#define DVDAF3_TR_ROW_ID			0x00010000	// .... .... .... ...1
#define DVDAF3_NOTHING_ON_EMPTY		0x00020000	// .... .... .... ..1.	// 	no output for get_browser_field on empty
#define DVDAF3_INPUT				0x00040000	// .... .... .... .1..
#define DVDAF3_ESCAPE_NL			0x00080000	// .... .... .... 1...
#define DVDAF3_STAR_MEMBER			0x00100000	// .... .... ...1 ....
#define DVDAF3_NO_INPUT				0x00200000	// .... .... ..1. ....
#define DVDAF3_HIRES				0x00400000	// .... .... .1.. ....
#define DVDAF3_NBSP_ON_EMPTY		0x00800000	// .... .... 1... ....	// &nbsp; for value when empty
#define DVDAF3_HELPER				0x01000000	// .... ...1 .... ....
#define DVDAF3_TESTER				0x02000000	// .... ..1. .... ....
#define DVDAF3_SPIN_MASK			0x0C000000	// .... 11.. .... ....
#define DVDAF3_SPIN_1				0x04000000	// .... 01.. .... ....
#define DVDAF3_SPIN_2				0x08000000	// .... 10.. .... ....
#define DVDAF3_SPIN_3				0x0C000000	// .... 11.. .... ....
#define DVDAF3_SPIN_4_pt1			0x00000000	// .... 00.. .... ....
#define DVDAF3_SPIN_5_pt1			0x04000000	// .... 01.. .... ....
#define DVDAF3_DEFAULT				0x10000000	// ...1 .... .... ....
#define DVDAF3_EXPLAIN				0x20000000	// ..1. .... .... ....
#define DVDAF3_CMP_X				0x40000000	// .1.. .... .... ....
#define DVDAF3_SKIP_OUT_OF_PRINT	0x80000000	// 1... .... .... ....

// formatting styles (4rd HIWORD + LOWORD) may reuse definitions if not inconflict with price comparison
#define DVDAF_MAX_VENDORS			20			// .... .... .... 1111 1111 1111 1111 1111 (0x003FFFFF)
#define DVDAF4_VENDOR_MASK			0x000FFFFF	// .... .... .... 1111
#define DVDAF4_VENDOR_1				0x00000001	// .... .... .... ...1
#define DVDAF4_BEST_PRICE_MASK		0x01F00000	// .... ...1 1111 ....
#define DVDAF4_BEST_PRICE_1			0x00100000	// .... .... ...1 .... 
#define DVDAF4_SEL_VENDOR_MASK		0x3E000000	// ..11 111. .... ....
#define DVDAF4_SEL_VENDOR_1			0x02000000	// .... ..1. .... .... 
#define DVDAF4_ZERO_DVD_ID_OK		0x40000000	// .1.. .... .... .... 
#define DVDAF4_CB_PROPAGATE			0x80000000	// 1... .... .... .... 

// formatting styles (5th LOWORD)
#define DVDAF5_TESTER_2				0x00000001	// .... .... .... ...1
#define DVDAF5_PROPOSED				0x00000002	// .... .... .... ..1.
#define DVDAF5_TEXT_ONLY			0x00000004	// .... .... .... .1..
#define DVDAF5_TABLE_FIELD			0x00000008	// .... .... .... 1...
#define DVDAF5_SPIN_MASK			0x00000030	// .... .... ..11 ....
#define DVDAF5_SPIN_MASK_DIV		0x00000010	// .... .... ...1 ....
#define DVDAF5_SPIN_4_pt2			0x00000010	// .... .... ...1 ....
#define DVDAF5_SPIN_5_pt2			0x00000020	// .... .... ..1. ....
#define DVDAF5_EXPAND_TITLE			0x00000010	// .... .... .1.. ....


/* ========================================================================== */

#endif	/* DVDAF_VFIELD_C_H */
