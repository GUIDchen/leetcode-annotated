// 题目：2488. 统计中位数为 K 的子数组（Count Subarrays With Median K）
// 思路：以 K 所在位置为中心，大于 K 记 +1、小于 K 记 -1，左右两侧偏置和之和为 0 或 1 的子数组，其中位数恰为 K。
// 时间复杂度：O(n)，两侧各线性扫描一次；空间复杂度：O(n)，计数数组长度为 2n+1。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSubarrays(vector<int>& nums, int k) {  // nums：整数数组；k：目标中位数；返回中位数恰好为 k 的子数组个数
        int n = nums.size();  // 数组长度
        int i = find(nums.begin(), nums.end(), k) - nums.begin();  // 定位 k 的下标（题目保证 k 在数组中出现一次）
        int cnt[n << 1 | 1];  // cnt[x + n]：右半边偏置和为 x 的位置个数，下标偏移 n 以避免负数
        memset(cnt, 0, sizeof(cnt));  // 计数数组清零
        int ans = 1;  // 先计入只含 k 本身的子数组 [i, i]
        int x = 0;  // x：从左往右累加的偏置和，元素大于 k 记 +1，小于 k 记 -1
        for (int j = i + 1; j < n; ++j) {  // 枚举以 i 为左端点的右半部分
            x += nums[j] > k ? 1 : -1;  // 更新偏置和
            if (x >= 0 && x <= 1) {  // 偏置和为 0 或 1 时，[i, j] 的中位数正好是 k
                ++ans;  // 计入这个子数组
            }  // 不满足则不计
            ++cnt[x + n];  // 记录该偏置和出现次数，供左半部分配对使用
        }  // 右半部分扫描结束
        x = 0;  // 重置偏置和，改为从 k 向左累加
        for (int j = i - 1; ~j; --j) {  // 枚举 k 左侧的元素；~j 等价于 j >= 0
            x += nums[j] > k ? 1 : -1;  // 更新左侧偏置和
            if (x >= 0 && x <= 1) {  // 左侧偏置和为 0 或 1 时，[j, i] 的中位数也是 k
                ++ans;  // 计入以 k 为右端点的子数组
            }  // 不满足则不计
            ans += cnt[-x + n] + cnt[-x + 1 + n];  // 与右半边配对：左和 + 右和 为 0 或 1，即右和为 -x 或 -x+1
        }  // 左半部分扫描结束
        return ans;  // 返回统计结果
    }  // 方法结束
};  // 类定义结束