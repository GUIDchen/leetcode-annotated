// 3467. Transform Array by Parity / 3467. 将数组按照奇偶性转化
// 核心思路：统计偶数个数 even，转化后前 even 个位置为 0、其余为 1。
// 复杂度：时间 O(n)，空间 O(1)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 公有接口
    vector<int> transformArray(vector<int>& nums) {  // 原地把偶数改成 0、奇数改成 1 后返回
        int even = 0;  // even 记录偶数个数，也就是最终 0 的个数
        for (int x : nums) {  // 遍历数组统计偶数个数
            even += (x & 1 ^ 1);  // (x & 1) 取最低位再异或 1：偶数得 1、奇数得 0，直接累加
        }  // 统计结束
        for (int i = 0; i < even; ++i) {  // 前 even 个位置填 0
            nums[i] = 0;  // 偶数位置赋 0
        }  // 填 0 结束
        for (int i = even; i < nums.size(); ++i) {  // 其余位置填 1
            nums[i] = 1;  // 奇数位置赋 1
        }  // 填 1 结束
        return nums;  // 返回按奇偶性转化后的数组
    }  // 方法结束
};  // 类定义结束
