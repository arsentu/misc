#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <iterator>

using std::vector;
using std::pair;
using std::make_pair;
using std::begin;
using std::end;
using std::cout;
using std::endl;

int solution(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D) {
    int m = A.size();
    int n = D.size();

    // convert input graph to adjency list
    vector<vector<pair<int, int> > > g(n); // graph in <vertex_i, <vertex_j, distance>>
    for (int i = 0; i < m; ++i) {
        int v1 = A[i];
        int v2 = B[i];
        int distance = C[i];
        g[v1].push_back(make_pair(v2, distance));
        g[v2].push_back(make_pair(v1, distance));
    }

    // record the current shortest path for each vertex
    vector<int> dists(n); // <vertex, distance>
    const int INFINITY = INT_MAX;
    for (int i = 0; i < n; ++i) {
        dists[i] = INFINITY;
    }

    // record if visited for each vertex
    vector<bool> visit(n, false);
    int visit_count = 0;

    // initialize
    dists[0] = 0;

    // iterate
    while (visit_count < n)
    {
        // get current neareast node and add to visit
        int min_dist = INFINITY;
        int min_vertex;
        for(int i = 0; i < n; ++i) {
            if (!visit[i] && dists[i] < min_dist) {
                min_dist = dists[i];
                min_vertex = i;
            }
        }
        if (min_dist == INFINITY) {
            break; // the left vertices are not reachable
        }
        visit[min_vertex] = true;
        ++visit_count;

        // found result and return
        if (min_dist <= D[min_vertex]) {
            //return min_dist;
        }

        // enumerate all its edges and adjust shortest path for other vertices
        for (size_t i = 0; i < g[min_vertex].size(); ++i) {
            int vertex_to = g[min_vertex][i].first;
            if (!visit[vertex_to] && min_dist + g[min_vertex][i].second < dists[vertex_to]) {
                dists[vertex_to] = min_dist + g[min_vertex][i].second;
            }
        }
    }

    // post process: none

    for (size_t i = 0; i < dists.size(); ++i) {
        cout << i << "\t" << dists[i] << endl;
    }

    return -1;
}

int main() {
    int a[] = {0, 1, 2};
    int b[] = {1, 2, 3};
    int c[] = {2, 3, 4};
    int d[] = {-1, 1, 3, 8};

    vector<int> A(begin(a), end(a));
    vector<int> B(begin(b), end(b));
    vector<int> C(begin(c), end(c));
    vector<int> D(begin(d), end(d));
/*
    vector<int> A(a, a + sizeof(a) / sizeof(a[0]));
    vector<int> B(b, b + sizeof(b) / sizeof(b[0]));
    vector<int> C(c, c + sizeof(c) / sizeof(c[0]));
    vector<int> D(d, d + sizeof(d) / sizeof(d[0]));
*/
    int result = solution(A, B, C, D);

    cout << result << endl;

    return 0;
}
