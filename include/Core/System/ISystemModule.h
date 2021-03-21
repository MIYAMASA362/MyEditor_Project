#pragma once
#ifndef CORE_ISYSTEM_MODULE_H
#define CORE_ISYSTEM_MODULE_H

namespace Core
{
	namespace System
	{
		class ISystem;

		/**
		* @enum		ModuleType
		* @brief    処理を行うタイミングを指定
		*/
		enum ModuleType
		{
			None = 0,				//設定なし
			Initialize = 1 << 0,	//初期化
			Update = 1 << 1,		//更新
			Render = 1 << 2,		//描画
			Finalize = 1 << 3,		//終了処理
		};

		constexpr ModuleType operator&(ModuleType a, ModuleType b)
		{
			return static_cast<ModuleType>(static_cast<u8>(a) & static_cast<u8>(b));
		}

		constexpr ModuleType operator|(ModuleType a, ModuleType b)
		{
			return static_cast<ModuleType>(static_cast<u8>(a) | static_cast<u8>(b));
		}

		/**
		* @class    SystemModule
		* @brief    システムに組み込まれるモジュール
		*/
		class ISystemModule : public ::Platform::detail::IModule
		{
			friend ISystem;
		private:
			const ModuleType m_ModuleType;

		public:
			ISystemModule(ModuleType type);
			virtual ~ISystemModule();

			virtual void behaviour() ENGINE_PURE;

		};// class SystemModule

	}// namesapce Core::System
}// namespace Core

#endif // ifndef CORE_ISYSTEM_MODULE_H