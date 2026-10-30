// 3915. Maximum Sum of Alternating Subsequence With Distance at Least K | 距离至少为 K 的交替子序列的最大和（困难）
// 核心思路：令 f[i][0/1] 表示以 i 结尾、且最后一步是下降/上升的最优交替子序列和，转移需要在“下标不超过 i-k 且值严格大于/小于 nums[i]”的元素中取最大值；把值离散化后用两棵 max 树状数组维护（bit1 存倒序下标以支持后缀最大值），逐点插入下标 i-k 即可满足距离约束。
// 复杂度：时间 O(n log n)（排序离散化 + 每个元素两次树状数组操作）；空间 O(n)（离散化数组、f 与树状数组）。
class BinaryIndexedTree {  // 树状数组，维护前缀最大值（不是求和）
public:  // 公有接口
    explicit BinaryIndexedTree(int n)  // 构造函数，n 为值域大小
        : n(n)  // 初始化成员 n
        , c(n + 1) {}  // 树状数组本体，有效下标 1..n，初值全 0

    void update(int x, long long val) {  // 单点更新：把 val 计入位置 x 并向上更新
        while (x <= n) {  // 沿着 x += lowbit(x) 一路向上跳
            c[x] = max(c[x], val);  // 每个祖先节点取自身与 val 的较大者
            x += x & -x;  // 跳到父节点
        }  // while 结束
    }  // 方法结束

    long long query(int x) {  // 查询前缀区间 [1, x] 的最大值
        long long ans = 0;  // 空前缀的最大值记为 0，正好作为“不接任何元素”的基准
        while (x > 0) {  // 沿着 x -= lowbit(x) 一路向下跳
            ans = max(ans, c[x]);  // 用当前分块的最大值更新答案
            x -= x & -x;  // 跳到前一个分块
        }  // while 结束
        return ans;  // 返回 [1, x] 的最大值，x 为 0 时返回 0
    }  // 方法结束

private:  // 私有成员
    int n;  // 值域大小
    vector<long long> c;  // 树状数组本体
};  // 类定义结束

class Solution {  // 定义题解类
public:  // 公有接口
    long long maxAlternatingSum(vector<int>& nums, int k) {  // 返回相邻元素下标距离至少为 k 的交替子序列的最大和
        vector<int> sorted = nums;  // 复制一份用于离散化
        ranges::sort(sorted);  // 排序，准备去重
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());  // 去重，得到所有不同的取值
        int m = sorted.size();  // 不同取值的个数，也就是离散化后的值域大小
        auto rank = [&](int x) {  // 定义离散化函数：值 -> 1-based 排名
            return ranges::lower_bound(sorted, x) - sorted.begin() + 1;  // 二分找到第一个不小于 x 的位置，再 +1 得到 1-based 排名
        };  // lambda 结束
        BinaryIndexedTree bit0(m), bit1(m);  // bit0 用正序排名维护 f[..][0]；bit1 用倒序排名维护 f[..][1]，从而把前缀查询变成后缀查询
        int n = nums.size();  // 数组长度
        vector<array<long long, 2>> f(n);  // f[i][0/1]：以 i 结尾、最后一步为下降/上升的最优交替子序列和
        long long ans = 0;  // 全局答案
        for (int i = 0; i < n; ++i) {  // 从左往右枚举每个元素，把它当作子序列的末尾
            if (i >= k) {  // 下标 i-k 与 i 的距离恰好为 k，从这一轮起它才允许作为前驱
                int r = rank(nums[i - k]);  // 前驱 i-k 的离散化排名
                bit0.update(r, f[i - k][0]);  // 把 f[i-k][0] 按正序排名插入 bit0
                bit1.update(m + 1 - r, f[i - k][1]);  // 把 f[i-k][1] 按倒序排名插入 bit1，便于后面查“后缀最大值”
            }  // if 结束
            int r = rank(nums[i]);  // 当前元素的离散化排名
            f[i][0] = nums[i] + bit1.query(m - r);  // 最后一步为下降：接在值严格大于 nums[i] 的前驱之后（倒序下标不超过 m-r）
            f[i][1] = nums[i] + bit0.query(r - 1);  // 最后一步为上升：接在值严格小于 nums[i] 的前驱之后（正序下标不超过 r-1）
            ans = max({ans, f[i][0], f[i][1]});  // 用历史答案与两个新状态一起更新全局答案
        }  // 循环结束
        return ans;  // 返回最大和（单个元素也被允许，因为空区间查询返回 0）
    }  // 方法结束
};  // 类定义结束
