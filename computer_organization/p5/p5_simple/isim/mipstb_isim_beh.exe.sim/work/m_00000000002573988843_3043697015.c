/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/Tasks/Beihang University/HW/Beihang-University/computer_organization/p5/p5_simple/bw_ext.v";
static unsigned int ng1[] = {32U, 0U};
static int ng2[] = {0, 0};
static int ng3[] = {24, 0};
static int ng4[] = {1, 0};
static int ng5[] = {2, 0};
static int ng6[] = {3, 0};
static unsigned int ng7[] = {36U, 0U};
static unsigned int ng8[] = {0U, 0U};
static unsigned int ng9[] = {33U, 0U};
static int ng10[] = {16, 0};
static unsigned int ng11[] = {37U, 0U};



static void Always_33_0(char *t0)
{
    char t10[8];
    char t11[8];
    char t21[8];
    char t25[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    int t9;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t22;
    char *t23;
    char *t24;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;

LAB0:    t1 = (t0 + 3232U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 3552);
    *((int *)t2) = 1;
    t3 = (t0 + 3264);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(33, ng0);

LAB5:    xsi_set_current_line(34, ng0);
    t4 = (t0 + 1912U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t4, 6);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t2, 6);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t2, 6);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t2, 6);
    if (t6 == 1)
        goto LAB13;

LAB14:
LAB16:
LAB15:    xsi_set_current_line(87, ng0);
    t2 = (t0 + 1592U);
    t3 = *((char **)t2);
    t2 = (t0 + 2312);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 32);

LAB17:    goto LAB2;

LAB7:    xsi_set_current_line(35, ng0);

LAB18:    xsi_set_current_line(36, ng0);
    t7 = (t0 + 1752U);
    t8 = *((char **)t7);

LAB19:    t7 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t8, 2, t7, 32);
    if (t9 == 1)
        goto LAB20;

LAB21:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB22;

LAB23:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB24;

LAB25:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB26;

LAB27:
LAB28:    goto LAB17;

LAB9:    xsi_set_current_line(51, ng0);

LAB33:    xsi_set_current_line(52, ng0);
    t3 = (t0 + 1752U);
    t4 = *((char **)t3);

LAB34:    t3 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t4, 2, t3, 32);
    if (t9 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 32);
    if (t6 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 32);
    if (t6 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t4, 2, t2, 32);
    if (t6 == 1)
        goto LAB41;

LAB42:
LAB43:    goto LAB17;

LAB11:    xsi_set_current_line(67, ng0);

LAB48:    xsi_set_current_line(68, ng0);
    t3 = (t0 + 1752U);
    t7 = *((char **)t3);

LAB49:    t3 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t7, 2, t3, 32);
    if (t9 == 1)
        goto LAB50;

LAB51:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t7, 2, t2, 32);
    if (t6 == 1)
        goto LAB52;

LAB53:
LAB54:    goto LAB17;

LAB13:    xsi_set_current_line(77, ng0);

LAB57:    xsi_set_current_line(78, ng0);
    t3 = (t0 + 1752U);
    t12 = *((char **)t3);

LAB58:    t3 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t12, 2, t3, 32);
    if (t9 == 1)
        goto LAB59;

LAB60:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t12, 2, t2, 32);
    if (t6 == 1)
        goto LAB61;

LAB62:
LAB63:    goto LAB17;

LAB20:    xsi_set_current_line(37, ng0);

LAB29:    xsi_set_current_line(38, ng0);
    t12 = (t0 + 1592U);
    t13 = *((char **)t12);
    memset(t11, 0, 8);
    t12 = (t11 + 4);
    t14 = (t13 + 4);
    t15 = *((unsigned int *)t13);
    t16 = (t15 >> 0);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t14);
    t18 = (t17 >> 0);
    *((unsigned int *)t12) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t20 & 255U);
    t22 = ((char*)((ng3)));
    t23 = (t0 + 1592U);
    t24 = *((char **)t23);
    memset(t25, 0, 8);
    t23 = (t25 + 4);
    t26 = (t24 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (t27 >> 7);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t26);
    t31 = (t30 >> 7);
    t32 = (t31 & 1);
    *((unsigned int *)t23) = t32;
    xsi_vlog_mul_concat(t21, 24, 1, t22, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 24, t11, 8);
    t33 = (t0 + 2312);
    xsi_vlogvar_assign_value(t33, t10, 0, 0, 32);
    goto LAB28;

LAB22:    xsi_set_current_line(40, ng0);

