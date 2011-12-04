/* Generated from lookup.scm by the CHICKEN compiler
   http://www.call-with-current-continuation.org
   2011-12-04 12:46
   Version 4.7.0 
   macosx-unix-gnu-x86-64 [ 64bit manyargs dload ptables ]
   compiled 2011-11-23 on beta.macosforge.org (Darwin)
   command line: lookup.scm -output-file lookup.c
   used units: library eval
*/

#include "chicken.h"

static C_PTABLE_ENTRY *create_ptable(void);
C_noret_decl(C_library_toplevel)
C_externimport void C_ccall C_library_toplevel(C_word c,C_word d,C_word k) C_noret;
C_noret_decl(C_eval_toplevel)
C_externimport void C_ccall C_eval_toplevel(C_word c,C_word d,C_word k) C_noret;

static C_TLS C_word lf[9];
static double C_possibly_force_alignment;
static C_char C_TLS li0[] C_aligned={C_lihdr(0,0,20),40,102,105,108,116,101,114,32,112,114,111,112,49,32,108,105,115,116,50,41,0,0,0,0};
static C_char C_TLS li1[] C_aligned={C_lihdr(0,0,34),40,109,97,116,99,104,45,114,101,99,111,114,100,32,107,101,121,55,32,118,97,108,117,101,56,32,114,101,99,111,114,100,57,41,0,0,0,0,0,0};
static C_char C_TLS li2[] C_aligned={C_lihdr(0,0,15),40,97,49,49,55,32,114,101,99,111,114,100,49,57,41,0};
static C_char C_TLS li3[] C_aligned={C_lihdr(0,0,33),40,107,101,121,102,105,108,116,32,107,101,121,49,54,32,118,97,108,117,101,49,55,32,114,101,99,108,105,115,116,49,56,41,0,0,0,0,0,0,0};
static C_char C_TLS li4[] C_aligned={C_lihdr(0,0,35),40,112,114,111,99,101,115,115,45,112,111,114,116,32,112,111,114,116,50,49,32,107,101,121,50,50,32,118,97,108,117,101,50,51,41,0,0,0,0,0};
static C_char C_TLS li5[] C_aligned={C_lihdr(0,0,10),40,97,49,53,49,32,120,50,54,41,0,0,0,0,0,0};
static C_char C_TLS li6[] C_aligned={C_lihdr(0,0,13),40,109,97,105,110,32,97,114,103,115,50,53,41,0,0,0};
static C_char C_TLS li7[] C_aligned={C_lihdr(0,0,10),40,116,111,112,108,101,118,101,108,41,0,0,0,0,0,0};


C_noret_decl(C_toplevel)
C_externexport void C_ccall C_toplevel(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_40)
static void C_ccall f_40(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_43)
static void C_ccall f_43(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_170)
static void C_ccall f_170(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_167)
static void C_ccall f_167(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_138)
static void C_ccall f_138(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_152)
static void C_ccall f_152(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_146)
static void C_ccall f_146(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_124)
static void C_ccall f_124(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_136)
static void C_ccall f_136(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_132)
static void C_ccall f_132(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_112)
static void C_ccall f_112(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_118)
static void C_ccall f_118(C_word c,C_word t0,C_word t1,C_word t2) C_noret;
C_noret_decl(f_86)
static void C_ccall f_86(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4) C_noret;
C_noret_decl(f_96)
static void C_fcall f_96(C_word t0,C_word t1) C_noret;
C_noret_decl(f_45)
static void C_ccall f_45(C_word c,C_word t0,C_word t1,C_word t2,C_word t3) C_noret;
C_noret_decl(f_58)
static void C_ccall f_58(C_word c,C_word t0,C_word t1) C_noret;
C_noret_decl(f_69)
static void C_ccall f_69(C_word c,C_word t0,C_word t1) C_noret;

