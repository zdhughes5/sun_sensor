#include "sun_sensor_packet.hpp"

// ---------------------------------------------------------------------------
// Byte offsets — taken verbatim from table_parsed.json ("start_byte" field).
// Note: lat_gps (688) and lon_gps (694) overlap by 2 bytes in the spec;
// we faithfully reproduce the published offsets.
// ---------------------------------------------------------------------------
namespace {
    // PSS 0
    constexpr size_t OFF_V_X1_PSS_0    = 0;
    constexpr size_t OFF_V_X2_PSS_0    = 8;
    constexpr size_t OFF_V_Y1_PSS_0    = 16;
    constexpr size_t OFF_V_Y2_PSS_0    = 24;
    constexpr size_t OFF_V_SUM_PSS_0   = 32;
    constexpr size_t OFF_THRESH_PSS_0  = 40;
    constexpr size_t OFF_RADIUS_PSS_0  = 48;
    constexpr size_t OFF_GOOD_PSS_0    = 56;
    constexpr size_t OFF_X_RAW_PSS_0   = 57;
    constexpr size_t OFF_Y_RAW_PSS_0   = 65;
    constexpr size_t OFF_X_CORR_PSS_0  = 73;
    constexpr size_t OFF_Y_CORR_PSS_0  = 81;
    constexpr size_t OFF_AZ_PSS_0      = 89;
    constexpr size_t OFF_EL_PSS_0      = 97;
    constexpr size_t OFF_VALID_PSS_0   = 105;

    // PSS 1
    constexpr size_t OFF_V_X1_PSS_1    = 106;
    constexpr size_t OFF_V_X2_PSS_1    = 114;
    constexpr size_t OFF_V_Y1_PSS_1    = 122;
    constexpr size_t OFF_V_Y2_PSS_1    = 130;
    constexpr size_t OFF_V_SUM_PSS_1   = 138;
    constexpr size_t OFF_THRESH_PSS_1  = 146;
    constexpr size_t OFF_RADIUS_PSS_1  = 154;
    constexpr size_t OFF_GOOD_PSS_1    = 162;
    constexpr size_t OFF_X_RAW_PSS_1   = 163;
    constexpr size_t OFF_Y_RAW_PSS_1   = 171;
    constexpr size_t OFF_X_CORR_PSS_1  = 179;
    constexpr size_t OFF_Y_CORR_PSS_1  = 187;
    constexpr size_t OFF_AZ_PSS_1      = 195;
    constexpr size_t OFF_EL_PSS_1      = 203;
    constexpr size_t OFF_VALID_PSS_1   = 211;

    // PSS 2
    constexpr size_t OFF_V_X1_PSS_2    = 212;
    constexpr size_t OFF_V_X2_PSS_2    = 220;
    constexpr size_t OFF_V_Y1_PSS_2    = 228;
    constexpr size_t OFF_V_Y2_PSS_2    = 236;
    constexpr size_t OFF_V_SUM_PSS_2   = 244;
    constexpr size_t OFF_THRESH_PSS_2  = 252;
    constexpr size_t OFF_RADIUS_PSS_2  = 260;
    constexpr size_t OFF_GOOD_PSS_2    = 268;
    constexpr size_t OFF_X_RAW_PSS_2   = 269;
    constexpr size_t OFF_Y_RAW_PSS_2   = 277;
    constexpr size_t OFF_X_CORR_PSS_2  = 285;
    constexpr size_t OFF_Y_CORR_PSS_2  = 293;
    constexpr size_t OFF_AZ_PSS_2      = 301;
    constexpr size_t OFF_EL_PSS_2      = 309;
    constexpr size_t OFF_VALID_PSS_2   = 317;

