// 题目：2184. 建造坚实的砖墙的方法数（Number of Ways to Build Sturdy Brick Wall）
// 思路：先 DFS 枚举出所有宽度恰好为 width 的单行砖块排列，再筛掉「在同一列有砖缝」的相邻行对构成兼容图，最后按行做 DP 累加方案数。
// 时间复杂度：O(2^width + n^2 * width + height * n^2)，n 为单行合法排列数；空间复杂度：O(n^2 + height * n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> bricks;  // 可用的砖块长度（作为成员，方便 dfs 直接访问）
    int width;  // 墙的宽度（作为成员，方便 dfs 直接访问）
    int mod = 1e9 + 7;  // 取模常量，防止方案数溢出
    vector<vector<int>> res;  // 保存所有宽度恰好为 width 的单行砖块排列
    vector<int> t;  // DFS 过程中正在拼的当前行（存砖块长度序列）

    int buildWall(int height, int width, vector<int>& bricks) {  // height：砖墙高度；width：宽度；bricks：砖块长度集合
        this->width = width;  // 把宽度存到成员变量，供 dfs 使用
        this->bricks = bricks;  // 把砖块长度集合存到成员变量，供 dfs 使用
        dfs(0);  // 从已拼长度 0 开始，枚举出所有单行合法排列
        t.resize(0);  // 清空 DFS 临时数组（dfs 结束时它已经为空，这里只是显式复位）
        int n = res.size();  // 单行合法排列的总数
        vector<vector<int>> g(n);  // 兼容图：g[i] 存所有与第 i 种排列不共享砖缝、可以上下相邻的排列下标
        for (int i = 0; i < n; ++i) {  // 枚举每一对排列（含自身）
            if (check(res[i], res[i])) {  // 自己与自己比较，判断该行内部是否存在同列砖缝（首尾相接的砖缝）
                g[i].push_back(i);  // 自身兼容，说明同一排列可以上下堆叠
            }
            for (int j = i + 1; j < n; ++j) {  // 只需枚举 j > i，避免重复
                if (check(res[i], res[j])) {  // 两种排列没有公共砖缝，可以上下相邻
                    g[i].push_back(j);  // 记录 i 的下方可以是 j
                    g[j].push_back(i);  // 记录 j 的下方可以是 i（双向）
                }
            }
        }
        vector<vector<int>> dp(height, vector<int>(n));  // dp[i][j]：搭到第 i 行、且该行使用第 j 种排列的方案数
        for (int j = 0; j < n; ++j) dp[0][j] = 1;  // 第一行用任意一种排列都算 1 种方案
        for (int i = 1; i < height; ++i) {  // 逐行向上递推
            for (int j = 0; j < n; ++j) {  // 枚举当前行（第 i 行）使用的排列
                for (int k : g[j]) {  // 枚举与它兼容的上一行（第 i-1 行）排列
                    dp[i][j] += dp[i - 1][k];  // 累加上一行的方案数
                    dp[i][j] %= mod;  // 随时取模，避免溢出
                }
            }
        }
        int ans = 0;  // 最终答案
        for (int j = 0; j < n; ++j) {  // 累加最后一行用各种排列的方案数
            ans += dp[height - 1][j];  // 加上该排列作为顶行的方案数
            ans %= mod;  // 取模
        }
        return ans;  // 返回总方案数
    }

    bool check(vector<int>& a, vector<int>& b) {  // 判断两种排列 a、b 是否不存在同一列的砖缝（可上下相邻）
        int s1 = a[0], s2 = b[0];  // s1、s2 分别表示 a、b 中当前砖块的右端位置（前缀和）
        int i = 1, j = 1;  // i、j 表示 a、b 中下一块砖的下标
        while (i < a.size() && j < b.size()) {  // 两行都还没走到最后一块砖
            if (s1 == s2) return false;  // 砖缝落在同一列，冲突，不能相邻
            if (s1 < s2)  // a 的砖缝更靠左
                s1 += a[i++];  // 先推进 a 的右端到下一块砖，再比较
            else  // b 的砖缝更靠左
                s2 += b[j++];  // 先推进 b 的右端到下一块砖，再比较
        }
        return true;  // 中途没有出现同列砖缝，兼容
    }

    void dfs(int v) {  // v：当前这一行已经铺好的长度
        if (v > width) return;  // 超出墙宽，方案非法，回溯
        if (v == width) {  // 恰好铺满一整行
            res.push_back(t);  // 记录这条完整排列
            return;  // 结束本次递归
        }
        for (int x : bricks) {  // 尝试每一块可用的砖
            t.push_back(x);  // 把这块砖加入当前行
            dfs(v + x);  // 递归继续往右铺
            t.pop_back();  // 回溯：撤销这块砖，尝试下一个长度
        }
    }
};
