// 题目：1713. 得到子序列的最少操作次数（Minimum Operations to Make a Subsequence）
// 思路：把 target 的值映射成 1 基下标，取出 arr 中命中 target 的那些下标组成序列；它的最长上升子序列长度 L 就是 target 与 arr 的最长公共子序列长度，答案 = m - L，LIS 用树状数组优化。
// 时间复杂度：O((n + m) log m)，n、m 分别是 arr、target 的长度；空间复杂度：O(m)。
class BinaryIndexedTree {  // 树状数组：维护前缀最大值，用于在 O(log m) 内求 LIS 转移
private:  // 以下为内部数据成员
    int n;  // 树状数组的下标上界
    vector<int> c;  // 树状数组本体，c[i] 保存区间 (i - lowbit(i), i] 的最大值

public:  // 对外提供的接口
    BinaryIndexedTree(int n)  // 构造函数：上界为 n，内部下标从 1 开始
        : n(n)  // 记录上界，供 update 与 query 使用
        , c(n + 1) {}  // 多开一格并清零，避免下标 1 越界

    void update(int x, int v) {  // 把位置 x 的最优值更新为 v（与原值取最大）
        for (; x <= n; x += x & -x) {  // 沿 lowbit 依次跳到所有覆盖 x 的节点
            c[x] = max(c[x], v);  // 每个覆盖节点都用 v 尝试更新
        }
    }

    int query(int x) {  // 查询前缀 [1, x] 的最大值
        int ans = 0;  // 空集的最大值记为 0
        for (; x > 0; x -= x & -x) {  // 沿 lowbit 把前缀拆成若干段
            ans = max(ans, c[x]);  // 逐段合并最大值
        }
        return ans;  // 返回前缀最大值，即 LIS 转移来源
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(vector<int>& target, vector<int>& arr) {  // target：目标序列；arr：给定序列
        int m = target.size();  // target 的长度，也是答案的基准值
        unordered_map<int, int> d;  // 哈希表：值 → 它在 target 中的下标（从 1 开始计）
        for (int i = 0; i < m; ++i) {  // 遍历 target 建立「值 → 下标」映射
            d[target[i]] = i + 1;  // 下标加 1，方便树状数组使用 1 基下标
        }
        vector<int> nums;  // 收集 arr 中能匹配上 target 的值所对应的下标
        for (int x : arr) {  // 遍历 arr 的每个元素
            if (d.contains(x)) {  // C++20 的 contains：判断该值是否在 target 中出现过
                nums.push_back(d[x]);  // 记录它在 target 中的位置，得到待求 LIS 的序列
            }
        }
        BinaryIndexedTree tree(m);  // 树状数组大小取 target 的长度
        int ans = 0;  // 记录最长上升子序列（即最长公共子序列）的长度
        for (int x : nums) {  // 依次处理映射后的下标序列
            int v = tree.query(x - 1) + 1;  // 严格上升：只能接在比 x 小的位置后面，故查前缀 x-1
            ans = max(ans, v);  // 更新当前最优 LIS 长度
            tree.update(x, v);  // 把以 x 结尾的最优长度写入树状数组
        }
        return m - ans;  // target 中不在 LIS 里的元素都需要插入，插入次数即答案
    }
};