// 题目：2501. 数组中最长的方波（Longest Square Streak in an Array）
// 思路：元素入哈希集合，枚举每个数作为起点，不断平方并检查结果是否仍在集合中，取最长链长。
// 时间复杂度：O(n·log log M)，每条链至多 O(log log M) 步；空间复杂度：O(n)，哈希集合保存所有元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSquareStreak(vector<int>& nums) {  // nums：输入数组；返回最长方波长度
        unordered_set<long long> s(nums.begin(), nums.end());  // 把数组元素放进哈希集合；long long 防止链式平方时溢出
        int ans = -1;  // 答案初值 -1：题目要求不存在长度 ≥2 的方波时返回 -1
        for (long long x : nums) {  // 枚举每个数作为方波起点（x 用 long long 便于不断平方）
            int t = 0;  // t：以 x 为起点的方波长度
            for (; s.contains(x); x *= x) {  // 只要 x 还在集合中，链就能延续；每轮结束把 x 平方作为下一个数
                ++t;  // 长度加一
            }  // 链式检查结束
            if (t > 1) {  // 题目要求方波长度至少为 2
                ans = max(ans, t);  // 更新最长方波长度
            }  // 长度判断结束
        }  // 起点枚举结束
        return ans;  // 返回最长长度；没有任何长度 ≥2 的方波时仍是 -1
    }  // 方法结束
};  // 类定义结束