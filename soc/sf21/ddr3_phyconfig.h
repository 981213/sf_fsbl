#ifndef __DDRP_H__
#define __DDRP_H__
#include <stdiol.h>
#include <asm/types.h>
#include "ddr_regs.h"
#include "phyinit3_struct.h"

#define TRAIN_1D_MSG_NUM (412)

int streaming_idx_arr[TRAIN_1D_MSG_NUM];
#if 0
void init_streaming_idx_arr(void) {
        streaming_idx_arr[  0] = 0x00000001;
        streaming_idx_arr[  1] = 0x00010000;
        streaming_idx_arr[  2] = 0x00020000;
        streaming_idx_arr[  3] = 0x00030002;
        streaming_idx_arr[  4] = 0x00040000;
        streaming_idx_arr[  5] = 0x00050000;
        streaming_idx_arr[  6] = 0x00060001;
        streaming_idx_arr[  7] = 0x00070001;
        streaming_idx_arr[  8] = 0x00080000;
        streaming_idx_arr[  9] = 0x00090001;
        streaming_idx_arr[ 10] = 0x000a0001;
        streaming_idx_arr[ 11] = 0x000b0001;
        streaming_idx_arr[ 12] = 0x000c0001;
        streaming_idx_arr[ 13] = 0x000d0001;
        streaming_idx_arr[ 14] = 0x000e0003;
        streaming_idx_arr[ 15] = 0x000f0004;
        streaming_idx_arr[ 16] = 0x00100003;
        streaming_idx_arr[ 17] = 0x00110001;
        streaming_idx_arr[ 18] = 0x00120002;
        streaming_idx_arr[ 19] = 0x00130000;
        streaming_idx_arr[ 20] = 0x00140003;
        streaming_idx_arr[ 21] = 0x00150006;
        streaming_idx_arr[ 22] = 0x00160000;
        streaming_idx_arr[ 23] = 0x00170005;
        streaming_idx_arr[ 24] = 0x00180002;
        streaming_idx_arr[ 25] = 0x00190004;
        streaming_idx_arr[ 26] = 0x001a0002;
        streaming_idx_arr[ 27] = 0x001b0004;
        streaming_idx_arr[ 28] = 0x001c0003;
        streaming_idx_arr[ 29] = 0x001d0000;
        streaming_idx_arr[ 30] = 0x001e0002;
        streaming_idx_arr[ 31] = 0x001f0005;
        streaming_idx_arr[ 32] = 0x00200002;
        streaming_idx_arr[ 33] = 0x00210002;
        streaming_idx_arr[ 34] = 0x00220002;
        streaming_idx_arr[ 35] = 0x00230002;
        streaming_idx_arr[ 36] = 0x00240001;
        streaming_idx_arr[ 37] = 0x00250000;
        streaming_idx_arr[ 38] = 0x00260002;
        streaming_idx_arr[ 39] = 0x00270005;
        streaming_idx_arr[ 40] = 0x00280003;
        streaming_idx_arr[ 41] = 0x00290004;
        streaming_idx_arr[ 42] = 0x002a0000;
        streaming_idx_arr[ 43] = 0x002b0002;
        streaming_idx_arr[ 44] = 0x002c0000;
        streaming_idx_arr[ 45] = 0x002d0000;
        streaming_idx_arr[ 46] = 0x002e0004;
        streaming_idx_arr[ 47] = 0x002f0003;
        streaming_idx_arr[ 48] = 0x00300006;
        streaming_idx_arr[ 49] = 0x00310002;
        streaming_idx_arr[ 50] = 0x00320002;
        streaming_idx_arr[ 51] = 0x00330006;
        streaming_idx_arr[ 52] = 0x00340002;
        streaming_idx_arr[ 53] = 0x00350006;
        streaming_idx_arr[ 54] = 0x00360000;
        streaming_idx_arr[ 55] = 0x00370002;
        streaming_idx_arr[ 56] = 0x00380005;
        streaming_idx_arr[ 57] = 0x00390003;
        streaming_idx_arr[ 58] = 0x003a0002;
        streaming_idx_arr[ 59] = 0x003b0001;
        streaming_idx_arr[ 60] = 0x003c0005;
        streaming_idx_arr[ 61] = 0x003d0009;
        streaming_idx_arr[ 62] = 0x003e0002;
        streaming_idx_arr[ 63] = 0x003f0004;
        streaming_idx_arr[ 64] = 0x00400002;
        streaming_idx_arr[ 65] = 0x00410004;
        streaming_idx_arr[ 66] = 0x00420003;
        streaming_idx_arr[ 67] = 0x00430002;
        streaming_idx_arr[ 68] = 0x00440003;
        streaming_idx_arr[ 69] = 0x00450003;
        streaming_idx_arr[ 70] = 0x00460003;
        streaming_idx_arr[ 71] = 0x00470002;
        streaming_idx_arr[ 72] = 0x00480003;
        streaming_idx_arr[ 73] = 0x00490003;
        streaming_idx_arr[ 74] = 0x004a0000;
        streaming_idx_arr[ 75] = 0x004b0002;
        streaming_idx_arr[ 76] = 0x004c0002;
        streaming_idx_arr[ 77] = 0x004d0001;
        streaming_idx_arr[ 78] = 0x004e0001;
        streaming_idx_arr[ 79] = 0x004f0001;
        streaming_idx_arr[ 80] = 0x00500001;
        streaming_idx_arr[ 81] = 0x00510001;
        streaming_idx_arr[ 82] = 0x00520000;
        streaming_idx_arr[ 83] = 0x00530003;
        streaming_idx_arr[ 84] = 0x00540006;
        streaming_idx_arr[ 85] = 0x00550006;
        streaming_idx_arr[ 86] = 0x00560008;
        streaming_idx_arr[ 87] = 0x00570004;
        streaming_idx_arr[ 88] = 0x00580008;
        streaming_idx_arr[ 89] = 0x00590005;
        streaming_idx_arr[ 90] = 0x005a0000;
        streaming_idx_arr[ 91] = 0x005b0005;
        streaming_idx_arr[ 92] = 0x005c0005;
        streaming_idx_arr[ 93] = 0x005d0005;
        streaming_idx_arr[ 94] = 0x005e0005;
        streaming_idx_arr[ 95] = 0x005f0005;
        streaming_idx_arr[ 96] = 0x00600005;
        streaming_idx_arr[ 97] = 0x00610005;
        streaming_idx_arr[ 98] = 0x00620005;
        streaming_idx_arr[ 99] = 0x00630002;
        streaming_idx_arr[100] = 0x00640002;
        streaming_idx_arr[101] = 0x00650002;
        streaming_idx_arr[102] = 0x00660000;
        streaming_idx_arr[103] = 0x00670001;
        streaming_idx_arr[104] = 0x00680002;
        streaming_idx_arr[105] = 0x00690000;
        streaming_idx_arr[106] = 0x006a0000;
        streaming_idx_arr[107] = 0x006b0009;
        streaming_idx_arr[108] = 0x006c0009;
        streaming_idx_arr[109] = 0x006d0002;
        streaming_idx_arr[110] = 0x006e0000;
        streaming_idx_arr[111] = 0x006f0000;
        streaming_idx_arr[112] = 0x00700001;
        streaming_idx_arr[113] = 0x00710000;
        streaming_idx_arr[114] = 0x00720001;
        streaming_idx_arr[115] = 0x00730001;
        streaming_idx_arr[116] = 0x00740003;
        streaming_idx_arr[117] = 0x00750002;
        streaming_idx_arr[118] = 0x00760002;
        streaming_idx_arr[119] = 0x00770000;
        streaming_idx_arr[120] = 0x00780002;
        streaming_idx_arr[121] = 0x00790002;
        streaming_idx_arr[122] = 0x007a0003;
        streaming_idx_arr[123] = 0x007b0002;
        streaming_idx_arr[124] = 0x007c0001;
        streaming_idx_arr[125] = 0x007d0001;
        streaming_idx_arr[126] = 0x007e0001;
        streaming_idx_arr[127] = 0x007f0001;
        streaming_idx_arr[128] = 0x00800000;
        streaming_idx_arr[129] = 0x00810001;
        streaming_idx_arr[130] = 0x00820001;
        streaming_idx_arr[131] = 0x00830000;
        streaming_idx_arr[132] = 0x00840003;
        streaming_idx_arr[133] = 0x00850001;
        streaming_idx_arr[134] = 0x00860004;
        streaming_idx_arr[135] = 0x00870005;
        streaming_idx_arr[136] = 0x00880003;
        streaming_idx_arr[137] = 0x00890000;
        streaming_idx_arr[138] = 0x008a0004;
        streaming_idx_arr[139] = 0x008b0005;
        streaming_idx_arr[140] = 0x008c0002;
        streaming_idx_arr[141] = 0x008d0005;
        streaming_idx_arr[142] = 0x008e0002;
        streaming_idx_arr[143] = 0x008f0000;
        streaming_idx_arr[144] = 0x00900003;
        streaming_idx_arr[145] = 0x00910000;
        streaming_idx_arr[146] = 0x00920000;
        streaming_idx_arr[147] = 0x00930001;
        streaming_idx_arr[148] = 0x00940001;
        streaming_idx_arr[149] = 0x00950001;
        streaming_idx_arr[150] = 0x00960001;
        streaming_idx_arr[151] = 0x00970000;
        streaming_idx_arr[152] = 0x00980001;
        streaming_idx_arr[153] = 0x00990001;
        streaming_idx_arr[154] = 0x009a0000;
        streaming_idx_arr[155] = 0x009b0003;
        streaming_idx_arr[156] = 0x009c0001;
        streaming_idx_arr[157] = 0x009d0001;
        streaming_idx_arr[158] = 0x009e0002;
        streaming_idx_arr[159] = 0x009f0002;
        streaming_idx_arr[160] = 0x00a00000;
        streaming_idx_arr[161] = 0x00a10003;
        streaming_idx_arr[162] = 0x00a20002;
        streaming_idx_arr[163] = 0x00a30001;
        streaming_idx_arr[164] = 0x00a40001;
        streaming_idx_arr[165] = 0x00a50000;
        streaming_idx_arr[166] = 0x00a60000;
        streaming_idx_arr[167] = 0x00a70003;
        streaming_idx_arr[168] = 0x00a80002;
        streaming_idx_arr[169] = 0x00a90000;
        streaming_idx_arr[170] = 0x00aa0000;
        streaming_idx_arr[171] = 0x00ab0000;
        streaming_idx_arr[172] = 0x00ac0000;
        streaming_idx_arr[173] = 0x00ad0000;
        streaming_idx_arr[174] = 0x00ae0000;
        streaming_idx_arr[175] = 0x00af0001;
        streaming_idx_arr[176] = 0x00b00000;
        streaming_idx_arr[177] = 0x00b10000;
        streaming_idx_arr[178] = 0x00b20000;
        streaming_idx_arr[179] = 0x00b30000;
        streaming_idx_arr[180] = 0x00b40000;
        streaming_idx_arr[181] = 0x00b50001;
        streaming_idx_arr[182] = 0x00b60001;
        streaming_idx_arr[183] = 0x00b70001;
        streaming_idx_arr[184] = 0x00b80001;
        streaming_idx_arr[185] = 0x00b90000;
        streaming_idx_arr[186] = 0x00ba0001;
        streaming_idx_arr[187] = 0x00bb0000;
        streaming_idx_arr[188] = 0x00bc0000;
        streaming_idx_arr[189] = 0x00bd0000;
        streaming_idx_arr[190] = 0x00be0000;
        streaming_idx_arr[191] = 0x00bf0000;
        streaming_idx_arr[192] = 0x00c00000;
        streaming_idx_arr[193] = 0x00c10000;
        streaming_idx_arr[194] = 0x00c20000;
        streaming_idx_arr[195] = 0x00c30000;
        streaming_idx_arr[196] = 0x00c40000;
        streaming_idx_arr[197] = 0x00c50000;
        streaming_idx_arr[198] = 0x00c60000;
        streaming_idx_arr[199] = 0x00c70000;
        streaming_idx_arr[200] = 0x00c80000;
        streaming_idx_arr[201] = 0x00c90000;
        streaming_idx_arr[202] = 0x00ca0000;
        streaming_idx_arr[203] = 0x00cb0000;
        streaming_idx_arr[204] = 0x00cc0000;
        streaming_idx_arr[205] = 0x00cd0000;
        streaming_idx_arr[206] = 0x00ce0000;
        streaming_idx_arr[207] = 0x00cf0000;
        streaming_idx_arr[208] = 0x00d00000;
        streaming_idx_arr[209] = 0x00d10000;
        streaming_idx_arr[210] = 0x00d20000;
        streaming_idx_arr[211] = 0x00d30000;
        streaming_idx_arr[212] = 0x00d40000;
        streaming_idx_arr[213] = 0x00d50002;
        streaming_idx_arr[214] = 0x00d60001;
        streaming_idx_arr[215] = 0x00d70001;
        streaming_idx_arr[216] = 0x00d80001;
        streaming_idx_arr[217] = 0x00d90005;
        streaming_idx_arr[218] = 0x00da0001;
        streaming_idx_arr[219] = 0x00db0000;
        streaming_idx_arr[220] = 0x00dc0000;
        streaming_idx_arr[221] = 0x00dd0002;
        streaming_idx_arr[222] = 0x00de0002;
        streaming_idx_arr[223] = 0x00df0002;
        streaming_idx_arr[224] = 0x00e00001;
        streaming_idx_arr[225] = 0x00e10002;
        streaming_idx_arr[226] = 0x00e20003;
        streaming_idx_arr[227] = 0x00e30003;
        streaming_idx_arr[228] = 0x00e40003;
        streaming_idx_arr[229] = 0x00e50000;
        streaming_idx_arr[230] = 0x00e60000;
        streaming_idx_arr[231] = 0x00e70000;
        streaming_idx_arr[232] = 0x00e80000;
        streaming_idx_arr[233] = 0x00e90000;
        streaming_idx_arr[234] = 0x00ea0001;
        streaming_idx_arr[235] = 0x00eb0001;
        streaming_idx_arr[236] = 0x00ec0005;
        streaming_idx_arr[237] = 0x00ed0004;
        streaming_idx_arr[238] = 0x00ee0001;
        streaming_idx_arr[239] = 0x00ef000b;
        streaming_idx_arr[240] = 0x00f00003;
        streaming_idx_arr[241] = 0x00f10000;
        streaming_idx_arr[242] = 0x00f20001;
        streaming_idx_arr[243] = 0x00f30001;
        streaming_idx_arr[244] = 0x00f40001;
        streaming_idx_arr[245] = 0x00f50001;
        streaming_idx_arr[246] = 0x00f60000;
        streaming_idx_arr[247] = 0x00f70000;
        streaming_idx_arr[248] = 0x00f80000;
        streaming_idx_arr[249] = 0x00f90000;
        streaming_idx_arr[250] = 0x00fa0003;
        streaming_idx_arr[251] = 0x00fb0003;
        streaming_idx_arr[252] = 0x00fc0000;
        streaming_idx_arr[253] = 0x00fd0001;
        streaming_idx_arr[254] = 0x00fe0003;
        streaming_idx_arr[255] = 0x00ff0003;
        streaming_idx_arr[256] = 0x01000003;
        streaming_idx_arr[257] = 0x01010003;
        streaming_idx_arr[258] = 0x01020003;
        streaming_idx_arr[259] = 0x01030003;
        streaming_idx_arr[260] = 0x01040003;
        streaming_idx_arr[261] = 0x01050003;
        streaming_idx_arr[262] = 0x01060003;
        streaming_idx_arr[263] = 0x01070003;
        streaming_idx_arr[264] = 0x01080003;
        streaming_idx_arr[265] = 0x01090003;
        streaming_idx_arr[266] = 0x010a0004;
        streaming_idx_arr[267] = 0x010b0004;
        streaming_idx_arr[268] = 0x010c0004;
        streaming_idx_arr[269] = 0x010d0004;
        streaming_idx_arr[270] = 0x010e0004;
        streaming_idx_arr[271] = 0x010f0004;
        streaming_idx_arr[272] = 0x01100004;
        streaming_idx_arr[273] = 0x01110004;
        streaming_idx_arr[274] = 0x01120000;
        streaming_idx_arr[275] = 0x01130003;
        streaming_idx_arr[276] = 0x01140000;
        streaming_idx_arr[277] = 0x01150001;
        streaming_idx_arr[278] = 0x01160001;
        streaming_idx_arr[279] = 0x01170001;
        streaming_idx_arr[280] = 0x01180001;
        streaming_idx_arr[281] = 0x01190001;
        streaming_idx_arr[282] = 0x011a0001;
        streaming_idx_arr[283] = 0x011b0001;
        streaming_idx_arr[284] = 0x011c0001;
        streaming_idx_arr[285] = 0x011d0001;
        streaming_idx_arr[286] = 0x011e0001;
        streaming_idx_arr[287] = 0x011f0001;
        streaming_idx_arr[288] = 0x01200001;
        streaming_idx_arr[289] = 0x01210000;
        streaming_idx_arr[290] = 0x01220002;
        streaming_idx_arr[291] = 0x01230002;
        streaming_idx_arr[292] = 0x01240002;
        streaming_idx_arr[293] = 0x01250001;
        streaming_idx_arr[294] = 0x01260002;
        streaming_idx_arr[295] = 0x01270002;
        streaming_idx_arr[296] = 0x01280002;
        streaming_idx_arr[297] = 0x01290002;
        streaming_idx_arr[298] = 0x012a0003;
        streaming_idx_arr[299] = 0x012b0002;
        streaming_idx_arr[300] = 0x012c0000;
        streaming_idx_arr[301] = 0x012d0004;
        streaming_idx_arr[302] = 0x012e0003;
        streaming_idx_arr[303] = 0x012f0003;
        streaming_idx_arr[304] = 0x01300002;
        streaming_idx_arr[305] = 0x01310003;
        streaming_idx_arr[306] = 0x01320003;
        streaming_idx_arr[307] = 0x01330003;
        streaming_idx_arr[308] = 0x01340003;
        streaming_idx_arr[309] = 0x01350001;
        streaming_idx_arr[310] = 0x01360000;
        streaming_idx_arr[311] = 0x01370000;
        streaming_idx_arr[312] = 0x01380000;
        streaming_idx_arr[313] = 0x01390000;
        streaming_idx_arr[314] = 0x013a0000;
        streaming_idx_arr[315] = 0x013b0002;
        streaming_idx_arr[316] = 0x013c0002;
        streaming_idx_arr[317] = 0x013d0002;
        streaming_idx_arr[318] = 0x013e0002;
        streaming_idx_arr[319] = 0x013f0000;
        streaming_idx_arr[320] = 0x01400002;
        streaming_idx_arr[321] = 0x01410001;
        streaming_idx_arr[322] = 0x01420001;
        streaming_idx_arr[323] = 0x01430001;
        streaming_idx_arr[324] = 0x01440002;
        streaming_idx_arr[325] = 0x01450002;
        streaming_idx_arr[326] = 0x01460002;
        streaming_idx_arr[327] = 0x01470003;
        streaming_idx_arr[328] = 0x01480000;
        streaming_idx_arr[329] = 0x01490000;
        streaming_idx_arr[330] = 0x014a0007;
        streaming_idx_arr[331] = 0x014b0000;
        streaming_idx_arr[332] = 0x014c0000;
        streaming_idx_arr[333] = 0x014d0001;
        streaming_idx_arr[334] = 0x014e0003;
        streaming_idx_arr[335] = 0x014f0003;
        streaming_idx_arr[336] = 0x01500003;
        streaming_idx_arr[337] = 0x01510004;
        streaming_idx_arr[338] = 0x01520003;
        streaming_idx_arr[339] = 0x01530003;
        streaming_idx_arr[340] = 0x01540002;
        streaming_idx_arr[341] = 0x01550002;
        streaming_idx_arr[342] = 0x01560000;
        streaming_idx_arr[343] = 0x01570001;
        streaming_idx_arr[344] = 0x01580003;
        streaming_idx_arr[345] = 0x01590003;
        streaming_idx_arr[346] = 0x015a0003;
        streaming_idx_arr[347] = 0x015b0004;
        streaming_idx_arr[348] = 0x015c0003;
        streaming_idx_arr[349] = 0x015d0003;
        streaming_idx_arr[350] = 0x015e0002;
        streaming_idx_arr[351] = 0x015f0002;
        streaming_idx_arr[352] = 0x01600000;
        streaming_idx_arr[353] = 0x01610000;
        streaming_idx_arr[354] = 0x01620009;
        streaming_idx_arr[355] = 0x01630000;
        streaming_idx_arr[356] = 0x01640001;
        streaming_idx_arr[357] = 0x01650001;
        streaming_idx_arr[358] = 0x01660002;
        streaming_idx_arr[359] = 0x01670003;
        streaming_idx_arr[360] = 0x01680005;
        streaming_idx_arr[361] = 0x01690002;
        streaming_idx_arr[362] = 0x016a0002;
        streaming_idx_arr[363] = 0x016b0000;
        streaming_idx_arr[364] = 0x016c0001;
        streaming_idx_arr[365] = 0x016d0003;
        streaming_idx_arr[366] = 0x016e0002;
        streaming_idx_arr[367] = 0x016f0003;
        streaming_idx_arr[368] = 0x01700000;
        streaming_idx_arr[369] = 0x01710002;
        streaming_idx_arr[370] = 0x01720002;
        streaming_idx_arr[371] = 0x01730003;
        streaming_idx_arr[372] = 0x04000000;
        streaming_idx_arr[373] = 0x04010000;
        streaming_idx_arr[374] = 0x04020000;
        streaming_idx_arr[375] = 0x04030002;
        streaming_idx_arr[376] = 0x04040003;
        streaming_idx_arr[377] = 0x04050002;
        streaming_idx_arr[378] = 0x04060002;
        streaming_idx_arr[379] = 0x04070001;
        streaming_idx_arr[380] = 0x04080001;
        streaming_idx_arr[381] = 0x0409000c;
        streaming_idx_arr[382] = 0x040a0000;
        streaming_idx_arr[383] = 0x040b0000;
        streaming_idx_arr[384] = 0x040c0000;
        streaming_idx_arr[385] = 0x040d0002;
        streaming_idx_arr[386] = 0x040e0002;
        streaming_idx_arr[387] = 0x040f0002;
        streaming_idx_arr[388] = 0x04100002;
        streaming_idx_arr[389] = 0x04110001;
        streaming_idx_arr[390] = 0x04120001;
        streaming_idx_arr[391] = 0x04130001;
        streaming_idx_arr[392] = 0x04140000;
        streaming_idx_arr[393] = 0x04150001;
        streaming_idx_arr[394] = 0x04160000;
        streaming_idx_arr[395] = 0x04170002;
        streaming_idx_arr[396] = 0x04180000;
        streaming_idx_arr[397] = 0x04190001;
        streaming_idx_arr[398] = 0x041a0000;
        streaming_idx_arr[399] = 0x041b0000;
        streaming_idx_arr[400] = 0x041c0000;
        streaming_idx_arr[401] = 0x041d0002;
        streaming_idx_arr[402] = 0x041e0001;
        streaming_idx_arr[403] = 0x041f0000;
        streaming_idx_arr[404] = 0x04200000;
        streaming_idx_arr[405] = 0x04210001;
        streaming_idx_arr[406] = 0x04220001;
        streaming_idx_arr[407] = 0x04230001;
        streaming_idx_arr[408] = 0x04240001;
        streaming_idx_arr[409] = 0x04250000;
        streaming_idx_arr[410] = 0x04260003;
        streaming_idx_arr[411] = 0x04270005;
}
#endif
#if 0
void init_streaming_msg_arr(void) {
        strcpy(streaming_msg_arr[  0], "PMU1:prbsGenCtl:%x\n");
        strcpy(streaming_msg_arr[  1], "PMU1: loading 2D acsm sequence\n");
        strcpy(streaming_msg_arr[  2], "PMU1: loading 1D acsm sequence\n");
        strcpy(streaming_msg_arr[  3], "PMU3: %d memclocks @ %d to get half of 300ns\n");
        strcpy(streaming_msg_arr[  4], "PMU: Error: User requested MPR read pattern for read DQS training in DDR3 Mode\n");
        strcpy(streaming_msg_arr[  5], "PMU3: Running 1D search for left eye edge\n");
        strcpy(streaming_msg_arr[  6], "PMU1: In Phase Left Edge Search cs %d\n");
        strcpy(streaming_msg_arr[  7], "PMU1: Out of Phase Left Edge Search cs %d\n");
        strcpy(streaming_msg_arr[  8], "PMU3: Running 1D search for right eye edge\n");
        strcpy(streaming_msg_arr[  9], "PMU1: In Phase Right Edge Search cs %d\n");
        strcpy(streaming_msg_arr[ 10], "PMU1: Out of Phase Right Edge Search cs %d\n");
        strcpy(streaming_msg_arr[ 11], "PMU1: mxRdLat training pstate %d\n");
        strcpy(streaming_msg_arr[ 12], "PMU1: mxRdLat search for cs %d\n");
        strcpy(streaming_msg_arr[ 13], "PMU0: MaxRdLat non consistant DtsmLoThldXingInd 0x%03x\n");
        strcpy(streaming_msg_arr[ 14], "PMU4: CS %d Dbyte %d worked with DFIMRL = %d DFICLKs \n");
        strcpy(streaming_msg_arr[ 15], "PMU3: MaxRdLat Read Lane err mask for csn %d, DFIMRL %2d DFIClks, dbyte %d = 0x%03x\n");
        strcpy(streaming_msg_arr[ 16], "PMU3: MaxRdLat Read Lane err mask for csn %d DFIMRL %2d, All dbytes = 0x%03x\n");
        strcpy(streaming_msg_arr[ 17], "PMU: Error: CS%d failed to find a DFIMRL setting that worked for all bytes during MaxRdLat training\n");
        strcpy(streaming_msg_arr[ 18], "PMU3: Smallest passing DFIMRL for all dbytes in CS%d = %d DFIClks\n");
        strcpy(streaming_msg_arr[ 19], "PMU: Error: No passing DFIMRL value found for any chip select during MaxRdLat training\n");
        strcpy(streaming_msg_arr[ 20], "PMU: Error: Dbyte %d lane %d txDqDly passing region is too small (width = %d)\n");
        strcpy(streaming_msg_arr[ 21], "PMU4: Adjusting rxclkdly db %d nib %d from %d+%d=%d->%d\n");
        strcpy(streaming_msg_arr[ 22], "PMU4: TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\n");
        strcpy(streaming_msg_arr[ 23], "PMU4: DB %d Lane %d: %3d %3d -> %3d\n");
        strcpy(streaming_msg_arr[ 24], "PMU2: TXDQ delayLeft[%2d] = %3d (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 25], "PMU2: TXDQ delayLeft[%2d] = %3d oopScaled = %3d selectOop %d\n");
        strcpy(streaming_msg_arr[ 26], "PMU2: TXDQ delayRight[%2d] = %3d (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 27], "PMU2: TXDQ delayRight[%2d] = %3d oopScaled = %3d selectOop %d\n");
        strcpy(streaming_msg_arr[ 28], "PMU: Error: Dbyte %d lane %d txDqDly passing region is too small (width = %d)\n");
        strcpy(streaming_msg_arr[ 29], "PMU4: TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\n");
        strcpy(streaming_msg_arr[ 30], "PMU4: DB %d Lane %d: (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 31], "PMU4: DB %d Lane %d: %3d %3d -> %3d\n");
        strcpy(streaming_msg_arr[ 32], "PMU3: Running 1D search csn %d for DM Right/NotLeft(%d) eye edge\n");
        strcpy(streaming_msg_arr[ 33], "PMU3: WrDq DM byte%2d with Errcnt %d\n");
        strcpy(streaming_msg_arr[ 34], "PMU3: WrDq DM byte%2d avgDly 0x%04x\n");
        strcpy(streaming_msg_arr[ 35], "PMU1: WrDq DM byte%2d with Errcnt %d\n");
        strcpy(streaming_msg_arr[ 36], "PMU: Error: Dbyte %d txDqDly DM training did not start inside the eye\n");
        strcpy(streaming_msg_arr[ 37], "PMU4: DM TxDqDly Passing Regions (EyeLeft EyeRight -> EyeCenter) Units=1/32 UI\n");
        strcpy(streaming_msg_arr[ 38], "PMU4: DB %d Lane %d: (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 39], "PMU4: DB %d Lane %d: %3d %3d -> %3d\n");
        strcpy(streaming_msg_arr[ 40], "PMU: Error: Dbyte %d lane %d txDqDly DM passing region is too small (width = %d)\n");
        strcpy(streaming_msg_arr[ 41], "PMU3: Errcnt for MRD/MWD search nib %2d delay = (%d, 0x%02x) = %d\n");
        strcpy(streaming_msg_arr[ 42], "PMU3: Precharge all open banks\n");
        strcpy(streaming_msg_arr[ 43], "PMU: Error: Dbyte %d nibble %d found multiple working coarse delay setting for MRD/MWD\n");
        strcpy(streaming_msg_arr[ 44], "PMU4: MRD Passing Regions (coarseVal, fineLeft fineRight -> fineCenter)\n");
        strcpy(streaming_msg_arr[ 45], "PMU4: MWD Passing Regions (coarseVal, fineLeft fineRight -> fineCenter)\n");
        strcpy(streaming_msg_arr[ 46], "PMU10: Warning: DB %d nibble %d has multiple working coarse positions, %d and %d, choosing the smaller delay\n");
        strcpy(streaming_msg_arr[ 47], "PMU: Error: Dbyte %d nibble %d MRD/MWD passing region is too small (width = %d)\n");
        strcpy(streaming_msg_arr[ 48], "PMU4: DB %d nibble %d: %3d, %3d %3d -> %3d\n");
        strcpy(streaming_msg_arr[ 49], "PMU1: Start MRD/nMWD %d for csn %d\n");
        strcpy(streaming_msg_arr[ 50], "PMU2: RXDQS delayLeft[%2d] = %3d (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 51], "PMU2: RXDQS delayLeft[%2d] = %3d delayOop[%2d] = %3d OopScaled %4d, selectOop %d\n");
        strcpy(streaming_msg_arr[ 52], "PMU2: RXDQS delayRight[%2d] = %3d (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 53], "PMU2: RXDQS delayRight[%2d] = %3d delayOop[%2d] = %4d OopScaled %4d, selectOop %d\n");
        strcpy(streaming_msg_arr[ 54], "PMU4: RxClkDly Passing Regions (EyeLeft EyeRight -> EyeCenter)\n");
        strcpy(streaming_msg_arr[ 55], "PMU4: DB %d nibble %d: (DISCONNECTED)\n");
        strcpy(streaming_msg_arr[ 56], "PMU4: DB %d nibble %d: %3d %3d -> %3d\n");
        strcpy(streaming_msg_arr[ 57], "PMU: Error: Dbyte %d nibble %d rxClkDly passing region is too small (width = %d)\n");
        strcpy(streaming_msg_arr[ 58], "PMU0: goodbar = %d for RDWR_BLEN %d\n");
        strcpy(streaming_msg_arr[ 59], "PMU3: RxClkDly = %d\n");
        strcpy(streaming_msg_arr[ 60], "PMU0: db %d l %d absLane %d -> bottom %d top %d\n");
        strcpy(streaming_msg_arr[ 61], "PMU3: BYTE %d - %3d %3d %3d %3d %3d %3d %3d %3d\n");
        strcpy(streaming_msg_arr[ 62], "PMU: Error: dbyte %d lane %d's per-lane vrefDAC's had no passing region\n");
        strcpy(streaming_msg_arr[ 63], "PMU0: db%d l%d - %d %d\n");
        strcpy(streaming_msg_arr[ 64], "PMU0: goodbar = %d for RDWR_BLEN %d\n");
        strcpy(streaming_msg_arr[ 65], "PMU3: db%d l%d saw %d issues at rxClkDly %d\n");
        strcpy(streaming_msg_arr[ 66], "PMU3: db%d l%d first saw a pass->fail edge at rxClkDly %d\n");
        strcpy(streaming_msg_arr[ 67], "PMU3: lane %d PBD = %d\n");
        strcpy(streaming_msg_arr[ 68], "PMU3: db%d l%d first saw a DBI pass->fail edge at rxClkDly %d\n");
        strcpy(streaming_msg_arr[ 69], "PMU2: db%d l%d already passed rxPBD = %d\n");
        strcpy(streaming_msg_arr[ 70], "PMU0: db%d l%d, PBD = %d\n");
        strcpy(streaming_msg_arr[ 71], "PMU: Error: dbyte %d lane %d failed read deskew\n");
        strcpy(streaming_msg_arr[ 72], "PMU0: db%d l%d, inc PBD = %d\n");
        strcpy(streaming_msg_arr[ 73], "PMU1: Running lane deskew on pstate %d csn %d rdDBIEn %d\n");
        strcpy(streaming_msg_arr[ 74], "PMU: Error: Read deskew training has been requested, but csrMajorModeDbyte[2] is set\n");
        strcpy(streaming_msg_arr[ 75], "PMU1: AcsmCsMapCtrl%02d 0x%04x\n");
        strcpy(streaming_msg_arr[ 76], "PMU1: AcsmCsMapCtrl%02d 0x%04x\n");
        strcpy(streaming_msg_arr[ 77], "PMU: Error: Wrong PMU image loaded. message Block DramType = 0x%02x, but image built for D3U Type\n");
        strcpy(streaming_msg_arr[ 78], "PMU: Error: Wrong PMU image loaded. message Block DramType = 0x%02x, but image built for D3R Type\n");
        strcpy(streaming_msg_arr[ 79], "PMU: Error: Wrong PMU image loaded. message Block DramType = 0x%02x, but image built for D4U Type\n");
        strcpy(streaming_msg_arr[ 80], "PMU: Error: Wrong PMU image loaded. message Block DramType = 0x%02x, but image built for D4R Type\n");
        strcpy(streaming_msg_arr[ 81], "PMU: Error: Wrong PMU image loaded. message Block DramType = 0x%02x, but image built for D4LR Type\n");
        strcpy(streaming_msg_arr[ 82], "PMU: Error: Both 2t timing mode and ddr4 geardown mode specifed in the messageblock's PhyCfg and MR3 fields. Only one can be enabled\n");
        strcpy(streaming_msg_arr[ 83], "PMU10: PHY TOTALS - NUM_DBYTES %d NUM_NIBBLES %d NUM_ANIBS %d\n");
        strcpy(streaming_msg_arr[ 84], "PMU10: CSA=0x%02X, CSB=0x%02X, TSTAGES=0x%04X, HDTOUT=%d, MMISC=%d DRAMFreq=%dMT DramType=LPDDR3\n");
        strcpy(streaming_msg_arr[ 85], "PMU10: CSA=0x%02X, CSB=0x%02X, TSTAGES=0x%04X, HDTOUT=%d, MMISC=%d DRAMFreq=%dMT DramType=LPDDR4\n");
        strcpy(streaming_msg_arr[ 86], "PMU10: CS=0x%02X, TSTAGES=0x%04X, HDTOUT=%d, 2T=%d, MMISC=%d AddrMirror=%d DRAMFreq=%dMT DramType=%d\n");
        strcpy(streaming_msg_arr[ 87], "PMU10: Pstate%d MR0=0x%04X MR1=0x%04X MR2=0x%04X\n");
        strcpy(streaming_msg_arr[ 88], "PMU10: Pstate%d MRS MR0=0x%04X MR1=0x%04X MR2=0x%04X MR3=0x%04X MR4=0x%04X MR5=0x%04X MR6=0x%04X\n");
        strcpy(streaming_msg_arr[ 89], "PMU10: Pstate%d MRS MR1_A0=0x%04X MR2_A0=0x%04X MR3_A0=0x%04X MR11_A0=0x%04X\n");
        strcpy(streaming_msg_arr[ 90], "PMU10: UseBroadcastMR set. All ranks and channels use MRXX_A0 for MR settings.\n");
        strcpy(streaming_msg_arr[ 91], "PMU10: Pstate%d MRS MR01_A0=0x%02X MR02_A0=0x%02X MR03_A0=0x%02X MR11_A0=0x%02X\n");
        strcpy(streaming_msg_arr[ 92], "PMU10: Pstate%d MRS MR12_A0=0x%02X MR13_A0=0x%02X MR14_A0=0x%02X MR22_A0=0x%02X\n");
        strcpy(streaming_msg_arr[ 93], "PMU10: Pstate%d MRS MR01_A1=0x%02X MR02_A1=0x%02X MR03_A1=0x%02X MR11_A1=0x%02X\n");
        strcpy(streaming_msg_arr[ 94], "PMU10: Pstate%d MRS MR12_A1=0x%02X MR13_A1=0x%02X MR14_A1=0x%02X MR22_A1=0x%02X\n");
        strcpy(streaming_msg_arr[ 95], "PMU10: Pstate%d MRS MR01_B0=0x%02X MR02_B0=0x%02X MR03_B0=0x%02X MR11_B0=0x%02X\n");
        strcpy(streaming_msg_arr[ 96], "PMU10: Pstate%d MRS MR12_B0=0x%02X MR13_B0=0x%02X MR14_B0=0x%02X MR22_B0=0x%02X\n");
        strcpy(streaming_msg_arr[ 97], "PMU10: Pstate%d MRS MR01_B1=0x%02X MR02_B1=0x%02X MR03_B1=0x%02X MR11_B1=0x%02X\n");
        strcpy(streaming_msg_arr[ 98], "PMU10: Pstate%d MRS MR12_B1=0x%02X MR13_B1=0x%02X MR14_B1=0x%02X MR22_B1=0x%02X\n");
        strcpy(streaming_msg_arr[ 99], "PMU1: AcsmOdtCtrl%02d 0x%02x\n");
        strcpy(streaming_msg_arr[100], "PMU1: AcsmCsMapCtrl%02d 0x%04x\n");
        strcpy(streaming_msg_arr[101], "PMU1: AcsmCsMapCtrl%02d 0x%04x\n");
        strcpy(streaming_msg_arr[102], "PMU1: HwtCAMode set\n");
        strcpy(streaming_msg_arr[103], "PMU3: DDR4 infinite preamble enter/exit mode %d\n");
        strcpy(streaming_msg_arr[104], "PMU1: In rxenb_train() csn=%d pstate=%d\n");
        strcpy(streaming_msg_arr[105], "PMU3: Finding DQS falling edge\n");
        strcpy(streaming_msg_arr[106], "PMU3: Searching for DDR3/LPDDR3/LPDDR4 read preamble\n");
        strcpy(streaming_msg_arr[107], "PMU3: dtsm fails Even Nibbles : %2x %2x %2x %2x %2x %2x %2x %2x %2x\n");
        strcpy(streaming_msg_arr[108], "PMU3: dtsm fails Odd  Nibbles : %2x %2x %2x %2x %2x %2x %2x %2x %2x\n");
        strcpy(streaming_msg_arr[109], "PMU3: Preamble search pass=%d anyfail=%d\n");
        strcpy(streaming_msg_arr[110], "PMU: Error: RxEn training preamble not found\n");
        strcpy(streaming_msg_arr[111], "PMU3: Found DQS pre-amble\n");
        strcpy(streaming_msg_arr[112], "PMU: Error: Dbyte %d couldn't find the rising edge of DQS during RxEn Training\n");
        strcpy(streaming_msg_arr[113], "PMU3: RxEn aligning to first rising edge of burst\n");
        strcpy(streaming_msg_arr[114], "PMU3: Decreasing RxEn delay by %d fine step to allow full capture of reads\n");
        strcpy(streaming_msg_arr[115], "PMU3: MREP Delay = %d\n");
        strcpy(streaming_msg_arr[116], "PMU3: Errcnt for MREP nib %2d delay = %2d is %d\n");
        strcpy(streaming_msg_arr[117], "PMU3: MREP nibble %d sampled a 1 at data buffer delay %d\n");
        strcpy(streaming_msg_arr[118], "PMU3: MREP nibble %d saw a 0 to 1 transition at data buffer delay %d\n");
        strcpy(streaming_msg_arr[119], "PMU2:  MREP did not find a 0 to 1 transition for all nibbles. Failing nibbles assumed to have rising edge close to fine delay 63\n");
        strcpy(streaming_msg_arr[120], "PMU2:  Rising edge found in alias window, setting rxDly for nibble %d = %d\n");
        strcpy(streaming_msg_arr[121], "PMU: Error: Failed MREP for nib %d with %d one\n");
        strcpy(streaming_msg_arr[122], "PMU2:  Rising edge not found in alias window with %d one, leaving rxDly for nibble %d = %d\n");
        strcpy(streaming_msg_arr[123], "PMU3: Training DIMM %d CSn %d\n");
        strcpy(streaming_msg_arr[124], "PMU3: exitCAtrain_lp3 cs 0x%x\n");
        strcpy(streaming_msg_arr[125], "PMU3: enterCAtrain_lp3 cs 0x%x\n");
        strcpy(streaming_msg_arr[126], "PMU3: CAtrain_switchmsb_lp3 cs 0x%x\n");
        strcpy(streaming_msg_arr[127], "PMU3: CATrain_rdwr_lp3 looking for pattern %x\n");
        strcpy(streaming_msg_arr[128], "PMU3: exitCAtrain_lp4\n");
        strcpy(streaming_msg_arr[129], "PMU3: DEBUG enterCAtrain_lp4 1: cs 0x%x\n");
        strcpy(streaming_msg_arr[130], "PMU3: DEBUG enterCAtrain_lp4 3: Put dbyte %d in async mode\n");
        strcpy(streaming_msg_arr[131], "PMU3: DEBUG enterCAtrain_lp4 5: Send MR13 to turn on CA training\n");
        strcpy(streaming_msg_arr[132], "PMU3: DEBUG enterCAtrain_lp4 7: idx = %d vref = %x mr12 = %x \n");
        strcpy(streaming_msg_arr[133], "PMU3: CATrain_rdwr_lp4 looking for pattern %x\n");
        strcpy(streaming_msg_arr[134], "PMU3: Phase %d CAreadbackA db:%d %x xo:%x\n");
        strcpy(streaming_msg_arr[135], "PMU3: DEBUG lp4SetCatrVref 1: cs=%d chan=%d mr12=%x vref=%d.%d%%\n");
        strcpy(streaming_msg_arr[136], "PMU3: DEBUG lp4SetCatrVref 3: mr12 = %x send vref= %x to db=%d\n");
        strcpy(streaming_msg_arr[137], "PMU10:Optimizing vref\n");
        strcpy(streaming_msg_arr[138], "PMU4:mr12:%2x cs:%d chan %d r:%4x\n");
        strcpy(streaming_msg_arr[139], "PMU3: i:%2d bstr:%2d bsto:%2d st:%d r:%d\n");
        strcpy(streaming_msg_arr[140], "Failed to find sufficient CA Vref Passing Region for CS %d channel %d\n");
        strcpy(streaming_msg_arr[141], "PMU3:Found %d.%d%% MR12:%x for cs:%d chan %d\n");
        strcpy(streaming_msg_arr[142], "PMU3:Calculated %d for AtxImpedence from acx %d.\n");
        strcpy(streaming_msg_arr[143], "PMU3:CA Odt impedence ==0.  Use default vref.\n");
        strcpy(streaming_msg_arr[144], "PMU3:Calculated %d.%d%% for Vref MR12=0x%x.\n");
        strcpy(streaming_msg_arr[145], "PMU3: CAtrain_lp\n");
        strcpy(streaming_msg_arr[146], "PMU3: CAtrain Begins.\n");
        strcpy(streaming_msg_arr[147], "PMU3: CAtrain_lp testing dly %d\n");
        strcpy(streaming_msg_arr[148], "PMU5: CA bitmap dump for cs %x\n");
        strcpy(streaming_msg_arr[149], "PMU5: CAA%d ");
        strcpy(streaming_msg_arr[150], "%02x");
        strcpy(streaming_msg_arr[151], "\n");
        strcpy(streaming_msg_arr[152], "PMU5: CAB%d ");
        strcpy(streaming_msg_arr[153], "%02x");
        strcpy(streaming_msg_arr[154], "\n");
        strcpy(streaming_msg_arr[155], "PMU3: anibi=%d, anibichan[anibi]=%d ,chan=%d\n");
        strcpy(streaming_msg_arr[156], "%02x");
        strcpy(streaming_msg_arr[157], "\nPMU3:Raw CA setting :%x");
        strcpy(streaming_msg_arr[158], "\nPMU3:ATxDly setting:%x margin:%d\n");
        strcpy(streaming_msg_arr[159], "\nPMU3:InvClk ATxDly setting:%x margin:%d\n");
        strcpy(streaming_msg_arr[160], "\nPMU3:No Range found!\n");
        strcpy(streaming_msg_arr[161], "PMU3: 2 anibi=%d, anibichan[anibi]=%d ,chan=%d");
        strcpy(streaming_msg_arr[162], "\nPMU3: no neg clock => CA setting anib=%d, :%d\n");
        strcpy(streaming_msg_arr[163], "PMU3:Normal margin:%d\n");
        strcpy(streaming_msg_arr[164], "PMU3:Inverted margin:%d\n");
        strcpy(streaming_msg_arr[165], "PMU3:Using Inverted clock\n");
        strcpy(streaming_msg_arr[166], "PMU3:Using normal clk\n");
        strcpy(streaming_msg_arr[167], "PMU3: 3 anibi=%d, anibichan[anibi]=%d ,chan=%d\n");
        strcpy(streaming_msg_arr[168], "PMU3: Setting ATxDly for anib %x to %x\n");
        strcpy(streaming_msg_arr[169], "PMU: Error: CA Training Failed.\n");
        strcpy(streaming_msg_arr[170], "PMU1: Writing MRs\n");
        strcpy(streaming_msg_arr[171], "PMU4:Using MR12 values from 1D CA VREF training.\n");
        strcpy(streaming_msg_arr[172], "PMU3:Writing all MRs to fsp 1\n");
        strcpy(streaming_msg_arr[173], "PMU10:Lp4Quickboot mode.\n");
        strcpy(streaming_msg_arr[174], "PMU3: Writing MRs\n");
        strcpy(streaming_msg_arr[175], "PMU10: Setting boot clock divider to %d\n");
        strcpy(streaming_msg_arr[176], "PMU3: Resetting DRAM\n");
        strcpy(streaming_msg_arr[177], "PMU3: setup for RCD initalization\n");
        strcpy(streaming_msg_arr[178], "PMU3: pmu_exit_SR from dev_init()\n");
        strcpy(streaming_msg_arr[179], "PMU3: initializing RCD\n");
        strcpy(streaming_msg_arr[180], "PMU10: **** Executing 2D Image ****\n");
        strcpy(streaming_msg_arr[181], "PMU10: **** Start DDR4 Training. PMU Firmware Revision 0x%04x ****\n");
        strcpy(streaming_msg_arr[182], "PMU10: **** Start DDR3 Training. PMU Firmware Revision 0x%04x ****\n");
        strcpy(streaming_msg_arr[183], "PMU10: **** Start LPDDR3 Training. PMU Firmware Revision 0x%04x ****\n");
        strcpy(streaming_msg_arr[184], "PMU10: **** Start LPDDR4 Training. PMU Firmware Revision 0x%04x ****\n");
        strcpy(streaming_msg_arr[185], "PMU: Error: Mismatched internal revision between DCCM and ICCM images\n");
        strcpy(streaming_msg_arr[186], "PMU10: **** Testchip %d Specific Firmware ****\n");
        strcpy(streaming_msg_arr[187], "PMU1: LRDIMM with EncodedCS mode, one DIMM\n");
        strcpy(streaming_msg_arr[188], "PMU1: LRDIMM with EncodedCS mode, two DIMMs\n");
        strcpy(streaming_msg_arr[189], "PMU1: RDIMM with EncodedCS mode, one DIMM\n");
        strcpy(streaming_msg_arr[190], "PMU2: Starting LRDIMM MREP training for all ranks\n");
        strcpy(streaming_msg_arr[191], "PMU199: LRDIMM MREP training for all ranks completed\n");
        strcpy(streaming_msg_arr[192], "PMU2: Starting LRDIMM DWL training for all ranks\n");
        strcpy(streaming_msg_arr[193], "PMU199: LRDIMM DWL training for all ranks completed\n");
        strcpy(streaming_msg_arr[194], "PMU2: Starting LRDIMM MRD training for all ranks\n");
        strcpy(streaming_msg_arr[195], "PMU199: LRDIMM MRD training for all ranks completed\n");
        strcpy(streaming_msg_arr[196], "PMU2: Starting RXEN training for all ranks\n");
        strcpy(streaming_msg_arr[197], "PMU2: Starting write leveling fine delay training for all ranks\n");
        strcpy(streaming_msg_arr[198], "PMU2: Starting LRDIMM MWD training for all ranks\n");
        strcpy(streaming_msg_arr[199], "PMU199: LRDIMM MWD training for all ranks completed\n");
        strcpy(streaming_msg_arr[200], "PMU2: Starting write leveling fine delay training for all ranks\n");
        strcpy(streaming_msg_arr[201], "PMU2: Starting read deskew training\n");
        strcpy(streaming_msg_arr[202], "PMU2: Starting SI friendly 1d RdDqs training for all ranks\n");
        strcpy(streaming_msg_arr[203], "PMU2: Starting write leveling coarse delay training for all ranks\n");
        strcpy(streaming_msg_arr[204], "PMU2: Starting 1d WrDq training for all ranks\n");
        strcpy(streaming_msg_arr[205], "PMU2: Running DQS2DQ Oscillator for all ranks\n");
        strcpy(streaming_msg_arr[206], "PMU2: Starting again read deskew training but with PRBS\n");
        strcpy(streaming_msg_arr[207], "PMU2: Starting 1d RdDqs training for all ranks\n");
        strcpy(streaming_msg_arr[208], "PMU2: Starting again 1d WrDq training for all ranks\n");
        strcpy(streaming_msg_arr[209], "PMU2: Starting MaxRdLat training\n");
        strcpy(streaming_msg_arr[210], "PMU2: Starting 2d RdDqs training for all ranks\n");
        strcpy(streaming_msg_arr[211], "PMU2: Starting 2d WrDq training for all ranks\n");
        strcpy(streaming_msg_arr[212], "PMU2: Starting 2d RdDqs training for all ranks\n");
        strcpy(streaming_msg_arr[213], "PMU3:read_fifo %x %x\n");
        strcpy(streaming_msg_arr[214], "PMU: Error: Invalid PhyDrvImpedance of 0x%x specified in message block.\n");
        strcpy(streaming_msg_arr[215], "PMU: Error: Invalid PhyOdtImpedance of 0x%x specified in message block.\n");
        strcpy(streaming_msg_arr[216], "PMU: Error: Invalid BPZNResVal of 0x%x specified in message block.\n");
        strcpy(streaming_msg_arr[217], "PMU3: fixRxEnBackOff csn:%d db:%d dn:%d bo:%d dly:%x\n");
        strcpy(streaming_msg_arr[218], "PMU3: fixRxEnBackOff dly:%x\n");
        strcpy(streaming_msg_arr[219], "PMU3: Entering setupPpt\n");
        strcpy(streaming_msg_arr[220], "PMU3: Start lp4PopulateHighLowBytes\n");
        strcpy(streaming_msg_arr[221], "PMU3:Dbyte Detect: db%d received %x\n");
        strcpy(streaming_msg_arr[222], "PMU3:getDqs2Dq read %x from dbyte %d\n");
        strcpy(streaming_msg_arr[223], "PMU3:getDqs2Dq(2) read %x from dbyte %d\n");
        strcpy(streaming_msg_arr[224], "PMU: Error: Dbyte %d read 0 from the DQS oscillator it is connected to\n");
        strcpy(streaming_msg_arr[225], "PMU4: Dbyte %d dqs2dq = %d/32 UI\n");
        strcpy(streaming_msg_arr[226], "PMU3:getDqs2Dq set dqs2dq:%d/32 ui (%d ps) from dbyte %d\n");
        strcpy(streaming_msg_arr[227], "PMU3: Setting coarse delay in AtxDly chiplet %d from 0x%02x to 0x%02x \n");
        strcpy(streaming_msg_arr[228], "PMU3: Clearing coarse delay in AtxDly chiplet %d from 0x%02x to 0x%02x \n");
        strcpy(streaming_msg_arr[229], "PMU3: Performing DDR4 geardown sync sequence\n");
        strcpy(streaming_msg_arr[230], "PMU1: Enter self refresh\n");
        strcpy(streaming_msg_arr[231], "PMU1: Exit self refresh\n");
        strcpy(streaming_msg_arr[232], "PMU: Error: No dbiEnable with lp4\n");
        strcpy(streaming_msg_arr[233], "PMU: Error: No dbiDisable with lp4\n");
        strcpy(streaming_msg_arr[234], "PMU1: DDR4 update Rx DBI Setting disable %d\n");
        strcpy(streaming_msg_arr[235], "PMU1: DDR4 update 2nCk WPre Setting disable %d\n");
        strcpy(streaming_msg_arr[236], "PMU1: read_delay: db%d lane%d delays[%2d] = 0x%02x (max 0x%02x)\n");
        strcpy(streaming_msg_arr[237], "PMU1: write_delay: db%d lane%d delays[%2d] = 0x%04x\n");
        strcpy(streaming_msg_arr[238], "PMU5: ID=%d -- db0  db1  db2  db3  db4  db5  db6  db7  db8  db9 --\n");
        strcpy(streaming_msg_arr[239], "PMU5: [%d]:0x %4x %4x %4x %4x %4x %4x %4x %4x %4x %4x\n");
        strcpy(streaming_msg_arr[240], "PMU2: dump delays - pstate=%d dimm=%d csn=%d\n");
        strcpy(streaming_msg_arr[241], "PMU3: Printing Mid-Training Delay Information\n");
        strcpy(streaming_msg_arr[242], "PMU5: CS%d <<KEY>> 0 TrainingCntr <<KEY>> coarse(15:10) fine(9:0)\n");
        strcpy(streaming_msg_arr[243], "PMU5: CS%d <<KEY>> 0 RxEnDly, 1 RxClkDly <<KEY>> coarse(10:6) fine(5:0)\n");
        strcpy(streaming_msg_arr[244], "PMU5: CS%d <<KEY>> 0 TxDqsDly, 1 TxDqDly <<KEY>> coarse(9:6) fine(5:0)\n");
        strcpy(streaming_msg_arr[245], "PMU5: CS%d <<KEY>> 0 RxPBDly <<KEY>> 1 Delay Unit ~= 7ps \n");
        strcpy(streaming_msg_arr[246], "PMU5: all CS <<KEY>> 0 DFIMRL <<KEY>> Units = DFI clocks\n");
        strcpy(streaming_msg_arr[247], "PMU5: all CS <<KEY>> VrefDACs <<KEY>> DAC(6:0)\n");
        strcpy(streaming_msg_arr[248], "PMU1: Set DMD in MR13 and wrDBI in MR3 for training\n");
        strcpy(streaming_msg_arr[249], "PMU: Error: getMaxRxen() failed to find largest rxen nibble delay\n");
        strcpy(streaming_msg_arr[250], "PMU2: getMaxRxen(): maxDly %d maxTg %d maxNib %d\n");
        strcpy(streaming_msg_arr[251], "PMU2: getRankMaxRxen(): maxDly %d Tg %d maxNib %d\n");
        strcpy(streaming_msg_arr[252], "PMU1: skipping CDD calculation in 2D image\n");
        strcpy(streaming_msg_arr[253], "PMU3: Calculating CDDs for pstate %d\n");
        strcpy(streaming_msg_arr[254], "PMU3: rxFromDly[%d][%d] = %d\n");
        strcpy(streaming_msg_arr[255], "PMU3: rxToDly  [%d][%d] = %d\n");
        strcpy(streaming_msg_arr[256], "PMU3: rxDly    [%d][%d] = %d\n");
        strcpy(streaming_msg_arr[257], "PMU3: txDly    [%d][%d] = %d\n");
        strcpy(streaming_msg_arr[258], "PMU3: allFine CDD_RR_%d_%d = %d\n");
        strcpy(streaming_msg_arr[259], "PMU3: allFine CDD_WW_%d_%d = %d\n");
        strcpy(streaming_msg_arr[260], "PMU3: CDD_RR_%d_%d = %d\n");
        strcpy(streaming_msg_arr[261], "PMU3: CDD_WW_%d_%d = %d\n");
        strcpy(streaming_msg_arr[262], "PMU3: allFine CDD_RW_%d_%d = %d\n");
        strcpy(streaming_msg_arr[263], "PMU3: allFine CDD_WR_%d_%d = %d\n");
        strcpy(streaming_msg_arr[264], "PMU3: CDD_RW_%d_%d = %d\n");
        strcpy(streaming_msg_arr[265], "PMU3: CDD_WR_%d_%d = %d\n");
        strcpy(streaming_msg_arr[266], "PMU3: F%dBC2x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[267], "PMU3: F%dBC3x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[268], "PMU3: F%dBC4x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[269], "PMU3: F%dBC5x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[270], "PMU3: F%dBC8x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[271], "PMU3: F%dBC9x_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[272], "PMU3: F%dBCAx_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[273], "PMU3: F%dBCBx_B%d_D%d = 0x%02x\n");
        strcpy(streaming_msg_arr[274], "PMU10: Entering context_switch_postamble\n");
        strcpy(streaming_msg_arr[275], "PMU10: context_switch_postamble is enabled for DIMM %d, RC0A=0x%x, RC3x=0x%x\n");
        strcpy(streaming_msg_arr[276], "PMU10: Setting bcw fspace 0\n");
        strcpy(streaming_msg_arr[277], "PMU10: Sending BC0A = 0x%x\n");
        strcpy(streaming_msg_arr[278], "PMU10: Sending BC6x = 0x%x\n");
        strcpy(streaming_msg_arr[279], "PMU10: Sending RC0A = 0x%x\n");
        strcpy(streaming_msg_arr[280], "PMU10: Sending RC3x = 0x%x\n");
        strcpy(streaming_msg_arr[281], "PMU10: Sending RC0A = 0x%x\n");
        strcpy(streaming_msg_arr[282], "PMU1: enter_lp3: DEBUG: pstate = %d\n");
        strcpy(streaming_msg_arr[283], "PMU1: enter_lp3: DEBUG: dfifreqxlat_pstate = %d\n");
        strcpy(streaming_msg_arr[284], "PMU1: enter_lp3: DEBUG: pllbypass = %d\n");
        strcpy(streaming_msg_arr[285], "PMU1: enter_lp3: DEBUG: forcecal = %d\n");
        strcpy(streaming_msg_arr[286], "PMU1: enter_lp3: DEBUG: pllmaxrange = 0x%x\n");
        strcpy(streaming_msg_arr[287], "PMU1: enter_lp3: DEBUG: dacval_out = 0x%x\n");
        strcpy(streaming_msg_arr[288], "PMU1: enter_lp3: DEBUG: pllctrl3 = 0x%x\n");
        strcpy(streaming_msg_arr[289], "PMU3: Loading DRAM with BIOS supplied MR values and entering self refresh prior to exiting PMU code.\n");
        strcpy(streaming_msg_arr[290], "PMU3: Setting DataBuffer function space of dimmcs 0x%02x to %d\n");
        strcpy(streaming_msg_arr[291], "PMU4: Setting RCW FxRC%Xx = 0x%02x\n");
        strcpy(streaming_msg_arr[292], "PMU4: Setting RCW FxRC%02X = 0x%02x\n");
        strcpy(streaming_msg_arr[293], "PMU1: DDR4 update Rd Pre Setting disable %d\n");
        strcpy(streaming_msg_arr[294], "PMU2: Setting BCW FxBC%Xx = 0x%02x\n");
        strcpy(streaming_msg_arr[295], "PMU2: Setting BCW BC%02X = 0x%02x\n");
        strcpy(streaming_msg_arr[296], "PMU2: Setting BCW PBA mode FxBC%Xx = 0x%02x\n");
        strcpy(streaming_msg_arr[297], "PMU2: Setting BCW PBA mode BC%02X = 0x%02x\n");
        strcpy(streaming_msg_arr[298], "PMU4: BCW value for dimm %d, fspace %d, addr 0x%04x\n");
        strcpy(streaming_msg_arr[299], "PMU4: DB %d, value 0x%02x\n");
        strcpy(streaming_msg_arr[300], "PMU6: WARNING MREP underflow, set to min value -2 coarse, 0 fine\n");
        strcpy(streaming_msg_arr[301], "PMU6: LRDIMM Writing final data buffer fine delay value nib %2d, trainDly %3d, fineDly code %2d, new MREP fine %2d\n");
        strcpy(streaming_msg_arr[302], "PMU6: LRDIMM Writing final data buffer fine delay value nib %2d, trainDly %3d, fineDly code %2d\n");
        strcpy(streaming_msg_arr[303], "PMU6: LRDIMM Writing data buffer fine delay type %d nib %2d, code %2d\n");
        strcpy(streaming_msg_arr[304], "PMU6: Writing final data buffer coarse delay value dbyte %2d, coarse = 0x%02x\n");
        strcpy(streaming_msg_arr[305], "PMU4: data 0x%04x at MB addr 0x%08x saved at CSR addr 0x%08x\n");
        strcpy(streaming_msg_arr[306], "PMU4: data 0x%04x at MB addr 0x%08x restored from CSR addr 0x%08x\n");
        strcpy(streaming_msg_arr[307], "PMU4: data 0x%04x at MB addr 0x%08x saved at CSR addr 0x%08x\n");
        strcpy(streaming_msg_arr[308], "PMU4: data 0x%04x at MB addr 0x%08x restored from CSR addr 0x%08x\n");
        strcpy(streaming_msg_arr[309], "PMU3: Update BC00, BC01, BC02 for rank-dimm 0x%02x\n");
        strcpy(streaming_msg_arr[310], "PMU3: Writing D4 RDIMM RCD Control words F0RC00 -> F0RC0F\n");
        strcpy(streaming_msg_arr[311], "PMU3: Disable parity in F0RC0E\n");
        strcpy(streaming_msg_arr[312], "PMU3: Writing D4 RDIMM RCD Control words F1RC00 -> F1RC05\n");
        strcpy(streaming_msg_arr[313], "PMU3: Writing D4 RDIMM RCD Control words F1RC1x -> F1RC9x\n");
        strcpy(streaming_msg_arr[314], "PMU3: Writing D4 Data buffer Control words BC00 -> BC0E\n");
        strcpy(streaming_msg_arr[315], "PMU1: setAltCL Sending MR0 0x%x cl=%d\n");
        strcpy(streaming_msg_arr[316], "PMU1: restoreFromAltCL Sending MR0 0x%x cl=%d\n");
        strcpy(streaming_msg_arr[317], "PMU1: restoreAcsmFromAltCL Sending MR0 0x%x cl=%d\n");
        strcpy(streaming_msg_arr[318], "PMU2: Setting D3R RC%d = 0x%01x\n");
        strcpy(streaming_msg_arr[319], "PMU3: Writing D3 RDIMM RCD Control words RC0 -> RC11\n");
        strcpy(streaming_msg_arr[320], "PMU0: VrefDAC0/1 vddqStart %d dacToVddq %d\n");
        strcpy(streaming_msg_arr[321], "PMU: Error: Messageblock phyVref=0x%x is above the limit for TSMC28's attenuated LPDDR4 receivers. Please see the pub databook\n");
        strcpy(streaming_msg_arr[322], "PMU: Error: Messageblock phyVref=0x%x is above the limit for TSMC28's attenuated DDR4 receivers. Please see the pub databook\n");
        strcpy(streaming_msg_arr[323], "PMU0: PHY VREF @ (%d/1000) VDDQ\n");
        strcpy(streaming_msg_arr[324], "PMU0: initalizing phy vrefDacs to %d ExtVrefRange %x\n");
        strcpy(streaming_msg_arr[325], "PMU0: initalizing global vref to %d range %d\n");
        strcpy(streaming_msg_arr[326], "PMU4: Setting initial device vrefDQ for CS%d to MR6 = 0x%04x\n");
        strcpy(streaming_msg_arr[327], "PMU1: In write_level_fine() csn=%d dimm=%d pstate=%d\n");
        strcpy(streaming_msg_arr[328], "PMU3: Fine write leveling hardware search increasing TxDqsDly until full bursts are seen\n");
        strcpy(streaming_msg_arr[329], "PMU4: WL normalized pos   : ........................|........................\n");
        strcpy(streaming_msg_arr[330], "PMU4: WL margin for nib %2d: %08x%08x%08x%08x%08x%08x\n");
        strcpy(streaming_msg_arr[331], "PMU4: WL normalized pos   : ........................|........................\n");
        strcpy(streaming_msg_arr[332], "PMU3: Exiting write leveling mode\n");
        strcpy(streaming_msg_arr[333], "PMU3: got %d for cl in load_wrlvl_acsm\n");
        strcpy(streaming_msg_arr[334], "PMU1: In write_level_coarse() csn=%d dimm=%d pstate=%d\n");
        strcpy(streaming_msg_arr[335], "PMU3: left eye edge search db:%d ln:%d dly:0x%x\n");
        strcpy(streaming_msg_arr[336], "PMU3: right eye edge search db:%d ln:%d dly:0x%x\n");
        strcpy(streaming_msg_arr[337], "PMU3: eye center db:%d ln:%d dly:0x%x (maxdq:%x)\n");
        strcpy(streaming_msg_arr[338], "PMU3: Wrote to TxDqDly db:%d ln:%d dly:0x%x\n");
        strcpy(streaming_msg_arr[339], "PMU3: Wrote to TxDqDly db:%d ln:%d dly:0x%x\n");
        strcpy(streaming_msg_arr[340], "PMU3: Coarse write leveling dbyte%2d is still failing for TxDqsDly=0x%04x\n");
        strcpy(streaming_msg_arr[341], "PMU4: Coarse write leveling iteration %d saw %d data miscompares across the entire phy\n");
        strcpy(streaming_msg_arr[342], "PMU: Error: Failed write leveling coarse\n");
        strcpy(streaming_msg_arr[343], "PMU3: got %d for cl in load_wrlvl_acsm\n");
        strcpy(streaming_msg_arr[344], "PMU3: In write_level_coarse() csn=%d dimm=%d pstate=%d\n");
        strcpy(streaming_msg_arr[345], "PMU3: left eye edge search db:%d ln:%d dly:0x%x\n");
        strcpy(streaming_msg_arr[346], "PMU3: right eye edge search db: %d ln: %d dly: 0x%x\n");
        strcpy(streaming_msg_arr[347], "PMU3: eye center db: %d ln: %d dly: 0x%x (maxdq: 0x%x)\n");
        strcpy(streaming_msg_arr[348], "PMU3: Wrote to TxDqDly db: %d ln: %d dly: 0x%x\n");
        strcpy(streaming_msg_arr[349], "PMU3: Wrote to TxDqDly db: %d ln: %d dly: 0x%x\n");
        strcpy(streaming_msg_arr[350], "PMU3: Coarse write leveling nibble%2d is still failing for TxDqsDly=0x%04x\n");
        strcpy(streaming_msg_arr[351], "PMU4: Coarse write leveling iteration %d saw %d data miscompares across the entire phy\n");
        strcpy(streaming_msg_arr[352], "PMU: Error: Failed write leveling coarse\n");
        strcpy(streaming_msg_arr[353], "PMU4: WL normalized pos   : ................................|................................\n");
        strcpy(streaming_msg_arr[354], "PMU4: WL margin for nib %2d: %08x%08x%08x%08x%08x%08x%08x%08x\n");
        strcpy(streaming_msg_arr[355], "PMU4: WL normalized pos   : ................................|................................\n");
        strcpy(streaming_msg_arr[356], "PMU8: Adjust margin after WL coarse to be larger than %d\n");
        strcpy(streaming_msg_arr[357], "PMU: Error: All margin after write leveling coarse are smaller than minMargin %d\n");
        strcpy(streaming_msg_arr[358], "PMU8: Decrement nib %d TxDqsDly by %d fine step\n");
        strcpy(streaming_msg_arr[359], "PMU3: In write_level_coarse() csn=%d dimm=%d pstate=%d\n");
        strcpy(streaming_msg_arr[360], "PMU2: Write level: dbyte %d nib%d dq/dmbi %2d dqsfine 0x%04x dqDly 0x%04x\n");
        strcpy(streaming_msg_arr[361], "PMU3: Coarse write leveling nibble%2d is still failing for TxDqsDly=0x%04x\n");
        strcpy(streaming_msg_arr[362], "PMU4: Coarse write leveling iteration %d saw %d data miscompares across the entire phy\n");
        strcpy(streaming_msg_arr[363], "PMU: Error: Failed write leveling coarse\n");
        strcpy(streaming_msg_arr[364], "PMU3: DWL delay = %d\n");
        strcpy(streaming_msg_arr[365], "PMU3: Errcnt for DWL nib %2d delay = %2d is %d\n");
        strcpy(streaming_msg_arr[366], "PMU3: DWL nibble %d sampled a 1 at delay %d\n");
        strcpy(streaming_msg_arr[367], "PMU3: DWL nibble %d passed at delay %d. Rising edge was at %d\n");
        strcpy(streaming_msg_arr[368], "PMU2: DWL did nto find a rising edge of memclk for all nibbles. Failing nibbles assumed to have rising edge close to fine delay 63\n");
        strcpy(streaming_msg_arr[369], "PMU2:  Rising edge found in alias window, setting wrlvlDly for nibble %d = %d\n");
        strcpy(streaming_msg_arr[370], "PMU: Error: Failed DWL for nib %d with %d one\n");
        strcpy(streaming_msg_arr[371], "PMU2:  Rising edge not found in alias window with %d one, leaving wrlvlDly for nibble %d = %d\n");
        strcpy(streaming_msg_arr[372], "PMU: Error:Mailbox Buffer Overflowed.\n");
        strcpy(streaming_msg_arr[373], "PMU: Error:Mailbox Buffer Overflowed.\n");
        strcpy(streaming_msg_arr[374], "PMU: ***** Assertion Error - terminating *****\n");
        strcpy(streaming_msg_arr[375], "PMU1: swapByte db %d by %d\n");
        strcpy(streaming_msg_arr[376], "PMU3: get_cmd_dly max(%d ps, %d memclk) = %d\n");
        strcpy(streaming_msg_arr[377], "PMU0: Write CSR 0x%06x 0x%04x\n");
        strcpy(streaming_msg_arr[378], "PMU0: hwt_init_ppgc_prbs(): Polynomial: %x, Deg: %d\n");
        strcpy(streaming_msg_arr[379], "PMU: Error: acsm_set_cmd to non existant instruction adddress %d\n");
        strcpy(streaming_msg_arr[380], "PMU: Error: acsm_set_cmd with unknown ddr cmd 0x%x\n");
        strcpy(streaming_msg_arr[381], "PMU1: acsm_addr %02x, acsm_flgs %04x, ddr_cmd %02x, cmd_dly %02x, ddr_addr %04x, ddr_bnk %02x, ddr_cs %02x, cmd_rcnt %02x, AcsmSeq0/1/2/3 %04x %04x %04x %04x\n");
        strcpy(streaming_msg_arr[382], "PMU: Error: Polling on ACSM done failed to complete in acsm_poll_done()...\n");
        strcpy(streaming_msg_arr[383], "PMU1: acsm RUN\n");
        strcpy(streaming_msg_arr[384], "PMU1: acsm STOPPED\n");
        strcpy(streaming_msg_arr[385], "PMU1: acsm_init: acsm_mode %04x mxrdlat %04x\n");
        strcpy(streaming_msg_arr[386], "PMU: Error: setAcsmCLCWL: cl and cwl must be each >= 2 and 5, resp. CL=%d CWL=%d\n");
        strcpy(streaming_msg_arr[387], "PMU: Error: setAcsmCLCWL: cl and cwl must be each >= 5. CL=%d CWL=%d\n");
        strcpy(streaming_msg_arr[388], "PMU1: setAcsmCLCWL: CASL %04d WCASL %04d\n");
        strcpy(streaming_msg_arr[389], "PMU: Error: Reserved value of register F0RC0F found in message block: 0x%04x\n");
        strcpy(streaming_msg_arr[390], "PMU3: Written MRS to CS=0x%02x\n");
        strcpy(streaming_msg_arr[391], "PMU3: Written MRS to CS=0x%02x\n");
        strcpy(streaming_msg_arr[392], "PMU3: Entering Boot Freq Mode.\n");
        strcpy(streaming_msg_arr[393], "PMU: Error: Boot clock divider setting of %d is too small\n");
        strcpy(streaming_msg_arr[394], "PMU3: Exiting Boot Freq Mode.\n");
        strcpy(streaming_msg_arr[395], "PMU3: Writing MR%d OP=%x\n");
        strcpy(streaming_msg_arr[396], "PMU: Error: Delay too large in slomo\n");
        strcpy(streaming_msg_arr[397], "PMU3: Written MRS to CS=0x%02x\n");
        strcpy(streaming_msg_arr[398], "PMU3: Enable Channel A\n");
        strcpy(streaming_msg_arr[399], "PMU3: Enable Channel B\n");
        strcpy(streaming_msg_arr[400], "PMU3: Enable All Channels\n");
        strcpy(streaming_msg_arr[401], "PMU2: Use PDA mode to set MR%d with value 0x%02x\n");
        strcpy(streaming_msg_arr[402], "PMU3: Written Vref with PDA to CS=0x%02x\n");
        strcpy(streaming_msg_arr[403], "PMU1: start_cal: DEBUG: setting CalRun to 1\n");
        strcpy(streaming_msg_arr[404], "PMU1: start_cal: DEBUG: setting CalRun to 0\n");
        strcpy(streaming_msg_arr[405], "PMU1: lock_pll_dll: DEBUG: pstate = %d\n");
        strcpy(streaming_msg_arr[406], "PMU1: lock_pll_dll: DEBUG: dfifreqxlat_pstate = %d\n");
        strcpy(streaming_msg_arr[407], "PMU1: lock_pll_dll: DEBUG: pllbypass = %d\n");
        strcpy(streaming_msg_arr[408], "PMU3: SaveLcdlSeed: Saving seed seed %d\n");
        strcpy(streaming_msg_arr[409], "PMU1: in phy_defaults()\n");
        strcpy(streaming_msg_arr[410], "PMU3: ACXConf:%d MaxNumDbytes:%d NumDfi:%d\n");
        strcpy(streaming_msg_arr[411], "PMU1: setAltAcsmCLCWL setting cl=%d cwl=%d\n");
}
#endif
void dwc_ddrphy_apb_wr(unsigned long reg, u32 val)
{
//	printf("dwc_ddrphy_apb_wr(32'h%x,16'h%x);\n",reg,val);
	writel(val, (SIFLOWER_DDR_PHY_BASE + 4*reg));
}

int dwc_ddrphy_apb_rd(unsigned long reg)
{
	return readl(SIFLOWER_DDR_PHY_BASE + 4*reg);
}

// === Global Struct Defines === //
/// instance of runtime objects
//runtime_config_t             runtimeConfig;
/// instance of useInputBasic
user_input_basic_t           userInputBasic;
/// instance of userInputAdvanced
user_input_advanced_t        userInputAdvanced;
/// instance of userInputSim
user_input_sim_t             userInputSim;

// === Firmware Message Block Structs === //
/// 1D message block instance
PMU_SMB_DDR3U_1D_t        mb_DDR3U_1D[1];
/// Shadow of 1D message block. Used by PhyInit to track user changes to the
/// data structure.

u8 ODIC = 0;
u8 read_dbi_en=0;
u8 write_dbi_en=0;
u8 data_mask=0;
//char rtt_wr=4;
//char rtt_nom=1;
//char rtt_park=1;
//char vrefdq=70;
u32 ddr_freq=1066;


int dwc_ddrphy_phyinit_setDefault(int Train2D)
{
        userInputBasic.DramType                 = DDR3;
        userInputBasic.DimmType                 = NODIMM; //->NODIMM
        userInputBasic.HardMacroVer             = 0; //default: HardMacro family D  *find


        userInputBasic.NumDbyte                 = 0x0002;//	->2
        userInputBasic.NumActiveDbyteDfi0       = 0x0002;//   ->2
        userInputBasic.NumActiveDbyteDfi1       = 0x0000;//   ->0
        userInputBasic.NumAnib                  = 0x000a;
        userInputBasic.NumRank_dfi0             = 0x0001; // 1 rank
        userInputBasic.NumPStates               = 0x0001; // 1 Pstate
        userInputBasic.Frequency[3]             = 800;
        userInputBasic.Frequency[2]             = 933;
        userInputBasic.Frequency[1]             = 1067;
        userInputBasic.Frequency[0]             = 800; // 3200Mbps
        userInputBasic.PllBypass[0]             = 0x0000;
        userInputBasic.PllBypass[1]             = 0x0000;
        userInputBasic.PllBypass[2]             = 0x0000;
        userInputBasic.PllBypass[3]             = 0x0000;
        userInputBasic.DfiFreqRatio[0]          = 0x0001;
        userInputBasic.DfiFreqRatio[1]          = 0x0001;
        userInputBasic.DfiFreqRatio[2]          = 0x0001;
        userInputBasic.DfiFreqRatio[3]          = 0x0001;
        userInputBasic.Dfi1Exists               = 0x0000;
        userInputBasic.DramDataWidth            = 0x0010; //x16

    // ##############################################################
    // userInputAdvnaced (Optional)
    // Default values will be used if no input provided
    // ##############################################################

        userInputAdvanced.DramByteSwap             = 0x0000;   //to ensure
        userInputAdvanced.ExtCalResVal             = 0x0001;    //search doc to ensure
        userInputAdvanced.TxSlewRiseDQ[0]          = 0x000f;
        userInputAdvanced.TxSlewRiseDQ[1]          = 0x000f;
        userInputAdvanced.TxSlewRiseDQ[2]          = 0x000f;
        userInputAdvanced.TxSlewRiseDQ[3]          = 0x000f;
        userInputAdvanced.TxSlewFallDQ[0]          = 0x000f;
        userInputAdvanced.TxSlewFallDQ[1]          = 0x000f;
        userInputAdvanced.TxSlewFallDQ[2]          = 0x000f;
        userInputAdvanced.TxSlewFallDQ[3]          = 0x000f;
        userInputAdvanced.TxSlewRiseAC             = 0x0004;
        userInputAdvanced.TxSlewFallAC             = 0x0004;
        userInputAdvanced.ODTImpedance[0]          = 60;      //input**
        userInputAdvanced.ODTImpedance[1]          = 60;
        userInputAdvanced.ODTImpedance[2]          = 60;
        userInputAdvanced.ODTImpedance[3]          = 60;
        userInputAdvanced.TxImpedance[0]           = 40;
        userInputAdvanced.TxImpedance[1]           = 60;
        userInputAdvanced.TxImpedance[2]           = 60;
        userInputAdvanced.TxImpedance[3]           = 60;
        userInputAdvanced.ATxImpedance             = 40;      //with HardMacro family E, ATxImpedance will default to 40 Ohm instead
        userInputAdvanced.MemAlertEn               = 0x0000;
        userInputAdvanced.MemAlertPUImp            = 0x0005;
        userInputAdvanced.MemAlertVrefLevel        = 0x0029;
        userInputAdvanced.MemAlertSyncBypass       = 0x0000;
        userInputAdvanced.CalInterval              = 0x0009;
        userInputAdvanced.CalOnce                  = 0x0000;

        userInputAdvanced.DisDynAdrTri[0]          = 0x0000;
        userInputAdvanced.DisDynAdrTri[1]          = 0x0000;
        userInputAdvanced.DisDynAdrTri[2]          = 0x0000;
        userInputAdvanced.DisDynAdrTri[3]          = 0x0000;
        userInputAdvanced.Is2Ttiming[0]            = 0x0000;
        userInputAdvanced.Is2Ttiming[1]            = 0x0000;
        userInputAdvanced.Is2Ttiming[2]            = 0x0000;
        userInputAdvanced.Is2Ttiming[3]            = 0x0000;


    // ##############################################################
    // Basic Message Block Variables
    // ##############################################################

        uint8_t myps;

    // ##############################################################
    // These are typically invariant across Pstate
    // ##############################################################
        uint8_t MsgMisc              = 0x00;
        uint8_t Reserved00           = 0x0;  // Set Reserved00[7]   = 1 (If using T28 attenuated receivers)
                                         // Set Reserved00[6:0] = 0 (Reserved; must be programmed to 0)

        uint8_t HdtCtrl              = 0xc8;//0x04; //input
        uint8_t CsPresent            = 0x01; // Indicates presence of DRAM at each chip select for PHY.
                                         //
                                         // If the bit is set to 1, the CS is connected to DRAM.
                                         // If the bit is set to 0, the CS is not connected to DRAM.
                                         //
                                         // Set CsPresent[0]   = 1 (if CS0 is populated with DRAM)
                                         // Set CsPresent[1]   = 1 (if CS1 is populated with DRAM)
                                         // Set CsPresent[2]   = 1 (if CS2 is populated with DRAM)
                                         // Set CsPresent[3]   = 1 (if CS3 is populated with DRAM)
                                         // Set CsPresent[7:4] = 0 (Reserved; must be programmed to 0)

        uint8_t PhyVref              = 0x56; //input //Use Analytical VREF and Compensate for T28 Attenuator, see PHY databook
        uint8_t DFIMRLMargin         = 0x01; //1 is typically good in DDR3
        uint8_t AddrMirror           = 0x00; // Set AddrMirror[pstate] if CS[pstate] is mirrored. (typically odd CS are mirroed in DIMMs)
        uint8_t WRODTPAT_RANK0       = 0x01; //When Writing Rank0 : Bits[3:0] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t WRODTPAT_RANK1       = 0x02; //When Writing Rank1 : Bits[3:0] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t WRODTPAT_RANK2       = 0x04; //When Writing Rank2 : Bits[3:0] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t WRODTPAT_RANK3       = 0x08; //When Writing Rank3 : Bits[3:0] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t RDODTPAT_RANK0       = 0x20; //When Reading Rank0 : Bits[7:4] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t RDODTPAT_RANK1       = 0x10; //When Reading Rank1 : Bits[7:4] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t RDODTPAT_RANK2       = 0x80; //When Reading Rank2 : Bits[7:4] should be set to the desired setting of ODT[3:0] to the DRAM
        uint8_t RDODTPAT_RANK3       = 0x40; //When Reading Rank3 : Bits[7:4] should be set to the desired setting of ODT[3:0] to the DRAM
        uint16_t SequenceCtrl[4];
	//input
        SequenceCtrl[0] = 0x031f;
        SequenceCtrl[1] = 0x031f;
        SequenceCtrl[2] = 0x031f;
        SequenceCtrl[3] = 0x031f;

        uint16_t mr0[4];
        uint16_t mr1[4];
        uint16_t mr2[4];
/*    uint16_t mr3[4];
    uint16_t mr4[4];
    uint16_t mr5[4];
    uint16_t mr6[4];

    uint16_t ALT_CAS_L[4];  //Need to set if using RDDBI
    uint16_t ALT_WCAS_L[4]; //Need to set if using 2tck Write Preambles
 */
        mr0[0] = 0x1e14;
        mr1[0] = 0x0004;
        mr2[0] = 0x0020;
  /* mr3[0] = 0x0400;
    mr4[0] = 0x0000;
    mr5[0] = 0x0480;
    mr6[0] = 0x0800 | 0x0018; // Example Vref : 0x18=907mV = 0.75*VDDQ

    //check when DBI used
    ALT_CAS_L[0]  = 0x0000;
    ALT_WCAS_L[0] = 0x0000;
 */

    // ##############################################################
    // These are per-pstate Control Words for RCD
    // Please enter the correct values for your configuration
    // ##############################################################




    // ##############################################################
    // 95% of users will not need to edit below
    // ##############################################################

    // Per Rank MR seeting for RTT_NOM, RTT_WR, RTT_PARK per rank. Options unlikely need to be used.
    // See MB details on how to program if required.
/*    uint16_t RTT_NOM_WR_PARK0[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK1[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK2[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK3[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK4[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK5[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK6[4]  = {0x0,0x0,0x0,0x0};
    uint16_t RTT_NOM_WR_PARK7[4]  = {0x0,0x0,0x0,0x0};
*/

    // 1D message block defaults
        for (myps=0; myps<1; myps++) {
                mb_DDR3U_1D[myps].Pstate               = myps;
                mb_DDR3U_1D[myps].DramType               = 1;
                //input
                mb_DDR3U_1D[myps].SequenceCtrl         = SequenceCtrl[myps];
                mb_DDR3U_1D[myps].PhyConfigOverride    = 0x0;
                //input
                mb_DDR3U_1D[myps].HdtCtrl              = HdtCtrl;
                mb_DDR3U_1D[myps].MsgMisc              = MsgMisc;
                mb_DDR3U_1D[myps].Reserved00           = Reserved00;
                mb_DDR3U_1D[myps].DFIMRLMargin         = DFIMRLMargin;
                mb_DDR3U_1D[myps].PhyVref              = PhyVref;

                mb_DDR3U_1D[myps].CsPresent            = CsPresent;
                mb_DDR3U_1D[myps].CsPresentD0          = CsPresent;
                mb_DDR3U_1D[myps].CsPresentD1          = 0x0000; //Unused in UDIMM or DRAM-ON-PCB
                mb_DDR3U_1D[myps].AddrMirror           = AddrMirror;
                mb_DDR3U_1D[myps].AcsmOdtCtrl0         = WRODTPAT_RANK0 | RDODTPAT_RANK0;
                mb_DDR3U_1D[myps].AcsmOdtCtrl1         = WRODTPAT_RANK1 | RDODTPAT_RANK1;
                mb_DDR3U_1D[myps].AcsmOdtCtrl2         = WRODTPAT_RANK2 | RDODTPAT_RANK2;
                mb_DDR3U_1D[myps].AcsmOdtCtrl3         = WRODTPAT_RANK3 | RDODTPAT_RANK3;

                mb_DDR3U_1D[myps].AcsmOdtCtrl4         = 0x0000; //Unused in UDIMM or DRAM-ON-PCB
                mb_DDR3U_1D[myps].AcsmOdtCtrl5         = 0x0000; //Unused in UDIMM or DRAM-ON-PCB
                mb_DDR3U_1D[myps].AcsmOdtCtrl6         = 0x0000; //Unused in UDIMM or DRAM-ON-PCB
                mb_DDR3U_1D[myps].AcsmOdtCtrl7         = 0x0000; //Unused in UDIMM or DRAM-ON-PCB
                mb_DDR3U_1D[myps].EnabledDQs           = (userInputBasic.NumActiveDbyteDfi0+userInputBasic.NumActiveDbyteDfi1)*8;
                mb_DDR3U_1D[myps].PhyCfg               = userInputAdvanced.Is2Ttiming[myps];
                //    mb_DDR3U_1D[myps].PhyCfg               = (mr3[myps]&0x8) ? 0 : userInputAdvanced.Is2Ttiming[myps];
                mb_DDR3U_1D[myps].MR0                  = mr0[myps];
                mb_DDR3U_1D[myps].MR1                  = mr1[myps];
                mb_DDR3U_1D[myps].MR2                  = mr2[myps];
        } // myps

   // ##############################################################
    // userInputSim - Dram/Dimm Timing Parameters the user must p
    // provide value if applicable
    // ##############################################################
        userInputSim.tDQS2DQ                    = 0;
        userInputSim.tDQSCK                     = 0;
        userInputSim.tSTAOFF[0]                 = 0;
        userInputSim.tSTAOFF[1]                 = 0;
        userInputSim.tSTAOFF[2]                 = 0;
        userInputSim.tSTAOFF[3]                 = 0;
        userInputSim.tPDM[0]                    = 0;
        userInputSim.tPDM[1]                    = 0;
        userInputSim.tPDM[2]                    = 0;
        userInputSim.tPDM[3]                    = 0;

        return 0;
}

int dwc_ddrphy_phyinit_userCustom_overrideUserInput(void)
{
	return 0;
}

int dwc_ddrphy_phyinit_userCustom_A_bringupPower(void)
{
	return 0;
}

int dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy(void)
{
	return 0;
}

int dwc_ddrphy_phyinit_mapDrvStren (int DrvStren_ohm, enum DrvType TargetCSR, int HardMacroVer) {

        int Stren_setting = 0;

        if ( ( TargetCSR == DrvStrenFSDqP  ) || ( TargetCSR == DrvStrenFSDqN  ) ) {

                //......................................................................................
                // DrvStrenFSDqP or DrvStrenFSDqP
                //......................................................................................

                if      (DrvStren_ohm == 0 ) Stren_setting = 0x00; // High-impedance
                else if (DrvStren_ohm < 29 ) Stren_setting = 0x3f;
                else if (DrvStren_ohm < 31 ) Stren_setting = 0x3e;
                else if (DrvStren_ohm < 33 ) Stren_setting = 0x3b;
                else if (DrvStren_ohm < 35 ) Stren_setting = 0x3a;
                else if (DrvStren_ohm < 38 ) Stren_setting = 0x39;
                else if (DrvStren_ohm < 41 ) Stren_setting = 0x38;
                else if (DrvStren_ohm < 45 ) Stren_setting = 0x1b;
                else if (DrvStren_ohm < 50 ) Stren_setting = 0x1a;
                else if (DrvStren_ohm < 56 ) Stren_setting = 0x19;
                else if (DrvStren_ohm < 64 ) Stren_setting = 0x18;
                else if (DrvStren_ohm < 74 ) Stren_setting = 0x0b;
                else if (DrvStren_ohm < 88 ) Stren_setting = 0x0a;
                else if (DrvStren_ohm < 108) Stren_setting = 0x09;
                else if (DrvStren_ohm < 140) Stren_setting = 0x08;
                else if (DrvStren_ohm < 200) Stren_setting = 0x03;
                else if (DrvStren_ohm < 360) Stren_setting = 0x02;
                else if (DrvStren_ohm < 481) Stren_setting = 0x01;
                else                         Stren_setting = 0x00; // High-impedance
        } else if ( TargetCSR == ODTStrenP ) {
                //......................................................................................
                // ODTStrenP
                //......................................................................................

                // DDR3 - P and N has the same impedance and non-zero
                // user input is half the individual pull-up and pull-down impedances values because of parallel between them

                if      (DrvStren_ohm == 0 )  Stren_setting = 0x00; // High-impedance
                else if (DrvStren_ohm < 15 )  Stren_setting = 0x3f;
                else if (DrvStren_ohm < 16 )  Stren_setting = 0x3e;
                else if (DrvStren_ohm < 17 )  Stren_setting = 0x3b;
                else if (DrvStren_ohm < 18 )  Stren_setting = 0x3a;
                else if (DrvStren_ohm < 20 )  Stren_setting = 0x39;
                else if (DrvStren_ohm < 21 )  Stren_setting = 0x38;
                else if (DrvStren_ohm < 23 )  Stren_setting = 0x1b;
                else if (DrvStren_ohm < 26 )  Stren_setting = 0x1a;
                else if (DrvStren_ohm < 29 )  Stren_setting = 0x19;
                else if (DrvStren_ohm < 33 )  Stren_setting = 0x18;
                else if (DrvStren_ohm < 38 )  Stren_setting = 0x0b;
                else if (DrvStren_ohm < 45 )  Stren_setting = 0x0a;
                else if (DrvStren_ohm < 55 )  Stren_setting = 0x09;
                else if (DrvStren_ohm < 71 )  Stren_setting = 0x08;
                else if (DrvStren_ohm < 101 ) Stren_setting = 0x03;
                else if (DrvStren_ohm < 181 ) Stren_setting = 0x02;
                else if (DrvStren_ohm < 241 ) Stren_setting = 0x01;
                else                          Stren_setting = 0x00; // High-impedance
        } else if ( TargetCSR == ODTStrenN ) {
                //......................................................................................
                // ODTStrenN
                //......................................................................................

                // DDR3 - P and N has the same impedance and non-zero
                // Times 2 of user input because of parallel pull-up and pull-down termination

                if      (DrvStren_ohm == 0 )  Stren_setting = 0x00; // High-impedance
                else if (DrvStren_ohm < 15 )  Stren_setting = 0x3f;
                else if (DrvStren_ohm < 16 )  Stren_setting = 0x3e;
                else if (DrvStren_ohm < 17 )  Stren_setting = 0x3b;
                else if (DrvStren_ohm < 18 )  Stren_setting = 0x3a;
                else if (DrvStren_ohm < 20 )  Stren_setting = 0x39;
                else if (DrvStren_ohm < 21 )  Stren_setting = 0x38;
                else if (DrvStren_ohm < 23 )  Stren_setting = 0x1b;
                else if (DrvStren_ohm < 26 )  Stren_setting = 0x1a;
                else if (DrvStren_ohm < 29 )  Stren_setting = 0x19;
                else if (DrvStren_ohm < 33 )  Stren_setting = 0x18;
                else if (DrvStren_ohm < 38 )  Stren_setting = 0x0b;
                else if (DrvStren_ohm < 45 )  Stren_setting = 0x0a;
                else if (DrvStren_ohm < 55 )  Stren_setting = 0x09;
                else if (DrvStren_ohm < 71 )  Stren_setting = 0x08;
                else if (DrvStren_ohm < 101 ) Stren_setting = 0x03;
                else if (DrvStren_ohm < 181 ) Stren_setting = 0x02;
                else if (DrvStren_ohm < 241 ) Stren_setting = 0x01;
                else                              Stren_setting = 0x00; // High-impedance
        } else if ( ( TargetCSR == ADrvStrenP  ) || ( TargetCSR == ADrvStrenN  ) ) {
                //......................................................................................
                // ADrvStrenP or ADrvStrenN
                //......................................................................................
                if      (DrvStren_ohm == 120)   Stren_setting = 0x00;
                else if (DrvStren_ohm == 60)    Stren_setting = 0x01;
                else if (DrvStren_ohm == 40)    Stren_setting = 0x03;
                else if (DrvStren_ohm == 30)    Stren_setting = 0x07;
                else if (DrvStren_ohm == 24)    Stren_setting = 0x0F;
                else if (DrvStren_ohm == 20)    Stren_setting = 0x1F;
        }

        return Stren_setting;
}

#if 0
int dwc_ddrphy_phyinit_C_initPhyConfig()
{
    int lane;
    int b_addr;
    int byte;
    int c_addr;
    int anib;
    int pstate;
    int p_addr;

    int TxSlewRate[4];
    int TxPreP[4];          // Default to 0xf (max). Optimal setting is technology specific.
    int TxPreN[4];          // Default to 0xf (max). Optimal setting is technology specific.
    int TxPreDrvMode;

    TxPreDrvMode = 0x2;
//userInputBasic.NumPStates = 1
    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        TxPreP[pstate] = userInputAdvanced.TxSlewRiseDQ[pstate];
        TxPreN[pstate] = userInputAdvanced.TxSlewFallDQ[pstate];

        TxSlewRate[pstate] = (TxPreDrvMode << csr_TxPreDrvMode_LSB) | (TxPreN[pstate] << csr_TxPreN_LSB) | (TxPreP[pstate] << csr_TxPreP_LSB);

	//userInputBasic.NumDbyte = 2
	//#define tDBYTE 0x10000
        for (byte=0; byte<userInputBasic.NumDbyte; byte++) {
            c_addr = byte << 12;
            for (lane=0; lane <= b_max ; lane++) {
                b_addr = lane << 8;
                dwc_ddrphy_apb_wr((p_addr | tDBYTE | c_addr | b_addr | csr_TxSlewRate_ADDR), TxSlewRate[pstate]);
            }
        }
    }

    /** 
     * - Program ATxSlewRate:
     *  - ATxSlewRate::ATxPreDrvMode is dependent on DramType and whether
     *    the ACX4 instance is used for AC or CK
     *  - ATxSlewRate::ATxPreP and ATxSlewRate::TxPreN are technology-specific
     *    User should consult the "Output Slew Rate" section of 
     *    HSpice Model App Note in specific technology for recommended settings
     */

    int ATxSlewRate;
    int ATxPreP;          // Default to 0xf (max). Optimal setting is technology specific.
    int ATxPreN;          // Default to 0xf (max). Optimal setting is technology specific.
    int ATxPreDrvMode; 
    int CK_ANIB_inst[2];

    //4
    ATxPreP = userInputAdvanced.TxSlewRiseAC;
    ATxPreN = userInputAdvanced.TxSlewFallAC;

    // # of ANIBs      CK ANIB Instance
    // ACX8            ANIB 1
    // ACX10           ANIB 4,5
    // ACX12           ANIB 4,5
    // ACX13           ANIB 4,5
    if (userInputBasic.NumAnib == 8) {
        CK_ANIB_inst[0] = 1;
        CK_ANIB_inst[1] = 1;
    }
    else if (userInputBasic.NumAnib == 10 || userInputBasic.NumAnib == 12 || userInputBasic.NumAnib == 13) {
        CK_ANIB_inst[0] = 4;
        CK_ANIB_inst[1] = 5;
    }

    //userInputBasic.NumAnib=0xa
    for (anib=0; anib<userInputBasic.NumAnib; anib++) {
        c_addr = anib << 12;

        if (anib == CK_ANIB_inst[0] || anib == CK_ANIB_inst[1] )  {// CK ANIB instance
            ATxPreDrvMode = 0x0;
        }
        else {// non-CK ANIB instance
            ATxPreDrvMode = 0x3;
        }

	//3<<8 | 4<<4 | 4 << 0
	//0x344
        ATxSlewRate = (ATxPreDrvMode << csr_ATxPreDrvMode_LSB) | (ATxPreN << csr_ATxPreN_LSB) | (ATxPreP << csr_ATxPreP_LSB);

	//tANIB=0 
	//csr_ATxSlewRate_ADDR=0x55
        dwc_ddrphy_apb_wr((tANIB | c_addr | csr_ATxSlewRate_ADDR), ATxSlewRate);
    }



    /** 
     * - Program DfiRdDataCsDestMap and DfiWrDataCsDestMap
     *   - Dependencies:
     *     mb_DDR4U_1D[0].MsgMisc[6] Determine Partial Rank Support
     */
    uint16_t DfiRdDataCsDestMap;
    uint16_t DfiWrDataCsDestMap;
    //.MsgMisc=0
    if ( (mb_DDR4U_1D[0].MsgMisc & 0x40) != 0)
      {
        DfiRdDataCsDestMap = 0xa0;
        DfiWrDataCsDestMap = 0xa0; 
	//userInputBasic.NumPStates=1
        for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
          p_addr = pstate << 20;
	  //tMASTER=0x20000
	  //csr_DfiRdDataCsDestMap_ADDR=0xb0
          dwc_ddrphy_apb_wr( (p_addr | tMASTER | csr_DfiRdDataCsDestMap_ADDR), DfiRdDataCsDestMap );
          dwc_ddrphy_apb_wr( (p_addr | tMASTER | csr_DfiWrDataCsDestMap_ADDR), DfiWrDataCsDestMap );
        }
      }

    /** 
     * - Program PllCtrl2:
     *   - Calculate PLL controls per p-state from Frequency
     */

    int PllCtrl2[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
          p_addr = pstate << 20;

          if (userInputBasic.Frequency[pstate]/2 < 235) {
            PllCtrl2[pstate] = 0x7;
          }
          else if(userInputBasic.Frequency[pstate]/2 < 313) {
            PllCtrl2[pstate] = 0x6;
          }
          else if(userInputBasic.Frequency[pstate]/2 < 469) {
            PllCtrl2[pstate] = 0xb;
          }
          else if(userInputBasic.Frequency[pstate]/2 < 625) {
            PllCtrl2[pstate] = 0xa;
          }
          else if(userInputBasic.Frequency[pstate]/2 < 938) {
            PllCtrl2[pstate] = 0x19;
          }
          else if(userInputBasic.Frequency[pstate]/2 < 1067) {
            PllCtrl2[pstate] = 0x18;
          }
          else {
            PllCtrl2[pstate] = 0x19;
          }

	  //200c5
          dwc_ddrphy_apb_wr( (p_addr | tMASTER | csr_PllCtrl2_ADDR), PllCtrl2[pstate] );
    }

    /**
     * - Program ARdPtrInitVal:
     *   - The values programmed here assume ideal properties of DfiClk and Pclk including:
     *     - DfiClk skew
     *     - DfiClk jitter
     *     - DfiClk PVT variations
     *     - Pclk skew
     *     - Pclk jitter
     *
     *     ARdPtrInitVal Programmed differently based on PLL Bypass mode and Frequency:
     *   - PLL Bypassed mode:
     *     - For MemClk frequency > 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 2-5
     *     - For MemClk frequency < 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 1-5
     *   - PLL Enabled mode:
     *     - For MemClk frequency > 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 1-5
     *     - For MemClk frequency < 933MHz, the valid range of ARdPtrInitVal_p0[3:0] is: 0-5
     */


    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        if (userInputBasic.Frequency[pstate] >= 933) {
            ARdPtrInitVal[pstate] = 0x2;
        }
        else {
            ARdPtrInitVal[pstate] = 0x1;
        }
        // Add one UI for synchronizer on SyncBus when PLL is bypassed
        if (userInputBasic.PllBypass[pstate] == 1) {
            ARdPtrInitVal[pstate] ++;
        }

	//2002e
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_ARdPtrInitVal_ADDR), ARdPtrInitVal[pstate]);
    }



    /**
     * - Program DbyteDllModeCntrl:
     *   - DllRxPreambleMode
     * - Program DqsPreambleControl:
     *   - Fields:
     *     - TwoTckRxDqsPre
     *     - TwoTckTxDqsPre
     *     - PositionDfeInit
     *     - LP4TglTwoTckTxDqsPre
     *     - LP4PostambleExt
     *     - LP4SttcPreBridgeRxEn
     *   - Dependencies:
     *      - user_input_basic.DramType

     *      - user_input_advanced.D4TxPreambleLength

     */
    int DqsPreambleControl;
    int TwoTckRxDqsPre[4];
    int TwoTckTxDqsPre=0;
    int PositionDfeInit;
    int LP4TglTwoTckTxDqsPre=0;
    int LP4PostambleExt=0;
    int LP4SttcPreBridgeRxEn=0;
    int WDQSEXTENSION=0;
    int DllRxPreambleMode=0;
    int DbyteDllModeCntrl;
    int DllLockParam;
    int DisDllSeedSel=0;
    int DisDllGainIVSeed=1;
    int LcdlSeed0=0x21;
    int DllGainCtl;
    int DllGainIV=0x1;
    int DllGainTV=0x6;


    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;


            // DDR4
            TwoTckRxDqsPre[pstate]  = userInputAdvanced.D4RxPreambleLength[pstate];
            LP4SttcPreBridgeRxEn    = 0x0;
            DllRxPreambleMode       = 0x1;
            TwoTckTxDqsPre          = userInputAdvanced.D4TxPreambleLength[pstate];
            LP4TglTwoTckTxDqsPre    = 0x0;
            PositionDfeInit         = 0x2;
            LP4PostambleExt         = 0x0;


	    //2<<2
        DqsPreambleControl = (WDQSEXTENSION << csr_WDQSEXTENSION_LSB) | (LP4SttcPreBridgeRxEn << csr_LP4SttcPreBridgeRxEn_LSB) | (LP4PostambleExt << csr_LP4PostambleExt_LSB) | (LP4TglTwoTckTxDqsPre << csr_LP4TglTwoTckTxDqsPre_LSB) | (PositionDfeInit << csr_PositionDfeInit_LSB) | (TwoTckTxDqsPre << csr_TwoTckTxDqsPre_LSB) | (TwoTckRxDqsPre[pstate] << csr_TwoTckRxDqsPre_LSB) ;

	//20024
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_DqsPreambleControl_ADDR), DqsPreambleControl);

	//1 << 1
        DbyteDllModeCntrl = DllRxPreambleMode << csr_DllRxPreambleMode_LSB;

	//2003a
        dwc_ddrphy_apb_wr((tMASTER | csr_DbyteDllModeCntrl_ADDR), DbyteDllModeCntrl);

	//1 | 6 <<4
        DllGainCtl = DllGainIV | (DllGainTV<<csr_DllGainTV_LSB);
	//1<<1 | 0x21 << 4
        DllLockParam =  DisDllSeedSel |  (DisDllGainIVSeed<<csr_DisDllGainIVSeed_LSB)|(LcdlSeed0<<csr_LcdlSeed0_LSB) ;
       //2007d
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_DllLockParam_ADDR), DllLockParam);

        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_DllGainCtl_ADDR), DllGainCtl);
    }


    /**
     * - Program ProcOdtTimeCtl:
     *   - Fields:
     *     - POdtStartDelay[3:2]
     *     - POdtTailWidth[1:0]
     *   - Dependencies:
     *     - user_input_basic.Frequency
     *     - user_input_basic.DramType
     */
    int ProcOdtTimeCtl[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        if (userInputAdvanced.WDQSExt) {
            ProcOdtTimeCtl[pstate] = 0x3;
        }
        // Memclk Freq <= 933MHz
        else if (userInputBasic.Frequency[pstate] <= 933) {
            ProcOdtTimeCtl[pstate] = 0xa;
        }
        // 933MHz < Memclk Freq <= 1200MHz
        else if (userInputBasic.Frequency[pstate] <= 1200) {
            if (TwoTckRxDqsPre[pstate] == 1) {
                ProcOdtTimeCtl[pstate] = 0x2;
            }
            else {
                ProcOdtTimeCtl[pstate] = 0x6;
            }
        }
        // Memclk Freq > 1200MHz
        else {
            if (TwoTckRxDqsPre[pstate] == 1) {
                ProcOdtTimeCtl[pstate] = 0x3;
            }
            else {
                ProcOdtTimeCtl[pstate] = 0x7;
            }
        }

	//20056
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_ProcOdtTimeCtl_ADDR), ProcOdtTimeCtl[pstate]);
    }

    /**
     * - Program TxOdtDrvStren:
     *   - Fields:
     *     - ODTStrenP_px[5:0]
     *     - ODTStrenN_px[11:6]
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.HardMacroVer
     *     - user_input_advanced.ODTImpedance
     */
    int   TxOdtDrvStren[4];
    int   ODTStrenP_state[4];
    int   ODTStrenN_state[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
      p_addr = pstate << 20;
      //input 2 0
      //0x18
      ODTStrenP_state[pstate] = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.ODTImpedance[pstate], ODTStrenP, userInputBasic.HardMacroVer );
      //0x0
      ODTStrenN_state[pstate] = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.ODTImpedance[pstate], ODTStrenN, userInputBasic.HardMacroVer );
      TxOdtDrvStren[pstate] = (ODTStrenN_state[pstate] << csr_ODTStrenN_LSB) | ODTStrenP_state[pstate];

      //userInputBasic.NumDbyte=2
      for (byte=0; byte<userInputBasic.NumDbyte; byte++) {
          c_addr = byte << 12;
          for (lane=0; lane <= b_max ; lane++) {
              b_addr = lane << 8;
	      //1004d + byte << 12 + lane << 8
              dwc_ddrphy_apb_wr((p_addr | tDBYTE | c_addr | b_addr | csr_TxOdtDrvStren_ADDR), TxOdtDrvStren[pstate]);
          }
      }
    }

    /**
     * - Program TxImpedanceCtrl1:
     *   - Fields:
     *     - DrvStrenFSDqP[5:0]
     *     - DrvStrenFSDqN[11:6]
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.HardMacroVer
     *     - user_input_advanced.TxImpedance
     */
    int TxImpedanceCtrl1[4];
    int DrvStrenFSDqP_state[4];
    int DrvStrenFSDqN_state[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        DrvStrenFSDqP_state[pstate] = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.TxImpedance[pstate], DrvStrenFSDqP, userInputBasic.HardMacroVer);
        DrvStrenFSDqN_state[pstate] = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.TxImpedance[pstate], DrvStrenFSDqN, userInputBasic.HardMacroVer);

        TxImpedanceCtrl1[pstate] = (DrvStrenFSDqN_state[pstate] << csr_DrvStrenFSDqN_LSB) | (DrvStrenFSDqP_state[pstate] << csr_DrvStrenFSDqP_LSB);

        for (byte=0; byte<userInputBasic.NumDbyte; byte++) {
            c_addr = byte << 12;
            for (lane=0; lane <= b_max ; lane++) {
                b_addr = lane << 8;
                dwc_ddrphy_apb_wr((p_addr | tDBYTE | c_addr | b_addr | csr_TxImpedanceCtrl1_ADDR), TxImpedanceCtrl1[pstate]);
            }
        }
    }


    /**
     * - Program ATxImpedance:
     *   - Fields:
     *     - ADrvStrenP[4:0]
     *     - ADrvStrenN[9:5]
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.HardMacroVer
     *     - user_input_advanced.ATxImpedance
     */
    int ATxImpedance;
    int ADrvStrenP_state;
    int ADrvStrenN_state;

    // In hardmacro family E, the default 20 Ohm value is invalid
    // override de default value to be 40ohm
    if ( userInputBasic.HardMacroVer == 4 )  {
      if( userInputAdvanced.ATxImpedance == 20 ) {
        userInputAdvanced.ATxImpedance = 40;
      }
    }

    ADrvStrenP_state    = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.ATxImpedance, ADrvStrenP, userInputBasic.HardMacroVer);
    ADrvStrenN_state    = dwc_ddrphy_phyinit_mapDrvStren ((int) userInputAdvanced.ATxImpedance, ADrvStrenN, userInputBasic.HardMacroVer);

    ATxImpedance  = (ADrvStrenN_state << csr_ADrvStrenN_LSB) | (ADrvStrenP_state << csr_ADrvStrenP_LSB);

    for (anib=0; anib<userInputBasic.NumAnib; anib++) {
        c_addr = anib << 12;
        dwc_ddrphy_apb_wr(( tANIB | c_addr | csr_ATxImpedance_ADDR), ATxImpedance);
    }

    /**
     * - Program DfiMode:
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.Dfi1Exists
     *     - user_input_basic.NumActiveDbyteDfi0
     *     - user_input_basic.NumActiveDbyteDfi1
     *     - user_input_basic.NumAnib 
     */
    int DfiMode;

    if(userInputBasic.Dfi1Exists == 1) {
        DfiMode = 0x5;     // DFI1 exists but disabled; DFI0 controls entire PHY
    }
    else {
        DfiMode = 0x1;     // DFI1 does not physically exists
    }

    //20018
    dwc_ddrphy_apb_wr((tMASTER | csr_DfiMode_ADDR), DfiMode);

    /**
     * - Program DfiCAMode:
     *   - Fields:
     *     - DfiLp3CAMode
     *     - DfiD4CAMode
     *     - DfiLp4CAMode
     *     - DfiD4AltCAMode
     *   - Dependencies:
     *     - user_input_basic.DramType
     */
    int DfiCAMode=0;

    // DDR4
    DfiCAMode = 2;

    //20075
    dwc_ddrphy_apb_wr((tMASTER | csr_DfiCAMode_ADDR), DfiCAMode);

    /**
     * - Program CalDrvStr0:
     *   - Fields:
     *     - CalDrvStrPd50[3:0]
     *     - CalDrvStrPu50[7:4]
     *   - Dependencies:
     *     - user_input_advanced.ExtCalResVal
     */
    uint16_t CalDrvStr0;
    uint16_t CalDrvStrPd50;
    uint16_t CalDrvStrPu50;

    if (userInputBasic.HardMacroVer ==  4 )
      {
        switch (userInputAdvanced.ExtCalResVal)
          {
            case 0x1: // 120
              CalDrvStrPu50 = 0x1;
              break;
            case 0x2: // 40
              CalDrvStrPu50 = 0x2;
              break;
            default:
              CalDrvStrPu50 = 0x0;
          }
      }
    else
      {
        CalDrvStrPu50 = userInputAdvanced.ExtCalResVal;
      }

    CalDrvStrPd50 = CalDrvStrPu50;
    CalDrvStr0 = (CalDrvStrPu50 << csr_CalDrvStrPu50_LSB) | CalDrvStrPd50;
    //20050
    dwc_ddrphy_apb_wr((tMASTER | csr_CalDrvStr0_ADDR), CalDrvStr0);

    /**
     * - Program CalVRefs:
     *   - Impedance calibration VRef for Hard Macro E.
     *   - Dependencies:
     *     - user_input_basic.HardMacro
     */
    uint16_t CalVRefs;
    if (userInputBasic.HardMacroVer ==  4)
      {
        CalVRefs = 0x2;
        dwc_ddrphy_apb_wr((tMASTER | csr_CalVRefs_ADDR), CalVRefs);
      }

    /**
     * - Program CalUclkInfo:
     *   - Impedance calibration CLK Counter.
     *   - Fields:
     *     - CalUClkTicksPer1uS
     *   - Dependencies:
     *     - user_input_basic.Frequency
     */
    double  CalUClkTicksPer1uS_double[4];
    uint16_t     CalUClkTicksPer1uS[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        // Number of DfiClk cycles per 1us
        CalUClkTicksPer1uS_double[pstate] = (double)  (1.0*userInputBasic.Frequency[pstate])/2.0;
        CalUClkTicksPer1uS[pstate]        = (int) ceil ( CalUClkTicksPer1uS_double[pstate] );

        if (CalUClkTicksPer1uS[pstate] < 24)
            CalUClkTicksPer1uS[pstate] = 24;  // Minimum value of CalUClkTicksPer1uS = 24

	//20008
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_CalUclkInfo_ADDR), CalUClkTicksPer1uS[pstate]);
    }


    //##############################################################
    //
    // Program Calibration CSRs based on user input
    //
    // CSRs to program:
    //      CalRate:: CalInterval
    //             :: CalOnce
    //
    // User input dependencies::
    //      CalInterval
    //      CalOnce
    //
    //##############################################################
    int CalRate;
    int CalInterval;
    int CalOnce;

    CalInterval = userInputAdvanced.CalInterval;
    CalOnce = userInputAdvanced.CalOnce;

    CalRate = (CalOnce << csr_CalOnce_LSB) | (CalInterval << csr_CalInterval_LSB);

    //20088
    dwc_ddrphy_apb_wr((tMASTER | csr_CalRate_ADDR), CalRate);

    /**
     * - Program VrefInGlobal:
     *   - DqDqsRcvCntrl and csrVrefInGlobal to select Global VREF
     *     from Master to be used in each DQ
     *   - Fields:
     *     - GlobalVrefInSel: Select Range of GlobalVref DAC. Default: set to 1.
     *     - GlobalVrefInDAC: Vref level is set based on mb_DDR4U_1D[pstate].PhyVref value.
     *       The following formula is used to convert the PhyVref into the register setting.
     *       \f{eqnarray*}{
     *           PhyVrefPrcnt &=& \frac{mb DDR4U 1D[pstate].PhyVref}{128} \\
     *        if GlobalVrefInSel = 1 :
     *           GlobalVrefInDAC &=& 1+\frac{PhyVrefPrcnt}{0.005} \\
     *        if GlobalVrefInSel = 0 :
     *           GlobalVrefInDAC &=& \frac{(PhyVrefPrcnt-0.345)}{0.005} \\
     *           RxVref &=& (GlobalVrefInDAC == 0) ? Hi-Z : (PhyVrefPrcnt \times VDDQ)
     *        \f}
     *   - Dependencies:
     *     - user_input_basic.DramType
     *
     * - Program DqDqsRcvCntrl:
     *   - DqDqsRcvCntrl and csrVrefInGlobal to select Global VREF
     *     from Master to be used in each DQ
     *   - Fields:
     *    - SelAnalogVref
     *    - MajorModeDbyte
     *    - ExtVrefRange
     *    - DfeCtrl
     *    - GainCurrAdj
     *   - Dependencies:
     *     - user_input_basic.DramType
     */
    int VrefInGlobal;
    int DqDqsRcvCntrl;
    int SelAnalogVref = 1; // Use Global VREF from Master
    int MajorModeDbyte = 0;
    int ExtVrefRange_defval = 0;
    int DfeCtrl_defval = 0;
    int GainCurrAdj_defval = 0xb;

    // DDR4
    MajorModeDbyte = 3;

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        int32_t vref_percentVddq = (mb_DDR4U_1D[pstate].PhyVref)*1000*100/128;
        uint8_t GlobalVrefInDAC = 0x0; 
        uint8_t GlobalVrefInSel = 0x4;
        // check range1 first. Only use range0 if customer input maxes out range1
        GlobalVrefInDAC = (uint8_t)((vref_percentVddq / 500)+1);  // Min value is 1
        if (GlobalVrefInDAC > 127){
           GlobalVrefInDAC = (uint8_t)(max((vref_percentVddq-34500),500) / 500); // Min value is 1
           GlobalVrefInSel = 0x0;
        }
        GlobalVrefInDAC = min(GlobalVrefInDAC,127);

        VrefInGlobal = (GlobalVrefInDAC << csr_GlobalVrefInDAC_LSB) | GlobalVrefInSel;
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_VrefInGlobal_ADDR), VrefInGlobal);

        DqDqsRcvCntrl = (GainCurrAdj_defval << csr_GainCurrAdj_LSB) | (MajorModeDbyte << csr_MajorModeDbyte_LSB) | (DfeCtrl_defval << csr_DfeCtrl_LSB) | (ExtVrefRange_defval << csr_ExtVrefRange_LSB) | (SelAnalogVref << csr_SelAnalogVref_LSB);

        for (byte=0; byte<userInputBasic.NumDbyte; byte++) {
            c_addr = byte << 12;
            for (lane=0; lane <= b_max ; lane++) {
                b_addr = lane << 8;
		//10043
                dwc_ddrphy_apb_wr((p_addr | tDBYTE | c_addr | b_addr | csr_DqDqsRcvCntrl_ADDR), DqDqsRcvCntrl);
            }
        }
    }


    /**
     * - Program MemAlertControl and MemAlertControl2:
     *   - Fields:
     *     - MALERTVrefLevel
     *     - MALERTPuStren
     *     - MALERTPuEn
     *     - MALERTRxEn
     *     - MALERTSyncBypass
     *     - MALERTDisableVal
     *   - Dependencies:
     *     - user_input_advanced.MemAlertEn
     *     - user_input_advanced.MemAlertPUImp
     *     - user_input_advanced.MemAlertVrefLevel
     */
    int MemAlertControl;
    int MemAlertControl2;
    int MALERTPuEn;
    int MALERTRxEn;
    int MALERTVrefLevel;
    int MALERTPuStren;
    int MALERTSyncBypass;
    int MALERTDisableVal_defval = 1;

    // MemAlert applies to DDR4(all DIMM) or DDR3(RDIMM) only
    if ( (userInputBasic.DramType ==  DDR4 || (userInputBasic.DramType ==  DDR3 && userInputBasic.DimmType ==  RDIMM)) && userInputAdvanced.MemAlertEn == 1) {
        MALERTPuEn = 1;
        MALERTRxEn = 1;
        MALERTPuStren = userInputAdvanced.MemAlertPUImp;
        MALERTVrefLevel = userInputAdvanced.MemAlertVrefLevel;
        MALERTSyncBypass = userInputAdvanced.MemAlertSyncBypass;

        MemAlertControl = (MALERTDisableVal_defval << 14) | (MALERTRxEn << 13) | (MALERTPuEn << 12) | (MALERTPuStren << 8) | MALERTVrefLevel;
        MemAlertControl2 = (MALERTSyncBypass << csr_MALERTSyncBypass_LSB);

        dwc_ddrphy_apb_wr((tMASTER | csr_MemAlertControl_ADDR), MemAlertControl);
        dwc_ddrphy_apb_wr((tMASTER | csr_MemAlertControl2_ADDR), MemAlertControl2);

    }


    /**
     * - Program DfiFreqRatio :
     *   - Dependencies:
     *     - user_input_basic.DfiFreqRatio
     */
    int DfiFreqRatio[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;

        DfiFreqRatio[pstate] = userInputBasic.DfiFreqRatio[pstate];

	//200fa
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_DfiFreqRatio_ADDR), DfiFreqRatio[pstate]);
    }

    /**
     * - Program TristateModeCA based on DramType and 2T Timing
     *   - Fields:
     *     - CkDisVal
     *     - DisDynAdrTri
     *     - DDR2TMode
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_advanced.Is2Ttiming
     *     - user_input_advanced.DisDynAdrTri
     */
    int TristateModeCA[4];
    int DisDynAdrTri[4];
    int DDR2TMode[4];
    int CkDisVal_def;

    // CkDisVal depends on DramType
    // DDR4 or DDR3
    CkDisVal_def = 1; // {CLK_t,CLK_c} = 2'b00;

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
      p_addr = pstate << 20;

      DisDynAdrTri[pstate] = userInputAdvanced.DisDynAdrTri[pstate];

      DDR2TMode[pstate] = userInputAdvanced.Is2Ttiming[pstate];

      //1<<2|
        TristateModeCA[pstate] = (CkDisVal_def << csr_CkDisVal_LSB) | (DDR2TMode[pstate] << csr_DDR2TMode_LSB) | (DisDynAdrTri[pstate] << csr_DisDynAdrTri_LSB) ;
        //20019
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_TristateModeCA_ADDR), TristateModeCA[pstate]);

    }


    /**
     * - Program DfiXlat based on Pll Bypass Input
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.PllBypass
     */

    uint16_t loopVector;
    uint16_t dfifreqxlat_dat;
    uint16_t pllbypass_dat;
    uint16_t skipddc_dat=0; // set to vector offset based on Pstate frequency to disable dram drift compensation.
    //0
    pllbypass_dat = (userInputBasic.PllBypass[3] << 12) | (userInputBasic.PllBypass[2]<< 8) | (userInputBasic.PllBypass[1]<< 4) | (userInputBasic.PllBypass[0]);

    for (pstate=0; pstate<=3; pstate++) {
        if (userInputBasic.Frequency[pstate] < 333) skipddc_dat = skipddc_dat | (0x5 << 4*pstate);
    }


    for(loopVector=0; loopVector<8; loopVector++) {
        if (loopVector == 0 ) { // Relock DfiFreq = 00,01,02,03)  Use StartVec 5 (pll_enabled) or StartVec 6 (pll_bypassed)
            dfifreqxlat_dat = pllbypass_dat + 0x5555;
	    //200f0
            dwc_ddrphy_apb_wr((c0 | tMASTER | (csr_DfiFreqXlat0_ADDR+loopVector)), dfifreqxlat_dat);
        } else if (loopVector == 7) { // LP3-entry DfiFreq = 1F
            dwc_ddrphy_apb_wr((c0 | tMASTER | (csr_DfiFreqXlat0_ADDR+loopVector)), 0xF000);
        } else { // everything else = skip retrain  (could also map to 0000 since retrain code is excluded, but this is cleaner)
            dwc_ddrphy_apb_wr((c0 | tMASTER | (csr_DfiFreqXlat0_ADDR+loopVector)), 0x5555);
        }

    }

    /**
     * - Program DqDqsRcvCntrl1 (Receiver Powerdown) and DbyteMiscMode
     *   - see function dwc_ddrphy_phyinit_IsDbyteDisabled() to determine
     *     which DBytes are turned off completely based on PHY configuration.
     *   - Fields:
     *     - DByteDisable
     *     - PowerDownRcvr
     *     - PowerDownRcvrDqs
     *     - RxPadStandbyEn
     *   - Dependencies:
     *     - user_input_basic.DramType
     *     - user_input_basic.Dfi1Exists
     *     - user_input_basic.NumActiveDbyteDfi0
     *     - user_input_basic.NumActiveDbyteDfi1
     *     - user_input_basic.NumDbyte

     *     - user_input_basic.DramDataWidth
     *     - mb_DDR4U_1D[0].MR5

     */
    uint16_t regData;
    regData = 0x1 << csr_DByteDisable_LSB;
    unsigned int regData1;
    regData1 = (0x1ff << csr_PowerDownRcvr_LSB | 0x1 << csr_PowerDownRcvrDqs_LSB | 0x1 << csr_RxPadStandbyEn_LSB) ;
    unsigned int regData2; // turn off Rx of DBI lane
    //500
    regData2 = (0x100 << csr_PowerDownRcvr_LSB | csr_RxPadStandbyEn_MASK) ;

    int d;
    // Implements Section 1.3 of Pub Databook
    for (d=0;d<userInputBasic.NumDbyte;d++)  // for each dbyte
      {
	      //c1 0x1000
        c_addr = d*c1;
	//d=0,1 return
        if (dwc_ddrphy_phyinit_IsDbyteDisabled(d))
          {
            dwc_ddrphy_apb_wr((c_addr | tDBYTE | csr_DbyteMiscMode_ADDR), regData);
            dwc_ddrphy_apb_wr((c_addr | tDBYTE | csr_DqDqsRcvCntrl1_ADDR), regData1);
          }
        else
          {
           // disable RDBI lane if not used.

            if ( (userInputBasic.DramDataWidth != 4 ) &&
                 ((mb_DDR4U_1D[0].MR5 >> 12) & 0x1) == 0 &&
                 ((mb_DDR4U_1D[1].MR5 >> 12) & 0x1) == 0 &&
                 ((mb_DDR4U_1D[2].MR5 >> 12) & 0x1) == 0 &&
                 ((mb_DDR4U_1D[3].MR5 >> 12) & 0x1) == 0)
              {

		      //1004a
                dwc_ddrphy_apb_wr((c_addr | tDBYTE | csr_DqDqsRcvCntrl1_ADDR), regData2);

              } // DBI

          } // DbyteDisable.
      } // for each dbyte

    /**
     * - Program DqDqsRcvCntrl1 (Receiver Powerdown) and DbyteMiscMode
     *   - Fields:
     *     - X4TG
     *     - MasterX4Config
     *   - Dependencies:
     *     - user_input_basic.DramDataWidth
     *
     * \note PHY does not support mixed dram device data width
     */
    int X4TG;
    int MasterX4Config;

    if (userInputBasic.DramDataWidth == 4)
        X4TG = 0xf;
    else
        X4TG = 0x0;

    MasterX4Config = X4TG << csr_X4TG_LSB;

    //20025
    dwc_ddrphy_apb_wr((tMASTER | csr_MasterX4Config_ADDR), MasterX4Config);

    /**
     * - Program DMIPinPresent based on DramType and Read-DBI enable
     *   - Fields:
     *     - RdDbiEnabled
     *   - Dependencies:
     *     - user_input_basic.DramDataWidth
     *     - mb_DDR4U_1D[0].MR5 
     */
    int DMIPinPresent[4];

    for (pstate=0; pstate<userInputBasic.NumPStates; pstate++) {
        p_addr = pstate << 20;
        
        // For DDR4, Read DBI is enabled in MR5-A12
        DMIPinPresent[pstate] = (mb_DDR4U_1D[pstate].MR5 >> 12) & 0x1;

	//2002d
        dwc_ddrphy_apb_wr((p_addr | tMASTER | csr_DMIPinPresent_ADDR), DMIPinPresent[pstate]);
    }



    uint16_t AForceTriCont=0x0;
    uint16_t Acx4AnibDis= 0x0;
    int NumRank = userInputBasic.NumRank_dfi0 + userInputBasic.NumRank_dfi1;
    for (anib=0; (anib<userInputBasic.NumAnib) && userInputAdvanced.DisableUnusedAddrLns; anib++)
      {
        c_addr = anib << 12;
        AForceTriCont=0x0;
        if (userInputBasic.NumAnib == 12)
          {
            if      (anib == 0 && NumRank == 1 ) AForceTriCont = 0xe;
            else if (anib == 0 && NumRank == 2 ) AForceTriCont = 0xc;
            else if (anib == 0 && NumRank == 3 ) AForceTriCont = 0x8;
            else if (anib == 0 && NumRank == 4 ) AForceTriCont = 0x0;
            else if (anib == 4 && NumRank  < 3 ) AForceTriCont = 0xc;
            else if (anib == 5 && NumRank == 1 ) AForceTriCont = 0xf;
            else if (anib == 5 && NumRank  < 4 ) AForceTriCont = 0xc;
            else if (anib == 8 ) AForceTriCont = 0x1; // MTEST
            else if (anib == 9 && userInputBasic.DimmType == UDIMM )
              {
                AForceTriCont = userInputBasic.DramDataWidth == 0x4 ? 0x7 : 0xf;
              }
            else if (anib == 10 && NumRank == 1 ) AForceTriCont = 0xe;
            else if (anib == 10 && NumRank == 2 ) AForceTriCont = 0xc;
            else if (anib == 10 && NumRank == 3 ) AForceTriCont = 0x8;
            else if (anib == 10 && NumRank == 4 ) AForceTriCont = 0x0;
            else if (anib == 11 && NumRank == 1 ) AForceTriCont = 0xe;
            else if (anib == 11 && NumRank == 2 ) AForceTriCont = 0xc;
            else if (anib == 11 && NumRank == 3 ) AForceTriCont = 0x8;
          }
        else if (userInputBasic.NumAnib == 10) 
          {
            if      (anib == 0 && NumRank == 1 && userInputBasic.DimmType == UDIMM) AForceTriCont = 0xa;
            else if (anib == 0 && NumRank == 2 && userInputBasic.DimmType == UDIMM) AForceTriCont = 0x8;
            else if (anib == 0 && NumRank == 1 && userInputBasic.DimmType != UDIMM) AForceTriCont = 0x2;
            else if (anib == 4 ) AForceTriCont = 0xc;
            else if (anib == 5 && NumRank == 1 ) AForceTriCont = 0xf;
            else if (anib == 5 && NumRank == 2 ) AForceTriCont = 0xc;
            else if (anib == 8 && userInputBasic.DimmType == UDIMM ) AForceTriCont = 0x1;
            else if (anib == 9 && NumRank == 1 && userInputBasic.DimmType == UDIMM) AForceTriCont = 0xe;
            else if (anib == 9 && NumRank == 2 && userInputBasic.DimmType == UDIMM) AForceTriCont = 0x8;
            else if (anib == 9 && NumRank == 1 && userInputBasic.DimmType != UDIMM) AForceTriCont = 0x6;
          }
        else if (userInputBasic.NumAnib == 8) 
          {
            if (anib == 0 && NumRank == 1) AForceTriCont = 0x2;
            else if (anib == 1 && NumRank == 1) AForceTriCont = 0xc;
            else if (anib == 6) AForceTriCont = 0x1;
          }

        // if all the lanes can be disabled, and Anib is not the first or last disable entire chiplet
        if ( AForceTriCont == 0xf && anib !=0 && anib !=userInputBasic.NumAnib-1) Acx4AnibDis = Acx4AnibDis | (0x1 << anib);
        dwc_ddrphy_apb_wr(( tANIB | c_addr | csr_AForceTriCont_ADDR), AForceTriCont);
      }
    //2002c
    dwc_ddrphy_apb_wr(( tMASTER |  csr_Acx4AnibDis_ADDR), Acx4AnibDis);


}
#endif

