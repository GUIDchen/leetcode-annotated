// 题目：765. 情侣牵手（Couples Holding Hands）
// 思路：把每对情侣看作一个并查集结点，若两个情侣对坐在同一张双人座上就合并；每合并成一个含 k 对的连通块，最少需要 k-1 次交换。
// 时间复杂度：O(n α(n))，并查集近似线性；空间复杂度：O(n)，父数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSwapsCouples(vector<int>& row) {  // row：座位表，元素是每个人编号
        int n = row.size() / 2;  // 情侣对数，也是并查集的大小
        int p[n];  // 并查集父数组（变长数组，判题环境支持）
        iota(p, p + n, 0);  // 初始时每对情侣各自构成一个集合
        function<int(int)> find = [&](int x) -> int {  // 带路径压缩的查找函数
            if (p[x] != x) {  // 当前结点不是根
                p[x] = find(p[x]);  // 递归找到根并顺带压缩路径
            }
            return p[x];  // 返回根结点
        };
        for (int i = 0; i < n << 1; i += 2) {  // 每两个人一组遍历座位
            int a = row[i] >> 1, b = row[i + 1] >> 1;  // 右移一位即除以 2，得到所属情侣对编号
            p[find(a)] = find(b);  // 合并这两个情侣对所在的集合
        }
        int ans = n;  // 先假设每对都要换位，再用连通分量个数修正
        for (int i = 0; i < n; ++i) {  // 统计连通分量个数
            ans -= i == find(i);  // 是根结点就减 1，每个大小为 k 的块正好少换一次
        }
        return ans;  // 返回最少交换次数
    }
};  // 类定义结束（源文件末尾无换行）