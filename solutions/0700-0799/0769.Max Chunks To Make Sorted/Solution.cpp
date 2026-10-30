// 题目：769. 最多能完成排序的块（Max Chunks To Make Sorted）
// 核心思路：arr 是 0..n-1 的排列，前缀最大值 mx 等于下标 i 时前 i+1 个数正好是 0..i，可以切一刀。
// 时间复杂度 O(n)（一次线性扫描）；空间复杂度 O(1)（只用到两个整型变量）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对判题器可见
    int maxChunksToSorted(vector<int>& arr) {  // arr：0..n-1 的排列；返回最多能切分的块数
        int ans = 0, mx = 0;  // ans 记录块数，mx 记录前缀最大值
        for (int i = 0; i < arr.size(); ++i) {  // 从左到右扫描每个下标 i
            mx = max(mx, arr[i]);  // 更新前 i+1 个元素的最大值
            ans += i == mx;  // 若 mx 等于 i 则表达式取 1，块数加一；否则加 0
        }  // for 循环结束
        return ans;  // 返回最多块数
    }  // 方法结束
};  // 类定义结束