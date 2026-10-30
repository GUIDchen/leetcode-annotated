// 题目：746. 使用最小花费爬楼梯（Min Cost Climbing Stairs）
// 核心思路：记忆化搜索，dfs(i) = cost[i] + min(dfs(i + 1), dfs(i + 2))，越过楼顶（i >= n）返回 0，答案取 dfs(0) 与 dfs(1) 的较小值。
// 时间复杂度：O(n)，每个状态只计算一次；空间复杂度：O(n)，memo 数组加 O(n) 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCostClimbingStairs(vector<int>& cost) {  // cost[i] 是踩上第 i 阶需要支付的费用
        int n = cost.size();  // 台阶数量，也是记忆化数组的长度
        int f[n];  // memo 数组：f[i] 记录从第 i 阶出发到楼顶的最小花费
        memset(f, -1, sizeof(f));  // 整体初始化为 -1，表示该状态还没算过（费用非负，-1 可安全作哨兵）
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 递归 lambda：this auto&& 让 lambda 把自己当成第一个实参，从而能自我调用
            if (i >= n) {  // 走到 n 或 n + 1 时已经越过楼顶
                return 0;  // 越界不再产生费用，作为递归的终止条件
            }  // 结束终止条件判断
            if (f[i] < 0) {  // 只有还没算过才真正递归，避免重复搜索
                f[i] = cost[i] + min(dfs(i + 1), dfs(i + 2));  // 踩当前阶付 cost[i]，再在走一阶与走两阶中选更省的一条
            }  // 结束记忆化计算
            return f[i];  // 返回该状态的结果（可能来自记忆化）
        };  // 结束 lambda 定义
        return min(dfs(0), dfs(1));  // 起点可以是第 0 阶或第 1 阶，取两种起步方式中花费更小的
    }  // 结束 minCostClimbingStairs 方法
};  // 结束 Solution 类
