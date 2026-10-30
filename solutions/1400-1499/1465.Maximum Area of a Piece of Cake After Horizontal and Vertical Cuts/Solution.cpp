// 题目：1465. 切割后面积最大的蛋糕（Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts）
// 核心思路：把 0 与 h（或 w）当作虚拟切线一起排序，最大块面积等于水平方向最大间距与垂直方向最大间距之积，最后对 1e9+7 取模。
// 时间复杂度：O(m log m + n log n)，瓶颈在两次排序；空间复杂度：O(1)，只在原数组上追加元素并使用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {  // h、w 是蛋糕的高与宽；两个数组分别是水平、垂直方向的切线位置
        horizontalCuts.push_back(0);  // 补上蛋糕上边界，作为第一条虚拟切线
        horizontalCuts.push_back(h);  // 补上蛋糕下边界，作为最后一条虚拟切线
        verticalCuts.push_back(0);  // 补上蛋糕左边界
        verticalCuts.push_back(w);  // 补上蛋糕右边界
        sort(horizontalCuts.begin(), horizontalCuts.end());  // 排序后相邻两线之差就是各水平块的高度
        sort(verticalCuts.begin(), verticalCuts.end());  // 排序后相邻两线之差就是各垂直块的宽度
        int x = 0, y = 0;  // x、y 分别记录水平最大高度与垂直最大宽度
        for (int i = 1; i < horizontalCuts.size(); ++i) {  // 从第二条切线开始，与它的前一条比较
            x = max(x, horizontalCuts[i] - horizontalCuts[i - 1]);  // 用当前间距更新最大高度
        }  // 水平方向统计结束
        for (int i = 1; i < verticalCuts.size(); ++i) {  // 垂直方向用同样的方式统计
            y = max(y, verticalCuts[i] - verticalCuts[i - 1]);  // 用当前间距更新最大宽度
        }  // 垂直方向统计结束
        const int mod = 1e9 + 7;  // 题目要求对 1e9+7 取模
        return (1ll * x * y) % mod;  // 先转 long long 再相乘，避免 int 溢出，最后取模
    }  // 方法结束
};  // 类定义结束