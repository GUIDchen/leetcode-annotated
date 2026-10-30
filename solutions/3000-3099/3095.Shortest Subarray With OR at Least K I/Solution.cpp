// 题目：3095. 或值至少为 K 的最短子数组 I（Shortest Subarray With OR at Least K I）
// 思路：维护滑动窗口 [i, j]，cnt[h] 记录窗口内第 h 位上 1 的个数，s 是窗口内所有数的按位或；当 s >= k 时不断右移左边界并更新最短长度。
// 时间复杂度：O(n × 32)，每个元素最多进出窗口一次；空间复杂度：O(32)，只用了长度 32 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSubarrayLength(vector<int>& nums, int k) {  // nums 是数组，k 是或值下限
        int n = nums.size();  // 数组长度
        int cnt[32]{};  // cnt[h]：窗口内第 h 位为 1 的元素个数（{} 保证全部初始化为 0）
        int ans = n + 1;  // 最短长度初值取「不可能达到」的 n+1，方便最后判断无解
        for (int i = 0, j = 0, s = 0; j < n; ++j) {  // i 是左边界，j 是右边界，s 是窗口或值
            s |= nums[j];  // 把新元素并入窗口或值
            for (int h = 0; h < 32; ++h) {  // 统计新元素各个二进制位
                if ((nums[j] >> h & 1) == 1) {  // 第 h 位为 1 才需要计数
                    ++cnt[h];  // 该位为 1 的个数加一
                }
            }
            for (; s >= k && i <= j; ++i) {  // 窗口合法时不断右移左边界，尝试更短的子数组
                ans = min(ans, j - i + 1);  // 用当前窗口长度更新答案
                for (int h = 0; h < 32; ++h) {  // 逐位移除 nums[i] 的贡献
                    if ((nums[i] >> h & 1) == 1) {  // 该元素第 h 位为 1
                        if (--cnt[h] == 0) {  // 减一后该位在窗口内已没有 1
                            s ^= 1 << h;  // 把或值中的这一位清掉
                        }
                    }
                }
            }
        }
        return ans > n ? -1 : ans;  // 全程没找到合法子数组就返回 -1
    }
};