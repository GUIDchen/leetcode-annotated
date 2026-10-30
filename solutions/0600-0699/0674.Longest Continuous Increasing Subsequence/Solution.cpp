// 题目：674. 最长连续递增序列（Longest Continuous Increasing Subsequence）
// 思路：一次遍历，维护以当前位置结尾的连续递增段长度 cnt，遇到断点就重置为 1，全程用 ans 记录最大值。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用两个计数器变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findLengthOfLCIS(vector<int>& nums) {  // nums：输入数组
        int ans = 1;  // 答案至少为 1（单个元素也算连续递增）
        for (int i = 1, cnt = 1; i < nums.size(); ++i) {  // i 从 1 开始比较相邻元素，cnt 是当前连续递增段长度
            if (nums[i - 1] < nums[i]) {  // 相邻严格递增，说明连续段可以延长
                ans = max(ans, ++cnt);  // 先把 cnt 加一，再更新最大值
            } else {  // 递增中断
                cnt = 1;  // 从当前元素重新开始计一段
            }
        }
        return ans;  // 返回最长连续递增序列的长度
    }
};