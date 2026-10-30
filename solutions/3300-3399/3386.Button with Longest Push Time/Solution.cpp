// 题目：3386. 按下时间最长的按钮（Button with Longest Push Time）
// 思路：相邻两次按键的时刻差就是后一个按钮的按下时长，一次遍历取最大；时长相同则取按钮编号更小的。
// 时间复杂度：O(n)，只扫一遍事件数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int buttonWithLongestTime(vector<vector<int>>& events) {  // events[k] = [按钮编号, 按下时刻]，返回按下时间最长的按钮编号
        int ans = events[0][0], t = events[0][1];  // 初始化：第一个按钮的编号，以及它从 0 时刻按下的耗时
        for (int k = 1; k < events.size(); ++k) {  // 从第二个按键开始遍历
            int i = events[k][0], t2 = events[k][1], t1 = events[k - 1][1];  // i：本次按钮编号；t2：本次时刻；t1：上一次时刻
            int d = t2 - t1;  // d：这次按钮被按住的时长
            if (d > t || (d == t && ans > i)) {  // 时长更长则胜出；时长相同则取编号更小的按钮
                ans = i;  // 更新答案按钮编号
                t = d;  // 同步更新当前最长时长
            }
        }
        return ans;  // 返回按下时间最长的按钮编号
    }
};  // 题解类定义结束
