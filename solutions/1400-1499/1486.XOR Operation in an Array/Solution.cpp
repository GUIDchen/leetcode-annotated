// 题目：1486. 数组异或操作（XOR Operation in an Array）
// 核心思路：直接按定义生成 nums[i] = start + 2*i，边生成边异或，0 作为异或单位元起步。
// 时间复杂度：O(n)，遍历 n 个元素；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int xorOperation(int n, int start) {  // n：元素个数；start：首项，后继元素公差为 2
        int ans = 0;  // 异或累加器，0 是异或的单位元
        for (int i = 0; i < n; ++i) {  // 依次生成第 i 个元素
            ans ^= start + 2 * i;  // 第 i 项为 start + 2i，边计算边异或进累加器
        }  // for 循环结束
        return ans;  // 返回全部元素的异或和
    }  // 方法结束
};  // Solution 类定义结束