C_noret_decl(trf_96)
static void C_fcall trf_96(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall trf_96(void *dummy){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
f_96(t0,t1);}

C_noret_decl(tr4)
static void C_fcall tr4(C_proc4 k) C_regparm C_noret;
C_regparm static void C_fcall tr4(C_proc4 k){
C_word t3=C_pick(0);
C_word t2=C_pick(1);
C_word t1=C_pick(2);
C_word t0=C_pick(3);
C_adjust_stack(-4);
(k)(4,t0,t1,t2,t3);}

C_noret_decl(tr5)
static void C_fcall tr5(C_proc5 k) C_regparm C_noret;
C_regparm static void C_fcall tr5(C_proc5 k){
C_word t4=C_pick(0);
C_word t3=C_pick(1);
C_word t2=C_pick(2);
C_word t1=C_pick(3);
C_word t0=C_pick(4);
C_adjust_stack(-5);
(k)(5,t0,t1,t2,t3,t4);}

C_noret_decl(tr3)
static void C_fcall tr3(C_proc3 k) C_regparm C_noret;
C_regparm static void C_fcall tr3(C_proc3 k){
C_word t2=C_pick(0);
C_word t1=C_pick(1);
C_word t0=C_pick(2);
C_adjust_stack(-3);
(k)(3,t0,t1,t2);}

C_noret_decl(tr2)
static void C_fcall tr2(C_proc2 k) C_regparm C_noret;
C_regparm static void C_fcall tr2(C_proc2 k){
C_word t1=C_pick(0);
C_word t0=C_pick(1);
C_adjust_stack(-2);
(k)(2,t0,t1);}

/* toplevel */
static C_TLS int toplevel_initialized=0;
C_main_entry_point
C_noret_decl(toplevel_trampoline)
static void C_fcall toplevel_trampoline(void *dummy) C_regparm C_noret;
C_regparm static void C_fcall toplevel_trampoline(void *dummy){
C_toplevel(2,C_SCHEME_UNDEFINED,C_restore);}

void C_ccall C_toplevel(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word *a;
if(toplevel_initialized) C_kontinue(t1,C_SCHEME_UNDEFINED);
else C_toplevel_entry(C_text("toplevel"));
C_resize_stack(262144);
C_check_nursery_minimum(3);
if(!C_demand(3)){
C_save(t1);
C_reclaim((void*)toplevel_trampoline,NULL);}
toplevel_initialized=1;
if(!C_demand_2(90)){
C_save(t1);
C_rereclaim2(90*sizeof(C_word), 1);
t1=C_restore;}
a=C_alloc(3);
C_initialize_lf(lf,9);
lf[0]=C_h_intern(&lf[0],6,"filter");
lf[1]=C_h_intern(&lf[1],12,"match-record");
lf[2]=C_h_intern(&lf[2],7,"keyfilt");
lf[3]=C_h_intern(&lf[3],12,"process-port");
lf[4]=C_h_intern(&lf[4],4,"read");
lf[5]=C_h_intern(&lf[5],4,"main");
lf[6]=C_h_intern(&lf[6],7,"display");
lf[7]=C_h_intern(&lf[7],21,"call-with-intput-file");
lf[8]=C_h_intern(&lf[8],25,"\003sysimplicit-exit-handler");
C_register_lf2(lf,9,create_ptable());
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_40,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
C_library_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k38 */
static void C_ccall f_40(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_40,2,t0,t1);}
t2=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_43,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
C_eval_toplevel(2,C_SCHEME_UNDEFINED,t2);}

/* k41 in k38 */
static void C_ccall f_43(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[21],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_43,2,t0,t1);}
t2=C_mutate((C_word*)lf[0]+1 /* (set! filter ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_45,a[2]=((C_word)li0),tmp=(C_word)a,a+=3,tmp));
t3=C_mutate((C_word*)lf[1]+1 /* (set! match-record ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_86,a[2]=((C_word)li1),tmp=(C_word)a,a+=3,tmp));
t4=C_mutate((C_word*)lf[2]+1 /* (set! keyfilt ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_112,a[2]=((C_word)li3),tmp=(C_word)a,a+=3,tmp));
t5=C_mutate((C_word*)lf[3]+1 /* (set! process-port ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_124,a[2]=((C_word)li4),tmp=(C_word)a,a+=3,tmp));
t6=C_mutate((C_word*)lf[5]+1 /* (set! main ...) */,(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_138,a[2]=((C_word)li6),tmp=(C_word)a,a+=3,tmp));
t7=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_167,a[2]=((C_word*)t0)[2],tmp=(C_word)a,a+=3,tmp);
t8=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_170,a[2]=t7,tmp=(C_word)a,a+=3,tmp);
C_trace("##sys#implicit-exit-handler");
((C_proc2)C_fast_retrieve_symbol_proc(lf[8]))(2,*((C_word*)lf[8]+1),t8);}

