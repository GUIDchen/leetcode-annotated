// 题目：2831. 找出最长等值子数组（Find the Longest Equal Subarray）
// 思路：滑动窗口 + 出现次数统计。窗口 [l, r] 内出现次数最多的值的次数记为 mx，窗口长度为 r-l+1，需要删掉的元素个数是 (r-l+1-mx)；只要这个值大于 k 就收缩左边界，答案即所有窗口中最大的 mx。
// 时间复杂度：O(n)，左右指针各自单调移动，哈希表每次均摊 O(1)；空间复杂度：O(n)，哈希表最多存 n 种不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestEqualSubarray(vector<int>& nums, int k) {  // nums：输入数组；k：最多可删除的元素个数
        unordered_map<int, int> cnt;  // 记录当前窗口内每个值出现的次数
        int mx = 0, l = 0;  // mx：窗口内出现次数的最大值；l：滑动窗口左端点
        for (int r = 0; r < nums.size(); ++r) {  // 右端点 r 从左到右扩展窗口
            mx = max(mx, ++cnt[nums[r]]);  // 把 nums[r] 计入窗口，并同步更新窗口内的最大出现次数
            if (r - l + 1 - mx > k) {  // 窗口内「非众数」元素超过 k 个，说明无法靠删除变成等值数组
                --cnt[nums[l++]];  // 移出左端点元素并让左指针右移一格，缩小窗口
            }
        }
        return mx;  // 全程记录的最大出现次数就是最长等值子数组的长度
    }
};