#pragma once

#include <cstdint>
#include <cstring>
#include <cstddef>

// ---------------------------------------------------------------------------
// PacketField — enumerates every telemetry field defined in table_parsed.json
// ---------------------------------------------------------------------------
enum class PacketField : uint8_t {
    // PSS 0
    V_X1_PSS_0,
    V_X2_PSS_0,
    V_Y1_PSS_0,
    V_Y2_PSS_0,
    V_SUM_PSS_0,
    THRESH_PSS_0,
    RADIUS_PSS_0,
    GOOD_PSS_0,
    X_RAW_PSS_0,
    Y_RAW_PSS_0,
    X_CORR_PSS_0,
    Y_CORR_PSS_0,
    AZ_PSS_0,
    EL_PSS_0,
    VALID_PSS_0,
    // PSS 1
    V_X1_PSS_1,
    V_X2_PSS_1,
    V_Y1_PSS_1,
    V_Y2_PSS_1,
    V_SUM_PSS_1,
    THRESH_PSS_1,
    RADIUS_PSS_1,
    GOOD_PSS_1,
    X_RAW_PSS_1,
    Y_RAW_PSS_1,
    X_CORR_PSS_1,
    Y_CORR_PSS_1,
    AZ_PSS_1,
    EL_PSS_1,
    VALID_PSS_1,
    // PSS 2
    V_X1_PSS_2,
    V_X2_PSS_2,
    V_Y1_PSS_2,
    V_Y2_PSS_2,
    V_SUM_PSS_2,
    THRESH_PSS_2,
    RADIUS_PSS_2,
    GOOD_PSS_2,
    X_RAW_PSS_2,
    Y_RAW_PSS_2,
    X_CORR_PSS_2,
    Y_CORR_PSS_2,
    AZ_PSS_2,
    EL_PSS_2,
    VALID_PSS_2,
    // PSS 3
    V_X1_PSS_3,
    V_X2_PSS_3,
    V_Y1_PSS_3,
    V_Y2_PSS_3,
    V_SUM_PSS_3,
    THRESH_PSS_3,
    RADIUS_PSS_3,
    GOOD_PSS_3,
    X_RAW_PSS_3,
    Y_RAW_PSS_3,
    X_CORR_PSS_3,
    Y_CORR_PSS_3,
    AZ_PSS_3,
    EL_PSS_3,
    VALID_PSS_3,
    // PSS 4
    V_X1_PSS_4,
    V_X2_PSS_4,
    V_Y1_PSS_4,
    V_Y2_PSS_4,
    V_SUM_PSS_4,
    THRESH_PSS_4,
    RADIUS_PSS_4,
    GOOD_PSS_4,
    X_RAW_PSS_4,
    Y_RAW_PSS_4,
    X_CORR_PSS_4,
    Y_CORR_PSS_4,
    AZ_PSS_4,
    EL_PSS_4,
    VALID_PSS_4,
    // PSS 5
    V_X1_PSS_5,
    V_X2_PSS_5,
    V_Y1_PSS_5,
    V_Y2_PSS_5,
    V_SUM_PSS_5,
    THRESH_PSS_5,
    RADIUS_PSS_5,
    GOOD_PSS_5,
    X_RAW_PSS_5,
    Y_RAW_PSS_5,
    X_CORR_PSS_5,
    Y_CORR_PSS_5,
    AZ_PSS_5,
    EL_PSS_5,
    VALID_PSS_5,
    // ADC boxcar sizes
    BOXCAR_SIZE_ADC_0,
    BOXCAR_SIZE_ADC_1,
    BOXCAR_SIZE_ADC_2,
    BOXCAR_SIZE_ADC_3,
    BOXCAR_SIZE_ADC_4,
    BOXCAR_SIZE_ADC_5,
    // Azimuth / elevation candidates
    CURRENT_AZ,
    OFFSET_AZ,
    BEST_AZ,
    BEST_EL,
    // GPS
    TIMESTAMP_GPS,
    LAT_GPS,
    LON_GPS,
    ALT_GPS,
    BAUD_GPS,
    RA_SUN_GPS,
    DEC_SUN_GPS,
    AZ_SUN_GPS,
    EL_SUN_GPS,
    HA_SUN_GPS,
    // Array / table
    ARRAY_TIP,
    ARRAY_TILT,
    POS_TABLE,
    LAST_TIME_TABLE,
    AT_TARGET_TABLE,
    CMD_POSITION_TABLE,
    CMD_SPEED_TABLE,
    SET_POS_TABLE,
    CYCLE_START_TABLE,
    CYCLE_END_TABLE,
    CYCLES_LEFT_TABLE,

