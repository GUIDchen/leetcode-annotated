// 题目：2177. 找到和为给定整数的三个连续整数（Find Three Consecutive Integers That Sum to a Given Number）
// 思路：三个连续整数之和必为 3 的倍数，且中间那个数就是 num/3；不能被 3 整除则无解，返回空数组。
// 时间复杂度：O(1)；空间复杂度：O(1)，只返回长度最多为 3 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> sumOfThree(long long num) {  // num：目标和；返回三个连续整数组成的数组，不存在则返回空数组
        if (num % 3) {  // num % 3 不为 0 说明 num 不是 3 的倍数，三个连续整数不可能凑出它
            return {};  // 直接返回空 vector，表示无解
        }  // 判断分支结束
        long long x = num / 3;  // 中间那个数就是 num / 3，左右各差 1
        return {x - 1, x, x + 1};  // 返回 (x-1, x, x+1)，三者之和恰好是 3x = num
    }  // 方法结束
};  // 类定义结束，源文件到此为止