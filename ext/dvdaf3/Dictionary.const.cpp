#include "Dictionary.h"

#define DICT_1_(code,desc)		{(unsigned int)(code),{SS(#desc)}}
#define DICT_1c(code,desc)		{(unsigned int)(code),{SS(desc)}}
#define DICT_2_(c1,c2,desc)		{(unsigned int)(CHAR2_TO_INT_(c1,c2)),{SS(#desc)}}
#define DICT_2c(c1,c2,desc)		{(unsigned int)(CHAR2_TO_INT_(c1,c2)),{SS(desc)}}
#define DICT_I_(code,desc)		{(unsigned int)(code),{SS(#desc)}}
#define DICT_Ic(code,desc)		{(unsigned int)(code),{SS(desc)}}

const CDictionary::t_option
/*
	+------------------+------------------+
	| CDictionary      | decodes table    |
	+------------------+------------------+
	| amz_country      |                  |
	| dvd_country      | country          |
	| disposition      | disposition_cd   |
	| expire_reason    |                  |
	| feature_cd       |                  |
	| frame_conversion |                  |
	| img_suitability  | img_suitability  |
	| img_treatment    | img_treatment    |
	| language         | language         |
	| media_type       | media_type       |
	| pic_code         |                  |
	| pic_type         | pic_type         |
	| public           |                  |
	| film_rating      |                  |
	| region           | region           |
	| release_status   |                  |
	| request_dvd      | (request_cd)     |
	| request_film     | (request_cd)     |
	| request_person   | (request_cd)     |
	| request_pub      | (request_cd)     |
	| request_pic      | request_cd (pic) |
	| person_role      |                  |
	| role_dir         |                  |
	| role_cast        |                  |
	| role_crew        |                  |
	| sound_system     |                  |
	| source           | source           |
	| surround_mode    |                  |
	| trade_loan       |                  |
	| video_mode       |                  |
	| yes_no           |                  |
	| genre            | genre            |
	| genre_lower      | genre_lower      |
	| birth_country    |                  |
	|                  | obj_type         |
	|                  | membership_cd    |
	+------------------+------------------+
*/
CDictionary::___amz_country[] = {
	DICT_1_('-',U.S.											),
	DICT_1_('C',Canada											),
	DICT_1_('D',Germany											),
	DICT_1_('F',France											),
	DICT_1_('I',Italy											),
	DICT_1_('E',Spain											),
	DICT_1_('J',Japan											),
	DICT_1_('K',U.K.											)},

CDictionary::___dvd_country[] = {									// table decodes: country
	DICT_2_(a,r,Argentina										),
	DICT_2_(a,t,Austria											),
	DICT_2_(a,u,Australia										),
	DICT_2_(b,e,Belgium											),
	DICT_2_(b,r,Brazil											),
	DICT_2_(c,a,Canada											),
	DICT_2_(c,h,Switzerland										),
	DICT_2_(c,l,Chile											),
	DICT_2_(c,n,China											),
	DICT_2_(c,u,Cuba											),
	DICT_2_(c,z,Czech Republic									),
	DICT_2_(d,e,Germany											),
	DICT_2_(d,k,Denmark											),
	DICT_2_(e,e,Estonia											),
	DICT_2_(e,s,Spain											),
	DICT_2_(f,i,Finland											),
	DICT_2_(f,r,France											),
	DICT_2_(g,r,Greece											),
	DICT_2_(h,k,Hong Kong										),
	DICT_2_(h,r,Croatia											),
	DICT_2_(h,u,Hungary											),
	DICT_2_(i,d,Indonesia										),
	DICT_2_(i,l,Israel											),
	DICT_2_(i,n,India											),
	DICT_2_(i,s,Iceland											),
	DICT_2_(i,t,Italy											),
	DICT_2_(j,p,Japan											),
	DICT_2_(k,r,South Korea										),
	DICT_2_(l,t,Lithuania										),
	DICT_2_(m,k,Macedonia										),
	DICT_2_(m,x,Mexico											),
	DICT_2_(m,y,Malaysia										),
	DICT_2_(n,l,Netherlands										),
	DICT_2_(n,o,Norway											),
	DICT_2_(n,z,New Zealand										),
	DICT_2_(p,h,Philippines										),
	DICT_2_(p,l,Poland											),
	DICT_2_(p,t,Portugal										),
	DICT_2_(r,o,Romania											),
	DICT_2_(r,s,Serbia											),
	DICT_2_(r,u,Russian Federation								),
	DICT_2_(s,e,Sweden											),
	DICT_2_(s,g,Singapore										),
	DICT_2_(s,i,Slovenia										),
	DICT_2_(s,k,Slovakia										),
	DICT_2_(t,h,Thailand										),
	DICT_2_(t,r,Turkey											),
	DICT_2_(t,w,Taiwan											),
	DICT_2_(u,k,U.K.											),
	DICT_2_(u,n,Unknown Country									),
	DICT_2_(u,s,U.S.											),
	DICT_2_(z,a,South Africa									)},

CDictionary::___disposition[] = {									// table decodes: disposition_cd
	DICT_1_('A',Approved										),
	DICT_1_('P',Partially approved								),
	DICT_1_('R',Declined										),
	DICT_1_('W',Withdrawn										),
	DICT_1_('X',Expired											),
	DICT_1_('-',Not processed									)},

CDictionary::___expire_reason[] = {
	DICT_1_('P',Missing picture									),
	DICT_1_('-',Not expired										)},

CDictionary::___feature_cd[] = {
	DICT_1_('-',Full length										),
	DICT_1_('S',Short											),
	DICT_1_('E',Episode											),
	DICT_1_('D',Documentary										),
	DICT_1_('C',Container for series							),
	DICT_1_('O',Other											)},

CDictionary::___frame_conversion[] = {
	DICT_1c('1',"Original (within 97%)"							),
	DICT_1_('L',Letterboxed										),
	DICT_1_('P',Pan &amp; scan									),
	DICT_1_('R',Reverse &amp; and scan							),
	DICT_1_('C',Cropped											),
	DICT_1_('O',Open-matted										),
	DICT_1_('-',Undefined										)},

CDictionary::___img_suitability[] = {								// table decodes: img_suitability
	DICT_1_('-',Unrestricted									),
	DICT_1_('X',NC-17											)},

CDictionary::___img_treatment[] = {									// table decodes: img_treatment
	DICT_1_('B',DVD												),
	DICT_1_('H',HD DVD											),
	DICT_1_('R',Blu-ray											),
	DICT_1_('O',No border										),
	DICT_1_('K',Keep ratio										),
	DICT_1_('F',16:9 frame										)},

