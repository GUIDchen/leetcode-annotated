// 题目：1558. 得到目标数组的最少函数调用次数（Minimum Numbers of Function Calls to Make Target Array）
// 思路：正难则反，把目标数组一路「减 1 / 整体除 2」还原成全 0；每个数的二进制 1 的个数是需要单独减 1 的次数，所有数共用的除 2 次数由最大值决定。
// 时间复杂度：O(n)，每个元素只做一次 popcount；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& nums) {  // nums：目标数组
        int ans = 0;  // 累计最少操作次数
        int mx = 0;  // 记录数组最大值，它的二进制长度决定整体除 2 的次数
        for (int v : nums) {  // 逐个处理数组元素
            mx = max(mx, v);  // 维护最大值
            ans += __builtin_popcount(v);  // 二进制中 1 的个数 = 该元素需要的单独加 1 次数
        }  // 左花括号结束循环体
        if (mx) ans += 31 - __builtin_clz(mx);  // 最大值二进制位数减一 = 所有元素共用的大于 1 的整体乘 2 次数（mx 为 0 时无需操作）
        return ans;  // 返回总操作次数
    }  // 方法结束
};  // 类定义结束