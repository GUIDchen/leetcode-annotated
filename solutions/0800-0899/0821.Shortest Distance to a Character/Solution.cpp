// 题目：821. 字符的最短距离（Shortest Distance to a Character）
// 思路：两次扫描。左扫记录最近一次出现 c 的位置，得到向左的最短距离；右扫同理得到向右的距离，两轮取较小值即为答案。
// 时间复杂度：O(n)，只扫描两遍；空间复杂度：O(n)，返回所用数组（不计返回值则为 O(1)）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> shortestToChar(string s, char c) {  // s：给定字符串；c：目标字符
        int n = s.size();  // 字符串长度
        const int inf = 1 << 30;  // 一个足够大的数，用来表示「无穷远」的距离
        vector<int> ans(n, inf);  // ans[i] 表示位置 i 到最近 c 的距离，先初始化为无穷大
        for (int i = 0, pre = -inf; i < n; ++i) {  // 从左往右扫，pre 记录最近一次出现 c 的下标（初始为 -inf）
            if (s[i] == c) {  // 当前位置就是目标字符
                pre = i;  // 更新最近出现的位置
            }  // if 结束
            ans[i] = min(ans[i], i - pre);  // 与左侧最近的 c 的距离
        }  // 左扫结束
        for (int i = n - 1, suf = inf; ~i; --i) {  // 从右往左扫，suf 记录右侧最近一次出现 c 的下标
            if (s[i] == c) {  // 当前位置就是目标字符
                suf = i;  // 更新最近出现的位置
            }  // if 结束
            ans[i] = min(ans[i], suf - i);  // 与右侧最近的 c 的距离，与左扫结果取较小值
        }  // 右扫结束
        return ans;  // 返回每个位置的最短距离
    }  // shortestToChar 方法结束
};  // Solution 类结束