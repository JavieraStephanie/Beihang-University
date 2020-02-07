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
static const char *ng0 = "D:/Tasks/Beihang University/HW/Beihang-University/computer_organization/p5/p5_simple/dm.v";
static int ng1[] = {0, 0};
static int ng2[] = {1024, 0};
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0};
static int ng5[] = {7, 0};
static int ng6[] = {2, 0};
static int ng7[] = {15, 0};
static int ng8[] = {8, 0};
static int ng9[] = {4, 0};
static int ng10[] = {23, 0};
static int ng11[] = {16, 0};
static int ng12[] = {31, 0};
static int ng13[] = {24, 0};
static int ng14[] = {3, 0};
static int ng15[] = {9, 0};
static const char *ng16 = "%d@%h: *%h <= %h";



static void Initial_36_0(char *t0)
{
    char t5[8];
    char t14[8];
    char t15[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    unsigned int t26;
    int t27;
    char *t28;
    unsigned int t29;
    int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    int t34;
    int t35;

LAB0:    xsi_set_current_line(36, ng0);

LAB2:    xsi_set_current_line(37, ng0);
    xsi_set_current_line(37, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2888);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 2888);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng2)));
    memset(t5, 0, 8);
    xsi_vlog_signed_less(t5, 32, t3, 32, t4, 32);
    t6 = (t5 + 4);
    t7 = *((unsigned int *)t6);
    t8 = (~(t7));
    t9 = *((unsigned int *)t5);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB4;

LAB5:
LAB1:    return;
LAB4:    xsi_set_current_line(38, ng0);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 2728);
    t16 = (t0 + 2728);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 2888);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    xsi_vlog_generic_convert_array_indices(t14, t15, t18, t21, 2, 1, t24, 32, 1);
    t25 = (t14 + 4);
    t26 = *((unsigned int *)t25);
    t27 = (!(t26));
    t28 = (t15 + 4);
    t29 = *((unsigned int *)t28);
    t30 = (!(t29));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB6;

LAB7:    xsi_set_current_line(37, ng0);
    t1 = (t0 + 2888);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 2888);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB6:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB7;

}

