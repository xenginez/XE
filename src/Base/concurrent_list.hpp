/*!
 * \file	concurrent_list.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/06/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONCURRENT_LIST_HPP__54A2A6BA_6D14_4E6D_9661_A14BE186618B
#define CONCURRENT_LIST_HPP__54A2A6BA_6D14_4E6D_9661_A14BE186618B

#include "Type.h"

BEG_XE_NAMESPACE

template< typename _Ty> struct _concurrent_list_node
{
public:
	using value_type = _Ty;
	using node_type = _concurrent_list_node<_Ty>;
	using pointer = _concurrent_list_node<_Ty> *;
	using reference = _concurrent_list_node<_Ty> &;
	using const_pointer = const _concurrent_list_node<_Ty> *;
	using const_reference = const _concurrent_list_node<_Ty> &;

public:
	_concurrent_list_node()
		:Next( nullptr ), Prev( nullptr )
	{ 
	}

	_concurrent_list_node( value_type && val, node_type * prev, node_type * next )
		:Value( val ), Next( next ), Prev( prev )
	{
	}

	_concurrent_list_node( const value_type & val, node_type * prev, node_type * next )
		:Value( val ), Next( next ), Prev( prev )
	{
	}

	_concurrent_list_node( const _concurrent_list_node & val )
		:Value( val.Value ), Next( val.Next.load() ), Prev( val.Prev.load() )
	{
	}

public:
	value_type Value;
	std::atomic<node_type *> Next;
	std::atomic<node_type *> Prev;
};


template <class _Mylist> class _concurrent_list_const_iterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;

	using _Nodeptr        = typename _Mylist::node_type *;
	using value_type      = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer         = const value_type *;
	using reference       = const value_type &;
	
	_concurrent_list_const_iterator()
		:_Node( nullptr )
	{
	}

	_concurrent_list_const_iterator( _Nodeptr _Pnode )
		:_Node( _Pnode )
	{

	}

public:
	reference operator*() const
	{
		return _Node->Value;
	}

	pointer operator->() const
	{
		return &( _Node->Value );
	}

public:
	_concurrent_list_const_iterator & operator++()
	{
		_Node = _Node->Next;
		return *this;
	}

	_concurrent_list_const_iterator operator++( int )
	{
		_Nodeptr n = _Node;
		_Node = _Node->Next;
		return { n, _List };
	}

	_concurrent_list_const_iterator & operator--()
	{
		_Node = _Node->Prev;
		return *this;
	}

	_concurrent_list_const_iterator operator--( int )
	{
		_Nodeptr n = _Node;
		_Node = _Node->Prev;
		return { n, _List };
	}

public:
	bool operator==( const _concurrent_list_const_iterator & _Right ) const
	{
		return _Node == _Right._Node;
	}

	bool operator!=( const _concurrent_list_const_iterator & _Right ) const
	{
		return _Node != _Right._Node;
	}

public:
	_Nodeptr _node() const
	{
		return _Node;
	}

protected:
	_Nodeptr _Node;
};

template <class _Mylist> class _concurrent_list_iterator : public _concurrent_list_const_iterator<_Mylist>
{
public:
	using iterator_category = std::bidirectional_iterator_tag;

	using _Nodeptr        = typename _Mylist::node_type*;
	using value_type      = typename _Mylist::value_type;
	using difference_type = typename _Mylist::difference_type;
	using pointer         = typename _Mylist::pointer;
	using reference       = value_type &;

	_concurrent_list_iterator()
		:_concurrent_list_const_iterator()
	{ }

	_concurrent_list_iterator( _Nodeptr _Pnode )
		:_concurrent_list_const_iterator( _Pnode )
	{
	}

public:
	reference operator*() const
	{
		return _Node->Value;
	}

	pointer operator->() const
	{
		return &( _Node->Value );
	}

public:
	_concurrent_list_iterator & operator++()
	{
		_Node = _Node->Next;
		return *this;
	}

	_concurrent_list_iterator operator++( int )
	{
		_Nodeptr n = _Node;
		_Node = _Node->Next;
		return { n, _List };
	}

	_concurrent_list_iterator & operator--()
	{
		_Node = _Node->Prev;
		return *this;
	}

	_concurrent_list_iterator operator--( int )
	{
		_Nodeptr n = _Node;
		_Node = _Node->Prev;
		return { n, _List };
	}

public:
	bool operator==( const _concurrent_list_iterator & _Right ) const
	{
		return _Node == _Right._Node;
	}

	bool operator!=( const _concurrent_list_iterator & _Right ) const
	{
		return _Node != _Right._Node;
	}
};


template< typename _Ty, typename _Alloc = std::allocator<_Ty>> class concurrent_list
{
public:
	static_assert( std::is_same_v<_Ty, typename _Alloc::value_type>, "concurrent_list<T, Allocator>" );
	
	using value_type      = _Ty;
	using node_type       = typename _concurrent_list_node<_Ty>;
	using allocator_type  = typename std::allocator_traits<_Alloc>::template rebind_alloc<node_type>;
	using allocator_traits= std::allocator_traits<_Alloc>;
	using size_type       = typename allocator_traits::size_type;
	using difference_type = typename allocator_traits::difference_type;
	using pointer         = typename allocator_traits::pointer;
	using const_pointer   = typename allocator_traits::const_pointer;
	using reference       = value_type &;
	using const_reference = const value_type &;

	using iterator                  = _concurrent_list_iterator<concurrent_list<_Ty, _Alloc>>;
	using const_iterator            = _concurrent_list_const_iterator<concurrent_list<_Ty, _Alloc>>;

	using reverse_iterator       = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
	concurrent_list()
		:_Size( 0 ), _First( nullptr )
	{
		_First = nullptr;
		_Last = nullptr;
	}

	concurrent_list( const _Alloc & _Al )
		:_Size( 0 )
	{
		_First = nullptr;
		_Last = nullptr;
	}

public:
	concurrent_list( _Ty && _Val )
		:_Size( 1 )
	{
		_First = _construct( std::move( _Val ) );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

	concurrent_list( _Ty && _Val, const _Alloc & _Al )
		:_Size( 1 )
		: _Allocator( _Al )
	{
		_First = _construct( std::move( _Val ) );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

public:
	concurrent_list( size_type _Count )
		:_Size( _Count )
	{
		_First = _construct_n( _Count );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

	concurrent_list( size_type _Count, const _Alloc & _Al )
		:_Size( _Count )
	{
		_First = _construct_n( _Count );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

public:
	concurrent_list( size_type _Count, const _Ty & _Val )
		:_Size( _Count )
	{
		_First = _construct_n( _Count, _Val );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

	concurrent_list( size_type _Count, const _Ty & _Val, const _Alloc & _Al )
		:_Size( _Count )
	{
		_First = _construct_n( _Count, _Val );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

public:
	concurrent_list( const concurrent_list & _Right )
		:_Size( _Right.size() )
	{
		_First = _construct_n( _Right.begin(), _Right.end() );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

	concurrent_list( const concurrent_list & _Right, const _Alloc & _Al )
		:_Size( _Right.size() )
	{
		_First = _construct_n( _Right.begin(), _Right.end() );

		if( _First.load()->Prev == nullptr )
		{
			_Last = _First.load()->Prev.load();

			_Last.load()->Next = nullptr;
		}

		_First.load()->Prev = nullptr;
	}

public:
	concurrent_list( concurrent_list && _Right )
		:_Size( _Right._Size ), _First( _Right._First ), _Last( _Right._Last )
	{
	}

	concurrent_list( concurrent_list && _Right, const _Alloc & _Al )
		:_Size( _Right._Size ), _First( _Right._First ), _Last( _Right._Last )
	{
	}

public:
	template <class _Iter> concurrent_list( _Iter _First, _Iter _Last )
		:_Size( 0 )
	{
		_First = _construct_n( _First, _Last, &_Size );

		_Last = _First.load()->Prev;
		_First.load()->Prev = nullptr;
		_Last.load()->Next = nullptr;
	}

	template <class _Iter> concurrent_list( _Iter _First, _Iter _Last, const _Alloc & _Al )
		:_Size( 0 )
	{
		_First = _construct_n( _First, _Last, &_Size );

		_Last = _First.load()->Prev;
		_First.load()->Prev = nullptr;
		_Last.load()->Next = nullptr;
	}

public:
	~concurrent_list()
	{
		clear();
	}

public:
	concurrent_list & operator=( concurrent_list && _Right )
	{
		clear();

		_Size = _Right._Size;
		_First = _Right._First;
		_Last = _Right._Last;
	}

	concurrent_list & operator=( const concurrent_list & _Right )
	{
		clear();

		_Size = _Right._Size;
		_First = _construct_n( _Right.begin(), _Right.end() );

		_Last = _First.load()->Prev;
		_First.load()->Prev = nullptr;
		_Last.load()->Next = nullptr;
	}

public:
	iterator begin()
	{
		return _First.load();
	}

	const_iterator begin() const
	{
		return _First.load();
	}

	iterator end()
	{
		return nullptr;
	}
	
	const_iterator end() const
	{
		return nullptr;
	}
	
	reverse_iterator rbegin()
	{
		return reverse_iterator( iterator( _Last.load() ) );
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator( const_iterator( _Last.load() ) );
	}

	reverse_iterator rend()
	{
		return reverse_iterator( iterator( _First.load() ) );
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator( const_iterator( _First.load() ) );
	}

	const_iterator cbegin() const
	{
		return begin();
	}

	const_iterator cend() const
	{
		return end();
	}

	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}

	const_reverse_iterator crend() const
	{
		return rend();
	}

public:
	size_type size() const
	{
		return _Size;
	}

	bool empty() const
	{
		return _Size == 0;
	}

	allocator_type get_allocator() const
	{
		return _Allocator;
	}

public:
	reference front()
	{
		return _First.load()->Value;
	}

	const_reference front() const
	{
		return _First.load()->Value;
	}

	reference back()
	{
		return _Last->Value;
	}

	const_reference back() const
	{
		return _Last->Value;
	}

public:
	void push_front( _Ty && _Val )
	{
		node_type * node = _construct( std::move( _Val ) );

		node_type * head = _First;
		do
		{
			node->Next = head;
		}
		while( !_First.compare_exchange_weak( head, node ) );

		head->Prev = node;
	}

	void push_front( const _Ty & _Val )
	{
		node_type * node = _construct( _Val );

		node_type * head = _First;
		do
		{
			node->Next = head;
		} while( !_First.compare_exchange_weak( head, node ) );

		head->Prev = node;
	}

	void pop_front()
	{
		node_type * first = _First;
		
		while( !_First.compare_exchange_weak( first, first->Next.load() ) );

		_First.load()->Prev = nullptr;

		_Allocator.destroy( first );
		_Allocator.deallocate( first, 1 );
	}

	void push_back( const _Ty & _Val )
	{
		node_type * node = _construct( _Val );
		node->Next = nullptr;

		node_type * last = _Last;

		do 
		{
			node->Prev = last;
		} while( !_Last.compare_exchange_weak( last, node ) );

		last->Next = node;
	}

	void pop_back()
	{
		node_type * last = _Last;

		while( !_Last.compare_exchange_weak( last, last->Prev.load() ) );

		_Allocator.destroy( last );
		_Allocator.deallocate( last, 1 );
	}

	iterator emplace_front( _Ty && _Val )
	{
		node_type * node = _construct( std::move( _Val ) );

		node_type * head = _First;
		do
		{
			node->Next = head;
		} while( !_First.compare_exchange_weak( head, node ) );

		head->Prev = node;

		return _First;
	}

	iterator emplace_back( _Ty && _Val )
	{
		node_type * node = _construct( std::move( _Val ) );
		node->Next = nullptr;

		node_type * last = _Last;

		do
		{
			node->Prev = last;
		} while( !_Last.compare_exchange_weak( last, node ) );

		last->Next = node;

		return _Last.load();
	}

public:
	iterator insert( const_iterator _Where, _Ty && _Val )
	{
		node_type * node = _construct( std::move( _Val ) );
		node_type * prev = _Where._node();
		node_type * next = prev->Next;
		node->Prev = prev;

		do 
		{
			node->Next = next;
		} while (_Where._node().Next.compare_exchange_weak(next, node));

		++_Size;

		return { node, this };
	}

	iterator insert( const_iterator _Where, const _Ty & _Val )
	{
		node_type * node = _construct( _Val );
		node_type * prev = _Where._node();
		node_type * next = prev->Next;
		node->Prev = prev;

		do
		{
			node->Next = next;
		} while( _Where._node().Next.compare_exchange_weak( next, node ) );

		++_Size;

		return { node, this };
	}

	iterator insert( const_iterator _Where, size_type _Count, const _Ty & _Val )
	{
		node_type * first = _construct_n( _Count, _Val );
		node_type * last = first->Prev;
		first->Prev = _Where._node();

		node_type * next = prev->Next;

		do
		{
			last->Next = next;
		} while( _Where._node().Next.compare_exchange_weak( next, last ) );

		size_type sz = _Size;
		while( !_Size.compare_exchange_weak( sz, sz + _Count ) );

		return { first, this };
	}

	template <class _Iter> iterator insert( const_iterator _Where, _Iter _First, _Iter _Last )
	{
		size_type _Count = 0;
		node_type * first = _construct_n( _Count, _Val, &_Count );
		node_type * last = first->Prev;
		first->Prev = _Where._node();

		node_type * next = prev->Next;

		do
		{
			last->Next = next;
		} while( _Where._node().Next.compare_exchange_weak( next, last ) );

		size_type sz = _Size;
		while( !_Size.compare_exchange_weak( sz, sz + _Count ) );

		return { first, this };
	}

public:
	iterator remove( const _Ty & _Val )
	{
		for( auto it = begin(); it != end(); ++it )
		{
			if( _Val == *it )
			{
				return erase( it );
			}
		}

		return end();
	}

	template <class _Pr1> iterator remove_if( _Pr1 _Pred )
	{
		for( auto it = begin(); it != end(); ++it )
		{
			if( _Pred( *it ) )
			{
				return erase( it );
			}
		}

		return end();
	}

public:
	void clear()
	{
		node_type * first = _First;
		while( !_First.compare_exchange_weak( first, nullptr ) );

		_Size = 0;
		_First = nullptr;
		_Last = nullptr;

		while( first )
		{
			node_type * next = first->Next;
			
			_Allocator.destroy( first );
			_Allocator.deallocate( first, 1 );

			first = next;
		}
	}

public:
	iterator erase( const_iterator _Where )
	{
		node_type * node = _Where._node();

		node_type * next = node->Next;
		
		node_type * prev = node->Prev;
		node_type * pnext = node;

		do
		{
			prev = pnext;
			pnext = node;
		}
		while( !prev->Next.compare_exchange_weak( pnext, next ) );

		next->Prev = prev;

		_Allocator.destroy( node );
		_Allocator.deallocate( node, 1 );

		return prev;
	}

private:
	node_type * _construct()
	{
		node_type * node = _Allocator.allocate( 1 );
		_Allocator.construct( node );

		return node;
	}

	node_type * _construct( value_type && val )
	{
		node_type * node = _Allocator.allocate( 1 );
		_Allocator.construct( node, std::move( val ), nullptr, nullptr );

		return node;
	}

	node_type * _construct( const value_type & val )
	{
		node_type * node = _Allocator.allocate( 1 );
		_Allocator.construct( node, val, nullptr, nullptr );

		return node;
	}

	node_type * _construct_n( size_type count )
	{
		if( count == 0 )
		{
			return nullptr;
		}

		node_type * node = nullptr;
		node_type * head = _Allocator.allocate( 1 );
		_Allocator.construct( head );

		node_type * prev = head;
		for( size_type i = 1; i < count; ++i )
		{
			node = _Allocator.allocate( 1 );
			_Allocator.construct( node );

			prev->Next = node;
			node->Prev = prev;
			prev = node;
		}

		head->Prev = node;

		return head;
	}

	node_type * _construct_n( size_type count, const value_type & val )
	{
		if( count == 0 )
		{
			return nullptr;
		}

		node_type * node = nullptr;
		node_type * head = _Allocator.allocate( 1 );
		_Allocator.construct( head, val, nullptr, nullptr );

		node_type * prev = head;
		for( size_type i = 1; i < count; ++i )
		{
			node = _Allocator.allocate( 1 );
			_Allocator.construct( node, val, nullptr, nullptr );

			prev->Next = node;
			node->Prev = prev;
			prev = node;
		}

		head->Prev = node;

		return head;
	}

	template<typename _Iter> node_type * _construct_n( _Iter _First, _Iter _Last, XE::uint64 * _Size = nullptr )
	{
		if( _First == _Last )
		{
			return nullptr;
		}

		node_type * node = nullptr;
		node_type * head = _Allocator.allocate( 1 );
		_Allocator.construct( head, *_First, nullptr, nullptr );
		++_First;
		if( _Size ) ++( *_Size );

		node_type * prev = head;
		for( ; _First != _Last; ++_First )
		{
			node_type * node = _Allocator.allocate( 1 );
			_Allocator.construct( node, *_First, nullptr, nullptr );

			prev->Next = node;
			node->Prev = prev;
			prev = node;

			if( _Size ) ++( *_Size );
		}

		head->Prev = node;

		return head;
	}

private:
	allocator_type _Allocator;
	std::atomic_size_t _Size;
	std::atomic<node_type *> _First;
	std::atomic<node_type *> _Last;
};

END_XE_NAMESPACE

#endif // CONCURRENT_LIST_HPP__54A2A6BA_6D14_4E6D_9661_A14BE186618B
