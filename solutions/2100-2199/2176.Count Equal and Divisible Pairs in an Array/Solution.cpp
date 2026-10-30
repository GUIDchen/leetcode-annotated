// 题目：2176. 统计数组中相等且可以被整除的数对（Count Equal and Divisible Pairs in an Array）
// 思路：枚举所有 i < j 的下标对，同时判断值相等与 (i*j) % k == 0 两个条件。
// 时间复杂度：O(n^2)，双重循环；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPairs(vector<int>& nums, int k) {  // nums：输入数组；k：整除条件里的除数；返回满足条件的数对个数
        int ans = 0;  // ans 统计答案，初值为 0
        for (int j = 1; j < nums.size(); ++j) {  // 外层枚举较大的下标 j，从 1 开始，保证前面至少存在 i = 0
            for (int i = 0; i < j; ++i) {  // 内层枚举较小的下标 i，范围 [0, j)，天然满足 i < j，不会重复计数
                ans += nums[i] == nums[j] && (i * j % k) == 0;  // 布尔表达式结果为 0/1，两个条件都成立时答案加一
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回统计结果
    }  // 方法结束
};  // 类定义结束，源文件到此为止
