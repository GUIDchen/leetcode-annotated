// 题目：1725. 可以形成最大正方形的矩形数目（Number Of Rectangles That Can Form The Largest Square）
// 思路：正方形的边长受矩形较短边限制，所以每个矩形能贡献的边长为 min(长, 宽)；边遍历边维护最大边长及其出现次数。
// 时间复杂度：O(n)，每个矩形只处理一次；空间复杂度：O(1)，只用了两个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countGoodRectangles(vector<vector<int>>& rectangles) {  // rectangles：每个二元组是一条矩形的长与宽
        int ans = 0, mx = 0;  // ans 记录最大边长出现的次数，mx 记录目前遇到的最大边长
        for (auto& e : rectangles) {  // 逐个矩形处理，e 是长宽二元组
            int x = min(e[0], e[1]);  // 该矩形能切出的最大正方形边长取长与宽的较小值
            if (mx < x) {  // 出现了比当前记录更大的正方形
                mx = x;  // 更新最大边长
                ans = 1;  // 旧的最大值失效，计数从 1 重新开始
            } else if (mx == x) {  // 与当前最大边长相等，说明这条矩形也能形成最大正方形
                ++ans;  // 计数加一
            }  // 小于 mx 的矩形无法形成最大正方形，直接忽略
        }  // 遍历结束
        return ans;  // 返回能形成最大正方形的矩形数目
    }  // 方法结束
};  // 类结束