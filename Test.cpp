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

TEST_CASE("Test graph addition") {
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
    ariel::Graph g3 = g1 + g2;
    string result = g3.printGraph();
    CHECK(result == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    add_test_data("Test graph addition", graph, weightedGraph, result);
}

TEST_CASE("Test graph multiplication") {
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
    ariel::Graph g4 = g1 * g2;
    string result = g4.printGraph();
    CHECK(result == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
    add_test_data("Test graph multiplication", graph, weightedGraph, result);
}

TEST_CASE("Invalid operations") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
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

TEST_CASE("Test graph increment and decrement operators") {
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

TEST_CASE("Test graph multiplication operator") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 * g2;
    CHECK(g3.printGraph() == "[0, 0, 1]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Test graph addition operator") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);
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

TEST_CASE("Test graph subtraction operator") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);
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

TEST_CASE("Test graph multiplication by scalar") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    g1 *= -2;
    CHECK(g1.printGraph() == "[0, -2, 0]\n[-2, 0, -2]\n[0, -2, 0]");
    g1 /= -2;
    CHECK(g1.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Test graph unary operators") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
    ariel::Graph g3 = -g1;
    CHECK(g3.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
}

TEST_CASE("Test graph comparison operators") {
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
    CHECK(g1 == g1);
    CHECK(g1 != g2);
    CHECK(g1 < g2);
    CHECK(g1 <= g2);
    CHECK(g2 > g1);
    CHECK(g2 >= g1);
}

TEST_CASE("Test graph addition assignment operator") {
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
    g1 += g2;
    CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph subtraction assignment operator") {
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
    g1 -= g2;
    CHECK(g1.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");
}

TEST_CASE("Test graph equality operator") {
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
    CHECK(g1 == g1);
    CHECK_FALSE(g1 == g2);
}

TEST_CASE("Test graph inequality operator") {
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
    CHECK_FALSE(g1 != g1);
    CHECK(g1 != g2);
}

TEST_CASE("Test graph less than operator") {
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
    CHECK(g1 < g2);
    CHECK_FALSE(g2 < g1);
}

TEST_CASE("Test graph less than or equal to operator") {
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
    CHECK(g1 <= g2);
    CHECK_FALSE(g2 <= g1);
    CHECK(g1 <= g1);
}

TEST_CASE("Test graph greater than operator") {
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
    CHECK(g2 > g1);
    CHECK_FALSE(g1 > g2);
}

TEST_CASE("Test graph greater than or equal to operator") {
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
    CHECK(g2 >= g1);
    CHECK_FALSE(g1 >= g2);
    CHECK(g1 >= g1);
}

TEST_CASE("Test arithmetic operations after increment/decrement") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}
    };
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    
    ariel::Graph g3 = ++g1;
    ariel::Graph g4 = g3 + g2;
    string result = g4.printGraph();
    CHECK(result == "[0, 4, 1]\n[4, 0, 4]\n[1, 4, 0]");
    
    ariel::Graph g5 = g4--;
    ariel::Graph g6 = g5 - g2;
    result = g6.printGraph();
    CHECK(result == "[0, 2, 1]\n[2, 0, 2]\n[1, 2, 0]");
}
