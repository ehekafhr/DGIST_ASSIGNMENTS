// Project - Code Optimization
// System Programming, DGIST, Prof. Yeseong Kim
// 
// YOU WILL TURN IN THIS FILE.
// Read the provided instruction carefully.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmplib.h"
#include "proj.h"

// This implementation is simply copied from "main.c".
// Your job is to modify and optimize it for better performance!
unsigned char ret[3];

inline static unsigned char fit(float flt){
    if(flt>=255) return 255;
    else if (flt<=0) return 0;
    else return (unsigned char)flt;
}
inline static void convolution_block(Pixel* input, Pixel* output, int start, int width, int height, float* filter) {
    float filt0 = filter[0]; float filt1 = filter[1]; float filt2 = filter[2]; float filt3 = filter[3]; float filt4 = filter[4]; float filt5 = filter[5]; float filt6 = filter[6]; float filt7 = filter[7]; float filt8 = filter[8];
    //첫번째 줄 6개
    int strcol = start - width - 1;
    Pixel* i00 = &input[strcol]; Pixel* i01 = &input[strcol + 1]; Pixel* i02 = &input[strcol + 2]; Pixel* i03 = &input[strcol+3]; Pixel* i04 = &input[strcol +4]; Pixel* i05 = &input[strcol + 5];
    float r00 = i00->r; float g00 = i00->g; float b00 = i00->b;
    float r01 = i01->r; float g01 = i01->g; float b01 = i01->b;
    float r02 = i02->r; float g02 = i02->g; float b02 = i02->b;
    float r03 = i03->r; float g03 = i03->g; float b03 = i03->b;
    float r04 = i04->r; float g04 = i04->g; float b04 = i04->b;
    float r05 = i05->r; float g05 = i05->g; float b05 = i05->b;
    //2번째 줄 6개
    strcol += width;
    Pixel* i10 = &input[strcol]; Pixel* i11 = &input[strcol + 1]; Pixel* i12 = &input[strcol + 2]; 
    Pixel* i13 = &input[strcol + 3]; Pixel* i14 = &input[strcol + 4]; Pixel* i15 = &input[strcol + 5];
    float r10 = i10->r; float g10 = i10->g; float b10 = i10->b;
    float r11 = i11->r; float g11 = i11->g; float b11 = i11->b;
    float r12 = i12->r; float g12 = i12->g; float b12 = i12->b;
    float r13 = i13->r; float g13 = i13->g; float b13 = i13->b;
    float r14 = i14->r; float g14 = i14->g; float b14 = i14->b;
    float r15 = i15->r; float g15 = i15->g; float b15 = i15->b;
    //3번째 줄 6개
    strcol += width;
    Pixel* i20 = &input[strcol]; Pixel* i21 = &input[strcol + 1]; Pixel* i22 = &input[strcol + 2];
    Pixel* i23 = &input[strcol + 3]; Pixel* i24 = &input[strcol + 4]; Pixel* i25 = &input[strcol + 5];
    float r20 = i20->r; float g20 = i20->g; float b20 = i20->b;
    float r21 = i21->r; float g21 = i21->g; float b21 = i21->b;
    float r22 = i22->r; float g22 = i22->g; float b22 = i22->b;
    float r23 = i23->r; float g23 = i23->g; float b23 = i23->b;
    float r24 = i24->r; float g24 = i24->g; float b24 = i24->b;
    float r25 = i25->r; float g25 = i25->g; float b25 = i25->b;
    //4번째 줄 6개
    strcol += width;
    Pixel* i30 = &input[strcol]; Pixel* i31 = &input[strcol + 1]; Pixel* i32 = &input[strcol + 2];
    Pixel* i33 = &input[strcol + 3]; Pixel* i34 = &input[strcol + 4]; Pixel* i35 = &input[strcol + 5];
    float r30 = i30->r; float g30 = i30->g; float b30 = i30->b;
    float r31 = i31->r; float g31 = i31->g; float b31 = i31->b;
    float r32 = i32->r; float g32 = i32->g; float b32 = i32->b;
    float r33 = i33->r; float g33 = i33->g; float b33 = i33->b;
    float r34 = i34->r; float g34 = i34->g; float b34 = i34->b;
    float r35 = i35->r; float g35 = i35->g; float b35 = i35->b;
    //5번째 줄 6개
    strcol += width;
    Pixel* i40 = &input[strcol]; Pixel* i41 = &input[strcol + 1]; Pixel* i42 = &input[strcol + 2];
    Pixel* i43 = &input[strcol + 3]; Pixel* i44 = &input[strcol + 4]; Pixel* i45 = &input[strcol + 5];
    float r40 = i40->r; float g40 = i40->g; float b40 = i40->b;
    float r41 = i41->r; float g41 = i41->g; float b41 = i41->b;
    float r42 = i42->r; float g42 = i42->g; float b42 = i42->b;
    float r43 = i43->r; float g43 = i43->g; float b43 = i43->b;
    float r44 = i44->r; float g44 = i44->g; float b44 = i44->b;
    float r45 = i45->r; float g45 = i45->g; float b45 = i45->b;

    //6번째 줄 6개
    strcol += width;
    Pixel* i50 = &input[strcol]; Pixel* i51 = &input[strcol + 1]; Pixel* i52 = &input[strcol + 2];
    Pixel* i53 = &input[strcol + 3]; Pixel* i54 = &input[strcol + 4]; Pixel* i55 = &input[strcol + 5];
    float r50 = i50->r; float g50 = i50->g; float b50 = i50->b;
    float r51 = i51->r; float g51 = i51->g; float b51 = i51->b;
    float r52 = i52->r; float g52 = i52->g; float b52 = i52->b;
    float r53 = i53->r; float g53 = i53->g; float b53 = i53->b;
    float r54 = i54->r; float g54 = i54->g; float b54 = i54->b;
    float r55 = i55->r; float g55 = i55->g; float b55 = i55->b;

    //첫번째 덧셈
    float rr11 = r00 * filt0; float rr12 = r01 * filt0; float rr13 = r02 * filt0; float rr14 = r03 * filt0;
    float rr21 = r10 * filt0; float rr22 = r11 * filt0; float rr23 = r12 * filt0; float rr24 = r13 * filt0;
    float rr31 = r20 * filt0; float rr32 = r21 * filt0; float rr33 = r22 * filt0; float rr34 = r23 * filt0;
    float rr41 = r30 * filt0; float rr42 = r31 * filt0; float rr43 = r32 * filt0; float rr44 = r33 * filt0;

    //두번째 덧셈
    rr11 += r01 * filt1; rr12 += r02 * filt1; rr13 += r03 * filt1; rr14 += r04 * filt1;
    rr21 += r11 * filt1; rr22 += r12 * filt1; rr23 += r13 * filt1; rr24 += r14 * filt1;
    rr31 += r21 * filt1; rr32 += r22 * filt1; rr33 += r23 * filt1; rr34 += r24 * filt1;
    rr41 += r31 * filt1; rr42 += r32 * filt1; rr43 += r33 * filt1; rr44 += r34 * filt1;

    //세번째 덧셈
    rr11 += r02 * filt2; rr12 += r03 * filt2; rr13 += r04 * filt2; rr14 += r05 * filt2;
    rr21 += r12 * filt2; rr22 += r13 * filt2; rr23 += r14 * filt2; rr24 += r15 * filt2;
    rr31 += r22 * filt2; rr32 += r23 * filt2; rr33 += r24 * filt2; rr34 += r25 * filt2;
    rr41 += r32 * filt2; rr42 += r33 * filt2; rr43 += r34 * filt2; rr44 += r35 * filt2;

    //네번째 덧셈
    rr11 += r10 * filt3; rr12 += r11 * filt3; rr13 += r12 * filt3; rr14 += r13 * filt3;
    rr21 += r20 * filt3; rr22 += r21 * filt3; rr23 += r22 * filt3; rr24 += r23 * filt3;
    rr31 += r30 * filt3; rr32 += r31 * filt3; rr33 += r32 * filt3; rr34 += r33 * filt3;
    rr41 += r40 * filt3; rr42 += r41 * filt3; rr43 += r42 * filt3; rr44 += r43 * filt3;

    //다섯번째 덧셈
    rr11 += r11 * filt4; rr12 += r12 * filt4; rr13 += r13 * filt4; rr14 += r14 * filt4;
    rr21 += r21 * filt4; rr22 += r22 * filt4; rr23 += r23 * filt4; rr24 += r24 * filt4;
    rr31 += r31 * filt4; rr32 += r32 * filt4; rr33 += r33 * filt4; rr34 += r34 * filt4;
    rr41 += r41 * filt4; rr42 += r42 * filt4; rr43 += r43 * filt4; rr44 += r44 * filt4;

    //여섯번째 덧셈
    rr11 += r12 * filt5; rr12 += r13 * filt5; rr13 += r14 * filt5; rr14 += r15 * filt5;
    rr21 += r22 * filt5; rr22 += r23 * filt5; rr23 += r24 * filt5; rr24 += r25 * filt5;
    rr31 += r32 * filt5; rr32 += r33 * filt5; rr33 += r34 * filt5; rr34 += r35 * filt5;
    rr41 += r42 * filt5; rr42 += r43 * filt5; rr43 += r44 * filt5; rr44 += r45 * filt5;

    //일곱번째 덧셈
    rr11 += r20 * filt6; rr12 += r21 * filt6; rr13 += r22 * filt6; rr14 += r23 * filt6;
    rr21 += r30 * filt6; rr22 += r31 * filt6; rr23 += r32 * filt6; rr24 += r33 * filt6;
    rr31 += r40 * filt6; rr32 += r41 * filt6; rr33 += r42 * filt6; rr34 += r43 * filt6;
    rr41 += r50 * filt6; rr42 += r51 * filt6; rr43 += r52 * filt6; rr44 += r53 * filt6;

    //여덟번째 덧셈
    rr11 += r21 * filt7; rr12 += r22 * filt7; rr13 += r23 * filt7; rr14 += r24 * filt7;
    rr21 += r31 * filt7; rr22 += r32 * filt7; rr23 += r33 * filt7; rr24 += r34 * filt7;
    rr31 += r41 * filt7; rr32 += r42 * filt7; rr33 += r43 * filt7; rr34 += r44 * filt7;
    rr41 += r51 * filt7; rr42 += r52 * filt7; rr43 += r53 * filt7; rr44 += r54 * filt7;

    //아홉번째 덧셈
    rr11 += r22 * filt8; rr12 += r23 * filt8; rr13 += r24 * filt8; rr14 += r25 * filt8;
    rr21 += r32 * filt8; rr22 += r33 * filt8; rr23 += r34 * filt8; rr24 += r35 * filt8;
    rr31 += r42 * filt8; rr32 += r43 * filt8; rr33 += r44 * filt8; rr34 += r45 * filt8;
    rr41 += r52 * filt8; rr42 += r53 * filt8; rr43 += r54 * filt8; rr44 += r55 * filt8;

    //g

    float gg11 = g00 * filt0; float gg12 = g01 * filt0; float gg13 = g02 * filt0; float gg14 = g03 * filt0;
    float gg21 = g10 * filt0; float gg22 = g11 * filt0; float gg23 = g12 * filt0; float gg24 = g13 * filt0;
    float gg31 = g20 * filt0; float gg32 = g21 * filt0; float gg33 = g22 * filt0; float gg34 = g23 * filt0;
    float gg41 = g30 * filt0; float gg42 = g31 * filt0; float gg43 = g32 * filt0; float gg44 = g33 * filt0;

    //두번째 덧셈
    gg11 += g01 * filt1; gg12 += g02 * filt1; gg13 += g03 * filt1; gg14 += g04 * filt1;
    gg21 += g11 * filt1; gg22 += g12 * filt1; gg23 += g13 * filt1; gg24 += g14 * filt1;
    gg31 += g21 * filt1; gg32 += g22 * filt1; gg33 += g23 * filt1; gg34 += g24 * filt1;
    gg41 += g31 * filt1; gg42 += g32 * filt1; gg43 += g33 * filt1; gg44 += g34 * filt1;

    //세번째 덧셈
    gg11 += g02 * filt2; gg12 += g03 * filt2; gg13 += g04 * filt2; gg14 += g05 * filt2;
    gg21 += g12 * filt2; gg22 += g13 * filt2; gg23 += g14 * filt2; gg24 += g15 * filt2;
    gg31 += g22 * filt2; gg32 += g23 * filt2; gg33 += g24 * filt2; gg34 += g25 * filt2;
    gg41 += g32 * filt2; gg42 += g33 * filt2; gg43 += g34 * filt2; gg44 += g35 * filt2;

    //네번째 덧셈
    gg11 += g10 * filt3; gg12 += g11 * filt3; gg13 += g12 * filt3; gg14 += g13 * filt3;
    gg21 += g20 * filt3; gg22 += g21 * filt3; gg23 += g22 * filt3; gg24 += g23 * filt3;
    gg31 += g30 * filt3; gg32 += g31 * filt3; gg33 += g32 * filt3; gg34 += g33 * filt3;
    gg41 += g40 * filt3; gg42 += g41 * filt3; gg43 += g42 * filt3; gg44 += g43 * filt3;

    //다섯번째 덧셈
    gg11 += g11 * filt4; gg12 += g12 * filt4; gg13 += g13 * filt4; gg14 += g14 * filt4;
    gg21 += g21 * filt4; gg22 += g22 * filt4; gg23 += g23 * filt4; gg24 += g24 * filt4;
    gg31 += g31 * filt4; gg32 += g32 * filt4; gg33 += g33 * filt4; gg34 += g34 * filt4;
    gg41 += g41 * filt4; gg42 += g42 * filt4; gg43 += g43 * filt4; gg44 += g44 * filt4;

    //여섯번째 덧셈
    gg11 += g12 * filt5; gg12 += g13 * filt5; gg13 += g14 * filt5; gg14 += g15 * filt5;
    gg21 += g22 * filt5; gg22 += g23 * filt5; gg23 += g24 * filt5; gg24 += g25 * filt5;
    gg31 += g32 * filt5; gg32 += g33 * filt5; gg33 += g34 * filt5; gg34 += g35 * filt5;
    gg41 += g42 * filt5; gg42 += g43 * filt5; gg43 += g44 * filt5; gg44 += g45 * filt5;

    //일곱번째 덧셈
    gg11 += g20 * filt6; gg12 += g21 * filt6; gg13 += g22 * filt6; gg14 += g23 * filt6;
    gg21 += g30 * filt6; gg22 += g31 * filt6; gg23 += g32 * filt6; gg24 += g33 * filt6;
    gg31 += g40 * filt6; gg32 += g41 * filt6; gg33 += g42 * filt6; gg34 += g43 * filt6;
    gg41 += g50 * filt6; gg42 += g51 * filt6; gg43 += g52 * filt6; gg44 += g53 * filt6;

    //여덟번째 덧셈
    gg11 += g21 * filt7; gg12 += g22 * filt7; gg13 += g23 * filt7; gg14 += g24 * filt7;
    gg21 += g31 * filt7; gg22 += g32 * filt7; gg23 += g33 * filt7; gg24 += g34 * filt7;
    gg31 += g41 * filt7; gg32 += g42 * filt7; gg33 += g43 * filt7; gg34 += g44 * filt7;
    gg41 += g51 * filt7; gg42 += g52 * filt7; gg43 += g53 * filt7; gg44 += g54 * filt7;

    //아홉번째 덧셈
    gg11 += g22 * filt8; gg12 += g23 * filt8; gg13 += g24 * filt8; gg14 += g25 * filt8;
    gg21 += g32 * filt8; gg22 += g33 * filt8; gg23 += g34 * filt8; gg24 += g35 * filt8;
    gg31 += g42 * filt8; gg32 += g43 * filt8; gg33 += g44 * filt8; gg34 += g45 * filt8;
    gg41 += g52 * filt8; gg42 += g53 * filt8; gg43 += g54 * filt8; gg44 += g55 * filt8;

    //b
    float bb11 = b00 * filt0; float bb12 = b01 * filt0; float bb13 = b02 * filt0; float bb14 = b03 * filt0;
    float bb21 = b10 * filt0; float bb22 = b11 * filt0; float bb23 = b12 * filt0; float bb24 = b13 * filt0;
    float bb31 = b20 * filt0; float bb32 = b21 * filt0; float bb33 = b22 * filt0; float bb34 = b23 * filt0;
    float bb41 = b30 * filt0; float bb42 = b31 * filt0; float bb43 = b32 * filt0; float bb44 = b33 * filt0;

    //두번째 덧셈
    bb11 += b01 * filt1; bb12 += b02 * filt1; bb13 += b03 * filt1; bb14 += b04 * filt1;
    bb21 += b11 * filt1; bb22 += b12 * filt1; bb23 += b13 * filt1; bb24 += b14 * filt1;
    bb31 += b21 * filt1; bb32 += b22 * filt1; bb33 += b23 * filt1; bb34 += b24 * filt1;
    bb41 += b31 * filt1; bb42 += b32 * filt1; bb43 += b33 * filt1; bb44 += b34 * filt1;

    //세번째 덧셈
    bb11 += b02 * filt2; bb12 += b03 * filt2; bb13 += b04 * filt2; bb14 += b05 * filt2;
    bb21 += b12 * filt2; bb22 += b13 * filt2; bb23 += b14 * filt2; bb24 += b15 * filt2;
    bb31 += b22 * filt2; bb32 += b23 * filt2; bb33 += b24 * filt2; bb34 += b25 * filt2;
    bb41 += b32 * filt2; bb42 += b33 * filt2; bb43 += b34 * filt2; bb44 += b35 * filt2;

    //네번째 덧셈
    bb11 += b10 * filt3; bb12 += b11 * filt3; bb13 += b12 * filt3; bb14 += b13 * filt3;
    bb21 += b20 * filt3; bb22 += b21 * filt3; bb23 += b22 * filt3; bb24 += b23 * filt3;
    bb31 += b30 * filt3; bb32 += b31 * filt3; bb33 += b32 * filt3; bb34 += b33 * filt3;
    bb41 += b40 * filt3; bb42 += b41 * filt3; bb43 += b42 * filt3; bb44 += b43 * filt3;

    //다섯번째 덧셈
    bb11 += b11 * filt4; bb12 += b12 * filt4; bb13 += b13 * filt4; bb14 += b14 * filt4;
    bb21 += b21 * filt4; bb22 += b22 * filt4; bb23 += b23 * filt4; bb24 += b24 * filt4;
    bb31 += b31 * filt4; bb32 += b32 * filt4; bb33 += b33 * filt4; bb34 += b34 * filt4;
    bb41 += b41 * filt4; bb42 += b42 * filt4; bb43 += b43 * filt4; bb44 += b44 * filt4;

    //여섯번째 덧셈
    bb11 += b12 * filt5; bb12 += b13 * filt5; bb13 += b14 * filt5; bb14 += b15 * filt5;
    bb21 += b22 * filt5; bb22 += b23 * filt5; bb23 += b24 * filt5; bb24 += b25 * filt5;
    bb31 += b32 * filt5; bb32 += b33 * filt5; bb33 += b34 * filt5; bb34 += b35 * filt5;
    bb41 += b42 * filt5; bb42 += b43 * filt5; bb43 += b44 * filt5; bb44 += b45 * filt5;

    //일곱번째 덧셈
    bb11 += b20 * filt6; bb12 += b21 * filt6; bb13 += b22 * filt6; bb14 += b23 * filt6;
    bb21 += b30 * filt6; bb22 += b31 * filt6; bb23 += b32 * filt6; bb24 += b33 * filt6;
    bb31 += b40 * filt6; bb32 += b41 * filt6; bb33 += b42 * filt6; bb34 += b43 * filt6;
    bb41 += b50 * filt6; bb42 += b51 * filt6; bb43 += b52 * filt6; bb44 += b53 * filt6;

    //여덟번째 덧셈
    bb11 += b21 * filt7; bb12 += b22 * filt7; bb13 += b23 * filt7; bb14 += b24 * filt7;
    bb21 += b31 * filt7; bb22 += b32 * filt7; bb23 += b33 * filt7; bb24 += b34 * filt7;
    bb31 += b41 * filt7; bb32 += b42 * filt7; bb33 += b43 * filt7; bb34 += b44 * filt7;
    bb41 += b51 * filt7; bb42 += b52 * filt7; bb43 += b53 * filt7; bb44 += b54 * filt7;

    //아홉번째 덧셈
    bb11 += b22 * filt8; bb12 += b23 * filt8; bb13 += b24 * filt8; bb14 += b25 * filt8;
    bb21 += b32 * filt8; bb22 += b33 * filt8; bb23 += b34 * filt8; bb24 += b35 * filt8;
    bb31 += b42 * filt8; bb32 += b43 * filt8; bb33 += b44 * filt8; bb34 += b45 * filt8;
    bb41 += b52 * filt8; bb42 += b53 * filt8; bb43 += b54 * filt8; bb44 += b55 * filt8;

    Pixel* out11 = &output[start]; Pixel* out12 = &output[start + 1]; Pixel* out13 = &output[start + 2]; Pixel* out14 = &output[start + 3];
    start += width;
    Pixel* out21 = &output[start]; Pixel* out22 = &output[start + 1]; Pixel* out23 = &output[start + 2]; Pixel* out24 = &output[start + 3];
    start += width;
    Pixel* out31 = &output[start]; Pixel* out32 = &output[start + 1]; Pixel* out33 = &output[start + 2]; Pixel* out34 = &output[start + 3];
    start += width;
    Pixel* out41 = &output[start]; Pixel* out42 = &output[start + 1]; Pixel* out43 = &output[start + 2]; Pixel* out44 = &output[start + 3];
    out11->r = fit(rr11); out11->g = fit(gg11); out11->b =fit(bb11);
    out12->r = fit(rr12); out12->g = fit(gg12); out12->b =fit(bb12);
    out13->r = fit(rr13); out13->g = fit(gg13); out13->b =fit(bb13);
    out14->r = fit(rr14); out14->g = fit(gg14); out14->b =fit(bb14);
    
    out21->r = fit(rr21); out21->g = fit(gg21); out21->b =fit(bb21);
    out22->r = fit(rr22); out22->g = fit(gg22); out22->b =fit(bb22);
    out23->r = fit(rr23); out23->g = fit(gg23); out23->b =fit(bb23);
    out24->r = fit(rr24); out24->g = fit(gg24); out24->b =fit(bb24);

    out31->r = fit(rr31); out31->g = fit(gg31); out31->b =fit(bb31);
    out32->r = fit(rr32); out32->g = fit(gg32); out32->b =fit(bb32);
    out33->r = fit(rr33); out33->g = fit(gg33); out33->b =fit(bb33);
    out34->r = fit(rr34); out34->g = fit(gg34); out34->b =fit(bb34);

    out41->r = fit(rr41); out41->g = fit(gg41); out41->b =fit(bb41);
    out42->r = fit(rr42); out42->g = fit(gg42); out42->b =fit(bb42);
    out43->r = fit(rr43); out43->g = fit(gg43); out43->b =fit(bb43);
    out44->r = fit(rr44); out44->g = fit(gg44); out44->b =fit(bb44);




}
inline static unsigned char* convolution_in(
		Pixel* input, int start, int width, int height, float*filter){    
    //test 
    //-1,-1
    float filt=filter[0];
    int inpval=start-width-1;
    Pixel* i1=&input[inpval];
    float r=i1->r*filt;
    float g=i1->g*filt;
    float b=i1->b*filt;

    //0,-1
    filt=filter[1];
    Pixel* i2=&input[inpval+1];
    r+=i2->r*filt;
    g+=i2->g*filt;
    b+=i2->b*filt;

    //1,-1
    filt=filter[2];
    Pixel *i3=&input[inpval+2];
    r+=i3->r*filt;
    g+=i3->g*filt;
    b+=i3->b*filt;

    inpval+=width;
    

    //-1,0
    filt=filter[3];
    Pixel *i4=&input[inpval];
    r+=i4->r*filt;
    g+=i4->g*filt;
    b+=i4->b*filt;

    //0,0
    filt=filter[4];
    Pixel *i5=&input[inpval+1];
    r+=i5->r *filt;
    g+=i5->g *filt;
    b+=i5->b *filt;

    //1,0
    filt=filter[5];
    Pixel* i6=&input[inpval+2];
    r+=i6->r *filt;
    g+=i6->g *filt;
    b+=i6->b *filt;
    

    inpval+=width;
    //-1,1
    filt=filter[6];
    Pixel* i7=&input[inpval];
    r+=i7->r *filt;
    g+=i7->g *filt;
    b+=i7->b *filt;

    //0,1
    filt=filter[7];
    Pixel*i8=&input[inpval+1];
    r+=i8->r *filt;
    g+=i8->g *filt;
    b+=i8->b * filt;
    //1,1
    filt=filter[8];
    Pixel*i9=&input[inpval+2];
    r+=i9->r *filt;
    g+=i9->g *filt;
    b+=i9->b *filt;
    
    if(r>=0 && r<=255){
	    ret[0]=(unsigned char)r;
    }
    else if (r<0) ret[0]=0;
    else ret[0]=255;
    
    if(g>=0 && g<=255){
	    ret[1]=(unsigned char)g;
    }
    else if(g<0) ret[1]=0;
    else ret[1]=255;
    
    
    if(b>=0 && b<=255){
            ret[2]=(unsigned char)b;
    }
    else if(b<0) ret[2]=0;
    else ret[2]=255;


   

    return ret;
}

