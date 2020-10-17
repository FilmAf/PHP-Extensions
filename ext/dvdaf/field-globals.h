/* ---------------------------------------------------------------------------- *\
 *  Film Aficionado is public domain software. Promotional material images,
 *  if present, are copyrighted by the respective copyright owners and should
 *  only be used under the provisions dictated by those copyright holders.
 *  There are no warranties expressed on implied.
\* ---------------------------------------------------------------------------- */

#ifndef DVDAF_FIELD_GLOBALS_H
#define DVDAF_FIELD_GLOBALS_H

/* ========================================================================================= *\
	GLOBAL VARIABLES
\* ========================================================================================= */

/* ========================================= *\
	CSS constants
\* ========================================= */

#define FC(a)				 {" class='" #a "'",sizeof(" class='" #a "'")-1}

const t_string
gp_field_class[3][TOT_CSS] = {
							// CSS_TABLE					a
							// CSS_HEADER_TR				b
							// CSS_HEADER_TD				c
							// CSS_HEADER					d
							// CSS_FIELD_TR					e
							// CSS_FIELD_TR_CONTRAST		f
							// CSS_FIELD_TD					g
							// CSS_FIELD					h
							// CSS_LABEL_TD					i
							// CSS_LABEL					j
							// CSS_GENERIC_LINK				k
							// CSS_COMMENTS					l
							// CSS_DIRECTOR					m
							// CSS_PUBLISHER				n
							// CSS_COUNTRY					o
							// CSS_GENRE					p
							// CSS_IMDB						q
							// CSS_VENDOR					r
							// CSS_TITLE_RELEASE_DATE		s
							// CSS_TITLE_RECENT_RELEASE		t
							// CSS_TITLE_PIC_IS_POSTER		u
							// CSS_PRICES					v
							// CSS_EBAY_SEARCH				x
							// CSS_DVD_PIC_LINK				y
							// CSS_HIGHLIGHT				z

							// CSS_TITLE_OWNED				1
							// CSS_TITLE_ON_ORDER			2
							// CSS_TITLE_WISH_LIST			3
							// CSS_TITLE_WORK				4
							// CSS_TITLE_HAVE_SEEN			5
							{FC(sa),FC(sb),FC(sc),FC(sd),FC(se),FC(sf),FC(sg),FC(sh),FC(si),FC(sj),FC(sk),FC(sl),FC(sm),FC(sn),FC(so),FC(sp),FC(sq),FC(sr),FC(ss),FC(st),FC(su),FC(sv),FC(sx),FC(sy),FC(sz),FC(s1),FC(s2),FC(s3),FC(s4),FC(s5)},  // SCREEN
							{FC(pa),FC(sb),FC(sc),FC(sd),FC(pe),FC(sf),FC(pg),FC(sh),FC(si),FC(sj),FC(sk),FC(pl),FC(sm),FC(sn),FC(po),FC(sp),FC(sq),FC(sr),FC(ps),FC(pt),FC(pu),FC(sv),FC(sx),FC(sy),FC(sz),FC(p1),FC(p2),FC(p3),FC(p4),FC(p5)},  // PRINT
							{FC(sa),FC(sb),FC(sc),FC(sd),FC(se),FC(sf),FC(og),FC(oh),FC(oi),FC(oj),FC(sk),FC(sl),FC(sm),FC(sn),FC(so),FC(sp),FC(sq),FC(sr),FC(ss),FC(st),FC(su),FC(sv),FC(sx),FC(sy),FC(sz),FC(s1),FC(s2),FC(s3),FC(s4),FC(s5)}}; // ONE

#undef FC

/* ========================================= *\
	Ajax Queries
\* ========================================= */

const t_string
gp_ajax_type[] = {
	STR_AND_LEN("dir"),		// c_ajax_director
	STR_AND_LEN("wri"),		// c_ajax_writer
	STR_AND_LEN("cas"),		// c_ajax_cast
	STR_AND_LEN("pub")		// c_ajax_dvd_publisher
};

const char
gc_ajax_class[] = {
	'd',					// c_ajax_director
	'w',					// c_ajax_writer
	'c',					// c_ajax_cast
	'p'						// c_ajax_dvd_publisher
};

const t_string
gp_ajax_callback[] = {
	STR_AND_LEN("fa_dir"),	// c_ajax_director
	STR_AND_LEN("fa_wri"),	// c_ajax_writer
	STR_AND_LEN("fa_cas"),	// c_ajax_cast
	STR_AND_LEN("fa_pub")	// c_ajax_dvd_publisher
};

/* ========================================= *\
	Vendor links
\* ========================================= */

#define VENDOR___(n,a,t,o,k)	 {n, sizeof(n)-1, a, sizeof(a)-1, t, sizeof(t)-1, o, sizeof(o)-1, k, sizeof(k)-1, NULL, 0, NULL, 0}
#define VENDOR_P_(n,a,t,o,k,p)	 {n, sizeof(n)-1, a, sizeof(a)-1, t, sizeof(t)-1, o, sizeof(o)-1, k, sizeof(k)-1, p, sizeof(p)-1, NULL, 0}
#define VENDOR__F(n,a,t,o,k,f)	 {n, sizeof(n)-1, a, sizeof(a)-1, t, sizeof(t)-1, o, sizeof(o)-1, k, sizeof(k)-1, NULL, 0, f, sizeof(f)-1}

/* ========================================= *\
	Decode dictionary
\* ========================================= */

#define FIELD_OPTION(code,desc)		{(int)(code)			,			  #desc,sizeof(#desc) > 1 ? sizeof(#desc)-1:0}
#define FIELD_OPTIO_(code,desc)		{(int)(code)			,			   desc,sizeof( desc) > 1 ? sizeof( desc)-1:0}	// used when desc has ",()"
#define FIELD_OPTION_STR(desc)		{(int)(#desc)			,			  #desc,sizeof(#desc) > 1 ? sizeof(#desc)-1:0}	// used when there is no decode, just pic from list
#define FIELD_OPT2CH(c1,c2,code)	{CHAR2_TO_INT_(c1,c2)	,(unsigned char*)-1,								 code}
#define FIELD_OPT2CS(c1,c2,desc)	{CHAR2_TO_INT_(c1,c2)	,			  #desc,sizeof(#desc) > 1 ? sizeof(#desc)-1:0}

static const t_field_option
_gp_authorized[] =		   {FIELD_OPTION('A',Authorized										),
							FIELD_OPTION('U',Unauthorized									),
							FIELD_OPTION('P',Public Domain									),
							FIELD_OPTION('b',Bootleg										),
							FIELD_OPTION('-',Unknown										)},
_gp_dvd_type[] =		   {FIELD_OPTION('F',Feature Film									),
							FIELD_OPTION('S',Collection of Shorts							),
							FIELD_OPTION('T',TV Series										),
							FIELD_OPTION('D',Documentary									),
							FIELD_OPTION('C',Animation										),
							FIELD_OPTION('a',Anime											),
							FIELD_OPTION('M',Music Video									),
							FIELD_OPTION('K',Karaoke DVD									),
							FIELD_OPTION('U',Audio DVD										),
							FIELD_OPTION('-',Unknown										)},
_gp_expire_reason[] =	   {FIELD_OPTION('P',Missing picture								),
							FIELD_OPTION('-',Not expired									)},
_gp_frame_alternate[] =	   {FIELD_OPTION('S',Full-Screen on same disc						),
							FIELD_OPTION('a',Full-Screen on additional disc					),
							FIELD_OPTION('N',None											),
							FIELD_OPTION('-',Unknown										)},
_gp_frame_convers[] =	   {FIELD_OPTION('O',Original (within 97%)							),
							FIELD_OPTION('P',Pan &amp; Scan									),
							FIELD_OPTION('C',Cropped										),
							FIELD_OPTION('M',Open-Matted									),
							FIELD_OPTION('T',See technical notes							),
							FIELD_OPTION('-',Unknown										)},
_gp_frame_present[] =	   {FIELD_OPTION('A',Anamorphic										),
							FIELD_OPTION('L',Letterboxed									),
							FIELD_OPTION('F',Full-Frame										),
							FIELD_OPTION('S',Full-Screen									),
							FIELD_OPTION('b',Window-boxed									),
							FIELD_OPTION('-',Unknown										)},
_gp_movie_rating[] =	   {FIELD_OPTION('U',Unrated										),
							FIELD_OPTION('N',NR (Not Rated)									),
							FIELD_OPTION('G',G (General Audience)							),
							FIELD_OPTION('P',PG (Parental Guidance Suggested)				),
							FIELD_OPTION('3',PG-13 (Parental Guidance Suggested)			),
							FIELD_OPTION('R',R (Restricted)									),
							FIELD_OPTION('C',NC-17											),
							FIELD_OPTION('X',X (Mature Audiences Only)						),
							FIELD_OPTION('-',Unknown										)},
_gp_region_char[] =		   {FIELD_OPTIO_('0',"0: Plays on any player"							),
							FIELD_OPTIO_('1',"1: US and Canada"									),
							FIELD_OPTIO_('2',"2: Europe, Middle East, Japan and South Africa"	),
							FIELD_OPTIO_('3',"3: Southeast Asia"								),
							FIELD_OPTIO_('4',"4: Australia, New Zealand and Latin America"		),
							FIELD_OPTIO_('5',"5: Africa, Eastern Europe and the rest of Asia"	),
							FIELD_OPTIO_('6',"6: China and Hong Kong"							),
							FIELD_OPTIO_('A',"A: Americas, Japan, Korea and Southeast Asia"		),
							FIELD_OPTIO_('B',"B: Europe, Australia, New Zealand and Africa"		),
							FIELD_OPTIO_('C',"C: Eastern Europe and the rest of Asia"			),
							FIELD_OPTIO_('-',"Unknown"											)},
_gp_release_status[] =	   {FIELD_OPTION('C',Current										),
							FIELD_OPTION('O',Out of print									),
							FIELD_OPTION('A',Announced										),
							FIELD_OPTION('N',Not announced									),
							FIELD_OPTION('D',Release delayed								),
							FIELD_OPTION('X',Release cancelled								),
							FIELD_OPTION('-',Unknown										)},
_gp_suitability[] =		   {FIELD_OPTION('G',Too much gore									),
							FIELD_OPTION('H',Hentai											),
							FIELD_OPTION('P',Soft porn										),
							FIELD_OPTION('-',Unrestricted									)},
_gp_video_format[] =	   {FIELD_OPTION('N',NTSC: USA and Japan							),
							FIELD_OPTION('P',PAL: Europe and Australia						),
							FIELD_OPTION('2',NTSC + PAL										),
							FIELD_OPTION('-',Unknown										)},
_gp_public[] =			   {FIELD_OPTION('Y',Public											),
							FIELD_OPTION('N',Private										)},
_gp_trade_loan[] =		   {FIELD_OPTION('L',On Loan										),
							FIELD_OPTION('T',For Trade										),
							FIELD_OPTION('-',Neither										)},
