// 题目：3189. 得到一个和平棋盘的最少步骤（Minimum Moves to Get a Peaceful Board）
// 思路：和平棋盘要求所有车占满互不相同的行和列；把行坐标排序后依次对齐到 0..n-1，列坐标同理，两方向差值绝对值之和即为最小步数。
// 时间复杂度：O(n log n)，两次排序；空间复杂度：O(log n)，仅排序使用的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minMoves(vector<vector<int>>& rooks) {  // rooks：各车的 (行, 列) 坐标，返回使两两不能互攻的最少移动步数
        sort(rooks.begin(), rooks.end());  // 先按行升序排序，把行坐标整理成有序序列
        int ans = 0;  // 累计最少移动步数
        int n = rooks.size();  // 车的数量，也是行、列方向上需要占用的不同坐标数
        for (int i = 0; i < n; ++i) {  // 第 i 辆车最终安排在第 i 行（0 基）
            ans += abs(rooks[i][0] - i);  // 有序行坐标与 0..n-1 逐项对齐取差，就是行方向的最小移动次数
        }  // 行方向处理完毕
        sort(rooks.begin(), rooks.end(), [](const vector<int>& a, const vector<int>& b) {  // 再按列升序排序，列方向可以独立求解
            return a[1] < b[1];  // 比较器：按列坐标从小到大排序
        });  // 排序结束
        for (int j = 0; j < n; ++j) {  // 第 j 辆车最终安排在第 j 列
            ans += abs(rooks[j][1] - j);  // 列方向的最小移动次数累加
        }  // 列方向处理完毕
        return ans;  // 行与列的调整互不影响，总步数就是两部分之和
    }  // 方法结束
};