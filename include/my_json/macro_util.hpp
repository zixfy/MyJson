//
// Created by wwww on 2023/8/27.
//

#ifndef CPP_JSON_PARSER_MACRO_UTIL_HPP
#define CPP_JSON_PARSER_MACRO_UTIL_HPP
#define MACRO_LITERALLY_IMPL(x) #x
#define MACRO_UNWRAP(x) x
#define MACRO_LITERALLY(x) MACRO_UNWRAP(MACRO_LITERALLY_IMPL(x))
// (v1, v2, v3, v4, ..., vN) -> N
#if (defined(_MSC_VER) && !defined(_MSVC_TRADITIONAL)) || \
    (defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL)
#define MYJSON_ARG_COUNT(...)                                                  \
  MYJSON_GET_ARG_COUNT_IMPL_MSVC(                                              \
      MYJSON_GET_ARG_COUNT_PREPROCESS_MSVC(__VA_ARGS__))

#define MYJSON_GET_ARG_COUNT_PREPROCESS_MSVC(...) unused, __VA_ARGS__
#define MYJSON_GET_ARG_COUNT_IMPL_MSVC(...)                                    \
  MACRO_UNWRAP(MYJSON_GET_ARG_COUNT_IMPL(                                      \
      __VA_ARGS__, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, \
      94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77,  \
      76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59,  \
      58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41,  \
      40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23,  \
      22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, \
      2, 1, 0))

#else // Other compilers

#define MYJSON_ARG_COUNT(...)                                                  \
  MYJSON_GET_ARG_COUNT_IMPL(                                                   \
      unused, __VA_ARGS__, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, \
      96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79,  \
      78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61,  \
      60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43,  \
      42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25,  \
      24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,  \
      5, 4, 3, 2, 1, 0)

#endif

#define MYJSON_GET_ARG_COUNT_IMPL(\
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, \
    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, \
    _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, \
    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
    _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, \
    _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
    _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, \
    _105, _106, _107, count, ...)                                              \
  count

#define MYJSON_FIELDS_LOOP_1(func, name, i, arg) func(name, i, arg)
#define MYJSON_FIELDS_LOOP_2(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_1(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_3(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_2(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_4(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_3(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_5(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_4(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_6(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_5(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_7(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_6(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_8(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_7(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_9(func, name, i, arg, ...)                                \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_8(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_10(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_9(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_11(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_10(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_12(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_11(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_13(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_12(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_14(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_13(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_15(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_14(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_16(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_15(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_17(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_16(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_18(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_17(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_19(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_18(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_20(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_19(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_21(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_20(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_22(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_21(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_23(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_22(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_24(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_23(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_25(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_24(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_26(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_25(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_27(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_26(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_28(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_27(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_29(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_28(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_30(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_29(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_31(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_30(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_32(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_31(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_33(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_32(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_34(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_33(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_35(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_34(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_36(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_35(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_37(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_36(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_38(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_37(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_39(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_38(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_40(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_39(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_41(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_40(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_42(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_41(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_43(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_42(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_44(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_43(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_45(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_44(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_46(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_45(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_47(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_46(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_48(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_47(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_49(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_48(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_50(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_49(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_51(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_50(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_52(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_51(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_53(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_52(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_54(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_53(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_55(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_54(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_56(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_55(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_57(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_56(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_58(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_57(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_59(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_58(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_60(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_59(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_61(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_60(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_62(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_61(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_63(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_62(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_64(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_63(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_65(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_64(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_66(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_65(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_67(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_66(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_68(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_67(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_69(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_68(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_70(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_69(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_71(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_70(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_72(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_71(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_73(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_72(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_74(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_73(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_75(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_74(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_76(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_75(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_77(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_76(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_78(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_77(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_79(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_78(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_80(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_79(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_81(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_80(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_82(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_81(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_83(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_82(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_84(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_83(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_85(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_84(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_86(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_85(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_87(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_86(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_88(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_87(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_89(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_88(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_90(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_89(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_91(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_90(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_92(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_91(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_93(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_92(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_94(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_93(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_95(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_94(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_96(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_95(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_97(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_96(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_98(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_97(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_99(func, name, i, arg, ...)                               \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_98(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_100(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_99(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_101(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_100(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_102(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_101(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_103(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_102(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_104(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_103(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_105(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_104(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_106(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_105(func, name, i + 1, __VA_ARGS__))
#define MYJSON_FIELDS_LOOP_107(func, name, i, arg, ...)                              \
  func(name, i, arg) MACRO_UNWRAP(MYJSON_FIELDS_LOOP_106(func, name, i + 1, __VA_ARGS__))
// (type) name -> name;
#define MYJSON_UNWRAP_NAME_TYPE_ERASER(...)
#define MYJSON_UNWRAP_NAME(field)                                              \
  MACRO_UNWRAP(MYJSON_UNWRAP_NAME_TYPE_ERASER field)