    FIELD_COUNT  ///< Sentinel – always last
};

// ---------------------------------------------------------------------------
// SunSensorPacket
//
// Parses a raw 833-byte UDP datagram that follows the layout described in
// table_parsed.json.  All multi-byte values are assumed to be in the native
// byte order of the sender (little-endian ARM/x86); if the sender is
// big-endian, add byte-swap helpers in the .cpp.
// ---------------------------------------------------------------------------
class SunSensorPacket {
public:
    /// Total wire size of one telemetry frame (bytes).
    static constexpr size_t PACKET_SIZE = 833;

    SunSensorPacket() = default;

    // -------------------------------------------------------------------
    // Parsing / serialisation
    // -------------------------------------------------------------------

    /// Deserialise a raw UDP payload into this object.
    /// Returns true on success, false if `len` < PACKET_SIZE.
    bool parse(const uint8_t* buf, size_t len);

    /// Serialise this object back into a raw buffer.
    /// Returns the number of bytes written (PACKET_SIZE) on success, or 0
    /// if `len` < PACKET_SIZE.
    size_t serialize(uint8_t* buf, size_t len) const;

    // -------------------------------------------------------------------
    // Getters — PSS 0
    // -------------------------------------------------------------------
    double   get_v_x1_pss_0()    const { return v_x1_pss_0_;    }
    double   get_v_x2_pss_0()    const { return v_x2_pss_0_;    }
    double   get_v_y1_pss_0()    const { return v_y1_pss_0_;    }
    double   get_v_y2_pss_0()    const { return v_y2_pss_0_;    }
    double   get_v_sum_pss_0()   const { return v_sum_pss_0_;   }
    double   get_thresh_pss_0()  const { return thresh_pss_0_;  }
    double   get_radius_pss_0()  const { return radius_pss_0_;  }
    uint8_t  get_good_pss_0()    const { return good_pss_0_;    }
    double   get_x_raw_pss_0()   const { return x_raw_pss_0_;   }
    double   get_y_raw_pss_0()   const { return y_raw_pss_0_;   }
    double   get_x_corr_pss_0()  const { return x_corr_pss_0_;  }
    double   get_y_corr_pss_0()  const { return y_corr_pss_0_;  }
    double   get_az_pss_0()      const { return az_pss_0_;      }
    double   get_el_pss_0()      const { return el_pss_0_;      }
    uint8_t  get_valid_pss_0()   const { return valid_pss_0_;   }

    // PSS 1
    double   get_v_x1_pss_1()    const { return v_x1_pss_1_;    }
    double   get_v_x2_pss_1()    const { return v_x2_pss_1_;    }
    double   get_v_y1_pss_1()    const { return v_y1_pss_1_;    }
    double   get_v_y2_pss_1()    const { return v_y2_pss_1_;    }
    double   get_v_sum_pss_1()   const { return v_sum_pss_1_;   }
    double   get_thresh_pss_1()  const { return thresh_pss_1_;  }
    double   get_radius_pss_1()  const { return radius_pss_1_;  }
    uint8_t  get_good_pss_1()    const { return good_pss_1_;    }
    double   get_x_raw_pss_1()   const { return x_raw_pss_1_;   }
    double   get_y_raw_pss_1()   const { return y_raw_pss_1_;   }
    double   get_x_corr_pss_1()  const { return x_corr_pss_1_;  }
    double   get_y_corr_pss_1()  const { return y_corr_pss_1_;  }
    double   get_az_pss_1()      const { return az_pss_1_;      }
    double   get_el_pss_1()      const { return el_pss_1_;      }
    uint8_t  get_valid_pss_1()   const { return valid_pss_1_;   }

