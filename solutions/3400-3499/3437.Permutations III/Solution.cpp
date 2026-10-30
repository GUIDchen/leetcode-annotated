// 3437. 全排列 III / Permutations III
// 核心思路：DFS 回溯枚举 1..n 的排列，仅当相邻元素奇偶性不同时才可相邻（首个位置不限制），vis 标记已用数字。
// 复杂度：时间 O(n * n!)，空间 O(n)（不计结果存储）。
class Solution {  // 定义题解类
public:  // 公有方法
    vector<vector<int>> permute(int n) {  // 返回 1..n 中相邻元素奇偶交替的全部排列
        vector<vector<int>> ans;  // 结果集合
        vector<bool> vis(n + 1);  // vis[x] 表示数字 x 是否已被使用
        vector<int> t;  // 当前正在构造的排列
        auto dfs = [&](this auto&& dfs, int i) -> void {  // 递归回溯：i 为当前已填位置数
            if (i >= n) {  // 已填满 n 个位置
                ans.push_back(t);  // 记录一个完整排列
                return;  // 结束本层递归
            }  // 结束终止分支
            for (int j = 1; j <= n; ++j) {  // 枚举下一个可放的数字
                if (!vis[j] && (i == 0 || t[i - 1] % 2 != j % 2)) {  // 未被使用，且与上一个数字奇偶性不同
                    vis[j] = true;  // 标记数字 j 已使用
                    t.push_back(j);  // 把 j 加入当前排列
                    dfs(i + 1);  // 递归填下一个位置
                    t.pop_back();  // 回溯：弹出 j
                    vis[j] = false;  // 回溯：取消使用标记
                }  // 结束本候选分支
            }  // 结束候选枚举
        };  // 结束 lambda 定义
        dfs(0);  // 从第 0 个位置开始搜索
        return ans;  // 返回全部合法排列
    }  // 结束 permute 方法
};  // 结束 Solution 类
