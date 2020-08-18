#pragma once
#ifndef BITFLAGS_H
#define BITFLAGS_H

namespace Core
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

	}//namespace Core::detail

}//namespace Core

#endif //ifndef BITFLAGS_H