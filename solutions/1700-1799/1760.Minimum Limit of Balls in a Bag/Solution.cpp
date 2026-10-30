// 题目：1760. 袋子里最少数目的球（Minimum Limit of Balls in a Bag）
// 思路：二分答案。上限 mx 越小所需操作越多，答案具有单调性；把 x 个球拆成每袋不超过 mx 需 (x-1)/mx 次操作。
// 时间复杂度：O(n log M)，M = max(nums)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSize(vector<int>& nums, int maxOperations) {  // nums：每袋的球数；maxOperations：最多操作次数
        int l = 1, r = ranges::max(nums);  // 答案下界为 1，上界为不做任何拆分时的最大值
        while (l < r) {  // 二分寻找最小的可行上限
            int mid = (l + r) >> 1;  // 取中点作为试探的每袋上限，右移一位等价于除以 2
            long long s = 0;  // 统计当前上限下需要的总操作次数
            for (int x : nums) {  // 逐个袋子计算
                s += (x - 1) / mid;  // x 个球分成每袋不超过 mid，需要 ceil(x/mid)-1 即 (x-1)/mid 次拆分
            }
            if (s <= maxOperations) {  // 操作次数没超限，说明上限还可以更小
                r = mid;  // 收缩右边界，保留 mid 这个可行解
            } else {  // 操作次数超限，上限必须放大
                l = mid + 1;  // 舍弃 mid 及其左侧
            }
        }
        return l;  // 收敛后 l 就是最小可行的每袋上限
    }
};