    // PSS 3
    constexpr size_t OFF_V_X1_PSS_3    = 318;
    constexpr size_t OFF_V_X2_PSS_3    = 326;
    constexpr size_t OFF_V_Y1_PSS_3    = 334;
    constexpr size_t OFF_V_Y2_PSS_3    = 342;
    constexpr size_t OFF_V_SUM_PSS_3   = 350;
    constexpr size_t OFF_THRESH_PSS_3  = 358;
    constexpr size_t OFF_RADIUS_PSS_3  = 366;
    constexpr size_t OFF_GOOD_PSS_3    = 374;
    constexpr size_t OFF_X_RAW_PSS_3   = 375;
    constexpr size_t OFF_Y_RAW_PSS_3   = 383;
    constexpr size_t OFF_X_CORR_PSS_3  = 391;
    constexpr size_t OFF_Y_CORR_PSS_3  = 399;
    constexpr size_t OFF_AZ_PSS_3      = 407;
    constexpr size_t OFF_EL_PSS_3      = 415;
    constexpr size_t OFF_VALID_PSS_3   = 423;

    // PSS 4
    constexpr size_t OFF_V_X1_PSS_4    = 424;
    constexpr size_t OFF_V_X2_PSS_4    = 432;
    constexpr size_t OFF_V_Y1_PSS_4    = 440;
    constexpr size_t OFF_V_Y2_PSS_4    = 448;
    constexpr size_t OFF_V_SUM_PSS_4   = 456;
    constexpr size_t OFF_THRESH_PSS_4  = 464;
    constexpr size_t OFF_RADIUS_PSS_4  = 472;
    constexpr size_t OFF_GOOD_PSS_4    = 480;
    constexpr size_t OFF_X_RAW_PSS_4   = 481;
    constexpr size_t OFF_Y_RAW_PSS_4   = 489;
    constexpr size_t OFF_X_CORR_PSS_4  = 497;
    constexpr size_t OFF_Y_CORR_PSS_4  = 505;
    constexpr size_t OFF_AZ_PSS_4      = 513;
    constexpr size_t OFF_EL_PSS_4      = 521;
    constexpr size_t OFF_VALID_PSS_4   = 529;

    // PSS 5
    constexpr size_t OFF_V_X1_PSS_5    = 530;
    constexpr size_t OFF_V_X2_PSS_5    = 538;
    constexpr size_t OFF_V_Y1_PSS_5    = 546;
    constexpr size_t OFF_V_Y2_PSS_5    = 554;
    constexpr size_t OFF_V_SUM_PSS_5   = 562;
    constexpr size_t OFF_THRESH_PSS_5  = 570;
    constexpr size_t OFF_RADIUS_PSS_5  = 578;
    constexpr size_t OFF_GOOD_PSS_5    = 586;
    constexpr size_t OFF_X_RAW_PSS_5   = 587;
    constexpr size_t OFF_Y_RAW_PSS_5   = 595;
    constexpr size_t OFF_X_CORR_PSS_5  = 603;
    constexpr size_t OFF_Y_CORR_PSS_5  = 611;
    constexpr size_t OFF_AZ_PSS_5      = 619;
    constexpr size_t OFF_EL_PSS_5      = 627;
    constexpr size_t OFF_VALID_PSS_5   = 635;

    // ADC boxcar sizes
    constexpr size_t OFF_BOXCAR_ADC_0  = 636;
    constexpr size_t OFF_BOXCAR_ADC_1  = 638;
    constexpr size_t OFF_BOXCAR_ADC_2  = 640;
    constexpr size_t OFF_BOXCAR_ADC_3  = 642;
    constexpr size_t OFF_BOXCAR_ADC_4  = 644;
    constexpr size_t OFF_BOXCAR_ADC_5  = 646;

    // Azimuth / elevation candidates
    constexpr size_t OFF_CURRENT_AZ    = 648;
    constexpr size_t OFF_OFFSET_AZ     = 656;
    constexpr size_t OFF_BEST_AZ       = 664;
    constexpr size_t OFF_BEST_EL       = 672;

