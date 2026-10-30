// 3688. Bitwise OR of Even Numbers in an Array（3688. 偶数的按位或运算）
// 核心思路：遍历数组，只把偶数按位或进答案，最终结果即为所有偶数的按位或。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    int evenNumberBitwiseORs(vector<int>& nums) {  // 返回所有偶数的按位或结果
        int ans = 0;  // 0 是按位或的单位元
        for (int x : nums) {  // 遍历数组中的每个数
            if (x % 2 == 0) {  // 只处理偶数
                ans |= x;  // 把该偶数按位或进答案
            }
        }
        return ans;  // 返回结果，没有偶数时为 0
    }
};
