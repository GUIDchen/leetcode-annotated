// 题目：1687. 从仓库到码头运输箱子（Delivering Boxes from Storage to Ports）
// 思路：重量与换港口次数各做前缀和，用 f[i] 表示运完前 i 个箱子的最少行程，枚举最后一趟的起点 j 做区间 DP 转移。
// 时间复杂度：O(n^2) 的区间枚举；空间复杂度：O(n)，重量前缀和、换港口次数前缀和与 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {  // boxes[i] = {ports[i], weight[i]}；maxBoxes / maxWeight 是每趟的两个上限
        int n = boxes.size();  // 箱子总数
        long ws[n + 1];  // ws[i]：前 i 个箱子的重量前缀和（ws[0] = 0）
        int cs[n];  // cs[i]：前 i 个箱子中「相邻箱子港口不同」的次数前缀和
        ws[0] = cs[0] = 0;  // 两个前缀和的起点都初始化为 0
        for (int i = 0; i < n; ++i) {  // 遍历每个箱子，建立前缀和
            int p = boxes[i][0], w = boxes[i][1];  // 取出当前箱子的港口 p 与重量 w
            ws[i + 1] = ws[i] + w;  // 重量前缀和：把当前箱子重量累加进去
            if (i < n - 1) cs[i + 1] = cs[i] + (p != boxes[i + 1][0]);  // 与下一个箱子港口不同则换港口次数 +1；最后一个箱子没有后继，不统计
        }  // 前缀和循环结束
        int f[n + 1];  // f[i]：把前 i 个箱子全部送达所需的最少行程数
        memset(f, 0x3f, sizeof f);  // memset 按字节填充 0x3f，得到一个足够大的「无穷大」初值
        f[0] = 0;  // 空区间不需要任何行程
        for (int i = 1; i <= n; ++i) {  // 按箱子个数从小到大求解
            for (int j = max(0, i - maxBoxes); j < i; ++j) {  // 枚举最后一趟运送的区间 [j, i-1]，下限保证这一段不超过 maxBoxes 个箱子
                if (ws[i] - ws[j] <= maxWeight) {  // 该段重量不超过 maxWeight，才是一次合法的运送
                    f[i] = min(f[i], f[j] + cs[i - 1] - cs[j] + 2);  // 转移：运完前 j 个的代价 + 本段换港口次数 + 2（回仓库一趟、再从仓库出发一趟）
                }  // 合法转移判断结束
            }  // 枚举起点 j 的循环结束
        }  // 外层循环结束
        return f[n];  // 运完 n 个箱子的最优解
    }  // 方法结束
};  // 类结束
