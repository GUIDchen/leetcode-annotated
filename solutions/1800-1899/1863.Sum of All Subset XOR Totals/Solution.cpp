// 题目：1863. 找出所有子集的异或总和再求和（Sum of All Subset XOR Totals）
// 思路：n 个元素只有 2^n 个子集，用二进制数 i 枚举子集——i 的第 j 位为 1 表示选入 nums[j]，算出该子集的异或和再累加。
// 时间复杂度：O(2^n · n)，枚举子集与逐元素的二重循环；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subsetXORSum(vector<int>& nums) {  // nums：输入数组
        int n = nums.size();  // 元素个数，子集总数为 2^n
        int ans = 0;  // 累加所有子集的异或和
        for (int i = 0; i < 1 << n; ++i) {  // 用 i 的二进制位表示一个子集，1 << n 就是 2^n
            int s = 0;  // 当前子集的异或和，0 是异或的单位元
            for (int j = 0; j < n; ++j) {  // 逐位检查第 j 个元素是否被选入
                if (i >> j & 1) {  // 第 j 位为 1 说明 nums[j] 属于当前子集
                    s ^= nums[j];  // 把 nums[j] 异或进当前结果
                }  // 这一位检查完毕
            }  // 所有位检查完毕，s 就是当前子集的异或和
            ans += s;  // 累加当前子集的异或和
        }  // 所有子集枚举完毕
        return ans;  // 返回所有子集异或和的总和
    }  // 方法结束
};  // 类定义结束