// 题目：327. 区间和的个数（Count of Range Sum）
// 思路：前缀和 + 离散化 + 树状数组；对每个右端点 i 统计前面有多少个 s[j] 满足 lower <= s[i]-s[j] <= upper，即 s[j] 落在 [s[i]-upper, s[i]-lower]。
// 时间复杂度：O(n log n)，排序一次、每次二分与树状数组操作都是 O(log n)；空间复杂度：O(n)，前缀和数组、离散化数组与树状数组。
class BinaryIndexedTree {  // 树状数组（Binary Indexed Tree）模板类：按离散化后的值域统计元素个数
public:
    BinaryIndexedTree(int _n)  // 构造函数：_n 是离散化后的值域大小（不同取值个数）
        : n(_n)  // 下标上界，树状数组内部使用 1 起下标
        , c(_n + 1) {}  // 数组开 n+1 个位置，c[0] 空着不用

    void update(int x, int v) {  // 在下标 x 处加 v（这里是加 1，表示某个值出现了一次）
        while (x <= n) {  // 沿 lowbit 方向向上，更新所有覆盖到 x 的位置
            c[x] += v;  // 该位置计数累加 v
            x += x & -x;  // x & -x 取最低位的 1，加上它跳到下一个覆盖位置
        }  // 循环结束
    }  // update 结束

    int query(int x) {  // 求前缀和：统计下标 <= x 的元素个数
        int s = 0;  // 累加器，保存前缀和结果
        while (x) {  // 沿 lowbit 方向向下，把覆盖区间一段段加起来
            s += c[x];  // 累加当前覆盖区间的计数
            x -= x & -x;  // 减去 lowbit，跳到前一个区间
        }  // 循环结束
        return s;  // 返回前缀和
    }  // query 结束

private:  // 以下为内部私有数据
    int n;  // 值域大小（可用的最大下标）
    vector<int> c;  // 树状数组本体，c[i] 存一段区间的计数和
};  // 类定义结束

class Solution {  // LeetCode 约定的题解类
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {  // nums：输入数组；lower/upper：区间和的下界与上界，返回满足条件的子数组个数
        using ll = long long;  // 前缀和可能累加到 1e14 级别，必须用 64 位整数
        int n = nums.size();  // 数组长度 n
        ll s[n + 1];  // 前缀和数组：s[i] 表示前 i 个元素之和（共 n+1 个）
        s[0] = 0;  // 空前缀和为 0，对应「一个元素都不选」
        for (int i = 0; i < n; ++i) {  // 递推计算每一个前缀和
            s[i + 1] = s[i] + nums[i];  // 前 i+1 项和 = 前 i 项和 + 第 i 个数
        }  // 循环结束
        ll arr[(n + 1) * 3];  // 离散化数组：每个前缀和会贡献 3 个可能需要二分的取值
        for (int i = 0, j = 0; i <= n; ++i, j += 3) {  // 同时推进 i（前缀和下标）与 j（离散化数组下标，每步走 3 格）
            arr[j] = s[i];  // 插入树状数组时要用到的值 s[i]
            arr[j + 1] = s[i] - lower;  // 查询左边界 s[i]-lower 也要参与离散化
            arr[j + 2] = s[i] - upper;  // 查询右边界 s[i]-upper 也要参与离散化
        }  // 循环结束
        sort(arr, arr + (n + 1) * 3);  // 排序，之后才能二分查找某个值对应的离散化下标
        int m = unique(arr, arr + (n + 1) * 3) - arr;  // unique 把相邻重复元素移到末尾并返回新结尾，相减得到不同值的个数 m
        BinaryIndexedTree tree(m);  // 用值域大小 m 建立树状数组
        int ans = 0;  // 答案：满足 lower <= 区间和 <= upper 的子数组个数
        for (int i = 0; i <= n; ++i) {  // 枚举每个前缀和作为区间右端点，统计它前面有多少个前缀和落在窗口内
            int l = lower_bound(arr, arr + m, s[i] - upper) - arr + 1;  // 历史前缀和需满足 s[j] >= s[i]-upper，二分出它的下标（转成 1 起）
            int r = lower_bound(arr, arr + m, s[i] - lower) - arr + 1;  // 历史前缀和还需满足 s[j] <= s[i]-lower，二分出右端下标（转成 1 起）
            ans += tree.query(r) - tree.query(l - 1);  // 两次前缀和相减，得到值落在 [l, r] 内的历史前缀和个数，累加进答案
            tree.update(lower_bound(arr, arr + m, s[i]) - arr + 1, 1);  // 把当前前缀和 s[i] 插入树状数组，供后面的右端点查询
        }  // 循环结束
        return ans;  // 返回统计结果
    }  // 方法结束
};  // 类结束