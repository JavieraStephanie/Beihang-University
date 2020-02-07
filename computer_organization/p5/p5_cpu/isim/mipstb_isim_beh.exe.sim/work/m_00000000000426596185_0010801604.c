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
static const char *ng0 = "D:/Tasks/Beihang University/HW/Beihang-University/computer_organization/p5/p5_cpu/dm.v";
static int ng1[] = {0, 0};
static int ng2[] = {1024, 0};
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0};
static int ng5[] = {2, 0};
static int ng6[] = {4, 0};
static int ng7[] = {8, 0};
static int ng8[] = {3, 0};
static int ng9[] = {9, 0};
static const char *ng10 = "%d@%h: *%h <= %h";



static void Initial_37_0(char *t0)
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

LAB0:    xsi_set_current_line(37, ng0);

LAB2:    xsi_set_current_line(38, ng0);
    xsi_set_current_line(38, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3048);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 3048);
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
LAB4:    xsi_set_current_line(39, ng0);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 2888);
    t16 = (t0 + 2888);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2888);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 3048);
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

LAB7:    xsi_set_current_line(38, ng0);
    t1 = (t0 + 3048);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 3048);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB6:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB7;

}

static void Cont_42_1(char *t0)
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

LAB0:    t1 = (t0 + 4216U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(42, ng0);
    t2 = (t0 + 2888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 2888);
    t7 = (t6 + 72U);
    t8 = *((char **)t7);
    t9 = (t0 + 2888);
    t10 = (t9 + 64U);
    t11 = *((char **)t10);
    t12 = (t0 + 1688U);
    t13 = *((char **)t12);
    xsi_vlog_generic_get_array_select_value(t5, 32, t4, t8, t11, 2, 1, t13, 10, 2);
    t12 = (t0 + 5144);
    t14 = (t12 + 56U);
    t15 = *((char **)t14);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t5, 8);
    xsi_driver_vfirst_trans(t12, 0, 31);
    t18 = (t0 + 5032);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Cont_44_2(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char t33[8];
    char t34[8];
    char t47[8];
    char t56[8];
    char t68[8];
    char t69[8];
    char t72[8];
    char t99[8];
    char t103[8];
    char t112[8];
    char t120[8];
    char t133[8];
    char t142[8];
    char t154[8];
    char t155[8];
    char t158[8];
    char t185[8];
    char t189[8];
    char t198[8];
    char t206[8];
    char t219[8];
    char t228[8];
    char t240[8];
    char t241[8];
    char t244[8];
    char t271[8];
    char t275[8];
    char t284[8];
    char t292[8];
    char t306[8];
    char t307[8];
    char t310[8];
    char t337[8];
    char t338[8];
    char t351[8];
    char t360[8];
    char t372[8];
    char t373[8];
    char t376[8];
    char t403[8];
    char t407[8];
    char t416[8];
    char t424[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
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
    char *t35;
    char *t36;
    char *t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
    char *t46;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t54;
    char *t55;
    char *t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t70;
    char *t71;
    char *t73;
    char *t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    char *t87;
    char *t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    char *t94;
    char *t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    char *t100;
    char *t101;
    char *t102;
    char *t104;
    char *t105;
    char *t106;
    char *t107;
    char *t108;
    char *t109;
    char *t110;
    char *t111;
    char *t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    char *t121;
    char *t122;
    char *t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    unsigned int t128;
    unsigned int t129;
    char *t130;
    char *t131;
    char *t132;
    char *t134;
    char *t135;
    char *t136;
    char *t137;
    char *t138;
    char *t139;
    char *t140;
    char *t141;
    char *t143;
    unsigned int t144;
    unsigned int t145;
    unsigned int t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    unsigned int t150;
    unsigned int t151;
    unsigned int t152;
    unsigned int t153;
    char *t156;
    char *t157;
    char *t159;
    char *t160;
    unsigned int t161;
    unsigned int t162;
    unsigned int t163;
    unsigned int t164;
    unsigned int t165;
    unsigned int t166;
    unsigned int t167;
    unsigned int t168;
    unsigned int t169;
    unsigned int t170;
    unsigned int t171;
    unsigned int t172;
    char *t173;
    char *t174;
    unsigned int t175;
    unsigned int t176;
    unsigned int t177;
    unsigned int t178;
    unsigned int t179;
    char *t180;
    char *t181;
    unsigned int t182;
    unsigned int t183;
    unsigned int t184;
    char *t186;
    char *t187;
    char *t188;
    char *t190;
    char *t191;
    char *t192;
    char *t193;
    char *t194;
    char *t195;
    char *t196;
    char *t197;
    char *t199;
    unsigned int t200;
    unsigned int t201;
    unsigned int t202;
    unsigned int t203;
    unsigned int t204;
    unsigned int t205;
    char *t207;
    char *t208;
    char *t209;
    unsigned int t210;
    unsigned int t211;
    unsigned int t212;
    unsigned int t213;
    unsigned int t214;
    unsigned int t215;
    char *t216;
    char *t217;
    char *t218;
    char *t220;
    char *t221;
    char *t222;
    char *t223;
    char *t224;
    char *t225;
    char *t226;
    char *t227;
    char *t229;
    unsigned int t230;
    unsigned int t231;
    unsigned int t232;
    unsigned int t233;
    unsigned int t234;
    unsigned int t235;
    unsigned int t236;
    unsigned int t237;
    unsigned int t238;
    unsigned int t239;
    char *t242;
    char *t243;
    char *t245;
    char *t246;
    unsigned int t247;
    unsigned int t248;
    unsigned int t249;
    unsigned int t250;
    unsigned int t251;
    unsigned int t252;
    unsigned int t253;
    unsigned int t254;
    unsigned int t255;
    unsigned int t256;
    unsigned int t257;
    unsigned int t258;
    char *t259;
    char *t260;
    unsigned int t261;
    unsigned int t262;
    unsigned int t263;
    unsigned int t264;
    unsigned int t265;
    char *t266;
    char *t267;
    unsigned int t268;
    unsigned int t269;
    unsigned int t270;
    char *t272;
    char *t273;
    char *t274;
    char *t276;
    char *t277;
    char *t278;
    char *t279;
    char *t280;
    char *t281;
    char *t282;
    char *t283;
    char *t285;
    unsigned int t286;
    unsigned int t287;
    unsigned int t288;
    unsigned int t289;
    unsigned int t290;
    unsigned int t291;
    char *t293;
    char *t294;
    char *t295;
    unsigned int t296;
    unsigned int t297;
    unsigned int t298;
    unsigned int t299;
    unsigned int t300;
    unsigned int t301;
    unsigned int t302;
    unsigned int t303;
    unsigned int t304;
    unsigned int t305;
    char *t308;
    char *t309;
    char *t311;
    char *t312;
    unsigned int t313;
    unsigned int t314;
    unsigned int t315;
    unsigned int t316;
    unsigned int t317;
    unsigned int t318;
    unsigned int t319;
    unsigned int t320;
    unsigned int t321;
    unsigned int t322;
    unsigned int t323;
    unsigned int t324;
    char *t325;
    char *t326;
    unsigned int t327;
    unsigned int t328;
    unsigned int t329;
    unsigned int t330;
    unsigned int t331;
    char *t332;
    char *t333;
    unsigned int t334;
    unsigned int t335;
    unsigned int t336;
    char *t339;
    char *t340;
    char *t341;
    unsigned int t342;
    unsigned int t343;
    unsigned int t344;
    unsigned int t345;
    unsigned int t346;
    unsigned int t347;
    char *t348;
    char *t349;
    char *t350;
    char *t352;
    char *t353;
    char *t354;
    char *t355;
    char *t356;
    char *t357;
    char *t358;
    char *t359;
    char *t361;
    unsigned int t362;
    unsigned int t363;
    unsigned int t364;
    unsigned int t365;
    unsigned int t366;
    unsigned int t367;
    unsigned int t368;
    unsigned int t369;
    unsigned int t370;
    unsigned int t371;
    char *t374;
    char *t375;
    char *t377;
    char *t378;
    unsigned int t379;
    unsigned int t380;
    unsigned int t381;
    unsigned int t382;
    unsigned int t383;
    unsigned int t384;
    unsigned int t385;
    unsigned int t386;
    unsigned int t387;
    unsigned int t388;
    unsigned int t389;
    unsigned int t390;
    char *t391;
    char *t392;
    unsigned int t393;
    unsigned int t394;
    unsigned int t395;
    unsigned int t396;
    unsigned int t397;
    char *t398;
    char *t399;
    unsigned int t400;
    unsigned int t401;
    unsigned int t402;
    char *t404;
    char *t405;
    char *t406;
    char *t408;
    char *t409;
    char *t410;
    char *t411;
    char *t412;
    char *t413;
    char *t414;
    char *t415;
    char *t417;
    unsigned int t418;
    unsigned int t419;
    unsigned int t420;
    unsigned int t421;
    unsigned int t422;
    unsigned int t423;
    char *t425;
    char *t426;
    char *t427;
    unsigned int t428;
    unsigned int t429;
    unsigned int t430;
    unsigned int t431;
    unsigned int t432;
    unsigned int t433;
    unsigned int t434;
    unsigned int t435;
    unsigned int t436;
    unsigned int t437;
    char *t438;
    char *t439;
    char *t440;
    char *t441;
    char *t442;
    char *t443;
    char *t444;

LAB0:    t1 = (t0 + 4464U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1528U);
    t5 = *((char **)t2);
    t2 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t2 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t2);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB7;

LAB4:    if (t18 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t6) = 1;

LAB7:    memset(t4, 0, 8);
    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 & 1U);
    if (t27 != 0)
        goto LAB8;

