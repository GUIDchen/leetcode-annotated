// 题目：1802. 有界数组中指定下标处的最大值（Maximum Value at a Given Index in a Bounded Array）
// 思路：二分答案 x，构造以 nums[index] = x 为峰、向两侧每次减 1 且不小于 1 的最小数组，用等差数列公式 O(1) 求最小总和，验证是否不超过 maxSum。
// 时间复杂度：O(log maxSum)，二分次数为对数级；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxValue(int n, int index, int maxSum) {  // n 为数组长度，index 为目标下标，maxSum 为元素总和上限
        auto sum = [](long x, int cnt) {  // lambda：计算 cnt 个位置从 x 开始逐 1 递减（最小到 1）所需的最少元素和
            return x >= cnt ? (x + x - cnt + 1) * cnt / 2 : (x + 1) * x / 2 + cnt - x;  // x >= cnt 时是 x 到 x-cnt+1 的等差和；否则减到 1 后剩下的位置全填 1
        };  // 求和辅助 lambda 定义结束
        int left = 1, right = maxSum;  // 答案下界为 1（元素至少为 1），上界为 maxSum
        while (left < right) {  // 二分查找满足总和限制的最大 x
            int mid = (left + right + 1) >> 1;  // 取上中位数，保证 left = mid 收缩时不会死循环
            if (sum(mid - 1, index) + sum(mid, n - index) <= maxSum) {  // 左侧 index 个位置加右侧 n-index 个位置的最小和不超过 maxSum
                left = mid;  // 可行：记录下来并尝试更大的值
            } else {  // 否则当前 x 太大
                right = mid - 1;  // 把上界压到 mid - 1
            }
        }
        return left;  // 循环结束时 left == right，即最大可行值
    }
};