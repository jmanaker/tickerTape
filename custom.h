#ifndef CUSTOM

#include <cassert>

#ifndef INCLUDE

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>

#ifdef INCLUDE_ALGORITHM
#undef INCLUDE_ALGORITHM
#include <algorithm>
#else
template<class _II, class _Fn>
inline _Fn for_each(_II _F, _II _L, _Fn _Op)
{
	for (; _F != _L; ++_F)
	{
		_Op(*_F);
	}
	return (_Op);
}
#endif
//INCLUDE_ALGORITHM

#include <math.h>

#ifdef INCLUDE_STDLIB
#include <stdlib.h>
#endif
//INCLUDE_STDLIB

#ifdef INCLUDE_TIME
#include <time.h>
#endif
//INCLUDE_TIME

#include <iostream>
#include <string>
#include <functional>

using namespace std;

#else
#undef INCLUDE
//include
#endif

#ifndef FULL

template<typename T, typename U>
U* cast(T* start, int length)
{
	U* end = new U[length];
	for(int index = 0; index < length; index++)
	{
		*(end + index) = (U)start[index];
	}
	return end;
}

template<typename T>
inline T* copy(T* start, int length, T*& end)
{
	for(int index = 0; index < length; index++)
	{
		*(end + index) = *(start + index);
	}
	return end;
}

inline int* range(int lower, int upper, int*& length)
{
        return range(lower, upper, 1, length);
}

int* range(int lower, int upper, int step, int*& length)
{
	*length = (upper - lower) / step;
	int* partial = new int[*length];
	for(int index = 0; index < *length; index++)
	{
		*(partial + index) = lower + step * index; 
	}
	return partial;
}

template<typename T>
T aggregate(T* array, T* end, T defaulte = *(new T()))
{
	for( ; array < end; array++)
	{
		defaulte = defaulte + *array;
	}
	return defaulte;
}

template<typename T>
class Vector
{
	private:
		struct LinkItem
		{
			public:
				T* Item;
				LinkItem* Next;
				const int Length&;
				LinkItem(T* Item = NULL, int length = 1, LinkItem* Next = NULL) : Length(length)
				{
					this->Item = Item;
					this->length = length;
					this->Next = Next;
				}
				LinkItem& operator =(LinkItem rhs)
				{
					this->Item = rhs.Item;
					this->length = rhs.length;
					this->Next = rhs.Next;
					return *this;
				}
			private:
				int length;
		};
                LinkItem* current = NULL;
	public:
		LinkItem* Head = NULL;
		Vector()
		{
			goTo = 0;
		}
		Vector(Vector<T>& copy)
		{
			Head = copy.current;
			current = Head;
			while(current.Next != NULL)
			{
				current.Next = current.Next;
				current = current.Next;
			}
			current = Head;
			this->goTo = copy.goTo;
		}
		Vector(Vector<T>* copy)
		{
			Head = copy->current;
			current = Head;
			while(current.Next != NULL)
			{
				current.Next = current.Next;
				current = current.Next;
			}
			current = Head;
			this->goTo = copy->goTo;
		}
		~Vector()
		{
			current = Head.Next;
			while(current != NULL)
			{
				delete Head;
				Head = current;
				current = Head.Next;
			}
		}
		void Add(T* array, int length = 1)
		{
			current.Next = new LinkItem(array, length);
			current = current.Next;
		}
		Vector<T>& operator +(int rarg)
		{
			this->goTo += rarg;
			return *this;
		}
		Vector<T>& operator -(int rarg)
		{
			this->goTo -= rarg;
			return *this;
		}
		bool operator !=(T* rarg)
		{
			return &(*(*this)) != rarg;
		}
		bool operator ==(T* rarg)
		{
			return !((*this) != rarg);
		}
		bool operator >=(T* rarg)
		{
			return &(*(*this)) >= rarg;
		}
		bool operator <=(T* rarg)
		{
			return &(*(*this)) <= rarg;
		}
		bool operator >(T* rarg)
		{
			return !((*this) <= rarg);
		}
		bool operator <(T* rarg)
		{
			return !((*this) >= rarg);
		}
		T operator [](int rarg)
		{
			return (*this + rarg).operator*();
		}
		T& operator *()
		{
			LinkItem* newOne = Head;
			int offset = 0;
			int gT = this->goTo;
			while(((int)newOne->Next) && (gT > newOne->Length))
			{
				gT -= newOne->Length;
				newOne = newOne->Next;
			}
			if(!((int)newOne->Next) && gT)
			{
				newOne = (newOne->Next = new LinkItem(new T[gT], gT));
			}
			return *(newOne.Item + gT);
		}
		T* operator ->()
		{
			return &(this->operator*());
		}
#define CONVERT(x) operator x(){return &((*this).operator*());}
		CONVERT(signed int)
		CONVERT(unsigned int)
		CONVERT(signed long int)
		CONVERT(unsigned long int)
		CONVERT(unsigned short int)
		CONVERT(signed short int)
		COVERT(T*);
#undef CONVERT
	private:
		int goTo;
};