LAB9:    if (*((unsigned int *)t22) != 0)
        goto LAB10;

LAB11:    t29 = (t4 + 4);
    t30 = *((unsigned int *)t4);
    t31 = *((unsigned int *)t29);
    t32 = (t30 || t31);
    if (t32 > 0)
        goto LAB12;

LAB13:    t64 = *((unsigned int *)t4);
    t65 = (~(t64));
    t66 = *((unsigned int *)t29);
    t67 = (t65 || t66);
    if (t67 > 0)
        goto LAB14;

LAB15:    if (*((unsigned int *)t29) > 0)
        goto LAB16;

LAB17:    if (*((unsigned int *)t4) > 0)
        goto LAB18;

LAB19:    memcpy(t3, t68, 8);

LAB20:    t438 = (t0 + 5208);
    t440 = (t438 + 56U);
    t441 = *((char **)t440);
    t442 = (t441 + 56U);
    t443 = *((char **)t442);
    memcpy(t443, t3, 8);
    xsi_driver_vfirst_trans(t438, 0, 31);
    t444 = (t0 + 5048);
    *((int *)t444) = 1;

LAB1:    return;
LAB6:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

LAB8:    *((unsigned int *)t4) = 1;
    goto LAB11;

LAB10:    t28 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB11;

LAB12:    t35 = (t0 + 1848U);
    t36 = *((char **)t35);
    memset(t34, 0, 8);
    t35 = (t34 + 4);
    t37 = (t36 + 4);
    t38 = *((unsigned int *)t36);
    t39 = (t38 >> 0);
    *((unsigned int *)t34) = t39;
    t40 = *((unsigned int *)t37);
    t41 = (t40 >> 0);
    *((unsigned int *)t35) = t41;
    t42 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t42 & 255U);
    t43 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t43 & 255U);
    t44 = (t0 + 2888);
    t45 = (t44 + 56U);
    t46 = *((char **)t45);
    t48 = (t0 + 2888);
    t49 = (t48 + 72U);
    t50 = *((char **)t49);
    t51 = (t0 + 2888);
    t52 = (t51 + 64U);
    t53 = *((char **)t52);
    t54 = (t0 + 1688U);
    t55 = *((char **)t54);
    xsi_vlog_generic_get_array_select_value(t47, 32, t46, t50, t53, 2, 1, t55, 10, 2);
    memset(t56, 0, 8);
    t54 = (t56 + 4);
    t57 = (t47 + 4);
    t58 = *((unsigned int *)t47);
    t59 = (t58 >> 8);
    *((unsigned int *)t56) = t59;
    t60 = *((unsigned int *)t57);
    t61 = (t60 >> 8);
    *((unsigned int *)t54) = t61;
    t62 = *((unsigned int *)t56);
    *((unsigned int *)t56) = (t62 & 16777215U);
    t63 = *((unsigned int *)t54);
    *((unsigned int *)t54) = (t63 & 16777215U);
    xsi_vlogtype_concat(t33, 32, 32, 2U, t56, 24, t34, 8);
    goto LAB13;