    // PSS 2
    double   get_v_x1_pss_2()    const { return v_x1_pss_2_;    }
    double   get_v_x2_pss_2()    const { return v_x2_pss_2_;    }
    double   get_v_y1_pss_2()    const { return v_y1_pss_2_;    }
    double   get_v_y2_pss_2()    const { return v_y2_pss_2_;    }
    double   get_v_sum_pss_2()   const { return v_sum_pss_2_;   }
    double   get_thresh_pss_2()  const { return thresh_pss_2_;  }
    double   get_radius_pss_2()  const { return radius_pss_2_;  }
    uint8_t  get_good_pss_2()    const { return good_pss_2_;    }
    double   get_x_raw_pss_2()   const { return x_raw_pss_2_;   }
    double   get_y_raw_pss_2()   const { return y_raw_pss_2_;   }
    double   get_x_corr_pss_2()  const { return x_corr_pss_2_;  }
    double   get_y_corr_pss_2()  const { return y_corr_pss_2_;  }
    double   get_az_pss_2()      const { return az_pss_2_;      }
    double   get_el_pss_2()      const { return el_pss_2_;      }
    uint8_t  get_valid_pss_2()   const { return valid_pss_2_;   }

    // PSS 3
    double   get_v_x1_pss_3()    const { return v_x1_pss_3_;    }
    double   get_v_x2_pss_3()    const { return v_x2_pss_3_;    }
    double   get_v_y1_pss_3()    const { return v_y1_pss_3_;    }
    double   get_v_y2_pss_3()    const { return v_y2_pss_3_;    }
    double   get_v_sum_pss_3()   const { return v_sum_pss_3_;   }
    double   get_thresh_pss_3()  const { return thresh_pss_3_;  }
    double   get_radius_pss_3()  const { return radius_pss_3_;  }
    uint8_t  get_good_pss_3()    const { return good_pss_3_;    }
    double   get_x_raw_pss_3()   const { return x_raw_pss_3_;   }
    double   get_y_raw_pss_3()   const { return y_raw_pss_3_;   }
    double   get_x_corr_pss_3()  const { return x_corr_pss_3_;  }
    double   get_y_corr_pss_3()  const { return y_corr_pss_3_;  }
    double   get_az_pss_3()      const { return az_pss_3_;      }
    double   get_el_pss_3()      const { return el_pss_3_;      }
    uint8_t  get_valid_pss_3()   const { return valid_pss_3_;   }

    // PSS 4
    double   get_v_x1_pss_4()    const { return v_x1_pss_4_;    }
    double   get_v_x2_pss_4()    const { return v_x2_pss_4_;    }
    double   get_v_y1_pss_4()    const { return v_y1_pss_4_;    }
    double   get_v_y2_pss_4()    const { return v_y2_pss_4_;    }
    double   get_v_sum_pss_4()   const { return v_sum_pss_4_;   }
    double   get_thresh_pss_4()  const { return thresh_pss_4_;  }
    double   get_radius_pss_4()  const { return radius_pss_4_;  }
    uint8_t  get_good_pss_4()    const { return good_pss_4_;    }
    double   get_x_raw_pss_4()   const { return x_raw_pss_4_;   }
    double   get_y_raw_pss_4()   const { return y_raw_pss_4_;   }
    double   get_x_corr_pss_4()  const { return x_corr_pss_4_;  }
    double   get_y_corr_pss_4()  const { return y_corr_pss_4_;  }
    double   get_az_pss_4()      const { return az_pss_4_;      }
    double   get_el_pss_4()      const { return el_pss_4_;      }
    uint8_t  get_valid_pss_4()   const { return valid_pss_4_;   }

