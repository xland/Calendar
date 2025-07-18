﻿#include "NongLi.h"

namespace {
    const std::vector<int> lunarInfo{
        0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2, //1900-1909
        0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977, //1910-1919
        0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970, //1920-1929
        0x06566, 0x0d4a0, 0x0ea50, 0x16a95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950,//1930-1939
        0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557,//1940-1949
        0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0,//1950-1959
        0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0,//1960-1969
        0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6,//1970-1979
        0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570,//1980-1989
        0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x05ac0, 0x0ab60, 0x096d5, 0x092e0,//1990-1999
        0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5,//2000-2009
        0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930,//2010-2019
        0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530,//2020-2029
        0x05aa0, 0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45,//2030-2039
        0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0,//2040-2049
        0x14b63, 0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6, 0x0ea50, 0x06aa0, 0x1a6c4, 0x0aae0,//2050-2059
        0x092e0, 0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50, 0x05d55, 0x056a0, 0x0a6d0, 0x055d4,//2060-2069
        0x052d0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50, 0x055a0, 0x0aba4, 0x0a5b0, 0x052b0,//2070-2079
        0x0b273, 0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55, 0x04b60, 0x0a570, 0x054e4, 0x0d160,//2080-2089
        0x0e968, 0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0, 0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252,//2090-2099
        0x0d520, 0x0db27, 0x0b5a0, 0x055d0, 0x04db5, 0x049b0, 0x0a4b0, 0x0d4b4, 0x0aa50, 0x0b559,//2100-2109
        0x06d20, 0x0ad60, 0x05766, 0x09370, 0x04970, 0x06974, 0x054b0, 0x06a50, 0x07a53, 0x06aa0,//2110-2119
        0x1aaa7, 0x0aad0, 0x052e0, 0x0cae5, 0x0a960, 0x0d4a0, 0x1e4a4, 0x0d950, 0x05abb, 0x056a0,//2120-2129
        0x0a6d0, 0x151d6, 0x052d0, 0x0a8d0, 0x1d155, 0x0b2a0, 0x0b550, 0x06d52, 0x055a0, 0x1a5a7,//2130-2139
        0x0a5b0, 0x052b0, 0x0a975, 0x068b0, 0x07290, 0x0baa4, 0x06b50, 0x02dbb, 0x04b60, 0x0a570,//2140-2149
        0x052e6, 0x0d160, 0x0e8b0, 0x06d25, 0x0da90, 0x05b50, 0x036d3, 0x02ae0, 0x0a3d7, 0x0a2d0,//2150-2159
        0x0d150, 0x0d556, 0x0b520, 0x0d690, 0x155a4, 0x055b0, 0x02afa, 0x045b0, 0x0a2b0, 0x0aab6,//2160-2169
        0x0a950, 0x0b4a0, 0x1b2a5, 0x0ad50, 0x055b0, 0x02b73, 0x04570, 0x06377, 0x052b0, 0x06950,//2170-2179
        0x06d56, 0x05aa0, 0x0ab50, 0x056d4, 0x04ae0, 0x0a570, 0x06562, 0x0d2a0, 0x0eaa6, 0x0d550,//2180-2189
        0x05aa0, 0x0aea5, 0x0a6d0, 0x04ae0, 0x0aab3, 0x0a4d0, 0x0d2b7, 0x0b290, 0x0b550, 0x15556,//2190-2199
        0x02da0, 0x095d0, 0x145b4, 0x049b0, 0x0a4f9, 0x064b0, 0x06a90, 0x0b696, 0x06b50, 0x02b60,//2200-2209
        0x09b64, 0x09370, 0x04970, 0x06963, 0x0e4a0, 0x0eaa7, 0x0da90, 0x05b50, 0x02ed5, 0x02ae0,//2210-2219
        0x092e0, 0x1c2d4, 0x0c950, 0x0d4d9, 0x0b4a0, 0x0b690, 0x057a7, 0x055b0, 0x025d0, 0x095b5,//2220-2229
        0x092b0, 0x0a950, 0x1c953, 0x0b4a0, 0x0b5a8, 0x0ad50, 0x055b0, 0x12375, 0x02570, 0x052b0,//2230-2239
        0x1a2b4, 0x06950, 0x06cbb, 0x05aa0, 0x0ab50, 0x14ad6, 0x04ae0, 0x0a570, 0x054d5, 0x0d260,//2240-2249
        0x0e950, 0x07553, 0x05aa0, 0x0aba7, 0x095d0, 0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x0da55,//2250-2259
        0x0b540, 0x0d6a0, 0x0ada1, 0x095b0, 0x04b77, 0x049b0, 0x0a4b0, 0x0b4b5, 0x06a50, 0x0ad40,//2260-2269
        0x1ab53, 0x02b60, 0x19568, 0x09370, 0x04970, 0x06566, 0x0e4a0, 0x0ea50, 0x16a94, 0x05ad0,//2270-2279
        0x02b60, 0x0aae2, 0x092e0, 0x0cad6, 0x0c950, 0x0d4a0, 0x0dca5, 0x0b650, 0x056a0, 0x0b5b3,//2280-2289
        0x025d0, 0x093b7, 0x092b0, 0x0a950, 0x0b556, 0x074a0, 0x0b550, 0x05d54, 0x04da0, 0x0a5b0,//2290-2299
        0x06572, 0x052b0, 0x0aaa6, 0x0e950, 0x06aa0, 0x1aaa5, 0x0ab50, 0x04b60, 0x0aae3, 0x0a570,//2300-2309
        0x052d7, 0x0d260, 0x0d950, 0x16956, 0x056a0, 0x09ad0, 0x145d4, 0x04ad0, 0x0a4fa, 0x0a4d0,//2310-2319
        0x0d250, 0x1d457, 0x0b540, 0x0b6a0, 0x195a5, 0x095b0, 0x049b0, 0x0a973, 0x0a4b0, 0x0b2b8,//2320-2329
        0x06a50, 0x06d40, 0x0b746, 0x0ab60, 0x09570, 0x142f4, 0x04970, 0x064b0, 0x074a3, 0x0ea50,//2330-2339
        0x16c57, 0x05ac0, 0x0ab60, 0x096d5, 0x092e0, 0x0c960, 0x0d954, 0x0d4a0, 0x0daa8, 0x0b550,//2340-2349
        0x056a0, 0x1a9b6, 0x025d0, 0x092d0, 0x0cab5, 0x0a950, 0x0b4a0, 0x0f4a1, 0x0b550, 0x15557,//2350-2359
        0x04ba0, 0x0a5b0, 0x05575, 0x052b0, 0x0a930, 0x07954, 0x06aa0, 0x0ada8, 0x0ab50, 0x04b60,//2360-2369
        0x0a6e6, 0x0a570, 0x05260, 0x0ea65, 0x0d920, 0x0daa0, 0x156a2, 0x096d0, 0x04bd7, 0x04ad0,//2370-2379
        0x0a4d0, 0x0d4b5, 0x0d250, 0x0d520, 0x1d544, 0x0b5a0, 0x056ea, 0x095b0, 0x049b0, 0x0a576,//2380-2389
        0x0a4b0, 0x0b250, 0x0ba54, 0x06d20, 0x0ada0, 0x06b62, 0x09370, 0x04af6, 0x04970, 0x064b0,//2390-2399
        0x06ca5, 0x0ea50, 0x06b20, 0x0bac3, 0x0ab60, 0x093d8, 0x092e0, 0x0c960, 0x0d556, 0x0d4a0,//2400-2409
        0x0da50, 0x05d55, 0x056a0, 0x0aad0, 0x065d2, 0x052d0, 0x1a8b7, 0x0a950, 0x0b4a0, 0x1b2a5,//2410-2419
        0x0ad50, 0x055a0, 0x0aba3, 0x0a5b0, 0x15278, 0x05270, 0x06930, 0x07536, 0x06aa0, 0x0ad50,//2420-2429
        0x14b54, 0x04b60, 0x0a570, 0x144e3, 0x0d260, 0x1e867, 0x0d520, 0x0da90, 0x06ea5, 0x056d0,//2430-2439
        0x04ae0, 0x0a9d4, 0x0a4d0, 0x0d2b8, 0x0d250, 0x0d520, 0x0db27, 0x0b5a0, 0x056d0, 0x04db5,//2440-2449
        0x049b0, 0x0a4b0, 0x1c4b3, 0x0aa50, 0x0b558, 0x06d20, 0x0ad60, 0x15365, 0x05370, 0x04970,//2450-2459
        0x06974, 0x064b0, 0x06aa8, 0x0ea50, 0x06aa0, 0x1aaa6, 0x0aad0, 0x052e0, 0x0cae5, 0x0c960,//2460-2469
        0x0d4a0, 0x0f4a3, 0x0d950, 0x05b57, 0x056a0, 0x0a6d0, 0x055d5, 0x052d0, 0x0a950, 0x0d954,//2470-2479
        0x0b4a0, 0x0b56a, 0x0ad50, 0x055a0, 0x0a7a6, 0x0a5b0, 0x052b0, 0x0a975, 0x06930, 0x07290,//2480-2489
        0x1aa93, 0x06d50, 0x12d57, 0x04b60, 0x0a570, 0x052e5, 0x0d160, 0x0e8b0, 0x16524, 0x0da90,//2490-2499
        0x06b6a, 0x056d0, 0x02ae0, 0x0a5d6, 0x0a2d0, 0x0d150, 0x1d155, 0x0b520, 0x0da90, 0x075a2,//2500-2509
        0x055b0, 0x02bb7, 0x045b0, 0x0a2b0, 0x0b2b5, 0x0a950, 0x0b520, 0x0bd24, 0x0ad50, 0x055b0,//2510-2519
        0x05371, 0x04570, 0x16176, 0x052b0, 0x06950, 0x16955, 0x05aa0, 0x0ab50, 0x14ad3, 0x04ae0,//2520-2529
        0x1a4e7, 0x0a560, 0x0d4a0, 0x0eaa6, 0x0d950, 0x05aa0, 0x1a6a4, 0x0a6d0, 0x04ae0, 0x0cab1,//2530-2539
        0x0a8d0, 0x0d4b7, 0x0b290, 0x0b550, 0x15555, 0x035a0, 0x095d0, 0x055b3, 0x049b0, 0x0a977,//2540-2549
        0x068b0, 0x06a90, 0x0b696, 0x06b50, 0x02da0, 0x09b64, 0x09570, 0x051e8, 0x0d160, 0x0e4a0,//2550-2559
        0x0eaa7, 0x0da90, 0x05b50, 0x02ed5, 0x02ae0, 0x092e0, 0x0d2d4, 0x0c950, 0x0d557, 0x0b4a0,//2560-2569
        0x0b690, 0x15996, 0x055b0, 0x029d0, 0x095b4, 0x0a2b0, 0x1a939, 0x0a950, 0x0b4a0, 0x0b6a6,//2570-2579
        0x0ad50, 0x055a0, 0x0ab74, 0x02570, 0x052b0, 0x0b2b3, 0x06950, 0x06d57, 0x05aa0, 0x0ab50,//2580-2589
        0x056d5, 0x04ae0, 0x0a570, 0x05554, 0x0d260, 0x0e96a, 0x0d550, 0x05aa0, 0x1aaa7, 0x096d0,//2590-2599
        0x04ae0, 0x1a1b5, 0x0a4d0, 0x0d250, 0x1d253, 0x0b540, 0x1d658, 0x02da0, 0x095b0, 0x14976,//2600-2609
        0x049b0, 0x0a4b0, 0x0b4b4, 0x06a50, 0x0b55b, 0x06b50, 0x02b60, 0x09766, 0x09370, 0x04970,//2610-2619
        0x16165, 0x0e4a0, 0x0ea50, 0x07a93, 0x05ac0, 0x0abd8, 0x02ae0, 0x092e0, 0x0cad6, 0x0c950,//2620-2629
        0x0d4a0, 0x0dca5, 0x0b650, 0x056a0, 0x0d5b1, 0x025d0, 0x093b7, 0x092b0, 0x0a950, 0x1d155,//2630-2639
        0x074a0, 0x0b550, 0x14d53, 0x055a0, 0x1a568, 0x0a570, 0x052b0, 0x0aaa6, 0x0e950, 0x06ca0,//2640-2649
        0x1aaa4, 0x0ab50, 0x04b60, 0x18ae2, 0x0a570, 0x052d7, 0x0d260, 0x0e920, 0x0ed55, 0x05aa0,//2650-2659
        0x09ad0, 0x056d3, 0x04ad0, 0x0a5b7, 0x0a4d0, 0x0d250, 0x0da56, 0x0b540, 0x0d6a0, 0x09da4,//2660-2669
        0x095b0, 0x04ab0, 0x0a973, 0x0a4b0, 0x0b2b7, 0x06a50, 0x06d40, 0x1b345, 0x0ab60, 0x095b0,//2670-2679
        0x05373, 0x04970, 0x06567, 0x0d4a0, 0x0ea50, 0x06e56, 0x05ac0, 0x0ab60, 0x096d4, 0x092e0,//2680-2689
        0x0c960, 0x0e953, 0x0d4a0, 0x0daa7, 0x0b550, 0x056a0, 0x0ada5, 0x0a5d0, 0x092d0, 0x0d2b3,//2690-2699
        0x0a950, 0x1b458, 0x074a0, 0x0b550, 0x15556, 0x04da0, 0x0a5b0, 0x05574, 0x052b0, 0x0a930,//2700-2709
        0x16933, 0x06aa0, 0x1aca7, 0x0ab50, 0x04b60, 0x1a2e5, 0x0a560, 0x0d260, 0x1e264, 0x0d920,//2710-2719
        0x0dac9, 0x0d6a0, 0x09ad0, 0x149d6, 0x04ad0, 0x0a4d0, 0x0d4b5, 0x0d250, 0x0d53b, 0x0b540,//2720-2729
        0x0b6a0, 0x057a7, 0x095b0, 0x049b0, 0x1a175, 0x0a4b0, 0x0b250, 0x0ba54, 0x06d20, 0x0adc9,//2730-2739
        0x0ab60, 0x09570, 0x04af6, 0x04970, 0x064b0, 0x06ca5, 0x0ea50, 0x06d20, 0x19aa2, 0x0ab50,//2740-2749
        0x152d7, 0x092e0, 0x0c960, 0x0d556, 0x0d4a0, 0x0da50, 0x15554, 0x056a0, 0x1aaa8, 0x0a5d0,//2750-2759
        0x052d0, 0x0aab6, 0x0a950, 0x0b4a0, 0x1b4a5, 0x0b550, 0x055a0, 0x0aba3, 0x0a5b0, 0x05377,//2760-2769
        0x05270, 0x06930, 0x07536, 0x06aa0, 0x0ad50, 0x05b53, 0x04b60, 0x0a5e8, 0x0a4e0, 0x0d260,//2770-2779
        0x0ea66, 0x0d520, 0x0da90, 0x06ea5, 0x056d0, 0x04ae0, 0x0aad3, 0x0a4d0, 0x0d2b7, 0x0d250,//2780-2789
        0x0d520, 0x1d926, 0x0b6a0, 0x056d0, 0x055b3, 0x049b0, 0x1a478, 0x0a4b0, 0x0aa50, 0x0b656,//2790-2799
        0x06d20, 0x0ad60, 0x05b64, 0x05370, 0x04970, 0x06973, 0x064b0, 0x06aa7, 0x0ea50, 0x06b20,//2800-2809
        0x0aea6, 0x0ab50, 0x05360, 0x1c2e4, 0x0c960, 0x0d4d9, 0x0d4a0, 0x0da50, 0x05b57, 0x056a0,//2810-2819
        0x0a6d0, 0x055d5, 0x052d0, 0x0a950, 0x1c953, 0x0b490, 0x0b5a8, 0x0ad50, 0x055a0, 0x1a3a5,//2820-2829
        0x0a5b0, 0x052b0, 0x1a174, 0x06930, 0x072b9, 0x06a90, 0x06d50, 0x02f56, 0x04b60, 0x0a570,//2830-2839
        0x054e5, 0x0d160, 0x0e920, 0x0f523, 0x0da90, 0x06ba8, 0x056d0, 0x02ae0, 0x0a5d6, 0x0a4d0,//2840-2849
        0x0d150, 0x0d955, 0x0d520, 0x0daa9, 0x0b590, 0x056b0, 0x02bb7, 0x049b0, 0x0a2b0, 0x0b2b5,//2850-2859
        0x0aa50, 0x0b520, 0x1ad23, 0x0ad50, 0x15567, 0x05370, 0x04970, 0x06576, 0x054b0, 0x06a50,//2860-2869
        0x07954, 0x06aa0, 0x0ab6a, 0x0aad0, 0x05360, 0x0a6e6, 0x0a960, 0x0d4a0, 0x0eca5, 0x0d950,//2870-2879
        0x05aa0, 0x0b6a3, 0x0a6d0, 0x04bd7, 0x04ab0, 0x0a8d0, 0x0d4b6, 0x0b290, 0x0b540, 0x0dd54,//2880-2889
        0x055a0, 0x095ea, 0x095b0, 0x052b0, 0x0a976, 0x068b0, 0x07290, 0x1b295, 0x06d50, 0x02da0,//2890-2899
        0x18b63, 0x09570, 0x150e7, 0x0d160, 0x0e8a0, 0x1e8a6, 0x0da90, 0x05b50, 0x126d4, 0x02ae0,//2900-2909
        0x092fb, 0x0a2d0, 0x0d150, 0x0d557, 0x0b4a0, 0x0da90, 0x05d95, 0x055b0, 0x02ad0, 0x185b3,//2910-2919
        0x0a2b0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x1b4a6, 0x0ad50, 0x055a0, 0x0ab64, 0x0a570, 0x052f9,//2920-2929
        0x052b0, 0x06950, 0x06d57, 0x05aa0, 0x0ab50, 0x152d5, 0x04ae0, 0x0a570, 0x05554, 0x0d260,//2930-2939
        0x0e9a8, 0x0d950, 0x05aa0, 0x1aaa6, 0x096d0, 0x04ad0, 0x0aab4, 0x0a4d0, 0x0d2b8, 0x0b250,//2940-2949
        0x0b540, 0x0d757, 0x02da0, 0x095b0, 0x04db5, 0x049b0, 0x0a4b0, 0x0b4b4, 0x06a50, 0x0b598,//2950-2959
        0x06d50, 0x02d60, 0x09766, 0x09370, 0x04970, 0x06964, 0x0e4a0, 0x0ea6a, 0x0da50, 0x05b40,//2960-2969
        0x1aad7, 0x02ae0, 0x092e0, 0x0cad5, 0x0c950, 0x0d4a0, 0x1d4a3, 0x0b650, 0x15658, 0x055b0,//2970-2979
        0x029d0, 0x191b6, 0x092b0, 0x0a950, 0x0d954, 0x0b4a0, 0x0b56a, 0x0ad50, 0x055a0, 0x0a766,//2980-2989
        0x0a570, 0x052b0, 0x0aaa5, 0x0e950, 0x06ca0, 0x0baa3, 0x0ab50, 0x04bd8, 0x04ae0, 0x0a570,//2990-2999
        0x150d6 // 3000
    };
    // 公历每月天数
    static constexpr std::array<int, 12> solarMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    // 中文字符
    std::array<QString, 10> Gan = { "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸" };
    std::array<QString, 12> Zhi = { "子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥" };
    std::array<QString, 12> Animals = { "鼠", "牛", "虎", "兔", "龙", "蛇", "马", "羊", "猴", "鸡", "狗", "猪" };
    std::array<QString, 11> nStr1 = { "日", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十" };
    std::array<QString, 4> nStr2 = { "初", "十", "廿", "卅" };
    std::array<QString, 12> nStr3 = { "正", "二", "三", "四", "五", "六", "七", "八", "九", "十", "冬", "腊" };
    QMap<QString, QString> festival = {
        {"1-1", "元旦节"},{"2-14", "情人节"},{"5-1", "劳动节"},{"5-4", "青年节"},{"6-1", "儿童节"},
        {"9-10", "教师节"},{"10-1", "国庆节"},{"12-25", "圣诞节"},{"3-8", "妇女节"},{"3-12", "植树节"},
        {"4-1", "愚人节"},{"5-12", "护士节"},{"7-1", "建党节"},{"8-1", "建军节"},{"12-24", "平安夜"}
    };

    QMap<QString, QString> lFestival = {
        {"12-30", "除夕"},{"1-1", "春节"},{"1-15", "元宵节"},{"2-2", "龙抬头"},{"5-5", "端午节"},
        {"7-7", "七夕节"},{"7-15", "中元节"},{"8-15", "中秋节"},{"9-9", "重阳节"},{"10-1", "寒衣节"},
        {"10-15", "下元节"},{"12-8", "腊八节"},{"12-23", "北方小年"},{"12-24", "南方小年"}
    };
}

// 获取闰月
int NongLi::leapMonth(int y) {
    if (y < 1900 || y > 2100) return 0;
    return lunarInfo[y - 1900] & 0xf;
}

// 获取闰月天数
int NongLi::leapDays(int y) {
    if (leapMonth(y)) {
        return (lunarInfo[y - 1900] & 0x10000) ? 30 : 29;
    }
    return 0;
}

// 获取农历某月天数
int NongLi::monthDays(int y, int m) {
    if (y < 1900 || y > 2100 || m < 1 || m > 12) return -1;
    return (lunarInfo[y - 1900] & (0x10000 >> m)) ? 30 : 29;
}

// 获取农历某年总天数
int NongLi::lYearDays(int y) {
    int sum = 348;
    for (uint32_t i = 0x8000; i > 0x8; i >>= 1) {
        sum += (lunarInfo[y - 1900] & i) ? 1 : 0;
    }
    return sum + leapDays(y);
}

// 公历某月天数
int NongLi::solarDays(int y, int m) {
    if (m < 1 || m > 12) return -1;
    if (m == 2) {
        return QDate(y, m, 1).isLeapYear(y) ? 29 : 28;
    }
    return solarMonth[m - 1];
}

// 转换为干支年
QString NongLi::toGanZhiYear(int lYear){
    int ganKey = (lYear - 3) % 10;
    int zhiKey = (lYear - 3) % 12;
    if (ganKey == 0) ganKey = 10;
    if (zhiKey == 0) zhiKey = 12;
    return Gan[ganKey - 1] + Zhi[zhiKey - 1];
}

// 转换为生肖
QString NongLi::getAnimal(int y) {
    return Animals[(y - 4) % 12];
}

// 转换为中文月份
QString NongLi::toChinaMonth(int m){
    if (m < 1 || m > 12) return "";
    return nStr3[m - 1] + "月";
}

// 转换为中文日期
QString NongLi::toChinaDay(int d) {
    switch (d) {
    case 10: return "初十";
    case 20: return "二十";
    case 30: return "三十";
    default:
        return nStr2[d / 10] + nStr1[d % 10];
    }
}

DateInfo NongLi::solar2lunar(int y, int m, int d) {
    if (y < 1900 || y > 2100 || !QDate(y, m, d).isValid()) {
        throw std::invalid_argument("Invalid solar date");
    }

    QDate baseDate(1900, 1, 31); // 农历基准日期
    QDate targetDate(y, m, d);
    int64_t offset = baseDate.daysTo(targetDate);

    // 计算农历年
    int year = 1900, temp = 0;
    for (; year < 2101 && offset > 0; year++) {
        temp = lYearDays(year);
        offset -= temp;
    }
    if (offset < 0) {
        offset += temp;
        year--;
    }

    // 计算农历月和日
    int leap = leapMonth(year);
    bool isLeap = false;
    int month = 1;
    for (; month < 13 && offset > 0; month++) {
        if (leap > 0 && month == (leap + 1) && !isLeap) {
            --month;
            isLeap = true;
            temp = leapDays(year);
        }
        else {
            temp = monthDays(year, month);
        }
        if (isLeap && month == (leap + 1)) isLeap = false;
        offset -= temp;
    }
    if (offset == 0 && leap > 0 && month == leap + 1) {
        if (isLeap) {
            isLeap = false;
        }
        else {
            isLeap = true;
            --month;
        }
    }
    if (offset < 0) {
        offset += temp;
        --month;
    }
    int day = offset + 1;
    // 节日处理
    QString festivalDate = QString("%1-%2").arg(m).arg(d);
    QString lunarFestivalDate = QString("%1-%2").arg(month).arg(day);
    if (month == 12 && day == 29 && monthDays(year, month) == 29) {
        lunarFestivalDate = "12-30";
    }

    QString festivalStr = festival.value(festivalDate, "");
    festivalStr = lFestival.value(lunarFestivalDate, festivalStr);

    return DateInfo{
        QDate(year,month,day),
        festivalStr,
        getAnimal(year),
        isLeap ? "闰" + toChinaMonth(month) : toChinaMonth(month),
        toChinaDay(day),
        toGanZhiYear(year),
        isLeap
    };
}