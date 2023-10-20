xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 380;
 20.88434;1.52911;1.22234;,
 23.58980;2.46265;1.22234;,
 23.41892;2.95779;1.74612;,
 20.71346;2.02425;1.74612;,
 20.71346;2.02425;1.74612;,
 23.41892;2.95779;1.74612;,
 23.18558;3.63415;1.93784;,
 20.48010;2.70061;1.93784;,
 22.95182;4.31053;1.74612;,
 20.24672;3.37699;1.74612;,
 20.24672;3.37699;1.74612;,
 22.95182;4.31053;1.74612;,
 22.78096;4.80567;1.22234;,
 20.07584;3.87211;1.22234;,
 22.71844;4.98689;0.50684;,
 20.01332;4.05333;0.50684;,
 22.78096;4.80567;-0.20866;,
 20.07584;3.87211;-0.20866;,
 22.95182;4.31053;-0.73244;,
 20.24672;3.37699;-0.73244;,
 20.24672;3.37699;-0.73244;,
 22.95182;4.31053;-0.73244;,
 23.18558;3.63415;-0.92416;,
 20.48010;2.70061;-0.92416;,
 23.41892;2.95779;-0.73244;,
 20.71346;2.02425;-0.73244;,
 20.71346;2.02425;-0.73244;,
 23.41892;2.95779;-0.73244;,
 23.58980;2.46265;-0.20866;,
 20.88434;1.52911;-0.20866;,
 23.65232;2.28141;0.50684;,
 20.94686;1.34787;0.50684;,
 20.71346;2.02425;1.74612;,
 20.48010;2.70061;0.50684;,
 20.88434;1.52911;1.22234;,
 20.48010;2.70061;1.93784;,
 20.24672;3.37699;1.74612;,
 20.07584;3.87211;1.22234;,
 20.01332;4.05333;0.50684;,
 20.07584;3.87211;-0.20866;,
 20.24672;3.37699;-0.73244;,
 20.48010;2.70061;-0.92416;,
 20.71346;2.02425;-0.73244;,
 20.88434;1.52911;-0.20866;,
 20.94686;1.34787;0.50684;,
 23.58980;2.46265;1.22234;,
 23.18558;3.63415;0.50684;,
 23.41892;2.95779;1.74612;,
 23.18558;3.63415;1.93784;,
 22.95182;4.31053;1.74612;,
 22.78096;4.80567;1.22234;,
 22.71844;4.98689;0.50684;,
 22.78096;4.80567;-0.20866;,
 22.95182;4.31053;-0.73244;,
 23.18558;3.63415;-0.92416;,
 23.41892;2.95779;-0.73244;,
 23.58980;2.46265;-0.20866;,
 23.65232;2.28141;0.50684;,
 5.69812;4.44965;-4.31800;,
 8.18384;4.44965;-4.31800;,
 9.12466;2.11067;-3.82774;,
 6.59132;1.97831;-3.82774;,
 5.69812;4.44965;5.70090;,
 8.18384;4.44965;5.70090;,
 8.18384;4.44965;-4.31800;,
 5.69812;4.44965;-4.31800;,
 8.18384;4.44965;5.70090;,
 5.69812;4.44965;5.70090;,
 6.59132;1.97831;5.21064;,
 9.12466;2.11067;5.21064;,
 7.71642;-4.08795;-6.70290;,
 10.06964;-4.10711;-6.45242;,
 10.06964;-4.10711;6.86136;,
 7.71642;-4.08795;6.86136;,
 21.97292;2.78209;-4.80826;,
 20.79052;4.96133;-4.80826;,
 20.79052;4.96133;6.19116;,
 21.97292;2.78209;6.19116;,
 0.65278;3.14655;6.19116;,
 1.23426;4.96133;6.19116;,
 1.23426;4.96133;-4.80826;,
 0.65278;3.14655;-4.80826;,
 0.05956;-1.62539;6.86136;,
 0.05956;-1.62539;-5.13046;,
 2.34888;-5.09319;-6.09734;,
 2.14972;-5.09319;6.86136;,
 1.23426;4.96133;6.19116;,
 0.65278;3.14655;6.19116;,
 3.73764;1.82919;6.19116;,
 2.89812;4.96133;6.19116;,
 1.23426;4.96133;-4.80826;,
 1.23426;4.96133;6.19116;,
 2.89812;4.96133;6.19116;,
 2.89812;4.96133;-4.80826;,
 0.65278;3.14655;-4.80826;,
 1.23426;4.96133;-4.80826;,
 2.89812;4.96133;-4.80826;,
 3.93682;1.82919;-5.69512;,
 -0.01390;2.29987;-5.07210;,
 4.97476;-0.70547;-6.00792;,
 9.84868;-0.72507;-6.35158;,
 7.46296;-0.71585;-6.59404;,
 6.59132;1.97831;-6.25058;,
 9.12466;2.11067;-6.02080;,
 21.94822;-0.77181;-5.07210;,
 21.94822;-0.77181;6.53462;,
 9.12466;2.11067;6.19116;,
 6.59132;1.97831;6.19116;,
 7.46296;-0.71585;6.53462;,
 9.84868;-0.72507;6.53462;,
 -0.01390;2.29987;6.53462;,
 4.77560;-0.70547;6.53462;,
 -0.01390;2.29987;6.53462;,
 -0.01390;2.29987;-5.07210;,
 0.01638;0.40927;-5.18144;,
 2.44660;-3.29297;-5.95054;,
 7.56852;-2.90073;-6.73638;,
 9.80398;-2.97207;-6.48868;,
 19.75856;-1.97225;-5.18144;,
 21.94822;-0.77181;-5.07210;,
 21.94822;-0.77181;6.53462;,
 19.75856;-1.97275;6.74626;,
 10.72022;-2.88733;6.74626;,
 7.56852;-2.90121;6.74626;,
 0.01638;0.40881;6.74626;,
 2.98654;-3.29343;6.25246;,
 0.01638;0.40881;6.74626;,
 0.01638;0.40927;-5.18144;,
 21.94822;-0.77181;-5.07210;,
 19.75856;-1.97225;-5.18144;,
 18.28620;-2.23387;-5.37528;,
 20.57194;-0.76649;-5.26182;,
 21.97292;2.78209;-4.80826;,
 18.09788;2.70573;-4.98806;,
 19.35656;4.96133;-4.80826;,
 20.79052;4.96133;-4.80826;,
 19.35656;4.96133;6.19116;,
 20.79052;4.96133;6.19116;,
 20.79052;4.96133;-4.80826;,
 19.35656;4.96133;-4.80826;,
 21.97292;2.78209;6.19116;,
 20.79052;4.96133;6.19116;,
 19.35656;4.96133;6.19116;,
 18.69478;2.70573;6.19116;,
 21.94822;-0.77181;6.53462;,
 20.57194;-0.76649;6.53462;,
 19.75856;-1.97275;6.74626;,
 18.38830;-2.10487;6.74626;,
 16.13246;-3.53545;-5.53738;,
 17.22030;-3.28119;-5.27270;,
 17.22030;-3.28119;6.90772;,
 16.13246;-3.53545;6.86136;,
 2.89812;4.96133;-4.80826;,
 2.89812;4.44965;-4.31800;,
 3.73764;1.82919;-3.82774;,
 3.93682;1.82919;-5.69512;,
 6.59132;1.97831;-3.82774;,
 9.12466;2.11067;-3.82774;,
 9.12466;2.11067;-6.02080;,
 6.59132;1.97831;-6.25058;,
 18.09788;2.70573;-4.98806;,
 18.09788;2.70573;-3.82774;,
 19.35656;4.44965;-4.31800;,
 19.35656;4.96133;-4.80826;,
 2.89812;4.96133;6.19116;,
 2.89812;4.44965;5.70090;,
 19.35656;4.44965;5.70090;,
 19.35656;4.96133;6.19116;,
 18.69478;2.70573;5.21064;,
 18.69478;2.70573;6.19116;,
 9.12466;2.11067;5.21064;,
 6.59132;1.97831;5.21064;,
 6.59132;1.97831;6.19116;,
 9.12466;2.11067;6.19116;,
 3.73764;1.82919;6.19116;,
 3.73764;1.82919;5.21064;,
 3.07142;-4.27985;-6.42584;,
 2.98032;-4.27985;6.86136;,
 6.23342;-0.71111;6.53462;,
 4.10336;-2.91489;6.74626;,
 5.28568;1.91007;6.19116;,
 5.28568;1.91007;5.21064;,
 5.28568;1.91007;6.19116;,
 4.41704;4.44965;5.70090;,
 5.28568;1.91007;5.21064;,
 4.41704;4.44965;5.70090;,
 4.41704;4.44965;-4.31800;,
 4.41704;4.44965;-4.31800;,
 5.28568;1.91007;-3.82774;,
 5.28568;1.91007;-3.82774;,
 5.37680;1.91007;-5.99644;,
 6.32454;-0.71111;-6.32588;,
 5.37680;1.91007;-5.99644;,
 3.45534;-2.91443;-6.46240;,
 2.34888;-5.09319;-6.09734;,
 2.14972;-5.09319;6.86136;,
 3.73764;1.82919;5.21064;,
 3.73764;1.82919;6.19116;,
 2.89812;4.44965;5.70090;,
 3.73764;1.82919;5.21064;,
 2.89812;4.44965;5.70090;,
 2.89812;4.44965;-4.31800;,
 2.89812;4.44965;-4.31800;,
 3.73764;1.82919;-3.82774;,
 3.93682;1.82919;-5.69512;,
 3.73764;1.82919;-3.82774;,
 10.09544;2.16141;6.19116;,
 10.76288;-0.72861;6.53462;,
 11.47450;-3.22363;6.74626;,
 10.59986;-4.90977;-6.35642;,
 10.59986;-4.90977;6.86136;,
 10.76288;-0.72861;-6.25868;,
 10.36330;-3.28857;-6.39376;,
 10.09542;2.16141;-5.93276;,
 10.09542;2.16141;-3.82774;,
 10.09542;2.16141;-5.93276;,
 9.13636;4.44965;-4.31800;,
 10.09542;2.16141;-3.82774;,
 9.13636;4.44965;5.70090;,
 9.13636;4.44965;-4.31800;,
 9.13636;4.44965;5.70090;,
 10.09544;2.16141;5.21064;,
 10.09544;2.16141;5.21064;,
 10.09544;2.16141;6.19116;,
 18.09788;2.70573;-3.82774;,
 18.09788;2.70573;-4.98806;,
 19.35656;4.44965;-4.31800;,
 18.09788;2.70573;-3.82774;,
 19.35656;4.44965;5.70090;,
 19.35656;4.44965;-4.31800;,
 19.35656;4.44965;5.70090;,
 18.69478;2.70573;5.21064;,
 18.69478;2.70573;6.19116;,
 18.69478;2.70573;5.21064;,
 0.05956;-1.62539;-5.13046;,
 2.34888;-5.09319;-6.09734;,
 3.07142;-4.27985;-6.42584;,
 7.71642;-4.08795;-6.70290;,
 10.06964;-4.10711;-6.45242;,
 10.59986;-4.90977;-6.35642;,
 16.13246;-3.53545;-5.53738;,
 17.22030;-3.28119;-5.27270;,
 16.13246;-3.53545;6.86136;,
 17.22030;-3.28119;6.90772;,
 10.59986;-4.90977;6.86136;,
 10.06964;-4.10711;6.86136;,
 7.71642;-4.08795;6.86136;,
 2.98032;-4.27985;6.86136;,
 2.14972;-5.09319;6.86136;,
 0.05956;-1.62539;6.86136;,
 16.98826;-10.99871;-2.66628;,
 13.49734;-2.73619;-2.66628;,
 14.61490;-2.26403;-2.66628;,
 18.10580;-10.52653;-2.66628;,
 14.51152;-2.30769;-0.62140;,
 14.51152;-2.30769;1.79870;,
 15.62910;-1.83551;1.79870;,
 15.62910;-1.83551;-0.62140;,
 13.49734;-2.73619;4.04096;,
 16.98826;-10.99871;4.04096;,
 18.10580;-10.52653;4.04096;,
 14.61490;-2.26403;4.04096;,
 18.00244;-10.57021;1.79870;,
 18.00244;-10.57021;-0.62140;,
 19.12000;-10.09805;-0.62140;,
 19.12000;-10.09805;1.79870;,
 15.62910;-1.83551;-0.62140;,
 15.62910;-1.83551;1.79870;,
 19.12000;-10.09805;1.79870;,
 19.12000;-10.09805;-0.62140;,
 14.51152;-2.30769;1.79870;,
 14.51152;-2.30769;-0.62140;,
 18.00244;-10.57021;-0.62140;,
 18.00244;-10.57021;1.79870;,
 13.49734;-2.73619;-2.66628;,
 14.61490;-2.26403;-2.66628;,
 18.10580;-10.52653;-2.66628;,
 14.61490;-2.26403;-2.66628;,
 16.98826;-10.99871;-2.66628;,
 18.10580;-10.52653;-2.66628;,
 13.49734;-2.73619;-2.66628;,
 16.98826;-10.99871;-2.66628;,
 16.98826;-10.99871;4.04096;,
 18.10580;-10.52653;4.04096;,
 14.61490;-2.26403;4.04096;,
 18.10580;-10.52653;4.04096;,
 13.49734;-2.73619;4.04096;,
 14.61490;-2.26403;4.04096;,
 16.98826;-10.99871;4.04096;,
 13.49734;-2.73619;4.04096;,
 9.83098;-4.01437;-6.34496;,
 10.40736;-4.84751;-6.40124;,
 10.59952;-12.68169;-6.80864;,
 9.61232;-13.41537;-6.84564;,
 9.83474;-4.10791;-4.59004;,
 10.41112;-4.94107;-4.64630;,
 10.40736;-4.84751;-6.40124;,
 9.83098;-4.01437;-6.34496;,
 9.61608;-13.50892;-5.09070;,
 10.60328;-12.77523;-5.05370;,
 10.41112;-4.94107;-4.64630;,
 9.83474;-4.10791;-4.59004;,
 9.61232;-13.41537;-6.84564;,
 10.59952;-12.68169;-6.80864;,
 10.60328;-12.77523;-5.05370;,
 9.61608;-13.50892;-5.09070;,
 2.96198;-13.08181;-5.05370;,
 2.52594;-5.25741;-4.64630;,
 2.52218;-5.16385;-6.40124;,
 2.95822;-12.98825;-6.80864;,
 4.09260;-13.63682;-6.84564;,
 6.84246;-14.69100;-6.90772;,
 6.84622;-14.78456;-5.15278;,
 4.09636;-13.73038;-5.09070;,
 4.09636;-13.73038;-5.09070;,
 6.84622;-14.78456;-5.15278;,
 6.42954;-4.20823;-4.58810;,
 3.13554;-4.37669;-4.59004;,
 3.13554;-4.37669;-4.59004;,
 6.42954;-4.20823;-4.58810;,
 6.42578;-4.11467;-6.34304;,
 3.13178;-4.28315;-6.34496;,
 3.13178;-4.28315;-6.34496;,
 6.42578;-4.11467;-6.34304;,
 6.84246;-14.69100;-6.90772;,
 4.09260;-13.63682;-6.84564;,
 2.96198;-13.08181;-5.05370;,
 2.95822;-12.98825;-6.80864;,
 2.52594;-5.25741;-4.64630;,
 2.96198;-13.08181;-5.05370;,
 3.13554;-4.37669;-4.59004;,
 3.13178;-4.28315;-6.34496;,
 2.95822;-12.98825;-6.80864;,
 2.52218;-5.16385;-6.40124;,
 9.83474;-4.10791;-4.59004;,
 9.83098;-4.01437;-6.34496;,
 9.61232;-13.41537;-6.84564;,
 9.61608;-13.50892;-5.09070;,
 7.47804;-4.32677;3.68026;,
 7.91692;-4.95909;3.74730;,
 8.06326;-10.88885;4.46898;,
 7.31154;-11.44401;4.53742;,
 7.48090;-4.16683;5.00888;,
 7.91978;-4.79913;5.07592;,
 7.91692;-4.95909;3.74730;,
 7.47804;-4.32677;3.68026;,
 7.31438;-11.28407;5.86606;,
 8.06610;-10.72889;5.79760;,
 7.91978;-4.79913;5.07592;,
 7.48090;-4.16683;5.00888;,
 7.31154;-11.44401;4.53742;,
 8.06326;-10.88885;4.46898;,
 8.06610;-10.72889;5.79760;,
 7.31438;-11.28407;5.86606;,
 2.24752;-10.95883;5.83780;,
 1.91548;-5.03641;5.11740;,
 1.91262;-5.19637;3.78878;,
 2.24466;-11.11879;4.50918;,
 3.10846;-11.61013;4.56646;,
 5.20236;-12.40901;4.65814;,
 5.20524;-12.24905;5.98676;,
 3.11130;-11.45019;5.89510;,
 3.11130;-11.45019;5.89510;,
 5.20524;-12.24905;5.98676;,
 4.88794;-4.24179;5.02348;,
 2.37968;-4.36841;5.04412;,
 2.37680;-4.52837;3.71550;,
 4.88510;-4.40175;3.69486;,
 5.20236;-12.40901;4.65814;,
 3.10846;-11.61013;4.56646;,
 2.24752;-10.95883;5.83780;,
 2.24466;-11.11879;4.50918;,
 1.91548;-5.03641;5.11740;,
 2.24752;-10.95883;5.83780;,
 2.37968;-4.36841;5.04412;,
 2.37680;-4.52837;3.71550;,
 2.24466;-11.11879;4.50918;,
 1.91262;-5.19637;3.78878;,
 7.31154;-11.44401;4.53742;,
 7.31438;-11.28407;5.86606;;
 
 178;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;20,21,22,23;,
 4;23,22,24,25;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;31,30,1,0;,
 3;32,33,34;,
 3;35,33,32;,
 3;36,33,35;,
 3;37,33,36;,
 3;38,33,37;,
 3;39,33,38;,
 3;40,33,39;,
 3;41,33,40;,
 3;42,33,41;,
 3;43,33,42;,
 3;44,33,43;,
 3;34,33,44;,
 3;45,46,47;,
 3;47,46,48;,
 3;48,46,49;,
 3;49,46,50;,
 3;50,46,51;,
 3;51,46,52;,
 3;52,46,53;,
 3;53,46,54;,
 3;54,46,55;,
 3;55,46,56;,
 3;56,46,57;,
 3;57,46,45;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,94,97,99;,
 4;100,101,102,103;,
 4;104,74,77,105;,
 4;106,107,108,109;,
 4;87,110,111,88;,
 4;112,78,81,113;,
 4;114,98,99,115;,
 4;116,101,100,117;,
 4;118,119,120,121;,
 4;122,109,108,123;,
 4;110,124,125,111;,
 4;126,112,113,127;,
 4;128,129,130,131;,
 4;132,128,131,133;,
 4;134,135,132,133;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,140,143,145;,
 4;146,144,145,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,153,152;,
 4;163,162,166,167;,
 4;167,166,168,169;,
 4;170,171,172,173;,
 4;174,175,165,164;,
 4;176,70,73,177;,
 4;123,108,178,179;,
 4;107,180,178,108;,
 4;171,181,182,172;,
 4;67,183,184,68;,
 4;185,62,65,186;,
 4;187,58,61,188;,
 4;189,156,159,190;,
 4;101,191,192,102;,
 4;193,191,101,116;,
 4;194,176,177,195;,
 4;179,178,111,125;,
 4;180,88,111,178;,
 4;181,196,197,182;,
 4;183,198,199,184;,
 4;200,185,186,201;,
 4;202,187,188,203;,
 4;204,205,189,190;,
 4;191,99,97,192;,
 4;115,99,191,193;,
 4;206,106,109,207;,
 4;208,207,109,122;,
 4;71,209,210,72;,
 4;117,100,211,212;,
 4;211,100,103,213;,
 4;157,214,215,158;,
 4;59,216,217,60;,
 4;63,218,219,64;,
 4;220,66,69,221;,
 4;222,170,173,223;,
 4;143,206,207,145;,
 4;147,145,207,208;,
 4;209,148,151,210;,
 4;212,211,131,130;,
 4;131,211,213,133;,
 4;214,224,225,215;,
 4;216,226,227,217;,
 4;218,228,229,219;,
 4;230,220,221,231;,
 4;232,233,222,223;,
 4;234,114,115,235;,
 4;236,235,115,193;,
 4;237,236,193,116;,
 4;238,237,116,117;,
 4;239,238,117,212;,
 4;240,239,212,130;,
 4;129,241,240,130;,
 4;149,118,121,150;,
 4;242,243,146,147;,
 4;244,242,147,208;,
 4;245,244,208,122;,
 4;246,245,122,123;,
 4;247,246,123,179;,
 4;248,247,179,125;,
 4;124,249,248,125;,
 4;82,126,127,83;,
 4;250,251,252,253;,
 4;254,255,256,257;,
 4;258,259,260,261;,
 4;262,263,264,265;,
 4;266,267,268,269;,
 4;270,271,272,273;,
 4;274,254,257,275;,
 4;276,277,266,269;,
 4;263,278,279,264;,
 4;271,280,281,272;,
 4;282,262,265,283;,
 4;267,284,285,268;,
 4;255,286,287,256;,
 4;288,289,270,273;,
 4;290,291,292,293;,
 4;294,295,296,297;,
 4;298,299,300,301;,
 4;302,303,304,305;,
 4;303,296,295,304;,
 4;306,307,308,309;,
 4;310,311,312,313;,
 4;314,315,316,317;,
 4;318,319,320,321;,
 4;322,323,324,325;,
 4;326,327,310,313;,
 4;328,329,314,317;,
 4;308,307,330,331;,
 4;332,333,322,325;,
 4;323,290,293,324;,
 4;319,334,335,320;,
 4;315,298,301,316;,
 4;311,336,337,312;,
 4;338,339,340,341;,
 4;342,343,344,345;,
 4;346,347,348,349;,
 4;350,351,352,353;,
 4;351,344,343,352;,
 4;354,355,356,357;,
 4;358,359,360,361;,
 4;362,363,364,365;,
 4;366,367,368,369;,
 4;370,371,358,361;,
 4;372,373,362,365;,
 4;356,355,374,375;,
 4;376,377,366,369;,
 4;367,338,341,368;,
 4;363,346,349,364;,
 4;359,378,379,360;;
 
 MeshMaterialList {
  1;
  178;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MATERIAL\\ac2_01.png";
   }
  }
 }
 MeshNormals {
  214;
  0.282483;-0.818654;0.500009;,
  0.163091;-0.472650;0.866027;,
  0.000003;-0.000016;1.000000;,
  -0.163106;0.472636;0.866032;,
  -0.282522;0.818650;0.499993;,
  -0.326228;0.945291;0.000000;,
  -0.282522;0.818650;-0.499993;,
  -0.163106;0.472636;-0.866032;,
  0.000003;-0.000016;-1.000000;,
  0.163091;-0.472650;-0.866027;,
  0.282483;-0.818654;-0.500009;,
  0.326185;-0.945306;-0.000000;,
  -0.945305;-0.326187;0.000000;,
  0.945260;0.326319;-0.000000;,
  -0.957855;-0.287233;-0.003334;,
  0.345548;-0.938401;-0.000009;,
  -0.952310;0.305133;0.000000;,
  0.878958;0.476900;0.000000;,
  -0.846460;-0.532413;-0.006426;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -0.883016;0.469342;0.000000;,
  -0.144658;0.121686;-0.981971;,
  0.970116;0.242641;0.000000;,
  0.038406;0.122257;0.991755;,
  -0.136383;0.151081;-0.979068;,
  -0.222625;0.196530;-0.954890;,
  0.999976;-0.006950;-0.000000;,
  -0.019510;0.132695;0.990965;,
  0.081261;0.115891;0.989932;,
  0.234342;-0.972154;-0.000000;,
  0.113945;0.011684;-0.993418;,
  0.072368;0.087075;-0.993570;,
  0.022621;0.027159;-0.999375;,
  -0.001481;0.068146;0.997674;,
  -0.004812;0.125242;0.992115;,
  0.985724;0.142704;0.089353;,
  0.943303;0.281334;0.176154;,
  -0.506466;0.853127;0.125169;,
  -0.956326;0.268341;0.115903;,
  0.987656;0.141764;-0.066626;,
  -0.984385;0.160455;-0.072386;,
  -0.938029;0.315898;-0.142511;,
  0.950928;0.280027;-0.131607;,
  0.016375;-0.999866;0.000069;,
  -0.001535;0.110628;0.993861;,
  -0.003053;0.124728;0.992186;,
  0.005124;-0.194085;0.980971;,
  0.005124;-0.194085;-0.980971;,
  -0.064331;0.098894;-0.993016;,
  -0.042634;0.090847;-0.994952;,
  0.412923;-0.910756;0.004362;,
  -0.060680;0.130063;0.989647;,
  -0.003137;0.128945;0.991647;,
  -0.052185;0.998637;0.000000;,
  0.004931;-0.187722;0.982210;,
  0.004931;-0.187722;-0.982210;,
  -0.054261;0.998524;-0.002534;,
  -0.246603;0.157716;-0.956197;,
  -0.002945;0.120386;0.992723;,
  0.003955;0.108694;0.994067;,
  -0.477301;-0.878740;0.000000;,
  0.107610;0.096795;-0.989470;,
  0.091297;0.140792;-0.985821;,
  0.005308;-0.201506;-0.979473;,
  0.005308;-0.201506;0.979473;,
  -0.003182;0.112946;0.993596;,
  0.002283;0.110292;0.993897;,
  -0.834387;-0.551179;0.000000;,
  0.112333;0.074096;-0.990904;,
  0.097679;0.138914;-0.985475;,
  -0.060032;0.998197;0.000000;,
  0.006152;-0.221325;-0.975181;,
  0.005917;-0.221419;0.975161;,
  -0.226200;0.057765;-0.972367;,
  -0.339217;0.166735;-0.925814;,
  -0.280669;0.158590;-0.946612;,
  0.000835;0.032814;-0.999461;,
  0.133451;0.025269;-0.990733;,
  0.143976;-0.008015;-0.989549;,
  0.161852;-0.145342;-0.976053;,
  0.469572;-0.882894;-0.000019;,
  -0.021937;0.144630;0.989243;,
  0.010737;0.091314;0.995764;,
  0.016934;0.086633;0.996096;,
  -0.000449;0.095027;0.995475;,
  -0.184031;0.211893;0.959809;,
  -0.105473;0.198138;0.974483;,
  0.156689;0.058534;0.985912;,
  0.000000;0.000000;-1.000000;,
  -0.389189;0.921158;-0.000004;,
  0.389187;-0.921159;-0.000002;,
  0.389187;-0.921159;0.000002;,
  -0.389189;0.921158;0.000004;,
  -0.850867;-0.524730;-0.026152;,
  -0.010552;0.052772;-0.998551;,
  -0.962570;0.270531;0.016483;,
  0.950996;0.308867;0.014427;,
  0.010536;-0.052771;0.998551;,
  -0.006342;0.053002;-0.998574;,
  0.006336;-0.053001;0.998574;,
  0.451641;0.890986;0.046528;,
  -0.428977;-0.902083;-0.047174;,
  -0.001449;-0.053269;0.998579;,
  -0.487018;0.872097;0.047532;,
  0.032683;-0.998045;-0.053276;,
  -0.040207;0.997770;0.053274;,
  0.002136;-0.053231;0.998580;,
  -0.850871;-0.521388;0.064598;,
  -0.010538;-0.119969;-0.992722;,
  -0.962571;0.269324;-0.030350;,
  0.950997;0.306734;-0.038970;,
  0.010548;0.119971;0.992721;,
  -0.006338;-0.119746;-0.992784;,
  0.006341;0.119748;0.992784;,
  0.822955;0.563821;-0.069648;,
  -0.428985;-0.896726;0.108876;,
  -0.001453;0.119485;0.992835;,
  0.001449;-0.119484;-0.992835;,
  0.032684;-0.992309;0.119391;,
  -0.002135;-0.119522;-0.992829;,
  0.002136;0.119523;0.992829;,
  -0.945308;-0.326179;-0.000015;,
  -0.945304;-0.326191;-0.000005;,
  -0.945313;-0.326164;0.000000;,
  -0.945302;-0.326196;0.000014;,
  -0.945299;-0.326206;0.000006;,
  -0.945303;-0.326194;0.000000;,
  -0.945299;-0.326206;-0.000006;,
  -0.945302;-0.326196;-0.000014;,
  -0.945313;-0.326164;0.000000;,
  -0.945308;-0.326179;0.000015;,
  -0.945304;-0.326191;0.000005;,
  -0.945309;-0.326177;0.000000;,
  0.945307;0.326181;0.000011;,
  0.945313;0.326164;0.000020;,
  0.945236;0.326389;0.000000;,
  0.945196;0.326505;0.000086;,
  0.945236;0.326389;0.000127;,
  0.945227;0.326413;0.000000;,
  0.945236;0.326389;-0.000127;,
  0.945196;0.326505;-0.000086;,
  0.945236;0.326389;0.000000;,
  0.945313;0.326164;-0.000020;,
  0.945307;0.326181;-0.000011;,
  0.945313;0.326165;0.000000;,
  0.059358;0.117860;0.991255;,
  -0.107345;0.163153;-0.980744;,
  -0.087589;0.108370;-0.990244;,
  -0.947491;0.319783;-0.000000;,
  0.480805;-0.876828;-0.000018;,
  -0.999827;-0.018616;-0.000000;,
  0.119393;-0.036668;-0.992170;,
  0.193696;-0.249472;-0.948813;,
  0.056526;0.059196;-0.996645;,
  -0.476593;0.869840;0.127427;,
  -0.000474;0.048411;0.998827;,
  -0.004756;0.137672;0.990466;,
  -0.031521;0.183586;0.982498;,
  -0.053161;0.998586;-0.000548;,
  -0.052187;0.998637;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.052186;0.998637;0.000000;,
  -0.052185;0.998637;0.000000;,
  -0.217900;0.043338;-0.975008;,
  0.724574;-0.689151;0.007947;,
  -0.052176;0.998638;0.000000;,
  0.004868;-0.185115;0.982705;,
  0.004868;-0.185115;-0.982705;,
  -0.054375;0.998513;-0.003971;,
  -0.057685;0.998335;0.000000;,
  0.241077;-0.970506;-0.000000;,
  0.006939;-0.237421;-0.971382;,
  0.006470;-0.237608;0.971340;,
  -0.063172;0.998003;0.000000;,
  -0.305318;0.031004;-0.951746;,
  -0.400962;0.068377;-0.913539;,
  -0.285145;0.042005;-0.957563;,
  0.022588;-0.017027;-0.999600;,
  0.143106;-0.002070;-0.989705;,
  0.161369;-0.024934;-0.986579;,
  0.193821;-0.196726;-0.961110;,
  0.238972;-0.332566;-0.912300;,
  -0.036478;0.140899;0.989352;,
  -0.054468;0.188669;0.980529;,
  0.013724;0.074962;0.997092;,
  0.023013;0.076269;0.996822;,
  -0.000883;0.093548;0.995615;,
  -0.250546;0.294403;0.922254;,
  -0.112904;0.322468;0.939823;,
  0.267179;0.119791;0.956172;,
  0.893212;0.377380;-0.244452;,
  0.897273;0.379096;0.226245;,
  -0.897273;-0.379098;-0.226242;,
  -0.893212;-0.377382;0.244449;,
  -0.389187;0.921159;-0.000008;,
  0.811067;0.342674;-0.474072;,
  0.389193;-0.921156;-0.000004;,
  -0.811070;-0.342677;0.474066;,
  0.389193;-0.921156;0.000004;,
  0.826856;0.349345;0.440757;,
  -0.389187;0.921159;0.000007;,
  -0.826858;-0.349348;-0.440751;,
  0.510599;-0.858541;-0.046858;,
  0.899011;-0.437199;-0.025229;,
  0.001454;0.053271;-0.998579;,
  -0.002136;0.053231;-0.998580;,
  -0.005034;-0.053307;0.998565;,
  0.005048;0.053309;-0.998565;,
  0.510597;-0.853786;0.101690;,
  0.899009;-0.435015;0.050444;,
  -0.005043;0.119445;0.992828;,
  -0.822784;0.564488;-0.066184;,
  0.005032;-0.119444;-0.992828;;
  178;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;11,11,0,0;,
  3;122,12,123;,
  3;124,12,122;,
  3;125,12,124;,
  3;126,12,125;,
  3;127,12,126;,
  3;128,12,127;,
  3;129,12,128;,
  3;130,12,129;,
  3;131,12,130;,
  3;132,12,131;,
  3;133,12,132;,
  3;123,12,133;,
  3;134,13,135;,
  3;135,13,136;,
  3;136,13,137;,
  3;137,13,138;,
  3;138,13,139;,
  3;139,13,140;,
  3;140,13,141;,
  3;141,13,142;,
  3;142,13,143;,
  3;143,13,144;,
  3;144,13,145;,
  3;145,13,134;,
  4;48,64,64,48;,
  4;20,20,20,20;,
  4;65,47,47,65;,
  4;44,61,61,44;,
  4;23,17,17,23;,
  4;21,16,16,21;,
  4;14,14,18,18;,
  4;19,146,24,19;,
  4;20,20,20,20;,
  4;147,148,148,22;,
  4;25,147,22,26;,
  4;62,50,49,63;,
  4;27,23,23,27;,
  4;59,46,45,60;,
  4;146,29,28,24;,
  4;149,21,21,149;,
  4;74,25,26,75;,
  4;77,50,62,78;,
  4;81,150,150,81;,
  4;84,60,45,85;,
  4;29,88,87,28;,
  4;151,149,149,151;,
  4;152,153,80,31;,
  4;154,152,31,32;,
  4;33,33,154,32;,
  4;20,20,20,155;,
  4;156,19,19,34;,
  4;157,156,34,35;,
  4;158,157,35,82;,
  4;30,15,15,30;,
  4;36,36,37,37;,
  4;159,160,160,159;,
  4;38,38,39,155;,
  4;40,40,36,36;,
  4;161,39,41,41;,
  4;41,41,42,42;,
  4;162,163,163,162;,
  4;43,43,40,40;,
  4;51,44,44,51;,
  4;85,45,52,86;,
  4;46,53,52,45;,
  4;163,54,54,163;,
  4;47,55,55,47;,
  4;20,20,20,20;,
  4;56,48,48,56;,
  4;57,159,159,57;,
  4;50,58,164,49;,
  4;76,58,50,77;,
  4;165,51,51,165;,
  4;86,52,28,87;,
  4;53,24,28,52;,
  4;54,166,166,54;,
  4;55,167,167,55;,
  4;20,20,20,20;,
  4;168,56,56,168;,
  4;169,169,57,57;,
  4;58,26,22,164;,
  4;75,26,58,76;,
  4;66,59,60,67;,
  4;83,67,60,84;,
  4;61,68,68,61;,
  4;78,62,69,79;,
  4;69,62,63,70;,
  4;160,71,71,160;,
  4;64,72,72,64;,
  4;20,20,20,20;,
  4;73,65,65,73;,
  4;170,162,162,170;,
  4;34,66,67,35;,
  4;82,35,67,83;,
  4;171,30,30,171;,
  4;79,69,31,80;,
  4;31,69,70,32;,
  4;71,38,38,71;,
  4;72,172,172,72;,
  4;20,20,20,20;,
  4;173,73,73,173;,
  4;174,174,170,170;,
  4;175,74,75,176;,
  4;177,176,75,76;,
  4;178,177,76,77;,
  4;179,178,77,78;,
  4;180,179,78,79;,
  4;181,180,79,80;,
  4;153,182,181,80;,
  4;15,81,81,15;,
  4;183,184,158,82;,
  4;185,183,82,83;,
  4;186,185,83,84;,
  4;187,186,84,85;,
  4;188,187,85,86;,
  4;189,188,86,87;,
  4;88,190,189,87;,
  4;14,151,151,14;,
  4;89,89,89,89;,
  4;90,93,93,90;,
  4;19,19,19,19;,
  4;92,91,91,92;,
  4;191,192,192,191;,
  4;193,194,194,193;,
  4;195,90,90,195;,
  4;196,196,191,191;,
  4;91,197,197,91;,
  4;194,198,198,194;,
  4;199,92,92,199;,
  4;192,200,200,192;,
  4;93,201,201,93;,
  4;202,202,193,193;,
  4;99,95,95,99;,
  4;101,97,97,101;,
  4;100,98,98,100;,
  4;203,204,204,203;,
  4;204,97,97,204;,
  4;94,96,96,94;,
  4;102,105,105,102;,
  4;103,107,107,103;,
  4;104,106,106,104;,
  4;205,206,206,205;,
  4;94,94,102,102;,
  4;207,207,103,103;,
  4;96,96,104,104;,
  4;208,208,205,205;,
  4;206,99,99,206;,
  4;106,101,101,106;,
  4;107,100,100,107;,
  4;105,203,203,105;,
  4;113,109,109,113;,
  4;115,111,111,115;,
  4;114,112,112,114;,
  4;209,210,210,209;,
  4;210,111,111,210;,
  4;108,110,110,108;,
  4;116,119,119,116;,
  4;117,121,121,117;,
  4;118,120,120,118;,
  4;108,108,116,116;,
  4;211,211,117,117;,
  4;110,110,212,212;,
  4;213,213,118,118;,
  4;120,113,113,120;,
  4;121,114,114,121;,
  4;119,209,209,119;;
 }
 MeshTextureCoords {
  380;
  0.935540;0.016190;,
  0.935540;0.053700;,
  0.928540;0.051330;,
  0.928540;0.013820;,
  0.955570;0.014620;,
  0.956510;0.052850;,
  0.946950;0.053090;,
  0.946010;0.014850;,
  0.937390;0.053320;,
  0.936450;0.015090;,
  0.927510;0.051510;,
  0.927630;0.015350;,
  0.934620;0.017660;,
  0.934510;0.053810;,
  0.944180;0.018530;,
  0.944070;0.054680;,
  0.953750;0.017720;,
  0.953630;0.053870;,
  0.960750;0.015460;,
  0.960640;0.051610;,
  0.936950;0.015120;,
  0.936800;0.053360;,
  0.927240;0.053330;,
  0.927380;0.015080;,
  0.917670;0.053300;,
  0.917820;0.015050;,
  0.961660;0.013820;,
  0.961660;0.051330;,
  0.954660;0.053700;,
  0.954660;0.016190;,
  0.945100;0.054570;,
  0.945100;0.017060;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.919060;0.087470;,
  0.931670;0.079770;,
  0.924390;0.093110;,
  0.931670;0.095180;,
  0.938960;0.093110;,
  0.944290;0.087470;,
  0.946240;0.079770;,
  0.944290;0.072060;,
  0.938960;0.066420;,
  0.931670;0.064350;,
  0.924390;0.066420;,
  0.919060;0.072060;,
  0.917110;0.079770;,
  0.632770;0.175850;,
  0.645090;0.176060;,
  0.649560;0.187740;,
  0.636990;0.188180;,
  0.632260;0.122550;,
  0.644430;0.122690;,
  0.643880;0.171740;,
  0.631710;0.171600;,
  0.644060;0.119300;,
  0.631970;0.119360;,
  0.636250;0.107320;,
  0.648570;0.107900;,
  0.775340;0.169230;,
  0.776840;0.153860;,
  0.863750;0.153140;,
  0.863880;0.168500;,
  0.786170;0.046460;,
  0.786070;0.031990;,
  0.859110;0.031450;,
  0.859220;0.045920;,
  0.859740;0.264330;,
  0.859510;0.276100;,
  0.788190;0.274720;,
  0.788420;0.262960;,
  0.864690;0.233480;,
  0.786930;0.231970;,
  0.781100;0.209370;,
  0.865120;0.210990;,
  0.566110;0.111840;,
  0.559340;0.094240;,
  0.589080;0.079490;,
  0.582540;0.110910;,
  0.570660;0.176280;,
  0.570660;0.116320;,
  0.579730;0.116320;,
  0.579730;0.176280;,
  0.560710;0.198280;,
  0.567070;0.180530;,
  0.583520;0.181090;,
  0.592750;0.212410;,
  0.553830;0.206430;,
  0.602160;0.237830;,
  0.650360;0.239650;,
  0.626770;0.238760;,
  0.619050;0.211830;,
  0.644150;0.211360;,
  0.784600;0.070080;,
  0.861680;0.069500;,
  0.642460;0.079230;,
  0.617350;0.079350;,
  0.624450;0.052240;,
  0.648010;0.050810;,
  0.552280;0.086250;,
  0.597900;0.053860;,
  0.862070;0.258890;,
  0.786820;0.257430;,
  0.553500;0.225140;,
  0.576300;0.262570;,
  0.627080;0.260410;,
  0.649170;0.261860;,
  0.784610;0.090540;,
  0.785210;0.076240;,
  0.860980;0.075610;,
  0.862480;0.089900;,
  0.655400;0.028950;,
  0.624260;0.030590;,
  0.551510;0.067550;,
  0.578770;0.029300;,
  0.863690;0.246650;,
  0.786350;0.245160;,
  0.770010;0.244160;,
  0.747960;0.255300;,
  0.733310;0.257400;,
  0.756400;0.243650;,
  0.771450;0.209020;,
  0.733100;0.208480;,
  0.746300;0.186590;,
  0.760480;0.187070;,
  0.745780;0.112700;,
  0.754920;0.112700;,
  0.754920;0.182850;,
  0.745780;0.182850;,
  0.769770;0.078630;,
  0.759320;0.100830;,
  0.745150;0.101630;,
  0.737340;0.079720;,
  0.767530;0.043530;,
  0.753930;0.044360;,
  0.745220;0.032900;,
  0.731600;0.032370;,
  0.782490;0.114230;,
  0.784160;0.107120;,
  0.863670;0.106460;,
  0.863420;0.113560;,
  0.589030;0.192200;,
  0.591910;0.187900;,
  0.606610;0.183710;,
  0.606550;0.200180;,
  0.628890;0.191670;,
  0.646170;0.192000;,
  0.645880;0.206960;,
  0.628570;0.208190;,
  0.712280;0.200700;,
  0.712280;0.189220;,
  0.729540;0.194070;,
  0.734600;0.198920;,
  0.589400;0.095180;,
  0.592250;0.099530;,
  0.729540;0.094920;,
  0.734600;0.090070;,
  0.712280;0.099770;,
  0.712280;0.090070;,
  0.644980;0.097830;,
  0.630850;0.097460;,
  0.630980;0.091360;,
  0.645110;0.091730;,
  0.606950;0.095340;,
  0.606920;0.103990;,
  0.777400;0.199540;,
  0.864140;0.199420;,
  0.612300;0.052980;,
  0.590010;0.032410;,
  0.604410;0.079420;,
  0.623560;0.097270;,
  0.623690;0.091170;,
  0.625730;0.119400;,
  0.629890;0.107020;,
  0.625990;0.122480;,
  0.625430;0.171530;,
  0.626420;0.175750;,
  0.630510;0.188410;,
  0.619980;0.191500;,
  0.620320;0.206300;,
  0.615510;0.238330;,
  0.607020;0.212090;,
  0.586400;0.259170;,
  0.779580;0.204240;,
  0.864180;0.204840;,
  0.614920;0.097040;,
  0.615050;0.090950;,
  0.618350;0.119440;,
  0.622360;0.106670;,
  0.618550;0.122400;,
  0.618000;0.171450;,
  0.618890;0.175620;,
  0.622830;0.188680;,
  0.610540;0.204060;,
  0.609420;0.191290;,
  0.652080;0.079190;,
  0.657040;0.050260;,
  0.662670;0.025210;,
  0.777440;0.150390;,
  0.863720;0.149680;,
  0.659400;0.239990;,
  0.654590;0.265180;,
  0.653770;0.211190;,
  0.652790;0.192130;,
  0.652510;0.206490;,
  0.649820;0.176150;,
  0.654380;0.187570;,
  0.649090;0.122740;,
  0.648540;0.171790;,
  0.648690;0.119280;,
  0.653300;0.108120;,
  0.650400;0.097970;,
  0.650530;0.091870;,
  0.707360;0.193180;,
  0.707210;0.201090;,
  0.700480;0.177010;,
  0.694090;0.185550;,
  0.699130;0.123310;,
  0.698570;0.172360;,
  0.698400;0.119010;,
  0.695140;0.110550;,
  0.698520;0.093130;,
  0.698390;0.099230;,
  0.553240;0.245280;,
  0.574730;0.280340;,
  0.582140;0.272540;,
  0.628150;0.272200;,
  0.651420;0.273180;,
  0.656390;0.281290;,
  0.711570;0.269550;,
  0.722410;0.267400;,
  0.708510;0.019500;,
  0.719400;0.021400;,
  0.653080;0.009040;,
  0.648290;0.017270;,
  0.625050;0.018790;,
  0.578150;0.019560;,
  0.569490;0.011990;,
  0.550790;0.047430;,
  0.908930;0.216460;,
  0.907700;0.149270;,
  0.916790;0.149100;,
  0.918020;0.216300;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.909030;0.216850;,
  0.907800;0.149650;,
  0.916890;0.149490;,
  0.918120;0.216680;,
  0.931020;0.193650;,
  0.931020;0.169700;,
  0.940010;0.169700;,
  0.940010;0.193650;,
  0.918560;0.102230;,
  0.930710;0.102230;,
  0.930710;0.143700;,
  0.918560;0.143700;,
  0.919780;0.102140;,
  0.931920;0.102140;,
  0.931920;0.143610;,
  0.919780;0.143610;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.908300;0.145850;,
  0.908300;0.104380;,
  0.922860;0.149460;,
  0.931850;0.149460;,
  0.942190;0.104290;,
  0.942190;0.145760;,
  0.922860;0.215840;,
  0.931850;0.215840;,
  0.941960;0.104380;,
  0.941960;0.145850;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.908520;0.145760;,
  0.908520;0.104290;,
  0.989550;0.064270;,
  0.992080;0.068420;,
  0.990820;0.106000;,
  0.985880;0.109240;,
  0.992150;0.118160;,
  0.992090;0.122260;,
  0.983470;0.122240;,
  0.983530;0.118150;,
  0.958880;0.108830;,
  0.954080;0.105400;,
  0.954330;0.067800;,
  0.957020;0.063750;,
  0.983440;0.164340;,
  0.983430;0.160730;,
  0.992060;0.160750;,
  0.992060;0.164350;,
  0.982910;0.164010;,
  0.982980;0.123280;,
  0.992110;0.123290;,
  0.992050;0.164010;,
  0.992310;0.170900;,
  0.992620;0.183090;,
  0.983940;0.183110;,
  0.983640;0.170910;,
  0.985380;0.109420;,
  0.972280;0.114710;,
  0.973370;0.063940;,
  0.989180;0.064460;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.957390;0.063690;,
  0.973210;0.063800;,
  0.972260;0.114580;,
  0.959380;0.108760;,
  0.983450;0.165880;,
  0.992130;0.165870;,
  0.992180;0.068640;,
  0.990770;0.106210;,
  0.982930;0.118700;,
  0.992070;0.118700;,
  0.954130;0.105340;,
  0.954220;0.067740;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.992310;0.171030;,
  0.983640;0.171050;,
  0.989970;0.063910;,
  0.992560;0.068050;,
  0.991700;0.105720;,
  0.986760;0.109010;,
  0.991890;0.118400;,
  0.991820;0.122460;,
  0.983360;0.122420;,
  0.983430;0.118370;,
  0.958770;0.109070;,
  0.953890;0.105610;,
  0.954140;0.067650;,
  0.956870;0.063550;,
  0.983300;0.164060;,
  0.983300;0.160500;,
  0.991750;0.160530;,
  0.991750;0.164100;,
  0.982600;0.164140;,
  0.982720;0.123180;,
  0.992450;0.123190;,
  0.992330;0.164150;,
  0.991830;0.170900;,
  0.992180;0.183130;,
  0.984120;0.183140;,
  0.983770;0.170920;,
  0.985680;0.109650;,
  0.972380;0.115000;,
  0.973470;0.063730;,
  0.989540;0.064240;,
  0.957550;0.063650;,
  0.973500;0.063600;,
  0.973090;0.114500;,
  0.960040;0.108800;,
  0.983860;0.165870;,
  0.991920;0.165860;,
  0.992590;0.068460;,
  0.991150;0.106400;,
  0.982670;0.118560;,
  0.992400;0.118580;,
  0.954710;0.105420;,
  0.954400;0.067740;,
  0.992010;0.170980;,
  0.983950;0.171000;;
 }
}