    // PSS 5
    double   get_v_x1_pss_5()    const { return v_x1_pss_5_;    }
    double   get_v_x2_pss_5()    const { return v_x2_pss_5_;    }
    double   get_v_y1_pss_5()    const { return v_y1_pss_5_;    }
    double   get_v_y2_pss_5()    const { return v_y2_pss_5_;    }
    double   get_v_sum_pss_5()   const { return v_sum_pss_5_;   }
    double   get_thresh_pss_5()  const { return thresh_pss_5_;  }
    double   get_radius_pss_5()  const { return radius_pss_5_;  }
    uint8_t  get_good_pss_5()    const { return good_pss_5_;    }
    double   get_x_raw_pss_5()   const { return x_raw_pss_5_;   }
    double   get_y_raw_pss_5()   const { return y_raw_pss_5_;   }
    double   get_x_corr_pss_5()  const { return x_corr_pss_5_;  }
    double   get_y_corr_pss_5()  const { return y_corr_pss_5_;  }
    double   get_az_pss_5()      const { return az_pss_5_;      }
    double   get_el_pss_5()      const { return el_pss_5_;      }
    uint8_t  get_valid_pss_5()   const { return valid_pss_5_;   }

    // ADC boxcar sizes
    uint16_t get_boxcar_size_adc_0() const { return boxcar_size_adc_0_; }
    uint16_t get_boxcar_size_adc_1() const { return boxcar_size_adc_1_; }
    uint16_t get_boxcar_size_adc_2() const { return boxcar_size_adc_2_; }
    uint16_t get_boxcar_size_adc_3() const { return boxcar_size_adc_3_; }
    uint16_t get_boxcar_size_adc_4() const { return boxcar_size_adc_4_; }
    uint16_t get_boxcar_size_adc_5() const { return boxcar_size_adc_5_; }

    // Azimuth / elevation
    double   get_current_az()    const { return current_az_;    }
    double   get_offset_az()     const { return offset_az_;     }
    double   get_best_az()       const { return best_az_;       }
    double   get_best_el()       const { return best_el_;       }

    // GPS
    double   get_timestamp_gps() const { return timestamp_gps_; }
    double   get_lat_gps()       const { return lat_gps_;       }
    double   get_lon_gps()       const { return lon_gps_;       }
    double   get_alt_gps()       const { return alt_gps_;       }
    int32_t  get_baud_gps()      const { return baud_gps_;      }
    double   get_ra_sun_gps()    const { return ra_sun_gps_;    }
    double   get_dec_sun_gps()   const { return dec_sun_gps_;   }
    double   get_az_sun_gps()    const { return az_sun_gps_;    }
    double   get_el_sun_gps()    const { return el_sun_gps_;    }
    double   get_ha_sun_gps()    const { return ha_sun_gps_;    }

    // Array / table
    double   get_array_tip()           const { return array_tip_;           }
    double   get_array_tilt()          const { return array_tilt_;          }
    double   get_pos_table()           const { return pos_table_;           }
    double   get_last_time_table()     const { return last_time_table_;     }
    uint8_t  get_at_target_table()     const { return at_target_table_;     }
    double   get_cmd_position_table()  const { return cmd_position_table_;  }
    double   get_cmd_speed_table()     const { return cmd_speed_table_;     }
    double   get_set_pos_table()       const { return set_pos_table_;       }
    double   get_cycle_start_table()   const { return cycle_start_table_;   }
    double   get_cycle_end_table()     const { return cycle_end_table_;     }
    int32_t  get_cycles_left_table()   const { return cycles_left_table_;   }

