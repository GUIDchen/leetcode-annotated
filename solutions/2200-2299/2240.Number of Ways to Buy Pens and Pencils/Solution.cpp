// 题目：2240. 买钢笔和铅笔的方案数（Number of Ways to Buy Pens and Pencils）
// 思路：枚举钢笔买 x 支（0 ≤ x ≤ total/cost1），剩余预算全用来买铅笔有 (剩余 / cost2) + 1 种数量选择，把这些方案数累加即可。
// 时间复杂度：O(total / cost1)，只枚举钢笔的购买数量；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {  // total：总预算；cost1 / cost2：钢笔与铅笔的单价
        long long ans = 0;  // 方案总数，可能超过 int 范围，所以用 long long 保存
        for (int x = 0; x <= total / cost1; ++x) {  // 枚举钢笔购买 x 支，最多买到预算花光为止
            int y = (total - x * cost1) / cost2 + 1;  // 剩余预算最多能买 (剩余 / cost2) 支铅笔，可选 0..该值，共 +1 种方案
            ans += y;  // 累加当前钢笔数量下对应的铅笔方案数
        }
        return ans;  // 返回所有购买方案的总数
    }
};