LAB14:    t70 = (t0 + 1528U);
    t71 = *((char **)t70);
    t70 = ((char*)((ng5)));
    memset(t72, 0, 8);
    t73 = (t71 + 4);
    t74 = (t70 + 4);
    t75 = *((unsigned int *)t71);
    t76 = *((unsigned int *)t70);
    t77 = (t75 ^ t76);
    t78 = *((unsigned int *)t73);
    t79 = *((unsigned int *)t74);
    t80 = (t78 ^ t79);
    t81 = (t77 | t80);
    t82 = *((unsigned int *)t73);
    t83 = *((unsigned int *)t74);
    t84 = (t82 | t83);
    t85 = (~(t84));
    t86 = (t81 & t85);
    if (t86 != 0)
        goto LAB24;

LAB21:    if (t84 != 0)
        goto LAB23;

LAB22:    *((unsigned int *)t72) = 1;

LAB24:    memset(t69, 0, 8);
    t88 = (t72 + 4);
    t89 = *((unsigned int *)t88);
    t90 = (~(t89));
    t91 = *((unsigned int *)t72);
    t92 = (t91 & t90);
    t93 = (t92 & 1U);
    if (t93 != 0)
        goto LAB25;

LAB26:    if (*((unsigned int *)t88) != 0)
        goto LAB27;

LAB28:    t95 = (t69 + 4);
    t96 = *((unsigned int *)t69);
    t97 = *((unsigned int *)t95);
    t98 = (t96 || t97);
    if (t98 > 0)
        goto LAB29;

LAB30:    t150 = *((unsigned int *)t69);
    t151 = (~(t150));
    t152 = *((unsigned int *)t95);
    t153 = (t151 || t152);
    if (t153 > 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t95) > 0)
        goto LAB33;

LAB34:    if (*((unsigned int *)t69) > 0)
        goto LAB35;

LAB36:    memcpy(t68, t154, 8);

LAB37:    goto LAB15;

LAB16:    xsi_vlog_unsigned_bit_combine(t3, 32, t33, 32, t68, 32);
    goto LAB20;

LAB18:    memcpy(t3, t33, 8);
    goto LAB20;

LAB23:    t87 = (t72 + 4);
    *((unsigned int *)t72) = 1;
    *((unsigned int *)t87) = 1;
    goto LAB24;

LAB25:    *((unsigned int *)t69) = 1;
    goto LAB28;

LAB27:    t94 = (t69 + 4);
    *((unsigned int *)t69) = 1;
    *((unsigned int *)t94) = 1;
    goto LAB28;

