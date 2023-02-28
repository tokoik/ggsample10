//
// ゲームグラフィックス特論宿題アプリケーション
//
#include "GgApp.h"

// プロジェクト名
#ifndef PROJECT_NAME
#  define PROJECT_NAME "ggsample10"
#endif

// シェーダー関連の処理
#include "shader.h"

//
// SH 係数テーブル
//
#include "shcoeff.h"

// アニメーションの周期（秒）
constexpr auto cycle{ 10.0 };

//
// アプリケーション本体
//
int GgApp::main(int argc, const char* const* argv)
{
  // ウィンドウを作成する (この行は変更しないでください)
  Window window{ argc > 1 ? argv[1] : PROJECT_NAME };

  // 背景色を指定する
  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

  // 隠面消去を有効にする
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // プログラムオブジェクトの作成
  const auto program{ loadProgram(PROJECT_NAME ".vert", "pv", PROJECT_NAME ".frag", "fc") };

  // uniform 変数のインデックスの検索（見つからなければ -1）
  const auto mwLoc{ glGetUniformLocation(program, "mw") };
  const auto mcLoc{ glGetUniformLocation(program, "mc") };
  const auto mgLoc{ glGetUniformLocation(program, "mg") };
  const auto shLoc{ glGetUniformLocation(program, "sh") };

  // ビュー変換行列を mv に求める
  const auto mv{ ggLookat(0.0f, 1.0f, 2.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f) };

  // 図形データの作成
  const auto object{ ggElementsObj("bunny.obj") };

  // 経過時間のリセット
  glfwSetTime(0.0);

  // ウィンドウが開いている間くり返し描画する
  while (window)
  {
    // 画面消去
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // シェーダプログラムの使用開始
    glUseProgram(program);

    // 時刻の計測
    const auto t{ static_cast<float>(fmod(glfwGetTime(), cycle) / cycle) };

    // SH 係数テーブルの番号
    const auto shtable{ static_cast<int>(nshcoeff * t) % nshcoeff };

    // モデルビュー変換行列 (時刻 t にもとづく回転アニメーション)
    const auto mw{ mv.rotateY(12.56637f * t) };

    // 法線変換行列
    const auto mg{ mw.normal() };

    // 投影変換行列
    const auto mp{ ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f) };

    // モデルビュー・投影変換
    const auto mc{ mp * mw };

    // uniform 変数を設定する
    glUniformMatrix4fv(mwLoc, 1, GL_FALSE, mw.get());
    glUniformMatrix4fv(mcLoc, 1, GL_FALSE, mc.get());
    glUniformMatrix4fv(mgLoc, 1, GL_FALSE, mg.get());
    glUniform3fv(shLoc, nshcoeff, *shcoeff[shtable]);

    // 図形の描画
    object->draw();

    // シェーダプログラムの使用終了
    glUseProgram(0);

    // カラーバッファを入れ替えてイベントを取り出す
    window.swapBuffers();
  }

  return 0;
}