//No algorithm here; it would violate encapsulation
template<typename T>
Vector<T> operator +(int larg, Vector<T>& rarg)
{
	return rarg + larg;
}
template<typename T>
inline Vector<T>& operator +=(Vector<T>& larg, int rarg)
{
	return (larg = larg + rarg);
}
template<typename T>
inline Vector<T>& operator ++(Vector<T>& arg)
{
	return (arg += 1);
}
template<typename T>
inline Vector<T>& operator ++(Vector<T>& arg, int placeholder)
{
	return ((arg++) - 1);
}
template<typename T>
inline Vector<T>& operator -=(Vector<T>& larg, int rarg)
{
	return (larg = larg - rarg);
}
template<typename T>
inline Vector<T>& operator --(Vector<T>& arg)
{
	return (arg += 1);
}
template<typename T>
inline Vector<T>& operator --(Vector<T>& arg, int placeholder)
{
	return ((arg--) + 1);
}

class Collection
{
	private:
		struct LinkItem
		{
			public:
				void* Item;
				LinkItem* Next;
				const int Length&;
				LinkItem(void* Item = NULL, int length = 1, LinkItem* Next = NULL) : Length(length)
				{
					this->Item = Item;
					this->length = length;
					this->Next = Next;
				}
				void Cut(int num, bool del = true)
				{
					assert(num > 0);
					length -= num;
					if(del)
					{
						delete[] (Item + Length);
					}
				}
				LinkItem& operator =(LinkItem rhs)
				{
					this->Item = rhs.Item;
					this->length = rhs.length;
					this->Next = rhs.Next;
					return *this;
				};
			private:
				int length;
		};
                LinkItem* current = NULL;
	public:
		LinkItem* Head&;
		Collection() : Head(head)
		{
			goTo = 0;
		}
		Collection(Collection& copy) : Head(head)
		{
			head = copy.current;
			current = head;
			while(current.Next != NULL)
			{
				current.Next = current.Next;
				current = current.Next;
			}
			current = head;
			this->goTo = copy.goTo;
		}
		Collection(Collection* copy) : Head(head)
		{
			head = copy->current;
			current = head;
			while(current.Next != NULL)
			{
				current.Next = current.Next;
				current = current.Next;
			}
			current = head;
			this->goTo = copy->goTo;
		}
		~Collection()
		{
			current = Head.Next;
			while(current != NULL)
			{
				delete Head;
				Head = current;
				current = Head.Next;
			}
                        delete Head;
		}
		void Add(void* array, int length = 1)
		{
			current.Next = new LinkItem(array, length);
			current = current.Next;
		}
		void Add(void* offset, void* array, int length = 1)
		{
			LinkItem*& index = head;
			while(index->Item != offset)
			{
				index = index.Next;
			}
			LinkItem* insert = new LinkItem(array, length, index.Next);
			index.Next = insert;
			return;
		}
		void Add(int offset, void* array, int length = 1)
		{
			LinkItem* newOne = head;
			int gT = 0;
			while(gT > newOne->Length)
			{
				assert(newOne->Next);
				gT -= newOne->Length;
				newOne = newOne->Next;
			}
			if(gT)
			{
				Add(newOne->Item, newOne->Item + gT, newOne->Length - gT);
				newOne->Cut(gT, false);
			}
			Add(newOne->Item, array, length);
		}
		void* Remove(void* offset)
		{
			LinkItem*& index = head;
			assert(index->Next);
			while(index->Next->Item != offset)
			{
				index = index.Next;
				assert(index->Next);
			}
			void* ret = index->Next->Item;
			index->Next = index->Next->Next;
			return ret;
		}
		void* Remove(int offset)
		{
			LinkItem*& newOne = head;
			int gT = 0;
			while(gT > newOne->Length)
			{
				assert(newOne->Next);
				gT -= newOne->Length;
				newOne = newOne->Next;
			}
		}
		void* Get(int gT)
		{
			LinkItem* newOne = head;
			int offset = 0;
			while(((int)newOne->Next) && (gT > newOne->Length))
			{
				gT -= newOne->Length;
				newOne = newOne->Next;
			}
			if((newOne->Next == NULL) && gT)
			{
                            LinkItem* temp = new LinkItem(NULL, 1, NULL);
                            for(int index = gT - 1; index > 0; index++)
                            {
                                temp = new LinkItem(NULL, 1, temp);
                            }
                            newOne = (newOne->Next = temp);
			}
			return newOne->Item + gT;
		}
		Collection operator=(Collection newOne)
		{
			head = newOne.current;
			current = head;
			while(current.Next != NULL)
			{
				current.Next = current.Next;
				current = current.Next;
			}
			current = head;
			this->goTo = newOne.goTo;
		}
	private:
		int goTo;
		LinkItem* head = NULL;
};

