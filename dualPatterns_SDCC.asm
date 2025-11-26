;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.0 #11528 (Linux)
;--------------------------------------------------------
	.module dualPatterns_SDCC
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _T2CON_7
	.globl _T2CON_6
	.globl _T2CON_5
	.globl _T2CON_4
	.globl _T2CON_3
	.globl _T2CON_2
	.globl _T2CON_1
	.globl _T2CON_0
	.globl _PT2
	.globl _ET2
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _F1
	.globl _P
	.globl _PS
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _RD
	.globl _WR
	.globl _T1
	.globl _T0
	.globl _INT1
	.globl _INT0
	.globl _TXD
	.globl _RXD
	.globl _P3_7
	.globl _P3_6
	.globl _P3_5
	.globl _P3_4
	.globl _P3_3
	.globl _P3_2
	.globl _P3_1
	.globl _P3_0
	.globl _EA
	.globl _ES
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _P2_7
	.globl _P2_6
	.globl _P2_5
	.globl _P2_4
	.globl _P2_3
	.globl _P2_2
	.globl _P2_1
	.globl _P2_0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _P1_7
	.globl _P1_6
	.globl _P1_5
	.globl _P1_4
	.globl _P1_3
	.globl _P1_2
	.globl _P1_1
	.globl _P1_0
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _P0_7
	.globl _P0_6
	.globl _P0_5
	.globl _P0_4
	.globl _P0_3
	.globl _P0_2
	.globl _P0_1
	.globl _P0_0
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2CON
	.globl _B
	.globl _ACC
	.globl _PSW
	.globl _IP
	.globl _P3
	.globl _IE
	.globl _P2
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _mode
	.globl _check_button
	.globl _delay_short
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_P2	=	0x00a0
_IE	=	0x00a8
_P3	=	0x00b0
_IP	=	0x00b8
_PSW	=	0x00d0
_ACC	=	0x00e0
_B	=	0x00f0
_T2CON	=	0x00c8
_RCAP2L	=	0x00ca
_RCAP2H	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (ABS,DATA)
	.org 0x0000
_P0_0	=	0x0080
_P0_1	=	0x0081
_P0_2	=	0x0082
_P0_3	=	0x0083
_P0_4	=	0x0084
_P0_5	=	0x0085
_P0_6	=	0x0086
_P0_7	=	0x0087
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_P1_0	=	0x0090
_P1_1	=	0x0091
_P1_2	=	0x0092
_P1_3	=	0x0093
_P1_4	=	0x0094
_P1_5	=	0x0095
_P1_6	=	0x0096
_P1_7	=	0x0097
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_P2_0	=	0x00a0
_P2_1	=	0x00a1
_P2_2	=	0x00a2
_P2_3	=	0x00a3
_P2_4	=	0x00a4
_P2_5	=	0x00a5
_P2_6	=	0x00a6
_P2_7	=	0x00a7
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES	=	0x00ac
_EA	=	0x00af
_P3_0	=	0x00b0
_P3_1	=	0x00b1
_P3_2	=	0x00b2
_P3_3	=	0x00b3
_P3_4	=	0x00b4
_P3_5	=	0x00b5
_P3_6	=	0x00b6
_P3_7	=	0x00b7
_RXD	=	0x00b0
_TXD	=	0x00b1
_INT0	=	0x00b2
_INT1	=	0x00b3
_T0	=	0x00b4
_T1	=	0x00b5
_WR	=	0x00b6
_RD	=	0x00b7
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS	=	0x00bc
_P	=	0x00d0
_F1	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_ET2	=	0x00ad
_PT2	=	0x00bd
_T2CON_0	=	0x00c8
_T2CON_1	=	0x00c9
_T2CON_2	=	0x00ca
_T2CON_3	=	0x00cb
_T2CON_4	=	0x00cc
_T2CON_5	=	0x00cd
_T2CON_6	=	0x00ce
_T2CON_7	=	0x00cf
_CP_RL2	=	0x00c8
_C_T2	=	0x00c9
_TR2	=	0x00ca
_EXEN2	=	0x00cb
_TCLK	=	0x00cc
_RCLK	=	0x00cd
_EXF2	=	0x00ce
_TF2	=	0x00cf
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_mode::
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genXINIT
	.globl __mcs51_genXRAMCLEAR
	.globl __mcs51_genRAMCLEAR
