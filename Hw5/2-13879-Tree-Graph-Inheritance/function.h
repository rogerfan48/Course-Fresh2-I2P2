#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <limits>

using std::pair;
using std::vector;
using std::numeric_limits;

class graph {
    protected:
        int n;

    private:
        vector<vector<int>> adjacent_lists;

    public:
        graph(int _n, vector<pair<int, int>> edges) : n(_n), adjacent_lists(_n) {
            for (auto [a, b] : edges) {
                adjacent_lists[a].push_back(b);
                adjacent_lists[b].push_back(a);
            }
        }
        vector<int> bfs(int) const; // Perform BFS traversal on a graph.
};

class tree : public graph {
    public:
        tree(int n, vector<pair<int, int> > edges) : graph(n, edges) {}
        int diameter() const; // Find the diameter by BFS traversal.
};

#endif // FUNCTION_H

////////////////////////////////////////////////////////////////////////////////
//                              Separate Line!!!                              //
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * It's recommended that you should implement the 3 member functions in a different file.
 *
 * If you edit `function.h` directly, don't paste the codes above.
 *
 */

// Starter codes are provided below. Uncomment them and begin coding!

/**

vector<int> graph::bfs(int source) const
{
    // TODO: Perform BFS traversal on a graph.
}

int tree::diameter() const
{
    // TODO: Find the diameter by BFS traversal.
}

 */
