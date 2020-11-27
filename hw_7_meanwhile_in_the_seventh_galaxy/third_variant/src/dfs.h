#ifndef MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H
#define MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H

#include "graph.h"
#include "type_list.h"
#include "value_list.h"

// Visited:
template <size_t size>
struct Visited : Construct<false, size> {};

// ConcatIf:
template <bool Cond, typename T, typename U>
struct ConcatIf {
  using type = T;
};

template <typename... U>
struct ConcatIf<false, NullType, TypeList<U...>> {
  using type = TypeList<U...>;
};

template <typename... T, typename... U>
struct ConcatIf<false, TypeList<T...>, TypeList<U...>> {
  using type = TypeList<T..., U...>;
};

// DFS:
template <size_t, typename...>
struct DFS {};

template <size_t from, typename Graph, typename Visited, typename... Edge>
struct DFS<from, Graph, Visited, TypeList<Edge...>> {
 private:
  using updated_visited = typename Set<from, true, Visited>::type;
  using updated_edges = typename ConcatIf<
      Get<TypeList<Edge...>::Head::to, Visited>::value,
      typename TypeList<Edge...>::Tail,
      typename TypeAt<TypeList<Edge...>::Head::to,
                      typename Graph::Vertices>::type::Edges>::type;

 public:
  using visited = typename DFS<TypeList<Edge...>::Head::to, Graph,
                               updated_visited, updated_edges>::visited;
};

template <size_t from, typename Graph, typename Visited>
struct DFS<from, Graph, Visited, NullType> {
  using visited = typename Set<from, true, Visited>::type;
};

// PathExists:
template <typename Graph, size_t start, size_t end>
struct PathExists {
 private:
  using initial_visited =
      typename Visited<Length<typename Graph::Vertices>::value>::type;

 public:
  using visited = typename DFS<
      start, Graph, initial_visited,
      typename TypeAt<start, typename Graph::Vertices>::type::Edges>::visited;
  static constexpr bool value = (start == end) || Get<end, visited>::value;
};

#endif  /// MEANWHILE_IN_THE_SEVENTH_GALAXY_THIRD_VARIANT_DFS_H.