static void Cont_41_1(char *t0)
{
    char t5[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;

LAB0:    t1 = (t0 + 4056U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(41, ng0);
    t2 = (t0 + 2728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 2728);
    t7 = (t6 + 72U);
    t8 = *((char **)t7);
    t9 = (t0 + 2728);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1688U);
    t13 = *((char **)t12);
    xsi_vlog_generic_get_array_select_value(t5, 32, t4, t8, t11, 2, 1, t13, 10, 2);
    t12 = (t0 + 4720);
    t14 = (t12 + 56U);
    t15 = *((char **)t14);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t5, 8);
    xsi_driver_vfirst_trans(t12, 0, 31);
    t18 = (t0 + 4624);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Always_43_2(char *t0)
{
    char t13[8];
    char t15[8];
    char t16[8];
    char t39[8];
    char t40[8];
    char t41[8];
    char t68[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    char *t14;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    int t28;
    char *t29;
    unsigned int t30;
    int t31;
    int t32;
    unsigned int t33;
    unsigned int t34;
    int t35;
    int t36;
    unsigned int t37;
    unsigned int t38;
    char *t42;
    char *t43;
    char *t44;
    unsigned int t45;
    char *t46;
    unsigned int t47;
    char *t48;
    unsigned int t49;
    int t50;
    char *t51;
    unsigned int t52;
    int t53;
    int t54;
    char *t55;
    unsigned int t56;
    int t57;
    int t58;
    unsigned int t59;
    int t60;
    unsigned int t61;
    unsigned int t62;
    int t63;
    unsigned int t64;
    unsigned int t65;
    int t66;
    int t67;

LAB0:    t1 = (t0 + 4304U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng0);
    t2 = (t0 + 4640);
    *((int *)t2) = 1;
    t3 = (t0 + 4336);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(43, ng0);

LAB5:    xsi_set_current_line(44, ng0);
    t4 = (t0 + 1208U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(47, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t3);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB14;

LAB15:
LAB16:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(45, ng0);
    xsi_set_current_line(45, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 2888);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 32);

LAB9:    t2 = (t0 + 2888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t13, 0, 8);
    xsi_vlog_signed_less(t13, 32, t4, 32, t5, 32);
    t11 = (t13 + 4);
    t6 = *((unsigned int *)t11);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB10;

LAB11:    goto LAB8;

LAB10:    xsi_set_current_line(46, ng0);
    t12 = ((char*)((ng3)));
    t14 = (t0 + 2728);
    t17 = (t0 + 2728);
    t18 = (t17 + 72U);
    t19 = *((char **)t18);
    t20 = (t0 + 2728);
    t21 = (t20 + 64U);
    t22 = *((char **)t21);
    t23 = (t0 + 2888);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    xsi_vlog_generic_convert_array_indices(t15, t16, t19, t22, 2, 1, t25, 32, 1);
    t26 = (t15 + 4);
    t27 = *((unsigned int *)t26);
    t28 = (!(t27));
    t29 = (t16 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (!(t30));
    t32 = (t28 && t31);
    if (t32 == 1)
        goto LAB12;

LAB13:    xsi_set_current_line(45, ng0);
    t2 = (t0 + 2888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 2888);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB9;

LAB12:    t33 = *((unsigned int *)t15);
    t34 = *((unsigned int *)t16);
    t35 = (t33 - t34);
    t36 = (t35 + 1);
    xsi_vlogvar_assign_value(t14, t12, 0, *((unsigned int *)t16), t36);
    goto LAB13;

LAB14:    xsi_set_current_line(47, ng0);

LAB17:    xsi_set_current_line(48, ng0);
    t4 = (t0 + 1528U);
    t5 = *((char **)t4);

LAB18:    t4 = ((char*)((ng4)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t4, 32);
    if (t28 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng6)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 32);
    if (t28 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng9)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 32);
    if (t28 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng8)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 32);
    if (t28 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng14)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 32);
    if (t28 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng15)));
    t28 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 32);
    if (t28 == 1)
        goto LAB29;

LAB30:
LAB32:
LAB31:    xsi_set_current_line(67, ng0);

LAB52:    xsi_set_current_line(68, ng0);
    t2 = (t0 + 1848U);
    t3 = *((char **)t2);
    t2 = (t0 + 2728);
    t4 = (t0 + 2728);
    t11 = (t4 + 72U);
    t12 = *((char **)t11);
    t14 = (t0 + 2728);
    t17 = (t14 + 64U);
    t18 = *((char **)t17);
    t19 = (t0 + 1688U);
    t20 = *((char **)t19);
    xsi_vlog_generic_convert_array_indices(t13, t15, t12, t18, 2, 1, t20, 10, 2);
    t19 = (t13 + 4);
    t6 = *((unsigned int *)t19);
    t28 = (!(t6));
    t21 = (t15 + 4);
    t7 = *((unsigned int *)t21);
    t31 = (!(t7));
    t32 = (t28 && t31);
    if (t32 == 1)
        goto LAB53;

LAB54:
LAB33:    xsi_set_current_line(71, ng0);
    t2 = xsi_vlog_time(t68, 1000.0000000000000, 1000.0000000000000);
    t3 = (t0 + 2008U);
    t4 = *((char **)t3);
    t3 = (t0 + 2168U);
    t11 = *((char **)t3);
    t3 = (t0 + 2728);
    t12 = (t3 + 56U);
    t14 = *((char **)t12);
    t17 = (t0 + 2728);
    t18 = (t17 + 72U);
    t19 = *((char **)t18);
    t20 = (t0 + 2728);
    t21 = (t20 + 64U);
    t22 = *((char **)t21);
    t23 = (t0 + 1688U);
    t24 = *((char **)t23);
    xsi_vlog_generic_get_array_select_value(t13, 32, t14, t19, t22, 2, 1, t24, 10, 2);
    xsi_vlogfile_write(1, 0, 0, ng16, 5, t0, (char)118, t68, 64, (char)118, t4, 32, (char)118, t11, 32, (char)118, t13, 32);
    goto LAB16;

