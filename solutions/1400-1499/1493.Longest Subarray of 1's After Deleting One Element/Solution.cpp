// 题目：1493. 删掉一个元素以后全为 1 的最长子数组（Longest Subarray of 1's After Deleting One Element）
// 思路：预处理每个位置向左、向右的连续 1 长度，再枚举被删除的位置，把左右两段拼接后取最大值。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，两个长度为 n+1 的辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSubarray(vector<int>& nums) {  // 返回删掉一个元素后最长的全 1 子数组长度
        int n = nums.size();  // 数组长度
        vector<int> left(n + 1);  // left[i] 表示以 nums[i-1] 结尾的连续 1 的个数（多开一位便于处理边界）
        vector<int> right(n + 1);  // right[i] 表示以 nums[i] 开头的连续 1 的个数
        for (int i = 1; i <= n; ++i) {  // 正序扫描，递推 left 数组
            if (nums[i - 1]) {  // 当前位置是 1 才能延长连续段
                left[i] = left[i - 1] + 1;  // 接上前一个位置结尾的连续长度
            }  // if 结束
        }  // for 结束，left 预处理完成
        for (int i = n - 1; ~i; --i) {  // 逆序扫描，递推 right 数组；~i 等价于 i >= 0
            if (nums[i]) {  // 当前位置是 1 才能延长连续段
                right[i] = right[i + 1] + 1;  // 接上后一个位置开头的连续长度
            }  // if 结束
        }  // for 结束，right 预处理完成
        int ans = 0;  // 记录最大长度
        for (int i = 0; i < n; ++i) {  // 枚举被删除的元素位置 i
            ans = max(ans, left[i] + right[i + 1]);  // 删掉 nums[i] 后，左边留下 left[i] 个 1，右边留下 right[i+1] 个 1，两段拼在一起
        }  // for 结束
        return ans;  // 返回最大值
    }  // 方法结束
};  // 类定义结束