/* k168 in k41 in k38 */
static void C_ccall f_170(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=t1;
((C_proc2)C_fast_retrieve_proc(t2))(2,t2,((C_word*)t0)[2]);}

/* k165 in k41 in k38 */
static void C_ccall f_167(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_SCHEME_UNDEFINED);}

/* main in k41 in k38 */
static void C_ccall f_138(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[7],*a=ab;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_138,3,t0,t1,t2);}
t3=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_146,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t4=C_i_car(t2);
t5=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_152,a[2]=t2,a[3]=((C_word)li5),tmp=(C_word)a,a+=4,tmp);
C_trace("lookup.scm:15: call-with-intput-file");
((C_proc4)C_fast_retrieve_symbol_proc(lf[7]))(4,*((C_word*)lf[7]+1),t3,t4,t5);}

/* a151 in main in k41 in k38 */
static void C_ccall f_152(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_152,3,t0,t1,t2);}
t3=C_i_cadr(((C_word*)t0)[2]);
t4=C_i_caddr(((C_word*)t0)[2]);
C_trace("lookup.scm:16: process-port");
((C_proc5)C_fast_retrieve_symbol_proc(lf[3]))(5,*((C_word*)lf[3]+1),t1,t2,t3,t4);}

/* k144 in main in k41 in k38 */
static void C_ccall f_146(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("lookup.scm:15: display");
((C_proc3)C_fast_retrieve_proc(*((C_word*)lf[6]+1)))(3,*((C_word*)lf[6]+1),((C_word*)t0)[2],t1);}

/* process-port in k41 in k38 */
static void C_ccall f_124(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word ab[8],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_124,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_132,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t6=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_136,a[2]=t4,a[3]=t5,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
C_trace("lookup.scm:13: read");
((C_proc3)C_fast_retrieve_proc(*((C_word*)lf[4]+1)))(3,*((C_word*)lf[4]+1),t6,t2);}

/* k134 in process-port in k41 in k38 */
static void C_ccall f_136(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("lookup.scm:13: key");
t2=((C_word*)t0)[4];
((C_proc4)C_fast_retrieve_proc(t2))(4,t2,((C_word*)t0)[3],((C_word*)t0)[2],t1);}

/* k130 in process-port in k41 in k38 */
static void C_ccall f_132(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
C_trace("lookup.scm:13: keyfilt");
((C_proc3)C_fast_retrieve_symbol_proc(lf[2]))(3,*((C_word*)lf[2]+1),((C_word*)t0)[2],t1);}

/* keyfilt in k41 in k38 */
static void C_ccall f_112(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_112,5,t0,t1,t2,t3,t4);}
t5=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_118,a[2]=t3,a[3]=t2,a[4]=((C_word)li2),tmp=(C_word)a,a+=5,tmp);
C_trace("lookup.scm:10: filter");
((C_proc4)C_fast_retrieve_symbol_proc(lf[0]))(4,*((C_word*)lf[0]+1),t1,t5,t4);}

/* a117 in keyfilt in k41 in k38 */
static void C_ccall f_118(C_word c,C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word *a;
if(c!=3) C_bad_argc_2(c,3,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr3,(void*)f_118,3,t0,t1,t2);}
C_trace("lookup.scm:10: match-record");
((C_proc5)C_fast_retrieve_symbol_proc(lf[1]))(5,*((C_word*)lf[1]+1),t1,((C_word*)t0)[3],((C_word*)t0)[2],t2);}

/* match-record in k41 in k38 */
static void C_ccall f_86(C_word c,C_word t0,C_word t1,C_word t2,C_word t3,C_word t4){
C_word tmp;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word ab[3],*a=ab;
if(c!=5) C_bad_argc_2(c,5,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr5,(void*)f_86,5,t0,t1,t2,t3,t4);}
t5=C_i_assoc(t2,t4);
t6=(*a=C_CLOSURE_TYPE|2,a[1]=(C_word)f_96,a[2]=t1,tmp=(C_word)a,a+=3,tmp);
t7=C_i_car(t5);
if(C_truep(C_i_equalp(t7,t2))){
t8=C_i_cdr(t5);
t9=t6;
f_96(t9,C_i_equalp(t8,t3));}
else{
t8=t6;
f_96(t8,C_SCHEME_FALSE);}}