LAB19:    xsi_set_current_line(49, ng0);

LAB34:    xsi_set_current_line(50, ng0);
    t11 = (t0 + 1848U);
    t12 = *((char **)t11);
    memset(t13, 0, 8);
    t11 = (t13 + 4);
    t14 = (t12 + 4);
    t27 = *((unsigned int *)t12);
    t30 = (t27 >> 0);
    *((unsigned int *)t13) = t30;
    t33 = *((unsigned int *)t14);
    t34 = (t33 >> 0);
    *((unsigned int *)t11) = t34;
    t37 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t37 & 255U);
    t38 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t38 & 255U);
    t17 = (t0 + 2728);
    t18 = (t0 + 2728);
    t19 = (t18 + 72U);
    t20 = *((char **)t19);
    t21 = (t0 + 2728);
    t22 = (t21 + 64U);
    t23 = *((char **)t22);
    t24 = (t0 + 1688U);
    t25 = *((char **)t24);
    xsi_vlog_generic_convert_array_indices(t15, t16, t20, t23, 2, 1, t25, 10, 2);
    t24 = (t0 + 2728);
    t26 = (t24 + 72U);
    t29 = *((char **)t26);
    t42 = ((char*)((ng5)));
    t43 = ((char*)((ng1)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t29)), 2, t42, 32, 1, t43, 32, 1);
    t44 = (t15 + 4);
    t45 = *((unsigned int *)t44);
    t31 = (!(t45));
    t46 = (t16 + 4);
    t47 = *((unsigned int *)t46);
    t32 = (!(t47));
    t35 = (t31 && t32);
    t48 = (t39 + 4);
    t49 = *((unsigned int *)t48);
    t36 = (!(t49));
    t50 = (t35 && t36);
    t51 = (t40 + 4);
    t52 = *((unsigned int *)t51);
    t53 = (!(t52));
    t54 = (t50 && t53);
    t55 = (t41 + 4);
    t56 = *((unsigned int *)t55);
    t57 = (!(t56));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB35;

LAB36:    goto LAB33;

LAB21:    xsi_set_current_line(52, ng0);

LAB37:    xsi_set_current_line(53, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t3 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 255U);
    t27 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t27 & 255U);
    t12 = (t0 + 2728);
    t14 = (t0 + 2728);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_convert_array_indices(t15, t16, t18, t21, 2, 1, t23, 10, 2);
    t22 = (t0 + 2728);
    t24 = (t22 + 72U);
    t25 = *((char **)t24);
    t26 = ((char*)((ng7)));
    t29 = ((char*)((ng8)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t25)), 2, t26, 32, 1, t29, 32, 1);
    t42 = (t15 + 4);
    t30 = *((unsigned int *)t42);
    t31 = (!(t30));
    t43 = (t16 + 4);
    t33 = *((unsigned int *)t43);
    t32 = (!(t33));
    t35 = (t31 && t32);
    t44 = (t39 + 4);
    t34 = *((unsigned int *)t44);
    t36 = (!(t34));
    t50 = (t35 && t36);
    t46 = (t40 + 4);
    t37 = *((unsigned int *)t46);
    t53 = (!(t37));
    t54 = (t50 && t53);
    t48 = (t41 + 4);
    t38 = *((unsigned int *)t48);
    t57 = (!(t38));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB38;

LAB39:    goto LAB33;

LAB23:    xsi_set_current_line(55, ng0);

