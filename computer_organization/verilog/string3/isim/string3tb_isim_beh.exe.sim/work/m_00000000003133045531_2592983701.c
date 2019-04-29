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

/* This file is designed for use with ISim build 0x8ef4fb42 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/HW/JiSuanJiZuCheng/Verilog/string3/string3.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static int ng3[] = {2, 0};
static int ng4[] = {3, 0};
static int ng5[] = {4, 0};
static int ng6[] = {5, 0};



static void Initial_28_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(28, ng0);

LAB2:    xsi_set_current_line(28, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1012);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(29, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 920);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);

LAB1:    return;
}

static void Always_32_1(char *t0)
{
    char t9[8];
    char t10[8];
    char t13[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    int t8;
    char *t11;
    char *t12;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    char *t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t45;
    char *t46;

LAB0:    t1 = (t0 + 1680U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(32, ng0);
    t2 = (t0 + 1876);
    *((int *)t2) = 1;
    t3 = (t0 + 1708);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(32, ng0);

LAB5:    xsi_set_current_line(33, ng0);
    t4 = (t0 + 1012);
    t5 = (t4 + 36U);
    t6 = *((char **)t5);

LAB6:    t7 = ((char*)((ng1)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t7, 32);
    if (t8 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t2, 32);
    if (t8 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng3)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t2, 32);
    if (t8 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng4)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t2, 32);
    if (t8 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng5)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t2, 32);
    if (t8 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng6)));
    t8 = xsi_vlog_signed_case_compare(t6, 32, t2, 32);
    if (t8 == 1)
        goto LAB17;

LAB18:
LAB19:    goto LAB2;

LAB7:    xsi_set_current_line(35, ng0);

LAB20:    xsi_set_current_line(36, ng0);
    t11 = (t0 + 692U);
    t12 = *((char **)t11);
    t11 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t14 = (t12 + 4);
    t15 = (t11 + 4);
    t16 = *((unsigned int *)t12);
    t17 = *((unsigned int *)t11);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t14);
    t20 = *((unsigned int *)t15);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t14);
    t24 = *((unsigned int *)t15);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB24;

LAB21:    if (t25 != 0)
        goto LAB23;

LAB22:    *((unsigned int *)t13) = 1;

LAB24:    memset(t10, 0, 8);
    t29 = (t13 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB25;

LAB26:    if (*((unsigned int *)t29) != 0)
        goto LAB27;

LAB28:    t36 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t36);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB29;

LAB30:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t36);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t36) > 0)
        goto LAB33;

LAB34:    if (*((unsigned int *)t10) > 0)
        goto LAB35;

LAB36:    memcpy(t9, t45, 8);

LAB37:    t46 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t46, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(37, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB19;

LAB9:    xsi_set_current_line(40, ng0);

LAB38:    xsi_set_current_line(41, ng0);
    t3 = (t0 + 692U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t7 = (t3 + 4);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t3);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t5);
    t20 = *((unsigned int *)t7);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t5);
    t24 = *((unsigned int *)t7);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB42;

LAB39:    if (t25 != 0)
        goto LAB41;

LAB40:    *((unsigned int *)t13) = 1;

LAB42:    memset(t10, 0, 8);
    t12 = (t13 + 4);
    t30 = *((unsigned int *)t12);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB43;

LAB44:    if (*((unsigned int *)t12) != 0)
        goto LAB45;

LAB46:    t15 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t15);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB47;

LAB48:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t15);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB49;

LAB50:    if (*((unsigned int *)t15) > 0)
        goto LAB51;

LAB52:    if (*((unsigned int *)t10) > 0)
        goto LAB53;

LAB54:    memcpy(t9, t29, 8);

LAB55:    t35 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t35, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(42, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB19;

LAB11:    xsi_set_current_line(45, ng0);

LAB56:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 692U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng1)));
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t7 = (t3 + 4);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t3);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t5);
    t20 = *((unsigned int *)t7);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t5);
    t24 = *((unsigned int *)t7);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB60;

LAB57:    if (t25 != 0)
        goto LAB59;

LAB58:    *((unsigned int *)t13) = 1;

LAB60:    memset(t10, 0, 8);
    t12 = (t13 + 4);
    t30 = *((unsigned int *)t12);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB61;

LAB62:    if (*((unsigned int *)t12) != 0)
        goto LAB63;

LAB64:    t15 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t15);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB65;

LAB66:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t15);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB67;

LAB68:    if (*((unsigned int *)t15) > 0)
        goto LAB69;

LAB70:    if (*((unsigned int *)t10) > 0)
        goto LAB71;

LAB72:    memcpy(t9, t29, 8);

LAB73:    t35 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t35, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(47, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB19;

LAB13:    xsi_set_current_line(50, ng0);

LAB74:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 692U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t7 = (t3 + 4);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t3);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t5);
    t20 = *((unsigned int *)t7);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t5);
    t24 = *((unsigned int *)t7);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB78;

LAB75:    if (t25 != 0)
        goto LAB77;

LAB76:    *((unsigned int *)t13) = 1;

LAB78:    memset(t10, 0, 8);
    t12 = (t13 + 4);
    t30 = *((unsigned int *)t12);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB79;

LAB80:    if (*((unsigned int *)t12) != 0)
        goto LAB81;

LAB82:    t15 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t15);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB83;

LAB84:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t15);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB85;

LAB86:    if (*((unsigned int *)t15) > 0)
        goto LAB87;

LAB88:    if (*((unsigned int *)t10) > 0)
        goto LAB89;

LAB90:    memcpy(t9, t29, 8);

LAB91:    t35 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t35, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(52, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB19;

LAB15:    xsi_set_current_line(55, ng0);

LAB92:    xsi_set_current_line(56, ng0);
    t3 = (t0 + 692U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t7 = (t3 + 4);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t3);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t5);
    t20 = *((unsigned int *)t7);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t5);
    t24 = *((unsigned int *)t7);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB96;

LAB93:    if (t25 != 0)
        goto LAB95;

LAB94:    *((unsigned int *)t13) = 1;

LAB96:    memset(t10, 0, 8);
    t12 = (t13 + 4);
    t30 = *((unsigned int *)t12);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB97;

LAB98:    if (*((unsigned int *)t12) != 0)
        goto LAB99;

LAB100:    t15 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t15);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB101;

LAB102:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t15);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB103;

LAB104:    if (*((unsigned int *)t15) > 0)
        goto LAB105;

LAB106:    if (*((unsigned int *)t10) > 0)
        goto LAB107;

LAB108:    memcpy(t9, t29, 8);

LAB109:    t35 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t35, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(57, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB19;

LAB17:    xsi_set_current_line(60, ng0);

LAB110:    xsi_set_current_line(61, ng0);
    t3 = (t0 + 692U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng2)));
    memset(t13, 0, 8);
    t5 = (t4 + 4);
    t7 = (t3 + 4);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t3);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t5);
    t20 = *((unsigned int *)t7);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t5);
    t24 = *((unsigned int *)t7);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB114;

LAB111:    if (t25 != 0)
        goto LAB113;

LAB112:    *((unsigned int *)t13) = 1;

LAB114:    memset(t10, 0, 8);
    t12 = (t13 + 4);
    t30 = *((unsigned int *)t12);
    t31 = (~(t30));
    t32 = *((unsigned int *)t13);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB115;

LAB116:    if (*((unsigned int *)t12) != 0)
        goto LAB117;

LAB118:    t15 = (t10 + 4);
    t37 = *((unsigned int *)t10);
    t38 = *((unsigned int *)t15);
    t39 = (t37 || t38);
    if (t39 > 0)
        goto LAB119;

LAB120:    t41 = *((unsigned int *)t10);
    t42 = (~(t41));
    t43 = *((unsigned int *)t15);
    t44 = (t42 || t43);
    if (t44 > 0)
        goto LAB121;

LAB122:    if (*((unsigned int *)t15) > 0)
        goto LAB123;

LAB124:    if (*((unsigned int *)t10) > 0)
        goto LAB125;

LAB126:    memcpy(t9, t29, 8);

LAB127:    t35 = (t0 + 1012);
    xsi_vlogvar_wait_assign_value(t35, t9, 0, 0, 32, 0LL);
    xsi_set_current_line(62, ng0);
    t2 = (t0 + 692U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t9, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t16 = *((unsigned int *)t3);
    t17 = *((unsigned int *)t2);
    t18 = (t16 ^ t17);
    t19 = *((unsigned int *)t4);
    t20 = *((unsigned int *)t5);
    t21 = (t19 ^ t20);
    t22 = (t18 | t21);
    t23 = *((unsigned int *)t4);
    t24 = *((unsigned int *)t5);
    t25 = (t23 | t24);
    t26 = (~(t25));
    t27 = (t22 & t26);
    if (t27 != 0)
        goto LAB131;

LAB128:    if (t25 != 0)
        goto LAB130;

LAB129:    *((unsigned int *)t9) = 1;

LAB131:    t11 = (t0 + 920);
    xsi_vlogvar_wait_assign_value(t11, t9, 0, 0, 1, 0LL);
    goto LAB19;

LAB23:    t28 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB24;

LAB25:    *((unsigned int *)t10) = 1;
    goto LAB28;

LAB27:    t35 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t35) = 1;
    goto LAB28;

LAB29:    t40 = ((char*)((ng2)));
    goto LAB30;

LAB31:    t45 = ((char*)((ng1)));
    goto LAB32;

LAB33:    xsi_vlog_unsigned_bit_combine(t9, 32, t40, 32, t45, 32);
    goto LAB37;

LAB35:    memcpy(t9, t40, 8);
    goto LAB37;

LAB41:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB42;

LAB43:    *((unsigned int *)t10) = 1;
    goto LAB46;

LAB45:    t14 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB46;

LAB47:    t28 = ((char*)((ng3)));
    goto LAB48;

LAB49:    t29 = ((char*)((ng1)));
    goto LAB50;

LAB51:    xsi_vlog_unsigned_bit_combine(t9, 32, t28, 32, t29, 32);
    goto LAB55;

LAB53:    memcpy(t9, t28, 8);
    goto LAB55;

LAB59:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB60;

LAB61:    *((unsigned int *)t10) = 1;
    goto LAB64;

LAB63:    t14 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB64;

LAB65:    t28 = ((char*)((ng4)));
    goto LAB66;

LAB67:    t29 = ((char*)((ng1)));
    goto LAB68;

LAB69:    xsi_vlog_unsigned_bit_combine(t9, 32, t28, 32, t29, 32);
    goto LAB73;

LAB71:    memcpy(t9, t28, 8);
    goto LAB73;

LAB77:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB78;

LAB79:    *((unsigned int *)t10) = 1;
    goto LAB82;

LAB81:    t14 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB82;

LAB83:    t28 = ((char*)((ng5)));
    goto LAB84;

LAB85:    t29 = ((char*)((ng1)));
    goto LAB86;

LAB87:    xsi_vlog_unsigned_bit_combine(t9, 32, t28, 32, t29, 32);
    goto LAB91;

LAB89:    memcpy(t9, t28, 8);
    goto LAB91;

LAB95:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB96;

LAB97:    *((unsigned int *)t10) = 1;
    goto LAB100;

LAB99:    t14 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB100;

LAB101:    t28 = ((char*)((ng6)));
    goto LAB102;

LAB103:    t29 = ((char*)((ng1)));
    goto LAB104;

LAB105:    xsi_vlog_unsigned_bit_combine(t9, 32, t28, 32, t29, 32);
    goto LAB109;

LAB107:    memcpy(t9, t28, 8);
    goto LAB109;

LAB113:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB114;

LAB115:    *((unsigned int *)t10) = 1;
    goto LAB118;

LAB117:    t14 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB118;

LAB119:    t28 = ((char*)((ng3)));
    goto LAB120;

LAB121:    t29 = ((char*)((ng4)));
    goto LAB122;

LAB123:    xsi_vlog_unsigned_bit_combine(t9, 32, t28, 32, t29, 32);
    goto LAB127;

LAB125:    memcpy(t9, t28, 8);
    goto LAB127;

LAB130:    t7 = (t9 + 4);
    *((unsigned int *)t9) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB131;

}


extern void work_m_00000000003133045531_2592983701_init()
{
	static char *pe[] = {(void *)Initial_28_0,(void *)Always_32_1};
	xsi_register_didat("work_m_00000000003133045531_2592983701", "isim/string3tb_isim_beh.exe.sim/work/m_00000000003133045531_2592983701.didat");
	xsi_register_executes(pe);
}
