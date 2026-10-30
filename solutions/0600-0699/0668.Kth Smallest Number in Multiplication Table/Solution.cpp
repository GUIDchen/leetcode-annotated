// 题目：668. 乘法表中第 k 小的数（Kth Smallest Number in Multiplication Table）
// 思路：在数值区间 [1, m*n] 上二分答案，统计乘法表中 ≤ mid 的数字个数；个数 ≥ k 说明答案不超过 mid，否则答案更大。
// 时间复杂度：O(m log(mn))，二分 log(mn) 轮、每轮统计 O(m)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    int findKthNumber(int m, int n, int k) {  // 返回 m × n 乘法表中按非递减顺序的第 k 个数
        int left = 1, right = m * n;  // 二分答案的上下界：最小 1，最大 m*n
        while (left < right) {  // 闭区间二分，区间缩到单点即答案
            int mid = (left + right) >> 1;  // 取中点，右移一位等价于除以 2
            int cnt = 0;  // 统计表中 ≤ mid 的数字个数
            for (int i = 1; i <= m; ++i) cnt += min(mid / i, n);  // 第 i 行的数是 i, 2i, …, n*i；不超过 mid 的有 min(mid/i, n) 个
            if (cnt >= k)  // 个数已经够 k 个，说明第 k 小的数不超过 mid
                right = mid;  // 收紧右界
            else  // 否则第 k 小的数一定大于 mid
                left = mid + 1;  // 收紧左界
        }
        return left;  // left == right 时就是第 k 小的数
    }  // 结束 findKthNumber
};