int dwc_ddrphy_phyinit_userCustom_E_setDfiClk(int val)
{
	return 0;
}

int get_mail(int mode)
{
	int mail;

	while((0x1&dwc_ddrphy_apb_rd(0x000d0004)) != 0){;} //UctWriteProtShadow

	mail = dwc_ddrphy_apb_rd(0x000d0032);

	if(mode==32) {
		mail |= (dwc_ddrphy_apb_rd(0x000d0034)<<16);
	}
	
	dwc_ddrphy_apb_wr(0x000d0031, 0);
	while((0x1&dwc_ddrphy_apb_rd(0x000d0004)) == 0) {;} //UctWriteProtShadow
	dwc_ddrphy_apb_wr(0x000d0031, 1);
	return mail;
}
#if 0
void c_uvm_info(int level, const char *fmt)
{
#ifdef SIMULATION
	return;
#else
	if(level == 0)
		printf(fmt);
#endif
}
#endif
#define c_uvm_info printf
#define c_uvm_error c_uvm_info

void decode_major_message(int major_info)
{
        if(major_info == 0x00) {
                c_uvm_info("End of initialization.\n");
        }
        else if(major_info == 0x01) {
                c_uvm_info("End of fine write leveling.\n");
        }
        else if(major_info == 0x02) {
                c_uvm_info("End of read enable training.\n");
        }
        else if(major_info == 0x03) {
                c_uvm_info("End of read delay center optimization.\n");
        }
        else if(major_info == 0x04) {
                c_uvm_info("End of write dealy center optimization.\n");
        }
        else if(major_info == 0x05) {
                c_uvm_info("End of 2D read delay/voltage center optimization.\n");
        }
        else if(major_info == 0x06) {
                c_uvm_info("End of 2D write delay/voltage center optimization.\n");
        }
        else if(major_info == 0x09) {
                c_uvm_info("End of max read latency training.\n");
        }
        else if(major_info == 0x0a) {
                c_uvm_info("End of read dq deskew training.\n");
        }
        else if(major_info == 0x0b) {
                c_uvm_info("Reserved\n");
        }
        else if(major_info == 0x0c) {
                c_uvm_info("End of all DB training.\n");
        }
        else if(major_info == 0x0d) {
                c_uvm_info("End of CA training.\n");
        }
        else if(major_info == 0xfd) {
                c_uvm_info("End of MPR read delay center optimization.\n");
        }
        else if(major_info == 0xfe) {
                c_uvm_info("End of Write leveling coarse delay.\n");
        }
        else if(major_info == 0x07) {
                c_uvm_info("Training has run successfully.\n");
        }
        else if(major_info == 0xff) {
                c_uvm_error("Training has failed.\n");
        }
        else if(major_info == 0x8) {
        //        c_display_error(0, "0x%0x, NOT defined major message.", major_info);
	        ;//        printf("0x%0x, NOT defined major message.\n", major_info);
        }
}

