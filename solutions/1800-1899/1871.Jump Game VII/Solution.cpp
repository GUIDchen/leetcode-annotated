// 题目：1871. 跳跃游戏 VII（Jump Game VII）
// 思路：f[i] 表示能否跳到 i，用前缀和把「区间 [i-maxJump, i-minJump] 内是否存在可达点」的查询压缩到 O(1)。
// 时间复杂度：O(n)，每个位置只被推导一次；空间复杂度：O(n)，需要存 f 数组与前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canReach(string s, int minJump, int maxJump) {  // s：只含 '0'/'1' 的字符串；minJump/maxJump：每次可跳距离的范围
        int n = s.size();  // 字符串长度
        vector<int> pre(n + 1);  // 前缀和数组：pre[k] = f[0..k-1] 中可达位置的数量
        pre[1] = 1;  // 起点 0 必然可达，所以前 1 个位置的可达计数为 1
        vector<bool> f(n);  // f[i] 表示能否从起点跳到下标 i
        f[0] = true;  // 起点自身可达
        for (int i = 1; i < n; ++i) {  // 按下标从小到大递推每个位置
            if (s[i] == '0') {  // 只能落在 '0' 上，'1' 位置直接不可达
                int l = max(0, i - maxJump);  // 可能的起跳下标下界
                int r = i - minJump;  // 可能的起跳下标上界
                f[i] = l <= r && pre[r + 1] - pre[l];  // 区间 [l, r] 内存在可达点则 i 可达（前缀和差值非零）
            }  // 结束 if
            pre[i + 1] = pre[i] + f[i];  // 把当前位置的可达性并入前缀和
        }  // 结束 for
        return f[n - 1];  // 终点是否可达就是答案
    }  // 结束方法
};  // 结束类