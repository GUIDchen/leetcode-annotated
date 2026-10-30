// 题目：1004. 最大连续1的个数 III（Max Consecutive Ones III）
// 核心思路：滑动窗口维护「窗口内 0 的个数不超过 k」的最长区间
// 复杂度：时间 O(n)，每个元素最多进出窗口一次；空间 O(1)
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestOnes(vector<int>& nums, int k) {  // nums：只含 0/1 的数组；k：最多可把 k 个 0 翻转成 1
        int l = 0, cnt = 0;  // l：滑动窗口左边界；cnt：当前窗口内 0 的个数
        // 右边界逐格右移，每次把 x 纳入窗口
        for (int x : nums) {  // 遍历数组中的每个元素
            cnt += x ^ 1;  // x 为 0 时 x^1 得 1，把新进入窗口的 0 计入 cnt
            if (cnt > k) {  // 窗口内 0 的个数超过可翻转上限，窗口不再合法
                cnt -= nums[l++] ^ 1;  // 左端元素移出窗口：它若是 0 就同步减 1，随后 l 右移一格
            }  // 收缩一格后窗口重新合法
        }  // 右边界已到数组末尾
        return nums.size() - l;  // 最后这段合法窗口一直延伸到末尾，其长度就是出现过的最长长度
    }  // 方法结束
};  // 类定义结束