    // -------------------------------------------------------------------
    // Setters — PSS 0
    // -------------------------------------------------------------------
    void set_v_x1_pss_0(double v)    { v_x1_pss_0_    = v; }
    void set_v_x2_pss_0(double v)    { v_x2_pss_0_    = v; }
    void set_v_y1_pss_0(double v)    { v_y1_pss_0_    = v; }
    void set_v_y2_pss_0(double v)    { v_y2_pss_0_    = v; }
    void set_v_sum_pss_0(double v)   { v_sum_pss_0_   = v; }
    void set_thresh_pss_0(double v)  { thresh_pss_0_  = v; }
    void set_radius_pss_0(double v)  { radius_pss_0_  = v; }
    void set_good_pss_0(uint8_t v)   { good_pss_0_    = v; }
    void set_x_raw_pss_0(double v)   { x_raw_pss_0_   = v; }
    void set_y_raw_pss_0(double v)   { y_raw_pss_0_   = v; }
    void set_x_corr_pss_0(double v)  { x_corr_pss_0_  = v; }
    void set_y_corr_pss_0(double v)  { y_corr_pss_0_  = v; }
    void set_az_pss_0(double v)      { az_pss_0_      = v; }
    void set_el_pss_0(double v)      { el_pss_0_      = v; }
    void set_valid_pss_0(uint8_t v)  { valid_pss_0_   = v; }

    // PSS 1
    void set_v_x1_pss_1(double v)    { v_x1_pss_1_    = v; }
    void set_v_x2_pss_1(double v)    { v_x2_pss_1_    = v; }
    void set_v_y1_pss_1(double v)    { v_y1_pss_1_    = v; }
    void set_v_y2_pss_1(double v)    { v_y2_pss_1_    = v; }
    void set_v_sum_pss_1(double v)   { v_sum_pss_1_   = v; }
    void set_thresh_pss_1(double v)  { thresh_pss_1_  = v; }
    void set_radius_pss_1(double v)  { radius_pss_1_  = v; }
    void set_good_pss_1(uint8_t v)   { good_pss_1_    = v; }
    void set_x_raw_pss_1(double v)   { x_raw_pss_1_   = v; }
    void set_y_raw_pss_1(double v)   { y_raw_pss_1_   = v; }
    void set_x_corr_pss_1(double v)  { x_corr_pss_1_  = v; }
    void set_y_corr_pss_1(double v)  { y_corr_pss_1_  = v; }
    void set_az_pss_1(double v)      { az_pss_1_      = v; }
    void set_el_pss_1(double v)      { el_pss_1_      = v; }
    void set_valid_pss_1(uint8_t v)  { valid_pss_1_   = v; }

    // PSS 2
    void set_v_x1_pss_2(double v)    { v_x1_pss_2_    = v; }
    void set_v_x2_pss_2(double v)    { v_x2_pss_2_    = v; }
    void set_v_y1_pss_2(double v)    { v_y1_pss_2_    = v; }
    void set_v_y2_pss_2(double v)    { v_y2_pss_2_    = v; }
    void set_v_sum_pss_2(double v)   { v_sum_pss_2_   = v; }
    void set_thresh_pss_2(double v)  { thresh_pss_2_  = v; }
    void set_radius_pss_2(double v)  { radius_pss_2_  = v; }
    void set_good_pss_2(uint8_t v)   { good_pss_2_    = v; }
    void set_x_raw_pss_2(double v)   { x_raw_pss_2_   = v; }
    void set_y_raw_pss_2(double v)   { y_raw_pss_2_   = v; }
    void set_x_corr_pss_2(double v)  { x_corr_pss_2_  = v; }
    void set_y_corr_pss_2(double v)  { y_corr_pss_2_  = v; }
    void set_az_pss_2(double v)      { az_pss_2_      = v; }
    void set_el_pss_2(double v)      { el_pss_2_      = v; }
    void set_valid_pss_2(uint8_t v)  { valid_pss_2_   = v; }

