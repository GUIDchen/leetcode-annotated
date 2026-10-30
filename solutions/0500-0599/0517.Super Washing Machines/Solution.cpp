// 题目：517. 超级洗衣机（Super Washing Machines）
// 思路：先判断能否均分；再从左到右扫描，用前缀和表示穿过当前边界的净流量，答案取「前缀和绝对值」与「单台机器盈余」的最大值。
// 时间复杂度：O(n)，一次求和加一次扫描；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findMinMoves(vector<int>& machines) {  // 返回使各台机器衣服数相等所需的最少轮数
        int n = machines.size();  // 机器数量
        int s = accumulate(machines.begin(), machines.end(), 0);  // 统计所有机器上的衣服总数
        if (s % n) {  // 总数不能被机器数整除，就永远无法均分
            return -1;  // 题目约定不可行时返回 -1
        }  // 不可行分支结束
        int k = s / n;  // k 是均分后每台机器应有的衣服数
        s = 0;  // 复用 s 作为前缀和，表示从左边流过来的净流量
        int ans = 0;  // 记录答案：所需的最少轮数
        for (int x : machines) {  // 从左到右扫描每台机器
            x -= k;  // 换算成该机器的盈余（正）或缺口（负）
            s += x;  // 更新前缀和：左边累计需要穿过当前位置的净流动量
            ans = max({ans, abs(s), x});  // 轮数取三者最大：已有答案、前缀流量绝对值、本机盈余
        }  // 扫描结束
        return ans;  // 返回最少轮数
    }  // 方法结束
};  // 类定义结束