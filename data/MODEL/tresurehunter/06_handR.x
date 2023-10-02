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
 273;
 -5.31576;-2.29383;1.78612;,
 -5.38266;0.00000;2.56197;,
 -5.71865;0.00000;2.69393;,
 -5.65175;-2.41508;1.86789;,
 -5.31576;2.29383;1.78612;,
 -5.65174;2.41508;1.86789;,
 -5.31576;2.29383;1.78612;,
 -5.16549;3.15842;-0.05886;,
 -5.50148;3.40249;-0.05886;,
 -5.65174;2.41508;1.86789;,
 -5.08470;2.11568;-1.79306;,
 -5.42068;2.32865;-1.92675;,
 -5.08470;2.11568;-1.79306;,
 -5.08726;0.00000;-2.49718;,
 -5.42324;0.00000;-2.69393;,
 -5.42068;2.32865;-1.92675;,
 -5.08470;-2.11568;-1.79306;,
 -5.42068;-2.32865;-1.92675;,
 -5.08470;-2.11568;-1.79306;,
 -5.16549;-3.15842;-0.05886;,
 -5.50148;-3.40249;-0.05886;,
 -5.42068;-2.32865;-1.92675;,
 -5.31576;-2.29383;1.78612;,
 -5.65175;-2.41508;1.86789;,
 -7.37339;-1.70893;1.22897;,
 -7.37339;0.00000;1.76326;,
 -8.63371;0.00000;2.32249;,
 -8.63371;-2.23283;1.62440;,
 -7.37339;1.70893;1.22897;,
 -8.63371;2.23283;1.62440;,
 -7.37339;1.70893;1.22897;,
 -7.37339;2.41680;-0.06093;,
 -8.63371;3.15770;-0.06093;,
 -8.63371;2.23283;1.62440;,
 -7.37339;1.70893;-1.35082;,
 -8.63371;2.23283;-1.74626;,
 -7.37339;1.70893;-1.35082;,
 -7.37339;0.00000;-1.88512;,
 -8.63371;0.00000;-2.44434;,
 -8.63371;2.23283;-1.74626;,
 -7.37339;-1.70893;-1.35082;,
 -8.63371;-2.23283;-1.74626;,
 -7.37339;-1.70893;-1.35082;,
 -7.37339;-2.41680;-0.06093;,
 -8.63371;-3.15770;-0.06093;,
 -8.63371;-2.23283;-1.74626;,
 -7.37339;-1.70893;1.22897;,
 -8.63371;-2.23283;1.62440;,
 -10.12036;0.00000;2.51886;,
 -10.12036;-2.41680;1.76326;,
 -10.12036;2.41680;1.76326;,
 -10.12036;3.41786;-0.06093;,
 -10.12036;2.41680;1.76326;,
 -10.12036;2.41680;-1.88512;,
 -10.12036;0.00000;-2.64072;,
 -10.12036;2.41680;-1.88512;,
 -10.12036;-2.41680;-1.88512;,
 -10.12036;-3.41786;-0.06093;,
 -10.12036;-2.41680;-1.88512;,
 -10.12036;-2.41680;1.76326;,
 -11.60701;0.00000;2.32249;,
 -11.60701;-2.23283;1.62440;,
 -11.60701;2.23283;1.62440;,
 -11.60701;3.15770;-0.06093;,
 -11.60701;2.23283;1.62440;,
 -11.60701;2.23283;-1.74626;,
 -11.60701;0.00000;-2.44434;,
 -11.60701;2.23283;-1.74626;,
 -11.60701;-2.23283;-1.74626;,
 -11.60701;-3.15770;-0.06093;,
 -11.60701;-2.23283;-1.74626;,
 -11.60701;-2.23283;1.62440;,
 -13.53912;0.00000;1.76326;,
 -13.52048;-1.60968;1.22897;,
 -13.52048;1.60968;1.22897;,
 -13.49107;2.45816;-0.06093;,
 -13.52048;1.60968;1.22897;,
 -13.40292;1.75395;-1.35082;,
 -13.45588;0.00000;-1.88512;,
 -13.40292;1.75395;-1.35082;,
 -13.40292;-1.75395;-1.35082;,
 -13.49107;-2.45816;-0.06093;,
 -13.40292;-1.75395;-1.35082;,
 -13.52048;-1.60968;1.22897;,
 -13.52048;-1.60968;1.22897;,
 -13.53912;0.00000;1.76326;,
 -13.92878;0.00000;0.92631;,
 -13.92878;-0.92487;0.63716;,
 -13.52048;1.60968;1.22897;,
 -13.92878;0.92487;0.63716;,
 -13.49107;2.45816;-0.06093;,
 -13.92878;1.30796;-0.06093;,
 -13.40292;1.75395;-1.35082;,
 -13.92878;0.92487;-0.75901;,
 -13.45588;0.00000;-1.88512;,
 -13.92878;0.00000;-1.04817;,
 -13.40292;-1.75395;-1.35082;,
 -13.92878;-0.92487;-0.75901;,
 -13.49107;-2.45816;-0.06093;,
 -13.92878;-1.30796;-0.06093;,
 -7.03741;0.00000;1.63129;,
 -7.03741;-1.58767;1.14720;,
 -6.69661;0.00000;-0.06093;,
 -7.03741;1.58767;1.14720;,
 -7.03741;2.17273;-0.06093;,
 -7.03741;1.49596;-1.21714;,
 -7.03741;0.00000;-1.68836;,
 -7.03741;-1.49596;-1.21714;,
 -7.03741;-2.17273;-0.06093;,
 -14.08962;0.00000;-0.06093;,
 -7.03741;-1.58767;1.14720;,
 -7.03741;0.00000;1.63129;,
 -5.38266;0.00000;2.56197;,
 -5.31576;-2.29383;1.78612;,
 -7.03741;1.58767;1.14720;,
 -5.31576;2.29383;1.78612;,
 -7.03741;1.58767;1.14720;,
 -7.03741;2.17273;-0.06093;,
 -5.16549;3.15842;-0.05886;,
 -5.31576;2.29383;1.78612;,
 -7.03741;1.49596;-1.21714;,
 -5.08470;2.11568;-1.79306;,
 -7.03741;1.49596;-1.21714;,
 -7.03741;0.00000;-1.68836;,
 -5.08726;0.00000;-2.49718;,
 -5.08470;2.11568;-1.79306;,
 -7.03741;-1.49596;-1.21714;,
 -5.08470;-2.11568;-1.79306;,
 -7.03741;-1.49596;-1.21714;,
 -7.03741;-2.17273;-0.06093;,
 -5.16549;-3.15842;-0.05886;,
 -5.08470;-2.11568;-1.79306;,
 -7.03741;-1.58767;1.14720;,
 -5.31576;-2.29383;1.78612;,
 -6.83501;1.26110;0.56265;,
 -6.83501;1.06945;1.11640;,
 0.02439;1.06945;1.11640;,
 0.02439;1.26110;0.56265;,
 -6.83501;0.77093;1.49779;,
 0.02439;0.77093;1.49779;,
 -6.83501;0.77093;1.49779;,
 -6.83501;0.39479;1.67963;,
 0.02439;0.39479;1.67963;,
 0.02439;0.77093;1.49779;,
 -6.83501;-0.02217;1.71862;,
 0.02439;-0.02217;1.71862;,
 -6.83501;-0.43913;1.67963;,
 0.02439;-0.43913;1.67963;,
 -6.83501;-0.81528;1.49779;,
 0.02439;-0.81528;1.49779;,
 -6.83501;-0.81528;1.49779;,
 -6.83501;-1.11379;1.11640;,
 0.02439;-1.11379;1.11640;,
 0.02439;-0.81528;1.49779;,
 -6.83501;-1.30545;0.56265;,
 0.02439;-1.30545;0.56265;,
 -6.83501;-1.37148;-0.05118;,
 0.02439;-1.37148;-0.05118;,
 -6.83501;-1.30545;-0.66502;,
 0.02439;-1.30545;-0.66502;,
 -6.83501;-1.11379;-1.21877;,
 0.02439;-1.11379;-1.21877;,
 -6.83501;-0.81528;-1.60015;,
 0.02439;-0.81528;-1.60015;,
 -6.83501;-0.81528;-1.60015;,
 -6.83501;-0.43913;-1.78199;,
 0.02439;-0.43913;-1.78199;,
 0.02439;-0.81528;-1.60015;,
 -6.83501;-0.02217;-1.82098;,
 0.02439;-0.02217;-1.82098;,
 -6.83501;0.39479;-1.78199;,
 0.02439;0.39479;-1.78199;,
 -6.83501;0.77093;-1.60015;,
 0.02439;0.77093;-1.60015;,
 -6.83501;0.77093;-1.60015;,
 -6.83501;1.06944;-1.21877;,
 0.02439;1.06944;-1.21877;,
 0.02439;0.77093;-1.60015;,
 -6.83501;1.26110;-0.66502;,
 0.02439;1.26110;-0.66502;,
 -6.83501;1.32714;-0.05118;,
 0.02439;1.32714;-0.05118;,
 -6.83501;1.06945;1.11640;,
 -6.83501;1.26110;0.56265;,
 -6.83501;-0.02217;-0.05118;,
 -6.83501;0.77093;1.49779;,
 -6.83501;0.39479;1.67963;,
 -6.83501;-0.02217;1.71862;,
 -6.83501;-0.43913;1.67963;,
 -6.83501;-0.81528;1.49779;,
 -6.83501;-1.11379;1.11640;,
 -6.83501;-1.30545;0.56265;,
 -6.83501;-1.37148;-0.05118;,
 -6.83501;-1.30545;-0.66502;,
 -6.83501;-1.11379;-1.21877;,
 -6.83501;-0.81528;-1.60015;,
 -6.83501;-0.43913;-1.78199;,
 -6.83501;-0.02217;-1.82098;,
 -6.83501;0.39479;-1.78199;,
 -6.83501;0.77093;-1.60015;,
 -6.83501;1.06944;-1.21877;,
 -6.83501;1.26110;-0.66502;,
 -6.83501;1.32714;-0.05118;,
 0.02439;1.26110;0.56265;,
 0.02439;1.06945;1.11640;,
 0.02439;-0.02217;-0.05118;,
 0.02439;0.77093;1.49779;,
 0.02439;0.39479;1.67963;,
 0.02439;-0.02217;1.71862;,
 0.02439;-0.43913;1.67963;,
 0.02439;-0.81528;1.49779;,
 0.02439;-1.11379;1.11640;,
 0.02439;-1.30545;0.56265;,
 0.02439;-1.37148;-0.05118;,
 0.02439;-1.30545;-0.66502;,
 0.02439;-1.11379;-1.21877;,
 0.02439;-0.81528;-1.60015;,
 0.02439;-0.43913;-1.78199;,
 0.02439;-0.02217;-1.82098;,
 0.02439;0.39479;-1.78199;,
 0.02439;0.77093;-1.60015;,
 0.02439;1.06944;-1.21877;,
 0.02439;1.26110;-0.66502;,
 0.02439;1.32714;-0.05118;,
 -0.01777;0.90972;1.19644;,
 -0.01777;-0.02917;1.71496;,
 0.51328;-0.02917;1.58020;,
 0.51328;0.83826;1.10115;,
 -0.01777;-0.96806;1.19644;,
 0.51328;-0.89659;1.10115;,
 -0.01777;-0.96806;1.19644;,
 -0.01777;-1.35696;-0.05536;,
 0.51328;-1.25589;-0.05536;,
 0.51328;-0.89659;1.10115;,
 -0.01777;-0.96806;-1.30717;,
 0.51328;-0.89659;-1.21188;,
 -0.01777;-0.96806;-1.30717;,
 -0.01777;-0.02917;-1.82568;,
 0.51328;-0.02917;-1.69092;,
 0.51328;-0.89659;-1.21188;,
 -0.01777;0.90972;-1.30717;,
 0.51328;0.83826;-1.21188;,
 -0.01777;0.90972;-1.30717;,
 -0.01777;1.29862;-0.05536;,
 0.51328;1.19755;-0.05536;,
 0.51328;0.83826;-1.21188;,
 -0.01777;0.90972;1.19644;,
 0.51328;0.83826;1.10115;,
 0.51328;0.83826;1.10115;,
 0.51328;-0.02917;1.58020;,
 0.96347;-0.02917;1.19644;,
 0.96347;0.63473;0.82980;,
 0.51328;-0.89659;1.10115;,
 0.96347;-0.69306;0.82980;,
 0.51328;-1.25589;-0.05536;,
 0.96347;-0.96806;-0.05536;,
 0.51328;-0.89659;-1.21188;,
 0.96347;-0.69306;-0.94052;,
 0.51328;-0.02917;-1.69092;,
 0.96347;-0.02917;-1.30717;,
 0.51328;0.83826;-1.21188;,
 0.96347;0.63473;-0.94052;,
 0.51328;1.19755;-0.05536;,
 0.96347;0.90972;-0.05536;,
 1.26429;-0.02917;0.62211;,
 1.26429;0.33013;0.42368;,
 1.26429;-0.38846;0.42368;,
 1.26429;-0.53729;-0.05536;,
 1.26429;-0.38846;-0.53441;,
 1.26429;-0.02917;-0.73283;,
 1.26429;0.33013;-0.53441;,
 1.26429;0.47895;-0.05536;,
 1.36992;-0.02917;-0.05536;;
 
 172;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;27,26,48,49;,
 4;26,29,50,48;,
 4;33,32,51,52;,
 4;32,35,53,51;,
 4;39,38,54,55;,
 4;38,41,56,54;,
 4;45,44,57,58;,
 4;44,47,59,57;,
 4;49,48,60,61;,
 4;48,50,62,60;,
 4;52,51,63,64;,
 4;51,53,65,63;,
 4;55,54,66,67;,
 4;54,56,68,66;,
 4;58,57,69,70;,
 4;57,59,71,69;,
 4;61,60,72,73;,
 4;60,62,74,72;,
 4;64,63,75,76;,
 4;63,65,77,75;,
 4;67,66,78,79;,
 4;66,68,80,78;,
 4;70,69,81,82;,
 4;69,71,83,81;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,84,87,99;,
 3;100,101,102;,
 3;103,100,102;,
 3;104,103,102;,
 3;105,104,102;,
 3;106,105,102;,
 3;107,106,102;,
 3;108,107,102;,
 3;101,108,102;,
 3;87,86,109;,
 3;86,89,109;,
 3;89,91,109;,
 3;91,93,109;,
 3;93,95,109;,
 3;95,97,109;,
 3;97,99,109;,
 3;99,87,109;,
 4;110,111,112,113;,
 4;25,24,3,2;,
 4;111,114,115,112;,
 4;28,25,2,5;,
 4;116,117,118,119;,
 4;31,30,9,8;,
 4;117,120,121,118;,
 4;34,31,8,11;,
 4;122,123,124,125;,
 4;37,36,15,14;,
 4;123,126,127,124;,
 4;40,37,14,17;,
 4;128,129,130,131;,
 4;43,42,21,20;,
 4;129,132,133,130;,
 4;46,43,20,23;,
 4;134,135,136,137;,
 4;135,138,139,136;,
 4;140,141,142,143;,
 4;141,144,145,142;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;150,151,152,153;,
 4;151,154,155,152;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;164,165,166,167;,
 4;165,168,169,166;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 4;174,175,176,177;,
 4;175,178,179,176;,
 4;178,180,181,179;,
 4;180,134,137,181;,
 3;182,183,184;,
 3;185,182,184;,
 3;186,185,184;,
 3;187,186,184;,
 3;188,187,184;,
 3;189,188,184;,
 3;190,189,184;,
 3;191,190,184;,
 3;192,191,184;,
 3;193,192,184;,
 3;194,193,184;,
 3;195,194,184;,
 3;196,195,184;,
 3;197,196,184;,
 3;198,197,184;,
 3;199,198,184;,
 3;200,199,184;,
 3;201,200,184;,
 3;202,201,184;,
 3;183,202,184;,
 3;203,204,205;,
 3;204,206,205;,
 3;206,207,205;,
 3;207,208,205;,
 3;208,209,205;,
 3;209,210,205;,
 3;210,211,205;,
 3;211,212,205;,
 3;212,213,205;,
 3;213,214,205;,
 3;214,215,205;,
 3;215,216,205;,
 3;216,217,205;,
 3;217,218,205;,
 3;218,219,205;,
 3;219,220,205;,
 3;220,221,205;,
 3;221,222,205;,
 3;222,223,205;,
 3;223,203,205;,
 4;224,225,226,227;,
 4;225,228,229,226;,
 4;230,231,232,233;,
 4;231,234,235,232;,
 4;236,237,238,239;,
 4;237,240,241,238;,
 4;242,243,244,245;,
 4;243,246,247,244;,
 4;248,249,250,251;,
 4;249,252,253,250;,
 4;252,254,255,253;,
 4;254,256,257,255;,
 4;256,258,259,257;,
 4;258,260,261,259;,
 4;260,262,263,261;,
 4;262,248,251,263;,
 4;251,250,264,265;,
 4;250,253,266,264;,
 4;253,255,267,266;,
 4;255,257,268,267;,
 4;257,259,269,268;,
 4;259,261,270,269;,
 4;261,263,271,270;,
 4;263,251,265,271;,
 3;265,264,272;,
 3;264,266,272;,
 3;266,267,272;,
 3;267,268,272;,
 3;268,269,272;,
 3;269,270,272;,
 3;270,271,272;,
 3;271,265,272;;
 
 MeshMaterialList {
  1;
  172;
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
    "data\\TEXTURE\\treasurehunter.png";
   }
  }
 }
 MeshNormals {
  138;
  0.984796;-0.107628;0.136359;,
  0.980317;0.000000;0.197428;,
  0.984796;0.107628;0.136359;,
  0.987891;0.154954;-0.007777;,
  0.982914;0.109667;-0.147827;,
  0.978769;0.000000;-0.204964;,
  0.982914;-0.109667;-0.147827;,
  0.987891;-0.154954;-0.007777;,
  -0.018028;-0.640421;0.767813;,
  -0.038092;0.000000;0.999274;,
  -0.018027;0.640421;0.767813;,
  0.506786;0.862072;-0.000001;,
  0.025601;0.627140;-0.778486;,
  0.016138;0.000000;-0.999870;,
  0.025601;-0.627140;-0.778486;,
  0.506786;-0.862072;-0.000001;,
  0.304714;-0.600495;0.739294;,
  0.271500;0.000000;0.962438;,
  0.304714;0.600495;0.739294;,
  0.347413;0.937712;-0.000000;,
  0.304715;0.600494;-0.739294;,
  0.271501;0.000000;-0.962438;,
  0.304715;-0.600494;-0.739294;,
  0.347413;-0.937712;-0.000000;,
  -0.000000;-0.632830;0.774291;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.632830;0.774291;,
  0.000000;1.000000;0.000000;,
  0.000000;0.632829;-0.774292;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.632829;-0.774292;,
  0.000000;-1.000000;-0.000000;,
  -0.237606;-0.608775;0.756926;,
  -0.209353;0.000000;0.977840;,
  -0.237606;0.608775;0.756926;,
  -0.272491;0.962144;0.005339;,
  -0.234340;0.612976;-0.754550;,
  -0.211287;0.000000;-0.977424;,
  -0.234340;-0.612976;-0.754550;,
  -0.272491;-0.962144;0.005339;,
  -0.682049;-0.453875;0.573417;,
  -0.656366;0.000000;0.754443;,
  -0.682049;0.453875;0.573417;,
  -0.720156;0.693803;-0.003676;,
  -0.658066;0.464491;-0.592619;,
  -0.625567;0.000000;-0.780170;,
  -0.658066;-0.464491;-0.592619;,
  -0.720156;-0.693803;-0.003676;,
  -0.960843;-0.170829;0.218168;,
  -0.954538;0.000000;0.298088;,
  -0.960843;0.170829;0.218168;,
  -0.968365;0.249410;-0.007988;,
  -0.952364;0.181937;-0.244749;,
  -0.942086;0.000000;-0.335370;,
  -0.952364;-0.181937;-0.244749;,
  -0.968365;-0.249410;-0.007988;,
  0.999983;-0.000000;-0.005852;,
  -1.000000;0.000000;-0.000000;,
  0.428683;-0.572070;0.699262;,
  0.353506;-0.000001;0.935432;,
  -0.067632;-0.000000;0.997710;,
  -0.030943;-0.642811;0.765400;,
  0.428688;0.572068;0.699260;,
  -0.030939;0.642811;0.765400;,
  0.568266;0.822765;0.011430;,
  0.558499;0.522653;-0.644137;,
  0.272739;0.498230;-0.823031;,
  0.511917;0.000000;-0.859035;,
  0.076204;0.000000;-0.997092;,
  0.558499;-0.522653;-0.644137;,
  0.090615;-0.625787;-0.774713;,
  0.568264;-0.822767;0.011432;,
  0.000000;0.975857;0.218408;,
  0.000000;0.878228;0.478242;,
  0.000000;0.627623;0.778517;,
  0.000000;0.268441;0.963296;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.268436;0.963297;,
  0.000000;-0.627626;0.778515;,
  0.000000;-0.878228;0.478242;,
  0.000000;-0.975857;0.218408;,
  0.000000;-1.000000;0.000001;,
  0.000000;-0.975858;-0.218407;,
  0.000000;-0.878225;-0.478248;,
  0.000000;-0.627621;-0.778519;,
  0.000000;-0.268436;-0.963297;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.268441;-0.963296;,
  0.000000;0.627625;-0.778516;,
  0.000000;0.878225;-0.478248;,
  0.000000;0.975856;-0.218415;,
  0.000000;1.000000;0.000001;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.212609;0.758479;0.616042;,
  0.245963;-0.000001;0.969279;,
  0.212616;-0.758477;0.616042;,
  0.186969;-0.982366;0.000001;,
  0.212617;-0.758475;-0.616044;,
  0.245963;-0.000001;-0.969279;,
  0.212610;0.758477;-0.616044;,
  0.186959;0.982368;0.000001;,
  0.411626;0.710318;0.570975;,
  0.463910;-0.000002;0.885882;,
  0.411629;-0.710316;0.570975;,
  0.370516;-0.928826;0.000001;,
  0.411630;-0.710315;-0.570976;,
  0.463910;-0.000001;-0.885882;,
  0.411627;0.710317;-0.570976;,
  0.370510;0.928828;0.000001;,
  0.736190;0.532596;0.417571;,
  0.784508;-0.000002;0.620119;,
  0.736190;-0.532595;0.417573;,
  0.693812;-0.720156;0.000001;,
  0.736190;-0.532595;-0.417573;,
  0.784507;-0.000002;-0.620119;,
  0.736190;0.532596;-0.417571;,
  0.693810;0.720158;0.000001;,
  0.934236;0.283293;0.216675;,
  0.950409;-0.000001;0.311002;,
  0.934236;-0.283293;0.216677;,
  0.918751;-0.394838;0.000001;,
  0.934236;-0.283292;-0.216677;,
  0.950409;-0.000001;-0.311002;,
  0.934236;0.283292;-0.216675;,
  0.918750;0.394839;0.000001;,
  1.000000;-0.000001;0.000000;,
  0.486495;0.583628;-0.650154;,
  0.474567;0.000000;-0.880220;,
  0.486495;-0.583628;-0.650154;,
  0.469680;-0.880893;0.058552;,
  -0.472020;0.881133;-0.028330;,
  0.401571;-0.566513;0.719586;,
  -0.399478;0.795480;-0.455664;,
  0.377552;0.000000;0.925988;,
  0.401571;0.566513;0.719586;,
  0.469680;0.880893;0.058552;,
  -0.472021;-0.881132;-0.028331;;
  172;
  4;58,59,60,61;,
  4;59,62,63,60;,
  4;62,64,64,63;,
  4;64,65,66,64;,
  4;65,67,68,66;,
  4;67,69,70,68;,
  4;69,71,71,70;,
  4;71,58,61,71;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  4;40,41,49,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,40,48,55;,
  3;1,0,56;,
  3;2,1,56;,
  3;3,2,56;,
  3;4,3,56;,
  3;5,4,56;,
  3;6,5,56;,
  3;7,6,56;,
  3;0,7,56;,
  3;48,49,57;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,48,57;,
  4;127,128,128,127;,
  4;9,8,61,60;,
  4;128,129,129,128;,
  4;10,9,60,63;,
  4;129,130,130,129;,
  4;131,10,63,131;,
  4;130,132,132,130;,
  4;12,131,131,133;,
  4;132,134,134,132;,
  4;13,12,66,68;,
  4;134,135,135,134;,
  4;14,13,68,70;,
  4;135,136,136,135;,
  4;137,14,70,137;,
  4;136,127,127,136;,
  4;8,137,137,61;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;90,91,91,90;,
  4;91,72,72,91;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;92,92,92;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,94,102,109;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;105,106,114,113;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,102,110,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,110,118,125;,
  3;118,119,126;,
  3;119,120,126;,
  3;120,121,126;,
  3;121,122,126;,
  3;122,123,126;,
  3;123,124,126;,
  3;124,125,126;,
  3;125,118,126;;
 }
 MeshTextureCoords {
  273;
  0.850920;0.732270;,
  0.823530;0.732900;,
  0.823500;0.736700;,
  0.852340;0.736080;,
  0.796150;0.732010;,
  0.794670;0.735800;,
  0.687790;0.730290;,
  0.665780;0.728480;,
  0.665750;0.732280;,
  0.688730;0.734090;,
  0.645080;0.727470;,
  0.643450;0.731270;,
  0.790380;0.729880;,
  0.765120;0.729790;,
  0.765090;0.733590;,
  0.792890;0.733690;,
  0.739870;0.729640;,
  0.737290;0.733430;,
  0.734000;0.729220;,
  0.713290;0.730040;,
  0.713250;0.733840;,
  0.735560;0.733030;,
  0.691240;0.731630;,
  0.690240;0.735430;,
  0.843740;0.755500;,
  0.823340;0.755400;,
  0.823220;0.769650;,
  0.849880;0.769780;,
  0.802940;0.755310;,
  0.796560;0.769520;,
  0.680940;0.753520;,
  0.665540;0.753450;,
  0.665420;0.767690;,
  0.685540;0.767790;,
  0.650140;0.753370;,
  0.645300;0.767600;,
  0.785310;0.755730;,
  0.764900;0.755630;,
  0.764790;0.769880;,
  0.791440;0.770010;,
  0.744500;0.755540;,
  0.738130;0.769760;,
  0.728500;0.755070;,
  0.713100;0.755000;,
  0.712980;0.769250;,
  0.733100;0.769340;,
  0.697700;0.754930;,
  0.692860;0.769150;,
  0.823080;0.786460;,
  0.851930;0.786590;,
  0.794230;0.786320;,
  0.665280;0.784500;,
  0.687060;0.784600;,
  0.643500;0.784400;,
  0.764640;0.786690;,
  0.793500;0.786830;,
  0.735790;0.786550;,
  0.712840;0.786050;,
  0.734620;0.786160;,
  0.691060;0.785950;,
  0.822940;0.803260;,
  0.849600;0.803390;,
  0.796280;0.803140;,
  0.665140;0.801310;,
  0.685260;0.801400;,
  0.645020;0.801210;,
  0.764500;0.803490;,
  0.791160;0.803620;,
  0.737850;0.803370;,
  0.712700;0.802860;,
  0.732820;0.802960;,
  0.692580;0.802770;,
  0.822760;0.825110;,
  0.841970;0.824990;,
  0.803540;0.824810;,
  0.664960;0.822610;,
  0.680360;0.823010;,
  0.649570;0.821540;,
  0.764330;0.824400;,
  0.785270;0.823900;,
  0.743390;0.823700;,
  0.712520;0.824160;,
  0.727930;0.823240;,
  0.697120;0.824420;,
  0.865650;0.785880;,
  0.859490;0.803010;,
  0.868920;0.803060;,
  0.872260;0.793210;,
  0.865370;0.820210;,
  0.872090;0.812930;,
  0.879810;0.829320;,
  0.879920;0.817060;,
  0.894400;0.821880;,
  0.887810;0.813010;,
  0.900580;0.803210;,
  0.891150;0.803160;,
  0.894720;0.784480;,
  0.887980;0.793290;,
  0.880250;0.776900;,
  0.880150;0.789160;,
  0.940490;0.793110;,
  0.943890;0.804270;,
  0.952380;0.793110;,
  0.943890;0.781950;,
  0.952380;0.777840;,
  0.960510;0.782600;,
  0.963820;0.793110;,
  0.960510;0.803630;,
  0.952380;0.808380;,
  0.880030;0.803110;,
  0.944870;0.778200;,
  0.944870;0.792940;,
  0.960240;0.792940;,
  0.960860;0.771640;,
  0.944870;0.807690;,
  0.960860;0.814250;,
  0.943260;0.781770;,
  0.943260;0.793000;,
  0.960650;0.792980;,
  0.959250;0.775840;,
  0.943260;0.803740;,
  0.961400;0.809090;,
  0.942090;0.777450;,
  0.942090;0.791340;,
  0.960200;0.791340;,
  0.960220;0.771690;,
  0.942090;0.805240;,
  0.960220;0.810990;,
  0.943490;0.780530;,
  0.943490;0.791270;,
  0.960880;0.791290;,
  0.961630;0.775180;,
  0.943490;0.802490;,
  0.959480;0.808430;,
  0.952850;0.934530;,
  0.949930;0.934530;,
  0.949930;0.970640;,
  0.952850;0.970640;,
  0.947920;0.934530;,
  0.947920;0.970640;,
  0.955910;0.934530;,
  0.953930;0.934530;,
  0.953930;0.970640;,
  0.955910;0.970640;,
  0.951730;0.934530;,
  0.951730;0.970640;,
  0.949540;0.934530;,
  0.949540;0.970640;,
  0.947560;0.934530;,
  0.947560;0.970640;,
  0.964190;0.934680;,
  0.962180;0.934680;,
  0.962180;0.970790;,
  0.964190;0.970790;,
  0.959260;0.934680;,
  0.959260;0.970790;,
  0.956030;0.934680;,
  0.956030;0.970790;,
  0.952800;0.934680;,
  0.952800;0.970790;,
  0.949890;0.934680;,
  0.949890;0.970790;,
  0.947880;0.934680;,
  0.947880;0.970790;,
  0.961270;0.934520;,
  0.959290;0.934520;,
  0.959290;0.970630;,
  0.961270;0.970630;,
  0.957090;0.934520;,
  0.957090;0.970630;,
  0.954900;0.934520;,
  0.954900;0.970630;,
  0.952920;0.934520;,
  0.952920;0.970630;,
  0.964230;0.934530;,
  0.962220;0.934530;,
  0.962220;0.970640;,
  0.964230;0.970640;,
  0.959310;0.934530;,
  0.959310;0.970640;,
  0.956080;0.934530;,
  0.956080;0.970640;,
  0.961910;0.953320;,
  0.962920;0.950400;,
  0.956160;0.947170;,
  0.960340;0.955320;,
  0.958360;0.956280;,
  0.956160;0.956480;,
  0.953970;0.956280;,
  0.951990;0.955320;,
  0.950420;0.953320;,
  0.949410;0.950400;,
  0.949060;0.947170;,
  0.949410;0.943940;,
  0.950420;0.941020;,
  0.951990;0.939020;,
  0.953970;0.938060;,
  0.956160;0.937850;,
  0.958360;0.938060;,
  0.960340;0.939020;,
  0.961910;0.941020;,
  0.962920;0.943940;,
  0.963270;0.947170;,
  0.962550;0.944860;,
  0.961540;0.941940;,
  0.955790;0.948090;,
  0.959970;0.939930;,
  0.957990;0.938980;,
  0.955790;0.938770;,
  0.953600;0.938980;,
  0.951620;0.939930;,
  0.950050;0.941940;,
  0.949040;0.944860;,
  0.948690;0.948090;,
  0.949040;0.951320;,
  0.950050;0.954230;,
  0.951620;0.956240;,
  0.953600;0.957200;,
  0.955790;0.957400;,
  0.957990;0.957200;,
  0.959970;0.956240;,
  0.961540;0.954230;,
  0.962550;0.951320;,
  0.962900;0.948090;,
  0.956460;0.941500;,
  0.956460;0.946450;,
  0.959260;0.946450;,
  0.959260;0.941880;,
  0.956460;0.951390;,
  0.959260;0.951010;,
  0.949320;0.937430;,
  0.949320;0.944020;,
  0.952110;0.944020;,
  0.952110;0.937930;,
  0.949320;0.950610;,
  0.952110;0.950110;,
  0.960030;0.941500;,
  0.960030;0.946450;,
  0.962830;0.946450;,
  0.962830;0.941880;,
  0.960030;0.951390;,
  0.962830;0.951010;,
  0.952890;0.937430;,
  0.952890;0.944020;,
  0.955690;0.944020;,
  0.955690;0.937930;,
  0.952890;0.950610;,
  0.955690;0.950110;,
  0.962590;0.940850;,
  0.958020;0.938330;,
  0.958020;0.940350;,
  0.961520;0.942280;,
  0.953460;0.940850;,
  0.954530;0.942280;,
  0.951570;0.946940;,
  0.953080;0.946940;,
  0.953460;0.953030;,
  0.954530;0.951600;,
  0.958020;0.955550;,
  0.958020;0.953530;,
  0.962590;0.953030;,
  0.961520;0.951600;,
  0.964480;0.946940;,
  0.962970;0.946940;,
  0.958020;0.943370;,
  0.959910;0.944420;,
  0.956130;0.944420;,
  0.955350;0.946940;,
  0.956130;0.949460;,
  0.958020;0.950510;,
  0.959910;0.949460;,
  0.960700;0.946940;,
  0.958020;0.946940;;
 }
}