_gp_amz_country[] =		   {FIELD_OPTION('-',U.S.											),
							FIELD_OPTION('C',Canada											),
							FIELD_OPTION('D',Germany										),
							FIELD_OPTION('F',France											),
							FIELD_OPTION('I',Italy											),
							FIELD_OPTION('E',Spain											),
							FIELD_OPTION('J',Japan											),
							FIELD_OPTION('K',U.K.											)},
_gp_pic_code[] =		   {FIELD_OPTION('Y',Present										),
							FIELD_OPTION('P',Processing										),
							FIELD_OPTION('-',Missing										)},
// added to dvdaf.decodes as 'request_cd'
_gp_request_dvd[] =		   {FIELD_OPTION('E',Change request									),
							FIELD_OPTION('N',New title proposal								),
							FIELD_OPTION('D',Title deletion request							),
							FIELD_OPTION('-',Missing										)},
// added to dvdaf.decodes as 'request_cd'
_gp_request_pic[] =		   {FIELD_OPTION('E',Change picture proposal						),
							FIELD_OPTION('N',New picture proposal							),
							FIELD_OPTION('R',Replace picture proposal						),
							FIELD_OPTION('D',Delete picture proposal						),
							FIELD_OPTION('-',Missing										)},
// added to dvdaf.decodes as 'disposition_cd'
_gp_disposition[] =		   {FIELD_OPTION('A',Approved										),
							FIELD_OPTION('P',Partially approved								),
							FIELD_OPTION('R',Declined										),
							FIELD_OPTION('W',Withdrawn										),
							FIELD_OPTION('X',Expired										),
							FIELD_OPTION('-',Not processed									)},
// added to dvdaf.decodes as 'pic_type'
_gp_pic_type[] =		   {FIELD_OPTION('D',Cover Art										),
							FIELD_OPTION('I',Bonus Items									),
							FIELD_OPTION('P',Movie Poster									),
							FIELD_OPTION('F',Screen Capture									),
							FIELD_OPTION('G',Fan-Created Cover Art							),
							FIELD_OPTION('B',Backstage Pictures								),
							FIELD_OPTION('C',Casting Pictures								),
							FIELD_OPTION('E',Events											)},
// added to dvdaf.decodes as 'img_suitability'
_gp_img_suitability[] =	   {FIELD_OPTION('-',Unrestricted									),
							FIELD_OPTION('X',NC-17											)},
// added to dvdaf.decodes as 'img_treatment'
_gp_img_treatment[] =	   {FIELD_OPTION('B',DVD											),
							FIELD_OPTION('H',HD DVD											),
							FIELD_OPTION('R',Blu-ray										),
							FIELD_OPTION('O',No border										),
							FIELD_OPTION('K',Keep ratio										),
							FIELD_OPTION('F',16:9 frame										)},
// added to dvdaf.decodes as 'media_type'
_gp_media_type[] =		   {FIELD_OPTION('D',DVD											),
							FIELD_OPTION('B',Blu-ray										),
							FIELD_OPTION('3',Blu-ray 3D										),
							FIELD_OPTION('2',Blu-ray/DVD Combo								),
							FIELD_OPTION('R',BD-R											),
							FIELD_OPTION('V',DVD-R											),
							FIELD_OPTION('H',HD DVD											),
							FIELD_OPTION('C',HD DVD/DVD Combo								),
							FIELD_OPTION('T',HD DVD/DVD TWIN Format							),
							FIELD_OPTION('A',DVD Audio										),
							FIELD_OPTION('O',Other											),
							FIELD_OPTION('P',-												),
							FIELD_OPTION('F',Film											),
							FIELD_OPTION('S',Short											),
							FIELD_OPTION('L',Television										),
							FIELD_OPTION('E',Featurette										),
							FIELD_OPTION('N',Events &amp; Performances						)},
// added to dvdaf.decodes as 'source'
_gp_source[] =			   {FIELD_OPTION('A',DVD Package									),
							FIELD_OPTION('I',Part of DVD Package							),
							FIELD_OPTION('E',DVD Package Bonus Disc							),
							FIELD_OPTION('C',Audio CD Bonus Disc							),
							FIELD_OPTION('G',Game Bonus Disc								),
							FIELD_OPTION('B',Book Bonus Disc								),
							FIELD_OPTION('M',Magazine Bonus Disc							),
							FIELD_OPTION('O',Other Product Bonus Disc						),
							FIELD_OPTION('T',Theatrical or Broadcast						)},

