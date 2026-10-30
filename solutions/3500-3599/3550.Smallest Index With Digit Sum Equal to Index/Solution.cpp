// 题目：3550. 数位和等于下标的最小下标（Smallest Index With Digit Sum Equal to Index）
// 思路：从下标 0 开始顺序枚举，逐个算出 nums[i] 的十进制数位和并与下标比较，第一个相等的位置就是答案；枚举结束仍未命中则返回 -1。
// 时间复杂度：O(n · log M)，M 为元素最大值，每个元素最多拆 log10(M) 位；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestIndex(vector<int>& nums) {  // nums：给定数组；返回数位和等于下标的最小下标，不存在则返回 -1
        for (int i = 0; i < nums.size(); ++i) {  // 按下标从小到大枚举，保证第一次命中就是最小下标
            int s = 0;  // s：当前元素 nums[i] 的数位和
            while (nums[i]) {  // 不断取最低位，直到数字被除到 0
                s += nums[i] % 10;  // 累加最低位上的数字
                nums[i] /= 10;  // 去掉最低位，继续处理更高位
            }  // 数位和计算结束
            if (s == i) {  // 数位和恰好等于下标
                return i;  // 从小到大枚举，首个命中的下标必然最小，直接返回
            }  // 条件分支结束
        }  // 枚举结束
        return -1;  // 没有数位和等于下标的元素
    }  // 方法结束
};  // 类定义结束