LAB29:    t100 = (t0 + 2888);
    t101 = (t100 + 56U);
    t102 = *((char **)t101);
    t104 = (t0 + 2888);
    t105 = (t104 + 72U);
    t106 = *((char **)t105);
    t107 = (t0 + 2888);
    t108 = (t107 + 64U);
    t109 = *((char **)t108);
    t110 = (t0 + 1688U);
    t111 = *((char **)t110);
    xsi_vlog_generic_get_array_select_value(t103, 32, t102, t106, t109, 2, 1, t111, 10, 2);
    memset(t112, 0, 8);
    t110 = (t112 + 4);
    t113 = (t103 + 4);
    t114 = *((unsigned int *)t103);
    t115 = (t114 >> 0);
    *((unsigned int *)t112) = t115;
    t116 = *((unsigned int *)t113);
    t117 = (t116 >> 0);
    *((unsigned int *)t110) = t117;
    t118 = *((unsigned int *)t112);
    *((unsigned int *)t112) = (t118 & 255U);
    t119 = *((unsigned int *)t110);
    *((unsigned int *)t110) = (t119 & 255U);
    t121 = (t0 + 1848U);
    t122 = *((char **)t121);
    memset(t120, 0, 8);
    t121 = (t120 + 4);
    t123 = (t122 + 4);
    t124 = *((unsigned int *)t122);
    t125 = (t124 >> 0);
    *((unsigned int *)t120) = t125;
    t126 = *((unsigned int *)t123);
    t127 = (t126 >> 0);
    *((unsigned int *)t121) = t127;
    t128 = *((unsigned int *)t120);
    *((unsigned int *)t120) = (t128 & 255U);
    t129 = *((unsigned int *)t121);
    *((unsigned int *)t121) = (t129 & 255U);
    t130 = (t0 + 2888);
    t131 = (t130 + 56U);
    t132 = *((char **)t131);
    t134 = (t0 + 2888);
    t135 = (t134 + 72U);
    t136 = *((char **)t135);
    t137 = (t0 + 2888);
    t138 = (t137 + 64U);
    t139 = *((char **)t138);
    t140 = (t0 + 1688U);
    t141 = *((char **)t140);
    xsi_vlog_generic_get_array_select_value(t133, 32, t132, t136, t139, 2, 1, t141, 10, 2);
    memset(t142, 0, 8);
    t140 = (t142 + 4);
    t143 = (t133 + 4);
    t144 = *((unsigned int *)t133);
    t145 = (t144 >> 16);
    *((unsigned int *)t142) = t145;
    t146 = *((unsigned int *)t143);
    t147 = (t146 >> 16);
    *((unsigned int *)t140) = t147;
    t148 = *((unsigned int *)t142);
    *((unsigned int *)t142) = (t148 & 65535U);
    t149 = *((unsigned int *)t140);
    *((unsigned int *)t140) = (t149 & 65535U);
    xsi_vlogtype_concat(t99, 32, 32, 3U, t142, 16, t120, 8, t112, 8);
    goto LAB30;

LAB31:    t156 = (t0 + 1528U);
    t157 = *((char **)t156);
    t156 = ((char*)((ng6)));
    memset(t158, 0, 8);
    t159 = (t157 + 4);
    t160 = (t156 + 4);
    t161 = *((unsigned int *)t157);
    t162 = *((unsigned int *)t156);
    t163 = (t161 ^ t162);
    t164 = *((unsigned int *)t159);
    t165 = *((unsigned int *)t160);
    t166 = (t164 ^ t165);
    t167 = (t163 | t166);
    t168 = *((unsigned int *)t159);
    t169 = *((unsigned int *)t160);
    t170 = (t168 | t169);
    t171 = (~(t170));
    t172 = (t167 & t171);
    if (t172 != 0)
        goto LAB41;

LAB38:    if (t170 != 0)
        goto LAB40;

LAB39:    *((unsigned int *)t158) = 1;

LAB41:    memset(t155, 0, 8);
    t174 = (t158 + 4);
    t175 = *((unsigned int *)t174);
    t176 = (~(t175));
    t177 = *((unsigned int *)t158);
    t178 = (t177 & t176);
    t179 = (t178 & 1U);
    if (t179 != 0)
        goto LAB42;

LAB43:    if (*((unsigned int *)t174) != 0)
        goto LAB44;

LAB45:    t181 = (t155 + 4);
    t182 = *((unsigned int *)t155);
    t183 = *((unsigned int *)t181);
    t184 = (t182 || t183);
    if (t184 > 0)
        goto LAB46;

LAB47:    t236 = *((unsigned int *)t155);
    t237 = (~(t236));
    t238 = *((unsigned int *)t181);
    t239 = (t237 || t238);
    if (t239 > 0)
        goto LAB48;

LAB49:    if (*((unsigned int *)t181) > 0)
        goto LAB50;

LAB51:    if (*((unsigned int *)t155) > 0)
        goto LAB52;

LAB53:    memcpy(t154, t240, 8);

LAB54:    goto LAB32;

LAB33:    xsi_vlog_unsigned_bit_combine(t68, 32, t99, 32, t154, 32);
    goto LAB37;

LAB35:    memcpy(t68, t99, 8);
    goto LAB37;

LAB40:    t173 = (t158 + 4);
    *((unsigned int *)t158) = 1;
    *((unsigned int *)t173) = 1;
    goto LAB41;

LAB42:    *((unsigned int *)t155) = 1;
    goto LAB45;

LAB44:    t180 = (t155 + 4);
    *((unsigned int *)t155) = 1;
    *((unsigned int *)t180) = 1;
    goto LAB45;

