// 题目：2031. 1 比 0 多的子数组个数（Count Subarrays With More Ones Than Zeros）
// 思路：把 1 记作 +1、0 记作 -1，求前缀和 s；子数组和大于 0 即「1 比 0 多」，于是转化为统计满足 s[j] > s[i] 的 (i, j) 对数，用树状数组按前缀和的值域动态维护已出现的 s 值，逐位累加比当前 s 小的历史前缀个数。
// 时间复杂度：O(n log n)，每个元素一次查询加一次更新；空间复杂度：O(n)，树状数组长度约 2n+1（另加偏移量避免负下标）。
class BinaryIndexedTree {  // 树状数组（Binary Indexed Tree），维护每个前缀和取值出现的次数
private:  // 以下成员对外不可见
    int n;  // n：树状数组的最大下标（也就是值域上界）
    vector<int> c;  // c：树状数组本体，下标从 1 开始，c[i] 负责区间 (i-lowbit(i), i] 的和

public:  // 以下成员对外可见
    BinaryIndexedTree(int n)  // 构造函数：n 为值域上界
        : n(n)  // 用初始化列表保存上界
        , c(n + 1, 0) {}  // 开 n+1 个桶并全部置 0（下标 0 不用，方便 lowbit 运算）

    void update(int x, int v) {  // 单点更新：把下标 x 处的计数加上 v
        for (; x <= n; x += x & -x) {  // x 不断加上最低位 1，沿「父链」向上更新所有覆盖 x 的节点
            c[x] += v;  // 给覆盖当前位置的节点累加增量
        }  // 继续上跳到下一个父节点
    }  // 更新结束

    int query(int x) {  // 前缀查询：返回下标 1..x 范围内所有计数之和
        int s = 0;  // s 累加答案
        for (; x > 0; x -= x & -x) {  // x 不断减去最低位 1，把 [1, x] 拆成 O(log n) 段快速求和
            s += c[x];  // 累加该段的和
        }  // 继续左跳到下一段
        return s;  // 返回 [1, x] 的计数总和
    }  // 查询结束
};  // 树状数组类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarraysWithMoreZerosThanOnes(vector<int>& nums) {  // nums：只含 0/1 的数组；返回「1 的个数多于 0 的个数」的子数组个数（结果对 1e9+7 取模）
        int n = nums.size();  // 数组长度
        int base = n + 1;  // 偏移量：前缀和可能为负，整体加 base 映射到正整数下标
        BinaryIndexedTree tree(n + base);  // 树状数组大小要覆盖 [-n, n] 全部前缀和取值（偏移后为 1..2n+1）
        tree.update(base, 1);  // 空前缀和 s = 0 先计入，作为所有从下标 0 开始的子数组的左端点
        const int mod = 1e9 + 7;  // 答案要对这个大质数取模
        int ans = 0, s = 0;  // ans 记录子数组个数，s 是当前前缀和
        for (int x : nums) {  // 从左到右遍历数组
            s += (x == 0) ? -1 : 1;  // 1 记 +1、0 记 -1，子数组和为正就表示 1 比 0 多
            ans += tree.query(s - 1 + base);  // 累加以「某个更小的历史前缀」为起点的子数组个数（query 求的是严格小于 s 的前缀个数）
            ans %= mod;  // 每一步都取模，防止溢出
            tree.update(s + base, 1);  // 把当前前缀和计入树状数组，供后面的位置作为左端点使用
        }  // 遍历结束
        return ans;  // 返回满足条件的子数组总数
    }  // 方法结束
};  // 类定义结束