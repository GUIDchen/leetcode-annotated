// 题目：1578. 使绳子变成彩色的最短时间（Minimum Time to Make Rope Colorful）
// 思路：把颜色相同的气球按连续段分组；每一段若长度大于 1，就必须删到只剩一个，最优是保留耗时最长的那个，代价为段内总耗时减去最大耗时。
// 时间复杂度：O(n)，每个气球只被扫描一次；空间复杂度：O(1)，只用常数个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(string colors, vector<int>& neededTime) {  // colors：气球颜色串；neededTime：移除每个气球所需的时间
        int ans = 0;  // 累计的最小移除时间
        int n = colors.size();  // 气球数量
        for (int i = 0, j = 0; i < n; i = j) {  // 按颜色分组扫描：i 是当前组起点，j 是下一组起点，每轮处理完跳到 j
            j = i;  // j 从当前组起点开始向后探测
            int s = 0, mx = 0;  // s 记录本组时间总和，mx 记录本组中的最大时间
            while (j < n && colors[j] == colors[i]) {  // 只要颜色与组首相同，就继续扩大本组
                s += neededTime[j];  // 累加本组总耗时
                mx = max(mx, neededTime[j]);  // 更新本组最大移除时间
                ++j;  // 移到下一个气球
            }  // 内层 while 结束，本组扫描完毕
            if (j - i > 1) {  // 组内多于一个气球就必须移除，直到只剩一个
                ans += s - mx;  // 保留耗时最长的那个，其余全部移除，代价是总和减最大值
            }  // if 分支结束
        }  // 外层 for 每轮结束，i 已跳到下一组起点
        return ans;  // 返回最小总耗时
    }  // 方法结束
};  // 题解类结束