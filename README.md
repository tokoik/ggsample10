# ggsample10 - 球面調和関数 (Spherical Harmonics) による環境照明

## 1. 概要

本プログラムは、[ゲームグラフィックス特論](https://tokoik.github.io/gg/)の講義資料 [ggnote10.pdf](https://tokoik.github.io/gg/ggnote10.pdf) に対応する宿題のひな型プログラムです。

- 講義ポータル: [ゲームグラフィックス特論 - 床井研究室](https://tokoik.github.io/gg/)
- 講義資料: [ggnote10.pdf](https://tokoik.github.io/gg/ggnote10.pdf)

## 2. 宿題の内容

環境の光源による放射照度の球面調和解析による陰影付けを実装してください。

- Lambert の余弦法則による直接光の陰影付けを、環境の放射照度マップの球面調和関数による近似を用いた陰影付けに変更してください (`ggsample10.vert`)。
- 球面調和係数は uniform 変数の配列 `sh`（9要素）に格納されています。

## 3. 対応環境

- **Windows**: Visual Studio 2019 / 2022 / 2026 (CMake 経由で GLFW 3.4 を自動ダウンロード)
- **macOS**: Xcode (GLFW 3.4 を自動ダウンロード、OpenGL Framework を使用)
- **Ubuntu Linux**: GCC / Make (システム標準の libglfw3-dev, libgl1-mesa-dev を使用)

## 4. ビルド手順

### Windows (Visual Studio)

```pwsh
cmake -B build -S .
cmake --build build --config Release
```

### macOS (Xcode)

```bash
cmake -B build -G Xcode
cmake --build build --config Release
```

### Ubuntu Linux (Makefile)

```bash
sudo apt-get update
sudo apt-get install -y libglfw3-dev libgl1-mesa-dev
cmake -B build -S .
cmake --build build
```

## 5. 起動方法

ビルド完了後、生成された実行ファイルを実行します。

- **Windows**: `build/Release/ggsample10.exe`
- **macOS**: `build/Release/ggsample10.app`
- **Linux**: `build/ggsample10`

## 6. 操作方法

- **マウス左ドラッグ**: シーンの視点回転
- **マウス右ドラッグ**: 視点の平行移動
- **マウスホイール**: ズームイン / ズームアウト
- **[q] / [Q] / [ESC]**: プログラムの終了