LAB30:    xsi_set_current_line(41, ng0);
    t3 = (t0 + 1592U);
    t4 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t7 = (t4 + 4);
    t15 = *((unsigned int *)t4);
    t16 = (t15 >> 8);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t7);
    t18 = (t17 >> 8);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 1592U);
    t14 = *((char **)t13);
    memset(t25, 0, 8);
    t13 = (t25 + 4);
    t22 = (t14 + 4);
    t27 = *((unsigned int *)t14);
    t28 = (t27 >> 15);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t22);
    t31 = (t30 >> 15);
    t32 = (t31 & 1);
    *((unsigned int *)t13) = t32;
    xsi_vlog_mul_concat(t21, 24, 1, t12, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 24, t11, 8);
    t23 = (t0 + 2312);
    xsi_vlogvar_assign_value(t23, t10, 0, 0, 32);
    goto LAB28;

LAB24:    xsi_set_current_line(43, ng0);

LAB31:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 1592U);
    t4 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t7 = (t4 + 4);
    t15 = *((unsigned int *)t4);
    t16 = (t15 >> 16);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t7);
    t18 = (t17 >> 16);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 1592U);
    t14 = *((char **)t13);
    memset(t25, 0, 8);
    t13 = (t25 + 4);
    t22 = (t14 + 4);
    t27 = *((unsigned int *)t14);
    t28 = (t27 >> 23);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t22);
    t31 = (t30 >> 23);
    t32 = (t31 & 1);
    *((unsigned int *)t13) = t32;
    xsi_vlog_mul_concat(t21, 24, 1, t12, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 24, t11, 8);
    t23 = (t0 + 2312);
    xsi_vlogvar_assign_value(t23, t10, 0, 0, 32);
    goto LAB28;

LAB26:    xsi_set_current_line(46, ng0);

LAB32:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 1592U);
    t4 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t7 = (t4 + 4);
    t15 = *((unsigned int *)t4);
    t16 = (t15 >> 24);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t7);
    t18 = (t17 >> 24);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 1592U);
    t14 = *((char **)t13);
    memset(t25, 0, 8);
    t13 = (t25 + 4);
    t22 = (t14 + 4);
    t27 = *((unsigned int *)t14);
    t28 = (t27 >> 31);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t22);
    t31 = (t30 >> 31);
    t32 = (t31 & 1);
    *((unsigned int *)t13) = t32;
    xsi_vlog_mul_concat(t21, 24, 1, t12, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 24, t11, 8);
    t23 = (t0 + 2312);
    xsi_vlogvar_assign_value(t23, t10, 0, 0, 32);
    goto LAB28;

LAB35:    xsi_set_current_line(53, ng0);

LAB44:    xsi_set_current_line(54, ng0);
    t7 = (t0 + 1592U);
    t12 = *((char **)t7);
    memset(t11, 0, 8);
    t7 = (t11 + 4);
    t13 = (t12 + 4);
    t15 = *((unsigned int *)t12);
    t16 = (t15 >> 0);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t13);
    t18 = (t17 >> 0);
    *((unsigned int *)t7) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t20 & 255U);
    t14 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t14, 24, t11, 8);
    t22 = (t0 + 2312);
    xsi_vlogvar_assign_value(t22, t10, 0, 0, 32);
    goto LAB43;

LAB37:    xsi_set_current_line(56, ng0);

LAB45:    xsi_set_current_line(57, ng0);
    t3 = (t0 + 1592U);
    t7 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t12 = (t7 + 4);
    t15 = *((unsigned int *)t7);
    t16 = (t15 >> 8);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t12);
    t18 = (t17 >> 8);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t13 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t13, 24, t11, 8);
    t14 = (t0 + 2312);
    xsi_vlogvar_assign_value(t14, t10, 0, 0, 32);
    goto LAB43;

LAB39:    xsi_set_current_line(59, ng0);

LAB46:    xsi_set_current_line(60, ng0);
    t3 = (t0 + 1592U);
    t7 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t12 = (t7 + 4);
    t15 = *((unsigned int *)t7);
    t16 = (t15 >> 16);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t12);
    t18 = (t17 >> 16);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t13 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t13, 24, t11, 8);
    t14 = (t0 + 2312);
    xsi_vlogvar_assign_value(t14, t10, 0, 0, 32);
    goto LAB43;

LAB41:    xsi_set_current_line(62, ng0);

LAB47:    xsi_set_current_line(63, ng0);
    t3 = (t0 + 1592U);
    t7 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t12 = (t7 + 4);
    t15 = *((unsigned int *)t7);
    t16 = (t15 >> 24);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t12);
    t18 = (t17 >> 24);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 255U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 255U);
    t13 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t13, 24, t11, 8);
    t14 = (t0 + 2312);
    xsi_vlogvar_assign_value(t14, t10, 0, 0, 32);
    goto LAB43;

