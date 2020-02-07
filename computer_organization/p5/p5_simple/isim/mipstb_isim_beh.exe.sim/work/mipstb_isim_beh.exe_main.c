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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003139372920_3383896982_init();
    work_m_00000000002032792504_3037376393_init();
    work_m_00000000000362893462_2104361617_init();
    work_m_00000000002794993459_2885957937_init();
    work_m_00000000002449127215_0555905401_init();
    work_m_00000000000313262135_1697392497_init();
    work_m_00000000001090294822_3146453351_init();
    work_m_00000000000306948156_4127636709_init();
    work_m_00000000003471271055_4241813833_init();
    work_m_00000000002569140895_0174666247_init();
    work_m_00000000001431614818_2577274396_init();
    work_m_00000000001356226597_2725559894_init();
    work_m_00000000002222036630_2956445220_init();
    work_m_00000000002269270816_0078821941_init();
    work_m_00000000001714191833_2630121153_init();
    work_m_00000000001448527882_0010801604_init();
    work_m_00000000002141101416_4191175503_init();
    work_m_00000000002573988843_3043697015_init();
    work_m_00000000002222036630_0071904933_init();
    work_m_00000000000642779543_3210399350_init();
    work_m_00000000001937123446_3877310806_init();
    work_m_00000000002047498008_0594944182_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000002047498008_0594944182");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
