// 3669. Balanced K-Factor Decomposition（K 因数分解）
// 核心思路：先预处理每个数的全部因子，再用回溯枚举 n 的 k 个因子的所有分解，取极差（最大值减最小值）最小的一组。
// 复杂度：预处理 O(MX log MX)，单次回溯枚举因子组合（最坏指数级），空间 O(MX log MX)。
class Solution {  // 定义 Solution 类
public:
    static const int MX = 100001;  // 预处理上界：10^5 + 1
    static vector<vector<int>> g;  // g[x] 存储 x 的所有因子（静态成员，全局共享）

    vector<int> ans;  // 记录当前最优的分解结果
    vector<int> path;  // 记录回溯过程中正在构造的分解
    int cur;  // 记录当前最优的极差（最大值减最小值）

    vector<int> minDifference(int n, int k) {  // 把 n 分解成 k 个因子，使极差最小
        if (g.empty()) {  // 因子表为空说明是首次调用，需要做预处理
            g.resize(MX);  // 把因子表大小开到 MX
            for (int i = 1; i < MX; i++) {  // 枚举每一个可能的因子 i
                for (int j = i; j < MX; j += i) {  // 枚举 i 的所有倍数 j
                    g[j].push_back(i);  // i 是 j 的因子，加入 g[j]
                }
            }
        }  // 因子预处理完成

        cur = INT_MAX;  // 最优极差初始化为无穷大
        ans.clear();  // 清空答案（静态成员需在多组测试之间重置）
        path.assign(k, 0);  // path 分配 k 个位置并初始化为 0

        dfs(k - 1, n, INT_MAX, 0);  // 从第 k-1 位开始，在 n 上做因子分解
        return ans;  // 返回最优分解结果
    }

private:  // 以下为私有的回溯辅助函数
    void dfs(int i, int x, int mi, int mx) {  // i 为待填位置，x 为剩余待分解的数，mi/mx 为已选因子的最小/最大值
        if (i == 0) {  // 已经填到第 0 位，剩余的 x 就是最后一个因子
            int d = max(mx, x) - min(mi, x);  // 计算当前 k 个因子分解的极差
            if (d < cur) {  // 发现更小的极差
                cur = d;  // 更新最优极差
                path[i] = x;  // 把最后一个因子写入 path
                ans = path;  // 保存当前最优分解
            }
            return;  // 回溯，返回上一层继续枚举
        }
        for (int y : g[x]) {  // 枚举剩余部分 x 的每个因子 y
            path[i] = y;  // 把因子 y 放在第 i 位
            dfs(i - 1, x / y, min(mi, y), max(mx, y));  // 继续分解 x / y，并更新已选因子的最小值和最大值
        }
    }
};

vector<vector<int>> Solution::g;  // 静态成员变量的类外定义
