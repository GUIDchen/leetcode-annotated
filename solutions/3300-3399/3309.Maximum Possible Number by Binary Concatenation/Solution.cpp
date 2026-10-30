// 题目：3309. 连接二进制表示可形成的最大数值（Maximum Possible Number by Binary Concatenation）
// 思路：只有三个数，全排列共 3! = 6 种，直接枚举每种顺序，把各数的二进制表示依次拼接后换算成十进制，取最大值。
// 复杂度：时间 O(1)，6 种排列、每个数最多 7 位；空间 O(1)，位暂存数组长度也是常数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxGoodNumber(vector<int>& nums) {  // nums 是三个正整数，可任意排列；返回连接二进制表示后能得到的最大数值
        int ans = 0;  // 记录所有排列中得到的最大值
        auto f = [&](vector<int>& nums) {  // 辅助 lambda：按当前排列顺序把各数的二进制表示拼接成一个整数
            int res = 0;  // res：拼接后换算出的十进制数值
            vector<int> t;  // 暂存二进制位，注意 push 的顺序是「低位在前」
            for (int x : nums) {  // 依次处理当前排列中的每个数
                for (; x; x >>= 1) {  // 反复取 x 的最低位并右移，直到 x 变成 0
                    t.push_back(x & 1);  // 把当前最低位存入数组
                }  // 内层 for 结束
            }  // 外层 for 结束
            while (t.size()) {  // 从尾部逐个弹出，弹出顺序正好是「高位在前」的拼接顺序
                res = res * 2 + t.back();  // 左移一位并加上新位，完成二进制到十进制的换算
                t.pop_back();  // 弹出已使用的位
            }  // while 结束
            return res;  // 返回该排列对应的拼接数值
        };  // 辅助 lambda 定义结束
        for (int i = 0; i < 6; ++i) {  // 三个数的全排列共 6 种，逐个枚举
            ans = max(ans, f(nums));  // 用当前排列算出一个候选值并更新最大值
            next_permutation(nums.begin(), nums.end());  // 原地生成字典序中的下一个排列，把 nums 变成下一种顺序（最后一次会回到升序）
        }  // for 循环结束
        return ans;  // 返回最大值
    }  // 方法结束
};  // 类定义结束
