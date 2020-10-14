#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iterator>

std::pair<int, std::vector<int>> dfs(std::unordered_map<int, std::vector<int>>& graph,
                                      std::unordered_set<int>& used, std::vector<int>& now, int cur, int cnt)
{
    std::pair<int, std::vector<int>> ans = std::make_pair(0, std::vector<int>());

    for (int i = 0; i < graph[cur].size(); i++)
    {
        if (used.find(graph[cur][i]) == used.end())
        {
            used.insert(graph[cur][i]);
            ans.second.push_back(graph[cur][i]);

            auto res = std::move(dfs(graph, used, now, graph[cur][i], 1));
            ans.first += res.first;

            std::move(res.second.begin(), res.second.end(), std::back_inserter(ans.second));
        }
    }

    return ans;
}

int main()
{
    int n = 0, m = 0;
    std::scanf("%d%d", &n, &m);

    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_set<int> used;

    while (m--)
    {
        int f = 0, s = 0;
        std::scanf("%d%d", &f, &s), f--, s--;
        graph[f].push_back(s);
    }

    std::vector<std::pair<int, std::vector>> ans;

    for (int i = 0; i < n; i++)
        if (used.find(i) != used.end())
            ans.push_back(std::move(dfs(graph, used, std::unordered_set(std::initializer_list<int>(i)), i, 1)));

    std::printf("%llu\n", ans.size());

    for (auto i : ans)
    {
        std::printf("%d\n", i.first);

        for (int q : i.second)
            std::printf("%d ", q);

        std::puts("");
    }

    return 0;
}
