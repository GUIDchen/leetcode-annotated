// 3875. 构造奇偶一致的数组 I（Construct Uniform Parity Array I）
// 核心思路：I 题条件下任意数组都可以构造成奇偶一致，因此直接返回 true（题目只要求返回布尔值）。
// 复杂度：时间复杂度 O(1)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 公有成员
    bool uniformArray(vector<int>& nums1) {  // 判断能否把数组构造成奇偶一致
        return true;  // 在 I 题的限制下总是可行
    }  // 方法结束
};  // 类结束