CDictionary::___language[] = {										// table decodes: language
	DICT_2_(a,m,Armenian										),
	DICT_2_(a,r,Arabic											),
	DICT_2_(b,g,Bulgarian										),
	DICT_2_(b,n,Indian-Bengali									),
	DICT_2_(b,r,Portuguese-Brazilian							),
	DICT_2_(c,a,French-Canadian									), // deprecated
	DICT_2_(c,s,Chinese-Shanghainese							),
	DICT_2_(c,t,Chinese-Cantonese								),
	DICT_2_(c,z,Czech											),
	DICT_2_(d,e,German											),
	DICT_2_(d,k,Danish											),
	DICT_2_(e,n,English											),
	DICT_2_(e,o,Esperanto										),
	DICT_2_(e,s,Spanish											),
	DICT_2_(e,t,Estonian										),
	DICT_2_(f,a,Farsi											),
	DICT_2_(f,i,Finnish											),
	DICT_2_(f,r,French											),
	DICT_2_(g,e,Georgian										),
	DICT_2_(g,r,Greek											),
	DICT_2_(h,e,Hebrew											),
	DICT_2_(h,i,Indian-Hindi									),
	DICT_2_(h,o,Chinese-Hokkien									),
	DICT_2_(h,u,Hungarian										),
	DICT_2_(i,d,Bahasa-Indonesia								),
	DICT_2_(i,l,Yiddish											),
	DICT_2_(i,n,Indian-Others									),
	DICT_2_(i,s,Icelandic										),
	DICT_2_(i,t,Italian											),
	DICT_2_(j,p,Japanese										),
	DICT_2_(k,h,Khmer											),
	DICT_2_(k,l,Klingon											), // deprecated
	DICT_2_(k,r,Korean											),
	DICT_2_(k,u,Kurdish											),
	DICT_2_(k,z,Kazakh											),
	DICT_2_(l,a,Latin											),
	DICT_2_(l,t,Lithuanian										),
	DICT_2_(l,v,Latvian											),
	DICT_2_(m,a,Chinese-Mandarin								),
	DICT_2_(m,k,Macedonian										),
	DICT_2_(m,l,Indian-Malayalam								),
	DICT_2_(m,n,Mongolian										),
	DICT_2_(m,y,Bahasa-Malaysia									),
	DICT_2_(n,l,Dutch											),
	DICT_2_(n,o,Norwegian										),
	DICT_2_(n,z,Aramaic											),
	DICT_2_(o,t,Other											),
	DICT_2_(p,h,Filipino										),
	DICT_2_(p,l,Polish											),
	DICT_2_(p,t,Portuguese										),
	DICT_2_(p,u,Indian-Punjabi									),
	DICT_2_(r,m,Romani											),
	DICT_2_(r,o,Romanian										),
	DICT_2_(r,u,Russian											),
	DICT_2_(s,c,Serbo-Croatian									),
	DICT_2_(s,e,Swedish											),
	DICT_2_(s,i,Slovenian										),
	DICT_2_(s,k,Slovak											),
	DICT_2_(s,l,Silent											),
	DICT_2_(t,a,Indian-Tamil									),
	DICT_2_(t,e,Indian-Telugu									),
	DICT_2_(t,h,Thai											),
	DICT_2_(t,r,Turkish											),
	DICT_2_(t,w,Chinese-Taiwanese								),
	DICT_2_(u,k,Ukrainian										),
	DICT_2_(u,n,Unknown Language								),
	DICT_2_(u,r,Indian-Urdu										),
	DICT_2_(v,e,Catalan											),
	DICT_2_(v,i,Vietnamese										)},

CDictionary::___media_type[] = {									// table decodes: media_type
	DICT_1_('D',DVD												),
	DICT_1_('B',Blu-ray											),
	DICT_1_('3',Blu-ray 3D										),
	DICT_1_('2',Blu-ray/DVD Combo								),
	DICT_1_('R',BD-R											),
	DICT_1_('V',DVD-R											),
	DICT_1_('H',HD DVD											),
	DICT_1_('C',HD DVD/DVD Combo								),
	DICT_1_('T',HD DVD/DVD TWIN Format							),
	DICT_1_('A',DVD Audio										),
	DICT_1_('P',Placeholder										),
	DICT_1_('F',Film											),
	DICT_1_('S',Short											),
	DICT_1_('L',Television										),
	DICT_1_('E',Featurette										),
	DICT_1_('N',Events &amp; Performances						),
	DICT_1_('O',Other											)},

CDictionary::___pic_code[] = {
	DICT_1_('Y',Present											),
	DICT_1_('P',Processing										),
	DICT_1_('-',Missing											)},

CDictionary::___pic_type[] = {										// table decodes: pic_type
	DICT_1_('D',Cover Art										),
	DICT_1_('I',Bonus Items										),
	DICT_1_('P',Movie Poster									),
	DICT_1_('F',Screen Capture									),
	DICT_1_('G',Fan-Created Cover Art							),
	DICT_1_('B',Backstage Pictures								),
	DICT_1_('C',Casting Pictures								),
	DICT_1_('E',Events											)},

CDictionary::___public[] = {
	DICT_1_('Y',Public											),
	DICT_1_('N',Private											)},

/*	generating codes for rating entity so that they remain alphabetical and numerically ascending:
	1st letter	2nd letter
		us	10000					A	10500					B	11000
		C	11500					D	12000					E	12500
		F	13000					G	13500					H	14000
		I	14500					J	15000					K	15500
		L	16000					M	16500					N	17000
		O	17500					P	18000					Q	18500
		R	19000					S	19500					T	20000
		U	20500					V	21000					W	21500
		X	22000					Y	22500					Z	23000
*/
CDictionary::___film_rating[] = {
	DICT_I_(    0,Unknown										),
	DICT_I_(    1,Not Rated										),
	DICT_I_(10010,U.S. / G										),
	DICT_I_(10020,U.S. / PG										),
	DICT_I_(10030,U.S. / PG-13									),
	DICT_I_(10040,U.S. / R										),
	DICT_I_(10050,U.S. / NC-17									),
	DICT_I_(10060,U.S. / M										),
	DICT_I_(10070,U.S. / GP										),
	DICT_I_(10080,U.S. / SMA									),
	DICT_I_(10090,U.S. / X										),
	DICT_I_(10910,Australia / E									),
	DICT_I_(10920,Australia / G									),
	DICT_I_(10930,Australia / PG								),
	DICT_I_(10940,Australia / M									),
	DICT_I_(10950,Australia / MA15+								),
	DICT_I_(10960,Australia / R18+								),
	DICT_I_(10970,Australia / X18+								),
	DICT_I_(10980,Australia / RC								),
	DICT_I_(11510,Canada / G									),
	DICT_I_(11520,Canada / PG									),
	DICT_I_(11530,Canada / 14A									),
	DICT_I_(11540,Canada / 18A									),
	DICT_I_(11550,Canada / R									),
	DICT_I_(11560,Canada / A									),
	DICT_I_(20710,U.K. / U										),
	DICT_I_(20720,U.K. / PG										),
	DICT_I_(20730,U.K. / 12A									),
	DICT_I_(20740,U.K. / 12										),
	DICT_I_(20750,U.K. / 15										),
	DICT_I_(20760,U.K. / 18										),
	DICT_I_(20770,U.K. / R18									)},

CDictionary::___region[] = {										// table decodes: region
	DICT_1c('0',"0: Plays on any player"						),
	DICT_1c('1',"1: US and Canada"								),
	DICT_1c('2',"2: Europe, Middle East, Japan and South Africa"),
	DICT_1c('3',"3: Southeast Asia"								),
	DICT_1c('4',"4: Australia, New Zealand and Latin America"	),
	DICT_1c('5',"5: Africa, Eastern Europe and the rest of Asia"),
	DICT_1c('6',"6: China and Hong Kong"						),
	DICT_1c('A',"A: Americas, Japan, Korea and Southeast Asia"	),
	DICT_1c('B',"B: Europe, Australia, New Zealand and Africa"	),
	DICT_1c('C',"C: Eastern Europe and the rest of Asia"		),
	DICT_1c('-',"Unknown"										)},

