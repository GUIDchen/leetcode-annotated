// 题目：849. 到最近的人的最大距离（Maximize Distance to Closest Person）
// 思路：记录第一个和最后一个已坐人的位置，并统计相邻两人之间的最大间隔；答案取左端、右端与中间间隔一半三者的最大值。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDistToClosest(vector<int>& seats) {  // seats 中 1 表示已坐人、0 表示空座；返回选一个空座时到最近的人的最大距离
        int first = -1, last = -1;  // first 记录第一个已坐人的位置，last 记录最近一个已坐人的位置，-1 表示还没有
        int d = 0, n = seats.size();  // d 记录相邻两人之间的最大下标差，n 是座位数
        for (int i = 0; i < n; ++i) {  // 从左到右扫描所有座位
            if (seats[i] == 1) {  // 当前位置已经有人
                if (last != -1) {  // 前面已经出现过至少一个已坐人的位置
                    d = max(d, i - last);  // 用当前与上一个已坐人的距离更新最大间隔
                }  // 相邻间隔更新结束
                if (first == -1) {  // 这是第一次遇到已坐人
                    first = i;  // 记下第一个已坐人的位置，用于计算左端点距离
                }  // 首个位置判断结束
                last = i;  // 更新最近一个已坐人的位置
            }  // 已坐人分支结束
        }  // 扫描结束
        return max({d / 2, max(first, n - last - 1)});  // 三者取最大：坐中间时距离是 d/2，坐左端是 first，坐右端是 n-last-1
    }  // 方法结束
};  // 类定义结束