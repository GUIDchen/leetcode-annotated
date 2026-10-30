// 题目：667. 优美的排列 II（Beautiful Arrangement II）
// 思路：前 k 个位置左右交替取最小/最大值，制造出 k 个不同的相邻差 k, k-1, …, 1；剩下的位置按指针顺序单调填充，差值恒为 1。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，存放构造结果。
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    vector<int> constructArray(int n, int k) {  // 构造 1..n 的排列，使相邻元素差值恰好有 k 种
        int l = 1, r = n;  // 双指针：l 是未用的最小值，r 是未用的最大值
        vector<int> ans(n);  // 结果数组，按下标依次填充
        for (int i = 0; i < k; ++i) {  // 前 k 个位置左右交替取值
            ans[i] = i % 2 == 0 ? l++ : r--;  // 偶数位取小端、奇数位取大端，相邻差依次为 k, k-1, …, 1
        }
        for (int i = k; i < n; ++i) {  // 剩余位置从当前指针开始单调填充
            ans[i] = k % 2 == 0 ? r-- : l++;  // k 为偶数时上一轮停在大端，要从 r 递减填才能保持差值为 1；奇数时反之
        }
        return ans;  // 返回构造好的排列
    }
};