CDictionary::___release_status[] = {
	DICT_1_('C',Current											),
	DICT_1_('O',Out of print									),
	DICT_1_('A',Announced										),
	DICT_1_('N',Not announced									),
	DICT_1_('D',Release delayed									),
	DICT_1_('X',Release cancelled								),
	DICT_1_('-',Unknown											)},

CDictionary::___request_dvd[] = {									// table decodes: (outdated "request_cd")
	DICT_1_('E',Change request									),
	DICT_1_('N',New DVD proposal								),
	DICT_1_('D',Title deletion request							),
	DICT_1_('-',Missing											)},

CDictionary::___request_film[] = {									// table decodes: (outdated "request_cd")
	DICT_1_('E',Change request									),
	DICT_1_('N',New film proposal								),
	DICT_1_('D',Title deletion request							),
	DICT_1_('-',Missing											)},

CDictionary::___request_person[] = {								// table decodes: (outdated "request_cd")
	DICT_1_('E',Change request									),
	DICT_1_('N',New person proposal								),
	DICT_1_('D',Title deletion request							),
	DICT_1_('-',Missing											)},

CDictionary::___request_pub[] = {									// table decodes: (outdated "request_cd")
	DICT_1_('E',Change request									),
	DICT_1_('N',New publisher proposal							),
	DICT_1_('D',Publisher deletion request						),
	DICT_1_('-',Missing											)},

CDictionary::___request_pic[] = {									// table decodes: request_cd (pic)
	DICT_1_('E',Change picture proposal							),
	DICT_1_('N',New picture proposal							),
	DICT_1_('R',Replace picture proposal						),
	DICT_1_('D',Delete picture proposal							),
	DICT_1_('-',Missing											)},

CDictionary::___person_role[] = {
	DICT_1_('d',Director										),
	DICT_1_('c',Cast											),
	DICT_1_('e',Crew											)},

CDictionary::___role_dir[] = {
	DICT_1_('D',Director										),
	DICT_1_('U',Guest director									)},

CDictionary::___role_cast[] = {
	DICT_1_('1',Principal										),
	DICT_1_('S',Supporting										),
	DICT_1_('G',Guest star										),
	DICT_1_('C',Cameo											),
	DICT_1_('X',Extra											)},

CDictionary::___role_crew[] = {
	DICT_1_('P',Producer										),
	DICT_1_('W',Writer											),
	DICT_1_('I',Cinematographer									),
	DICT_1_('M',Composer										),
	DICT_1_('O',Other											)},

CDictionary::___sound_system[] = {
	DICT_1c('1',"MPEG-1 Audio Layer II (MP2)"					),
	DICT_1_('A',Dolby Digital AC-3								),
	DICT_1_('X',Dolby Digital EX								),
	DICT_1_('P',Dolby Digital Plus								),
	DICT_1_('T',Dolby TrueHD									),
	DICT_1_('C',PCM												),
	DICT_1_('L',"Linear (uncompressed) PCM"						),
	DICT_1_('D',DTS												),
	DICT_1_('H',DTS-HD High Resolution Audio					),
	DICT_1_('M',DTS-HD Master Audio								),
	DICT_1_('-',Unknown											)},

CDictionary::___source[] = {										// table decodes: source
	DICT_1_('A',DVD Package										),
	DICT_1_('I',Part of DVD Package								),
	DICT_1_('E',DVD Package Bonus Disc							),
	DICT_1_('C',Audio CD Bonus Disc								),
	DICT_1_('G',Game Bonus Disc									),
	DICT_1_('B',Book Bonus Disc									),
	DICT_1_('M',Magazine Bonus Disc								),
	DICT_1_('O',Other Product Bonus Disc						),
	DICT_1_('T',Theatrical or Broadcast							)},

CDictionary::___surround_mode[] = {
	DICT_1_('1',1.0 mono										),
	DICT_1_('2',2.0 stereo										),
	DICT_1_('3',3.0 channel surround							),
	DICT_1_('4',4.0 channel surround							),
	DICT_1_('5',5.1 channel surround							),
	DICT_1_('6',6.1 channel surround							),
	DICT_1_('7',7.1 channel surround							),
	DICT_1_('-',Undefined										)},

CDictionary::___trade_loan[] = {
	DICT_1_('L',On Loan											),
	DICT_1_('T',For Trade										),
	DICT_1_('-',Neither											)},

CDictionary::___video_mode[] = {
	DICT_1c('N',"480i (NTSC)"									),
	DICT_1c('A',"576i (PAL)"									),
	DICT_1_('P',1080p											),
	DICT_1_('I',1080i											),
	DICT_1_('7',720p											),
	DICT_1_('4',480p											),
	DICT_1_('-',Undefined										)},

CDictionary::___yes_no[] = {
	DICT_1_('Y',Yes												),
	DICT_1_('N',No												)},

