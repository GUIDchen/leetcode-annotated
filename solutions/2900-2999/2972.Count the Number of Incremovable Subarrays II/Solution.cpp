// 题目：2972. 统计移除递增子数组的数目 II（Count the Number of Incremovable Subarrays II）
// 思路：与 2970 相同，先定出最长严格递增前缀末尾 i，再倒序枚举保留后缀起点 j，双指针累计方案数；答案用 long long 防溢出。
// 时间复杂度：O(n)，i 只减不增；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long incremovableSubarrayCount(vector<int>& nums) {  // nums：输入数组，返回可移除的递增子数组数目（结果可达 1e10 量级，故返回 long long）
        int i = 0, n = nums.size();  // i 指向最长严格递增前缀的末尾，n 为数组长度
        while (i + 1 < n && nums[i] < nums[i + 1]) {  // 前缀能继续严格递增就继续走
            ++i;  // 前缀仍在递增
        }  // 前缀末尾右移
        if (i == n - 1) {  // 整个数组已经严格递增
            return n * (n + 1LL) / 2;  // 此时任意子数组都可移除，答案 n*(n+1)/2；1LL 强制 long long 乘法防溢出
        }  // 分支结束
        long long ans = i + 2;  // 先计入「删到末尾」的 i+2 种方案
        for (int j = n - 1; j > 0; --j) {  // 倒序枚举保留下来的后缀起点 j
            while (i >= 0 && nums[i] >= nums[j]) {  // 左端点不能越过 i，且要满足前缀末尾小于 nums[j]
                --i;  // 不断左移前缀末尾，直到能拼成严格递增
            }  // 内层收缩结束
            ans += i + 2;  // 左端点 l 可取 0..i+1，共 i+2 种
            if (nums[j - 1] >= nums[j]) {  // 后缀自身不再严格递增，更长的后缀也不合法
                break;  // 提前退出
            }  // 分支结束
        }  // j 左移，扩大保留的后缀
        return ans;  // 循环体结束
    }  // 返回累计方案数
};  // 类结束