// (type) name -> type name;
#define MYJSON_UNWRAP_DECLARATION_IMPL(...) __VA_ARGS__
#define MYJSON_UNWRAP_DECLARATION(field) MYJSON_UNWRAP_DECLARATION_IMPL field;

// (a, b) -> "ab"
#define MYJSON_CONCAT_STR_IMPL(a, b) a##b
#define MYJSON_CONCAT_STR(a, b) MYJSON_CONCAT_STR_IMPL(a, b)
#define MYJSON_FIELD_DECL(name, _index, field)     MYJSON_UNWRAP_DECLARATION(field)

#define MYJSON_FIELD_IMPL(_name, _index, field)                                       \
  template <> struct _name::MetaInfo<_index> {                                        \
    using type = decltype(_name::MYJSON_UNWRAP_NAME(field));                          \
    using parent_type = _name;                                                 \
    static constexpr const char *name() {                                      \
      return MACRO_UNWRAP(MACRO_LITERALLY(MYJSON_UNWRAP_NAME(field)));         \
    }                                                                          \
    template <typename T>   static decltype(auto) get(T &&self) {                                      \
      return std::forward<decltype((std::forward<T>(self).MYJSON_UNWRAP_NAME(  \
          field)))>(std::forward<T>(self).MYJSON_UNWRAP_NAME(field));          \
    }                                                                          \
    static constexpr size_t index() { return _index; }                         \
  };

#define DEF_DATA_CLASS(name, ...)                                              \
  struct name {                                                                \
  public:                                                                      \
    static constexpr size_t fields_count = MYJSON_ARG_COUNT(__VA_ARGS__);      \
    static constexpr bool is_reflectable_class = true;                         \
    template <std::size_t> struct MetaInfo {};                                 \
    MACRO_UNWRAP(MYJSON_CONCAT_STR(                                            \
        MYJSON_FIELDS_LOOP_, MYJSON_ARG_COUNT(__VA_ARGS__))(MYJSON_FIELD_DECL, \
                                                            name, 0, __VA_ARGS__))   \
    MyJson::Json to_json() const & {                                             \
      MyJson::Object o;                                                          \
      MyJson::for_each_meta(*this, [&o](auto &&_name, auto &&value) {         \
        o.emplace(_name, std::forward<decltype(value)>(value));                \
      });                                                                      \
      return o;                                                                \
    }                                                                          \
    MyJson::Json to_json() && {                                                  \
      MyJson::Object o;                                                          \
      MyJson::for_each_meta(                                                  \
          std::move(*this), [&o](auto &&_name, auto &&value) {                 \
            o.emplace(_name, std::forward<decltype(value)>(value));            \
          });                                                                  \
      return o;                                                                \
    }                                                                          \
    static std::optional<name> from_json (const MyJson::Json& j)   {                       \
    auto p = std::get_if<MyJson::Object>(&(j.m_value));                            \
    if (p == nullptr)                                                          \
      return std::nullopt;                                            \
    name ret{};                                                                \
    bool flag = false;                                                         \
    MyJson::for_each_meta(ret, [p, &flag](auto &&_name, auto &&value) {       \
      if (p->find(_name) == p->end())                                          \
        flag = true;                                                           \
      auto &&opt =                                                             \
          p->at(_name).template to_type<std::decay_t<decltype(value)>>();      \
      if (!opt.has_value())                                                    \
        flag = true;                                                           \
      else                                                                     \
        value = std::move(opt.value());                                        \
      if (flag)                                                                \
        return;                                                                \
    });                                                                        \
    if (flag)                                                                  \
      return std::nullopt;                                            \
    return std::optional {std::move(ret)};                                \
  }                                                                           \
  static std::optional<name> from_json(MyJson::Json&& j)  {                            \
    auto p = std::get_if<MyJson::Object>(&(j.m_value));                            \
    if (p == nullptr)                                                          \
      return std::nullopt;                                            \
    name ret{};                                                                \
    bool flag = false;                                                         \
    MyJson::for_each_meta(ret, [p, &flag](auto &&_name, auto &&value) {       \
      if (p->find(_name) == p->end())                                          \
        flag = true;                                                           \
      auto &&opt = std::move(p->at(_name))                                     \
                       .template to_type<std::decay_t<decltype(value)>>();     \
      if (!opt.has_value())                                                    \
        flag = true;                                                           \
      else                                                                     \
        value = std::move(opt.value());                                        \
      if (flag)                                                                \
        return;                                                                \
    });                                                                        \
    if (flag)                                                                  \
      return std::nullopt;                                            \
    return std::optional {std::move(ret)};                                \
  }                                                                             \
  };                                                                           \
  MACRO_UNWRAP(MYJSON_CONCAT_STR(                                            \
        MYJSON_FIELDS_LOOP_, MYJSON_ARG_COUNT(__VA_ARGS__))(MYJSON_FIELD_IMPL, name, 0, __VA_ARGS__))   \


#endif // CPP_JSON_PARSER_MACRO_UTIL_HPP