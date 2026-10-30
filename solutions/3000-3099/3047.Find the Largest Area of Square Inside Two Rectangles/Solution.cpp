// 题目：3047. 求交集区域内的最大正方形面积（Find the Largest Area of Square Inside Two Rectangles）
// 核心思路：枚举每一对矩形，用 min(右边界) - max(左边界)、min(上边界) - max(下边界) 求交集宽高，正方形边长取较小值，累计最大面积。
// 时间复杂度：O(n^2)，两两枚举矩形；空间复杂度：O(1)，只用常数个中间变量。
class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {  // bottomLeft、topRight：每个矩形的左下角与右上角坐标，返回任意两个矩形交集内最大正方形的面积
        long long ans = 0;  // ans：目前找到的最大正方形面积；答案可能超过 int 所以用 long long
        for (int i = 0; i < bottomLeft.size(); ++i) {  // 枚举第一个矩形 i
            int x1 = bottomLeft[i][0], y1 = bottomLeft[i][1];  // x1、y1：第 i 个矩形的左下角坐标
            int x2 = topRight[i][0], y2 = topRight[i][1];  // x2、y2：第 i 个矩形的右上角坐标
            for (int j = i + 1; j < bottomLeft.size(); ++j) {  // 只枚举 j > i，每对矩形只处理一次
                int x3 = bottomLeft[j][0], y3 = bottomLeft[j][1];  // x3、y3：第 j 个矩形的左下角坐标
                int x4 = topRight[j][0], y4 = topRight[j][1];  // x4、y4：第 j 个矩形的右上角坐标
                int w = min(x2, x4) - max(x1, x3);  // 交集宽度：两个右边界取小、两个左边界取大再相减；为负说明不相交
                int h = min(y2, y4) - max(y1, y3);  // 交集高度：同理用上下边界计算
                int e = min(w, h);  // 正方形边长受宽高共同限制，取两者的较小值
                if (e > 0) {  // 边长为正才说明两个矩形确实有交集面积
                    ans = max(ans, 1LL * e * e);  // 面积用 1LL 强制转成 long long 再相乘，避免 int 溢出
                }
            }
        }
        return ans;  // 返回找到的最大正方形面积，没有任何交集时为 0
    }  // 方法结束
};  // 题解类结束