LAB46:    t186 = (t0 + 2888);
    t187 = (t186 + 56U);
    t188 = *((char **)t187);
    t190 = (t0 + 2888);
    t191 = (t190 + 72U);
    t192 = *((char **)t191);
    t193 = (t0 + 2888);
    t194 = (t193 + 64U);
    t195 = *((char **)t194);
    t196 = (t0 + 1688U);
    t197 = *((char **)t196);
    xsi_vlog_generic_get_array_select_value(t189, 32, t188, t192, t195, 2, 1, t197, 10, 2);
    memset(t198, 0, 8);
    t196 = (t198 + 4);
    t199 = (t189 + 4);
    t200 = *((unsigned int *)t189);
    t201 = (t200 >> 0);
    *((unsigned int *)t198) = t201;
    t202 = *((unsigned int *)t199);
    t203 = (t202 >> 0);
    *((unsigned int *)t196) = t203;
    t204 = *((unsigned int *)t198);
    *((unsigned int *)t198) = (t204 & 65535U);
    t205 = *((unsigned int *)t196);
    *((unsigned int *)t196) = (t205 & 65535U);
    t207 = (t0 + 1848U);
    t208 = *((char **)t207);
    memset(t206, 0, 8);
    t207 = (t206 + 4);
    t209 = (t208 + 4);
    t210 = *((unsigned int *)t208);
    t211 = (t210 >> 0);
    *((unsigned int *)t206) = t211;
    t212 = *((unsigned int *)t209);
    t213 = (t212 >> 0);
    *((unsigned int *)t207) = t213;
    t214 = *((unsigned int *)t206);
    *((unsigned int *)t206) = (t214 & 255U);
    t215 = *((unsigned int *)t207);
    *((unsigned int *)t207) = (t215 & 255U);
    t216 = (t0 + 2888);
    t217 = (t216 + 56U);
    t218 = *((char **)t217);
    t220 = (t0 + 2888);
    t221 = (t220 + 72U);
    t222 = *((char **)t221);
    t223 = (t0 + 2888);
    t224 = (t223 + 64U);
    t225 = *((char **)t224);
    t226 = (t0 + 1688U);
    t227 = *((char **)t226);
    xsi_vlog_generic_get_array_select_value(t219, 32, t218, t222, t225, 2, 1, t227, 10, 2);
    memset(t228, 0, 8);
    t226 = (t228 + 4);
    t229 = (t219 + 4);
    t230 = *((unsigned int *)t219);
    t231 = (t230 >> 24);
    *((unsigned int *)t228) = t231;
    t232 = *((unsigned int *)t229);
    t233 = (t232 >> 24);
    *((unsigned int *)t226) = t233;
    t234 = *((unsigned int *)t228);
    *((unsigned int *)t228) = (t234 & 255U);
    t235 = *((unsigned int *)t226);
    *((unsigned int *)t226) = (t235 & 255U);
    xsi_vlogtype_concat(t185, 32, 32, 3U, t228, 8, t206, 8, t198, 16);
    goto LAB47;

LAB48:    t242 = (t0 + 1528U);
    t243 = *((char **)t242);
    t242 = ((char*)((ng7)));
    memset(t244, 0, 8);
    t245 = (t243 + 4);
    t246 = (t242 + 4);
    t247 = *((unsigned int *)t243);
    t248 = *((unsigned int *)t242);
    t249 = (t247 ^ t248);
    t250 = *((unsigned int *)t245);
    t251 = *((unsigned int *)t246);
    t252 = (t250 ^ t251);
    t253 = (t249 | t252);
    t254 = *((unsigned int *)t245);
    t255 = *((unsigned int *)t246);
    t256 = (t254 | t255);
    t257 = (~(t256));
    t258 = (t253 & t257);
    if (t258 != 0)
        goto LAB58;

LAB55:    if (t256 != 0)
        goto LAB57;

LAB56:    *((unsigned int *)t244) = 1;

LAB58:    memset(t241, 0, 8);
    t260 = (t244 + 4);
    t261 = *((unsigned int *)t260);
    t262 = (~(t261));
    t263 = *((unsigned int *)t244);
    t264 = (t263 & t262);
    t265 = (t264 & 1U);
    if (t265 != 0)
        goto LAB59;

LAB60:    if (*((unsigned int *)t260) != 0)
        goto LAB61;

LAB62:    t267 = (t241 + 4);
    t268 = *((unsigned int *)t241);
    t269 = *((unsigned int *)t267);
    t270 = (t268 || t269);
    if (t270 > 0)
        goto LAB63;

LAB64:    t302 = *((unsigned int *)t241);
    t303 = (~(t302));
    t304 = *((unsigned int *)t267);
    t305 = (t303 || t304);
    if (t305 > 0)
        goto LAB65;

LAB66:    if (*((unsigned int *)t267) > 0)
        goto LAB67;

LAB68:    if (*((unsigned int *)t241) > 0)
        goto LAB69;

LAB70:    memcpy(t240, t306, 8);

LAB71:    goto LAB49;

LAB50:    xsi_vlog_unsigned_bit_combine(t154, 32, t185, 32, t240, 32);
    goto LAB54;

LAB52:    memcpy(t154, t185, 8);
    goto LAB54;

LAB57:    t259 = (t244 + 4);
    *((unsigned int *)t244) = 1;
    *((unsigned int *)t259) = 1;
    goto LAB58;