/* k94 in match-record in k41 in k38 */
static void C_fcall f_96(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word *a;
t2=((C_word*)t0)[2];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,(C_truep(t1)?C_SCHEME_TRUE:C_SCHEME_FALSE));}

/* filter in k41 in k38 */
static void C_ccall f_45(C_word c,C_word t0,C_word t1,C_word t2,C_word t3){
C_word tmp;
C_word t4;
C_word t5;
C_word t6;
C_word ab[5],*a=ab;
if(c!=4) C_bad_argc_2(c,4,t0);
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr4,(void*)f_45,4,t0,t1,t2,t3);}
if(C_truep(C_i_nullp(t3))){
t4=t1;
((C_proc2)(void*)(*((C_word*)t4+1)))(2,t4,C_SCHEME_END_OF_LIST);}
else{
t4=(*a=C_CLOSURE_TYPE|4,a[1]=(C_word)f_58,a[2]=t2,a[3]=t1,a[4]=t3,tmp=(C_word)a,a+=5,tmp);
t5=C_i_car(t3);
C_trace("lookup.scm:3: prop");
t6=t2;
((C_proc3)C_fast_retrieve_proc(t6))(3,t6,t4,t5);}}

/* k56 in filter in k41 in k38 */
static void C_ccall f_58(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word ab[4],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_58,2,t0,t1);}
if(C_truep(t1)){
t2=C_i_car(((C_word*)t0)[4]);
t3=(*a=C_CLOSURE_TYPE|3,a[1]=(C_word)f_69,a[2]=t2,a[3]=((C_word*)t0)[3],tmp=(C_word)a,a+=4,tmp);
t4=C_i_cdr(((C_word*)t0)[4]);
C_trace("lookup.scm:3: filter");
((C_proc4)C_fast_retrieve_symbol_proc(lf[0]))(4,*((C_word*)lf[0]+1),t3,((C_word*)t0)[2],t4);}
else{
t2=C_i_cdr(((C_word*)t0)[4]);
C_trace("lookup.scm:4: filter");
((C_proc4)C_fast_retrieve_symbol_proc(lf[0]))(4,*((C_word*)lf[0]+1),((C_word*)t0)[3],((C_word*)t0)[2],t2);}}

/* k67 in k56 in filter in k41 in k38 */
static void C_ccall f_69(C_word c,C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word ab[3],*a=ab;
C_check_for_interrupt;
if(!C_stack_probe(&a)){
C_save_and_reclaim((void*)tr2,(void*)f_69,2,t0,t1);}
t2=((C_word*)t0)[3];
((C_proc2)(void*)(*((C_word*)t2+1)))(2,t2,C_a_i_cons(&a,2,((C_word*)t0)[2],t1));}

#ifdef C_ENABLE_PTABLES
static C_PTABLE_ENTRY ptable[19] = {
{"toplevel:lookup_2escm",(void*)C_toplevel},
{"f_40:lookup_2escm",(void*)f_40},
{"f_43:lookup_2escm",(void*)f_43},
{"f_170:lookup_2escm",(void*)f_170},
{"f_167:lookup_2escm",(void*)f_167},
{"f_138:lookup_2escm",(void*)f_138},
{"f_152:lookup_2escm",(void*)f_152},
{"f_146:lookup_2escm",(void*)f_146},
{"f_124:lookup_2escm",(void*)f_124},
{"f_136:lookup_2escm",(void*)f_136},
{"f_132:lookup_2escm",(void*)f_132},
{"f_112:lookup_2escm",(void*)f_112},
{"f_118:lookup_2escm",(void*)f_118},
{"f_86:lookup_2escm",(void*)f_86},
{"f_96:lookup_2escm",(void*)f_96},
{"f_45:lookup_2escm",(void*)f_45},
{"f_58:lookup_2escm",(void*)f_58},
{"f_69:lookup_2escm",(void*)f_69},
{NULL,NULL}};
#endif

static C_PTABLE_ENTRY *create_ptable(void){
#ifdef C_ENABLE_PTABLES
return ptable;
#else
return NULL;
#endif
}
/* end of file */
