// 题目：1295. 统计位数为偶数的数字（Find Numbers with Even Number of Digits）
// 核心思路：把每个数字转成字符串取长度即为十进制位数，判断位数是否为偶数并计数。
// 时间复杂度：O(n·log V)，每个数做一次位数转换；空间复杂度：O(1)，Python 版另有 O(log V) 的字符串开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findNumbers(vector<int>& nums) {  // nums 是正整数数组，返回其中「十进制位数为偶数」的元素个数
        int ans = 0;  // ans 累计满足条件的元素个数
        for (int& x : nums) {  // 按引用遍历每个元素，避免拷贝
            ans += to_string(x).size() % 2 == 0;  // 转成字符串后取长度即位数；位数为偶数时比较结果为 true(1)，直接累加进 ans
        }  // 结束 for 循环
        return ans;  // 返回满足条件的元素个数
    }  // 结束函数
};  // 结束题解类
