#ifndef CPY_TYPES_H
#define CPY_TYPES_H

// Data type definition.

enum CPY_TYPES {
  cpy_void_t = 10,
  cpy_float_t = 1,
  cpy_int_t = 4,
  cpy_short_t = 4,
  cpy_char_t = 2,
  cpy_str_t = 8,
  cpy_uchar_t = 3,
  cpy_uint_t = 5,
  cpy_long_t = 6,
  cpy_ulong_t = 7,
  cpy_double_t = 1,
  cpy_num_t = 1,
  cpy_bool_t = 17,
  cpy_list_t = 18,
  /** type for cpy_list_t of `double` */
  cpy_listd_t = 19,
  /** type for cpy_list_t of `float` */
  cpy_listf_t = 20,
  /** type for string[] literal */
  cpy_arrs_t = 15,
  /** type for char[] liternal */
  cpy_arrc_t = 9,
  /** type for (unsigned int)[] literal */
  cpy_arru_t = 12,
  /** type for short[] literal */
  cpy_arrhi_t = 13,
  /** type for (unsigned short)[] literal */
  cpy_arrhu_t = 14,
  /** type for double[] literal */
  cpy_arrd_t = 11,
  /** type for float[] literal */
  cpy_arrf_t = 21,

  /** type not recognized by libcpy.h */
  cpy_unk_t = 0,
};

#endif  // CPY_TYPES_H
