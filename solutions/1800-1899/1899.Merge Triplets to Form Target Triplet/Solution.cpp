// 题目：1899. 合并若干三元组以形成目标三元组（Merge Triplets to Form Target Triplet）
// 思路：任一维超过 target 的三元组都不能参与合并（合并只会让分量变大），剩下可用的三元组按维取最大值，三个最大分量恰好等于 target 时就能合并出目标。
// 时间复杂度：O(m)，m 为三元组个数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {  // triplets：可选的三元组；target：目标三元组
        int x = target[0], y = target[1], z = target[2];  // 拆出目标三元组的三个分量
        int d = 0, e = 0, f = 0;  // 记录可用三元组在各维上能取到的最大值
        for (auto& t : triplets) {  // 逐个考察三元组
            int a = t[0], b = t[1], c = t[2];  // 当前三元组的三个分量
            if (a <= x && b <= y && c <= z) {  // 任一维超过目标就不能用，因为合并只会让分量变大
                d = max(d, a);  // 维护第一维最大值
                e = max(e, b);  // 维护第二维最大值
                f = max(f, c);  // 维护第三维最大值
            }
        }
        return d == x && e == y && f == z;  // 三个分量都能顶到目标值，说明可以合并出 target
    }
};