    // GPS
    constexpr size_t OFF_TIMESTAMP_GPS = 680;
    constexpr size_t OFF_LAT_GPS       = 688;
    constexpr size_t OFF_LON_GPS       = 694;   // overlaps lat by 2 bytes per spec
    constexpr size_t OFF_ALT_GPS       = 704;
    constexpr size_t OFF_BAUD_GPS      = 712;
    constexpr size_t OFF_RA_SUN_GPS    = 716;
    constexpr size_t OFF_DEC_SUN_GPS   = 724;
    constexpr size_t OFF_AZ_SUN_GPS    = 732;
    constexpr size_t OFF_EL_SUN_GPS    = 740;
    constexpr size_t OFF_HA_SUN_GPS    = 748;

    // Array / table
    constexpr size_t OFF_ARRAY_TIP          = 756;
    constexpr size_t OFF_ARRAY_TILT         = 764;
    constexpr size_t OFF_POS_TABLE          = 772;
    constexpr size_t OFF_LAST_TIME_TABLE    = 780;
    constexpr size_t OFF_AT_TARGET_TABLE    = 788;
    constexpr size_t OFF_CMD_POSITION_TABLE = 789;
    constexpr size_t OFF_CMD_SPEED_TABLE    = 797;
    constexpr size_t OFF_SET_POS_TABLE      = 805;
    constexpr size_t OFF_CYCLE_START_TABLE  = 813;
    constexpr size_t OFF_CYCLE_END_TABLE    = 821;
    constexpr size_t OFF_CYCLES_LEFT_TABLE  = 829;
} // namespace

