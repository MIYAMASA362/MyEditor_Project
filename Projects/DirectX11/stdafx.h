// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、
// または、参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>

#define ENGINE_EXPORT

// プログラムに必要な追加ヘッダーをここで参照してください
#include"Platform/Config.h"
#include"Platform/DesignPattern/Singleton.h"
#include"Platform/DesignPattern/Factory.h"
#include"Platform/Base/IRenderer.h"

#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Platform/Graphics/DirectX11.h"

#include"Core/Graphics/GraphicsFactory.h"
#include"Thirdparty/Graphics/DirectX11/DX11GraphicsFactory.h"
