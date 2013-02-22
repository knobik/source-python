//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifndef UTLPRIORITYQUEUE_H
#define UTLPRIORITYQUEUE_H
#ifdef _WIN32
#pragma once
#endif

#include "utlvector.h"

template < typename T >
class CDefUtlPriorityQueueLessFunc
{
public:
	bool operator()( const T &lhs, const T &rhs, bool (*lessFuncPtr)( T const&, T const& ) )	
	{ 
		return lessFuncPtr( lhs, rhs );	
	}
};


// T is the type stored in the queue, it must include the priority
// The head of the list contains the element with GREATEST priority
// configure the LessFunc_t to get the desired queue order
template< class T, class LessFunc = CDefUtlPriorityQueueLessFunc< T >, class A = CUtlMemory<T> > 
class CUtlPriorityQueue
{
public:
	// Less func typedef
	// Returns true if the first parameter is "less priority" than the second
	// Items that are "less priority" sort toward the tail of the queue
	typedef bool (*LessFunc_t)( T const&, T const& );

	typedef T ElemType_t;

	// constructor: lessfunc is required, but may be set after the constructor with
	// SetLessFunc
	CUtlPriorityQueue( int growSize = 0, int initSize = 0, LessFunc_t lessfunc = 0 );
	CUtlPriorityQueue( T *pMemory, int numElements, LessFunc_t lessfunc = 0 );

	// gets particular elements
	inline T const&	ElementAtHead() const { return m_heap.Element(0); }

	inline bool IsValidIndex(int index) { return m_heap.IsValidIndex(index); }

	// O(lgn) to rebalance the heap
	void		RemoveAtHead();
	void		RemoveAt( int index );

	// O(lgn) to rebalance heap
	void		Insert( T const &element );
	// Sets the less func
	void		SetLessFunc( LessFunc_t func );

	// Returns the count of elements in the queue
	inline int	Count() const { return m_heap.Count(); }
	
	// doesn't deallocate memory
	void		RemoveAll() { m_heap.RemoveAll(); }

	// Memory deallocation
	void		Purge() { m_heap.Purge(); }

	inline const T &	Element( int index ) const { return m_heap.Element(index); }

protected:
	CUtlVector<T, A>	m_heap;

	void		Swap( int index1, int index2 );

	// Used for sorting.
	LessFunc_t m_LessFunc;
};

template< class T, class LessFunc, class A >
inline CUtlPriorityQueue<T, LessFunc, A>::CUtlPriorityQueue( int growSize, int initSize, LessFunc_t lessfunc ) :
	m_heap(growSize, initSize), m_LessFunc(lessfunc)
{
}

template< class T, class LessFunc, class A >
inline CUtlPriorityQueue<T, LessFunc, A>::CUtlPriorityQueue( T *pMemory, int numElements, LessFunc_t lessfunc )	: 
	m_heap(pMemory, numElements), m_LessFunc(lessfunc)
{
}

template< class T, class LessFunc, class A >
void CUtlPriorityQueue<T, LessFunc, A>::RemoveAtHead()
{
	m_heap.FastRemove( 0 );
	int index = 0;

	int count = Count();
	if ( !count )
		return;

	LessFunc lessFunc;
	int half = count/2;
	int larger = index;
	while ( index < half )
	{
		int child = ((index+1) * 2) - 1;	// if we wasted an element, this math would be more compact (1 based array)
		if ( child < count )
		{
			// Item has been filtered down to its proper place, terminate.
			if ( lessFunc( m_heap[index], m_heap[child], m_LessFunc ) )
			{
				// mark the potential swap and check the other child
				larger = child;
			}
		}
		// go to sibling
		child++;
		if ( child < count )
		{
			// If this child is larger, swap it instead
			if ( lessFunc( m_heap[larger], m_heap[child], m_LessFunc ) )
				larger = child;
		}
		
		if ( larger == index )
			break;

		// swap with the larger child
		Swap( index, larger );
		index = larger;
	}
}


template< class T, class LessFunc, class A >
void CUtlPriorityQueue<T, LessFunc, A>::RemoveAt( int index )
{
	Assert(m_heap.IsValidIndex(index));
	m_heap.FastRemove( index );

	int count = Count();
	if ( !count )
		return;

	LessFunc lessFunc;
	int half = count/2;
	int larger = index;
	while ( index < half )
	{
		int child = ((index+1) * 2) - 1;	// if we wasted an element, this math would be more compact (1 based array)
		if ( child < count )
		{
			// Item has been filtered down to its proper place, terminate.
			if ( lessFunc( m_heap[index], m_heap[child], m_LessFunc ) )
			{
				// mark the potential swap and check the other child
				larger = child;
			}
		}
		// go to sibling
		child++;
		if ( child < count )
		{
			// If this child is larger, swap it instead
			if ( lessFunc( m_heap[larger], m_heap[child], m_LessFunc ) )
				larger = child;
		}
		
		if ( larger == index )
			break;

		// swap with the larger child
		Swap( index, larger );
		index = larger;
	}
}

template< class T, class LessFunc, class A >
void CUtlPriorityQueue<T, LessFunc, A>::Insert( T const &element )
{
	int index = m_heap.AddToTail();
	m_heap[index] = element;

	LessFunc lessFunc;
	while ( index != 0 )
	{
		int parent = ((index+1) / 2) - 1;
		if ( lessFunc( m_heap[index], m_heap[parent], m_LessFunc ) )
			break;

		// swap with parent and repeat
		Swap( parent, index );
		index = parent;
	}
}

template< class T, class LessFunc, class A >
void CUtlPriorityQueue<T, LessFunc, A>::Swap( int index1, int index2 )
{
	T tmp = m_heap[index1];
	m_heap[index1] = m_heap[index2];
	m_heap[index2] = tmp;
}

template< class T, class LessFunc, class A >
void CUtlPriorityQueue<T, LessFunc, A>::SetLessFunc( LessFunc_t lessfunc )
{
	m_LessFunc = lessfunc;
}

#endif // UTLPRIORITYQUEUE_H
