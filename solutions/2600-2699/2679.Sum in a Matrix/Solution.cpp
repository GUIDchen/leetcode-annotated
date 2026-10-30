// 题目：2679. 矩阵中的和（Sum in a Matrix）
// 思路：每轮取走各行当前最大值，得分为这些最大值中的最大者；每行升序排序后，第 j 轮的最大值就是各行的第 j 列。
// 时间复杂度：O(m·n log n)，瓶颈是每行排序；空间复杂度：O(1)，不计排序自身的栈开销。
class Solution {  // 每行排序后逐列取最大值求和
public:  // 对外接口
    int matrixSum(vector<vector<int>>& nums) {  // nums 是 m 行 n 列的矩阵，按行传入
        for (auto& row : nums) {  // 逐行处理
            sort(row.begin(), row.end());  // 行内升序排序：之后这一行被取走的顺序就是从右往左的最大值
        }  // for 结束，此时每行都已有序
        int ans = 0;  // ans 累计每一轮的得分
        for (int j = 0; j < nums[0].size(); ++j) {  // 第 j 轮取的是各行当前最大值，排序后正好是每行的第 j 列
            int mx = 0;  // mx 保存本轮所有行中的最大值（分值非负，从 0 起即可）
            for (auto& row : nums) {  // 扫描所有行，找出这一列的最大值
                mx = max(mx, row[j]);  // 用这一行第 j 列的值更新本轮最大值
            }  // 内层 for 结束
            ans += mx;  // 本轮得分累加进答案
        }  // 外层 for 结束
        return ans;  // 返回矩阵中的总和
    }  // matrixSum 结束
};  // 类定义结束