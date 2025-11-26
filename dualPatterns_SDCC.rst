                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.0.0 #11528 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module dualPatterns_SDCC
                                      6 	.optsdcc -mmcs51 --model-small
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _TF2
                                     13 	.globl _EXF2
                                     14 	.globl _RCLK
                                     15 	.globl _TCLK
                                     16 	.globl _EXEN2
                                     17 	.globl _TR2
                                     18 	.globl _C_T2
                                     19 	.globl _CP_RL2
                                     20 	.globl _T2CON_7
                                     21 	.globl _T2CON_6
                                     22 	.globl _T2CON_5
                                     23 	.globl _T2CON_4
                                     24 	.globl _T2CON_3
                                     25 	.globl _T2CON_2
                                     26 	.globl _T2CON_1
                                     27 	.globl _T2CON_0
                                     28 	.globl _PT2
                                     29 	.globl _ET2
                                     30 	.globl _CY
                                     31 	.globl _AC
                                     32 	.globl _F0
                                     33 	.globl _RS1
                                     34 	.globl _RS0
                                     35 	.globl _OV
                                     36 	.globl _F1
                                     37 	.globl _P
                                     38 	.globl _PS
                                     39 	.globl _PT1
                                     40 	.globl _PX1
                                     41 	.globl _PT0
                                     42 	.globl _PX0
                                     43 	.globl _RD
                                     44 	.globl _WR
                                     45 	.globl _T1
                                     46 	.globl _T0
                                     47 	.globl _INT1
                                     48 	.globl _INT0
                                     49 	.globl _TXD
                                     50 	.globl _RXD
                                     51 	.globl _P3_7
                                     52 	.globl _P3_6
                                     53 	.globl _P3_5
                                     54 	.globl _P3_4
                                     55 	.globl _P3_3
                                     56 	.globl _P3_2
                                     57 	.globl _P3_1
                                     58 	.globl _P3_0
                                     59 	.globl _EA
                                     60 	.globl _ES
                                     61 	.globl _ET1
                                     62 	.globl _EX1
                                     63 	.globl _ET0
                                     64 	.globl _EX0
                                     65 	.globl _P2_7
                                     66 	.globl _P2_6
                                     67 	.globl _P2_5
                                     68 	.globl _P2_4
                                     69 	.globl _P2_3
                                     70 	.globl _P2_2
                                     71 	.globl _P2_1
                                     72 	.globl _P2_0
                                     73 	.globl _SM0
                                     74 	.globl _SM1
                                     75 	.globl _SM2
                                     76 	.globl _REN
                                     77 	.globl _TB8
                                     78 	.globl _RB8
                                     79 	.globl _TI
                                     80 	.globl _RI
                                     81 	.globl _P1_7
                                     82 	.globl _P1_6
                                     83 	.globl _P1_5
                                     84 	.globl _P1_4
                                     85 	.globl _P1_3
                                     86 	.globl _P1_2
                                     87 	.globl _P1_1
                                     88 	.globl _P1_0
                                     89 	.globl _TF1
                                     90 	.globl _TR1
                                     91 	.globl _TF0
                                     92 	.globl _TR0
                                     93 	.globl _IE1
                                     94 	.globl _IT1
                                     95 	.globl _IE0
                                     96 	.globl _IT0
                                     97 	.globl _P0_7
                                     98 	.globl _P0_6
                                     99 	.globl _P0_5
                                    100 	.globl _P0_4
                                    101 	.globl _P0_3
                                    102 	.globl _P0_2
                                    103 	.globl _P0_1
                                    104 	.globl _P0_0
                                    105 	.globl _TH2
                                    106 	.globl _TL2
                                    107 	.globl _RCAP2H
                                    108 	.globl _RCAP2L
                                    109 	.globl _T2CON
                                    110 	.globl _B
                                    111 	.globl _ACC
                                    112 	.globl _PSW
                                    113 	.globl _IP
                                    114 	.globl _P3
                                    115 	.globl _IE
                                    116 	.globl _P2
                                    117 	.globl _SBUF
                                    118 	.globl _SCON
                                    119 	.globl _P1
                                    120 	.globl _TH1
                                    121 	.globl _TH0
                                    122 	.globl _TL1
                                    123 	.globl _TL0
                                    124 	.globl _TMOD
                                    125 	.globl _TCON
                                    126 	.globl _PCON
                                    127 	.globl _DPH
                                    128 	.globl _DPL
                                    129 	.globl _SP
                                    130 	.globl _P0
                                    131 	.globl _mode
                                    132 	.globl _check_button
                                    133 	.globl _delay_short
                                    134 ;--------------------------------------------------------
                                    135 ; special function registers
                                    136 ;--------------------------------------------------------
                                    137 	.area RSEG    (ABS,DATA)
      000000                        138 	.org 0x0000
                           000080   139 _P0	=	0x0080
                           000081   140 _SP	=	0x0081
                           000082   141 _DPL	=	0x0082
                           000083   142 _DPH	=	0x0083
                           000087   143 _PCON	=	0x0087
                           000088   144 _TCON	=	0x0088
                           000089   145 _TMOD	=	0x0089
                           00008A   146 _TL0	=	0x008a
                           00008B   147 _TL1	=	0x008b
                           00008C   148 _TH0	=	0x008c
                           00008D   149 _TH1	=	0x008d
                           000090   150 _P1	=	0x0090
                           000098   151 _SCON	=	0x0098
                           000099   152 _SBUF	=	0x0099
                           0000A0   153 _P2	=	0x00a0
                           0000A8   154 _IE	=	0x00a8
                           0000B0   155 _P3	=	0x00b0
                           0000B8   156 _IP	=	0x00b8
                           0000D0   157 _PSW	=	0x00d0
                           0000E0   158 _ACC	=	0x00e0
                           0000F0   159 _B	=	0x00f0
                           0000C8   160 _T2CON	=	0x00c8
                           0000CA   161 _RCAP2L	=	0x00ca
                           0000CB   162 _RCAP2H	=	0x00cb
                           0000CC   163 _TL2	=	0x00cc
                           0000CD   164 _TH2	=	0x00cd
                                    165 ;--------------------------------------------------------
                                    166 ; special function bits
                                    167 ;--------------------------------------------------------
                                    168 	.area RSEG    (ABS,DATA)
      000000                        169 	.org 0x0000
                           000080   170 _P0_0	=	0x0080
                           000081   171 _P0_1	=	0x0081
                           000082   172 _P0_2	=	0x0082
                           000083   173 _P0_3	=	0x0083
                           000084   174 _P0_4	=	0x0084
                           000085   175 _P0_5	=	0x0085
                           000086   176 _P0_6	=	0x0086
                           000087   177 _P0_7	=	0x0087
                           000088   178 _IT0	=	0x0088
                           000089   179 _IE0	=	0x0089
                           00008A   180 _IT1	=	0x008a
                           00008B   181 _IE1	=	0x008b
                           00008C   182 _TR0	=	0x008c
                           00008D   183 _TF0	=	0x008d
                           00008E   184 _TR1	=	0x008e
                           00008F   185 _TF1	=	0x008f
                           000090   186 _P1_0	=	0x0090
                           000091   187 _P1_1	=	0x0091
                           000092   188 _P1_2	=	0x0092
                           000093   189 _P1_3	=	0x0093
                           000094   190 _P1_4	=	0x0094
                           000095   191 _P1_5	=	0x0095
                           000096   192 _P1_6	=	0x0096
                           000097   193 _P1_7	=	0x0097
                           000098   194 _RI	=	0x0098
                           000099   195 _TI	=	0x0099
                           00009A   196 _RB8	=	0x009a
                           00009B   197 _TB8	=	0x009b
                           00009C   198 _REN	=	0x009c
                           00009D   199 _SM2	=	0x009d
                           00009E   200 _SM1	=	0x009e
                           00009F   201 _SM0	=	0x009f
                           0000A0   202 _P2_0	=	0x00a0
                           0000A1   203 _P2_1	=	0x00a1
                           0000A2   204 _P2_2	=	0x00a2
                           0000A3   205 _P2_3	=	0x00a3
                           0000A4   206 _P2_4	=	0x00a4
                           0000A5   207 _P2_5	=	0x00a5
                           0000A6   208 _P2_6	=	0x00a6
                           0000A7   209 _P2_7	=	0x00a7
                           0000A8   210 _EX0	=	0x00a8
                           0000A9   211 _ET0	=	0x00a9
                           0000AA   212 _EX1	=	0x00aa
                           0000AB   213 _ET1	=	0x00ab
                           0000AC   214 _ES	=	0x00ac
                           0000AF   215 _EA	=	0x00af
                           0000B0   216 _P3_0	=	0x00b0
                           0000B1   217 _P3_1	=	0x00b1
                           0000B2   218 _P3_2	=	0x00b2
                           0000B3   219 _P3_3	=	0x00b3
                           0000B4   220 _P3_4	=	0x00b4
                           0000B5   221 _P3_5	=	0x00b5
                           0000B6   222 _P3_6	=	0x00b6
                           0000B7   223 _P3_7	=	0x00b7
                           0000B0   224 _RXD	=	0x00b0
                           0000B1   225 _TXD	=	0x00b1
                           0000B2   226 _INT0	=	0x00b2
                           0000B3   227 _INT1	=	0x00b3
                           0000B4   228 _T0	=	0x00b4
                           0000B5   229 _T1	=	0x00b5
                           0000B6   230 _WR	=	0x00b6
                           0000B7   231 _RD	=	0x00b7
                           0000B8   232 _PX0	=	0x00b8
                           0000B9   233 _PT0	=	0x00b9
                           0000BA   234 _PX1	=	0x00ba
                           0000BB   235 _PT1	=	0x00bb
                           0000BC   236 _PS	=	0x00bc
                           0000D0   237 _P	=	0x00d0
                           0000D1   238 _F1	=	0x00d1
                           0000D2   239 _OV	=	0x00d2
                           0000D3   240 _RS0	=	0x00d3
                           0000D4   241 _RS1	=	0x00d4
                           0000D5   242 _F0	=	0x00d5
                           0000D6   243 _AC	=	0x00d6
                           0000D7   244 _CY	=	0x00d7
                           0000AD   245 _ET2	=	0x00ad
                           0000BD   246 _PT2	=	0x00bd
                           0000C8   247 _T2CON_0	=	0x00c8
                           0000C9   248 _T2CON_1	=	0x00c9
                           0000CA   249 _T2CON_2	=	0x00ca
                           0000CB   250 _T2CON_3	=	0x00cb
                           0000CC   251 _T2CON_4	=	0x00cc
                           0000CD   252 _T2CON_5	=	0x00cd
                           0000CE   253 _T2CON_6	=	0x00ce
                           0000CF   254 _T2CON_7	=	0x00cf
                           0000C8   255 _CP_RL2	=	0x00c8
                           0000C9   256 _C_T2	=	0x00c9
                           0000CA   257 _TR2	=	0x00ca
                           0000CB   258 _EXEN2	=	0x00cb
                           0000CC   259 _TCLK	=	0x00cc
                           0000CD   260 _RCLK	=	0x00cd
                           0000CE   261 _EXF2	=	0x00ce
                           0000CF   262 _TF2	=	0x00cf
                                    263 ;--------------------------------------------------------
                                    264 ; overlayable register banks
                                    265 ;--------------------------------------------------------
                                    266 	.area REG_BANK_0	(REL,OVR,DATA)
      000000                        267 	.ds 8
                                    268 ;--------------------------------------------------------
                                    269 ; internal ram data
                                    270 ;--------------------------------------------------------
                                    271 	.area DSEG    (DATA)
      000008                        272 _mode::
      000008                        273 	.ds 1
                                    274 ;--------------------------------------------------------
                                    275 ; overlayable items in internal ram 
                                    276 ;--------------------------------------------------------
                                    277 	.area	OSEG    (OVR,DATA)
                                    278 ;--------------------------------------------------------
                                    279 ; Stack segment in internal ram 
                                    280 ;--------------------------------------------------------
                                    281 	.area	SSEG
      000009                        282 __start__stack:
      000009                        283 	.ds	1
                                    284 
                                    285 ;--------------------------------------------------------
                                    286 ; indirectly addressable internal ram data
                                    287 ;--------------------------------------------------------
                                    288 	.area ISEG    (DATA)
                                    289 ;--------------------------------------------------------
                                    290 ; absolute internal ram data
                                    291 ;--------------------------------------------------------
                                    292 	.area IABS    (ABS,DATA)
                                    293 	.area IABS    (ABS,DATA)
                                    294 ;--------------------------------------------------------
                                    295 ; bit data
                                    296 ;--------------------------------------------------------
                                    297 	.area BSEG    (BIT)
                                    298 ;--------------------------------------------------------
                                    299 ; paged external ram data
                                    300 ;--------------------------------------------------------
                                    301 	.area PSEG    (PAG,XDATA)
                                    302 ;--------------------------------------------------------
                                    303 ; external ram data
                                    304 ;--------------------------------------------------------
                                    305 	.area XSEG    (XDATA)
                                    306 ;--------------------------------------------------------
                                    307 ; absolute external ram data
                                    308 ;--------------------------------------------------------
                                    309 	.area XABS    (ABS,XDATA)
                                    310 ;--------------------------------------------------------
                                    311 ; external initialized ram data
                                    312 ;--------------------------------------------------------
                                    313 	.area XISEG   (XDATA)
                                    314 	.area HOME    (CODE)
                                    315 	.area GSINIT0 (CODE)
                                    316 	.area GSINIT1 (CODE)
                                    317 	.area GSINIT2 (CODE)
                                    318 	.area GSINIT3 (CODE)
                                    319 	.area GSINIT4 (CODE)
                                    320 	.area GSINIT5 (CODE)
                                    321 	.area GSINIT  (CODE)
                                    322 	.area GSFINAL (CODE)
                                    323 	.area CSEG    (CODE)
                                    324 ;--------------------------------------------------------
                                    325 ; interrupt vector 
                                    326 ;--------------------------------------------------------
                                    327 	.area HOME    (CODE)
      000000                        328 __interrupt_vect:
      000000 02 00 06         [24]  329 	ljmp	__sdcc_gsinit_startup
                                    330 ;--------------------------------------------------------
                                    331 ; global & static initialisations
                                    332 ;--------------------------------------------------------
                                    333 	.area HOME    (CODE)
                                    334 	.area GSINIT  (CODE)
                                    335 	.area GSFINAL (CODE)
                                    336 	.area GSINIT  (CODE)
                                    337 	.globl __sdcc_gsinit_startup
                                    338 	.globl __sdcc_program_startup
                                    339 	.globl __start__stack
                                    340 	.globl __mcs51_genXINIT
                                    341 	.globl __mcs51_genXRAMCLEAR
                                    342 	.globl __mcs51_genRAMCLEAR
                                    343 ;	dualPatterns_SDCC.c:7: unsigned char mode = 0; 
      00005F 75 08 00         [24]  344 	mov	_mode,#0x00
                                    345 	.area GSFINAL (CODE)
      000062 02 00 03         [24]  346 	ljmp	__sdcc_program_startup
                                    347 ;--------------------------------------------------------
                                    348 ; Home
                                    349 ;--------------------------------------------------------
                                    350 	.area HOME    (CODE)
                                    351 	.area HOME    (CODE)
      000003                        352 __sdcc_program_startup:
      000003 02 00 65         [24]  353 	ljmp	_main
                                    354 ;	return from main will return to caller
                                    355 ;--------------------------------------------------------
                                    356 ; code
                                    357 ;--------------------------------------------------------
                                    358 	.area CSEG    (CODE)
                                    359 ;------------------------------------------------------------
                                    360 ;Allocation info for local variables in function 'main'
                                    361 ;------------------------------------------------------------
                                    362 ;i                         Allocated to registers r7 
                                    363 ;------------------------------------------------------------
                                    364 ;	dualPatterns_SDCC.c:13: void main()
                                    365 ;	-----------------------------------------
                                    366 ;	 function main
                                    367 ;	-----------------------------------------
      000065                        368 _main:
                           000007   369 	ar7 = 0x07
                           000006   370 	ar6 = 0x06
                           000005   371 	ar5 = 0x05
                           000004   372 	ar4 = 0x04
                           000003   373 	ar3 = 0x03
                           000002   374 	ar2 = 0x02
                           000001   375 	ar1 = 0x01
                           000000   376 	ar0 = 0x00
                                    377 ;	dualPatterns_SDCC.c:16: BUTTON = 1; // Init input
                                    378 ;	assignBit
      000065 D2 B2            [12]  379 	setb	_P3_2
                                    380 ;	dualPatterns_SDCC.c:18: while(1)
      000067                        381 00121$:
                                    382 ;	dualPatterns_SDCC.c:20: switch(mode)
      000067 E4               [12]  383 	clr	a
      000068 B5 08 02         [24]  384 	cjne	a,_mode,00211$
      00006B 80 07            [24]  385 	sjmp	00139$
      00006D                        386 00211$:
      00006D 74 01            [12]  387 	mov	a,#0x01
                                    388 ;	dualPatterns_SDCC.c:24: for(i = 0; i < 8; i++) {
      00006F B5 08 F5         [24]  389 	cjne	a,_mode,00121$
      000072 80 50            [24]  390 	sjmp	00110$
      000074                        391 00139$:
      000074 7F 00            [12]  392 	mov	r7,#0x00
      000076                        393 00123$:
                                    394 ;	dualPatterns_SDCC.c:25: P1 = (0x01 << i); 
      000076 8F 06            [24]  395 	mov	ar6,r7
      000078 8E F0            [24]  396 	mov	b,r6
      00007A 05 F0            [12]  397 	inc	b
      00007C 74 01            [12]  398 	mov	a,#0x01
      00007E 80 02            [24]  399 	sjmp	00215$
      000080                        400 00213$:
      000080 25 E0            [12]  401 	add	a,acc
      000082                        402 00215$:
      000082 D5 F0 FB         [24]  403 	djnz	b,00213$
      000085 F5 90            [12]  404 	mov	_P1,a
                                    405 ;	dualPatterns_SDCC.c:26: delay_short();
      000087 C0 07            [24]  406 	push	ar7
      000089 12 01 46         [24]  407 	lcall	_delay_short
                                    408 ;	dualPatterns_SDCC.c:27: if(check_button()) break;
      00008C 12 01 27         [24]  409 	lcall	_check_button
      00008F E5 82            [12]  410 	mov	a,dpl
      000091 D0 07            [24]  411 	pop	ar7
      000093 70 06            [24]  412 	jnz	00104$
                                    413 ;	dualPatterns_SDCC.c:24: for(i = 0; i < 8; i++) {
      000095 0F               [12]  414 	inc	r7
      000096 BF 08 00         [24]  415 	cjne	r7,#0x08,00217$
      000099                        416 00217$:
      000099 40 DB            [24]  417 	jc	00123$
      00009B                        418 00104$:
                                    419 ;	dualPatterns_SDCC.c:29: if(mode != 0) break; 
      00009B E5 08            [12]  420 	mov	a,_mode
      00009D 70 C8            [24]  421 	jnz	00121$
                                    422 ;	dualPatterns_SDCC.c:31: for(i = 6; i > 0; i--) {
      00009F 7F 06            [12]  423 	mov	r7,#0x06
      0000A1                        424 00125$:
                                    425 ;	dualPatterns_SDCC.c:32: P1 = (0x01 << i);
      0000A1 8F 06            [24]  426 	mov	ar6,r7
      0000A3 8E F0            [24]  427 	mov	b,r6
      0000A5 05 F0            [12]  428 	inc	b
      0000A7 74 01            [12]  429 	mov	a,#0x01
      0000A9 80 02            [24]  430 	sjmp	00222$
      0000AB                        431 00220$:
      0000AB 25 E0            [12]  432 	add	a,acc
      0000AD                        433 00222$:
      0000AD D5 F0 FB         [24]  434 	djnz	b,00220$
      0000B0 F5 90            [12]  435 	mov	_P1,a
                                    436 ;	dualPatterns_SDCC.c:33: delay_short();
      0000B2 C0 07            [24]  437 	push	ar7
      0000B4 12 01 46         [24]  438 	lcall	_delay_short
                                    439 ;	dualPatterns_SDCC.c:34: if(check_button()) break;
      0000B7 12 01 27         [24]  440 	lcall	_check_button
      0000BA E5 82            [12]  441 	mov	a,dpl
      0000BC D0 07            [24]  442 	pop	ar7
      0000BE 70 A7            [24]  443 	jnz	00121$
                                    444 ;	dualPatterns_SDCC.c:31: for(i = 6; i > 0; i--) {
      0000C0 DF DF            [24]  445 	djnz	r7,00125$
                                    446 ;	dualPatterns_SDCC.c:36: break;
                                    447 ;	dualPatterns_SDCC.c:39: case 1:
      0000C2 80 A3            [24]  448 	sjmp	00121$
      0000C4                        449 00110$:
                                    450 ;	dualPatterns_SDCC.c:40: for(i = 0; i < 8; i+=2) {
      0000C4 7F 00            [12]  451 	mov	r7,#0x00
      0000C6                        452 00127$:
                                    453 ;	dualPatterns_SDCC.c:41: P1 = (0x01 << i);
      0000C6 8F 06            [24]  454 	mov	ar6,r7
      0000C8 8E F0            [24]  455 	mov	b,r6
      0000CA 05 F0            [12]  456 	inc	b
      0000CC 74 01            [12]  457 	mov	a,#0x01
      0000CE 80 02            [24]  458 	sjmp	00227$
      0000D0                        459 00225$:
      0000D0 25 E0            [12]  460 	add	a,acc
      0000D2                        461 00227$:
      0000D2 D5 F0 FB         [24]  462 	djnz	b,00225$
      0000D5 F5 90            [12]  463 	mov	_P1,a
                                    464 ;	dualPatterns_SDCC.c:42: delay_short();
      0000D7 C0 06            [24]  465 	push	ar6
      0000D9 12 01 46         [24]  466 	lcall	_delay_short
                                    467 ;	dualPatterns_SDCC.c:43: if(check_button()) break;
      0000DC 12 01 27         [24]  468 	lcall	_check_button
      0000DF E5 82            [12]  469 	mov	a,dpl
      0000E1 D0 06            [24]  470 	pop	ar6
      0000E3 70 09            [24]  471 	jnz	00113$
                                    472 ;	dualPatterns_SDCC.c:40: for(i = 0; i < 8; i+=2) {
      0000E5 74 02            [12]  473 	mov	a,#0x02
      0000E7 2E               [12]  474 	add	a,r6
      0000E8 FF               [12]  475 	mov	r7,a
      0000E9 BF 08 00         [24]  476 	cjne	r7,#0x08,00229$
      0000EC                        477 00229$:
      0000EC 40 D8            [24]  478 	jc	00127$
      0000EE                        479 00113$:
                                    480 ;	dualPatterns_SDCC.c:45: if(mode != 1) break;
      0000EE 74 01            [12]  481 	mov	a,#0x01
      0000F0 B5 08 02         [24]  482 	cjne	a,_mode,00231$
      0000F3 80 03            [24]  483 	sjmp	00232$
      0000F5                        484 00231$:
      0000F5 02 00 67         [24]  485 	ljmp	00121$
      0000F8                        486 00232$:
                                    487 ;	dualPatterns_SDCC.c:47: for(i = 7; i > 1; i-=2) {
      0000F8 7F 07            [12]  488 	mov	r7,#0x07
      0000FA                        489 00129$:
                                    490 ;	dualPatterns_SDCC.c:48: P1 = (0x01 << i);
      0000FA 8F 06            [24]  491 	mov	ar6,r7
      0000FC 8E F0            [24]  492 	mov	b,r6
      0000FE 05 F0            [12]  493 	inc	b
      000100 74 01            [12]  494 	mov	a,#0x01
      000102 80 02            [24]  495 	sjmp	00235$
      000104                        496 00233$:
      000104 25 E0            [12]  497 	add	a,acc
      000106                        498 00235$:
      000106 D5 F0 FB         [24]  499 	djnz	b,00233$
      000109 F5 90            [12]  500 	mov	_P1,a
                                    501 ;	dualPatterns_SDCC.c:49: delay_short();
      00010B C0 06            [24]  502 	push	ar6
      00010D 12 01 46         [24]  503 	lcall	_delay_short
                                    504 ;	dualPatterns_SDCC.c:50: if(check_button()) break;
      000110 12 01 27         [24]  505 	lcall	_check_button
      000113 E5 82            [12]  506 	mov	a,dpl
      000115 D0 06            [24]  507 	pop	ar6
      000117 60 03            [24]  508 	jz	00236$
      000119 02 00 67         [24]  509 	ljmp	00121$
      00011C                        510 00236$:
                                    511 ;	dualPatterns_SDCC.c:47: for(i = 7; i > 1; i-=2) {
      00011C EE               [12]  512 	mov	a,r6
      00011D 24 FE            [12]  513 	add	a,#0xfe
      00011F FF               [12]  514 	mov  r7,a
      000120 24 FE            [12]  515 	add	a,#0xff - 0x01
      000122 40 D6            [24]  516 	jc	00129$
                                    517 ;	dualPatterns_SDCC.c:53: }
                                    518 ;	dualPatterns_SDCC.c:55: }
      000124 02 00 67         [24]  519 	ljmp	00121$
                                    520 ;------------------------------------------------------------
                                    521 ;Allocation info for local variables in function 'check_button'
                                    522 ;------------------------------------------------------------
                                    523 ;	dualPatterns_SDCC.c:57: unsigned char check_button(void)
                                    524 ;	-----------------------------------------
                                    525 ;	 function check_button
                                    526 ;	-----------------------------------------
      000127                        527 _check_button:
                                    528 ;	dualPatterns_SDCC.c:59: if(BUTTON == 0) 
      000127 20 B2 18         [24]  529 	jb	_P3_2,00109$
                                    530 ;	dualPatterns_SDCC.c:61: delay_short(); 
      00012A 12 01 46         [24]  531 	lcall	_delay_short
                                    532 ;	dualPatterns_SDCC.c:62: if(BUTTON == 0)
      00012D 20 B2 12         [24]  533 	jb	_P3_2,00109$
                                    534 ;	dualPatterns_SDCC.c:64: mode++;
      000130 05 08            [12]  535 	inc	_mode
                                    536 ;	dualPatterns_SDCC.c:65: if(mode >= TOTAL_MODES) mode = 0;
      000132 74 FE            [12]  537 	mov	a,#0x100 - 0x02
      000134 25 08            [12]  538 	add	a,_mode
      000136 50 03            [24]  539 	jnc	00103$
      000138 75 08 00         [24]  540 	mov	_mode,#0x00
                                    541 ;	dualPatterns_SDCC.c:66: while(BUTTON == 0); 
      00013B                        542 00103$:
      00013B 30 B2 FD         [24]  543 	jnb	_P3_2,00103$
                                    544 ;	dualPatterns_SDCC.c:67: return 1; 
      00013E 75 82 01         [24]  545 	mov	dpl,#0x01
      000141 22               [24]  546 	ret
      000142                        547 00109$:
                                    548 ;	dualPatterns_SDCC.c:70: return 0;
      000142 75 82 00         [24]  549 	mov	dpl,#0x00
                                    550 ;	dualPatterns_SDCC.c:71: }
      000145 22               [24]  551 	ret
                                    552 ;------------------------------------------------------------
                                    553 ;Allocation info for local variables in function 'delay_short'
                                    554 ;------------------------------------------------------------
                                    555 ;i                         Allocated to registers r6 r7 
                                    556 ;j                         Allocated to registers r4 r5 
                                    557 ;------------------------------------------------------------
                                    558 ;	dualPatterns_SDCC.c:73: void delay_short(void)
                                    559 ;	-----------------------------------------
                                    560 ;	 function delay_short
                                    561 ;	-----------------------------------------
      000146                        562 _delay_short:
                                    563 ;	dualPatterns_SDCC.c:76: for(i = 0; i < 100; i++) 
      000146 7E 00            [12]  564 	mov	r6,#0x00
      000148 7F 00            [12]  565 	mov	r7,#0x00
      00014A                        566 00106$:
                                    567 ;	dualPatterns_SDCC.c:77: for(j = 0; j < 300; j++);
      00014A 7C 2C            [12]  568 	mov	r4,#0x2c
      00014C 7D 01            [12]  569 	mov	r5,#0x01
      00014E                        570 00105$:
      00014E EC               [12]  571 	mov	a,r4
      00014F 24 FF            [12]  572 	add	a,#0xff
      000151 FA               [12]  573 	mov	r2,a
      000152 ED               [12]  574 	mov	a,r5
      000153 34 FF            [12]  575 	addc	a,#0xff
      000155 FB               [12]  576 	mov	r3,a
      000156 8A 04            [24]  577 	mov	ar4,r2
      000158 8B 05            [24]  578 	mov	ar5,r3
      00015A EA               [12]  579 	mov	a,r2
      00015B 4B               [12]  580 	orl	a,r3
      00015C 70 F0            [24]  581 	jnz	00105$
                                    582 ;	dualPatterns_SDCC.c:76: for(i = 0; i < 100; i++) 
      00015E 0E               [12]  583 	inc	r6
      00015F BE 00 01         [24]  584 	cjne	r6,#0x00,00124$
      000162 0F               [12]  585 	inc	r7
      000163                        586 00124$:
      000163 C3               [12]  587 	clr	c
      000164 EE               [12]  588 	mov	a,r6
      000165 94 64            [12]  589 	subb	a,#0x64
      000167 EF               [12]  590 	mov	a,r7
      000168 94 00            [12]  591 	subb	a,#0x00
      00016A 40 DE            [24]  592 	jc	00106$
                                    593 ;	dualPatterns_SDCC.c:78: }
      00016C 22               [24]  594 	ret
                                    595 	.area CSEG    (CODE)
                                    596 	.area CONST   (CODE)
                                    597 	.area XINIT   (CODE)
                                    598 	.area CABS    (ABS,CODE)
