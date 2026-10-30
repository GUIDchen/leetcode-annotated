// 题目：1428. 至少有一个 1 的最左端列（Leftmost Column with at Least a One）
// 思路：每行都是非递减的 0/1 序列，可二分出该行最左的 1；再对所有行取列号最小值。
// 时间复杂度：O(m log n)，m 行各二分一次；空间复杂度：O(1)，只用常数个变量。
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int leftMostColumnWithOne(BinaryMatrix& binaryMatrix) {  // binaryMatrix 是题目给的只读接口，只能通过 get/dimensions 访问
        auto e = binaryMatrix.dimensions();  // dimensions() 返回 {行数, 列数}
        int m = e[0], n = e[1];  // m：行数；n：列数
        int ans = n;  // 答案初值取 n，表示「目前还没找到任何 1」
        for (int i = 0; i < m; ++i) {  // 每一行单独二分，找该行最左的 1
            int l = 0, r = n;  // 二分区间 [l, r)，r 取 n 是「没有 1」的哨兵位置
            while (l < r) {  // 找第一个 1 的下标，即最后一个 0 之后的位置
                int mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
                if (binaryMatrix.get(i, mid)) {  // mid 列是 1，说明答案不晚于 mid
                    r = mid;  // 收缩右边界，继续在左半段找更小的列号
                } else {  // mid 列是 0，说明 1 只可能在 mid 右侧
                    l = mid + 1;  // 收缩左边界并排除 mid 本身
                }  // if/else 结束
            }  // 二分结束，l 就是该行最左 1 的列号（该行没有 1 时为 n）
            ans = min(ans, l);  // 用当前行的结果更新全局最小值
        }  // 行遍历结束
        return ans >= n ? -1 : ans;  // ans 仍为 n 说明整张矩阵没有 1，按题意返回 -1
    }  // 方法结束
};  // 类定义结束