// ---------------------------------------------------------------------------
// parse()
// ---------------------------------------------------------------------------
bool SunSensorPacket::parse(const uint8_t* buf, size_t len)
{
    if (len < PACKET_SIZE) {
        return false;
    }

    // PSS 0
    v_x1_pss_0_   = rd<double>(buf, OFF_V_X1_PSS_0);
    v_x2_pss_0_   = rd<double>(buf, OFF_V_X2_PSS_0);
    v_y1_pss_0_   = rd<double>(buf, OFF_V_Y1_PSS_0);
    v_y2_pss_0_   = rd<double>(buf, OFF_V_Y2_PSS_0);
    v_sum_pss_0_  = rd<double>(buf, OFF_V_SUM_PSS_0);
    thresh_pss_0_ = rd<double>(buf, OFF_THRESH_PSS_0);
    radius_pss_0_ = rd<double>(buf, OFF_RADIUS_PSS_0);
    good_pss_0_   = rd<uint8_t>(buf, OFF_GOOD_PSS_0);
    x_raw_pss_0_  = rd<double>(buf, OFF_X_RAW_PSS_0);
    y_raw_pss_0_  = rd<double>(buf, OFF_Y_RAW_PSS_0);
    x_corr_pss_0_ = rd<double>(buf, OFF_X_CORR_PSS_0);
    y_corr_pss_0_ = rd<double>(buf, OFF_Y_CORR_PSS_0);
    az_pss_0_     = rd<double>(buf, OFF_AZ_PSS_0);
    el_pss_0_     = rd<double>(buf, OFF_EL_PSS_0);
    valid_pss_0_  = rd<uint8_t>(buf, OFF_VALID_PSS_0);

    // PSS 1
    v_x1_pss_1_   = rd<double>(buf, OFF_V_X1_PSS_1);
    v_x2_pss_1_   = rd<double>(buf, OFF_V_X2_PSS_1);
    v_y1_pss_1_   = rd<double>(buf, OFF_V_Y1_PSS_1);
    v_y2_pss_1_   = rd<double>(buf, OFF_V_Y2_PSS_1);
    v_sum_pss_1_  = rd<double>(buf, OFF_V_SUM_PSS_1);
    thresh_pss_1_ = rd<double>(buf, OFF_THRESH_PSS_1);
    radius_pss_1_ = rd<double>(buf, OFF_RADIUS_PSS_1);
    good_pss_1_   = rd<uint8_t>(buf, OFF_GOOD_PSS_1);
    x_raw_pss_1_  = rd<double>(buf, OFF_X_RAW_PSS_1);
    y_raw_pss_1_  = rd<double>(buf, OFF_Y_RAW_PSS_1);
    x_corr_pss_1_ = rd<double>(buf, OFF_X_CORR_PSS_1);
    y_corr_pss_1_ = rd<double>(buf, OFF_Y_CORR_PSS_1);
    az_pss_1_     = rd<double>(buf, OFF_AZ_PSS_1);
    el_pss_1_     = rd<double>(buf, OFF_EL_PSS_1);
    valid_pss_1_  = rd<uint8_t>(buf, OFF_VALID_PSS_1);

    // PSS 2
    v_x1_pss_2_   = rd<double>(buf, OFF_V_X1_PSS_2);
    v_x2_pss_2_   = rd<double>(buf, OFF_V_X2_PSS_2);
    v_y1_pss_2_   = rd<double>(buf, OFF_V_Y1_PSS_2);
    v_y2_pss_2_   = rd<double>(buf, OFF_V_Y2_PSS_2);
    v_sum_pss_2_  = rd<double>(buf, OFF_V_SUM_PSS_2);
    thresh_pss_2_ = rd<double>(buf, OFF_THRESH_PSS_2);
    radius_pss_2_ = rd<double>(buf, OFF_RADIUS_PSS_2);
    good_pss_2_   = rd<uint8_t>(buf, OFF_GOOD_PSS_2);
    x_raw_pss_2_  = rd<double>(buf, OFF_X_RAW_PSS_2);
    y_raw_pss_2_  = rd<double>(buf, OFF_Y_RAW_PSS_2);
    x_corr_pss_2_ = rd<double>(buf, OFF_X_CORR_PSS_2);
    y_corr_pss_2_ = rd<double>(buf, OFF_Y_CORR_PSS_2);
    az_pss_2_     = rd<double>(buf, OFF_AZ_PSS_2);
    el_pss_2_     = rd<double>(buf, OFF_EL_PSS_2);
    valid_pss_2_  = rd<uint8_t>(buf, OFF_VALID_PSS_2);

    // PSS 3
    v_x1_pss_3_   = rd<double>(buf, OFF_V_X1_PSS_3);
    v_x2_pss_3_   = rd<double>(buf, OFF_V_X2_PSS_3);
    v_y1_pss_3_   = rd<double>(buf, OFF_V_Y1_PSS_3);
    v_y2_pss_3_   = rd<double>(buf, OFF_V_Y2_PSS_3);
    v_sum_pss_3_  = rd<double>(buf, OFF_V_SUM_PSS_3);
    thresh_pss_3_ = rd<double>(buf, OFF_THRESH_PSS_3);
    radius_pss_3_ = rd<double>(buf, OFF_RADIUS_PSS_3);
    good_pss_3_   = rd<uint8_t>(buf, OFF_GOOD_PSS_3);
    x_raw_pss_3_  = rd<double>(buf, OFF_X_RAW_PSS_3);
    y_raw_pss_3_  = rd<double>(buf, OFF_Y_RAW_PSS_3);
    x_corr_pss_3_ = rd<double>(buf, OFF_X_CORR_PSS_3);
    y_corr_pss_3_ = rd<double>(buf, OFF_Y_CORR_PSS_3);
    az_pss_3_     = rd<double>(buf, OFF_AZ_PSS_3);
    el_pss_3_     = rd<double>(buf, OFF_EL_PSS_3);
    valid_pss_3_  = rd<uint8_t>(buf, OFF_VALID_PSS_3);

    // PSS 4
    v_x1_pss_4_   = rd<double>(buf, OFF_V_X1_PSS_4);
    v_x2_pss_4_   = rd<double>(buf, OFF_V_X2_PSS_4);
    v_y1_pss_4_   = rd<double>(buf, OFF_V_Y1_PSS_4);
    v_y2_pss_4_   = rd<double>(buf, OFF_V_Y2_PSS_4);
    v_sum_pss_4_  = rd<double>(buf, OFF_V_SUM_PSS_4);
    thresh_pss_4_ = rd<double>(buf, OFF_THRESH_PSS_4);
    radius_pss_4_ = rd<double>(buf, OFF_RADIUS_PSS_4);
    good_pss_4_   = rd<uint8_t>(buf, OFF_GOOD_PSS_4);
    x_raw_pss_4_  = rd<double>(buf, OFF_X_RAW_PSS_4);
    y_raw_pss_4_  = rd<double>(buf, OFF_Y_RAW_PSS_4);
    x_corr_pss_4_ = rd<double>(buf, OFF_X_CORR_PSS_4);
    y_corr_pss_4_ = rd<double>(buf, OFF_Y_CORR_PSS_4);
    az_pss_4_     = rd<double>(buf, OFF_AZ_PSS_4);
    el_pss_4_     = rd<double>(buf, OFF_EL_PSS_4);
    valid_pss_4_  = rd<uint8_t>(buf, OFF_VALID_PSS_4);

    // PSS 5
    v_x1_pss_5_   = rd<double>(buf, OFF_V_X1_PSS_5);
    v_x2_pss_5_   = rd<double>(buf, OFF_V_X2_PSS_5);
    v_y1_pss_5_   = rd<double>(buf, OFF_V_Y1_PSS_5);
    v_y2_pss_5_   = rd<double>(buf, OFF_V_Y2_PSS_5);
    v_sum_pss_5_  = rd<double>(buf, OFF_V_SUM_PSS_5);
    thresh_pss_5_ = rd<double>(buf, OFF_THRESH_PSS_5);
    radius_pss_5_ = rd<double>(buf, OFF_RADIUS_PSS_5);
    good_pss_5_   = rd<uint8_t>(buf, OFF_GOOD_PSS_5);
    x_raw_pss_5_  = rd<double>(buf, OFF_X_RAW_PSS_5);
    y_raw_pss_5_  = rd<double>(buf, OFF_Y_RAW_PSS_5);
    x_corr_pss_5_ = rd<double>(buf, OFF_X_CORR_PSS_5);
    y_corr_pss_5_ = rd<double>(buf, OFF_Y_CORR_PSS_5);
    az_pss_5_     = rd<double>(buf, OFF_AZ_PSS_5);
    el_pss_5_     = rd<double>(buf, OFF_EL_PSS_5);
    valid_pss_5_  = rd<uint8_t>(buf, OFF_VALID_PSS_5);

    // ADC boxcar sizes
    boxcar_size_adc_0_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_0);
    boxcar_size_adc_1_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_1);
    boxcar_size_adc_2_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_2);
    boxcar_size_adc_3_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_3);
    boxcar_size_adc_4_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_4);
    boxcar_size_adc_5_ = rd<uint16_t>(buf, OFF_BOXCAR_ADC_5);

    // Azimuth / elevation candidates
    current_az_ = rd<double>(buf, OFF_CURRENT_AZ);
    offset_az_  = rd<double>(buf, OFF_OFFSET_AZ);
    best_az_    = rd<double>(buf, OFF_BEST_AZ);
    best_el_    = rd<double>(buf, OFF_BEST_EL);

    // GPS
    timestamp_gps_ = rd<double>(buf, OFF_TIMESTAMP_GPS);
    lat_gps_        = rd<double>(buf, OFF_LAT_GPS);
    lon_gps_        = rd<double>(buf, OFF_LON_GPS);
    alt_gps_        = rd<double>(buf, OFF_ALT_GPS);
    baud_gps_       = rd<int32_t>(buf, OFF_BAUD_GPS);
    ra_sun_gps_     = rd<double>(buf, OFF_RA_SUN_GPS);
    dec_sun_gps_    = rd<double>(buf, OFF_DEC_SUN_GPS);
    az_sun_gps_     = rd<double>(buf, OFF_AZ_SUN_GPS);
    el_sun_gps_     = rd<double>(buf, OFF_EL_SUN_GPS);
    ha_sun_gps_     = rd<double>(buf, OFF_HA_SUN_GPS);

    // Array / table
    array_tip_          = rd<double>(buf, OFF_ARRAY_TIP);
    array_tilt_         = rd<double>(buf, OFF_ARRAY_TILT);
    pos_table_          = rd<double>(buf, OFF_POS_TABLE);
    last_time_table_    = rd<double>(buf, OFF_LAST_TIME_TABLE);
    at_target_table_    = rd<uint8_t>(buf, OFF_AT_TARGET_TABLE);
    cmd_position_table_ = rd<double>(buf, OFF_CMD_POSITION_TABLE);
    cmd_speed_table_    = rd<double>(buf, OFF_CMD_SPEED_TABLE);
    set_pos_table_      = rd<double>(buf, OFF_SET_POS_TABLE);
    cycle_start_table_  = rd<double>(buf, OFF_CYCLE_START_TABLE);
    cycle_end_table_    = rd<double>(buf, OFF_CYCLE_END_TABLE);
    cycles_left_table_  = rd<int32_t>(buf, OFF_CYCLES_LEFT_TABLE);

    return true;
}