LAB50:    xsi_set_current_line(69, ng0);

LAB55:    xsi_set_current_line(70, ng0);
    t12 = (t0 + 1592U);
    t13 = *((char **)t12);
    memset(t11, 0, 8);
    t12 = (t11 + 4);
    t14 = (t13 + 4);
    t15 = *((unsigned int *)t13);
    t16 = (t15 >> 0);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t14);
    t18 = (t17 >> 0);
    *((unsigned int *)t12) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 65535U);
    t20 = *((unsigned int *)t12);
    *((unsigned int *)t12) = (t20 & 65535U);
    t22 = ((char*)((ng10)));
    t23 = (t0 + 1592U);
    t24 = *((char **)t23);
    memset(t25, 0, 8);
    t23 = (t25 + 4);
    t26 = (t24 + 4);
    t27 = *((unsigned int *)t24);
    t28 = (t27 >> 15);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t26);
    t31 = (t30 >> 15);
    t32 = (t31 & 1);
    *((unsigned int *)t23) = t32;
    xsi_vlog_mul_concat(t21, 16, 1, t22, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 16, t11, 16);
    t33 = (t0 + 2312);
    xsi_vlogvar_assign_value(t33, t10, 0, 0, 32);
    goto LAB54;

LAB52:    xsi_set_current_line(72, ng0);

LAB56:    xsi_set_current_line(73, ng0);
    t3 = (t0 + 1592U);
    t12 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t13 = (t12 + 4);
    t15 = *((unsigned int *)t12);
    t16 = (t15 >> 16);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t13);
    t18 = (t17 >> 16);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 65535U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 65535U);
    t14 = ((char*)((ng10)));
    t22 = (t0 + 1592U);
    t23 = *((char **)t22);
    memset(t25, 0, 8);
    t22 = (t25 + 4);
    t24 = (t23 + 4);
    t27 = *((unsigned int *)t23);
    t28 = (t27 >> 31);
    t29 = (t28 & 1);
    *((unsigned int *)t25) = t29;
    t30 = *((unsigned int *)t24);
    t31 = (t30 >> 31);
    t32 = (t31 & 1);
    *((unsigned int *)t22) = t32;
    xsi_vlog_mul_concat(t21, 16, 1, t14, 1U, t25, 1);
    xsi_vlogtype_concat(t10, 32, 32, 2U, t21, 16, t11, 16);
    t26 = (t0 + 2312);
    xsi_vlogvar_assign_value(t26, t10, 0, 0, 32);
    goto LAB54;

LAB59:    xsi_set_current_line(79, ng0);

LAB64:    xsi_set_current_line(80, ng0);
    t13 = (t0 + 1592U);
    t14 = *((char **)t13);
    memset(t11, 0, 8);
    t13 = (t11 + 4);
    t22 = (t14 + 4);
    t15 = *((unsigned int *)t14);
    t16 = (t15 >> 0);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t22);
    t18 = (t17 >> 0);
    *((unsigned int *)t13) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 65535U);
    t20 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t20 & 65535U);
    t23 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t23, 16, t11, 16);
    t24 = (t0 + 2312);
    xsi_vlogvar_assign_value(t24, t10, 0, 0, 32);
    goto LAB63;

LAB61:    xsi_set_current_line(82, ng0);

LAB65:    xsi_set_current_line(83, ng0);
    t3 = (t0 + 1592U);
    t13 = *((char **)t3);
    memset(t11, 0, 8);
    t3 = (t11 + 4);
    t14 = (t13 + 4);
    t15 = *((unsigned int *)t13);
    t16 = (t15 >> 16);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t14);
    t18 = (t17 >> 16);
    *((unsigned int *)t3) = t18;
    t19 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t19 & 65535U);
    t20 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t20 & 65535U);
    t22 = ((char*)((ng8)));
    xsi_vlogtype_concat(t10, 32, 32, 2U, t22, 16, t11, 16);
    t23 = (t0 + 2312);
    xsi_vlogvar_assign_value(t23, t10, 0, 0, 32);
    goto LAB63;

}


extern void work_m_00000000002573988843_3043697015_init()
{
	static char *pe[] = {(void *)Always_33_0};
	xsi_register_didat("work_m_00000000002573988843_3043697015", "isim/mipstb_isim_beh.exe.sim/work/m_00000000002573988843_3043697015.didat");
	xsi_register_executes(pe);
}
