// 4051. 统计遥远子数组的数目（Count Subarrays with Distant Sums）
// 核心思路：先求前缀和，再用树状数组按值域统计与 goal 距离不足 k 的右端点对，从全部子数组中扣除
// 复杂度：时间 O(n log n)，空间 O(n)
class BinaryIndexedTree {  // 封装树状数组（Fenwick 树），支持单点加与前缀和查询
    int n;  // 树状数组的下标上限
    vector<long long> c;  // 树状数组本体，采用 1 基下标

public:  // 对外接口
    BinaryIndexedTree(int n)  // 构造函数，n 为可用下标的最大值
        : n(n)  // 记录长度上限
        , c(n + 1) {}  // 开辟 n + 1 个桶并全部初始化为 0

    void update(int x, long long delta) {  // 在下标 x 处加上 delta
        while (x <= n) {  // 沿 lowbit 一路向上更新到树根
            c[x] += delta;  // 当前节点累加增量
            x += x & -x;  // 跳到下一个覆盖该位置的节点
        }  // 向上更新结束
    }  // update 方法结束

    long long query(int x) {  // 查询区间 [1, x] 的前缀和
        long long s = 0;  // 累加器从 0 开始
        while (x) {  // 沿 lowbit 逐步下跳，直到下标归零
            s += c[x];  // 累加当前块的值
            x -= x & -x;  // 跳到前一个互不重叠的块
        }  // 累加过程结束
        return s;  // 返回前缀和
    }  // query 方法结束
};  // 树状数组定义结束

class Solution {  // 题解主类
public:  // 对外接口
    long long distantSubarrays(vector<int>& nums, int goal, int k) {  // 统计满足条件的子数组个数
        int n = nums.size();  // 数组长度
        vector<long long> s(n + 1);  // 前缀和数组，多留一位存放空前缀 0

        for (int i = 0; i < n; i++) {  // 递推构造前缀和
            s[i + 1] = s[i] + nums[i];  // 前缀和转移：前 i 项之和加上第 i 个数
        }  // 构造前缀和结束

        vector<long long> st = s;  // 复制一份前缀和用于离散化
        sort(st.begin(), st.end());  // 排序得到有序值表，便于二分出下标

        long long ans = 1LL * n * (n + 1) / 2;  // 先按全部子数组计数，之后逐个扣除不合法的
        BinaryIndexedTree bit(st.size() + 1);  // 树状数组按离散化后的值域大小开空间

        for (long long v : s) {  // 以当前前缀和作为右端点 v，逐个处理
            long long a = v - goal - k + 1LL;  // 需要扣除的窗口左端 a：与 goal 距离不足 k 的前缀和从这里开始
            long long b = v - goal + k - 1LL;  // 需要扣除的窗口右端 b：到这个值为止都算距离不足

            int l = lower_bound(st.begin(), st.end(), a) - st.begin() + 1;  // 二分得到窗口左端在有序表中的 1 基下标
            int r = lower_bound(st.begin(), st.end(), b + 1) - st.begin();  // 第一个大于 b 的位置恰是闭区间右端的 1 基下标

            if (l <= r) {  // 窗口非空才有需要扣除的对象
                ans -= bit.query(r) - bit.query(l - 1);  // 减去已插入树状数组中落在窗口内的前缀和个数
            }  // 窗口统计结束

            int pos = lower_bound(st.begin(), st.end(), v) - st.begin() + 1;  // 当前前缀和离散化后的 1 基下标
            bit.update(pos, 1);  // 把当前前缀和插入树状数组，供后续右端点查询
        }  // 枚举右端点结束

        return ans;  // 返回满足条件的子数组数目
    }  // 方法结束
};  // 类结束