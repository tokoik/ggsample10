#version 150 core
#extension GL_ARB_explicit_attrib_location : enable

// ラスタライザから受け取る頂点属性の補間値
in vec3 idiff;                                      // 拡散反射光強度

// フレームバッファに出力するデータ
layout (location = 0) out vec4 fc;                  // フラグメントの色

void main(void)
{
  fc = vec4(idiff, 1.0);
}
