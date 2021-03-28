﻿// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"

#define ENGINE_EXPORT

#include"Platform/Config.h"
#include"Platform/Base/INetwork.h"
#include"Platform/Base/Logger.h"
#include"Platform/Base/Assert.h"
#include"Platform/IO/Stream.h"
#include"Platform/IO/FileStream.h"
#include"Platform/IO/DllLoader.h"

#include"Thirdparty/Network/Winsock/Winsock.h"
#include"Thirdparty/Network/Winsock/Network.h"

#endif //PCH_H