LAB59:    *((unsigned int *)t241) = 1;
    goto LAB62;

LAB61:    t266 = (t241 + 4);
    *((unsigned int *)t241) = 1;
    *((unsigned int *)t266) = 1;
    goto LAB62;

LAB63:    t272 = (t0 + 2888);
    t273 = (t272 + 56U);
    t274 = *((char **)t273);
    t276 = (t0 + 2888);
    t277 = (t276 + 72U);
    t278 = *((char **)t277);
    t279 = (t0 + 2888);
    t280 = (t279 + 64U);
    t281 = *((char **)t280);
    t282 = (t0 + 1688U);
    t283 = *((char **)t282);
    xsi_vlog_generic_get_array_select_value(t275, 32, t274, t278, t281, 2, 1, t283, 10, 2);
    memset(t284, 0, 8);
    t282 = (t284 + 4);
    t285 = (t275 + 4);
    t286 = *((unsigned int *)t275);
    t287 = (t286 >> 0);
    *((unsigned int *)t284) = t287;
    t288 = *((unsigned int *)t285);
    t289 = (t288 >> 0);
    *((unsigned int *)t282) = t289;
    t290 = *((unsigned int *)t284);
    *((unsigned int *)t284) = (t290 & 16777215U);
    t291 = *((unsigned int *)t282);
    *((unsigned int *)t282) = (t291 & 16777215U);
    t293 = (t0 + 1848U);
    t294 = *((char **)t293);
    memset(t292, 0, 8);
    t293 = (t292 + 4);
    t295 = (t294 + 4);
    t296 = *((unsigned int *)t294);
    t297 = (t296 >> 0);
    *((unsigned int *)t292) = t297;
    t298 = *((unsigned int *)t295);
    t299 = (t298 >> 0);
    *((unsigned int *)t293) = t299;
    t300 = *((unsigned int *)t292);
    *((unsigned int *)t292) = (t300 & 255U);
    t301 = *((unsigned int *)t293);
    *((unsigned int *)t293) = (t301 & 255U);
    xsi_vlogtype_concat(t271, 32, 32, 2U, t292, 8, t284, 24);
    goto LAB64;

LAB65:    t308 = (t0 + 1528U);
    t309 = *((char **)t308);
    t308 = ((char*)((ng8)));
    memset(t310, 0, 8);
    t311 = (t309 + 4);
    t312 = (t308 + 4);
    t313 = *((unsigned int *)t309);
    t314 = *((unsigned int *)t308);
    t315 = (t313 ^ t314);
    t316 = *((unsigned int *)t311);
    t317 = *((unsigned int *)t312);
    t318 = (t316 ^ t317);
    t319 = (t315 | t318);
    t320 = *((unsigned int *)t311);
    t321 = *((unsigned int *)t312);
    t322 = (t320 | t321);
    t323 = (~(t322));
    t324 = (t319 & t323);
    if (t324 != 0)
        goto LAB75;

LAB72:    if (t322 != 0)
        goto LAB74;

LAB73:    *((unsigned int *)t310) = 1;

LAB75:    memset(t307, 0, 8);
    t326 = (t310 + 4);
    t327 = *((unsigned int *)t326);
    t328 = (~(t327));
    t329 = *((unsigned int *)t310);
    t330 = (t329 & t328);
    t331 = (t330 & 1U);
    if (t331 != 0)
        goto LAB76;

LAB77:    if (*((unsigned int *)t326) != 0)
        goto LAB78;

LAB79:    t333 = (t307 + 4);
    t334 = *((unsigned int *)t307);
    t335 = *((unsigned int *)t333);
    t336 = (t334 || t335);
    if (t336 > 0)
        goto LAB80;

LAB81:    t368 = *((unsigned int *)t307);
    t369 = (~(t368));
    t370 = *((unsigned int *)t333);
    t371 = (t369 || t370);
    if (t371 > 0)
        goto LAB82;

LAB83:    if (*((unsigned int *)t333) > 0)
        goto LAB84;

LAB85:    if (*((unsigned int *)t307) > 0)
        goto LAB86;

LAB87:    memcpy(t306, t372, 8);

LAB88:    goto LAB66;

LAB67:    xsi_vlog_unsigned_bit_combine(t240, 32, t271, 32, t306, 32);
    goto LAB71;

LAB69:    memcpy(t240, t271, 8);
    goto LAB71;

LAB74:    t325 = (t310 + 4);
    *((unsigned int *)t310) = 1;
    *((unsigned int *)t325) = 1;
    goto LAB75;

LAB76:    *((unsigned int *)t307) = 1;
    goto LAB79;

LAB78:    t332 = (t307 + 4);
    *((unsigned int *)t307) = 1;
    *((unsigned int *)t332) = 1;
    goto LAB79;