    // PSS 3
    void set_v_x1_pss_3(double v)    { v_x1_pss_3_    = v; }
    void set_v_x2_pss_3(double v)    { v_x2_pss_3_    = v; }
    void set_v_y1_pss_3(double v)    { v_y1_pss_3_    = v; }
    void set_v_y2_pss_3(double v)    { v_y2_pss_3_    = v; }
    void set_v_sum_pss_3(double v)   { v_sum_pss_3_   = v; }
    void set_thresh_pss_3(double v)  { thresh_pss_3_  = v; }
    void set_radius_pss_3(double v)  { radius_pss_3_  = v; }
    void set_good_pss_3(uint8_t v)   { good_pss_3_    = v; }
    void set_x_raw_pss_3(double v)   { x_raw_pss_3_   = v; }
    void set_y_raw_pss_3(double v)   { y_raw_pss_3_   = v; }
    void set_x_corr_pss_3(double v)  { x_corr_pss_3_  = v; }
    void set_y_corr_pss_3(double v)  { y_corr_pss_3_  = v; }
    void set_az_pss_3(double v)      { az_pss_3_      = v; }
    void set_el_pss_3(double v)      { el_pss_3_      = v; }
    void set_valid_pss_3(uint8_t v)  { valid_pss_3_   = v; }

    // PSS 4
    void set_v_x1_pss_4(double v)    { v_x1_pss_4_    = v; }
    void set_v_x2_pss_4(double v)    { v_x2_pss_4_    = v; }
    void set_v_y1_pss_4(double v)    { v_y1_pss_4_    = v; }
    void set_v_y2_pss_4(double v)    { v_y2_pss_4_    = v; }
    void set_v_sum_pss_4(double v)   { v_sum_pss_4_   = v; }
    void set_thresh_pss_4(double v)  { thresh_pss_4_  = v; }
    void set_radius_pss_4(double v)  { radius_pss_4_  = v; }
    void set_good_pss_4(uint8_t v)   { good_pss_4_    = v; }
    void set_x_raw_pss_4(double v)   { x_raw_pss_4_   = v; }
    void set_y_raw_pss_4(double v)   { y_raw_pss_4_   = v; }
    void set_x_corr_pss_4(double v)  { x_corr_pss_4_  = v; }
    void set_y_corr_pss_4(double v)  { y_corr_pss_4_  = v; }
    void set_az_pss_4(double v)      { az_pss_4_      = v; }
    void set_el_pss_4(double v)      { el_pss_4_      = v; }
    void set_valid_pss_4(uint8_t v)  { valid_pss_4_   = v; }

    // PSS 5
    void set_v_x1_pss_5(double v)    { v_x1_pss_5_    = v; }
    void set_v_x2_pss_5(double v)    { v_x2_pss_5_    = v; }
    void set_v_y1_pss_5(double v)    { v_y1_pss_5_    = v; }
    void set_v_y2_pss_5(double v)    { v_y2_pss_5_    = v; }
    void set_v_sum_pss_5(double v)   { v_sum_pss_5_   = v; }
    void set_thresh_pss_5(double v)  { thresh_pss_5_  = v; }
    void set_radius_pss_5(double v)  { radius_pss_5_  = v; }
    void set_good_pss_5(uint8_t v)   { good_pss_5_    = v; }
    void set_x_raw_pss_5(double v)   { x_raw_pss_5_   = v; }
    void set_y_raw_pss_5(double v)   { y_raw_pss_5_   = v; }
    void set_x_corr_pss_5(double v)  { x_corr_pss_5_  = v; }
    void set_y_corr_pss_5(double v)  { y_corr_pss_5_  = v; }
    void set_az_pss_5(double v)      { az_pss_5_      = v; }
    void set_el_pss_5(double v)      { el_pss_5_      = v; }
    void set_valid_pss_5(uint8_t v)  { valid_pss_5_   = v; }

    // ADC boxcar sizes
    void set_boxcar_size_adc_0(uint16_t v) { boxcar_size_adc_0_ = v; }
    void set_boxcar_size_adc_1(uint16_t v) { boxcar_size_adc_1_ = v; }
    void set_boxcar_size_adc_2(uint16_t v) { boxcar_size_adc_2_ = v; }
    void set_boxcar_size_adc_3(uint16_t v) { boxcar_size_adc_3_ = v; }
    void set_boxcar_size_adc_4(uint16_t v) { boxcar_size_adc_4_ = v; }
    void set_boxcar_size_adc_5(uint16_t v) { boxcar_size_adc_5_ = v; }

