// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>

using namespace std;

struct TestData {
    string name;
    vector<vector<int>> input1;
    vector<vector<int>> input2;
    string output;
};

vector<TestData> test_data;

void add_test_data(const string &name, const vector<vector<int>> &input1, const vector<vector<int>> &input2, const string &output) {
    test_data.push_back({name, input1, input2, output});
}

void check_duplicate_tests() {
    for (size_t i = 0; i < test_data.size(); ++i) {
        for (size_t j = i + 1; j < test_data.size(); ++j) {
            if (test_data[i].input1 == test_data[j].input1 && test_data[i].input2 == test_data[j].input2 && test_data[i].output == test_data[j].output) {
                cout << "Duplicate found: " << test_data[i].name << " and " << test_data[j].name << endl;
            }
        }
    }
}

TEST_CASE("Check for duplicate tests") {
    check_duplicate_tests();
}

TEST_CASE("Graph operations") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    SUBCASE("Addition") {
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g2.loadGraph(weightedGraph);
        ariel::Graph g3 = g1 + g2;
        string result = g3.printGraph();
        CHECK(result == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
        add_test_data("Test graph addition", graph, weightedGraph, result);
    }

    SUBCASE("Multiplication") {
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}
        };
        g2.loadGraph(weightedGraph);
        ariel::Graph g4 = g1 * g2;
        string result = g4.printGraph();
        CHECK(result == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
        add_test_data("Test graph multiplication", graph, weightedGraph, result);
    }

    SUBCASE("Invalid operations") {
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1, 1},
            {1, 0, 2, 1},
            {1, 2, 0, 1}
        };
        g2.loadGraph(weightedGraph);
        ariel::Graph g5;
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}
        };
        g5.loadGraph(graph2);
        CHECK_THROWS(g5 * g1);
        CHECK_THROWS(g1 * g2);
        add_test_data("Invalid operations", graph, weightedGraph, "");

        // Addition of two graphs with different dimensions
        ariel::Graph g6;
        vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}
        };
        g6.loadGraph(graph3);
        CHECK_THROWS(g1 + g6);
        add_test_data("Invalid operations", graph, graph3, "");
    }
}

TEST_CASE("Graph increment and decrement operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2 = g1++;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    ariel::Graph g3 = ++g1;
    CHECK(g1.printGraph() == "[0, 3, 2]\n[3, 0, 3]\n[2, 3, 0]");
    CHECK(g3.printGraph() == "[0, 3, 2]\n[3, 0, 3]\n[2, 3, 0]");
    ariel::Graph g4 = g1--;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");
    CHECK(g4.printGraph() == "[0, 3, 2]\n[3, 0, 3]\n[2, 3, 0]");
    ariel::Graph g5 = --g1;
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    CHECK(g5.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Graph arithmetic operators") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    SUBCASE("Addition") {
        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
        };
        g2.loadGraph(graph2);
        ariel::Graph g3 = g1 + g2;
        CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");
    }

    SUBCASE("Subtraction") {
        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
        };
        g2.loadGraph(graph2);
        ariel::Graph g3 = g1 - g2;
        CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, 0]\n[-1, 0, 0]");
    }

    SUBCASE("Multiplication by scalar") {
        g1 *= -2;
        CHECK(g1.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
        g1 /= -2;
        CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    }
}

TEST_CASE("Graph unary operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    SUBCASE("Unary plus") {
        ariel::Graph g2 = +g1;
        CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    }

    SUBCASE("Unary minus") {
        ariel::Graph g3 = -g1;
        CHECK(g3.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
    }
}

TEST_CASE("Graph comparison operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    SUBCASE("Equality") {
        CHECK(g1 == g1);
        CHECK_FALSE(g1 == g2);
    }

    SUBCASE("Inequality") {
        CHECK_FALSE(g1 != g1);
        CHECK(g1 != g2);
    }

    SUBCASE("Less than") {
        CHECK(g1 < g2);
        CHECK_FALSE(g2 < g1);
    }

    SUBCASE("Less than or equal to") {
        CHECK(g1 <= g2);
        CHECK_FALSE(g2 <= g1);
        CHECK(g1 <= g1);
    }

    SUBCASE("Greater than") {
        CHECK(g2 > g1);
        CHECK_FALSE(g1 > g2);
    }

    SUBCASE("Greater than or equal to") {
        CHECK(g2 >= g1);
        CHECK_FALSE(g1 >= g2);
        CHECK(g1 >= g1);
    }
}

