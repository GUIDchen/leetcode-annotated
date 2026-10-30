// 3532. 针对图的路径存在性查询 I / Path Existence Queries in a Graph I
// 核心思路：数组已非递减，相邻差大于 maxDiff 处必须断开；扫描一遍给每个下标打上连通块编号，查询只需比较两端编号是否相同。
// 复杂度：时间 O(n + q)，空间 O(n)（不计返回值）。
class Solution {  // 定义题解类
public:  // 公有方法区
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {  // 回答：u 与 v 之间是否存在路径（即是否属于同一连通块）
        vector<int> g(n);  // g[i]：下标 i 所属的连通块编号
        int cnt = 0;  // cnt：当前连通块编号，初始为第 0 块
        for (int i = 1; i < n; ++i) {  // 从第二个元素开始扫描，与左邻居比较
            if (nums[i] - nums[i - 1] > maxDiff) {  // 相邻差超过 maxDiff，说明这两点之间没有边
                ++cnt;  // 断开，连通块编号加一
            }  // if 语句结束
            g[i] = cnt;  // 记录下标 i 所属的连通块编号
        }  // 循环结束

        vector<bool> ans;  // 存放每个查询的布尔答案
        for (const auto& q : queries) {  // 逐个处理查询
            int u = q[0], v = q[1];  // 取出查询的两个下标
            ans.push_back(g[u] == g[v]);  // 连通块编号相同即存在路径
        }  // 循环结束
        return ans;  // 返回全部查询的答案
    }  // 方法结束
};  // 类定义结束