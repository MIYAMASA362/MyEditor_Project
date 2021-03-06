// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、
// または、参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>

#define ENGINE_EXPORT
#define ENGINE_DIRECTX11

// プログラムに必要な追加ヘッダーをここで参照してください
#include"Platform/Config.h"
#include"Platform/DesignPattern/Singleton.h"
#include"Platform/Base/IRenderer.h"
#include"Platform/Base/IGraphics.h"
#include"Platform/Base/Logger.h"
#include"Platform/Base/Assert.h"
#include"Platform/IO/DllLoader.h"
#include"Platform/Module/Module.h"