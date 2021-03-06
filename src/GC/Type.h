/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04
#define __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04

#include <set>
#include <map>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "Base/Base.h"

BEG_XE_NAMESPACE

template< typename T >
using WeakPtr = std::weak_ptr<T>;
template< typename T >
using SharedPtr = std::shared_ptr<T>;

using String = XE::basic_string< XE::utf8_encode, std::pmr::polymorphic_allocator< XE::utf8_encode::storage_unit > >;
using AnsiString = XE::basic_string< XE::ansi_encode, std::pmr::polymorphic_allocator< XE::ansi_encode::storage_unit > >;
using WideString = XE::basic_string< XE::wide_encode, std::pmr::polymorphic_allocator< XE::wide_encode::storage_unit > >;
using UTF8String = XE::basic_string< XE::utf8_encode, std::pmr::polymorphic_allocator< XE::utf8_encode::storage_unit > >;

template< typename T >
using List = std::pmr::list<T>;
template< typename T >
using Deque = std::pmr::deque<T>;
template< typename T >
using Stack = std::stack<T, XE::Deque< T > >;
template< typename T >
using Queue = std::queue<T, XE::Deque< T > >;
template< typename T >
using Array = std::pmr::vector<T>;
template< typename K, typename V >
using Pair = std::pair<K, V>;
template< typename T >
using Set = std::pmr::set<T>;
template< typename K, typename V >
using Map = std::pmr::map<K, V>;
template< typename T >
using MultiSet = std::pmr::multiset<T>;
template< typename K, typename V >
using MultiMap = std::pmr::multimap<K, V>;
template< typename T >
using UnorderedSet = std::pmr::unordered_set<T>;
template< typename K, typename V >
using UnorderedMap = std::pmr::unordered_map<K, V>;
template< typename T >
using UnorderedMultiSet = std::pmr::unordered_multiset<T>;
template< typename K, typename V >
using UnorderedMultiMap = std::pmr::unordered_multimap<K, V>;

END_XE_NAMESPACE

#endif // __TYPE_H__6AF9B68A_CAEE_4C9A_88C7_E1903198CC04
