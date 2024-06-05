#include <iostream>
#include <algorithm> // Для функции std::min
using namespace std;

const int MAX_E = (int)1e6;
const int MAX_V = (int)1e3;
const int INF = (int)1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
    // Прямая ребро
    onEnd[edgeCount] = v;                   // конец ребра v
    nextEdge[edgeCount] = firstEdge[u];     // добавить в начало списка для u
    firstEdge[u] = edgeCount;               // теперь начало списка - новое ребро
    capacity[edgeCount++] = cap;            // установить пропускную способность
    // Обратная ребро
    onEnd[edgeCount] = u;                   // та же процедура, что и с прямым ребром
    nextEdge[edgeCount] = firstEdge[v];
    firstEdge[v] = edgeCount;
    capacity[edgeCount++] = 0;
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // вернуть результирующий минимум на пути
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // ищем поток в поддереве
            if (minResult > 0) {                    // если нашли
                capacity[edge] -= minResult;   // на прямых ребрах вычитаем поток
                capacity[edge ^ 1] += minResult;   // добавляем на обратных
                return minResult;
            }
        }
    }
    return 0; // если не нашли поток из этой вершины, возвращаем 0
}

int main() {
    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 означает, что нет ребра
    cin >> numOfVertex >> numOfEdge;            // читаем количество вершин и ребер
    cin >> sourceVertex >> destinationVertex;   // читаем источник и сток
    for (int i = 0, u, v, cap; i < numOfEdge; i++) {
        cin >> u >> v >> cap;
        addEdge(u, v, cap);
    }
    // Поиск максимального потока
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    cout << maxFlow << endl;
    return 0;
}