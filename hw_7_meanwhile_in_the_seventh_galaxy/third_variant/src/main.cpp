#include <iostream>
#include "graph.h"
#include "dfs.h"
#include "value_list.h"


int main () {
    using graph =
        Graph<
            Vertex<0, Edge<0, 1>>,
            Vertex<1, Edge<1, 2>, Edge<1, 5>>,
            Vertex<2, Edge<2, 3>, Edge<2, 0>>,
            Vertex<3, Edge<3, 4>>,
            Vertex<4, Edge<4, 1>>,
            Vertex<5, Edge<5, 4>>
        >;

    // 5 -> 4 -> 1 -> 2 -> 0
    /*
        1. Edges = TypeList<Edge<5, 4>>
        2. Edges = TypeList<Edge<4, 1>>
        3. Edges = TypeList<Edge<1, 2>, Edge<1, 5>>
        4. Edges = TypeList<Edge<1, 5>, Edge<2, 3>, Edge<2, 0>>
        5. Edges = TypeList<Edge<2, 3>, Edge<2, 0>>
        6. Edges = TypeList<Edge<2, 0>, Edge<3, 4>>
        7. Edges = TypeList<Edge<3, 4>, Edge<0, 1>>
        8. Edges = TypeList<Edge<0, 1>>
        9. Edges = NullType
    */
    static_assert(PathExists<graph, 5, 0>::value == true);

    using graph_1 =
        Graph<
            Vertex<0, Edge<0, 1>, Edge<0, 3>>,
            Vertex<1, Edge<1, 2>>,
            Vertex<2, Edge<2, 0>>,
            Vertex<3>,
            Vertex<4, Edge<4, 5>>,
            Vertex<5, Edge<5, 6>, Edge<5, 7>>,
            Vertex<6, Edge<6, 4>>,
            Vertex<7, Edge<7, 8>>,
            Vertex<8, Edge<8, 9>>,
            Vertex<9, Edge<9, 7>>,
            Vertex<10>,
            Vertex<11, Edge<11, 10>, Edge<11, 0>, Edge<11, 1>>
        >;

    static_assert(PathExists<graph_1, 0, 1>::value == true);
    static_assert(PathExists<graph_1, 1, 2>::value == true);
    static_assert(PathExists<graph_1, 2, 1>::value == true);

    static_assert(PathExists<graph_1, 1, 3>::value == true);
    static_assert(PathExists<graph_1, 3, 7>::value == false);
    static_assert(PathExists<graph_1, 3, 10>::value == false);

    static_assert(PathExists<graph_1, 6, 4>::value == true);
    static_assert(PathExists<graph_1, 6, 8>::value == true);
    static_assert(PathExists<graph_1, 8, 4>::value == false);

    static_assert(PathExists<graph_1, 10, 11>::value == false);
    static_assert(PathExists<graph_1, 11, 10>::value == true);
    static_assert(PathExists<graph_1, 11, 0>::value == true);
    static_assert(PathExists<graph_1, 11, 3>::value == true);

    static_assert(PathExists<graph_1, 0, 0>::value == true);
    static_assert(PathExists<graph_1, 3, 3>::value == true);

    using graph_2 =
        Graph<
            Vertex<0, Edge<0, 2>, Edge<0, 3>>,
            Vertex<1, Edge<1, 0>>,
            Vertex<2, Edge<2, 1>>,
            Vertex<3, Edge<3, 4>>,
            Vertex<4, Edge<4, 5>, Edge<4, 6>>,
            Vertex<5>,
            Vertex<6, Edge<6, 5>>
        >;

    static_assert(PathExists<graph_2, 0, 6>::value == true);

    return 0;
}
