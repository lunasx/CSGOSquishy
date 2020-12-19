
/*MIT License

Copyright(c) 2020 Black

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


https://github.com/xBlack40/CSGOSquishy/blob/main/LICENSE */

#pragma once
#include <assert.h>
template <class T, class I = int> class utl_memory
{
public:
	inline bool IsIdxValid(I i) const
	{
		long x = i;
		return (x >= 0) && (x < m_nAllocationCount);
	}
	T& operator[](I i);
	const T& operator[](I i) const;
	T *Base()
	{
		return m_pMemory;
	}
	inline int NumAllocated() const
	{
		return m_nAllocationCount;
	}
	void Grow(int num)
	{
		assert(num > 0);

		auto oldAllocationCount = m_nAllocationCount;
	
		int nAllocationRequested = m_nAllocationCount + num;

		int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));


		if ((int)(I)nNewAllocationCount < nAllocationRequested)
		{
			if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
			{
				--nNewAllocationCount; 
			}
			else
			{
				if ((int)(I)nAllocationRequested != nAllocationRequested)
				{
					assert(0);
					return;
				}
				while ((int)(I)nNewAllocationCount < nAllocationRequested)
				{
					nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
				}
			}
		}

		m_nAllocationCount = nNewAllocationCount;

		if (m_pMemory)
		{
			auto ptr = new unsigned char[m_nAllocationCount * sizeof(T)];

			memcpy(ptr, m_pMemory, oldAllocationCount * sizeof(T));
			m_pMemory = (T*)ptr;
		}
		else
		{
			m_pMemory = (T*)new unsigned char[m_nAllocationCount * sizeof(T)];
		}
	}
protected:
	T * m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template< class T, class I >
inline T& utl_memory<T, I>::operator[](I i)
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class I >
inline const T& utl_memory<T, I>::operator[](I i) const
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class A = utl_memory<T> >
class utl_vector
{
	typedef A CAllocator;

	typedef T *iterator;
	typedef const T *const_iterator;
public:
	T & operator[](int i);
	const T& operator[](int i) const;

	T& Element(int i)
	{
		return m_Memory[i];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int count() const
	{
		return m_Size;
	}

	void remove_all()
	{
		for (int i = m_Size; --i >= 0; )
			Destruct(&Element(i));

		m_Size = 0;
	}

	inline bool IsValidIndex(int i) const
	{
		return (i >= 0) && (i < m_Size);
	}

	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
		{
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());
		}

		m_Size += num;
	}

	int InsertBefore(int elem)
	{
	
		assert((elem == count()) || IsValidIndex(elem));

		GrowVector();
		Construct(&Element(elem));
		return elem;
	}

	inline int AddToHead()
	{
		return InsertBefore(0);
	}

	inline int AddToTail()
	{
		return InsertBefore(m_Size);
	}

	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + count(); }
	const_iterator end() const { return Base() + count(); }

protected:
	CAllocator m_Memory;
	int m_Size;
	T *m_pElements;
};

template< typename T, class A >
inline T& utl_vector<T, A>::operator[](int i)
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline const T& utl_vector<T, A>::operator[](int i) const
{
	assert(i < m_Size);
	return m_Memory[i];
}