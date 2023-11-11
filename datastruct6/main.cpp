#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 使用邻接表表示图的节点
template <typename T>
struct GraphNode {
    T value;
    vector<GraphNode*> neighbors;
    bool visited;
    GraphNode(T val) : value(val), visited(false) {}
};

// 图类模板
template <typename T>
class Graph {

public:
    // 添加节点
    void addNode(T value) {
        nodes.push_back(new GraphNode<T>(value));
    }

    // 添加边
    void addEdge(int from, int to) {
        nodes[from]->neighbors.push_back(nodes[to]);
        nodes[to]->neighbors.push_back(nodes[from]); // 无向图需要双向连接
    }

    // 深度优先搜索
    void DFS(GraphNode<T>* node) {
        if (node == nullptr) return;
        node->visited = true;
        cout << node->value << " ";
        for (auto neighbor : node->neighbors) {
            if (!neighbor->visited) {
                DFS(neighbor);
            }
        }
    }

    // 广度优先搜索
    void BFS(GraphNode<T>* node) {
        if (node == nullptr) return;
        queue<GraphNode<T>*> q;
        q.push(node);
        node->visited = true;
        while (!q.empty()) {
            GraphNode<T>* current = q.front();
            q.pop();
            cout << current->value << " ";
            for (auto neighbor : current->neighbors) {
                if (!neighbor->visited) {
                    neighbor->visited = true;
                    q.push(neighbor);
                }
            }
        }
    }

    vector<GraphNode<T>*> nodes;
};

int main() {
    Graph<int> graph; // 创建一个存储整数类型节点值的图

    // 添加至少7个顶点
    for (int i = 0; i < 7; i++) {
        graph.addNode(i);
    }

    // 添加至少11条边
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);
    graph.addEdge(4, 6);
    graph.addEdge(5, 6);
    graph.addEdge(1, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    // 深度优先遍历
    cout << "Depth First Traversal: ";
    graph.DFS(graph.nodes[0]);
    cout << endl;

    // 重置节点的访问状态
    for (auto node : graph.nodes) {
        node->visited = false;
    }

    // 广度优先遍历
    cout << "Breadth First Traversal: ";
    graph.BFS(graph.nodes[0]);
    cout << endl;

    return 0;
}
