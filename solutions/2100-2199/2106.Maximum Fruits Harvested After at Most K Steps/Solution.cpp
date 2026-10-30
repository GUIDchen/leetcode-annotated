// 题目：2106. 摘水果（Maximum Fruits Harvested After at Most K Steps）
// 思路：把有水果的位置按坐标排序后做滑动窗口 [i, j]；走遍该区间的最短步数是「区间宽度 + min(起点到左端, 起点到右端)」，超过 k 就收缩左端。
// 时间复杂度：O(n)，窗口左右端各只前进一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {  // fruits：{位置, 水果数} 组成的有序数组；startPos：起点；k：最多步数
        int ans = 0, s = 0;  // ans 记录答案，s 维护当前窗口内的水果总数
        for (int i = 0, j = 0; j < fruits.size(); ++j) {  // j 是窗口右端，从左往右扩展；i 是窗口左端
            int pj = fruits[j][0], fj = fruits[j][1];  // 取出右端位置 pj 与该位置的水果数 fj
            s += fj;  // 把右端的水果全部纳入窗口
            while (i <= j && pj - fruits[i][0] + min(abs(startPos - fruits[i][0]), abs(startPos - pj)) > k) {  // 走到覆盖 [左侧位置, pj] 这段至少需要区间长度加上从起点走近的那一端的距离，超预算就收缩左端
                s -= fruits[i++][1];  // 把左端的水果从窗口里移除，并让左端右移一格
            }  // 收缩结束，此时窗口可达
            ans = max(ans, s);  // 用当前窗口水果数更新最优答案
        }  // 右端遍历结束
        return ans;  // 返回最多能摘到的水果数
    }  // 方法结束
};  // 题解类结束