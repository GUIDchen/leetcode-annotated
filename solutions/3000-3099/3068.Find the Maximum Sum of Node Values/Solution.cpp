// 题目：3068. 最大节点价值之和（Find the Maximum Sum of Node Values）
// 核心思路：每一次边操作等价于「同时翻转边两端节点的标记」，标记可由边在树上任意传导，所以真正受限的只是被翻转节点个数的奇偶性；用 DP 记录已翻转个数为偶数/奇数时的最大价值之和。
// 时间复杂度：O(n)，只线性扫描一遍节点；空间复杂度：O(1)，只维护两个 DP 状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {  // nums：各节点价值；k：异或值；edges：树的边（本题只用它保证奇偶性约束，实际不参与计算）；返回最大价值之和
        long long f0 = 0, f1 = -0x3f3f3f3f;  // f0：已翻转节点个数为偶数时的最大和；f1：为奇数时的最大和；0x3f3f3f3f 取负作为「不可达」的极小值
        for (int x : nums) {  // 逐个节点决定它是否被异或翻转
            long long tmp = f0;  // 暂存旧的 f0，因为下面更新 f1 时还要用到它
            f0 = max(f0 + x, f1 + (x ^ k));  // 偶数状态：本节点不翻（f0 + x），或由奇数状态再翻一次变成偶数（f1 + (x ^ k)）
            f1 = max(f1 + x, tmp + (x ^ k));  // 奇数状态：本节点不翻（f1 + x），或由偶数状态翻一次变成奇数（tmp + (x ^ k)）
        }
        return f0;  // 翻转总数必须为偶数（每次边操作同时翻转两个标记），故答案取偶数状态 f0
    }
};
