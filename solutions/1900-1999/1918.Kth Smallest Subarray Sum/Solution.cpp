// 题目：1918. 第 K 小的子数组和（Kth Smallest Subarray Sum）
// 思路：二分答案。对候选和 s 用滑动窗口统计“和 ≤ s 的子数组个数”，因为元素全为正数窗口可单调收缩；再二分找第一个使计数 ≥ k 的 s。
// 时间复杂度：O(n log S)，S 为数组总和，每次判定 O(n)；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int kthSmallestSubarraySum(vector<int>& nums, int k) {  // nums 中全为正数；返回所有子数组和中第 k 小的那个值
        int l = 1 << 30, r = 0;  // l 为答案下界（先设很大），r 为答案上界（子数组和不会超过总和）
        for (int& x : nums) {  // 遍历数组以确定二分区间
            l = min(l, x);  // 子数组和的最小可能值就是最小元素
            r += x;  // 最大可能值是整个数组的和
        }  // 结束区间统计
        auto f = [&](int s) {  // 匿名函数：统计和不超过 s 的子数组个数（按值捕获外部变量）
            int cnt = 0, t = 0;  // cnt 计数，t 是窗口 [j, i] 内元素之和
            for (int i = 0, j = 0; i < nums.size(); ++i) {  // 右端点 i 向右滑动，j 是窗口左端点
                t += nums[i];  // 把 nums[i] 纳入窗口
                while (t > s) {  // 和超过 s 就收缩左端点（元素为正，收缩后必然更小）
                    t -= nums[j++];  // 移出左端点的值，并让 j 右移
                }  // 结束收缩循环
                cnt += i - j + 1;  // 以 i 结尾、和 ≤ s 的子数组恰有 i-j+1 个（左端点可落在 j..i）
            }  // 结束右端点遍历
            return cnt;  // 返回满足条件的子数组个数
        };  // 结束匿名函数
        while (l < r) {  // 二分答案：寻找最小的 s 使 f(s) ≥ k
            int mid = (l + r) >> 1;  // 取中点，向下取整避免区间停滞
            if (f(mid) >= k) {  // 至少有 k 个子数组的和 ≤ mid，说明答案不在 mid 右侧
                r = mid;  // 保留 mid 作为上界
            } else {  // 否则满足条件的子数组不足 k 个
                l = mid + 1;  // 答案严格大于 mid
            }  // 结束分支
        }  // 结束二分
        return l;  // l == r 时即为第 k 小的子数组和
    }  // 方法结束
};  // 类定义结束