    // Azimuth / elevation
    void set_current_az(double v)    { current_az_    = v; }
    void set_offset_az(double v)     { offset_az_     = v; }
    void set_best_az(double v)       { best_az_       = v; }
    void set_best_el(double v)       { best_el_       = v; }

    // GPS
    void set_timestamp_gps(double v) { timestamp_gps_ = v; }
    void set_lat_gps(double v)       { lat_gps_       = v; }
    void set_lon_gps(double v)       { lon_gps_       = v; }
    void set_alt_gps(double v)       { alt_gps_       = v; }
    void set_baud_gps(int32_t v)     { baud_gps_      = v; }
    void set_ra_sun_gps(double v)    { ra_sun_gps_    = v; }
    void set_dec_sun_gps(double v)   { dec_sun_gps_   = v; }
    void set_az_sun_gps(double v)    { az_sun_gps_    = v; }
    void set_el_sun_gps(double v)    { el_sun_gps_    = v; }
    void set_ha_sun_gps(double v)    { ha_sun_gps_    = v; }

    // Array / table
    void set_array_tip(double v)           { array_tip_           = v; }
    void set_array_tilt(double v)          { array_tilt_          = v; }
    void set_pos_table(double v)           { pos_table_           = v; }
    void set_last_time_table(double v)     { last_time_table_     = v; }
    void set_at_target_table(uint8_t v)    { at_target_table_     = v; }
    void set_cmd_position_table(double v)  { cmd_position_table_  = v; }
    void set_cmd_speed_table(double v)     { cmd_speed_table_     = v; }
    void set_set_pos_table(double v)       { set_pos_table_       = v; }
    void set_cycle_start_table(double v)   { cycle_start_table_   = v; }
    void set_cycle_end_table(double v)     { cycle_end_table_     = v; }
    void set_cycles_left_table(int32_t v)  { cycles_left_table_   = v; }

private:
    // -------------------------------------------------------------------
    // Internal helpers: copy bytes in/out without violating strict aliasing.
    // -------------------------------------------------------------------
    template <typename T>
    static T rd(const uint8_t* buf, size_t offset) {
        T val{};
        std::memcpy(&val, buf + offset, sizeof(T));
        return val;
    }

    template <typename T>
    static void wr(uint8_t* buf, size_t offset, T val) {
        std::memcpy(buf + offset, &val, sizeof(T));
    }

    // -------------------------------------------------------------------
    // Stored fields — order mirrors table_parsed.json for readability
    // -------------------------------------------------------------------

    // PSS 0
    double   v_x1_pss_0_   {};
    double   v_x2_pss_0_   {};
    double   v_y1_pss_0_   {};
    double   v_y2_pss_0_   {};
    double   v_sum_pss_0_  {};
    double   thresh_pss_0_ {};
    double   radius_pss_0_ {};
    uint8_t  good_pss_0_   {};
    double   x_raw_pss_0_  {};
    double   y_raw_pss_0_  {};
    double   x_corr_pss_0_ {};
    double   y_corr_pss_0_ {};
    double   az_pss_0_     {};
    double   el_pss_0_     {};
    uint8_t  valid_pss_0_  {};

    // PSS 1
    double   v_x1_pss_1_   {};
    double   v_x2_pss_1_   {};
    double   v_y1_pss_1_   {};
    double   v_y2_pss_1_   {};
    double   v_sum_pss_1_  {};
    double   thresh_pss_1_ {};
    double   radius_pss_1_ {};
    uint8_t  good_pss_1_   {};
    double   x_raw_pss_1_  {};
    double   y_raw_pss_1_  {};
    double   x_corr_pss_1_ {};
    double   y_corr_pss_1_ {};
    double   az_pss_1_     {};
    double   el_pss_1_     {};
    uint8_t  valid_pss_1_  {};

