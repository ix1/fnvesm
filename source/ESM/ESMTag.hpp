
#pragma once

namespace ESM
{
    enum class ESMTag : uint32_t {
        Invalid = 0x00000000,
        TES4 = 0x34534554,
        MAST = 0x5453414D,
        TX00 = 0x30305854,
        NAM0 = 0x304D414E,
        TX01 = 0x31305854,
        NAM1 = 0x314D414E,
        CIS1 = 0x31534943,
        TX02 = 0x32305854,
        PKC2 = 0x32434B50,
        MOD2 = 0x32444F4D,
        EPF2 = 0x32465045,
        NAM2 = 0x324D414E,
        ICO2 = 0x324F4349,
        PFO2 = 0x324F4650,
        CIS2 = 0x32534943,
        XIS2 = 0x32534958,
        TX03 = 0x33305854,
        MOD3 = 0x33444F4D,
        EPF3 = 0x33465045,
        NAM3 = 0x334D414E,
        TX04 = 0x34305854,
        MOD4 = 0x34444F4D,
        NAM4 = 0x344D414E,
        TX05 = 0x35305854,
        MOD5 = 0x35444F4D,
        NAM5 = 0x354D414E,
        TX06 = 0x364D414E,
        TX07 = 0x37305854,
        NAM7 = 0x374D414E,
        NAM8 = 0x384D414E,
        NAM9 = 0x394D414E,
        POBA = 0x41424F50,
        ALCA = 0x41434C41,
        POCA = 0x41434F50,
        SCDA = 0x41444353,
        CTDA = 0x41445443,
        PTDA = 0x41445450,
        KWDA = 0x4144574B,
        ALEA = 0x41454C41,
        POEA = 0x41454F50,
        ALFA = 0x41464C41,
        IDLA = 0x414C4449,
        RELA = 0x414C4552,
        NAMA = 0x414D414E,
        ARMA = 0x414D5241,
        ALNA = 0x414E4C41,
        APPA = 0x41505041,
        XPPA = 0x41505058,
        RDSA = 0x41534452,
        DATA = 0x41544144,
        QSTA = 0x41545351,
        ALUA = 0x41554C41,
        DEVA = 0x41564544,
        CRVA = 0x41565243,
        XCZA = 0x415A4358,
        PRCB = 0x42435250,
        XRGB = 0x42475258,
        XLIB = 0x42494C58,
        MDOB = 0x424F444D,
        GLOB = 0x424F4C47,
        REVB = 0x42564552,
        CLDC = 0x43444C43,
        LCEC = 0x4345434C,
        TIFC = 0x43464954,
        ALFC = 0x43464C41,
        TPIC = 0x43495054,
        PRKC = 0x434B5250,
        DALC = 0x434C4144,
        IDLC = 0x434C4449,
        VENC = 0x434E4556,
        TINC = 0x434E4954,
        XLOC = 0x434F4C58,
        PFPC = 0x43504650,
        ALPC = 0x43504C41,
        ASPC = 0x43505341,
        XSPC = 0x43505358,
        SDSC = 0x43534453,
        DESC = 0x43534544,
        MISC = 0x4353494D,
        MUSC = 0x4353554D,
        CITC = 0x43544943,
        XFVC = 0x43564658,
        XCZC = 0x435A4358,
        HEAD = 0x44414548,
        
        // NUL
        X0IAD = 0x44414900,
        X1IAD = 0x44414901,
        X2IAD = 0x44414902,
        X3IAD = 0x44414903,
        X4IAD = 0x44414904,
        X5IAD = 0x44414905,
        X6IAD = 0x44414906,
        X7IAD = 0x44414907,
        X8IAD = 0x44414908,
        X9IAD = 0x44414909,
        
        XAIAD = 0x4441490A,
        XBIAD = 0x4441490B,
        XCIAD = 0x4441490C,
        
        XDIAD = 0x4441490D,
        XEIAD = 0x4441490E,
        XFIAD = 0x4441490F,
        X10IAD = 0x44414910,
        X11IAD = 0x44414911,
        X12IAD = 0x44414912,
        X13IAD = 0x44414913,
        X14IAD = 0x44414914,
        