inline static Pixel convolution(
        Pixel* input, int x, int y, int width, int height, float* filter) {
    double r = 0;
    double g = 0;
    double b = 0;
    //y=-1
    int inpval=x+(y-1)*width-1;

    //-1,-1
    if(y>0 && x>0){

    	double filt=filter[0];
    	Pixel* i1=&input[inpval];
    	r+=i1->r*filt;
    	g+=i1->g*filt;
    	b+=i1->b*filt;
    }
    //0,-1
    if(y>0){

        double filt=filter[1];
        Pixel* i1=&input[inpval+1];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }
    //1,-1
    if(y>0 && x<(width-1)){

        double filt=filter[2];
        Pixel* i1=&input[inpval+2];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }

    inpval+=width;

    //-1,0
    if(x>0){

        double filt=filter[3];
        Pixel* i1=&input[inpval];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }
    //0,0

        double filt=filter[4];
        Pixel* i1=&input[inpval+1];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;

    //1,-0
    if(x<width-1){

        double filt=filter[5];
	Pixel* i1=&input[inpval+2];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }

    inpval+=width;

    //-1,1
    if(x>0 && y<(height-1)){

        double filt=filter[6];
        Pixel* i1=&input[inpval];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }
    //0,1
    if(y<(height-1)){

        double filt=filter[7];
        Pixel* i1=&input[inpval+1];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }

    //1,1
    if(x<(width-1) && y<(height-1)){

        double filt=filter[8];
	Pixel* i1= &input[inpval+2];
        r+=i1->r*filt;
        g+=i1->g*filt;
        b+=i1->b*filt;
    }
    
    if(r>=0.0){
	    if(r<=255.0){
		    if(g>=0.0){
			    if(g<=255){
				    if(b>=0.0){
					    if(b<=255){
						    Pixel p;
						    memset(&p,0,sizeof(p));
						    p.r=(unsigned char)r;
						    p.g=(unsigned char)g;
						    p.b=(unsigned char)b;
						    return p;
					    }

				   }
			    }
		    }
	    }
    }
 	
    if (r < 0) r = 0;
    else if(r>255)r = 255;
    if (g < 0) g = 0;
    else if(g>255) g= 255;
    if (b < 0) b = 0;
    else if(b>255) b=255;
    
    Pixel p;
    memset(&p, 0, sizeof(p));

    p.r = (unsigned char)r;
    p.g = (unsigned char)g;
    p.b = (unsigned char)b;
    return p;
}

