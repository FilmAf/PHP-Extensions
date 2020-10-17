#ifndef TBL_H
#define TBL_H

#include "StaticStr.h"

class CTbl
{
// Constructors and Destructor
//public:
//	CTbl(void);
//	virtual ~CTbl(void);

// Enums
public:
	enum eType
	{
		eTable_none				,
		eTable_dvd				,
		eTable_dvd_submit		,
		eTable_film				,
		eTable_film_submit		,
		eTable_edition			,
		eTable_edition_submit	,
		eTable_edpub			,
		eTable_edpub_submit		,
		eTable_eddir			,
		eTable_eddir_submit		,
		eTable_person			,
		eTable_person_submit	,
		eTable_role				,
		eTable_role_submit		,
		eTable_title			,
		eTable_title_submit		,
		eTable_pub				,
		eTable_pub_submit		,
		eTable_pic				,
		eTable_pic_submit		,
		eTable_price			,
		eTable_my_dvd			,
		eTable_my_dvd_2			,
		// Count
		eTable_total_types		,
		// Aliases
		eTable_zz			= eTable_none			,
		eTable_a			= eTable_dvd			,
		eTable_za			= eTable_dvd_submit		,
		eTable_f			= eTable_film			,
		eTable_zf			= eTable_film_submit	,
		eTable_e			= eTable_edition		,
		eTable_ze			= eTable_edition_submit	,
		eTable_v			= eTable_edpub			,
		eTable_zv			= eTable_edpub_submit	,
		eTable_d			= eTable_eddir			,
		eTable_zd			= eTable_eddir_submit	,
		eTable_c			= eTable_person			,
		eTable_zc			= eTable_person_submit	,
		eTable_r			= eTable_role			,
		eTable_zr			= eTable_role_submit	,
		eTable_t			= eTable_title			,
		eTable_zt			= eTable_title_submit	,
		eTable_u			= eTable_pub			,
		eTable_zu			= eTable_pub_submit		,
		eTable_p			= eTable_pic			,
		eTable_zp			= eTable_pic_submit		,
		eTable_pr			= eTable_price			,
		eTable_b			= eTable_my_dvd			,
		eTable_b2			= eTable_my_dvd_2
	};

// Private Variables and Structures
private:
	typedef struct {
		int				_TableId;			// this is a check that should point back to its own index
		CStaticStr		_Alias;
		CStaticStr		_Table;
		int				_FirstField;		// CField::eFieldType
		int				_LastField;			// CField::eFieldType
	}	t_table;

	static t_table gp_table[eTable_total_types];

// Interface
public:
	friend class CField;

public:
	static int GetTableId(unsigned char c1, unsigned char c2);
};

/* ========================================= *\
	Table aliases
\* ========================================= */

#define TBL_none				"zz"
#define TBL_dvd					"a"
#define TBL_dvd_submit			"za"
#define TBL_film				"f"
#define TBL_film_submit			"zf"
#define TBL_edition				"e"
#define TBL_edition_submit		"ze"
#define TBL_edpub				"v"
#define TBL_edpub_submit		"zv"
#define TBL_eddir				"d"
#define TBL_eddir_submit		"zd"
#define TBL_person				"c"
#define TBL_person_submit		"zc"
#define TBL_role				"r"
#define TBL_role_submit			"zr"
#define TBL_title				"t"
#define TBL_title_submit		"zt"
#define TBL_pub					"u"
#define TBL_pub_submit			"zu"
#define TBL_pic					"p"
#define TBL_pic_submit			"zp"
#define TBL_price				"pr"
#define TBL_my_dvd				"b"
#define TBL_my_dvd_2			"b2"

#endif	/* TBL_H */
