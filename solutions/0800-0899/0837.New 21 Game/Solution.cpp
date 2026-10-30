// 题目：837. 新 21 点（New 21 Game）
// 思路：记 f(i) 为当前分数 i 时最终不超过 n 的概率。i≥k 时停止，答案直接是 0/1；i=k-1 时抽一次必然停止，可用闭式公式；其余情况用前缀和递推 f(i)=f(i+1)+(f(i+1)-f(i+maxPts+1))/maxPts，并做记忆化。
// 时间复杂度：O(k)，每个分数状态只算一次；空间复杂度：O(k)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double new21Game(int n, int k, int maxPts) {  // n 为允许的最大得分，k 为停止阈值，maxPts 为每次可抽的最大点数；返回停止时得分不超过 n 的概率
        vector<double> f(k);  // 记忆化数组（长度 k）：f[i] 保存当前分数为 i 时的答案，值 0 同时兼作「尚未计算」
        auto dfs = [&](this auto&& dfs, int i) -> double {  // C++23 的显式对象参数：把 lambda 自身作为第一个参数传入，才能在内部递归调用自己
            if (i >= k) {  // 分数已经达到停止阈值 k
                return i <= n ? 1 : 0;  // 此时得分不超过 n 是成功事件，返回 1；否则返回 0
            }  // if 结束
            if (i == k - 1) {  // i == k-1 时再抽一次必然停止，可以不走递归直接算
                return min(n - k + 1, maxPts) * 1.0 / maxPts;  // 在 k..k+maxPts-1 上均匀取值，其中落在 ≤n 的比例就是答案
            }  // if 结束
            if (f[i]) {  // 命中记忆化结果（非 0）就直接返回，避免重复计算
                return f[i];  // 返回已缓存的值
            }  // if 结束
            return f[i] = dfs(i + 1) + (dfs(i + 1) - dfs(i + maxPts + 1)) / maxPts;  // 前缀和递推：f(i) = f(i+1) + (f(i+1) - f(i+maxPts+1)) / maxPts，同时写回记忆化数组
        };  // lambda 定义结束
        return dfs(0);  // 从初始分数 0 开始计算
    }  // 方法结束
};
