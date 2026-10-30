// 题目：2401. 最长优雅子数组（Longest Nice Subarray）
// 思路：滑动窗口维护一个两两按位与都为 0 的区间，mask 存窗口内所有元素的按位或，新元素与 mask 有交集时收缩左端。
// 时间复杂度：O(n)，左右指针各自只前进一次；空间复杂度：O(1)，只用了常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestNiceSubarray(vector<int>& nums) {  // nums：输入数组，返回最长优雅子数组的长度
        int ans = 0, mask = 0;  // ans 记录答案长度；mask 记录窗口内所有元素的按位或结果
        for (int l = 0, r = 0; r < nums.size(); ++r) {  // 右指针 r 逐个把元素纳入窗口，l 是窗口左端
            while (mask & nums[r]) {  // 新元素与窗口内某元素存在公共的 1 位，说明二元按位与不为 0
                mask ^= nums[l++];  // 把左端元素移出窗口：它的二进制位都在 mask 中，异或即可清除
            }
            mask |= nums[r];  // 新元素加入窗口，把它的二进制位并入 mask
            ans = max(ans, r - l + 1);  // 用当前窗口长度更新最长长度
        }
        return ans;  // 返回最长优雅子数组的长度
    }
};