        // @
        XATIAD = 0x44414940,
        AIAD = 0x44414941,
        BIAD = 0x44414942,
        CIAD = 0x44414943,
        DIAD = 0x44414944,
        EIAD = 0x44414945,
        FIAD = 0x44414946,
        GIAD = 0x44414947,
        HIAD = 0x44414948,
        IIAD = 0x44414949,
        JIAD = 0x4441494A,
        KIAD = 0x4441494B,
        LIAD = 0x4441494C,
        MIAD = 0x4441494D,
        NIAD = 0x4441494E,
        OIAD = 0x4441494F,
        PIAD = 0x44414950,
        QIAD = 0x44414951,
        RIAD = 0x44414952,
        SIAD = 0x44414953,
        TIAD = 0x44414954,
        IMAD = 0x44414D49,
        VMAD = 0x44414D56,
        SNDD = 0x44444E53,
        ALED = 0x44454C41,
        COED = 0x44454F43,
        SPED = 0x44455053,
        ALFD = 0x44464C41,
        EPFD = 0x44465045,
        SPGD = 0x44475053,
        XRGD = 0x44475258,
        CSGD = 0x44475343,
        LCID = 0x4449434C,
        EDID = 0x44494445,
        EFID = 0x44494645,
        ALID = 0x44494C41,
        HTID = 0x44495448,
        ATKD = 0x444B5441,
        RPLD = 0x444C5052,
        WRLD = 0x444C5257,
        LVLD = 0x444C564C,
        CSMD = 0x444D5343,
        LAND = 0x444E414C,
        OBND = 0x444E424F,
        VEND = 0x444E4556,
        TIND = 0x444E4954,
        BPND = 0x444E5042,
        XPOD = 0x444F5058,
        XAPD = 0x44504158,
        XPRD = 0x44525058,
        BPTD = 0x44545042,
        DSTD = 0x44545344,
        PLVD = 0x44564C50,
        KYWD = 0x4457594B,
        HAZD = 0x445A4148,
        PHZD = 0x445A4850,
        RACE = 0x45434152,
        TREE = 0x45455254,
        ALFE = 0x45464C41,
        PRKE = 0x454B5250,
        ATKE = 0x454B5441,
        IDLE = 0x454C4449,
        NAME = 0x454D414E,
        CSME = 0x454D5343,
        PGRE = 0x45524750,
        AHCF = 0x46434841,
        MGEF = 0x4645474D,
        AVIF = 0x46495641,
        PRKF = 0x464B5250,
        HCLF = 0x464C4348,
        IDLF = 0x464C4449,
        LVLF = 0x464C564C,
        RPRF = 0x46525052,
        FTSF = 0x46535446,
        DFTF = 0x46544644,
        DSTF = 0x46545344,
        PFIG = 0x47494650,
        XLIG = 0x47494C58,
        LVLG = 0x474C564C,
        MESG = 0x4753454D,
        ALCH = 0x48434C41,
        ENCH = 0x48434E45,
        LIGH = 0x4847494C,
        EFSH = 0x48534645,
        CPTH = 0x48545043,
        MPAI = 0x4941504D,
        ALFI = 0x49464C41,
        RPLI = 0x494C5052,
        LVLI = 0x494C564C,
        XEMI = 0x494D4558,
        NVMI = 0x494D564E,
        TINI = 0x494E4954,
        BPNI = 0x494E5042,
        XTRI = 0x49525458,
        ACTI = 0x49544341,
        NAVI = 0x4956414E,
        COBJ = 0x4A424F43,
        DOBJ = 0x4A424F44,
        QOBJ = 0x4A424F51,
        PROJ = 0x4A4F5250,
        PACK = 0x4B434150,
        VTCK = 0x4B435456,
        FNMK = 0x4B4D4E46,
        XRNK = 0x4B4E5258,
        BOOK = 0x4B4F4F42,
        PERK = 0x4B524550,
        XMRK = 0x4B524D58,
        AVSK = 0x4B535641,
        DIAL = 0x4C414944,
        DUAL = 0x4C415544,
        QUAL = 0x4C415551,
        ALCL = 0x4C434C41,
        XSCL = 0x4C435358,
        RGDL = 0x4C444752,
        DMDL = 0x4C444D44,
        MODL = 0x4C444F4D,
        SPEL = 0x4C455053,
        XTEL = 0x4C455458,
        ALFL = 0x4C464C41,
        CSFL = 0x4C465343,
        QTGL = 0x4C475451,
        JAIL = 0x4C49414A,
        CELL = 0x4C4C4543,
        COLL = 0x4C4C4F43,
        FULL = 0x4C4C5546,
        TINL = 0x4C4E4954,
        SCOL = 0x4C4F4353,
        STOL = 0x4C4F5453,
        EXPL = 0x4C505845,
        SCRL = 0x4C524353,
        SOUL = 0x4C554F53,
        XCVL = 0x4C564358,
        ANAM = 0x4D414E41,
        BNAM = 0x4D414E42,
        CNAM = 0x4D414E43,
        DNAM = 0x4D414E44,
        ENAM = 0x4D414E45,
        FNAM = 0x4D414E46,
        GNAM = 0x4D414E47,
        HNAM = 0x4D414E48,
        INAM = 0x4D414E49,
        JNAM = 0x4D414E4A,
        KNAM = 0x4D414E4B,
        LNAM = 0x4D414E4C,
        MNAM = 0x4D414E4D,
        NNAM = 0x4D414E4E,
        ONAM = 0x4D414E4F,
        PNAM = 0x4D414E50,
        QNAM = 0x4D414E51,
        RNAM = 0x4D414E52,
        SNAM = 0x4D414E53,
        TNAM = 0x4D414E54,
        UNAM = 0x4D414E55,
        VNAM = 0x4D414E56,
        WNAM = 0x4D414E57,
        XNAM = 0x4D414E58,
        YNAM = 0x4D414E59,
        ZNAM = 0x4D414E5A,
        AHCM = 0x4D434841,
        XLCM = 0x4D434C58,
        CLFM = 0x4D464C43,
        SLGM = 0x4D474C53,
        IDLM = 0x4D4C4449,
        MTNM = 0x4D4E544D,
        XTNM = 0x4D4E5458,
        SOPM = 0x4D504F53,
        XLRM = 0x4D524C58,
        RPRM = 0x4D525052,
        XPRM = 0x4D525058,
        FTSM = 0x4D535446,
        DFTM = 0x4D544644,
        LGTM = 0x4D54474C,
        EITM = 0x4D544945,
        NAVM = 0x4D56414E,
        KEYM = 0x4D59454B,
        SMBN = 0x4E424D53,
        PLCN = 0x4E434C50,
        XLCN = 0x4E434C58,
        XWCN = 0x4E435758,
        ADDN = 0x4E444441,
        ALDN = 0x4E444C41,
        SCEN = 0x4E454353,
        SMEN = 0x4E454D53,
        REGN = 0x4E474552,
        DMIN = 0x4E494D44,
        LVLN = 0x4E4C564C,
        BPNN = 0x4E4E5042,
        ICON = 0x4E4F4349,
        SMQN = 0x4E514D53,
        FURN = 0x4E525546,
        LCTN = 0x4E54434C,
        PHTN = 0x4E544850,
        BPTN = 0x4E545042,
        LCUN = 0x4E55434C,
        SOUN = 0x4E554F53,
        XOWN = 0x4E574F58,
        ECZN = 0x4E5A4345,
        XEZN = 0x4E5A4558,
        XMBO = 0x4F424D58,
        ALCO = 0x4F434C41,
        INFO = 0x4F464E49,
        ANIO = 0x4F494E41,
        SPLO = 0x4F4C5053,
        LVLO = 0x4F4C564C,
        RDMO = 0x4F4D4452,
        DEMO = 0x4F4D4544,
        AMMO = 0x4F4D4D41,
        ARMO = 0x4F4D5241,
        SCRO = 0x4F524353,
        MATO = 0x4F54414D,
        PDTO = 0x4F544450,
        CNTO = 0x4F544E43,
        ARTO = 0x4F545241,
        WEAP = 0x50414557,
        XMBP = 0x50424D58,
        SLCP = 0x50434C53,
        XOCP = 0x50434F58,
        XNDP = 0x50444E58,
        LCEP = 0x5045434C,
        XALP = 0x504C4158,
        RDMP = 0x504D4452,
        LTMP = 0x504D544C,
        TINP = 0x504E4954,
        WOOP = 0x504F4F57,
        NVPP = 0x5050564E,
        XESP = 0x50534558,
        ALSP = 0x50534C41,
        IMSP = 0x50534D49,
        LVSP = 0x5053564C,
        ASTP = 0x50545341,
        FSTP = 0x50545346,
        EQUP = 0x50555145,
        GRUP = 0x50555247,
        ETYP = 0x50595445,
        MTYP = 0x5059544D,
        VTYP = 0x50595456,
        ALEQ = 0x51454C41,
        DEBR = 0x52424544,
        DLBR = 0x52424C44,
        XMBR = 0x52424D58,
        CSCR = 0x52435343,
        LSCR = 0x5243534C,
        HEDR = 0x52444548,
        SNDR = 0x52444E53,
        NVER = 0x5245564E,
        REFR = 0x52464552,
        ALFR = 0x52464C41,
        INGR = 0x52474E49,
        CRGR = 0x52475243,
        ACHR = 0x52484341,
        SCHR = 0x52484353,
        WTHR = 0x52485457,
        HAIR = 0x52494148,
        XLKR = 0x524B4C58,
        RCLR = 0x524C4352,
        CSLR = 0x524C5343,
        XRMR = 0x524D5258,
        ECOR = 0x524F4345,
        PFOR = 0x524F4650,
        XHOR = 0x524F4858,
        FLOR = 0x524F4C46,
        DOOR = 0x524F4F44,
        SPOR = 0x524F5053,
        XAPR = 0x52504158,
        LCPR = 0x5250434C,
        FNPR = 0x52504E46,
        LCSR = 0x5253434C,
        WATR = 0x52544157,
        WCTR = 0x52544357,
        FLTR = 0x52544C46,
        XPWR = 0x52575058,
        MO2S = 0x53324F4D,
        MO3S = 0x53334F4D,
        MO4S = 0x53344F4D,
        CLAS = 0x53414C43,
        GRAS = 0x53415247,
        BIDS = 0x53444942,
        DMDS = 0x53444D44,
        MODS = 0x53444F4D,
        IPDS = 0x53445049,
        XRDS = 0x53445258,
        UNES = 0x53454E55,
        EYES = 0x53455945,
        IMGS = 0x53474D49,
        ALLS = 0x534C4C41,
        CAMS = 0x534D4143,
        TIRS = 0x53524954,
        FSTS = 0x53545346,
        MO2T = 0x54324F4D,
        MO3T = 0x54334F4D,
        MO4T = 0x54344F4D,
        MO5T = 0x54354F4D,
        RDAT = 0x54414452,
        STAT = 0x54415453,
        PWAT = 0x54415750,
        TWAT = 0x54415754,
        AACT = 0x54434141,
        FACT = 0x54434146,
        TACT = 0x54434154,
        XACT = 0x54434158,
        RFCT = 0x54434652,
        LLCT = 0x54434C4C,
        SNCT = 0x54434E53,
        COCT = 0x54434F43,
        IPCT = 0x54435049,
        SPCT = 0x54435053,
        WBDT = 0x54444257,
        MHDT = 0x5444484D,
        PKDT = 0x54444B50,
        PLDT = 0x54444C50,
        DMDT = 0x54444D44,
        BODT = 0x54444F42,
        DODT = 0x54444F44,
        MODT = 0x54444F4D,
        CRDT = 0x54445243,
        TRDT = 0x54445254,
        PSDT = 0x54445350,
        QSDT = 0x54445351,
        EPFT = 0x54465045,
        OTFT = 0x5446544F,
        FCHT = 0x54484346,
        MCHT = 0x5448434D,
        WAIT = 0x54494157,
        EFIT = 0x54494645,
        ENIT = 0x54494E45,
        SPIT = 0x54495053,
        TCLT = 0x544C4354,
        IDLT = 0x544C4449,
        BAMT = 0x544D4142,
        EAMT = 0x544D4145,
        CLMT = 0x544D4C43,
        XCNT = 0x544E4358,
        TINT = 0x544E4954,
        ALNT = 0x544E4C41,
        CONT = 0x544E4F43,
        BPNT = 0x544E5042,
        RDOT = 0x544F4452,
        SCPT = 0x54504353,
        HDPT = 0x54504448,
        LCRT = 0x5452434C,
        ALRT = 0x54524C41,
        XLRT = 0x54524C58,
        FPRT = 0x54525046,
        MPRT = 0x5452504D,
        DEST = 0x54534544,
        OFST = 0x5453464F,
        ALST = 0x54534C41,
        FLST = 0x54534C46,
        WLST = 0x54534C57,
        GMST = 0x54534D47,
        MUST = 0x5453554D,
        QUST = 0x54535551,
        TXST = 0x54535854,
        MATT = 0x5454414D,
        MSTT = 0x5454534D,
        JOUT = 0x54554F4A,
        MOVT = 0x54564F4D,
        RDWT = 0x54574452,
        PHWT = 0x54574850,
        NEXT = 0x5458454E,
        ITXT = 0x54585449,
        PKCU = 0x55434B50,
        XWCU = 0x55435758,
        SHOU = 0x554F4853,
        MPAV = 0x5641504D,
        WKMV = 0x564D4B57,
        FLMV = 0x564D4C46,
        RNMV = 0x564D4E52,
        SNMV = 0x564D4E53,
        SWMV = 0x564D5753,
        VENV = 0x564E4556,
        TINV = 0x564E4954,
        FLTV = 0x56544C46,
        INTV = 0x56544E49,
        XHTW = 0x57544858,
        XLTW = 0x57544C58,
        DLVW = 0x57564C44,
        DMAX = 0x58414D44,
        INDX = 0x58444E49,
        LTEX = 0x5845544C,
        X00TX = 0x58543030,
        X10TX = 0x58543031,
        X20TX = 0x58543032,
        X30TX = 0x58543033,
        X40TX = 0x58543034,
        X50TX = 0x58543035,
        X60TX = 0x58543036,
        X70TX = 0x58543037,
        X80TX = 0x58543038,
        X90TX = 0x58543039,
        
        // :
        XC0TX = 0x5854303A,
        
        // ;
        XS0TX = 0x5854303B,
        
        // <
        XL0TX = 0x5854303C,
        
        // =
        XE0TX = 0x5854303D,
        
        // >
        XG0TX = 0x5854303E,
        
        // ?
        XQ0TX = 0x5854303F,
        
        // @
        XA0TX = 0x58543040,
        A0TX = 0x58543041,
        B0TX = 0x58543042,
        C0TX = 0x58543043,
        D0TX = 0x58543044,
        E0TX = 0x58543045,
        F0TX = 0x58543046,
        G0TX = 0x58543047,
        H0TX = 0x58543048,
        I0TX = 0x58543049,
        J0TX = 0x5854304A,
        K0TX = 0x5854304B,
        L0TX = 0x5854304C,
        SCTX = 0x58544353,
        XXXX = 0x58585858,
        CSTY = 0x59545343,
        KSIZ = 0x5A49534B,
        NPC_ = 0x5F43504E,
        XLRL = 0x4c524c58,
        MICO = 0x4f43494d,
        SLSD = 0x44534c53,
        SCVR = 0x52564353,
        SCRV = 0x56524353,
    };
}