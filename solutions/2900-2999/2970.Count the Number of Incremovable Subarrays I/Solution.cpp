// 题目：2970. 统计移除递增子数组的数目 I（Count the Number of Incremovable Subarrays I）
// 思路：先求出最长严格递增前缀的末尾下标 i，再倒序枚举保留后缀的起点 j，用双指针统计每组合法左右端点。
// 时间复杂度：O(n)（i 只减不增，两个指针合计线性）；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int incremovableSubarrayCount(vector<int>& nums) {  // nums：输入数组；返回可移除的递增子数组数目
        int i = 0, n = nums.size();  // i 指向最长严格递增前缀的末尾，n 是数组长度
        while (i + 1 < n && nums[i] < nums[i + 1]) {  // 只要后一个比前一个大就继续延伸递增前缀
            ++i;  // 前缀仍在严格递增
        }  // 前缀尽头右移
        if (i == n - 1) {  // 整个数组本来就严格递增
            return n * (n + 1) / 2;  // 删掉任意子数组都仍递增，答案是 n*(n+1)/2（即所有子数组个数）
        }  // 分支结束
        int ans = i + 2;  // 先统计「删到末尾」的 i+2 种：左端点可取 0..i+1
        for (int j = n - 1; j > 0; --j) {  // 倒序枚举保留下来的后缀起点 j（被删子数组的右端是 j-1）
            while (i >= 0 && nums[i] >= nums[j]) {  // 左端点不能越过 i，且必须满足 nums[i] < nums[j] 才能拼成递增
                --i;  // 不断左移 i，直到前缀末尾的值小于 nums[j]
            }  // 内层收缩结束
            ans += i + 2;  // 此时左端点 l 可取 0..i+1，共 i+2 种删法
            if (nums[j - 1] >= nums[j]) {  // 后缀自身不再严格递增时，更长的后缀也不可能合法
                break;  // 提前结束枚举
            }  // 分支结束
        }  // j 左移，继续扩大保留的后缀
        return ans;  // 循环体结束
    }  // 返回累计的方案数
};  // 类结束