    // PSS 2
    double   v_x1_pss_2_   {};
    double   v_x2_pss_2_   {};
    double   v_y1_pss_2_   {};
    double   v_y2_pss_2_   {};
    double   v_sum_pss_2_  {};
    double   thresh_pss_2_ {};
    double   radius_pss_2_ {};
    uint8_t  good_pss_2_   {};
    double   x_raw_pss_2_  {};
    double   y_raw_pss_2_  {};
    double   x_corr_pss_2_ {};
    double   y_corr_pss_2_ {};
    double   az_pss_2_     {};
    double   el_pss_2_     {};
    uint8_t  valid_pss_2_  {};

    // PSS 3
    double   v_x1_pss_3_   {};
    double   v_x2_pss_3_   {};
    double   v_y1_pss_3_   {};
    double   v_y2_pss_3_   {};
    double   v_sum_pss_3_  {};
    double   thresh_pss_3_ {};
    double   radius_pss_3_ {};
    uint8_t  good_pss_3_   {};
    double   x_raw_pss_3_  {};
    double   y_raw_pss_3_  {};
    double   x_corr_pss_3_ {};
    double   y_corr_pss_3_ {};
    double   az_pss_3_     {};
    double   el_pss_3_     {};
    uint8_t  valid_pss_3_  {};

    // PSS 4
    double   v_x1_pss_4_   {};
    double   v_x2_pss_4_   {};
    double   v_y1_pss_4_   {};
    double   v_y2_pss_4_   {};
    double   v_sum_pss_4_  {};
    double   thresh_pss_4_ {};
    double   radius_pss_4_ {};
    uint8_t  good_pss_4_   {};
    double   x_raw_pss_4_  {};
    double   y_raw_pss_4_  {};
    double   x_corr_pss_4_ {};
    double   y_corr_pss_4_ {};
    double   az_pss_4_     {};
    double   el_pss_4_     {};
    uint8_t  valid_pss_4_  {};

    // PSS 5
    double   v_x1_pss_5_   {};
    double   v_x2_pss_5_   {};
    double   v_y1_pss_5_   {};
    double   v_y2_pss_5_   {};
    double   v_sum_pss_5_  {};
    double   thresh_pss_5_ {};
    double   radius_pss_5_ {};
    uint8_t  good_pss_5_   {};
    double   x_raw_pss_5_  {};
    double   y_raw_pss_5_  {};
    double   x_corr_pss_5_ {};
    double   y_corr_pss_5_ {};
    double   az_pss_5_     {};
    double   el_pss_5_     {};
    uint8_t  valid_pss_5_  {};

    // ADC boxcar sizes
    uint16_t boxcar_size_adc_0_ {};
    uint16_t boxcar_size_adc_1_ {};
    uint16_t boxcar_size_adc_2_ {};
    uint16_t boxcar_size_adc_3_ {};
    uint16_t boxcar_size_adc_4_ {};
    uint16_t boxcar_size_adc_5_ {};

    // Azimuth / elevation candidates
    double   current_az_   {};
    double   offset_az_    {};
    double   best_az_      {};
    double   best_el_      {};

    // GPS
    double   timestamp_gps_ {};
    double   lat_gps_        {};
    double   lon_gps_        {};
    double   alt_gps_        {};
    int32_t  baud_gps_       {};
    double   ra_sun_gps_     {};
    double   dec_sun_gps_    {};
    double   az_sun_gps_     {};
    double   el_sun_gps_     {};
    double   ha_sun_gps_     {};

    // Array / table
    double   array_tip_          {};
    double   array_tilt_         {};
    double   pos_table_          {};
    double   last_time_table_    {};
    uint8_t  at_target_table_    {};
    double   cmd_position_table_ {};
    double   cmd_speed_table_    {};
    double   set_pos_table_      {};
    double   cycle_start_table_  {};
    double   cycle_end_table_    {};
    int32_t  cycles_left_table_  {};
};
