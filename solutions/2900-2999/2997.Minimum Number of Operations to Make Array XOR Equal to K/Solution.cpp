// 题目：2997. 使数组异或和等于 K 的最少操作次数（Minimum Number of Operations to Make Array XOR Equal to K）
// 核心思路：把 k 依次与所有元素异或，结果就是「当前异或和 ⊕ 目标值」，其中每个为 1 的二进制位都需要一次翻转操作。
// 时间复杂度：O(n)，一次线性遍历加一次 popcount；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的解法接口
    int minOperations(vector<int>& nums, int k) {  // nums 是输入数组，k 是目标异或值，返回最少需要翻转的二进制位数
        for (int x : nums) {  // 遍历数组中的每个元素
            k ^= x;  // 把数组的异或和并入 k，遍历结束后 k 就是「当前异或和 ⊕ 目标值」
        }  // 遍历结束
        return __builtin_popcount(k);  // 每一个为 1 的二进制位都要翻转一次，所以答案是 1 的个数
    }  // 方法结束
};  // 类结束