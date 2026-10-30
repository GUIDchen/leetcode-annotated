// 题目：526. 优美的排列（Beautiful Arrangement）
// 思路：DFS 回溯，为位置 1..n 依次选数，选中的数必须能被位置整除或整除位置；预处理可选集合剪枝。
// 时间复杂度：O(n!)，最坏枚举全部排列（剪枝后远小于此）；空间复杂度：O(n²)，match 表与访问数组。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员区
    int n;  // 成员 n：题目规模，存下来供 dfs 递归使用
    int ans;  // 成员 ans：合法排列的计数器
    vector<bool> vis;  // 成员 vis：记录某个数字是否已经被使用
    unordered_map<int, vector<int>> match;  // 成员 match：match[i] 存放可以放在位置 i 上的所有数字

    int countArrangement(int n) {  // 主函数：统计 1..n 的优美排列个数
        this->n = n;  // 把参数 n 保存到成员变量，避免递归时层层传递
        this->ans = 0;  // 计数器清零，保证多次调用互不影响
        vis.resize(n + 1);  // 访问数组开到 n+1，下标 1..n 对应数字 1..n
        for (int i = 1; i <= n; ++i)  // 预处理：枚举每个位置 i
            for (int j = 1; j <= n; ++j)  // 枚举可能放在该位置的数值 j
                if (i % j == 0 || j % i == 0)  // 满足「i 是 j 的倍数」或「j 是 i 的倍数」之一即符合优美条件
                    match[i].push_back(j);  // 把 j 收进位置 i 的候选集合
        dfs(1);  // 从位置 1 开始深度优先搜索
        return ans;  // 返回合法排列总数
    }  // 主函数结束

    void dfs(int i) {  // 深度优先搜索：为位置 i 选择一个还没用过的数字
        if (i == n + 1) {  // i 走到 n+1 说明 1..n 已经全部放好，得到一种合法排列
            ++ans;  // 方案数加一
            return;  // 返回上一层，继续尝试其它数字
        }  // if 结束
        for (int j : match[i]) {  // 遍历位置 i 的所有合法候选数字
            if (!vis[j]) {  // 只尝试还没被使用的数字
                vis[j] = true;  // 标记 j 已被使用
                dfs(i + 1);  // 递归处理下一个位置
                vis[j] = false;  // 回溯：撤销标记，恢复现场供其它分支使用
            }  // if 结束
        }  // for 结束
    }  // dfs 结束
};  // 类定义结束