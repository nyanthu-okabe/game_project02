### **NYANCHU ENGINE** 設計書

0. info
gameengineは
*./nyanchu_engine/*

アプリ側は
*./application/*



1. 目的
- 複数ゲームで再利用可能な汎用C++ゲームエンジン
- OSSライブラリ(bgfx, GLFW, flecs, glm, Jolt, miniaudio, ImGui)を抽象化して提供
- アプリ側はライブラリAPIだけ触れば良い設計
- クロスプラットフォーム対応（Windows / Linux / macOS）
- 3DGameを抽象的に設計 / 運用できる

2. 開発環境
- *bgfx* レンダリング
- *GLFW* ウィンドウ・入力
- *glm*数学（ベクトル/行列）
- *flecsECS*（エンティティ・コンポーネント管理）
- *Jolt* 物理演算
- *miniaudio* オーディオ
- *ImGui* デバッグ / ツールUI

3. ビルド
+ cmake
+ ninja
+ gcc
* git
+ zed

4. デレクトリ構造
nyanchu-engine/
├─ CMakeLists.txt          # エンジン全体のビルド設定
├─ engine/                 # エンジン本体
│  ├─ include/nyanchu/     # 公開API
│  │    ├─ engine.h
│  │    ├─ renderer.h
│  │    ├─ audio.h
│  │    ├─ physics.h
│  │    └─ ecs.h
│  └─ src/                 # 実装
│       ├─ engine.cpp
│       ├─ renderer_bgfx.cpp
│       ├─ physics_jolt.cpp
│       ├─ audio_miniaudio.cpp
│       └─ ecs_flecs.cpp
├─ external/               # サードパーティライブラリ
├─ examples/               # サンプルゲーム
│  ├─ hello_world/
│  └─ voxel_demo/
├─ tools/                  # エディタやデバッグツール
└─ LICENSES/               # OSSライセンス文

5.  アプリ側のコード
#include <nyanchu/engine.h>
#include <nyanchu/renderer.h>
#include <nyanchu/audio.h>

int main() {
    nyanchu::Engine engine;
    engine.init();

    while (engine.running()) {
        engine.pollEvents();
        engine.beginFrame();

        engine.renderer().drawMesh("cube.obj");
        engine.audio().playSound("bgm.wav");

        engine.endFrame();
    }
}