;	dualPatterns_SDCC.c:7: unsigned char mode = 0; 
	mov	_mode,#0x00
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
__sdcc_program_startup:
	ljmp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;i                         Allocated to registers r7 
;------------------------------------------------------------
;	dualPatterns_SDCC.c:13: void main()
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	ar7 = 0x07
	ar6 = 0x06
	ar5 = 0x05
	ar4 = 0x04
	ar3 = 0x03
	ar2 = 0x02
	ar1 = 0x01
	ar0 = 0x00
;	dualPatterns_SDCC.c:16: BUTTON = 1; // Init input
;	assignBit
	setb	_P3_2
;	dualPatterns_SDCC.c:18: while(1)
00121$:
;	dualPatterns_SDCC.c:20: switch(mode)
	clr	a
	cjne	a,_mode,00211$
	sjmp	00139$
00211$:
	mov	a,#0x01
;	dualPatterns_SDCC.c:24: for(i = 0; i < 8; i++) {
	cjne	a,_mode,00121$
	sjmp	00110$
00139$:
	mov	r7,#0x00
00123$:
;	dualPatterns_SDCC.c:25: P1 = (0x01 << i); 
	mov	ar6,r7
	mov	b,r6
	inc	b
	mov	a,#0x01
	sjmp	00215$
00213$:
	add	a,acc
00215$:
	djnz	b,00213$
	mov	_P1,a
;	dualPatterns_SDCC.c:26: delay_short();
	push	ar7
	lcall	_delay_short
;	dualPatterns_SDCC.c:27: if(check_button()) break;
	lcall	_check_button
	mov	a,dpl
	pop	ar7
	jnz	00104$
;	dualPatterns_SDCC.c:24: for(i = 0; i < 8; i++) {
	inc	r7
	cjne	r7,#0x08,00217$
00217$:
	jc	00123$
00104$:
;	dualPatterns_SDCC.c:29: if(mode != 0) break; 
	mov	a,_mode
	jnz	00121$
;	dualPatterns_SDCC.c:31: for(i = 6; i > 0; i--) {
	mov	r7,#0x06
00125$:
;	dualPatterns_SDCC.c:32: P1 = (0x01 << i);
	mov	ar6,r7
	mov	b,r6
	inc	b
	mov	a,#0x01
	sjmp	00222$
00220$:
	add	a,acc
00222$:
	djnz	b,00220$
	mov	_P1,a
;	dualPatterns_SDCC.c:33: delay_short();
	push	ar7
	lcall	_delay_short
;	dualPatterns_SDCC.c:34: if(check_button()) break;
	lcall	_check_button
	mov	a,dpl
	pop	ar7
	jnz	00121$
;	dualPatterns_SDCC.c:31: for(i = 6; i > 0; i--) {
	djnz	r7,00125$
;	dualPatterns_SDCC.c:36: break;
;	dualPatterns_SDCC.c:39: case 1:
	sjmp	00121$
00110$:
;	dualPatterns_SDCC.c:40: for(i = 0; i < 8; i+=2) {
	mov	r7,#0x00
00127$:
;	dualPatterns_SDCC.c:41: P1 = (0x01 << i);
	mov	ar6,r7
	mov	b,r6
	inc	b
	mov	a,#0x01
	sjmp	00227$
00225$:
	add	a,acc
00227$:
	djnz	b,00225$
	mov	_P1,a
;	dualPatterns_SDCC.c:42: delay_short();
	push	ar6
	lcall	_delay_short
;	dualPatterns_SDCC.c:43: if(check_button()) break;
	lcall	_check_button
	mov	a,dpl
	pop	ar6
	jnz	00113$
;	dualPatterns_SDCC.c:40: for(i = 0; i < 8; i+=2) {
	mov	a,#0x02
	add	a,r6
	mov	r7,a
	cjne	r7,#0x08,00229$
00229$:
	jc	00127$
00113$:
;	dualPatterns_SDCC.c:45: if(mode != 1) break;
	mov	a,#0x01
	cjne	a,_mode,00231$
	sjmp	00232$
00231$:
	ljmp	00121$
00232$:
;	dualPatterns_SDCC.c:47: for(i = 7; i > 1; i-=2) {
	mov	r7,#0x07
00129$:
;	dualPatterns_SDCC.c:48: P1 = (0x01 << i);
	mov	ar6,r7
	mov	b,r6
	inc	b
	mov	a,#0x01
	sjmp	00235$
00233$:
	add	a,acc
00235$:
	djnz	b,00233$
	mov	_P1,a
;	dualPatterns_SDCC.c:49: delay_short();
	push	ar6
	lcall	_delay_short
;	dualPatterns_SDCC.c:50: if(check_button()) break;
	lcall	_check_button
	mov	a,dpl
	pop	ar6
	jz	00236$
	ljmp	00121$
00236$:
;	dualPatterns_SDCC.c:47: for(i = 7; i > 1; i-=2) {
	mov	a,r6
	add	a,#0xfe
	mov  r7,a
	add	a,#0xff - 0x01
	jc	00129$
;	dualPatterns_SDCC.c:53: }
;	dualPatterns_SDCC.c:55: }
	ljmp	00121$
;------------------------------------------------------------
;Allocation info for local variables in function 'check_button'
;------------------------------------------------------------
;	dualPatterns_SDCC.c:57: unsigned char check_button(void)
;	-----------------------------------------
;	 function check_button
;	-----------------------------------------
_check_button:
;	dualPatterns_SDCC.c:59: if(BUTTON == 0) 
	jb	_P3_2,00109$
;	dualPatterns_SDCC.c:61: delay_short(); 
	lcall	_delay_short
;	dualPatterns_SDCC.c:62: if(BUTTON == 0)
	jb	_P3_2,00109$
;	dualPatterns_SDCC.c:64: mode++;
	inc	_mode
;	dualPatterns_SDCC.c:65: if(mode >= TOTAL_MODES) mode = 0;
	mov	a,#0x100 - 0x02
	add	a,_mode
	jnc	00103$
	mov	_mode,#0x00
;	dualPatterns_SDCC.c:66: while(BUTTON == 0); 
00103$:
	jnb	_P3_2,00103$
;	dualPatterns_SDCC.c:67: return 1; 
	mov	dpl,#0x01
	ret
00109$:
;	dualPatterns_SDCC.c:70: return 0;
	mov	dpl,#0x00
;	dualPatterns_SDCC.c:71: }
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'delay_short'
;------------------------------------------------------------
;i                         Allocated to registers r6 r7 
;j                         Allocated to registers r4 r5 
;------------------------------------------------------------
;	dualPatterns_SDCC.c:73: void delay_short(void)
;	-----------------------------------------
;	 function delay_short
;	-----------------------------------------
_delay_short:
;	dualPatterns_SDCC.c:76: for(i = 0; i < 100; i++) 
	mov	r6,#0x00
	mov	r7,#0x00
00106$:
;	dualPatterns_SDCC.c:77: for(j = 0; j < 300; j++);
	mov	r4,#0x2c
	mov	r5,#0x01
00105$:
	mov	a,r4
	add	a,#0xff
	mov	r2,a
	mov	a,r5
	addc	a,#0xff
	mov	r3,a
	mov	ar4,r2
	mov	ar5,r3
	mov	a,r2
	orl	a,r3
	jnz	00105$
;	dualPatterns_SDCC.c:76: for(i = 0; i < 100; i++) 
	inc	r6
	cjne	r6,#0x00,00124$
	inc	r7
00124$:
	clr	c
	mov	a,r6
	subb	a,#0x64
	mov	a,r7
	subb	a,#0x00
	jc	00106$
;	dualPatterns_SDCC.c:78: }
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
