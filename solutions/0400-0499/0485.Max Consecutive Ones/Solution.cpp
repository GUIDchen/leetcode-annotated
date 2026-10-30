// 题目：485. 最大连续 1 的个数（Max Consecutive Ones）
// 思路：一次遍历，用 cnt 记录当前连续 1 的长度，遇到 1 就加一并用它更新答案，遇到 0 就把 cnt 清零。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的题解方法
    int findMaxConsecutiveOnes(vector<int>& nums) {  // nums 是只含 0 和 1 的数组，返回最长连续 1 的长度
        int ans = 0, cnt = 0;  // ans 记录历史最大长度，cnt 记录当前连续 1 的个数
        for (int x : nums) {  // 逐个元素遍历（按值遍历，不需要下标）
            if (x) {  // 当前元素是 1
                ans = max(ans, ++cnt);  // 先把当前长度加一，再用它刷新历史最大值
            } else {  // 否则当前元素是 0
                cnt = 0;  // 连续段被打断，长度清零
            }  // 结束 if-else 分支
        }  // 结束遍历
        return ans;  // 返回最大连续 1 的个数
    }  // 结束题解方法
};  // 结束题解类