inline void filter_optimized(void* args[]) {
    unsigned short int width = *(unsigned short int*)args[0];
    unsigned short int height = *(unsigned short int*)args[1];
    Pixel* input=args[2];
    Pixel* output = args[3];
    float* filter = args[4];
    int x =0;
    int y = 0;
    int ywid=0;
    for (y = 1; y < height - 1; ++y) {

        ywid += width;
        for (x = 1; x < 4; ++x) {
            unsigned char* outval = convolution_in(input, x + ywid, width, height, filter);
            Pixel* out = &output[x + ywid];
            out->r = outval[0];
            out->g = outval[1];
            out->b = outval[2];
        }
        for (x = width - 4; x < width - 1; x++) {
            unsigned char* outval = convolution_in(input, x + ywid, width, height, filter);
            Pixel* out = &output[x + ywid];
            out->r = outval[0];
            out->g = outval[1];
            out->b = outval[2];
        }
    }
    ywid = 0;
    for (y = 1; y < 4; ++y) {
        ywid += width;
        for (x = 1; x < width - 1; ++x) {
            unsigned char* outval = convolution_in(input, x + ywid, width, height, filter);
            Pixel* out = &output[x + ywid];
            out->r = outval[0];
            out->g = outval[1];
            out->b = outval[2];
        }
    }
    ywid = (height-5)*width;
    for (y = height - 4; y < height - 1; y++) {
        ywid += width;
        for (x = 1; x < width - 1; ++x) {
            unsigned char* outval = convolution_in(input, x + ywid, width, height, filter);
            Pixel* out = &output[x + ywid];
            out->r = outval[0];
            out->g = outval[1];
            out->b = outval[2];
        }
    }
    ywid = 0;
    int start_1;
	for(y=4;y<height-4;y+=4){
        ywid +=width<<2;
        for (x = 4; x < height - 4; x += 4) {
            start_1 = ywid + x;
            convolution_block(input, output, start_1, width, height, filter);
        }
		
   	}

    //가로 끝
    for(y = 0; y<height; ++y){
	    
	    x=0;
	    int ywid=y*width;
	    Pixel p = convolution(input,x,y,width,height,filter);
	    Pixel* out =&output[ywid];
	    out->r=p.r;
	    out->g=p.g;
	    out->b=p.b;

	    x=width-1;
            p = convolution(input,x,y,width,height,filter);
	    Pixel* out2 = &output[ywid+x];
            out2->r=p.r;
            out2->g=p.g;
            out2->b=p.b;
    }
    //세로 끝(꼭지점 제외)
    for(x=1; x<width-1; ++x){
	    
	    y=0;
	    Pixel p= convolution(input,x,y,width,height,filter);
	    Pixel* out= &output[x];
	    out->r=p.r;
	    out->g=p.g;
            out->b=p.b;
	    
	    y=height-1;
	    Pixel q=convolution(input,x,y,width,height,filter);
	    int outv=x+y*width;
	    Pixel* out2=&output[outv];
	    out2->r=q.r;
	    out2->g=q.g;
	    out2->b=q.b;
    }    
	
}

