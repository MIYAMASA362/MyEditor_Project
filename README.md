# MyEditor_Project

ざっと概要
- Core  
  プラットフォームを基盤にする上位階層で利用されるクラス群
- Platform  
  Windowsなどのプラットフォームを基盤にCoreなどの上位階層で利用できる様にまとめる
- Thirdparty  
  DirectXやOpenGLなど

# Core <layer2>
- 

# Engine <layer3>
- Base
- Application

# Platform <layer1>
- Config.h  
  システム全体に影響がある。プラットフォーム検出やEXPORTの設定がされている

# Thirdparty <layer2>
- Graphics
  - DirectX
  - OpenGL
- 