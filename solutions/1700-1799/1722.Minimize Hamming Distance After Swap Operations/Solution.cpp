// 题目：1722. 执行交换操作后的最小汉明距离（Minimize Hamming Distance After Swap Operations）难度：中等
// 思路：把 allowedSwaps 看成无向边，同一下标连通分量内的元素可以任意换位，因此各分量的多重集合固定。
// 对每个分量先统计 source 中各值的出现次数，再用 target 逐个“消耗”同分量的计数：消耗不到就说明该位置必然失配，答案加一。
// 时间复杂度：O(n·α(n) + m)，并查集近似常数（α 为反阿克曼函数），m 为允许交换对数；空间复杂度：O(n)，并查集与计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {  // source/target：两个等长数组；allowedSwaps：可交换的下标对
        int n = source.size();  // 数组长度
        vector<int> p(n);  // 并查集的父节点数组
        iota(p.begin(), p.end(), 0);  // 初始时每个下标自成一个集合
        function<int(int)> find = [&](int x) {  // 带路径压缩的递归查找（用 std::function 保存 lambda）
            return x == p[x] ? x : p[x] = find(p[x]);  // 找到根就返回，否则把父指针直接指向根
        };
        for (auto& a : allowedSwaps) {  // 遍历每一对允许交换的下标
            p[find(a[0])] = find(a[1]);  // 合并两个下标所在的集合：它们可以自由换位
        }
        unordered_map<int, unordered_map<int, int>> cnt;  // cnt[分量根][数值] = source 中该值的出现次数
        for (int i = 0; i < n; ++i) {  // 按分量统计 source 的数值频次
            ++cnt[find(i)][source[i]];  // 把 source[i] 计入它所在分量的计数表
        }
        int ans = 0;  // 最少汉明距离（必须失配的位置数）
        for (int i = 0; i < n; ++i) {  // 再按 target 逐个位置核对
            if (--cnt[find(i)][target[i]] < 0) {  // 用掉一个与该位置同分量、同值的 source 元素
                ++ans;  // 计数被减成负数：本分量没有值可匹配，这个位置一定失配
            }
        }
        return ans;  // 返回最少失配位置个数
    }  // minimumHammingDistance 方法结束
};  // Solution 类结束