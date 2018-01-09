// ウィンドウ関連の処理
#include "Window.h"

// シェーダー関連の処理
#include "shader.h"

// 標準ライブラリ
#include <cmath>
#include <memory>

// アニメーションの周期（秒）
const double cycle(10.0);

//
// SH 係数テーブル
//
#include "shcoeff.h"

//
// メインプログラム
//
int main(int argc, const char * argv[])
{
  // ウィンドウを作成する
  Window window("ggsample10");

  // 背景色を指定する
  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // プログラムオブジェクトの作成
  const GLuint program(loadProgram("simple.vert", "pv", "simple.frag", "fc"));

  // uniform 変数のインデックスの検索（見つからなければ -1）
  const GLint mwLoc(glGetUniformLocation(program, "mw"));
  const GLint mcLoc(glGetUniformLocation(program, "mc"));
  const GLint mgLoc(glGetUniformLocation(program, "mg"));
  const GLint shLoc(glGetUniformLocation(program, "sh"));

  // ビュー変換行列を mv に求める
  const GgMatrix mv(ggLookat(0.0f, 1.0f, 2.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // 図形データの作成
  const std::unique_ptr<const GgElements> object(ggElementsObj("bunny.obj"));

  // 経過時間のリセット
  glfwSetTime(0.0);

  // ウィンドウが開いている間くり返し描画する
  while (window.shouldClose() == GL_FALSE)
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // シェーダプログラムの使用開始
    glUseProgram(program);

    // 時刻の計測
    const float t(static_cast<float>(fmod(glfwGetTime(), cycle) / cycle));

    // SH 係数テーブルの番号
    const int shtable(static_cast<int>(nshcoeff * t) % nshcoeff);

    // モデルビュー変換行列 (時刻 t にもとづく回転アニメーション)
    const GgMatrix mw(mv.rotateY(12.56637f * t));

    // 法線変換行列
    const GgMatrix mg(mw.normal());

    // 投影変換行列
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // モデルビュー・投影変換
    const GgMatrix mc(mp * mw);

    // uniform 変数を設定する
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());
    glUniform3fv(shLoc, 9, *shcoeff[shtable]);

    // 図形の描画
    object->draw();

    // シェーダプログラムの使用終了
    glUseProgram(0);

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }

  return 0;
}
