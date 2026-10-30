// 题目：3641. 最长半重复子数组（Longest Semi-Repeating Subarray）
// 核心思路：滑动窗口。窗口内记录每个值的出现次数，以及「出现次数恰好为 2 的不同值个数」cur；右端每纳入一个元素就更新 cur，一旦 cur 超过 k 就不断右移左端收缩窗口，窗口合法时用其长度更新答案。
// 复杂度：时间 O(n)，左右指针各自最多右移 n 次；空间 O(n)，哈希表最多保存窗口内不同值的个数。
class Solution {  // LeetCode 题解类
public:  // 对外接口
    int longestSubarray(vector<int>& nums, int k) {  // nums：输入数组；k：允许「恰好出现两次」的元素种类数上限
        unordered_map<int, int> cnt;  // 滑动窗口内每个值的出现次数
        int ans = 0, cur = 0, l = 0;  // ans：最长长度；cur：窗口内恰出现两次的种类数；l：窗口左端
        for (int r = 0; r < nums.size(); ++r) {  // 枚举窗口右端，逐步向右扩张
            if (++cnt[nums[r]] == 2) {  // 新元素计数 +1，若加完正好等于 2
                ++cur;  // 则「恰好两次」的种类数又多了一种
            }
            while (cur > k) {  // 超出上限，需要收缩左端
                if (--cnt[nums[l++]] == 1) {  // 左端元素计数 -1 并右移左指针；减后为 1 说明它不再是「恰好两次」
                    --cur;  // 对应种类数减少
                }
            }
            ans = max(ans, r - l + 1);  // 用当前窗口长度更新答案
        }
        return ans;  // 返回最长合法长度
    }
};