TEST_CASE("Graph assignment operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    SUBCASE("Addition assignment") {
        g1 += g2;
        CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    }

    SUBCASE("Subtraction assignment") {
        g1 -= g2;
        CHECK(g1.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");
    }
}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    SUBCASE("Graph with three nodes and two edges forming a cycle") {
       vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }
           
    SUBCASE("Graph with one node") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Graph with two unconnected nodes") {
        vector<vector<int>> graph = {
            {0, 0},
            {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }

    SUBCASE("Connected graph") {
        vector<vector<int>> graph = {
            {0, 1},
            {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
    }

    SUBCASE("Disconnected graph") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
    }
   
    SUBCASE("Directed graph with two nodes and one edge") {
        vector<vector<int>> graph = {
            {0, 1},
            {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false); // The graph is not connected because there's no path from node 1 to node 0
     }

    SUBCASE("Undirected graph with two nodes and one edge") {
        vector<vector<int>> graph = {
            {0, 1},
            {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true); // The graph is connected because there's a path between every pair of nodes
    }

    SUBCASE("Directed graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 1},
            {0, 0, 1},
            {1, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true); // The graph is connected because there's a path between every pair of nodes
    }

    SUBCASE("Directed graph with three nodes and two edges not forming a cycle") {
         vector<vector<int>> graph = {
            {0, 1, 0},
            {0, 0, 1},
            {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false); // The graph is not connected because there's no path from node 2 to node 0 or node 1
    }
   
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    SUBCASE("Graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }
   
    SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
    }
   
    SUBCASE("Empty graph") {
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 1));
    }
   
    SUBCASE("Single node graph") {
        vector<vector<int>> graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 0) == "0");
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 1));
    }

    SUBCASE("Two nodes with no edge") {
        vector<vector<int>> graph = {{0, 0}, {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "-1");
    }

    SUBCASE("Two nodes with an edge") {
        vector<vector<int>> graph = {{0, 1}, {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->1");
    }

    SUBCASE("Three nodes in a line") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
    }

    SUBCASE("Three nodes in a cycle") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->2");
    }

    SUBCASE("Test shortestPath with negative edge but no negative cycle") {
        vector<vector<int>> graph = {
            {0, -1, 0, 0, 0},
            {-1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");
    }
    
    SUBCASE("Test shortestPath with negative edge but no negative cycle and directed graph") {
        vector<vector<int>> graph = {
            {0, -1, 0, 0, 0},
            {0, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");
    }
    
    SUBCASE("Test shortestPath with negative cycle") {
        vector<vector<int>> graph = {
            {0, 1, -1, 0, 0},
            {1, 0, -3, 0, 0},
            {-1, -3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 4));
    }
    
    SUBCASE("Test shortestPath with negative cycle and directed graph") {
        vector<vector<int>> graph = {
            {0, 1, -1, 0, 0},
            {0, 0, -3, 0, 0},
            {-1, -3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 4));
    }
    
    SUBCASE("Test shortestPath with disconnected graph") {
        vector<vector<int>> graph = {
            {0, 1, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "-1");
    }
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph;

    SUBCASE("Test with a graph that contains a cycle of length 3") {
        graph = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
    }

    SUBCASE("Test with a graph that is not bipartite") {
        graph = {{0, 1, 1, 0, 0}, {1, 0, 1, 0, 0}, {1, 1, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "0");
    }

    SUBCASE("Test with a graph that is bipartite and contains weights") {
        graph = {{0, 1, 0, 0, 0}, {1, 0, 3, 0, 0}, {0, 3, 0, 4, 0}, {0, 0, 4, 0, 5}, {0, 0, 0, 5, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
    }

    SUBCASE("Test with an empty graph") {
      CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }

    SUBCASE("Test with a graph that only contains one node") {
        graph = {{0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}");
    }

    SUBCASE("Test with a graph that contains a cycle of length 2 and contains two nodes and one edge") {
        graph = {{0, 1}, {1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");
    }

    SUBCASE("Test with a graph that contains two nodes but no edges") {
        graph = {{0, 0}, {0, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={1}");
    }

    SUBCASE("Test with a graph that contains multiple disconnected components") {
        graph = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
    }
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;

    SUBCASE("Graph with three nodes and two edges forming a cycle") {
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    }

    SUBCASE("Graph with five nodes and a disconnected component") {
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isContainsCycle(g) == true);
    }

    SUBCASE("Graph with no edges") {
        vector<vector<int>> graph = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a single edge") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a self-loop") {
        vector<vector<int>> graph = {{0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with a cycle") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with no cycle") {
        vector<vector<int>> graph = {{0, 1, 0}, {1, 0, 0}, {0, 0, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with multiple cycles") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Graph with multiple cycles and self-loops") {
        vector<vector<int>> graph = {{0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }
    
    SUBCASE("Weighted graph with a cycle") {
        vector<vector<int>> graph = {{0, 1, 2}, {1, 0, 3}, {2, 3, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with no cycle") {
        vector<vector<int>> graph = {{0, 1, 0}, {1, 0, 2}, {0, 2, 0}};
        g.loadGraph(graph);
        CHECK_FALSE(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with multiple cycles") {
        vector<vector<int>> graph = {{0, 2, 3}, {2, 0, 1}, {3, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

    SUBCASE("Weighted graph with multiple cycles and self-loops") {
        vector<vector<int>> graph = {{1, 2, 3}, {2, 1, 4}, {3, 4, 1}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g));
    }

}

TEST_CASE("Test negativeCycle")
{
    ariel::Graph g;

    SUBCASE("Graph with no edges") {
        vector<vector<int>> graph = {
            {0, 0, 0}, 
            {0, 0, 0},
             {0, 0, 0}
             };
        g.loadGraph(graph);   
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNo negative cycle detected in directed graph.");
    }

    SUBCASE("Graph with positive weights") {
        vector<vector<int>> graph = {
            {0, 1, 2}, 
            {1, 0, 3}, 
            {2, 3, 0}
            };
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNo negative cycle detected in directed graph.");
    }

    SUBCASE("Graph with negative weights but no negative cycle") {
        vector<vector<int>> graph = {
            {0, -1, 2},
             {-1, 0, 3},
              {2, 3, 0}
              };
        g.loadGraph(graph);
        // the graph is not connected, so there is no negative cycle
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    }

    SUBCASE("Graph with a negative cycle 1") {
        vector<vector<int>> graph = {
            {0, -1, 2}, 
            {-1, 0, -3}, 
            {2, -3, 0}
            };
        g.loadGraph(graph);     
        CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    }

    SUBCASE("Graph with a negative cycle 2") {
        vector<vector<int>> graph = {
            {0, 1, 2}, 
            {1, 0, -3},
            {2, -3, 0}};
        g.loadGraph(graph);        
        CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
    }

    SUBCASE("Graph with a negative cycle 3") {
            vector<vector<int>> graph = {
                {0, 1,-3}, 
                {1, 0, 2},
                {-3, 2, 0}};
            g.loadGraph(graph);        
            CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle detected in undirected graph.\nNegative cycle detected in directed graph.");
        }

}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    
    SUBCASE("Empty graph1") {
        vector<vector<int>> graph = {{}};
      CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }
  
    SUBCASE("Empty graph2") {
        vector<vector<int>> graph;
           CHECK_THROWS_WITH(g.loadGraph(graph), "Graph is empty");
    }
   
    SUBCASE("Empty graph3") {
    CHECK_THROWS_WITH(ariel::Algorithms::isConnected(g), "The graph is empty");
    }

}

