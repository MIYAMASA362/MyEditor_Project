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
		* @brief    �������s���^�C�~���O���w��
		*/
		enum ModuleType
		{
			None = 0,				//�ݒ�Ȃ�
			Initialize = 1 << 0,	//������
			Update = 1 << 1,		//�X�V
			Render = 1 << 2,		//�`��
			Finalize = 1 << 3,		//�I������
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
		* @brief    �V�X�e���ɑg�ݍ��܂�郂�W���[��
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