#define SI sizeInt
#define BE BitwiseEdit
namespace deprecated
{
	class BEType
	{
                private:
			int* obj;
			int SI;
		public:
			BEType()
			{
				SI = sizeof(5);
				obj = NULL;
			}
			void Push(void* obj, int size)
			{
				
				assert(this->obj == NULL);
				int length = size / SI;
				if(size % SI != 0)
				{
					length++;
				}
				this->obj = new int[length];
				int* hold = (int*)obj;
				for(int index = 0; index < length; index++)
				{
					*(this->obj + index) = *(hold + index);
				}
			}
			template<typename T>
			inline void Push(T*& obj) //Sure, I'll write your code for you...
			{
				Push(obj, sizeof(obj));
			}
			void* Pop()
			{
				assert(obj != NULL);
				void* hold = obj;
				obj = NULL;
				return hold;
			}
			template<typename T>
			inline T* Pop()
			{
				return (T*)this->Pop();
			}
			bool operator[](int rarg)
			{
				assert(obj != NULL);
#ifdef _DEBUG
				//Run steps one at a time
				printf("rarg = ");
				cout << rarg;
#define h1 holdOne
				int h1 = rarg / (SI * 8);
				printf("\nindex = ");
				cout << h1;
				h1 = *(obj + h1);
				printf("\nobj[index] = ");
				cout << h1;
#define h2 holdTwo
				int h2 = rarg % (SI * 8);
				printf("\noffset = ");
				cout << h2;
				h2 = 1 << h2;
				printf("\ntest = ");
				cout << h2;
				h1 = h1 & h2;
				printf("\nobj[index] & test = ");
				cout << h1;
				h1 = h1 >> (rarg % (SI * 8));
				printf("\nretval = ");
				cout << h1;
				printf("\n");
				return h1;
#undef h1
#undef h2
#else
				return (*(obj + rarg / (SI * 8)) & (1 << rarg % (SI * 8))) >> (rarg % (SI * 8));
#endif
			}
	};
}
deprecated::BEType BE ();

#define deprecated #error error:deprecated means deprecated!

#undef DEF
#undef SI
#undef BE
#undef CHECK

//full
#endif

#else
#undef CUSTOM
//custom
#endif