LAB40:    xsi_set_current_line(56, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t3 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 255U);
    t27 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t27 & 255U);
    t12 = (t0 + 2728);
    t14 = (t0 + 2728);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_convert_array_indices(t15, t16, t18, t21, 2, 1, t23, 10, 2);
    t22 = (t0 + 2728);
    t24 = (t22 + 72U);
    t25 = *((char **)t24);
    t26 = ((char*)((ng10)));
    t29 = ((char*)((ng11)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t25)), 2, t26, 32, 1, t29, 32, 1);
    t42 = (t15 + 4);
    t30 = *((unsigned int *)t42);
    t31 = (!(t30));
    t43 = (t16 + 4);
    t33 = *((unsigned int *)t43);
    t32 = (!(t33));
    t35 = (t31 && t32);
    t44 = (t39 + 4);
    t34 = *((unsigned int *)t44);
    t36 = (!(t34));
    t50 = (t35 && t36);
    t46 = (t40 + 4);
    t37 = *((unsigned int *)t46);
    t53 = (!(t37));
    t54 = (t50 && t53);
    t48 = (t41 + 4);
    t38 = *((unsigned int *)t48);
    t57 = (!(t38));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB41;

LAB42:    goto LAB33;

LAB25:    xsi_set_current_line(58, ng0);

LAB43:    xsi_set_current_line(59, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t3 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 255U);
    t27 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t27 & 255U);
    t12 = (t0 + 2728);
    t14 = (t0 + 2728);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_convert_array_indices(t15, t16, t18, t21, 2, 1, t23, 10, 2);
    t22 = (t0 + 2728);
    t24 = (t22 + 72U);
    t25 = *((char **)t24);
    t26 = ((char*)((ng12)));
    t29 = ((char*)((ng13)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t25)), 2, t26, 32, 1, t29, 32, 1);
    t42 = (t15 + 4);
    t30 = *((unsigned int *)t42);
    t31 = (!(t30));
    t43 = (t16 + 4);
    t33 = *((unsigned int *)t43);
    t32 = (!(t33));
    t35 = (t31 && t32);
    t44 = (t39 + 4);
    t34 = *((unsigned int *)t44);
    t36 = (!(t34));
    t50 = (t35 && t36);
    t46 = (t40 + 4);
    t37 = *((unsigned int *)t46);
    t53 = (!(t37));
    t54 = (t50 && t53);
    t48 = (t41 + 4);
    t38 = *((unsigned int *)t48);
    t57 = (!(t38));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB44;

LAB45:    goto LAB33;

LAB27:    xsi_set_current_line(61, ng0);

LAB46:    xsi_set_current_line(62, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t3 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 65535U);
    t27 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t27 & 65535U);
    t12 = (t0 + 2728);
    t14 = (t0 + 2728);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_convert_array_indices(t15, t16, t18, t21, 2, 1, t23, 10, 2);
    t22 = (t0 + 2728);
    t24 = (t22 + 72U);
    t25 = *((char **)t24);
    t26 = ((char*)((ng7)));
    t29 = ((char*)((ng1)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t25)), 2, t26, 32, 1, t29, 32, 1);
    t42 = (t15 + 4);
    t30 = *((unsigned int *)t42);
    t31 = (!(t30));
    t43 = (t16 + 4);
    t33 = *((unsigned int *)t43);
    t32 = (!(t33));
    t35 = (t31 && t32);
    t44 = (t39 + 4);
    t34 = *((unsigned int *)t44);
    t36 = (!(t34));
    t50 = (t35 && t36);
    t46 = (t40 + 4);
    t37 = *((unsigned int *)t46);
    t53 = (!(t37));
    t54 = (t50 && t53);
    t48 = (t41 + 4);
    t38 = *((unsigned int *)t48);
    t57 = (!(t38));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB47;

LAB48:    goto LAB33;

LAB29:    xsi_set_current_line(64, ng0);

