// 题目：1203. 项目管理（Sort Items by Groups Respecting Dependencies）
// 思路：把约束拆成「组内项目依赖」与「组间依赖」两张图分别拓扑排序：先排出小组顺序，再按小组顺序对组内项目排序；任一张图成环即无解。
// 时间复杂度：O(n + m + E)，E 为 beforeItems 的总边数，两张图各扫一遍；空间复杂度：O(n + m + E)，需要存两张邻接表与度数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {  // n：项目总数；m：组数；group：项目到组的映射（-1 表示未分组）；beforeItems：每个项目的前置依赖
        int idx = m;  // 未分组项目要各自单独成组，新组号从 m 开始分配
        vector<vector<int>> groupItems(n + m);  // groupItems[g] 存放组 g 里的项目下标；最坏情况 n 个项目各成一組，故容量取 n + m
        vector<int> itemDegree(n);  // 项目级入度：itemDegree[i] 表示项目 i 还有多少个同组前置项目没排
        vector<int> groupDegree(n + m);  // 组级入度：groupDegree[g] 表示组 g 还有多少个前置组没排
        vector<vector<int>> itemGraph(n);  // 项目级邻接表：itemGraph[j] 里的 i 表示 i 必须排在 j 之后
        vector<vector<int>> groupGraph(n + m);  // 组级邻接表：groupGraph[gj] 里的 gi 表示组 gi 必须排在组 gj 之后
        for (int i = 0; i < n; ++i) {  // 第一遍扫描：给未分组项目分配组号，并收集每个组包含的项目
            if (group[i] == -1) {  // group[i] == -1 说明项目 i 没有归属任何组
                group[i] = idx++;  // 给它单独开一个新组，并把组号计数器递增
            }  // 未分组处理结束
            groupItems[group[i]].push_back(i);  // 把项目 i 记录到它所属组的列表中，供后续组内排序使用
        }  // 第一遍扫描结束
        for (int i = 0; i < n; ++i) {  // 第二遍扫描：遍历所有依赖关系，按同组 / 跨组分别建图
            for (int j : beforeItems[i]) {  // j 是项目 i 的前置项目，即 j 必须排在 i 之前
                if (group[i] == group[j]) {  // 两者同组：先后关系只能在组内解决，落到项目级图上
                    ++itemDegree[i];  // 项目 i 多了一个同组前置，入度加一
                    itemGraph[j].push_back(i);  // 建立有向边 j -> i，表示 j 排在 i 前面
                } else {  // 两者跨组：说明组 group[j] 必须整体排在组 group[i] 之前，落到组级图上
                    ++groupDegree[group[i]];  // 目标组 group[i] 的前置组数量加一
                    groupGraph[group[j]].push_back(group[i]);  // 建立组级有向边 group[j] -> group[i]
                }  // 同组 / 跨组分支结束
            }  // 内层依赖循环结束
        }  // 第二遍扫描结束
        vector<int> items(n + m);  // 统一编址：项目用 0..n-1，组用 n..n+m-1，这里先备好全部候选下标
        iota(items.begin(), items.end(), 0);  // 从 0 开始逐个递增填充，得到 0..n+m-1 的候选集合
        auto topoSort = [](vector<vector<int>>& graph, vector<int>& degree, vector<int>& items) -> vector<int> {  // 通用拓扑排序：只对 items 指定的这批结点排序，检测到环时返回空数组
            queue<int> q;  // BFS 队列，存放当前入度为 0 的待处理结点
            for (int& i : items) {  // 先在这批结点里挑出所有入度为 0 的起点
                if (degree[i] == 0) {  // 入度为 0 意味着没有未完成的前置约束，可以立即排序
                    q.push(i);  // 把起点入队
                }  // 入度判断结束
            }  // 起点收集结束
            vector<int> ans;  // 保存拓扑序结果
            while (!q.empty()) {  // 队列非空说明还剩可以处理的结点
                int i = q.front();  // 取队头作为当前要排的结点
                q.pop();  // 队头出队
                ans.push_back(i);  // 该结点的前置都已排完，直接放进答案
                for (int& j : graph[i]) {  // 遍历 i 的所有后继，解除它们对 i 的依赖
                    if (--degree[j] == 0) {  // 后继入度减一；降为 0 说明它的前置也全排完了
                        q.push(j);  // 后继可以入队等待排序
                    }  // 入度判断结束
                }  // 后继遍历结束
            }  // BFS 循环结束
            return ans.size() == items.size() ? ans : vector<int>();  // 排出的结点数等于这批结点数说明无环；否则存在环，返回空数组
        };  // topoSort 定义结束
        auto groupOrder = topoSort(groupGraph, groupDegree, items);  // 第一步：对组级图做拓扑排序，得到各组之间的相对顺序
        if (groupOrder.empty()) {  // 返回空说明组之间存在环，组间先后无法满足
            return vector<int>();  // 题目无解，返回空数组
        }  // 组级无解分支结束
        vector<int> ans;  // 最终的项目排列结果
        for (int& gi : groupOrder) {  // 按组级拓扑序依次处理每一组
            items = groupItems[gi];  // 取出本组要参与排序的项目下标集合
            auto itemOrder = topoSort(itemGraph, itemDegree, items);  // 第二步：在本组内部按项目级依赖做拓扑排序
            if (items.size() != itemOrder.size()) {  // 排出的项目数少于组内项目数，说明组内存在循环依赖
                return vector<int>();  // 题目无解，返回空数组
            }  // 组内无解分支结束
            ans.insert(ans.end(), itemOrder.begin(), itemOrder.end());  // 把本组的组内顺序整体拼到答案末尾
        }  // 逐组处理结束
        return ans;  // 返回满足全部依赖的项目顺序
    }  // sortItems 方法结束
};  // 题解类定义结束