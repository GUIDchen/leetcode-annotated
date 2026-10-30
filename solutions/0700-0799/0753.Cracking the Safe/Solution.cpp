// 题目：753. 破解保险箱（Cracking the Safe）——困难
// 思路：把「n-1 位前缀」看作结点、把「加一位数字」看作有向边，答案就是一条欧拉回路；用 Hierholzer 深搜，回溯时把数字追加到答案末尾。
// 时间复杂度：O(k^n)，每条边（共 k^n 条）恰好访问一次；空间复杂度：O(k^n)，访问集合与答案串的规模均与边数同阶。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    string crackSafe(int n, int k) {  // n 是密码位数，k 是数字种类（0~k-1）
        unordered_set<int> vis;  // 记录已经走过的边（用整数编码的 n 位数）
        int mod = pow(10, n - 1);  // 10^(n-1)，用来截取后 n-1 位作为下一个结点
        string ans;  // 逆序累积访问到的边，最后反转成答案
        function<void(int)> dfs = [&](int u) {  // u 是当前所在的 n-1 位前缀
            for (int x = 0; x < k; ++x) {  // 尝试给前缀接上数字 x
                int e = u * 10 + x;  // 边 / 完整 n 位串的整数编码
                if (!vis.count(e)) {  // 这条边还没走过
                    vis.insert(e);  // 先标记为已访问，保证每条边只用一次
                    dfs(e % mod);  // 递归进入「后 n-1 位」这个新结点
                    ans += (x + '0');  // 回溯时再追加数字：这样得到的序列只差开头 n-1 个 0
                }
            }
        };
        dfs(0);  // 从全 0 前缀出发，图是连通的所以一次深搜能覆盖所有边
        ans += string(n - 1, '0');  // 补齐开头缺失的 n-1 个 0，形成完整密码
        return ans;  // 返回构造出的合法密码
    }
};