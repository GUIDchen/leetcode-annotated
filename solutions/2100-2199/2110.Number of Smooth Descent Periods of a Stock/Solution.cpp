// 题目：2110. 股票平滑下跌阶段的数目（Number of Smooth Descent Periods of a Stock）
// 思路：把数组切成若干个「相邻元素差恰为 1」的极大连续段；长度为 cnt 的段内任意子段都满足平滑下跌，贡献 cnt*(cnt+1)/2。
// 时间复杂度：O(n)，每段只扫描一次；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long getDescentPeriods(vector<int>& prices) {  // prices 是每日价格，返回所有平滑下跌阶段的数目（总数可能超过 int，用 long long）
        long long ans = 0;  // ans 累计答案，用 long long 防止溢出
        int n = prices.size();  // n 是价格数组长度
        for (int i = 0, j = 0; i < n; i = j) {  // i 是当前连续段的起点，每轮把段起点跳到段末尾 j
            j = i + 1;  // j 至少比 i 大一格（段长先估为 1）
            while (j < n && prices[j - 1] - prices[j] == 1) {  // 只要后一天恰好比前一天低 1，就继续延长这一段
                ++j;  // 段尾后移一格
            }  // 内层循环结束，得到极大平滑下跌段 [i, j)
            int cnt = j - i;  // cnt 是该段长度
            ans += (1LL + cnt) * cnt / 2;  // 长度 cnt 的段内共有 cnt*(cnt+1)/2 个合法子段，累加进答案（先用 1LL 提升为 long long）
        }  // 处理下一段
        return ans;  // 返回平滑下跌阶段总数
    }  // 方法结束
};  // 题解类结束