int find_streaming_idx(int streaming_idx) {
        for(int i=0; i<TRAIN_1D_MSG_NUM; i++) {
                if(streaming_idx_arr[i] == streaming_idx) {
                        return i;
                }
        }
        printf("streaming_loc can not find, streaming_idx=0x%x\n", streaming_idx);
        return -1;
}
#if 0
void find_streaming_msg(int loc, int msg_code[], int msg_code_num) {
//    char msg[200];
	int i;

        if( (loc<0) || (loc>=TRAIN_1D_MSG_NUM) ) {
                printf("streaming_loc error, loc=%d\n", loc);
        }
        printf("streaming_msg_arr number is %d !\n", loc);
//    strcpy(msg, streaming_msg_arr[loc]);

//    printf("--%s\n",msg);

        printf("--msg_code_num is %d\n", msg_code_num);
        for(i = 0;i < msg_code_num;i++)
                printf("msg_code[%d]--%d-\n",i,msg_code[i]);
#if 0
    if(msg_code_num == 0) {
        //send_message(msg, UVM_INFO);
	printf(msg);
    }
    else if(msg_code_num == 1) {
        printf(msg, msg_code[0]);
    }
    else if(msg_code_num == 2) {
        printf(msg, msg_code[0], msg_code[1]);
    }
    else if(msg_code_num == 3) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2]);
    }
    else if(msg_code_num == 4) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3]);
    }
    else if(msg_code_num == 5) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4]);
    }
    else if(msg_code_num == 6) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5]);
    }
    else if(msg_code_num == 7) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6]);
    }
    else if(msg_code_num == 8) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6], msg_code[7]);
    }
    else if(msg_code_num == 9) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6], msg_code[7], msg_code[8]);
    }
    else if(msg_code_num == 10) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6], msg_code[7], msg_code[8], msg_code[9]);
    }
    else if(msg_code_num == 11) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6], msg_code[7], msg_code[8], msg_code[9], msg_code[10]);
    }
    else if(msg_code_num == 12) {
        printf(msg, msg_code[0], msg_code[1], msg_code[2], msg_code[3], msg_code[4], msg_code[5], msg_code[6], msg_code[7], msg_code[8], msg_code[9], msg_code[10], msg_code[11]);
    }
    else {
        //send_message_hex("msg_code_num error, msg_code_num=", msg_code_num, UVM_FATAL);
        printf("msg_code_num error, msg_code_num=%d\n", msg_code_num);
    }