_gp_genre[] =			   {FIELD_OPTION(10000, Action-Adventure + Subgenres				),
							FIELD_OPTION(10100, Action-Adventure / Comedy					),
							FIELD_OPTION(10200, Action-Adventure / Crime					),
							FIELD_OPTION(10300, Action-Adventure / Disaster					),
							FIELD_OPTION(10400, Action-Adventure / Epic						),
							FIELD_OPTION(10500, Action-Adventure / Espionage				),
							FIELD_OPTION(10600, Action-Adventure / Martial Arts				),
							FIELD_OPTION(10700, Action-Adventure / Military					),
							FIELD_OPTION(10750, Action-Adventure / Samurai					),
							FIELD_OPTION(10800, Action-Adventure / Superheroes				),
							FIELD_OPTION(10999, Action-Adventure							),

							FIELD_OPTION(13000, Animation + Subgenres						),
							FIELD_OPTION(13100, Animation / Cartoons						),
							FIELD_OPTION(13300, Animation / Family							),
							FIELD_OPTION(13600, Animation / Mature						),
							FIELD_OPTION(13700, Animation / Puppetry &amp; Stop-Motion		),
							FIELD_OPTION(13800, Animation / Sci-Fi							),
							FIELD_OPTION(13900, Animation / Superheroes						),
							FIELD_OPTION(13999, Animation									),

							FIELD_OPTION(16000, Anime + Subgenres							),
							FIELD_OPTION(16200, Anime / Action								),
							FIELD_OPTION(16250, Anime / Comedy								),
							FIELD_OPTION(16300, Anime / Drama								),
							FIELD_OPTION(16400, Anime / Fantasy								),
							FIELD_OPTION(16500, Anime / Horror								),
							FIELD_OPTION(16600, Anime / Mahou Shoujo (Magical Girls)		),
							FIELD_OPTION(16700, Anime / Martial Arts						),
							FIELD_OPTION(16750, Anime / Mecha (Giant Robots)				),
							FIELD_OPTION(16800, Anime / Mo&#233; (Cute Girls, Romance)		),
							FIELD_OPTION(16850, Anime / Romance								),
							FIELD_OPTION(16900, Anime / Sci-Fi								),
							FIELD_OPTION(16999, Anime										),

							FIELD_OPTION(20000, Comedy + Subgenres							),
							FIELD_OPTION(20100, Comedy / Dark								),
							FIELD_OPTION(20200, Comedy / Farce								),
							FIELD_OPTION(20300, Comedy / Horror								),
							FIELD_OPTION(20400, Comedy / Romantic							),
							FIELD_OPTION(20600, Comedy / Satire								),
							FIELD_OPTION(20650, Comedy / Sci-Fi								),
							FIELD_OPTION(20700, Comedy / Screwball							),
							FIELD_OPTION(20750, Comedy / Sitcom								),
							FIELD_OPTION(20800, Comedy / Sketches &amp; Stand-Up			),
							FIELD_OPTION(20850, Comedy / Slapstick							),
							FIELD_OPTION(20900, Comedy / Teen								),
							FIELD_OPTION(20999, Comedy										),

							FIELD_OPTION(24000, Documentary + Subgenres						),
							FIELD_OPTION(24100, Documentary / Biography						),
							FIELD_OPTION(24200, Documentary / Crime							),
							FIELD_OPTION(24250, Documentary / Culture						),
							FIELD_OPTION(24270, Documentary / Entertainment					),
							FIELD_OPTION(24300, Documentary / History						),
							FIELD_OPTION(24400, Documentary / Nature						),
							FIELD_OPTION(24500, Documentary / Propaganda					),
							FIELD_OPTION(24600, Documentary / Religion						),
							FIELD_OPTION(24700, Documentary / Science						),
							FIELD_OPTION(24750, Documentary / Social						),
							FIELD_OPTION(24800, Documentary / Sports						),
							FIELD_OPTION(24900, Documentary / Travel						),
							FIELD_OPTION(24999, Documentary									),

							FIELD_OPTION(28000, Drama + Subgenres							),
							FIELD_OPTION(28100, Drama / Courtroom							),
							FIELD_OPTION(28150, Drama / Crime								),
							FIELD_OPTION(28200, Drama / Docudrama							),
							FIELD_OPTION(28400, Drama / Melodrama							),
							FIELD_OPTION(28600, Drama / Period								),
							FIELD_OPTION(28800, Drama / Romance								),
							FIELD_OPTION(28900, Drama / Sports								),
							FIELD_OPTION(28950, Drama / War									),
							FIELD_OPTION(28999, Drama										),

							FIELD_OPTION(32000, Educational + Subgenres						),
							FIELD_OPTION(32200, Educational / Children						),
							FIELD_OPTION(32700, Educational / School						),
							FIELD_OPTION(32999, Educational									),

							FIELD_OPTION(36000, Erotica + Subgenres							),
							FIELD_OPTION(36100, Erotica / Hentai							),
							FIELD_OPTION(36999, Erotica										),

							FIELD_OPTION(39999, Experimental								),

							FIELD_OPTION(41000, Exploitation + Subgenres					),
							FIELD_OPTION(41100, Exploitation / Blaxploitation				),
							FIELD_OPTION(41300, Exploitation / Nazisploitation				),
							FIELD_OPTION(41400, Exploitation / Nunsploitation				),
							FIELD_OPTION(41500, Exploitation / Pinku Eiga					),
							FIELD_OPTION(41600, Exploitation / Sexploitation				),
							FIELD_OPTION(41700, Exploitation / Shockumentary				),
							FIELD_OPTION(41800, Exploitation / WIP							),
							FIELD_OPTION(41999, Exploitation								),

							FIELD_OPTION(43999, Fantasy										),
							FIELD_OPTION(47999, Film Noir									),

							FIELD_OPTION(51000, Foreign + Subgenres							),
							FIELD_OPTION(51100, Foreign / Brazil							),
							FIELD_OPTION(51150, Foreign / China								),
							FIELD_OPTION(51200, Foreign / Netherlands						),
							FIELD_OPTION(51250, Foreign / Eastern Europe					),
							FIELD_OPTION(51300, Foreign / France							),
							FIELD_OPTION(51350, Foreign / Germany							),
							FIELD_OPTION(51400, Foreign / Hong Kong							),
							FIELD_OPTION(51450, Foreign / India								),
							FIELD_OPTION(51500, Foreign / Italy								),
							FIELD_OPTION(51550, Foreign / Japan								),
							FIELD_OPTION(51570, Foreign / South Korea						),
							FIELD_OPTION(51600, Foreign / Mexico							),
							FIELD_OPTION(51650, Foreign / Middle East						),
							FIELD_OPTION(51700, Foreign / Portugal							),
							FIELD_OPTION(51750, Foreign / Russia							),
							FIELD_OPTION(51780, Foreign / Scandinavia						),
							FIELD_OPTION(51790, Foreign / Spain								),
							FIELD_OPTION(51800, Foreign / Latin America						),
							FIELD_OPTION(51850, Foreign / Sweden							),
							FIELD_OPTION(51900, Foreign / Taiwan							),
							FIELD_OPTION(51999, Foreign										),

							FIELD_OPTION(55000, Horror + Subgenres							),
							FIELD_OPTION(55050, Horror / Anthology							),
							FIELD_OPTION(55100, Horror / Asian								),
							FIELD_OPTION(55250, Horror / Creature &amp; Animal				),
							FIELD_OPTION(55300, Horror / ESP &amp; Ghosts					),
							FIELD_OPTION(55350, Horror / Eurotrash							),
							FIELD_OPTION(55400, Horror / Exploitation						),
							FIELD_OPTION(55450, Horror / Gialli								),
							FIELD_OPTION(55500, Horror / Gore &amp; Shock					),
							FIELD_OPTION(55550, Horror / Gothic								),
							FIELD_OPTION(55700, Horror / Possession &amp; Satan				),
							FIELD_OPTION(55800, Horror / Shockumentary						),
							FIELD_OPTION(55850, Horror / Slasher &amp; Survival				),
							FIELD_OPTION(55900, Horror / Vampires							),
							FIELD_OPTION(55950, Horror / Zombies &amp; Infected				),
							FIELD_OPTION(55960, Horror / Other Undead						),
							FIELD_OPTION(55999, Horror										),

							FIELD_OPTION(59000, Music + Subgenres							),
							FIELD_OPTION(59300, Music / Live in Concert						),
							FIELD_OPTION(59700, Music / Music Videos						),
							FIELD_OPTION(59999, Music										),

							FIELD_OPTION(62999, Musical										),

							FIELD_OPTION(66000, Performing Arts + Subgenres					),
							FIELD_OPTION(66100, Performing Arts / Circus					),
							FIELD_OPTION(66300, Performing Arts / Concerts					),
							FIELD_OPTION(66500, Performing Arts / Dance						),
							FIELD_OPTION(66700, Performing Arts / Operas					),
							FIELD_OPTION(66900, Performing Arts / Theater					),
							FIELD_OPTION(66999, Performing Arts								),

							FIELD_OPTION(70000, Sci-Fi + Subgenres							),
							FIELD_OPTION(70100, Sci-Fi / Alien								),
							FIELD_OPTION(70200, Sci-Fi / Alternate Reality					),
							FIELD_OPTION(70250, Sci-Fi / Apocalyptic						),
							FIELD_OPTION(70300, Sci-Fi / Cyber Punk							),
							FIELD_OPTION(70400, Sci-Fi / Kaiju (Giant Monster)				),
							FIELD_OPTION(70500, Sci-Fi / Lost Worlds						),
							FIELD_OPTION(70550, Sci-Fi / Military							),
							FIELD_OPTION(70600, Sci-Fi / Other Worlds						),
							FIELD_OPTION(70800, Sci-Fi / Space								),
							FIELD_OPTION(70850, Sci-Fi / Space Horror						),
							FIELD_OPTION(70870, Sci-Fi / Superheroes						),
							FIELD_OPTION(70900, Sci-Fi / Utopia &amp; Dystopia				),
							FIELD_OPTION(70999, Sci-Fi										),

							FIELD_OPTION(73999, Short										),

							FIELD_OPTION(76000, Silent + Subgenres							),
							FIELD_OPTION(76100, Silent / Animation							),
							FIELD_OPTION(76300, Silent / Horror								),
							FIELD_OPTION(76500, Silent / Melodrama							),
							FIELD_OPTION(76700, Silent / Slapstick							),
							FIELD_OPTION(76800, Silent / Western							),
							FIELD_OPTION(76999, Silent										),

							FIELD_OPTION(80000, Sports + Subgenres							),
							FIELD_OPTION(80100, Sports / Baseball							),
							FIELD_OPTION(80130, Sports / Basketball							),
							FIELD_OPTION(80170, Sports / Biking								),
							FIELD_OPTION(80200, Sports / Fitness							),
							FIELD_OPTION(80250, Sports / Football							),
							FIELD_OPTION(80300, Sports / Golf								),
							FIELD_OPTION(80350, Sports / Hockey								),
							FIELD_OPTION(80400, Sports / Martial Arts						),
							FIELD_OPTION(80450, Sports / Motor Sports						),
							FIELD_OPTION(80500, Sports / Olympics							),
							FIELD_OPTION(80600, Sports / Skateboard							),
							FIELD_OPTION(80700, Sports / Skiing								),
							FIELD_OPTION(80800, Sports / Soccer								),
							FIELD_OPTION(80850, Sports / Tennis								),
							FIELD_OPTION(80900, Sports / Wrestling							),
							FIELD_OPTION(80999, Sports										),

							FIELD_OPTION(84000, Suspense + Subgenres						),
							FIELD_OPTION(84400, Suspense / Mystery							),
							FIELD_OPTION(84700, Suspense / Thriller							),
							FIELD_OPTION(84999, Suspense									),

							FIELD_OPTION(88000, War + Subgenres								),
							FIELD_OPTION(88200, War / US Civil War							),
							FIELD_OPTION(88300, War / World War I							),
							FIELD_OPTION(88400, War / World War II							),
							FIELD_OPTION(88500, War / Korea									),
							FIELD_OPTION(88600, War / Vietnam								),
							FIELD_OPTION(88700, War / Post-Cold War							),
							FIELD_OPTION(88900, War / Other									),
							FIELD_OPTION(88999, War											),

							FIELD_OPTION(91000, Western + Subgenres							),
							FIELD_OPTION(91400, Western / Epic								),
							FIELD_OPTION(91700, Western / Singing Cowboy					),
							FIELD_OPTION(91800, Western / Spaghetti							),
							FIELD_OPTION(91999, Western										),

							FIELD_OPTION(95999, DVD Audio									),

							FIELD_OPTION(98000, Other + Subgenres							),
							FIELD_OPTION(98200, Other / Digital Comic Books					),
							FIELD_OPTION(98250, Other / Game Shows							),
							FIELD_OPTION(98300, Other / Games								),
							FIELD_OPTION(98999, Other										),

							FIELD_OPTION(99999, Unspecified Genre							)},

_gp_genre_lower[] =		   {FIELD_OPTION(10100, action-comedy								),
							FIELD_OPTION(10200, action-crime								),
							FIELD_OPTION(10300, action-disaster								),
							FIELD_OPTION(10400, action-epic									),
							FIELD_OPTION(10500, action-espionage							),
							FIELD_OPTION(10600, action-martialarts							),
							FIELD_OPTION(10700, action-military								),
							FIELD_OPTION(10750, action-samurai							),
							FIELD_OPTION(10800, action-superheroes							),
							FIELD_OPTION(10999, action-nosub								),
							FIELD_OPTION(13100, animation-cartoons							),
							FIELD_OPTION(13300, animation-family							),
							FIELD_OPTION(13600, animation-mature						),
							FIELD_OPTION(13700, animation-puppetrystopmotion				),
							FIELD_OPTION(13800, animation-scifi								),
							FIELD_OPTION(13900, animation-superheroes						),
							FIELD_OPTION(13999, animation-nosub								),
							FIELD_OPTION(16200, anime-action								),
							FIELD_OPTION(16250, anime-comedy								),
							FIELD_OPTION(16300, anime-drama									),
							FIELD_OPTION(16400, anime-fantasy								),
							FIELD_OPTION(16500, anime-horror								),
							FIELD_OPTION(16600, anime-mahoushoujo							),
							FIELD_OPTION(16700, anime-martialarts							),
							FIELD_OPTION(16750, anime-mecha									),
							FIELD_OPTION(16800, anime-moe									),
							FIELD_OPTION(16850, anime-romance								),
							FIELD_OPTION(16900, anime-scifi									),
							FIELD_OPTION(16999, anime-nosub									),
							FIELD_OPTION(20100, comedy-dark									),
							FIELD_OPTION(20200, comedy-farce								),
							FIELD_OPTION(20300, comedy-horror								),
							FIELD_OPTION(20400, comedy-romantic								),
							FIELD_OPTION(20600, comedy-satire								),
							FIELD_OPTION(20650, comedy-scifi								),
							FIELD_OPTION(20700, comedy-screwball							),
							FIELD_OPTION(20750, comedy-sitcom								),
							FIELD_OPTION(20800, comedy-sketchesstandup						),
							FIELD_OPTION(20850, comedy-slapstick							),
							FIELD_OPTION(20900, comedy-teen									),
							FIELD_OPTION(20999, comedy-nosub								),
							FIELD_OPTION(24100, documentary-biography						),
							FIELD_OPTION(24200, documentary-crime							),
							FIELD_OPTION(24250, documentary-culture							),
							FIELD_OPTION(24270, documentary-entertainment					),
							FIELD_OPTION(24300, documentary-history							),
							FIELD_OPTION(24400, documentary-nature							),
							FIELD_OPTION(24500, documentary-propaganda						),
							FIELD_OPTION(24600, documentary-religion						),
							FIELD_OPTION(24700, documentary-science							),
							FIELD_OPTION(24750, documentary-social							),
							FIELD_OPTION(24800, documentary-sports							),
							FIELD_OPTION(24900, documentary-travel							),
							FIELD_OPTION(24999, documentary-nosub							),
							FIELD_OPTION(28100, drama-courtroom								),
							FIELD_OPTION(28150, drama-crime									),
							FIELD_OPTION(28200, drama-docudrama								),
							FIELD_OPTION(28400, drama-melodrama								),
							FIELD_OPTION(28600, drama-period								),
							FIELD_OPTION(28800, drama-romance								),
							FIELD_OPTION(28900, drama-sports								),
							FIELD_OPTION(28950, drama-war									),
							FIELD_OPTION(28999, drama-nosub									),
							FIELD_OPTION(32200, educational-children						),
							FIELD_OPTION(32700, educational-school							),
							FIELD_OPTION(32999, educational-nosub							),
							FIELD_OPTION(36100, erotica-hentai								),
							FIELD_OPTION(36999, erotica-nosub								),
							FIELD_OPTION(39999, experimental								),

							FIELD_OPTION(41100, exploitation-blaxploitation					),
							FIELD_OPTION(41300, exploitation-nazisploitation				),
							FIELD_OPTION(41400, exploitation-nunsploitation					),
							FIELD_OPTION(41500, exploitation-pinkueiga						),
							FIELD_OPTION(41600, exploitation-sexploitation					),
							FIELD_OPTION(41700, exploitation-shockumentary					),
							FIELD_OPTION(41800, exploitation-wip							),
							FIELD_OPTION(41999, exploitation-nosub							),

							FIELD_OPTION(43999, fantasy										),
							FIELD_OPTION(47999, filmnoir									),
							FIELD_OPTION(51100, foreign-brazil								),
							FIELD_OPTION(51150, foreign-china								),
							FIELD_OPTION(51200, foreign-netherlands							),
							FIELD_OPTION(51250, foreign-easterneurope						),
							FIELD_OPTION(51300, foreign-france								),
							FIELD_OPTION(51350, foreign-germany								),
							FIELD_OPTION(51400, foreign-hongkong							),
							FIELD_OPTION(51450, foreign-india								),
							FIELD_OPTION(51500, foreign-italy								),
							FIELD_OPTION(51550, foreign-japan								),
							FIELD_OPTION(51570, foreign-southkorea							),
							FIELD_OPTION(51600, foreign-mexico								),
							FIELD_OPTION(51650, foreign-middleeast							),
							FIELD_OPTION(51700, foreign-portugal							),
							FIELD_OPTION(51750, foreign-russia								),
							FIELD_OPTION(51780, foreign-scandinavia							),
							FIELD_OPTION(51790, foreign-spain								),
							FIELD_OPTION(51800, foreign-latinamerica						),
							FIELD_OPTION(51850, foreign-sweden								),
							FIELD_OPTION(51900, foreign-taiwan								),
							FIELD_OPTION(51999, foreign-nosub								),
							FIELD_OPTION(55050, horror-anthology							),
							FIELD_OPTION(55100, horror-asian								),
							FIELD_OPTION(55250, horror-creatureanimal						),
							FIELD_OPTION(55300, horror-espghosts							),
							FIELD_OPTION(55350, horror-eurotrash							),
							FIELD_OPTION(55400, horror-exploitation							),
							FIELD_OPTION(55450, horror-gialli								),
							FIELD_OPTION(55500, horror-goreshock							),
							FIELD_OPTION(55550, horror-gothic								),
							FIELD_OPTION(55700, horror-possessionsatan						),
							FIELD_OPTION(55800, horror-shockumentary						),
							FIELD_OPTION(55850, horror-slashersurvival						),
							FIELD_OPTION(55900, horror-vampires								),
							FIELD_OPTION(55950, horror-zombiesinfected						),
							FIELD_OPTION(55960, horror-otherundead							),
							FIELD_OPTION(55999, horror-nosub								),
							FIELD_OPTION(59300, music-liveinconcert							),
							FIELD_OPTION(59700, music-musicvideos							),
							FIELD_OPTION(59999, music-nosub									),
							FIELD_OPTION(62999, musical										),
							FIELD_OPTION(66100, performing-circus							),
							FIELD_OPTION(66300, performing-concerts							),
							FIELD_OPTION(66500, performing-dance							),
							FIELD_OPTION(66700, performing-operas							),
							FIELD_OPTION(66900, performing-theater							),
							FIELD_OPTION(66999, performing-nosub							),
							FIELD_OPTION(70100, scifi-alien									),
							FIELD_OPTION(70200, scifi-alternatereality						),
							FIELD_OPTION(70250, scifi-apocalyptic							),
							FIELD_OPTION(70300, scifi-cyberpunk								),
							FIELD_OPTION(70400, scifi-kaiju									),
							FIELD_OPTION(70500, scifi-lostworlds							),
							FIELD_OPTION(70550, scifi-military								),
							FIELD_OPTION(70600, scifi-otherworlds							),
							FIELD_OPTION(70800, scifi-space									),
							FIELD_OPTION(70850, scifi-spacehorror							),
							FIELD_OPTION(70870, scifi-superheroes							),
							FIELD_OPTION(70900, scifi-utopiadystopia						),
							FIELD_OPTION(70999, scifi-nosub									),
							FIELD_OPTION(73999, short										),
							FIELD_OPTION(76100, silent-animation							),
							FIELD_OPTION(76300, silent-horror								),
							FIELD_OPTION(76500, silent-melodrama							),
							FIELD_OPTION(76700, silent-slapstick							),
							FIELD_OPTION(76800, silent-western								),
							FIELD_OPTION(76999, silent-nosub								),
							FIELD_OPTION(80100, sports-baseball								),
							FIELD_OPTION(80130, sports-basketball							),
							FIELD_OPTION(80170, sports-biking								),
							FIELD_OPTION(80200, sports-fitness								),
							FIELD_OPTION(80250, sports-football								),
							FIELD_OPTION(80300, sports-golf									),
							FIELD_OPTION(80350, sports-hockey								),
							FIELD_OPTION(80400, sports-martialarts							),
							FIELD_OPTION(80450, sports-motorsports							),
							FIELD_OPTION(80500, sports-olympics								),
							FIELD_OPTION(80600, sports-skateboard							),
							FIELD_OPTION(80700, sports-skiing								),
							FIELD_OPTION(80800, sports-soccer								),
							FIELD_OPTION(80850, sports-tennis								),
							FIELD_OPTION(80900, sports-wrestling							),
							FIELD_OPTION(80999, sports-nosub								),
							FIELD_OPTION(84400, suspense-mystery							),
							FIELD_OPTION(84700, suspense-thriller							),
							FIELD_OPTION(84999, suspense-nosub								),
							FIELD_OPTION(88200, war-uscivilwar								),
							FIELD_OPTION(88300, war-wwi										),
							FIELD_OPTION(88400, war-wwii									),
							FIELD_OPTION(88500, war-korea									),
							FIELD_OPTION(88600, war-vietnam									),
							FIELD_OPTION(88700, war-postcoldwar								),
							FIELD_OPTION(88900, war-other									),
							FIELD_OPTION(88999, war-nosub									),
							FIELD_OPTION(91400, western-epic								),
							FIELD_OPTION(91700, western-singingcowboy						),
							FIELD_OPTION(91800, western-spaghetti							),
							FIELD_OPTION(91999, western-nosub								),
							FIELD_OPTION(95999, dvdaudio									),
							FIELD_OPTION(98200, other-digitalcomicbooks						),
							FIELD_OPTION(98250, other-gameshows								),
							FIELD_OPTION(98300, other-games									),
							FIELD_OPTION(98999, other-nosub									),
							FIELD_OPTION(99999, unspecifiedgenre							)},

_gp_country[] =			   {FIELD_OPT2CS(  a,r, Argentina									),
							FIELD_OPT2CS(  a,t, Austria										),
							FIELD_OPT2CS(  a,u, Australia									),
							FIELD_OPT2CS(  b,e, Belgium										),
							FIELD_OPT2CS(  b,r, Brazil										),
							FIELD_OPT2CS(  c,a, Canada										),
							FIELD_OPT2CS(  c,h, Switzerland									),
							FIELD_OPT2CS(  c,l, Chile										),
							FIELD_OPT2CS(  c,n, China										),
							FIELD_OPT2CS(  c,u, Cuba										),
							FIELD_OPT2CS(  c,z, Czech Republic								),
							FIELD_OPT2CS(  d,e, Germany										),
							FIELD_OPT2CS(  d,k, Denmark										),
							FIELD_OPT2CS(  e,e, Estonia										),
							FIELD_OPT2CS(  e,s, Spain										),
							FIELD_OPT2CS(  f,i, Finland										),
							FIELD_OPT2CS(  f,r, France										),
							FIELD_OPT2CS(  g,r, Greece										),
							FIELD_OPT2CS(  h,k, Hong Kong									),
							FIELD_OPT2CS(  h,r, Croatia										),
							FIELD_OPT2CS(  h,u, Hungary										),
							FIELD_OPT2CS(  i,d, Indonesia									),
							FIELD_OPT2CS(  i,l, Israel										),
							FIELD_OPT2CS(  i,n, India										),
							FIELD_OPT2CS(  i,s, Iceland										),
							FIELD_OPT2CS(  i,t, Italy										),
							FIELD_OPT2CS(  j,p, Japan										),
							FIELD_OPT2CS(  k,r, South Korea									),
							FIELD_OPT2CS(  l,t, Lithuania									),
							FIELD_OPT2CS(  m,k, Macedonia									),
							FIELD_OPT2CS(  m,x, Mexico										),
							FIELD_OPT2CS(  m,y, Malaysia									),
							FIELD_OPT2CS(  n,l, Netherlands									),
							FIELD_OPT2CS(  n,o, Norway										),
							FIELD_OPT2CS(  n,z, New Zealand									),
							FIELD_OPT2CS(  p,h, Philippines									),
							FIELD_OPT2CS(  p,l, Poland										),
							FIELD_OPT2CS(  p,t, Portugal									),
							FIELD_OPT2CS(  r,o, Romania										),
							FIELD_OPT2CS(  r,s, Serbia										),
							FIELD_OPT2CS(  r,u, Russian Federation							),
							FIELD_OPT2CS(  s,e, Sweden										),
							FIELD_OPT2CS(  s,g, Singapore									),
							FIELD_OPT2CS(  s,i, Slovenia									),
							FIELD_OPT2CS(  s,k, Slovakia									),
							FIELD_OPT2CS(  t,h, Thailand									),
							FIELD_OPT2CS(  t,r, Turkey										),
							FIELD_OPT2CS(  t,w, Taiwan										),
							FIELD_OPT2CS(  u,k, U.K.										),
							FIELD_OPT2CS(  u,n, Unknown Country								),
							FIELD_OPT2CS(  u,s, U.S.										),
							FIELD_OPT2CS(  z,a, South Africa								)},

_gp_language[] =		   {FIELD_OPT2CS(a,m,Armenian										),
							FIELD_OPT2CS(a,r,Arabic											),
							FIELD_OPT2CS(b,g,Bulgarian										),
							FIELD_OPT2CS(b,n,Indian-Bengali									),
							FIELD_OPT2CS(b,r,Portuguese-Brazilian							),
							FIELD_OPT2CS(c,a,French-Canadian								), // deprecated
							FIELD_OPT2CS(c,s,Chinese-Shanghainese							),
							FIELD_OPT2CS(c,t,Chinese-Cantonese								),
							FIELD_OPT2CS(c,z,Czech											),
							FIELD_OPT2CS(d,e,German											),
							FIELD_OPT2CS(d,k,Danish											),
							FIELD_OPT2CS(e,n,English										),
							FIELD_OPT2CS(e,o,Esperanto										),
							FIELD_OPT2CS(e,s,Spanish										),
							FIELD_OPT2CS(e,t,Estonian										),
							FIELD_OPT2CS(f,a,Farsi											),
							FIELD_OPT2CS(f,i,Finnish										),
							FIELD_OPT2CS(f,r,French											),
							FIELD_OPT2CS(g,e,Georgian										),
							FIELD_OPT2CS(g,r,Greek											),
							FIELD_OPT2CS(h,e,Hebrew											),
							FIELD_OPT2CS(h,i,Indian-Hindi									),
							FIELD_OPT2CS(h,o,Chinese-Hokkien								),
							FIELD_OPT2CS(h,u,Hungarian										),
							FIELD_OPT2CS(i,d,Bahasa-Indonesia								),
							FIELD_OPT2CS(i,l,Yiddish										),
							FIELD_OPT2CS(i,n,Indian-Others									),
							FIELD_OPT2CS(i,s,Icelandic										),
							FIELD_OPT2CS(i,t,Italian										),
							FIELD_OPT2CS(j,p,Japanese										),
							FIELD_OPT2CS(k,h,Khmer											),
							FIELD_OPT2CS(k,l,Klingon										), // deprecated
							FIELD_OPT2CS(k,r,Korean											),
							FIELD_OPT2CS(k,u,Kurdish										),
							FIELD_OPT2CS(k,z,Kazakh											),
							FIELD_OPT2CS(l,a,Latin											),
							FIELD_OPT2CS(l,t,Lithuanian										),
							FIELD_OPT2CS(l,v,Latvian										),
							FIELD_OPT2CS(m,a,Chinese-Mandarin								),
							FIELD_OPT2CS(m,k,Macedonian										),
							FIELD_OPT2CS(m,l,Indian-Malayalam								),
							FIELD_OPT2CS(m,n,Mongolian										),
							FIELD_OPT2CS(m,y,Bahasa-Malaysia								),
							FIELD_OPT2CS(n,l,Dutch											),
							FIELD_OPT2CS(n,o,Norwegian										),
							FIELD_OPT2CS(n,z,Aramaic										),
							FIELD_OPT2CS(o,t,Other											),
							FIELD_OPT2CS(p,h,Filipino										),
							FIELD_OPT2CS(p,l,Polish											),
							FIELD_OPT2CS(p,t,Portuguese										),
							FIELD_OPT2CS(p,u,Indian-Punjabi									),
							FIELD_OPT2CS(r,m,Romani											),
							FIELD_OPT2CS(r,o,Romanian										),
							FIELD_OPT2CS(r,u,Russian										),
							FIELD_OPT2CS(s,c,Serbo-Croatian									),
							FIELD_OPT2CS(s,e,Swedish										),
							FIELD_OPT2CS(s,i,Slovenian										),
							FIELD_OPT2CS(s,k,Slovak											),
							FIELD_OPT2CS(s,l,Silent											),
							FIELD_OPT2CS(t,a,Indian-Tamil									),
							FIELD_OPT2CS(t,e,Indian-Telugu									),
							FIELD_OPT2CS(t,h,Thai											),
							FIELD_OPT2CS(t,r,Turkish										),
							FIELD_OPT2CS(t,w,Chinese-Taiwanese								),
							FIELD_OPT2CS(u,k,Ukrainian										),
							FIELD_OPT2CS(u,n,Unknown Language								),
							FIELD_OPT2CS(u,r,Indian-Urdu									),
							FIELD_OPT2CS(v,e,Catalan										),
							FIELD_OPT2CS(v,i,Vietnamese										)};

#undef FIELD_OPTION
#undef FIELD_OPTIO_

#define DICT_UNSORTED_CHAR(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 0, c_dict_data_char			,def,val}
#define DICT___SORTED_CHAR(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 1, c_dict_data_char			,def,val}
#define DICT_UNSORTED_2C_N(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 0, c_dict_data_2char_int		,def,val}
#define DICT___SORTED_2C_N(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 1, c_dict_data_2char_int		,def,val}
#define DICT_UNSORTED_2C_S(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 0, c_dict_data_2char_string	,def,val}
#define DICT___SORTED_2C_S(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 1, c_dict_data_2char_string	,def,val}
#define DICT_RVSORTED_2C_S(options,def,val)		{options, sizeof(options)/sizeof(t_field_option),-1, c_dict_data_2char_string	,def,val}
#define DICT_UNSORTED__INT(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 0, c_dict_data_int			,def,val}
#define DICT___SORTED__INT(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 1, c_dict_data_int			,def,val}
#define DICT_UNSORTED_STR_(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 0, c_dict_data_string			,def,val}
#define DICT___SORTED_STR_(options,def,val)		{options, sizeof(options)/sizeof(t_field_option), 1, c_dict_data_string			,def,val}

const t_field_dictionary
gp_dictionary[] =		   {{NULL, 0, 0, 0, 0, -1},
							DICT_UNSORTED_CHAR(_gp_authorized		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_dvd_type			, -1,						0),
							DICT_UNSORTED_CHAR(_gp_expire_reason	, -1,						0),
							DICT_UNSORTED_CHAR(_gp_frame_alternate	, -1,						0),
							DICT_UNSORTED_CHAR(_gp_frame_convers	, -1,						0),
							DICT_UNSORTED_CHAR(_gp_frame_present	, -1,						0),
							DICT_UNSORTED_CHAR(_gp_movie_rating		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_release_status	, -1,						0),
							DICT_UNSORTED_CHAR(_gp_suitability		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_video_format		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_public			,  0,						0),
							DICT___SORTED__INT(_gp_genre			, -1,c_dict_direct_no_quotes ),
							DICT___SORTED__INT(_gp_genre_lower		, -1,c_dict_direct_no_quotes ),
							DICT___SORTED_2C_S(_gp_country			, 38,						0),
							DICT___SORTED_CHAR(_gp_trade_loan		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_amz_country		,  0,						0),
							DICT_UNSORTED_CHAR(_gp_pic_code			, -1,						0),
							DICT___SORTED_2C_S(_gp_language			, 43,						0),
							DICT_UNSORTED_STR_(_gp_request_dvd		, -1,						0),
							DICT_UNSORTED_STR_(_gp_request_pic		, -1,						0),
							DICT_UNSORTED_STR_(_gp_disposition		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_region_char		, -1,						0),
							DICT_UNSORTED_CHAR(_gp_pic_type			,  0,						0),
							DICT_UNSORTED_CHAR(_gp_img_suitability	,  0,						0),
							DICT_UNSORTED_CHAR(_gp_img_treatment	,  0,						0),
							DICT_UNSORTED_CHAR(_gp_media_type		,  0,						0),
							DICT_UNSORTED_CHAR(_gp_source			,  0,						0)
};

#undef DICT_UNSORTED_CHAR
#undef DICT___SORTED_CHAR
#undef DICT_UNSORTED__INT
#undef DICT___SORTED__INT

/* ========================================= *\
	Tables and their aliases
\* ========================================= */

#define TABLE_IT(alias,table) {#alias, sizeof(#alias)-1, #table, sizeof(#table)-1, 0, 0}

t_table
gp_table[]				 = {TABLE_IT(zz,no_table			),
							TABLE_IT( a,dvd					),
							TABLE_IT( w,dvdaf_user			),
							TABLE_IT( e,folder				),
							TABLE_IT( b,my_dvd				),
							TABLE_IT(b2,my_dvd_2			),
							TABLE_IT( p,pic					),
							TABLE_IT(za,dvd_submit			),
							TABLE_IT(zp,pic_submit			),
							TABLE_IT(pr,price				)};

#undef TABLE_IT

/* ========================================= *\
	Fields and their parameters
\* ========================================= */

static const m_field
_gp_dvd_publisher[]		 = {c_field_a_publisher, c_field_a_country, c_field_a_region_mask, c_field_a_rel_status},
_gp_links[]				 = {c_field_a_imdb_id, c_field_a_asin, c_field_a_amz_country},
_gp_pic[]				 = {c_field_a_pic_status, c_field_a_pic_name, c_field_a_pic_count, c_field_b_pic_overwrite},
_gp_film_rel_dd[]		 = {c_field_a_film_rel_dd},
_gp_title[]				 = {c_field_a_dvd_title, c_field_a_film_rel_year, c_field_b_comments, c_field_b_user_film_rating,
							c_field_b_user_dvd_rating, c_field_a_genre, c_field_b_genre_overwrite, c_field_a_region_mask,
							c_field_a_dvd_rel_dd, c_field_b_folder, c_field_a_media_type, c_field_a_source},										// c_field_a_rel_status
_gp_title_2[]			 = {c_field_a_dvd_title, c_field_a_film_rel_year, c_field_a_region_mask};

#define FIELD_1(table1,table_no,inputmode,width,size,column,label,parms)				 \
											c_field_ ## table1 ## _ ## column			,\
											LETTER_ ## table1							,\
											0											,\
											table_no									,\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											(sizeof(#column) <= 1) ? NULL : (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? (#table1 "_" #column) : #column),\
											(sizeof(#column) <= 1) ? 0    : (sizeof(#column)-1 + (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? 2 : 0)),\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											width										,\
											size										,\
											inputmode									,\
											#label										,\
											sizeof(#label) > 1 ? sizeof(#label)-1 : 0	,

#define FIELD_2(table1,table2,table_no,inputmode,width,size,column,label,parms)			 \
											c_field_ ## table1 ## table2 ## _ ## column	,\
											LETTER_ ## table1							,\
											LETTER_ ## table2							,\
											table_no									,\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											(sizeof(#column) <= 1) ? NULL : (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? (#table1 #table2 "_" #column) : #column),\
											(sizeof(#column) <= 1) ? 0    : (sizeof(#column)-1 + (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? 3 : 0)),\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											width										,\
											size										,\
											inputmode									,\
											#label										,\
											sizeof(#label) > 1 ? sizeof(#label)-1 : 0	,


#define FIELD_P1_o(table1,table_no,width,size,column,label,options,min,max,parms) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}	// to populate t_field
#define FIELD_P1_O(table1,table_no,inputmode,width,size,column,label,options,min,max,parms) {\
											FIELD_1(table1,table_no,inputmode,width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}	// to populate t_field
#define FIELD_P1__(table1,table_no,width,size,column,label,min,max,parms) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}	// to populate t_field
#define FIELD_F1__(table1,table_no,width,size,column,label,min,max,parms,fun,sec,secfd) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL										,\
											0											,\
											fun											,\
											sec											,\
											#secfd										,\
											sizeof(#secfd) > 1 ? sizeof(#secfd)-1 : 0	,\
											c_field_ ## table1 ## _ ## secfd			}
#define FIELD_f1__(table1,table_no,width,size,column,label,min,max,parms,fun,sec) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL										,\
											0											,\
											fun											,\
											sec											,\
											NULL, 0, 0									}
#define FIELD_D1_o(table1,table_no,width,size,column,label,options,min,max,parms,def) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											#def										,\
											sizeof(#def) > 1 ? sizeof(#def)-1 : 0		,\
											NULL, NULL, NULL, 0, 0						}
#define FIELD_D1__(table1,table_no,width,size,column,label,min,max,parms,def) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											#def										,\
											sizeof(#def) > 1 ? sizeof(#def)-1 : 0		,\
											NULL, NULL, NULL, 0, 0						}
#define FIELD_DF1o(table1,table_no,width,size,column,label,options,min,max,parms,def,fun,sec,secfd) {\
											FIELD_1(table1,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											#def										,\
											sizeof(#def) > 1 ? sizeof(#def)-1 : 0		,\
											fun											,\
											sec											,\
											#secfd										,\
											sizeof(#secfd) > 1 ? sizeof(#secfd)-1 : 0	,\
											c_field_ ## table1 ## _ ## secfd			}
#define FIELD_P2_o(table1,table2,table_no,width,size,column,label,options,min,max,parms) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}
#define FIELD_P2_O(table1,table2,table_no,inputmode,width,size,column,label,options,min,max,parms) {\
											FIELD_2(table1,table2,table_no,inputmode,width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}
#define FIELD_P2__(table1,table2,table_no,width,size,column,label,min,max,parms) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}
#define FIELD_F2__(table1,table2,table_no,width,size,column,label,min,max,parms,fun,sec,secfd) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL										,\
											0											,\
											fun											,\
											sec											,\
											#secfd										,\
											sizeof(#secfd) > 1 ? sizeof(#secfd)-1 : 0	,\
											c_field_ ## table1 ## _ ## secfd			}
#define FIELD_f2__(table1,table2,table_no,width,size,column,label,min,max,parms,fun,sec) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											NULL										,\
											0											,\
											fun											,\
											sec											,\
											NULL, 0, 0									}
#define FIELD_D2_o(table1,table2,table_no,width,size,column,label,options,min,max,parms,def) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											options										,\
											min											,\
											max											,\
											#def										,\
											sizeof(#def) > 1 ? sizeof(#def)-1 : 0		,\
											NULL, NULL, NULL, 0, 0						}
#define FIELD_D2__(table1,table2,table_no,width,size,column,label,min,max,parms,def) {\
											FIELD_2(table1,table2,table_no,'-',width,size,column,label,parms)\
											parms										,\
											NULL, 0										,\
											0											,\
											min											,\
											max											,\
											#def										,\
											sizeof(#def) > 1 ? sizeof(#def)-1 : 0		,\
											NULL, NULL, NULL, 0, 0						}
#define FIELD_P2_Z(width,size,column,label,composed,min,max,parms) {\
											c_field_zz_ ## column						,\
											LETTER_z									,\
											LETTER_z									,\
											c_table_no_table							,\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											(sizeof(#column) <= 1) ? NULL : (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? ("zz_" #column) : #column),\
											(sizeof(#column) <= 1) ? 0    : (sizeof(#column)-1 + (((parms) & FIELD_DB_MASK) == FIELD_DB_ALIAS ? 3 : 0)),\
											#column										,\
											sizeof(#column) > 1 ? sizeof(#column)-1 : 0	,\
											width										,\
											size										,\
											'-'											,\
											#label										,\
											sizeof(#label) > 1 ? sizeof(#label)-1 : 0	,\
											FIELD_COMPOSED | (parms)					,\
											composed									,\
											sizeof(composed)/sizeof(int)				,\
											0											,\
											min											,\
											max											,\
											NULL, 0, NULL, NULL, NULL, 0, 0				}	// to populate t_field

const t_field
gp_field[]				 = {
	FIELD_P1__(a  , 1,				1,   1,dvd_id			,DVD id						,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,				1,   1,version_id		,Current version			,   0,    0					,FIELD__INT								|0							),
	FIELD_F1__(a  , 1,TEXTAREA( 7,60),2000,dvd_title		,Title						,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							, NULL   , sec_dvd_title  , dvd_title_nocase),
	FIELD_P1__(a  , 1,				1,2000,dvd_title_nocase	,Title sort string			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_D1__(a  , 1,				4,   4,film_rel_year	,Film release year			,1880, 2020					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,(new Date()).getFullYear()),
	FIELD_F1__(a  , 1,			   20, 500,director			,Director					,   0,   20					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_director		, val_csv, sec_tran_search, director_nocase	),
	FIELD_P1__(a  , 1,				1, 500,director_nocase	,Director sort string		,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_F1__(a  , 1,			   20, 128,publisher		,DVD publisher				,   0,   10					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_dvd_publisher	, val_csv, sec_tran_search, publisher_nocase),
	FIELD_P1__(a  , 1,				1, 128,publisher_nocase	,DVD publisher no case		,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1_o(a  , 1,			   20,  32,orig_language	,Original language			,c_dict_language	   ,0,10,FIELDxcCHAR							|c_format_z_language		),
//	FIELD_D1_o(a  , 1,			   15,  32,country			,DVD country				,c_dict_country		   ,0, 5,FIELDxcCHAR							|c_format_z_country,us		),
	FIELD_DF1o(a  , 1,			   15,  32,country			,DVD country				,c_dict_country		   ,0, 5,FIELDxcCHAR							|c_format_z_country,us		, val_csv, sec_tran_country, country_block  ),
	FIELD_P1__(a  , 1,			    1,  32,country_block	,DVD country block			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,region_mask		,Region						,c_dict_region		   ,0, 0,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|c_format_z_region			),
	FIELD_P1_o(a  , 1,			   32,   1,genre			,Genre						,c_dict_genre		   ,0, 0,FIELDx_INT								|c_format_a_genre			),
	FIELD_P1__(a  , 1,				1,   1,lock_mask		,Lock Mask					,   0,    0					,FIELD__INT								|0							),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,media_type		,Media type					,c_dict_media_type	   ,0, 0,FIELDx_CHAR							|0							),
	FIELD_D1__(a  , 1,				4,   4,num_titles		,Number of titles			,   0, 1000					,FIELD__INT						 		|0,1						),
	FIELD_D1__(a  , 1,				4,   4,num_disks		,Number of discs			,   1, 1000					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,1						),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,source			,Source						,c_dict_source		   ,0, 0,FIELDx_CHAR							|0							),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,rel_status		,DVD release status			,c_dict_release_status ,0, 0,FIELDx_CHAR							|0							),
	FIELD_P1__(a  , 1,			   10,  10,film_rel_dd		,Film release date			,1880, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   10,  10,dvd_rel_dd		,DVD release date			,1990, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   10,  10,dvd_oop_dd		,Out of print date			,1990, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_f1__(a  , 1,			   10, 500,imdb_id			,Imdb links					,   0,   62					,FIELD_sCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_imdb_id			, val_imdb, NULL),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,pic_status		,Picture status				,c_dict_pic_code	   ,0, 0,FIELDx_CHAR							|0							),
	FIELD_P1__(a  , 1,			   16,  16,pic_name			,Picture filename			,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,				1,   1,pic_count		,Number of pictures			,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,				1,   1,film_rating		,Film rating				,  -1,    9					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|c_format_z_rating_film		),
	FIELD_P1__(a  , 1,				1,   1,dvd_rating		,DVD rating					,  -1,    9					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|c_format_z_rating_dvd		),
	FIELD_P1__(a  , 1,				1,   1,film_votes		,Film votes					,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,				1,   1,dvd_votes		,DVD votes					,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   10,  10,list_price		,List price					,   0,10000					,FIELD__DOUB|FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_f1__(a  , 1,			   16, 128,sku				,Studio product code		,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_z_vector			, val_csv, NULL),
	FIELD_f1__(a  , 1,			   16, 128,upc				,UPC						,   0,    0					,FIELD_sCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_z_upc				, val_upc, NULL),
	FIELD_P1__(a  , 1,			   16,  16,asin				,ASIN						,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1_O(a  , 1,USE_DDLB,    32,   1,amz_country		,Amazon country				,c_dict_amz_country	   ,0, 0,FIELDx_CHAR							|0							),
	FIELD_P1__(a  , 1,			   10,  10,best_price		,Best price					,   0,10000					,FIELD__DOUB|FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   16,  16,dvd_created_tm	,Created on					,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(a  , 1,			   16,  16,dvd_updated_tm	,Last updated on			,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(a  , 1,			   20,  32,dvd_updated_by	,Last Updated by			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,				1,   1,dvd_id_merged	,Merged with				,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,TEXTAREA(10,60), 200,last_justify		,Update justification for last version,0,0				,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   20,  32,dvd_verified_by	,Verified by				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(a  , 1,			   16,  16,dvd_verified_tm	,Verified on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(a  , 1,				1,   1,verified_version	,Last verified version		,   0,    0					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|0							),

//	FIELD_P1__(a  , 1,			   1,   1,film_studio		,Film studio										,0,0,0																	),
//	FIELD_P1_I(a  , 1,			  15,	1,film_country		,Film country				,c_dict_country_2		,0,0,FIELDx_INT								|c_format_z_country			),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,status_cd			,Status code				,c_dict_none			,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1__(a  , 1,			  10,  10,expire_dd			,Listing expiration date	,2005, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,expire_reason		,Listing expiration reason	,c_dict_expire_reason	,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1__(a  , 1,			   1,	1,replacement_id	,Replacement id				,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,			   1,	1,title_search		,Title search string		,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,TEXTAREA(3,70), 255,package_title		,Package title				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,TEXTAREA(3,70), 255,package_sufix		,Package sufix				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,TEXTAREA(3,70),2000,package_extras	,Package extras				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,video_format		,Video format				,c_dict_video_format	,0,0,FIELDx_CHAR							|0							),
//	FIELD_F1__(a  , 1,			  20, 500,writer			,Writer						,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_writer			, val_csv, sec_tran_search, writer_sort		),
//	FIELD_P1__(a  , 1,			   1,	1,writer_sort		,Writer sort string			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_F1__(a  , 1,			  20, 500,cast				,Cast						,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_cast			, val_csv, sec_tran_search, cast_sort		),
//	FIELD_P1__(a  , 1,			   1,	1,cast_sort			,Cast sort string			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,			   4,	4,num_episodes		,Number of episodes			,   0, 1000					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,			   1,	1,film_comments		,Number of film comments	,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,			   1,	1,dvd_comments		,Number of DVD comments		,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1_O(a  , 1,			  20,	1,lang_dubbed		,Dubbed language			,c_dict_language		,0,0,FIELDx_CHAR							|c_format_z_language		),
//	FIELD_P1_O(a  , 1,			  20,	1,lang_subtitle		,Subtitle language			,c_dict_language		,0,0,FIELDx_CHAR							|c_format_z_language		),
//	FIELD_P1__(a  , 1,TEXTAREA(5,70),2000,marketing_blurb	,Marketing blurb			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,TEXTAREA(5,70),2000,edition_notes		,Edition notes				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,dvd_type			,DVD type					,c_dict_dvd_type		,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,frame_conversion	,Frame conversion			,c_dict_frame_convers	,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,frame_presentation,Frame presentation			,c_dict_frame_present	,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,frame_alt			,Alternate presentation		,c_dict_frame_alternate	,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1__(a  , 1,			  10,  10,frame_aspect_dvd	,DVD aspect ratio			,   0,   10					,FIELD__DOUB|FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,			  10,  10,frame_aspect_ori	,Original aspect ratio		,   0,   10					,FIELD__DOUB|FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,movie_rating		,Movie rating				,c_dict_movie_rating	,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,authorized		,Authorized					,c_dict_authorized		,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1_O(a  , 1,USE_DDLB	    ,	1,suitability		,Suitability				,c_dict_suitability		,0,0,FIELDx_CHAR							|0							),
//	FIELD_P1__(a  , 1,			  16, 128,isbn				,ISBN						,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
//	FIELD_P1__(a  , 1,TEXTAREA(5,70),2000,moderator_notes	,Moderator notes			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),

	FIELD_P1__(w  , 2,  1,  1,user_id			,User id											,0,0,0										), // varchar(32) binary
	FIELD_P1_o(w  , 2,  1,  1,status_cd			,Status code				,c_dict_none			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(w  , 2,  1,  1,expire_dd			,Listing expiration date							,0,0,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY	|0	), // date
	FIELD_P1_o(w  , 2,  1,  1,expire_reason		,Listing expiration reason	,c_dict_expire_reason	,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(w  , 2,  1,  1,user_name			,User name											,0,0,0										), // varchar(32)
	FIELD_P1__(w  , 2,  1,  1,user_title		,User title											,0,0,0										), // varchar(64)
	FIELD_P1__(w  , 2,  1,  1,option_bits1		,Option flags part 1								,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,option_bits2		,Option flags part 2								,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,option_bits3		,Option flags part 3								,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,page_size			,Page size											,0,0,0										), // smallint unsigned
	FIELD_P1__(w  , 2,  1,  1,password_hash		,Password hash										,0,0,0										), // varchar(32) binary
	FIELD_P1__(w  , 2,  1,  1,password_public	,Password public									,0,0,0										), // varchar(32) binary
	FIELD_P1__(w  , 2,  1,  1,retailer_id		,Retailer id										,0,0,0										), // char(4) binary
	FIELD_P1__(w  , 2,  1,  1,agree_accept_dt	,Agreement acceptance time							,0,0,c_format_z_time						), // datetime
	FIELD_P1__(w  , 2,  1,  1,num_edits			,Number of edits									,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,num_new			,Number of new titles								,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,num_reviews		,Number of reviews									,0,0,0										), // int unsigned
	FIELD_P1__(w  , 2,  1,  1,num_posts			,Number of posts									,0,0,0										), // int unsigned
	FIELD_P1_o(w  , 2,  1,  1,user_group		,User group					,c_dict_none			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(w  , 2,  1,  1,group_begin_dt	,Group begin time									,0,0,c_format_z_time						), // datetime
	FIELD_P1__(w  , 2,  1,  1,group_end_dt		,Group end time										,0,0,c_format_z_time						), // datetime
	FIELD_P1__(w  , 2,  1,  1,font_screen		,Font screen										,0,0,0										), // varchar(64)
	FIELD_P1__(w  , 2,  1,  1,font_screen_small	,Font screen small									,0,0,0										), // varchar(64)
	FIELD_P1__(w  , 2,  1,  1,font_printer		,Font printer										,0,0,0										), // varchar(64)
	FIELD_P1__(w  , 2,  1,  1,font_printer_small,Font printer small									,0,0,0										), // varchar(64)
	FIELD_P1__(w  , 2,  1,  1,updated_tm		,Last updated on									,0,0,c_format_z_time						), // datetime
	FIELD_P1__(w  , 2,  1,  1,created_dt		,Created on											,0,0,c_format_z_time						), // datetime

	FIELD_P1__(e  , 3,  1,  1,user_id			,User id											,0,0,0										), // varchar(32) binary
	FIELD_P1__(e  , 3,  1,  1,folder_id			,Folder id											,0,0,0										), // int unsigned
	FIELD_P1__(e  , 3,  1,  1,folder_name		,Folder name										,0,0,0										), // varchar(255)
	FIELD_P1__(e  , 3,  1,  1,folder_level		,Folder level										,0,0,0										), // tinyint unsigned
	FIELD_P1__(e  , 3,  1,  1,parent_id			,Parent id											,0,0,0										), // int unsigned
	FIELD_P1__(e  , 3,  1,  1,view_folder_id	,View folder id										,0,0,0										), // int unsigned
	FIELD_P1__(e  , 3,  1,  1,view_criteria		,View criteria										,0,0,0										), // varchar(255)
	FIELD_P1__(e  , 3,  1,  1,title				,Title												,0,0,0										), // varchar(255)
	FIELD_P1__(e  , 3,  1,  1,homepage			,Homepage											,0,0,0										), // text
	FIELD_P1__(e  , 3,  1,  1,description		,Description										,0,0,0										), // varchar(255)
	FIELD_P1__(e  , 3,  1,  1,keywords			,Keywords											,0,0,0										), // varchar(255)
	FIELD_P1_o(e  , 3,  1,  1,home_alone		,Home alone					,c_dict_none			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(e  , 3,  1,  1,report_name		,Report name										,0,0,0										), // varchar(32) binary
	FIELD_P1__(e  , 3,  1,  1,template			,Template											,0,0,0										), // text
	FIELD_P1__(e  , 3,  1,  1,title_bits		,Title flags										,0,0,0										), // int unsigned
	FIELD_P1_o(e  , 3,  1,  1,allow_comment		,Allow comment				,c_dict_none			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(e  , 3,  1,  1,num_views			,Num views											,0,0,0										), // int unsigned
	FIELD_P1__(e  , 3,  1,  1,votes_folder		,Votes folder										,0,0,0										), // int unsigned
	FIELD_P1_o(e  , 3,  1,  1,public_ind		,Public indicator			,c_dict_public			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1_o(e  , 3,  1,  1,synchronize_ind	,Synchronize indicator		,c_dict_none			,0,0,FIELDx_CHAR							), // char(1) binary
	FIELD_P1__(e  , 3,  1,  1,sort_order		,Sort order											,0,0,0										), // smallint unsigned
	FIELD_P1__(e  , 3,  1,  1,created_dt		,Created on											,0,0,c_format_z_time						), // datetime
	FIELD_P1__(e  , 3,  1,  1,updated_tm		,Last updated on									,0,0,c_format_z_time						), // datetime

	FIELD_P1__(b  , 4,			   20,  32,user_id			,User id					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(b  , 4,				1,   1,dvd_id			,DVD id						,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(b  , 4,			   20, 200,folder			,Subfolder					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(b  , 4,			   20,  36,sort_text		,Sort text					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1_O(b  , 4,USE_DDLB,    32,   1,public_ind		,Public indicator			,c_dict_public			,0,0,FIELDx_CHAR							|0							),
	FIELD_P1_o(b  , 4,			   15,   1,genre_overwrite	,Genre override				,c_dict_genre			,0,0,FIELDx_INT								|c_format_b_genre			),
	FIELD_P1__(b  , 4,             16,  16,pic_overwrite	,Picture override			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|FIELD_NEED_VIEW_USER		),
	FIELD_P1__(b  , 4,				1,   1,user_film_rating	,Film rating				,  -1,    9					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|c_format_z_stars_film		),
	FIELD_P1__(b  , 4,				1,   1,user_dvd_rating	,DVD rating					,  -1,    9					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|c_format_z_stars_dvd		),
	FIELD_P1__(b  , 4,TEXTAREA( 5,70),4000,comments			,Comments					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|FIELD_NEED_VIEW_USER		),
	FIELD_P1__(b  , 4,			   10,  10,owned_dd			,Date of purchase			,1950, 2020					,FIELD__DA__|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(b  , 4,			   16,  16,my_dvd_created_tm,Created on					,   0,    0					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(b  , 4,			   16,  16,my_dvd_updated_tm,Last updated on			,   0,    0					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(b  , 4,			   16,  16,my_dvd_expire_tm	,Expired time				,   0,    0					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
//	FIELD_P1__(b  , 4,			   1,	1,symlink_id		,Symlink id					,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(b  , 4,			   8,	4,watch_count		,Watch count				,	0,10000					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
//	FIELD_P1__(b  , 4,			  20,  32,location			,Location					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),

	FIELD_P2__(b,2, 5,			   20,  32,user_id			,User id					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,				1,   1,dvd_id			,DVD id						,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   10,  10,last_watched_dd	,Date last watched			,1950, 2020					,FIELD__DA__|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  32,retailer			,Retailer					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   10,  10,price_paid		,Price paid					,   0,10000					,FIELD__DOUB|FIELD_DB_MINUS1_ON_EMPTY	|0							),
	FIELD_P2__(b,2, 5,			   10,  10,order_dd			,Order date					,1950, 2020					,FIELD__DA__|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  16,order_number		,Order number				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2_O(b,2, 5,USE_DDLB,    32,   1,trade_loan		,Trade or loan				,c_dict_trade_loan		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(b,2, 5,			   20,  32,loaned_to		,Loaned to					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   10,  10,loan_dd			,Loan date					,1950, 2020					,FIELD__DA__|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   10,  10,return_dd		,Return date				,1950, 2020					,FIELD__DA__|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   10,  10,asking_price		,Asking price				,   0,10000					,FIELD__DOUB|FIELD_DB_MINUS1_ON_EMPTY	|0							),
	FIELD_P2__(b,2, 5,			   20,  32,custom_1			,Custom 1					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  32,custom_2			,Custom 2					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  32,custom_3			,Custom 3					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  32,custom_4			,Custom 4					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(b,2, 5,			   20,  32,custom_5			,Custom 5					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),

	FIELD_P1__(p  , 6,				1,   1,pic_name			,Picture name				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,				1,   1,version_id		,Current version			,   0,    0					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				1,   1,sub_version_id	,Current subversion			,   0,    0					,FIELD__INT								|0							),
	FIELD_P1_O(p  , 6,USE_RADIO,   32,   1,pic_type			,Picture type				,c_dict_pic_type		,0,0,FIELDx_CHAR							|0							),
	FIELD_P1__(p  , 6,				1, 200,transforms		,Transforms					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,TEXTAREA( 4,60),1000,caption			,Picture caption text		,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,			   32, 100,copy_holder		,Copyright holder			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_D1__(p  , 6,				4,   4,copy_year		,Copyright year				,1880, 2020					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,(new Date()).getFullYear()),
	FIELD_P1_O(p  , 6,USE_RADIO,   32,   1,suitability_cd	,Image suitability			,c_dict_img_suitability	,0,0,FIELDx_CHAR							|0							),
	FIELD_P1__(p  , 6,				1,   1,pic_dx			,Uploaded picture width		,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,				1,   1,pic_dy			,Uploaded picture height	,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,			   16,  16,pic_uploaded_tm	,Uploaded on				,   0,    0					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(p  , 6,			   20,  32,pic_uploaded_by	,Uploader id				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,			   16,  16,pic_edited_tm	,Last edited on				,   0,    0					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(p  , 6,			   20,  32,pic_edited_by	,Last edited by				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,			   16,  16,pic_verified_tm	,Verified on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P1__(p  , 6,			   20,  32,pic_verified_by	,Verified by				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1__(p  , 6,				1,   1,verified_version	,Last verified version		,   0,    0					,FIELD__INT |FIELD_DB_MINUS1_ON_EMPTY	|0							),
	FIELD_P1__(p  , 6,				1,   1,creation_seed	,Creation seed				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P1_O(p  , 6,USE_RADIO,   32,   1,img_treatment	,Treatment					,c_dict_img_treatment	,0,0,FIELDx_CHAR							|0							),
	FIELD_P1__(p  , 6,				5,   8,rot_degrees		,Rotation in degrees		,-360,  360					,FIELD__DOUB							|0							),
	FIELD_P1__(p  , 6,				5,   5,rot_degrees_x	,Rotation in x pixels		,-100,  100					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,crop_x1			,Left margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,crop_x2			,Right margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,crop_y1			,Upper margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,crop_y2			,Lower margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,crop_fuzz		,Autocrop fuzz				,   0,  100					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,black_pt			,Levels black point			,   0,   90					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,white_pt			,Levels white point			,  10,  100					,FIELD__INT								|0							),
	FIELD_P1__(p  , 6,				5,   5,gamma			,Gamma adustment			,   0,    3					,FIELD__DOUB							|0							),

	FIELD_P2__(z,a, 7,				1,	 1,edit_id			,Edit id					,   0,    0					,FIELD__INT								|0							),
	FIELD_P2__(z,a, 7,				1,	 1,dvd_id			,DVD id						,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P2_o(z,a, 7,				1,	 1,request_cd		,Request type				,c_dict_request_dvd		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2_o(z,a, 7,				1,	 1,disposition_cd	,Disposition				,c_dict_disposition		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,a, 7,			   20,  32,proposer_id		,Proposer id				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,TEXTAREA( 5,60),1000,proposer_notes	,Proposer notes				,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,			   16,  16,proposed_tm		,Proposed on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,a, 7,			   16,  16,updated_tm		,Last Updated on			,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,a, 7,			   20,  32,reviewer_id		,Reviewer id				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,TEXTAREA( 5,60),1000,reviewer_notes	,Moderator notes			,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,			   16,  16,reviewed_tm		,Reviewed on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,a, 7,				1,	 1,hist_version_id	,Version					,   0,    0					,FIELD__INT								|0							),
	FIELD_P2__(z,a, 7,TEXTAREA( 7,60),2000,dvd_title		,Title						,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_D2__(z,a, 7,				4,	 4,film_rel_year	,Film release year			,1880, 2020					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,(new Date()).getFullYear()),
	FIELD_f2__(z,a, 7,			   20, 500,director			,Director					,   0,   20					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_director		, val_csv, NULL),
	FIELD_f2__(z,a, 7,			   20, 128,publisher		,DVD publisher				,   0,   10					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_dvd_publisher	, val_csv, NULL),
	FIELD_P2_o(z,a, 7,			   20,	32,orig_language	,Original language			,c_dict_language		,0,0,FIELDxcCHAR							|c_format_z_language		),
	FIELD_D2_o(z,a, 7,			   15,	32,country			,DVD country				,c_dict_country			,0,0,FIELDxcCHAR							|c_format_z_country,us		),
	FIELD_P2__(z,a, 7,				1,	 1,region_mask		,Region						,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|c_format_z_region			),
	FIELD_P2_o(z,a, 7,			   32,	 1,genre			,Genre						,c_dict_genre			,0,0,FIELDx_INT								|c_format_a_genre			),
	FIELD_P2_O(z,a, 7,USE_DDLB,    32,   1,media_type		,Media type					,c_dict_media_type	    ,0,0,FIELDx_CHAR							|0							),
	FIELD_D2__(z,a, 7,				4,	 4,num_titles		,Number of titles			,   0, 1000					,FIELD__INT								|0,1						),
	FIELD_D2__(z,a, 7,				4,	 4,num_disks		,Number of discs			,   1, 1000					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,1						),
	FIELD_P2_O(z,a, 7,USE_DDLB,    32,   1,source			,Source						,c_dict_source		   ,0, 0,FIELDx_CHAR							|0							),
	FIELD_P2_O(z,a, 7,USE_DDLB,    32,	 1,rel_status		,DVD release status			,c_dict_release_status	,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,a, 7,			   10,  10,film_rel_dd		,Film release date			,1880, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,			   10,  10,dvd_rel_dd		,DVD release date			,1990, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,a, 7,			   10,  10,dvd_oop_dd		,Out of print date			,1990, 2020					,FIELD__DATE|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_f2__(z,a, 7,			   10, 500,imdb_id			,Imdb links					,   0,   62					,FIELD_sCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_a_imdb_id			, val_imdb, NULL),
	FIELD_P2__(z,a, 7,			   10,  10,list_price		,List price					,   0,10000					,FIELD__DOUB|FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_f2__(z,a, 7,			   16, 128,sku				,Studio product code		,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_z_vector			, val_csv, NULL),
	FIELD_f2__(z,a, 7,			   16, 128,upc				,UPC						,   0,    0					,FIELD_sCHAR|FIELD_DB_DASH_ON_EMPTY		|c_format_z_upc				, val_upc, NULL),
	FIELD_P2__(z,a, 7,			   16,  16,asin				,ASIN						,   0,    0					,FIELD_cCHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2_O(z,a, 7,USE_DDLB,    32,	 1,amz_country		,Amazon country				,c_dict_amz_country		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,a, 7,TEXTAREA(10,60), 200,update_justify	,Update justification		,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),

	FIELD_P2__(z,p, 8,				1,	 1,pic_edit_id		,Picture edit id			,   0,    0					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				1,   1,pic_name			,Picture name				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2_o(z,p, 8,				1,	 1,request_cd		,Request type				,c_dict_request_pic		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2_o(z,p, 8,				1,	 1,disposition_cd	,Disposition				,c_dict_disposition		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,p, 8,			   20,  32,proposer_id		,Proposer id				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,TEXTAREA( 5,60),1000,proposer_notes	,Proposer notes				,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,			   16,  16,proposed_tm		,Proposed on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,p, 8,			   16,  16,updated_tm		,Last Updated on			,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,p, 8,			   20,  32,reviewer_id		,Reviewer id				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,TEXTAREA( 5,60),1000,reviewer_notes	,Moderator notes			,	0,	  0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,			   16,  16,reviewed_tm		,Reviewed on				,1999, 2020					,FIELD__DATE|FIELD_DB_NULL_ON_EMPTY		|c_format_z_time			),
	FIELD_P2__(z,p, 8,			   20,  64,uploaded_pic		,Uploaded file				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,				1,	 1,hist_version_id	,Version					,   0,    0					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				1,	 1,hist_subversion_id,Subversion				,   0,    0					,FIELD__INT								|0							),
	FIELD_P2_O(z,p, 8,USE_RADIO,   32,   1,pic_type			,Picture type				,c_dict_pic_type		,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,p, 8,				1,   1,transforms		,Transforms					,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,TEXTAREA( 4,60),1000,caption			,Picture caption text		,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,			   32, 100,copy_holder		,Copyright holder			,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_D2__(z,p, 8,				4,   4,copy_year		,Copyright year				,1880, 2020					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0,(new Date()).getFullYear()),
	FIELD_P2_O(z,p, 8,USE_RADIO,   32,   1,suitability_cd	,Image suitability			,c_dict_img_suitability	,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,p, 8,				1,   1,pic_dx			,Uploaded picture width		,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,				1,   1,pic_dy			,Uploaded picture height	,   0,    0					,FIELD__INT |FIELD_DB_ZERO_ON_EMPTY		|0							),
	FIELD_P2__(z,p, 8,				1,   1,creation_seed	,Creation seed				,   0,    0					,FIELD__CHAR|FIELD_DB_DASH_ON_EMPTY		|0							),
	FIELD_P2_O(z,p, 8,USE_RADIO,   32,   1,img_treatment	,Treatment					,c_dict_img_treatment	,0,0,FIELDx_CHAR							|0							),
	FIELD_P2__(z,p, 8,				5,   8,rot_degrees		,Rotation in degrees		,-360,  360					,FIELD__DOUB							|0							),
	FIELD_P2__(z,p, 8,				5,   5,rot_degrees_x	,Rotation in x pixels		,-100,  100					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,crop_x1			,Left margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,crop_x2			,Right margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,crop_y1			,Upper margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,crop_y2			,Lower margin crop			,   0, 2000					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,crop_fuzz		,Autocrop fuzz				,   0,  100					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,black_pt			,Levels black point			,   0,   90					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,white_pt			,Levels white point			,  10,  100					,FIELD__INT								|0							),
	FIELD_P2__(z,p, 8,				5,   5,gamma			,Gamma adustment			,   0,    3					,FIELD__DOUB							|0							),

	FIELD_P2__(p,r, 9,  1,  1,upc				,UPC												,0,0,c_format_z_upc						),
	FIELD_P2__(p,r, 9,  1,  1,price_00			,Vendor 0 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_01			,Vendor 1 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_02			,Vendor 2 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_03			,Vendor 3 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_04			,Vendor 4 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_05			,Vendor 5 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_06			,Vendor 6 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_07			,Vendor 7 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_08			,Vendor 8 price										,0,0,0									),
	FIELD_P2__(p,r, 9,  1,  1,price_09			,Vendor 9 price										,0,0,0									),

	FIELD_P2_Z(         1,  1,check				,Select						,NULL					,0,0,FIELD_NEED_DVD_ID|c_format_z_check		), // 
	FIELD_P2_Z(         1,  1,dvd_publisher		,DVD publisher				,_gp_dvd_publisher		,0,0,c_format_z_dvd_publisher				), // 
//	FIELD_P2_Z(         1,  1,expire_dd			,Listing expiration date	,_gp_expire				,0,0,c_format_z_expire_dd					), // 
	FIELD_P2_Z(         1,  1,links				,Links						,_gp_links				,0,0,FIELD_NEED_DVD_ID|c_format_z_links		), // 
	FIELD_P2_Z(         1,  1,med_pic			,Picture					,_gp_pic				,0,0,FIELD_NEED_DVD_ID|c_format_z_med_pic	), // 
	FIELD_P2_Z(         1,  1,pda_pic			,Picture					,_gp_pic				,0,0,FIELD_NEED_DVD_ID|c_format_z_pda_pic	), // 
	FIELD_P2_Z(         1,  1,row_number		,Row Number					,NULL					,0,0,FIELD_NEED_ROW_NO|c_format_z_row_number), // 
	FIELD_P2_Z(         1,  1,screening			,Film release date			,_gp_film_rel_dd		,0,0,c_format_z_release_dd					), // 
	FIELD_P2_Z(         1,  1,small_pic			,Picture					,_gp_pic				,0,0,FIELD_NEED_DVD_ID|c_format_z_small_pic	), // 
	FIELD_P2_Z(         1,  1,text				,Text						,NULL					,0,0,c_format_z_text						), // 
	FIELD_P2_Z(         1,  1,title				,Title						,_gp_title				,0,0,c_format_z_title						), //
	FIELD_P2_Z(         1,  1,title_2			,Title						,_gp_title_2			,0,0,c_format_z_title_2						), //
	FIELD_P2_Z(         1,  1,cart				,Cart						,NULL					,0,0,FIELD_NEED_DVD_ID|c_format_z_cart		), //
	FIELD_P2_Z(         1,  1,price_comparison	,Price Comparison			,NULL					,0,0,c_format_z_price_comp					), //
	FIELD_P2_Z(         1,  1,best_price		,Best						,NULL					,0,0,FIELD_DB_ZERO_ON_EMPTY|c_format_z_best_price	)}; 

static const t_string
gp_hoz_align[]			=  {STR_AND_LEN(" align='left'"		),
							STR_AND_LEN(" align='center'"	),
							STR_AND_LEN(" align='right'"	),
							STR_AND_LEN(" align='justify'"	)},
gp_ver_align[]			=  {STR_AND_LEN(" valign='top'"		),
							STR_AND_LEN(" valign='middle'"	),
							STR_AND_LEN(" valign='bottom'"	)};

const int
gn_field_count			 = sizeof(gp_field) / sizeof(t_field),
gn_table_count			 = sizeof(gp_table) / sizeof(t_table);

/* ========================================================================================= */

#endif	/* DVDAF_FIELD_GLOBALS_H */
