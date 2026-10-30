// 题目：2660. 保龄球游戏的获胜者（Determine the Winner of a Bowling Game）
// 核心思路：把计分逻辑抽成一个 lambda，第 i 轮的权重取决于前一轮/前两轮是否打出 10 分（全中），分别算出两人总分再比较。
// 时间复杂度：O(n)，n 为轮数，两人各扫一遍；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int isWinner(vector<int>& player1, vector<int>& player2) {  // player1/player2：两名选手每轮击倒的瓶数，返回获胜者编号
        auto f = [](vector<int>& arr) {  // 定义 lambda：计算单个选手的总分；形参用引用，避免拷贝整个数组
            int s = 0;  // 总分累加器，初值为 0
            for (int i = 0, n = arr.size(); i < n; ++i) {  // 逐轮遍历；i 为轮次下标，n 预先缓存轮数，省去循环里反复取长度
                int k = (i && arr[i - 1] == 10) || (i > 1 && arr[i - 2] == 10) ? 2 : 1;  // 权重 k：若前一轮是 10 分，或前两轮里有 10 分，则本轮得 2 倍分，否则 1 倍
                s += k * arr[i];  // 把本轮瓶数乘以权重后累加进总分
            }  // 循环结束：该选手所有轮次的分数已累加完毕
            return s;  // 返回该选手的保龄球总分
        };  // lambda 定义结束
        int a = f(player1), b = f(player2);  // 分别用 lambda 算出两名选手的总分
        return a > b ? 1 : (b > a ? 2 : 0);  // 选手 1 分高返回 1，选手 2 分高返回 2，打平返回 0
    }  // isWinner 方法结束
};  // 类定义结束（文件末尾无换行，按原样保留）