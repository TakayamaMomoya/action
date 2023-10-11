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
 102;
 -31.17894;49.36381;-2.08169;,
 31.17894;49.36381;-2.08169;,
 31.17894;-4.32817;-2.08169;,
 -31.17894;-4.32817;-2.08169;,
 31.17894;49.36381;-2.08169;,
 31.17894;49.36381;1.91217;,
 31.17894;-4.32817;1.91217;,
 31.17894;-4.32817;-2.08169;,
 31.17894;49.36381;1.91217;,
 -31.17894;49.36381;1.91217;,
 -31.17894;-4.32817;1.91217;,
 31.17894;-4.32817;1.91217;,
 -31.17894;49.36381;1.91217;,
 -31.17894;49.36381;-2.08169;,
 -31.17894;-4.32817;-2.08169;,
 -31.17894;-4.32817;1.91217;,
 -31.17894;49.36381;1.91217;,
 31.17894;49.36381;1.91217;,
 31.17894;49.36381;-2.08169;,
 -31.17894;49.36381;-2.08169;,
 -31.17894;-4.32817;-2.08169;,
 31.17894;-4.32817;-2.08169;,
 30.59312;61.92852;-3.28828;,
 37.16962;61.92852;-3.28828;,
 37.16962;-12.74840;-3.28828;,
 30.59312;-12.74840;-3.28828;,
 37.16962;61.92852;-3.28828;,
 37.16962;61.92852;3.28828;,
 37.16962;-12.74840;3.28828;,
 37.16962;-12.74840;-3.28828;,
 37.16962;61.92852;3.28828;,
 30.59312;61.92852;3.28828;,
 30.59312;-12.74840;3.28828;,
 37.16962;-12.74840;3.28828;,
 30.59312;61.92852;3.28828;,
 30.59312;61.92852;-3.28828;,
 30.59312;-12.74840;-3.28828;,
 30.59312;-12.74840;3.28828;,
 37.16962;61.92852;-3.28828;,
 30.59312;61.92852;-3.28828;,
 30.59312;-12.74840;-3.28828;,
 37.16962;-12.74840;-3.28828;,
 -34.89066;61.92852;-3.28828;,
 -28.31415;61.92852;-3.28828;,
 -28.31415;-12.74840;-3.28828;,
 -34.89066;-12.74840;-3.28828;,
 -28.31415;61.92852;-3.28828;,
 -28.31415;61.92852;3.28828;,
 -28.31415;-12.74840;3.28828;,
 -28.31415;-12.74840;-3.28828;,
 -28.31415;61.92852;3.28828;,
 -34.89066;61.92852;3.28828;,
 -34.89066;-12.74840;3.28828;,
 -28.31415;-12.74840;3.28828;,
 -34.89066;61.92852;3.28828;,
 -34.89066;61.92852;-3.28828;,
 -34.89066;-12.74840;-3.28828;,
 -34.89066;-12.74840;3.28828;,
 -28.31415;61.92852;-3.28828;,
 -34.89066;61.92852;-3.28828;,
 -34.89066;-12.74840;-3.28828;,
 -28.31415;-12.74840;-3.28828;,
 -31.20972;61.34027;-1.84376;,
 34.33673;61.34027;-1.84376;,
 34.33673;49.06383;-1.84376;,
 -31.20972;49.06383;-1.84376;,
 34.33673;61.34027;-1.84376;,
 34.33673;61.34027;1.84376;,
 34.33673;49.06383;1.84376;,
 34.33673;49.06383;-1.84376;,
 34.33673;61.34027;1.84376;,
 -31.20972;61.34027;1.84376;,
 -31.20972;49.06383;1.84376;,
 34.33673;49.06383;1.84376;,
 -31.20972;61.34027;1.84376;,
 -31.20972;61.34027;-1.84376;,
 -31.20972;49.06383;-1.84376;,
 -31.20972;49.06383;1.84376;,
 34.33673;61.34027;-1.84376;,
 -31.20972;61.34027;-1.84376;,
 -31.20972;49.06383;-1.84376;,
 34.33673;49.06383;-1.84376;,
 -31.20972;0.41997;-1.84376;,
 34.33673;0.41997;-1.84376;,
 34.33673;-11.85646;-1.84376;,
 -31.20972;-11.85646;-1.84376;,
 34.33673;0.41997;-1.84376;,
 34.33673;0.41997;1.84376;,
 34.33673;-11.85646;1.84376;,
 34.33673;-11.85646;-1.84376;,
 34.33673;0.41997;1.84376;,
 -31.20972;0.41997;1.84376;,
 -31.20972;-11.85646;1.84376;,
 34.33673;-11.85646;1.84376;,
 -31.20972;0.41997;1.84376;,
 -31.20972;0.41997;-1.84376;,
 -31.20972;-11.85646;-1.84376;,
 -31.20972;-11.85646;1.84376;,
 34.33673;0.41997;-1.84376;,
 -31.20972;0.41997;-1.84376;,
 -31.20972;-11.85646;-1.84376;,
 34.33673;-11.85646;-1.84376;;
 
 30;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,6,15;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;34,27,38,39;,
 4;40,41,28,37;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;54,47,58,59;,
 4;60,61,48,57;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;74,67,78,79;,
 4;80,81,68,77;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;94,87,98,99;,
 4;100,101,88,97;;
 
 MeshMaterialList {
  2;
  30;
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.592941;0.800000;0.762353;0.490000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.655686;0.655686;0.655686;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  30;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;;
 }
 MeshTextureCoords {
  102;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  -1.012990;-1.016390;,
  2.012990;-1.016390;,
  2.012990;2.008540;,
  -1.012990;2.008540;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}