#endif
}
#endif
#if 0
void get_streaming_message(int Train2D) {
        int streaming_message;
        int string_num;
        int loc;
        int msg_code[20];
        int string_data = get_mail(32);
        if(Train2D == 0) {
                loc = find_streaming_idx(string_data);
        }
        else {
                ;//FHT//loc = find_streaming_idx_2d(string_data);
        }

        string_num = string_data & 0xffff;
        for(int i=0; i<string_num; i++) {
                streaming_message = get_mail(32);
                msg_code[i] = streaming_message;
        }
        if(Train2D == 0) {
                find_streaming_msg(loc, msg_code, string_num);
        }
        else {
                ;//FHT//find_streaming_msg_2d(loc, msg_code, string_num);
        }

}
#endif
int dwc_ddrphy_phyinit_userCustom_G_waitFwDone(void)
{
//	int Train2D = 0;
	int major_info;
 //    c_uvm_info(0, "waiting training...");
	printf("waiting training!\n");

	while(1) {
		major_info = get_mail(16);
		decode_major_message(major_info);
		if( (major_info==0x07) || (major_info==0xff) ) {
			break;
		}

		if(major_info == 0x8) {
		//	get_streaming_message(Train2D);
	//		get_streaming_message(0);
			printf("Training Error\n");
			//c_uvm_error(0, "Training Error");
		}
	}

	if(major_info==0xff) {
		printf("DDR Training Failed.\n");//    c_uvm_fatal(0, "DDR Training Failed.");
	}

	return 0;
}

int dwc_ddrphy_phyinit_userCustom_H_readMsgBlock(int val)
{
	return 0;
}

int dwc_ddrphy_phyinit_userCustom_customPostTrain (void)
{
	return 0;
}

int dwc_ddrphy_phyinit_userCustom_J_enterMissionMode (void)
{
	return 0;
}

#endif
