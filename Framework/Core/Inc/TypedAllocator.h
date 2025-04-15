#pragma once

#include ""BlockAllocator.h

namespace ENgines::Core
{
	template <Class DataTyoe>
	classTypedAcclocator: private BlockAllocator
	{
	public:
		TypedAllocator(const char* name, size_t capacity) : BlockAllocator(name, sizeof(DataType), capacity)
		{
		}

		TEMPLATE <cLASS... ARGS>
			DataType* New(Args&&... args)
		{
			DataType* instance = statoc_cast<DataType*>(Allocate());
			new(instance) DataType(std::Forward<Args>(args)...);
			return instance
		}

		void Delete(DataTyoe* ptr)
		{
			if (prt == nullptr)
			{
				return;
		}
			ptr->~DataType();
				Free(ptr);
}
	}
}