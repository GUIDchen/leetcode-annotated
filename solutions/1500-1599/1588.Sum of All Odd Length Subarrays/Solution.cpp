// 题目：1588. 所有奇数长度子数组的和（Sum of All Odd Length Subarrays）
// 思路：f[i] 为以 i 结尾的奇数长子数组元素和，g[i] 为以 i 结尾的偶数长子数组元素和，由 i-1 的相反奇偶性转移而来。
// 时间复杂度：O(n)，一次线性递推；空间复杂度：O(n)，两个辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumOddLengthSubarrays(vector<int>& arr) {  // arr：输入数组
        int n = arr.size();  // 数组长度
        vector<int> f(n, arr[0]);  // f[i]：以 i 结尾的奇数长子数组元素和，f[0] 初值即 arr[0]
        vector<int> g(n);  // g[i]：以 i 结尾的偶数长子数组元素和，默认初始化为 0
        int ans = f[0];  // 先把单元素子数组计入答案
        for (int i = 1; i < n; ++i) {  // 从左到右线性递推
            f[i] = g[i - 1] + arr[i] * (i / 2 + 1);  // 偶数长整体 +1 变成奇数长；再加 i/2+1 个以 i 结尾的奇数长子数组
            g[i] = f[i - 1] + arr[i] * ((i + 1) / 2);  // 奇数长整体 +1 变成偶数长；再加 (i+1)/2 个以 i 结尾的偶数长子数组
            ans += f[i];  // 把这批以 i 结尾的奇数长子数组之和累加进答案
        }
        return ans;  // 返回所有奇数长度子数组的元素和
    }
};
