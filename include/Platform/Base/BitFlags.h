#pragma once
#ifndef PLATFORM_BITFLAGS_H
#define PLATFORM_BITFLAGS_H

namespace Platform
{
	namespace detail
	{
		template<typename BitType,typename MaskType = unsigned int>
		class BitFlags
		{
		private:
			MaskType m_mask;

		public:
			BitFlags() : m_mask(0) {}
			BitFlags(BitType bit) : m_mask(static_cast<MaskType>(bit)) {}
			BitFlags(BitFlags<BitType> const& flag) : m_mask(flag.m_mask){}

		};//class BitFlags

	}//namespace Platform::detail
}//namespace Platform

#endif //ifndef PLATFORM_BITFLAGS_H