LAB80:    t339 = (t0 + 1848U);
    t340 = *((char **)t339);
    memset(t338, 0, 8);
    t339 = (t338 + 4);
    t341 = (t340 + 4);
    t342 = *((unsigned int *)t340);
    t343 = (t342 >> 0);
    *((unsigned int *)t338) = t343;
    t344 = *((unsigned int *)t341);
    t345 = (t344 >> 0);
    *((unsigned int *)t339) = t345;
    t346 = *((unsigned int *)t338);
    *((unsigned int *)t338) = (t346 & 65535U);
    t347 = *((unsigned int *)t339);
    *((unsigned int *)t339) = (t347 & 65535U);
    t348 = (t0 + 2888);
    t349 = (t348 + 56U);
    t350 = *((char **)t349);
    t352 = (t0 + 2888);
    t353 = (t352 + 72U);
    t354 = *((char **)t353);
    t355 = (t0 + 2888);
    t356 = (t355 + 64U);
    t357 = *((char **)t356);
    t358 = (t0 + 1688U);
    t359 = *((char **)t358);
    xsi_vlog_generic_get_array_select_value(t351, 32, t350, t354, t357, 2, 1, t359, 10, 2);
    memset(t360, 0, 8);
    t358 = (t360 + 4);
    t361 = (t351 + 4);
    t362 = *((unsigned int *)t351);
    t363 = (t362 >> 16);
    *((unsigned int *)t360) = t363;
    t364 = *((unsigned int *)t361);
    t365 = (t364 >> 16);
    *((unsigned int *)t358) = t365;
    t366 = *((unsigned int *)t360);
    *((unsigned int *)t360) = (t366 & 65535U);
    t367 = *((unsigned int *)t358);
    *((unsigned int *)t358) = (t367 & 65535U);
    xsi_vlogtype_concat(t337, 32, 32, 2U, t360, 16, t338, 16);
    goto LAB81;

LAB82:    t374 = (t0 + 1528U);
    t375 = *((char **)t374);
    t374 = ((char*)((ng9)));
    memset(t376, 0, 8);
    t377 = (t375 + 4);
    t378 = (t374 + 4);
    t379 = *((unsigned int *)t375);
    t380 = *((unsigned int *)t374);
    t381 = (t379 ^ t380);
    t382 = *((unsigned int *)t377);
    t383 = *((unsigned int *)t378);
    t384 = (t382 ^ t383);
    t385 = (t381 | t384);
    t386 = *((unsigned int *)t377);
    t387 = *((unsigned int *)t378);
    t388 = (t386 | t387);
    t389 = (~(t388));
    t390 = (t385 & t389);
    if (t390 != 0)
        goto LAB92;

LAB89:    if (t388 != 0)
        goto LAB91;

LAB90:    *((unsigned int *)t376) = 1;

LAB92:    memset(t373, 0, 8);
    t392 = (t376 + 4);
    t393 = *((unsigned int *)t392);
    t394 = (~(t393));
    t395 = *((unsigned int *)t376);
    t396 = (t395 & t394);
    t397 = (t396 & 1U);
    if (t397 != 0)
        goto LAB93;

LAB94:    if (*((unsigned int *)t392) != 0)
        goto LAB95;

LAB96:    t399 = (t373 + 4);
    t400 = *((unsigned int *)t373);
    t401 = *((unsigned int *)t399);
    t402 = (t400 || t401);
    if (t402 > 0)
        goto LAB97;

LAB98:    t434 = *((unsigned int *)t373);
    t435 = (~(t434));
    t436 = *((unsigned int *)t399);
    t437 = (t435 || t436);
    if (t437 > 0)
        goto LAB99;

LAB100:    if (*((unsigned int *)t399) > 0)
        goto LAB101;

LAB102:    if (*((unsigned int *)t373) > 0)
        goto LAB103;

LAB104:    memcpy(t372, t439, 8);

LAB105:    goto LAB83;

LAB84:    xsi_vlog_unsigned_bit_combine(t306, 32, t337, 32, t372, 32);
    goto LAB88;

LAB86:    memcpy(t306, t337, 8);
    goto LAB88;

LAB91:    t391 = (t376 + 4);
    *((unsigned int *)t376) = 1;
    *((unsigned int *)t391) = 1;
    goto LAB92;

LAB93:    *((unsigned int *)t373) = 1;
    goto LAB96;

LAB95:    t398 = (t373 + 4);
    *((unsigned int *)t373) = 1;
    *((unsigned int *)t398) = 1;
    goto LAB96;

LAB97:    t404 = (t0 + 2888);
    t405 = (t404 + 56U);
    t406 = *((char **)t405);
    t408 = (t0 + 2888);
    t409 = (t408 + 72U);
    t410 = *((char **)t409);
    t411 = (t0 + 2888);
    t412 = (t411 + 64U);
    t413 = *((char **)t412);
    t414 = (t0 + 1688U);
    t415 = *((char **)t414);
    xsi_vlog_generic_get_array_select_value(t407, 32, t406, t410, t413, 2, 1, t415, 10, 2);
    memset(t416, 0, 8);
    t414 = (t416 + 4);
    t417 = (t407 + 4);
    t418 = *((unsigned int *)t407);
    t419 = (t418 >> 0);
    *((unsigned int *)t416) = t419;
    t420 = *((unsigned int *)t417);
    t421 = (t420 >> 0);
    *((unsigned int *)t414) = t421;
    t422 = *((unsigned int *)t416);
    *((unsigned int *)t416) = (t422 & 65535U);
    t423 = *((unsigned int *)t414);
    *((unsigned int *)t414) = (t423 & 65535U);
    t425 = (t0 + 1848U);
    t426 = *((char **)t425);
    memset(t424, 0, 8);
    t425 = (t424 + 4);
    t427 = (t426 + 4);
    t428 = *((unsigned int *)t426);
    t429 = (t428 >> 0);
    *((unsigned int *)t424) = t429;
    t430 = *((unsigned int *)t427);
    t431 = (t430 >> 0);
    *((unsigned int *)t425) = t431;
    t432 = *((unsigned int *)t424);
    *((unsigned int *)t424) = (t432 & 65535U);
    t433 = *((unsigned int *)t425);
    *((unsigned int *)t425) = (t433 & 65535U);
    xsi_vlogtype_concat(t403, 32, 32, 2U, t424, 16, t416, 16);
    goto LAB98;

