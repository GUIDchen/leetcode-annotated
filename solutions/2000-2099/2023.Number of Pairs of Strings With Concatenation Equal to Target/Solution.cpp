// 题目：2023. 连接后等于目标字符串的字符串对（Number of Pairs of Strings With Concatenation Equal to Target）
// 思路：暴力枚举所有有序下标对 (i, j)，当下标不同且 nums[i] + nums[j] 等于 target 时计数；有序意味着 (i, j) 与 (j, i) 分别统计。
// 时间复杂度：O(n^2 * L)，L 为字符串拼接与比较的长度；空间复杂度：O(L)，拼接产生的临时字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfPairs(vector<string>& nums, string target) {  // nums：候选字符串数组；target：目标字符串
        int n = nums.size();  // 数组长度，用于枚举下标
        int ans = 0;  // 合法有序对的计数
        for (int i = 0; i < n; ++i) {  // 枚举第一个下标 i
            for (int j = 0; j < n; ++j) {  // 枚举第二个下标 j
                if (i != j && nums[i] + nums[j] == target) ++ans;  // 下标必须不同，且拼接结果等于目标串才计数
            }  // 第二层循环结束
        }  // 第一层循环结束
        return ans;  // 返回合法有序对的个数
    }  // numOfPairs 方法结束
};  // Solution 类定义结束