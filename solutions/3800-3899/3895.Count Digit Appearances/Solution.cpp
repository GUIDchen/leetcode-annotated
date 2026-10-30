// 题目：3895. 统计数字出现总次数（Count Digit Appearances）
// 思路：对每个数不断取末位判断是否等于目标数字，再整除 10 去掉末位，逐个累加出现次数。
// 时间复杂度：O(n × log₁₀M)，M 为数值大小；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDigitOccurrences(vector<int>& nums, int digit) {  // nums：输入数组；digit：要统计的数字
        int ans = 0;  // 答案：digit 出现的总次数
        for (int x : nums) {  // 遍历每个整数
            for (; x > 0; x /= 10) {  // 不断取末位，直到这个数变成 0
                if (x % 10 == digit) {  // 末位恰好等于目标数字
                    ++ans;  // 出现次数加 1
                }
            }  // 去掉末位，继续看高位
        }
        return ans;  // 返回总次数
    }  // 结束方法
};  // 结束类
