// 题目：2317. 操作后的最大异或和（Maximum XOR After Operations）
// 核心思路：每次操作可把任一元素的任意二进制位清零，故答案的某一位只要在任一元素中出现过 1 就能保留；把所有元素按位或即得最大异或和。
// 时间复杂度：O(n)，只遍历数组一次；空间复杂度：O(1)，仅用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumXOR(vector<int>& nums) {  // nums：输入数组；返回经过任意次操作后能达到的最大异或和
        int ans = 0;  // ans 累积所有元素的按位或结果，先置 0
        for (int& x : nums) {  // 范围 for 遍历数组，用引用避免元素拷贝
            ans |= x;  // 按位或：只要某一位在任一元素中出现过 1，就能通过 AND/XOR 操作把它留在最终答案中
        }  // 循环体结束
        return ans;  // 全部元素的按位或就是可达到的最大异或和
    }  // maximumXOR 结束
};  // 类定义结束