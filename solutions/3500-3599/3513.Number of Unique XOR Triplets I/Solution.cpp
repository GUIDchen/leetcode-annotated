// 题目：3513. 不同 XOR 三元组的数目 I（Number of Unique XOR Triplets I）
// 思路：结论题——数组长度 n <= 2 时不同异或值恰好 n 个；n >= 3 时答案为 2 的「n 的二进制位数」次方。
// 时间复杂度：O(1)，只算长度与位宽；空间复杂度：O(1)，不额外开数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int uniqueXorTriplets(vector<int>& nums) {  // nums：输入的整数数组
        size_t n = nums.size();  // n：数组长度
        return n <= 2 ? n : 1 << bit_width(n);  // 长度不超过 2 时答案就是 n；否则答案为 1 左移 bit_width(n) 位，即 2 的二进制位数次方
    }  // 方法结束
};  // 类结束