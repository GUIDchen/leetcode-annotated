// 题目：1042. 不邻接植花（Flower Planting With No Adjacent）
// 思路：建无向邻接表后贪心染色，每个花园只看已染色的邻居用了哪些颜色，从 1..4 里挑第一个没用过的颜色。
// 时间复杂度：O(n + m)，m 为路径数（每个点度数不超过 3）；空间复杂度：O(n + m)，邻接表开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {  // n 是花园数（编号 1..n），paths 是相邻关系，返回每个花园种的花（1..4）
        vector<vector<int>> g(n);  // 邻接表，g[i] 存与花园 i 相邻的所有花园下标
        for (auto& p : paths) {  // 遍历每一条相邻关系
            int x = p[0] - 1, y = p[1] - 1;  // 把 1 基编号转成 0 基下标
            g[x].push_back(y);  // 记录 x 的邻居 y（有向存一份）
            g[y].push_back(x);  // 记录 y 的邻居 x（反向再存一份）
        }  // 建图结束
        vector<int> ans(n);  // 答案数组，ans[i] 是花园 i 种的花，初值 0 表示还没染色
        bool used[5];  // 颜色使用标记，下标 1..4 对应四种花
        for (int x = 0; x < n; ++x) {  // 按编号从小到大贪心染色，能保证每个点都有可选颜色
            memset(used, false, sizeof(used));  // 每一轮先清空使用标记（下标 0 只是占位）
            for (int y : g[x]) {  // 遍历当前花园的所有邻居
                used[ans[y]] = true;  // 把邻居已经用掉的颜色标记为不可用（未染色的邻居会把 used[0] 标上，无影响）
            }  // 邻居遍历结束
            for (int c = 1; c < 5; ++c) {  // 从 1 到 4 挑一个没被邻居占用的颜色
                if (!used[c]) {  // 该颜色可用
                    ans[x] = c;  // 给当前花园染上这个颜色
                    break;  // 选到即停，进入下一个花园
                }  // 颜色选择分支结束
            }  // 颜色枚举结束
        }  // 花园循环结束
        return ans;  // 返回所有花园的染色结果
    }  // 方法结束
};  // 类结束