// ---------------------------------------------------------------------------
// serialize()
// ---------------------------------------------------------------------------
size_t SunSensorPacket::serialize(uint8_t* buf, size_t len) const
{
    if (len < PACKET_SIZE) {
        return 0;
    }

    // PSS 0
    wr(buf, OFF_V_X1_PSS_0,   v_x1_pss_0_);
    wr(buf, OFF_V_X2_PSS_0,   v_x2_pss_0_);
    wr(buf, OFF_V_Y1_PSS_0,   v_y1_pss_0_);
    wr(buf, OFF_V_Y2_PSS_0,   v_y2_pss_0_);
    wr(buf, OFF_V_SUM_PSS_0,  v_sum_pss_0_);
    wr(buf, OFF_THRESH_PSS_0, thresh_pss_0_);
    wr(buf, OFF_RADIUS_PSS_0, radius_pss_0_);
    wr(buf, OFF_GOOD_PSS_0,   good_pss_0_);
    wr(buf, OFF_X_RAW_PSS_0,  x_raw_pss_0_);
    wr(buf, OFF_Y_RAW_PSS_0,  y_raw_pss_0_);
    wr(buf, OFF_X_CORR_PSS_0, x_corr_pss_0_);
    wr(buf, OFF_Y_CORR_PSS_0, y_corr_pss_0_);
    wr(buf, OFF_AZ_PSS_0,     az_pss_0_);
    wr(buf, OFF_EL_PSS_0,     el_pss_0_);
    wr(buf, OFF_VALID_PSS_0,  valid_pss_0_);

    // PSS 1
    wr(buf, OFF_V_X1_PSS_1,   v_x1_pss_1_);
    wr(buf, OFF_V_X2_PSS_1,   v_x2_pss_1_);
    wr(buf, OFF_V_Y1_PSS_1,   v_y1_pss_1_);
    wr(buf, OFF_V_Y2_PSS_1,   v_y2_pss_1_);
    wr(buf, OFF_V_SUM_PSS_1,  v_sum_pss_1_);
    wr(buf, OFF_THRESH_PSS_1, thresh_pss_1_);
    wr(buf, OFF_RADIUS_PSS_1, radius_pss_1_);
    wr(buf, OFF_GOOD_PSS_1,   good_pss_1_);
    wr(buf, OFF_X_RAW_PSS_1,  x_raw_pss_1_);
    wr(buf, OFF_Y_RAW_PSS_1,  y_raw_pss_1_);
    wr(buf, OFF_X_CORR_PSS_1, x_corr_pss_1_);
    wr(buf, OFF_Y_CORR_PSS_1, y_corr_pss_1_);
    wr(buf, OFF_AZ_PSS_1,     az_pss_1_);
    wr(buf, OFF_EL_PSS_1,     el_pss_1_);
    wr(buf, OFF_VALID_PSS_1,  valid_pss_1_);

    // PSS 2
    wr(buf, OFF_V_X1_PSS_2,   v_x1_pss_2_);
    wr(buf, OFF_V_X2_PSS_2,   v_x2_pss_2_);
    wr(buf, OFF_V_Y1_PSS_2,   v_y1_pss_2_);
    wr(buf, OFF_V_Y2_PSS_2,   v_y2_pss_2_);
    wr(buf, OFF_V_SUM_PSS_2,  v_sum_pss_2_);
    wr(buf, OFF_THRESH_PSS_2, thresh_pss_2_);
    wr(buf, OFF_RADIUS_PSS_2, radius_pss_2_);
    wr(buf, OFF_GOOD_PSS_2,   good_pss_2_);
    wr(buf, OFF_X_RAW_PSS_2,  x_raw_pss_2_);
    wr(buf, OFF_Y_RAW_PSS_2,  y_raw_pss_2_);
    wr(buf, OFF_X_CORR_PSS_2, x_corr_pss_2_);
    wr(buf, OFF_Y_CORR_PSS_2, y_corr_pss_2_);
    wr(buf, OFF_AZ_PSS_2,     az_pss_2_);
    wr(buf, OFF_EL_PSS_2,     el_pss_2_);
    wr(buf, OFF_VALID_PSS_2,  valid_pss_2_);

    // PSS 3
    wr(buf, OFF_V_X1_PSS_3,   v_x1_pss_3_);
    wr(buf, OFF_V_X2_PSS_3,   v_x2_pss_3_);
    wr(buf, OFF_V_Y1_PSS_3,   v_y1_pss_3_);
    wr(buf, OFF_V_Y2_PSS_3,   v_y2_pss_3_);
    wr(buf, OFF_V_SUM_PSS_3,  v_sum_pss_3_);
    wr(buf, OFF_THRESH_PSS_3, thresh_pss_3_);
    wr(buf, OFF_RADIUS_PSS_3, radius_pss_3_);
    wr(buf, OFF_GOOD_PSS_3,   good_pss_3_);
    wr(buf, OFF_X_RAW_PSS_3,  x_raw_pss_3_);
    wr(buf, OFF_Y_RAW_PSS_3,  y_raw_pss_3_);
    wr(buf, OFF_X_CORR_PSS_3, x_corr_pss_3_);
    wr(buf, OFF_Y_CORR_PSS_3, y_corr_pss_3_);
    wr(buf, OFF_AZ_PSS_3,     az_pss_3_);
    wr(buf, OFF_EL_PSS_3,     el_pss_3_);
    wr(buf, OFF_VALID_PSS_3,  valid_pss_3_);

    // PSS 4
    wr(buf, OFF_V_X1_PSS_4,   v_x1_pss_4_);
    wr(buf, OFF_V_X2_PSS_4,   v_x2_pss_4_);
    wr(buf, OFF_V_Y1_PSS_4,   v_y1_pss_4_);
    wr(buf, OFF_V_Y2_PSS_4,   v_y2_pss_4_);
    wr(buf, OFF_V_SUM_PSS_4,  v_sum_pss_4_);
    wr(buf, OFF_THRESH_PSS_4, thresh_pss_4_);
    wr(buf, OFF_RADIUS_PSS_4, radius_pss_4_);
    wr(buf, OFF_GOOD_PSS_4,   good_pss_4_);
    wr(buf, OFF_X_RAW_PSS_4,  x_raw_pss_4_);
    wr(buf, OFF_Y_RAW_PSS_4,  y_raw_pss_4_);
    wr(buf, OFF_X_CORR_PSS_4, x_corr_pss_4_);
    wr(buf, OFF_Y_CORR_PSS_4, y_corr_pss_4_);
    wr(buf, OFF_AZ_PSS_4,     az_pss_4_);
    wr(buf, OFF_EL_PSS_4,     el_pss_4_);
    wr(buf, OFF_VALID_PSS_4,  valid_pss_4_);

    // PSS 5
    wr(buf, OFF_V_X1_PSS_5,   v_x1_pss_5_);
    wr(buf, OFF_V_X2_PSS_5,   v_x2_pss_5_);
    wr(buf, OFF_V_Y1_PSS_5,   v_y1_pss_5_);
    wr(buf, OFF_V_Y2_PSS_5,   v_y2_pss_5_);
    wr(buf, OFF_V_SUM_PSS_5,  v_sum_pss_5_);
    wr(buf, OFF_THRESH_PSS_5, thresh_pss_5_);
    wr(buf, OFF_RADIUS_PSS_5, radius_pss_5_);
    wr(buf, OFF_GOOD_PSS_5,   good_pss_5_);
    wr(buf, OFF_X_RAW_PSS_5,  x_raw_pss_5_);
    wr(buf, OFF_Y_RAW_PSS_5,  y_raw_pss_5_);
    wr(buf, OFF_X_CORR_PSS_5, x_corr_pss_5_);
    wr(buf, OFF_Y_CORR_PSS_5, y_corr_pss_5_);
    wr(buf, OFF_AZ_PSS_5,     az_pss_5_);
    wr(buf, OFF_EL_PSS_5,     el_pss_5_);
    wr(buf, OFF_VALID_PSS_5,  valid_pss_5_);

    // ADC boxcar sizes
    wr(buf, OFF_BOXCAR_ADC_0, boxcar_size_adc_0_);
    wr(buf, OFF_BOXCAR_ADC_1, boxcar_size_adc_1_);
    wr(buf, OFF_BOXCAR_ADC_2, boxcar_size_adc_2_);
    wr(buf, OFF_BOXCAR_ADC_3, boxcar_size_adc_3_);
    wr(buf, OFF_BOXCAR_ADC_4, boxcar_size_adc_4_);
    wr(buf, OFF_BOXCAR_ADC_5, boxcar_size_adc_5_);

    // Azimuth / elevation candidates
    wr(buf, OFF_CURRENT_AZ, current_az_);
    wr(buf, OFF_OFFSET_AZ,  offset_az_);
    wr(buf, OFF_BEST_AZ,    best_az_);
    wr(buf, OFF_BEST_EL,    best_el_);

    // GPS
    wr(buf, OFF_TIMESTAMP_GPS, timestamp_gps_);
    wr(buf, OFF_LAT_GPS,       lat_gps_);
    wr(buf, OFF_LON_GPS,       lon_gps_);
    wr(buf, OFF_ALT_GPS,       alt_gps_);
    wr(buf, OFF_BAUD_GPS,      baud_gps_);
    wr(buf, OFF_RA_SUN_GPS,    ra_sun_gps_);
    wr(buf, OFF_DEC_SUN_GPS,   dec_sun_gps_);
    wr(buf, OFF_AZ_SUN_GPS,    az_sun_gps_);
    wr(buf, OFF_EL_SUN_GPS,    el_sun_gps_);
    wr(buf, OFF_HA_SUN_GPS,    ha_sun_gps_);

    // Array / table
    wr(buf, OFF_ARRAY_TIP,          array_tip_);
    wr(buf, OFF_ARRAY_TILT,         array_tilt_);
    wr(buf, OFF_POS_TABLE,          pos_table_);
    wr(buf, OFF_LAST_TIME_TABLE,    last_time_table_);
    wr(buf, OFF_AT_TARGET_TABLE,    at_target_table_);
    wr(buf, OFF_CMD_POSITION_TABLE, cmd_position_table_);
    wr(buf, OFF_CMD_SPEED_TABLE,    cmd_speed_table_);
    wr(buf, OFF_SET_POS_TABLE,      set_pos_table_);
    wr(buf, OFF_CYCLE_START_TABLE,  cycle_start_table_);
    wr(buf, OFF_CYCLE_END_TABLE,    cycle_end_table_);
    wr(buf, OFF_CYCLES_LEFT_TABLE,  cycles_left_table_);

    return PACKET_SIZE;
}
