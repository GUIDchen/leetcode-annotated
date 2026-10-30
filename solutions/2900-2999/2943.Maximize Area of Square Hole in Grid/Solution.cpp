// 题目：2943. 最大化网格图中正方形空洞的面积（Maximize Area of Square Hole in Grid）
// 思路：分别把两个方向可移除的杆编号排序，求最长的一段连续整数长度；连续 k 根杆能撑开的空洞边长为 k+1，两个方向取较小边再平方即得面积。
// 时间复杂度：O(h log h + v log v)，来自两次排序；空间复杂度：O(1)，排序原地进行，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {  // n、m 分别是网格行数与列数；hBars、vBars 是允许移除的横杆/竖杆编号
        auto f = [](vector<int>& nums) {  // 局部 lambda：输入某一方向的杆编号，返回该方向能撑开的最大空洞边长
            int ans = 1, cnt = 1;  // ans 记录历史最长的连续段长度，cnt 是当前连续段的长度
            sort(nums.begin(), nums.end());  // 先排序，编号连续的杆才会相邻出现
            for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，逐对比较相邻的杆编号
                if (nums[i] == nums[i - 1] + 1) {  // 相邻两数正好相差 1，说明连续段还能继续延长
                    ans = max(ans, ++cnt);  // 当前连续段长度加一，并用它更新历史最长
                } else {  // 否则连续段在这里被断开
                    cnt = 1;  // 当前连续段长度重置为 1
                }
            }
            return ans + 1;  // 连续 k 根杆能切出的正方形空洞边长是 k + 1
        };  // lambda 定义结束
        int x = min(f(hBars), f(vBars));  // 正方形边长受两个方向中较短的那一边限制
        return x * x;  // 返回边长平方，即正方形空洞的面积
    }
};