CDictionary::___genre[] = {											// table decodes: genre
	DICT_I_(10000, Action-Adventure + Subgenres					),
	DICT_I_(10100, Action-Adventure / Comedy					),
	DICT_I_(10200, Action-Adventure / Crime						),
	DICT_I_(10300, Action-Adventure / Disaster					),
	DICT_I_(10400, Action-Adventure / Epic						),
	DICT_I_(10500, Action-Adventure / Espionage					),
	DICT_I_(10600, Action-Adventure / Martial Arts				),
	DICT_I_(10700, Action-Adventure / Military					),
	DICT_I_(10750, Action-Adventure / Samurai					),
	DICT_I_(10800, Action-Adventure / Superheroes				), /* deprecated */
	DICT_I_(10999, Action-Adventure								),
	DICT_I_(13000, Animation + Subgenres						),
	DICT_I_(13100, Animation / Cartoons							),
	DICT_I_(13300, Animation / Family							),
	DICT_I_(13600, Animation / Mature							),
	DICT_I_(13700, Animation / Puppetry &amp; Stop-Motion		),
	DICT_I_(13800, Animation / Sci-Fi							),
	DICT_I_(13900, Animation / Superheroes						),
	DICT_I_(13999, Animation									),
	DICT_I_(16000, Anime + Subgenres							),
	DICT_I_(16200, Anime / Action								),
	DICT_I_(16250, Anime / Comedy								),
	DICT_I_(16300, Anime / Drama								),
	DICT_I_(16400, Anime / Fantasy								),
	DICT_I_(16500, Anime / Horror								),
	DICT_I_(16600, Anime / Mahou Shoujo (Magical Girls)			),
	DICT_I_(16700, Anime / Martial Arts							),
	DICT_I_(16750, Anime / Mecha (Giant Robots)					),
	DICT_I_(16800, Anime / Mo&#233; (Cute Girls, Romance)		),
	DICT_I_(16850, Anime / Romance								),
	DICT_I_(16900, Anime / Sci-Fi								),
	DICT_I_(16999, Anime										),
	DICT_I_(20000, Comedy + Subgenres							),
	DICT_I_(20100, Comedy / Dark								),
	DICT_I_(20200, Comedy / Farce								),
	DICT_I_(20300, Comedy / Horror								),
	DICT_I_(20400, Comedy / Romantic							),
	DICT_I_(20600, Comedy / Satire								),
	DICT_I_(20650, Comedy / Sci-Fi								),
	DICT_I_(20700, Comedy / Screwball							),
	DICT_I_(20750, Comedy / Sitcom								),
	DICT_I_(20800, Comedy / Sketches &amp; Stand-Up				),
	DICT_I_(20850, Comedy / Slapstick							),
	DICT_I_(20900, Comedy / Teen								),
	DICT_I_(20999, Comedy										),
	DICT_I_(24000, Documentary + Subgenres						),
	DICT_I_(24100, Documentary / Biography						),
	DICT_I_(24200, Documentary / Crime							),
	DICT_I_(24250, Documentary / Culture						),
	DICT_I_(24270, Documentary / Entertainment					),
	DICT_I_(24300, Documentary / History						),
	DICT_I_(24400, Documentary / Nature							),
	DICT_I_(24500, Documentary / Propaganda						),
	DICT_I_(24600, Documentary / Religion						),
	DICT_I_(24700, Documentary / Science						),
	DICT_I_(24750, Documentary / Social							),
	DICT_I_(24800, Documentary / Sports							),
	DICT_I_(24900, Documentary / Travel							),
	DICT_I_(24999, Documentary									),
	DICT_I_(28000, Drama + Subgenres							),
	DICT_I_(28100, Drama / Courtroom							),
	DICT_I_(28150, Drama / Crime								),
	DICT_I_(28200, Drama / Docudrama							),
	DICT_I_(28400, Drama / Melodrama							),
	DICT_I_(28600, Drama / Period								),
	DICT_I_(28800, Drama / Romance								),
	DICT_I_(28900, Drama / Sports								),
	DICT_I_(28950, Drama / War									),
	DICT_I_(28999, Drama										),
	DICT_I_(32000, Educational + Subgenres						),
	DICT_I_(32200, Educational / Children						),
	DICT_I_(32700, Educational / School							),
	DICT_I_(32999, Educational									),
	DICT_I_(36000, Erotica + Subgenres							),
	DICT_I_(36100, Erotica / Hentai								),
	DICT_I_(36999, Erotica										),
	DICT_I_(39999, Experimental									),
	DICT_I_(41000, Exploitation + Subgenres						),
	DICT_I_(41100, Exploitation / Blaxploitation				),
	DICT_I_(41300, Exploitation / Nazisploitation				),
	DICT_I_(41400, Exploitation / Nunsploitation				),
	DICT_I_(41500, Exploitation / Pinku Eiga					),
	DICT_I_(41600, Exploitation / Sexploitation					),
	DICT_I_(41700, Exploitation / Shockumentary					),
	DICT_I_(41800, Exploitation / WIP							),
	DICT_I_(41999, Exploitation									),
	DICT_I_(43999, Fantasy										),
	DICT_I_(47999, Film Noir									),
	DICT_I_(51000, Foreign + Subgenres							), /* deprecated */
	DICT_I_(51100, Foreign / Brazil								), /* deprecated */
	DICT_I_(51150, Foreign / China								), /* deprecated */
	DICT_I_(51200, Foreign / Netherlands						), /* deprecated */
	DICT_I_(51250, Foreign / Eastern Europe						), /* deprecated */
	DICT_I_(51300, Foreign / France								), /* deprecated */
	DICT_I_(51350, Foreign / Germany							), /* deprecated */
	DICT_I_(51400, Foreign / Hong Kong							), /* deprecated */
	DICT_I_(51450, Foreign / India								), /* deprecated */
	DICT_I_(51500, Foreign / Italy								), /* deprecated */
	DICT_I_(51550, Foreign / Japan								), /* deprecated */
	DICT_I_(51570, Foreign / South Korea						), /* deprecated */
	DICT_I_(51600, Foreign / Mexico								), /* deprecated */
	DICT_I_(51650, Foreign / Middle East						), /* deprecated */
	DICT_I_(51700, Foreign / Portugal							), /* deprecated */
	DICT_I_(51750, Foreign / Russia								), /* deprecated */
	DICT_I_(51780, Foreign / Scandinavia						), /* deprecated */
	DICT_I_(51790, Foreign / Spain								), /* deprecated */
	DICT_I_(51800, Foreign / Latin America						), /* deprecated */
	DICT_I_(51850, Foreign / Sweden								), /* deprecated */
	DICT_I_(51900, Foreign / Taiwan								), /* deprecated */
	DICT_I_(51999, Foreign										), /* deprecated */
	DICT_I_(55000, Horror + Subgenres							),
	DICT_I_(55050, Horror / Anthology							),
	DICT_I_(55100, Horror / Asian								), /* deprecated */
	DICT_I_(55250, Horror / Creature &amp; Animal				),
	DICT_I_(55300, Horror / ESP &amp; Ghosts					),
	DICT_I_(55350, Horror / Eurotrash							),
	DICT_I_(55400, Horror / Exploitation						),
	DICT_I_(55450, Horror / Gialli								),
	DICT_I_(55500, Horror / Gore &amp; Shock					),
	DICT_I_(55550, Horror / Gothic								),
	DICT_I_(55700, Horror / Possession &amp; Satan				),
	DICT_I_(55800, Horror / Shockumentary						),
	DICT_I_(55850, Horror / Slasher &amp; Survival				),
	DICT_I_(55900, Horror / Vampires							),
	DICT_I_(55950, Horror / Zombies &amp; Infected				),
	DICT_I_(55960, Horror / Other Undead						),
	DICT_I_(55999, Horror										),
	DICT_I_(59000, Music + Subgenres							),
	DICT_I_(59300, Music / Live in Concert						),
	DICT_I_(59700, Music / Music Videos							),
	DICT_I_(59999, Music										),
	DICT_I_(62999, Musical										),
	DICT_I_(66000, Performing Arts + Subgenres					),
	DICT_I_(66100, Performing Arts / Circus						),
	DICT_I_(66300, Performing Arts / Concerts					),
	DICT_I_(66500, Performing Arts / Dance						),
	DICT_I_(66700, Performing Arts / Operas						),
	DICT_I_(66900, Performing Arts / Theater					),
	DICT_I_(66999, Performing Arts								),
	DICT_I_(70000, Sci-Fi + Subgenres							),
	DICT_I_(70100, Sci-Fi / Alien								),
	DICT_I_(70200, Sci-Fi / Alternate Reality					),
	DICT_I_(70250, Sci-Fi / Apocalyptic							),
	DICT_I_(70300, Sci-Fi / Cyber Punk							),
	DICT_I_(70400, Sci-Fi / Kaiju (Giant Monster)				),
	DICT_I_(70500, Sci-Fi / Lost Worlds							),
	DICT_I_(70550, Sci-Fi / Military							),
	DICT_I_(70600, Sci-Fi / Other Worlds						),
	DICT_I_(70800, Sci-Fi / Space								),
	DICT_I_(70850, Sci-Fi / Space Horror						),
	DICT_I_(70870, Sci-Fi / Superheroes							),
	DICT_I_(70900, Sci-Fi / Utopia &amp; Dystopia				),
	DICT_I_(70999, Sci-Fi										),
	DICT_I_(73999, Short										),
	DICT_I_(76000, Silent + Subgenres							),
	DICT_I_(76100, Silent / Animation							),
	DICT_I_(76300, Silent / Horror								),
	DICT_I_(76500, Silent / Melodrama							),
	DICT_I_(76700, Silent / Slapstick							),
	DICT_I_(76800, Silent / Western								),
	DICT_I_(76999, Silent										),
	DICT_I_(80000, Sports + Subgenres							),
	DICT_I_(80100, Sports / Baseball							),
	DICT_I_(80130, Sports / Basketball							),
	DICT_I_(80170, Sports / Biking								),
	DICT_I_(80200, Sports / Fitness								),
	DICT_I_(80250, Sports / Football							),
	DICT_I_(80300, Sports / Golf								),
	DICT_I_(80350, Sports / Hockey								),
	DICT_I_(80400, Sports / Martial Arts						),
	DICT_I_(80450, Sports / Motor Sports						),
	DICT_I_(80500, Sports / Olympics							),
	DICT_I_(80600, Sports / Skateboard							),
	DICT_I_(80700, Sports / Skiing								),
	DICT_I_(80800, Sports / Soccer								),
	DICT_I_(80850, Sports / Tennis								),
	DICT_I_(80900, Sports / Wrestling							),
	DICT_I_(80999, Sports										),
	DICT_I_(84000, Suspense + Subgenres							),
	DICT_I_(84400, Suspense / Mystery							),
	DICT_I_(84700, Suspense / Thriller							),
	DICT_I_(84999, Suspense										),
	DICT_I_(88000, War + Subgenres								),
	DICT_I_(88200, War / US Civil War							),
	DICT_I_(88300, War / World War I							),
	DICT_I_(88400, War / World War II							),
	DICT_I_(88500, War / Korea									),
	DICT_I_(88600, War / Vietnam								),
	DICT_I_(88700, War / Post-Cold War							),
	DICT_I_(88900, War / Other									),
	DICT_I_(88999, War											),
	DICT_I_(91000, Western + Subgenres							),
	DICT_I_(91400, Western / Epic								),
	DICT_I_(91700, Western / Singing Cowboy						),
	DICT_I_(91800, Western / Spaghetti							),
	DICT_I_(91999, Western										),
	DICT_I_(95999, DVD Audio									),
	DICT_I_(98000, Other + Subgenres							),
	DICT_I_(98200, Other / Digital Comic Books					),
	DICT_I_(98250, Other / Game Shows							),
	DICT_I_(98300, Other / Games								),
	DICT_I_(98999, Other										),
	DICT_I_(99999, Unspecified Genre							)},
							
CDictionary::___genre_lower[] = {									// table decodes: genre_lower
	DICT_I_(10100, action-comedy								),
	DICT_I_(10200, action-crime									),
	DICT_I_(10300, action-disaster								),
	DICT_I_(10400, action-epic									),
	DICT_I_(10500, action-espionage								),
	DICT_I_(10600, action-martialarts							),
	DICT_I_(10700, action-military								),
	DICT_I_(10750, action-samurai								),
	DICT_I_(10800, action-superheroes							), /* deprecated */
	DICT_I_(10999, action-nosub									),
	DICT_I_(13100, animation-cartoons							),
	DICT_I_(13300, animation-family								),
	DICT_I_(13600, animation-mature								),
	DICT_I_(13700, animation-puppetrystopmotion					),
	DICT_I_(13800, animation-scifi								),
	DICT_I_(13900, animation-superheroes						),
	DICT_I_(13999, animation-nosub								),
	DICT_I_(16200, anime-action									),
	DICT_I_(16250, anime-comedy									),
	DICT_I_(16300, anime-drama									),
	DICT_I_(16400, anime-fantasy								),
	DICT_I_(16500, anime-horror									),
	DICT_I_(16600, anime-mahoushoujo							),
	DICT_I_(16700, anime-martialarts							),
	DICT_I_(16750, anime-mecha									),
	DICT_I_(16800, anime-moe									),
	DICT_I_(16850, anime-romance								),
	DICT_I_(16900, anime-scifi									),
	DICT_I_(16999, anime-nosub									),
	DICT_I_(20100, comedy-dark									),
	DICT_I_(20200, comedy-farce									),
	DICT_I_(20300, comedy-horror								),
	DICT_I_(20400, comedy-romantic								),
	DICT_I_(20600, comedy-satire								),
	DICT_I_(20650, comedy-scifi									),
	DICT_I_(20700, comedy-screwball								),
	DICT_I_(20750, comedy-sitcom								),
	DICT_I_(20800, comedy-sketchesstandup						),
	DICT_I_(20850, comedy-slapstick								),
	DICT_I_(20900, comedy-teen									),
	DICT_I_(20999, comedy-nosub									),
	DICT_I_(24100, documentary-biography						),
	DICT_I_(24200, documentary-crime							),
	DICT_I_(24250, documentary-culture							),
	DICT_I_(24270, documentary-entertainment					),
	DICT_I_(24300, documentary-history							),
	DICT_I_(24400, documentary-nature							),
	DICT_I_(24500, documentary-propaganda						),
	DICT_I_(24600, documentary-religion							),
	DICT_I_(24700, documentary-science							),
	DICT_I_(24750, documentary-social							),
	DICT_I_(24800, documentary-sports							),
	DICT_I_(24900, documentary-travel							),
	DICT_I_(24999, documentary-nosub							),
	DICT_I_(28100, drama-courtroom								),
	DICT_I_(28150, drama-crime									),
	DICT_I_(28200, drama-docudrama								),
	DICT_I_(28400, drama-melodrama								),
	DICT_I_(28600, drama-period									),
	DICT_I_(28800, drama-romance								),
	DICT_I_(28900, drama-sports									),
	DICT_I_(28950, drama-war									),
	DICT_I_(28999, drama-nosub									),
	DICT_I_(32200, educational-children							),
	DICT_I_(32700, educational-school							),
	DICT_I_(32999, educational-nosub							),
	DICT_I_(36100, erotica-hentai								),
	DICT_I_(36999, erotica-nosub								),
	DICT_I_(39999, experimental									),
	DICT_I_(41100, exploitation-blaxploitation					),
	DICT_I_(41300, exploitation-nazisploitation					),
	DICT_I_(41400, exploitation-nunsploitation					),
	DICT_I_(41500, exploitation-pinkueiga						),
	DICT_I_(41600, exploitation-sexploitation					),
	DICT_I_(41700, exploitation-shockumentary					),
	DICT_I_(41800, exploitation-wip								),
	DICT_I_(41999, exploitation-nosub							),
	DICT_I_(43999, fantasy										),
	DICT_I_(47999, filmnoir										),
	DICT_I_(51100, foreign-brazil								), /* deprecated */
	DICT_I_(51150, foreign-china								), /* deprecated */
	DICT_I_(51200, foreign-netherlands							), /* deprecated */
	DICT_I_(51250, foreign-easterneurope						), /* deprecated */
	DICT_I_(51300, foreign-france								), /* deprecated */
	DICT_I_(51350, foreign-germany								), /* deprecated */
	DICT_I_(51400, foreign-hongkong								), /* deprecated */
	DICT_I_(51450, foreign-india								), /* deprecated */
	DICT_I_(51500, foreign-italy								), /* deprecated */
	DICT_I_(51550, foreign-japan								), /* deprecated */
	DICT_I_(51570, foreign-southkorea							), /* deprecated */
	DICT_I_(51600, foreign-mexico								), /* deprecated */
	DICT_I_(51650, foreign-middleeast							), /* deprecated */
	DICT_I_(51700, foreign-portugal								), /* deprecated */
	DICT_I_(51750, foreign-russia								), /* deprecated */
	DICT_I_(51780, foreign-scandinavia							), /* deprecated */
	DICT_I_(51790, foreign-spain								), /* deprecated */
	DICT_I_(51800, foreign-latinamerica							), /* deprecated */
	DICT_I_(51850, foreign-sweden								), /* deprecated */
	DICT_I_(51900, foreign-taiwan								), /* deprecated */
	DICT_I_(51999, foreign-nosub								), /* deprecated */
	DICT_I_(55050, horror-anthology								),
	DICT_I_(55100, horror-asian									),
	DICT_I_(55250, horror-creatureanimal						),
	DICT_I_(55300, horror-espghosts								),
	DICT_I_(55350, horror-eurotrash								),
	DICT_I_(55400, horror-exploitation							),
	DICT_I_(55450, horror-gialli								),
	DICT_I_(55500, horror-goreshock								),
	DICT_I_(55550, horror-gothic								),
	DICT_I_(55700, horror-possessionsatan						),
	DICT_I_(55800, horror-shockumentary							),
	DICT_I_(55850, horror-slashersurvival						),
	DICT_I_(55900, horror-vampires								),
	DICT_I_(55950, horror-zombiesinfected						),
	DICT_I_(55960, horror-otherundead							),
	DICT_I_(55999, horror-nosub									),
	DICT_I_(59300, music-liveinconcert							),
	DICT_I_(59700, music-musicvideos							),
	DICT_I_(59999, music-nosub									),
	DICT_I_(62999, musical										),
	DICT_I_(66100, performing-circus							),
	DICT_I_(66300, performing-concerts							),
	DICT_I_(66500, performing-dance								),
	DICT_I_(66700, performing-operas							),
	DICT_I_(66900, performing-theater							),
	DICT_I_(66999, performing-nosub								),
	DICT_I_(70100, scifi-alien									),
	DICT_I_(70200, scifi-alternatereality						),
	DICT_I_(70250, scifi-apocalyptic							),
	DICT_I_(70300, scifi-cyberpunk								),
	DICT_I_(70400, scifi-kaiju									),
	DICT_I_(70500, scifi-lostworlds								),
	DICT_I_(70550, scifi-military								),
	DICT_I_(70600, scifi-otherworlds							),
	DICT_I_(70800, scifi-space									),
	DICT_I_(70850, scifi-spacehorror							),
	DICT_I_(70870, scifi-superheroes							),
	DICT_I_(70900, scifi-utopiadystopia							),
	DICT_I_(70999, scifi-nosub									),
	DICT_I_(73999, short										),
	DICT_I_(76100, silent-animation								),
	DICT_I_(76300, silent-horror								),
	DICT_I_(76500, silent-melodrama								),
	DICT_I_(76700, silent-slapstick								),
	DICT_I_(76800, silent-western								),
	DICT_I_(76999, silent-nosub									),
	DICT_I_(80100, sports-baseball								),
	DICT_I_(80130, sports-basketball							),
	DICT_I_(80170, sports-biking								),
	DICT_I_(80200, sports-fitness								),
	DICT_I_(80250, sports-football								),
	DICT_I_(80300, sports-golf									),
	DICT_I_(80350, sports-hockey								),
	DICT_I_(80400, sports-martialarts							),
	DICT_I_(80450, sports-motorsports							),
	DICT_I_(80500, sports-olympics								),
	DICT_I_(80600, sports-skateboard							),
	DICT_I_(80700, sports-skiing								),
	DICT_I_(80800, sports-soccer								),
	DICT_I_(80850, sports-tennis								),
	DICT_I_(80900, sports-wrestling								),
	DICT_I_(80999, sports-nosub									),
	DICT_I_(84400, suspense-mystery								),
	DICT_I_(84700, suspense-thriller							),
	DICT_I_(84999, suspense-nosub								),
	DICT_I_(88200, war-uscivilwar								),
	DICT_I_(88300, war-wwi										),
	DICT_I_(88400, war-wwii										),
	DICT_I_(88500, war-korea									),
	DICT_I_(88600, war-vietnam									),
	DICT_I_(88700, war-postcoldwar								),
	DICT_I_(88900, war-other									),
	DICT_I_(88999, war-nosub									),
	DICT_I_(91400, western-epic									),
	DICT_I_(91700, western-singingcowboy						),
	DICT_I_(91800, western-spaghetti							),
	DICT_I_(91999, western-nosub								),
	DICT_I_(95999, dvdaudio										),
	DICT_I_(98200, other-digitalcomicbooks						),
	DICT_I_(98250, other-gameshows								),
	DICT_I_(98300, other-games									),
	DICT_I_(98999, other-nosub									),
	DICT_I_(99999, unspecifiedgenre								)},

CDictionary::___birth_country[] = {
	DICT_I_(10000, Anguilla										), // North America
	DICT_I_(10300, Antigua and Barbuda							),
	DICT_I_(10600, Aruba										),
	DICT_I_(10900, Bahamas										),
	DICT_I_(11200, Barbados										),
	DICT_I_(11500, Belize										),
	DICT_I_(11800, Bermuda										),
	DICT_I_(12100, British Virgin Islands						),
	DICT_I_(12400, Canada										),
	DICT_I_(12700, Cayman Islands								),
	DICT_I_(13000, Clipperton Island							),
	DICT_I_(13300, Costa Rica									),
	DICT_I_(13600, Cuba											),
	DICT_I_(13900, Dominica										),
	DICT_I_(14200, Dominican Republic							),
	DICT_I_(14500, El Salvador									),
	DICT_I_(14800, Greenland									),
	DICT_I_(15100, Grenada										),
	DICT_I_(15400, Guadeloupe									),
	DICT_I_(15700, Guatemala									),
	DICT_I_(16000, Haiti										),
	DICT_I_(16300, Honduras										),
	DICT_I_(16600, Jamaica										),
	DICT_I_(16900, Martinique									),
	DICT_I_(17200, Mexico										),
	DICT_I_(17500, Montserrat									),
	DICT_I_(17800, Navassa Island								),
	DICT_I_(18100, Netherlands Antilles							),
	DICT_I_(18400, Nicaragua									),
	DICT_I_(18700, Panama										),
	DICT_I_(19000, Puerto Rico									),
	DICT_I_(19300, Saint Barthélemy								),
	DICT_I_(19600, Saint Kitts and Nevis						),
	DICT_I_(19900, Saint Lucia									),
	DICT_I_(20200, Saint Martin									),
	DICT_I_(20500, Saint Pierre and Miquelon					),
	DICT_I_(20800, Saint Vincent and the Grenadines				),
	DICT_I_(21100, Trinidad and Tobago							),
	DICT_I_(21400, Turks and Caicos Islands						),
	DICT_I_(21700, United States								),
	DICT_I_(22000, United States Virgin Islands					),
	DICT_I_(22300, Argentina									), // South America
	DICT_I_(22600, Bolivia										),
	DICT_I_(22900, Brazil										),
	DICT_I_(23200, Chile										),
	DICT_I_(23500, Colombia										),
	DICT_I_(23800, Ecuador										),
	DICT_I_(24100, Falkland Islands								),
	DICT_I_(24400, French Guiana								),
	DICT_I_(24700, Guyana										),
	DICT_I_(25000, Paraguay										),
	DICT_I_(25300, Peru											),
	DICT_I_(25600, Suriname										),
	DICT_I_(25900, Uruguay										),
	DICT_I_(26200, Venezuela									),
	DICT_I_(26500, Other										),
	DICT_I_(26800, Åland Islands								), // Europe
	DICT_I_(27100, Albania										),
	DICT_I_(27400, Andorra										),
	DICT_I_(27700, Austria										),
	DICT_I_(28000, Belarus										),
	DICT_I_(28300, Belgium										),
	DICT_I_(28600, Bosnia and Herzegovina						),
	DICT_I_(28900, Bulgaria										),
	DICT_I_(29200, Croatia										),
	DICT_I_(29500, Czech Republic								),
	DICT_I_(29800, Denmark										),
	DICT_I_(30100, Estonia										),
	DICT_I_(30400, Faroe Islands								),
	DICT_I_(30700, Finland										),
	DICT_I_(31000, France										),
	DICT_I_(31300, Germany										),
	DICT_I_(31600, Gibraltar									),
	DICT_I_(31900, Greece										),
	DICT_I_(32200, Guernsey										),
	DICT_I_(32500, Hungary										),
	DICT_I_(32800, Iceland										),
	DICT_I_(33100, Ireland										),
	DICT_I_(33400, Isle of Man									),
	DICT_I_(33700, Italy										),
	DICT_I_(34000, Jersey										),
	DICT_I_(34300, Kosovo										),
	DICT_I_(34600, Latvia										),
	DICT_I_(34900, Liechtenstein								),
	DICT_I_(35200, Lithuania									),
	DICT_I_(35500, Luxembourg									),
	DICT_I_(35800, Macedonia									),
	DICT_I_(36100, Malta										),
	DICT_I_(36400, Moldova										),
	DICT_I_(36700, Monaco										),
	DICT_I_(37000, Montenegro									),
	DICT_I_(37300, Netherlands									),
	DICT_I_(37600, Norway										),
	DICT_I_(37900, Poland										),
	DICT_I_(38200, Portugal										),
	DICT_I_(38500, Pridnestrovie (Transnistria)					),
	DICT_I_(38800, Romania										),
	DICT_I_(39100, Russia										),
	DICT_I_(39400, San Marino									),
	DICT_I_(39700, Serbia										),
	DICT_I_(40000, Slovakia										),
	DICT_I_(40300, Slovenia										),
	DICT_I_(40600, Spain										),
	DICT_I_(40900, Svalbard										),
	DICT_I_(41200, Sweden										),
	DICT_I_(41500, Switzerland									),
	DICT_I_(41800, Ukraine										),
	DICT_I_(42100, United Kingdom								),
	DICT_I_(42400, Vatican City									),
	DICT_I_(42700, Algeria										), // Africa
	DICT_I_(43000, Angola										),
	DICT_I_(43300, Benin										),
	DICT_I_(43600, Botswana										),
	DICT_I_(43900, Burkina Faso									),
	DICT_I_(44200, Burundi										),
	DICT_I_(44500, Cameroon										),
	DICT_I_(44800, Cape Verde									),
	DICT_I_(45100, Central African Republic						),
	DICT_I_(45400, Chad											),
	DICT_I_(45700, Comoros										),
	DICT_Ic(46000, "Congo, Democratic Republic of"				),
	DICT_Ic(46300, "Congo, Republic of"							),
	DICT_I_(46600, Djibouti										),
	DICT_I_(46900, Egypt										),
	DICT_I_(47200, Equatorial Guinea							),
	DICT_I_(47500, Eritrea										),
	DICT_I_(47800, Ethiopia										),
	DICT_I_(48100, Gabon										),
	DICT_I_(48400, Gambia										),
	DICT_I_(48700, Ghana										),
	DICT_I_(49000, Guinea										),
	DICT_I_(49300, Guinea-Bissau								),
	DICT_I_(49600, Ivory Coast									),
	DICT_I_(49900, Kenya										),
	DICT_I_(50200, Lesotho										),
	DICT_I_(50500, Liberia										),
	DICT_I_(50800, Libya										),
	DICT_I_(51100, Madagascar									),
	DICT_I_(51400, Malawi										),
	DICT_I_(51700, Mali											),
	DICT_I_(52000, Mauritania									),
	DICT_I_(52300, Mauritius									),
	DICT_I_(52600, Mayotte										),
	DICT_I_(52900, Morocco										),
	DICT_I_(53200, Mozambique									),
	DICT_I_(53500, Namibia										),
	DICT_I_(53800, Niger										),
	DICT_I_(54100, Nigeria										),
	DICT_I_(54400, Réunion										),
	DICT_I_(54700, Rwanda										),
	DICT_I_(55000, Saint Helena									),
	DICT_I_(55300, Sao Tome and Principe						),
	DICT_I_(55600, Senegal										),
	DICT_I_(55900, Seychelles									),
	DICT_I_(56200, Sierra Leone									),
	DICT_I_(56500, Somalia										),
	DICT_I_(56800, Somaliland									),
	DICT_I_(57100, South Africa									),
	DICT_I_(57400, Sudan										),
	DICT_I_(57700, Swaziland									),
	DICT_I_(58000, Tanzania										),
	DICT_I_(58300, Togo											),
	DICT_I_(58600, Tunisia										),
	DICT_I_(58900, Uganda										),
	DICT_I_(59200, Zambia										),
	DICT_I_(59500, Zimbabwe										),
	DICT_I_(59800, Abkhazia										), // Asia
	DICT_I_(60100, Afghanistan									),
	DICT_I_(60400, Armenia										),
	DICT_I_(60700, Azerbaijan									),
	DICT_I_(61000, Bahrain										),
	DICT_I_(61300, Bangladesh									),
	DICT_I_(61600, Bhutan										),
	DICT_I_(61900, British Indian Ocean Territory				),
	DICT_I_(62200, Brunei										),
	DICT_I_(62500, Cambodia										),
	DICT_I_(62800, China										),
	DICT_I_(63100, Christmas Island								),
	DICT_I_(63400, Cocos Islands								),
	DICT_I_(63700, Cyprus										),
	DICT_I_(64000, East Timor									),
	DICT_I_(64300, Georgia										),
	DICT_I_(64600, Hong Kong									),
	DICT_I_(64900, India										),
	DICT_I_(65200, Indonesia									),
	DICT_I_(65500, Iran											),
	DICT_I_(65800, Iraq											),
	DICT_I_(66100, Israel										),
	DICT_I_(66400, Japan										),
	DICT_I_(66700, Jordan										),
	DICT_I_(67000, Kazakhstan									),
	DICT_I_(67300, Kuwait										),
	DICT_I_(67600, Kyrgyzstan									),
	DICT_I_(67900, Laos											),
	DICT_I_(68200, Lebanon										),
	DICT_I_(68500, Macau										),
	DICT_I_(68800, Malaysia										),
	DICT_I_(69100, Maldives										),
	DICT_I_(69400, Mongolia										),
	DICT_I_(69700, Myanmar (Burma)								),
	DICT_I_(70000, Nagorno-Karabakh								),
	DICT_I_(70300, Nepal										),
	DICT_I_(70600, North Korea									),
	DICT_I_(70900, Northern Cyprus								),
	DICT_I_(71200, Oman											),
	DICT_I_(71500, Pakistan										),
	DICT_I_(71800, Palestinian territories						),
	DICT_I_(72100, Philippines									),
	DICT_I_(72400, Qatar										),
	DICT_I_(72700, Saudi Arabia									),
	DICT_I_(73000, Singapore									),
	DICT_I_(73300, South Korea									),
	DICT_I_(73600, South Ossetia								),
	DICT_I_(73900, Sri Lanka									),
	DICT_I_(74200, Syria										),
	DICT_I_(74500, Taiwan										),
	DICT_I_(74800, Tajikistan									),
	DICT_I_(75100, Thailand										),
	DICT_I_(75400, Turkey										),
	DICT_I_(75700, Turkmenistan									),
	DICT_I_(76000, United Arab Emirates							),
	DICT_I_(76300, Uzbekistan									),
	DICT_I_(76600, Vietnam										),
	DICT_I_(76900, Yemen										),
	DICT_I_(77200, American Samoa								), // Oceania
	DICT_I_(77500, Australia									),
	DICT_I_(77800, Baker Island									),
	DICT_I_(78100, Cook Islands									),
	DICT_I_(78400, Fiji											),
	DICT_I_(78700, French Polynesia								),
	DICT_I_(79000, Guam											),
	DICT_I_(79300, Howland Island								),
	DICT_I_(79600, Jarvis Island								),
	DICT_I_(79900, Johnston Atoll								),
	DICT_I_(80200, Kingman Reef									),
	DICT_I_(80500, Kiribati										),
	DICT_I_(80800, Marshall Islands								),
	DICT_I_(81100, Micronesia									),
	DICT_I_(81400, Midway Atoll									),
	DICT_I_(81700, Nauru										),
	DICT_I_(82000, New Caledonia								),
	DICT_I_(82300, New Zealand									),
	DICT_I_(82600, Niue											),
	DICT_I_(82900, Norfolk Island								),
	DICT_I_(83200, Northern Mariana Islands						),
	DICT_I_(83500, Palau										),
	DICT_I_(83800, Palmyra Atoll								),
	DICT_I_(84100, Papua New Guinea								),
	DICT_I_(84400, Pitcairn Islands								),
	DICT_I_(84700, Samoa										),
	DICT_I_(85000, Solomon Islands								),
	DICT_I_(85300, Tokelau										),
	DICT_I_(85600, Tonga										),
	DICT_I_(85900, Tuvalu										),
	DICT_I_(86200, Vanuatu										),
	DICT_I_(86500, Wake Island									),
	DICT_I_(86800, Wallis and Futuna							),
	DICT_I_(87100, Antarctica									), // Antartica
	DICT_I_(87400, Bouvet Island								),
	DICT_I_(87700, French Southern Territories					),
	DICT_I_(88000, Heard Island and McDonald Islands			),
	DICT_I_(88300, South Georgia and the South Sandwich Islands	),
	DICT_I_(99999, Unknown										)};

////_gp_frame_present[] =	   {FIELD_OPTION('A',Anamorphic										),
////							FIELD_OPTION('L',Letterboxed									),
////							FIELD_OPTION('F',Full-Frame										),
////							FIELD_OPTION('S',Full-Screen									),
////							FIELD_OPTION('b',Window-boxed									),
////							FIELD_OPTION('-',Unknown										)},

#define DICT_(name,typ,sort,def)							  \
	const CDictionary::t_dict CDictionary::__ ## name = {	  \
		{SS(#name)}											, \
		CDictionary::eDict_		## name						, \
		CDictionary::___		## name						, \
		ARRAY_SIZE(CDictionary::___	## name)				, \
		CDictionary::eDictSort_ ## sort						, \
		CDictionary::eEncode_	## typ						, \
		def													};\
	CDictionary CDictionary::_ ## name (CDictionary::__ ## name);

DICT_(amz_country			,char1,unsorted,				'-');
DICT_(dvd_country			,char2,  sorted, CHAR2_TO_INT_(u,s));
DICT_(disposition		 	,char1,unsorted,				'-');
DICT_(expire_reason	 		,char1,unsorted,				'-');
DICT_(feature_cd		 	,char1,unsorted,				'-');
DICT_(frame_conversion	 	,char1,unsorted,				'-');
DICT_(img_suitability	 	,char1,unsorted,				'-');
DICT_(img_treatment	 		,char1,unsorted,				'O');
DICT_(language			 	,char2,  sorted, CHAR2_TO_INT_(u,n));
DICT_(media_type		 	,char1,unsorted,				'D');
DICT_(pic_code			 	,char1,unsorted,				'-');
DICT_(pic_type			 	,char1,unsorted,				'D');
DICT_(public			 	,char1,unsorted,				'Y');
DICT_(film_rating		 	,int  ,  sorted,				  0);
DICT_(region			 	,char1,unsorted,				'-');
DICT_(release_status	 	,char1,unsorted,				'-');
DICT_(request_dvd		 	,char1,unsorted,				'-');
DICT_(request_film		 	,char1,unsorted,				'-');
DICT_(request_person	 	,char1,unsorted,				'-');
DICT_(request_pub		 	,char1,unsorted,				'-');
DICT_(request_pic		 	,char1,unsorted,				'-');
DICT_(person_role		 	,char1,unsorted,				'e');
DICT_(role_dir			 	,char1,unsorted,				'D');
DICT_(role_cast		 		,char1,unsorted,				'1');
DICT_(role_crew		 		,char1,unsorted,				'O');
DICT_(sound_system		 	,char1,unsorted,				'-');
DICT_(source			 	,char1,unsorted,				'A');
DICT_(surround_mode	 		,char1,unsorted,				'-');
DICT_(trade_loan		 	,char1,unsorted,				'-');
DICT_(video_mode		 	,char1,unsorted,				'-');
DICT_(yes_no			 	,char1,unsorted,				'Y');
DICT_(genre			 		,int  ,  sorted,			  99999);
DICT_(genre_lower		 	,int  ,  sorted,			  99999);
DICT_(birth_country	 		,int  ,  sorted,			  99999);

const CDictionary::t_dict CDictionary::__none = { {SS("none")}, CDictionary::eDict_none, NULL, 0,
	CDictionary::eDictSort_unsorted, CDictionary::eEncode_int, 0};

CDictionary CDictionary::_none (CDictionary::__none);

CDictionary CDictionary::_Dict[CDictionary::eDict_total_types] = {
	CDictionary::_none				,
	CDictionary::_amz_country		,
	CDictionary::_dvd_country		,
	CDictionary::_disposition		,
	CDictionary::_expire_reason		,
	CDictionary::_feature_cd		,
	CDictionary::_frame_conversion	,
	CDictionary::_img_suitability	,
	CDictionary::_img_treatment		,
	CDictionary::_language			,
	CDictionary::_media_type		,
	CDictionary::_pic_code			,
	CDictionary::_pic_type			,
	CDictionary::_public			,
	CDictionary::_film_rating		,
	CDictionary::_region			,
	CDictionary::_release_status	,
	CDictionary::_request_dvd		,
	CDictionary::_request_film		,
	CDictionary::_request_person	,
	CDictionary::_request_pub		,
	CDictionary::_request_pic		,
	CDictionary::_person_role		,
	CDictionary::_role_dir			,
	CDictionary::_role_cast			,
	CDictionary::_role_crew			,
	CDictionary::_sound_system		,
	CDictionary::_source			,
	CDictionary::_surround_mode		,
	CDictionary::_trade_loan		,
	CDictionary::_video_mode		,
	CDictionary::_yes_no			,
	CDictionary::_genre				,
	CDictionary::_genre_lower		,
	CDictionary::_birth_country		};

#undef DICT_1_
#undef DICT_1c
#undef DICT_2_
#undef DICT_2c
#undef DICT_I_
#undef DICT_Ic
#undef DICT_
