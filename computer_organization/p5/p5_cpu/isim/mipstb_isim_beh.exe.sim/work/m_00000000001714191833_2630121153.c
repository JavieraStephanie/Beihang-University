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
static const char *ng0 = "D:/Tasks/Beihang University/HW/Beihang-University/computer_organization/p5/p5_cpu/storeOpt.v";
static unsigned int ng1[] = {40U, 0U};
static int ng2[] = {0, 0};
static int ng3[] = {1, 0};
static int ng4[] = {2, 0};
static int ng5[] = {4, 0};
static int ng6[] = {3, 0};
static int ng7[] = {8, 0};
static unsigned int ng8[] = {41U, 0U};
static int ng9[] = {9, 0};
static int ng10[] = {15, 0};



static void Always_30_0(char *t0)
{
    char t12[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    int t9;
    char *t10;
    char *t11;
    char *t13;
    char *t14;
    char *t15;

LAB0:    t1 = (t0 + 2800U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 3120);
    *((int *)t2) = 1;
    t3 = (t0 + 2832);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(30, ng0);

LAB5:    xsi_set_current_line(31, ng0);
    t4 = (t0 + 1320U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t4, 6);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng8)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 6, t2, 6);
    if (t6 == 1)
        goto LAB9;

LAB10:
LAB12:
LAB11:    xsi_set_current_line(58, ng0);
    t2 = ((char*)((ng10)));
    t3 = (t0 + 1880);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 4);

LAB13:    goto LAB2;

LAB7:    xsi_set_current_line(32, ng0);

LAB14:    xsi_set_current_line(33, ng0);
    t7 = (t0 + 1480U);
    t8 = *((char **)t7);

LAB15:    t7 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t8, 2, t7, 32);
    if (t9 == 1)
        goto LAB16;

LAB17:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB18;

LAB19:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB20;

LAB21:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t8, 2, t2, 32);
    if (t6 == 1)
        goto LAB22;

LAB23:
LAB24:    goto LAB13;

LAB9:    xsi_set_current_line(48, ng0);

LAB29:    xsi_set_current_line(49, ng0);
    t3 = (t0 + 1480U);
    t4 = *((char **)t3);
    t3 = (t0 + 1440U);
    t7 = (t3 + 72U);
    t10 = *((char **)t7);
    t11 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t12, 32, t4, t10, 2, t11, 32, 1);

LAB30:    t13 = ((char*)((ng2)));
    t9 = xsi_vlog_unsigned_case_compare(t12, 32, t13, 32);
    if (t9 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t12, 32, t2, 32);
    if (t6 == 1)
        goto LAB33;

LAB34:
LAB35:    goto LAB13;

LAB16:    xsi_set_current_line(34, ng0);

LAB25:    xsi_set_current_line(35, ng0);
    t10 = ((char*)((ng3)));
    t11 = (t0 + 1880);
    xsi_vlogvar_assign_value(t11, t10, 0, 0, 4);
    goto LAB24;

LAB18:    xsi_set_current_line(37, ng0);

LAB26:    xsi_set_current_line(38, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 1880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB24;

LAB20:    xsi_set_current_line(40, ng0);

LAB27:    xsi_set_current_line(41, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 1880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB24;

LAB22:    xsi_set_current_line(43, ng0);

LAB28:    xsi_set_current_line(44, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 1880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB24;

LAB31:    xsi_set_current_line(50, ng0);

LAB36:    xsi_set_current_line(51, ng0);
    t14 = ((char*)((ng6)));
    t15 = (t0 + 1880);
    xsi_vlogvar_assign_value(t15, t14, 0, 0, 4);
    goto LAB35;

LAB33:    xsi_set_current_line(53, ng0);

LAB37:    xsi_set_current_line(54, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 1880);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 4);
    goto LAB35;

}


extern void work_m_00000000001714191833_2630121153_init()
{
	static char *pe[] = {(void *)Always_30_0};
	xsi_register_didat("work_m_00000000001714191833_2630121153", "isim/mipstb_isim_beh.exe.sim/work/m_00000000001714191833_2630121153.didat");
	xsi_register_executes(pe);
}