LAB49:    xsi_set_current_line(65, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t3 = (t13 + 4);
    t11 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 0);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t11);
    t9 = (t8 >> 0);
    *((unsigned int *)t3) = t9;
    t10 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t10 & 65535U);
    t27 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t27 & 65535U);
    t12 = (t0 + 2728);
    t14 = (t0 + 2728);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2728);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_convert_array_indices(t15, t16, t18, t21, 2, 1, t23, 10, 2);
    t22 = (t0 + 2728);
    t24 = (t22 + 72U);
    t25 = *((char **)t24);
    t26 = ((char*)((ng12)));
    t29 = ((char*)((ng11)));
    xsi_vlog_convert_partindices(t39, t40, t41, ((int*)(t25)), 2, t26, 32, 1, t29, 32, 1);
    t42 = (t15 + 4);
    t30 = *((unsigned int *)t42);
    t31 = (!(t30));
    t43 = (t16 + 4);
    t33 = *((unsigned int *)t43);
    t32 = (!(t33));
    t35 = (t31 && t32);
    t44 = (t39 + 4);
    t34 = *((unsigned int *)t44);
    t36 = (!(t34));
    t50 = (t35 && t36);
    t46 = (t40 + 4);
    t37 = *((unsigned int *)t46);
    t53 = (!(t37));
    t54 = (t50 && t53);
    t48 = (t41 + 4);
    t38 = *((unsigned int *)t48);
    t57 = (!(t38));
    t58 = (t54 && t57);
    if (t58 == 1)
        goto LAB50;

LAB51:    goto LAB33;

LAB35:    t59 = *((unsigned int *)t41);
    t60 = (t59 + 0);
    t61 = *((unsigned int *)t16);
    t62 = *((unsigned int *)t40);
    t63 = (t61 + t62);
    t64 = *((unsigned int *)t39);
    t65 = *((unsigned int *)t40);
    t66 = (t64 - t65);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t17, t13, t60, t63, t67);
    goto LAB36;

LAB38:    t45 = *((unsigned int *)t41);
    t60 = (t45 + 0);
    t47 = *((unsigned int *)t16);
    t49 = *((unsigned int *)t40);
    t63 = (t47 + t49);
    t52 = *((unsigned int *)t39);
    t56 = *((unsigned int *)t40);
    t66 = (t52 - t56);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t12, t13, t60, t63, t67);
    goto LAB39;

LAB41:    t45 = *((unsigned int *)t41);
    t60 = (t45 + 0);
    t47 = *((unsigned int *)t16);
    t49 = *((unsigned int *)t40);
    t63 = (t47 + t49);
    t52 = *((unsigned int *)t39);
    t56 = *((unsigned int *)t40);
    t66 = (t52 - t56);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t12, t13, t60, t63, t67);
    goto LAB42;

LAB44:    t45 = *((unsigned int *)t41);
    t60 = (t45 + 0);
    t47 = *((unsigned int *)t16);
    t49 = *((unsigned int *)t40);
    t63 = (t47 + t49);
    t52 = *((unsigned int *)t39);
    t56 = *((unsigned int *)t40);
    t66 = (t52 - t56);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t12, t13, t60, t63, t67);
    goto LAB45;

LAB47:    t45 = *((unsigned int *)t41);
    t60 = (t45 + 0);
    t47 = *((unsigned int *)t16);
    t49 = *((unsigned int *)t40);
    t63 = (t47 + t49);
    t52 = *((unsigned int *)t39);
    t56 = *((unsigned int *)t40);
    t66 = (t52 - t56);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t12, t13, t60, t63, t67);
    goto LAB48;

LAB50:    t45 = *((unsigned int *)t41);
    t60 = (t45 + 0);
    t47 = *((unsigned int *)t16);
    t49 = *((unsigned int *)t40);
    t63 = (t47 + t49);
    t52 = *((unsigned int *)t39);
    t56 = *((unsigned int *)t40);
    t66 = (t52 - t56);
    t67 = (t66 + 1);
    xsi_vlogvar_assign_value(t12, t13, t60, t63, t67);
    goto LAB51;

LAB53:    t8 = *((unsigned int *)t13);
    t9 = *((unsigned int *)t15);
    t35 = (t8 - t9);
    t36 = (t35 + 1);
    xsi_vlogvar_assign_value(t2, t3, 0, *((unsigned int *)t15), t36);
    goto LAB54;

}


extern void work_m_00000000001448527882_0010801604_init()
{
	static char *pe[] = {(void *)Initial_36_0,(void *)Cont_41_1,(void *)Always_43_2};
	xsi_register_didat("work_m_00000000001448527882_0010801604", "isim/mipstb_isim_beh.exe.sim/work/m_00000000001448527882_0010801604.didat");
	xsi_register_executes(pe);
}
