#pragma once
#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

namespace Core
{
	namespace System
	{
		class ISystemModule;

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
		* @class    ISystem
		* @brief    システムの基幹
		*/
		class ISystem : public Platform::detail::ISystem
		{
			using ModuleIndex = std::vector<ISystemModule*>;
		private:
			void removeAtModules(ModuleIndex* index, ISystemModule* iModule);

		protected:
			std::map<ModuleType,ModuleIndex> m_Modules{
				{ModuleType::Initialize,ModuleIndex()},
				{ModuleType::Update,ModuleIndex()},
				{ModuleType::Render,ModuleIndex()},
				{ModuleType::Finalize,ModuleIndex()}
			};

		public:
			ISystem();
			virtual ~ISystem();

			virtual void RegisterModule(ISystemModule* iModule);
			virtual void UnRegisterModule(ISystemModule* iModule);

			virtual void ProcessModule(ModuleType type);

			virtual int mainLoop() override =0;
		};// class ISystem

		/**
		* @class    SystemModule
		* @brief    システムに組み込まれるモジュール
		*/
		class ISystemModule : public Core::detail::IModule
		{
			friend ISystem;
		private:
			const ModuleType m_ModuleType;

		public:
			ISystemModule(ModuleType type);
			virtual ~ISystemModule();

			virtual void behaviour() = 0;

		};// class SystemModule

	}// namespace Core::System
}// namespace Core

#endif// ifndef CORE_SYSTEM_H