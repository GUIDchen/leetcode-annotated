// 题目：932. 漂亮数组（Beautiful Array）
// 思路：分治构造。把左侧漂亮数组映射成奇数 2x-1、右侧映射成偶数 2x 后拼接；奇偶分离保证不会出现跨度均匀的三元组。
// 时间复杂度：O(n log n)，每层元素总数不超过 n；空间复杂度：O(n)，递归各层的结果合起来与 n 同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> beautifulArray(int n) {  // 返回 1..n 的一个排列，使得任意 i<j<k 都不满足 a[i]+a[k] == 2*a[j]
        if (n == 1) return {1};  // 递归出口：只有一个数时数组本身就是漂亮的
        vector<int> left = beautifulArray((n + 1) >> 1);  // 奇数部分，长度取上整 (n+1)/2
        vector<int> right = beautifulArray(n >> 1);  // 偶数部分，长度取下整 n/2
        vector<int> ans(n);  // 预分配长度为 n 的结果数组
        int i = 0;  // 结果数组的写指针
        for (int& x : left) ans[i++] = x * 2 - 1;  // 先放奇数部分：x 映射成 2x-1，仍是漂亮数组，且两两之差为偶数
        for (int& x : right) ans[i++] = x * 2;  // 再放偶数部分：x 映射成 2x，偶数与奇数之差恒为奇数，凑不出等差的三元组
        return ans;  // 返回拼接结果
    }
};