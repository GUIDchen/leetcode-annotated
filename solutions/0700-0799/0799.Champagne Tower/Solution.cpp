// 题目：799. 香槟塔（Champagne Tower）
// 思路：按行递推，f[i][j] 表示流经第 i 行第 j 个杯子的香槟量；杯子最多留住 1 杯，超出的部分平分成两半流给下一行的两个杯子，推到查询所在行即可。
// 时间复杂度：O(query_row²)，逐行逐杯递推；空间复杂度：O(1)，固定 101x101 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double champagneTower(int poured, int query_row, int query_glass) {  // poured：总杯数；query_row、query_glass：要查询的杯子坐标
        double f[101][101] = {0.0};  // f[i][j]：流经第 i 行第 j 个杯子的香槟量，行数上界为 100
        f[0][0] = poured;  // 顶端杯子先倒入全部香槟
        for (int i = 0; i <= query_row; ++i) {  // 只需递推到查询所在行
            for (int j = 0; j <= i; ++j) {  // 第 i 行共有 i+1 个杯子
                if (f[i][j] > 1) {  // 只有满溢的杯子才会往下流
                    double half = (f[i][j] - 1) / 2.0;  // 溢出的部分平分给下面两个杯子
                    f[i][j] = 1;  // 自己最多留下 1 杯
                    f[i + 1][j] += half;  // 左下方的杯子分到一半
                    f[i + 1][j + 1] += half;  // 右下方的杯子分到另一半
                }  // 溢流判断结束
            }  // 行内遍历结束
        }  // 行遍历结束
        return f[query_row][query_glass];  // 返回目标杯中的香槟量（未装满时就是流入量）
    }  // champagneTower 结束
};  // 类定义结束