LAB99:    t438 = (t0 + 1848U);
    t439 = *((char **)t438);
    goto LAB100;

LAB101:    xsi_vlog_unsigned_bit_combine(t372, 32, t403, 32, t439, 32);
    goto LAB105;

LAB103:    memcpy(t372, t403, 8);
    goto LAB105;

}

static void Always_52_3(char *t0)
{
    char t13[8];
    char t15[8];
    char t16[8];
    char t37[16];
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

LAB0:    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(52, ng0);
    t2 = (t0 + 5064);
    *((int *)t2) = 1;
    t3 = (t0 + 4744);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(52, ng0);

LAB5:    xsi_set_current_line(53, ng0);
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

LAB7:    xsi_set_current_line(56, ng0);
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

LAB6:    xsi_set_current_line(54, ng0);
    xsi_set_current_line(54, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 3048);
    xsi_vlogvar_assign_value(t12, t11, 0, 0, 32);

LAB9:    t2 = (t0 + 3048);
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

LAB10:    xsi_set_current_line(55, ng0);
    t12 = ((char*)((ng3)));
    t14 = (t0 + 2888);
    t17 = (t0 + 2888);
    t18 = (t17 + 72U);
    t19 = *((char **)t18);
    t20 = (t0 + 2888);
    t21 = (t20 + 64U);
    t22 = *((char **)t21);
    t23 = (t0 + 3048);
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

LAB13:    xsi_set_current_line(54, ng0);
    t2 = (t0 + 3048);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t13, 0, 8);
    xsi_vlog_signed_add(t13, 32, t4, 32, t5, 32);
    t11 = (t0 + 3048);
    xsi_vlogvar_assign_value(t11, t13, 0, 0, 32);
    goto LAB9;

LAB12:    t33 = *((unsigned int *)t15);
    t34 = *((unsigned int *)t16);
    t35 = (t33 - t34);
    t36 = (t35 + 1);
    xsi_vlogvar_assign_value(t14, t12, 0, *((unsigned int *)t16), t36);
    goto LAB13;

LAB14:    xsi_set_current_line(56, ng0);

LAB17:    xsi_set_current_line(80, ng0);
    t4 = (t0 + 2488U);
    t5 = *((char **)t4);
    t4 = (t0 + 2888);
    t11 = (t0 + 2888);
    t12 = (t11 + 72U);
    t14 = *((char **)t12);
    t17 = (t0 + 2888);
    t18 = (t17 + 64U);
    t19 = *((char **)t18);
    t20 = (t0 + 1688U);
    t21 = *((char **)t20);
    xsi_vlog_generic_convert_array_indices(t13, t15, t14, t19, 2, 1, t21, 10, 2);
    t20 = (t13 + 4);
    t27 = *((unsigned int *)t20);
    t28 = (!(t27));
    t22 = (t15 + 4);
    t30 = *((unsigned int *)t22);
    t31 = (!(t30));
    t32 = (t28 && t31);
    if (t32 == 1)
        goto LAB18;

LAB19:    xsi_set_current_line(81, ng0);
    t2 = xsi_vlog_time(t37, 1000.0000000000000, 1000.0000000000000);
    t3 = (t0 + 2008U);
    t4 = *((char **)t3);
    t3 = (t0 + 2168U);
    t5 = *((char **)t3);
    t3 = (t0 + 2888);
    t11 = (t3 + 56U);
    t12 = *((char **)t11);
    t14 = (t0 + 2888);
    t17 = (t14 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2888);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1688U);
    t23 = *((char **)t22);
    xsi_vlog_generic_get_array_select_value(t13, 32, t12, t18, t21, 2, 1, t23, 10, 2);
    xsi_vlogfile_write(1, 0, 0, ng10, 5, t0, (char)118, t37, 64, (char)118, t4, 32, (char)118, t5, 32, (char)118, t13, 32);
    goto LAB16;

LAB18:    t33 = *((unsigned int *)t13);
    t34 = *((unsigned int *)t15);
    t35 = (t33 - t34);
    t36 = (t35 + 1);
    xsi_vlogvar_assign_value(t4, t5, 0, *((unsigned int *)t15), t36);
    goto LAB19;

}


extern void work_m_00000000000426596185_0010801604_init()
{
	static char *pe[] = {(void *)Initial_37_0,(void *)Cont_42_1,(void *)Cont_44_2,(void *)Always_52_3};
	xsi_register_didat("work_m_00000000000426596185_0010801604", "isim/mipstb_isim_beh.exe.sim/work/m_00000000000426596185_0010801604.didat");
	xsi_register_executes(pe);
}
