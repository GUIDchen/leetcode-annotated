// 题目：1829. 每个查询的最大异或值（Maximum XOR for Each Query）
// 思路：先求整个数组的异或和，从高位到低位把异或和为 0 的位在 k 上置 1，即可让异或结果最大；之后从尾部逐个删元素。
// 时间复杂度：O(n * maximumBit)；空间复杂度：O(n)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {  // nums：查询数组；maximumBit：答案允许的二进制位数；返回每次查询的最大异或值
        int xs = 0;  // xs：整个数组的异或和
        for (int& x : nums) {  // 遍历全部元素
            xs ^= x;  // 把当前元素异或进来
        }  // 累加完成
        int n = nums.size();  // n 既是元素个数，也是查询次数
        vector<int> ans(n);  // 答案数组，长度与查询次数相同
        for (int i = 0; i < n; ++i) {  // 第 i 次查询：每次会删掉数组末尾的一个元素
            int x = nums[n - i - 1];  // 本次查询要从异或和中删掉的元素
            int k = 0;  // 待构造的 k，初始为 0
            for (int j = maximumBit - 1; ~j; --j) {  // 从最高位枚举到最低位；j 变成 -1 时 ~j 为 0，循环结束
                if ((xs >> j & 1) == 0) {  // 异或和该位为 0，就把 k 的该位取 1，使异或结果该位为 1
                    k |= 1 << j;  // 置位 k 的第 j 位
                }  // 分支结束
            }  // 位枚举结束
            ans[i] = k;  // 记录本次查询的答案
            xs ^= x;  // 删掉该元素：再异或一次即可抵消
        }  // 查询结束
        return ans;  // 返回全部答案
    }  // 方法结束
};  // 类定义结束