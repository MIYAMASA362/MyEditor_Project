#pragma once
#ifndef CORE_MODULE_H
#define CORE_MODULE_H

namespace Core
{
	class ModuleSystem;

	/**
	* @enum		ModuleType
	* @brief    �������s���^�C�~���O���w��
	*/
	enum ModuleType
	{
		None		= 0,		//�ݒ�Ȃ�
		Initialize	= 1 << 0,	//������
		Update		= 1 << 1,	//�X�V
		Render		= 1 << 2,	//�`��
		Finalize	= 1 << 3,	//�I������
	};

	constexpr ModuleType operator&(ModuleType a,ModuleType b)
	{
		return static_cast<ModuleType>(static_cast<u8>(a) & static_cast<u8>(b));
	}

	constexpr ModuleType operator|(ModuleType a,ModuleType b)
	{
		return static_cast<ModuleType>(static_cast<u8>(a) | static_cast<u8>(b));
	}

	namespace detail
	{
		/**
		* @class    IModule
		* @brief    
		*/
		class IModule
		{
			friend ModuleSystem;
		private:
			const ModuleType m_ModuleType;

		public:
			IModule(ModuleType type): m_ModuleType(type) {};
			virtual ~IModule() {};

			virtual void behaviour() = 0;

		};//class IModule

	}//namespace Core::detail
}//namespace Core

#endif//ifndef CORE_MODULE_H