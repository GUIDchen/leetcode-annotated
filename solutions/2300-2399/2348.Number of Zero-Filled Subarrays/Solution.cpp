// 题目：2348. 全 0 子数组的数目（Number of Zero-Filled Subarrays）
// 思路：用 cnt 记录以当前位置结尾的连续 0 的个数，它对答案的贡献正好是 cnt，累加即得所有全 0 子数组数目。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了两个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long zeroFilledSubarray(vector<int>& nums) {  // nums 为输入数组
        long long ans = 0;  // 答案可能达到 O(n^2) 量级，必须用 64 位整数
        int cnt = 0;  // 以当前元素结尾的连续 0 的个数
        for (int x : nums) {  // 顺序扫描每个元素
            if (x == 0) {  // 当前元素是 0，连续段延长
                ans += ++cnt;  // 先把 cnt 加一，再把「以当前 0 结尾的全 0 子数组个数」计入答案
            } else {  // 遇到非 0，连续段被打断
                cnt = 0;  // 归零，后续重新开始计数
            }
        }
        return ans;  // 返回全 0 子数组的总数
    }
};
