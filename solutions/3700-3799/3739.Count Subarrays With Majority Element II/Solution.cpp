// 题目：3739. 统计主要元素子数组数目 II（Count Subarrays With Majority Element II）
// 核心思路：把 target 记 +1、其余元素记 -1 求前缀和，子数组里 target 是严格多数等价于该子数组的和大于 0，也就是右端前缀和严格大于左端前缀和；用树状数组统计「此前出现过的更小前缀和」个数，边扫边累加答案。
// 复杂度：时间 O(n log n)，每步一次查询加一次更新；空间 O(n)，树状数组开 2n+1 个位置。
class BinaryIndexedTree {  // 树状数组：支持单点加、前缀和查询
private:  // 内部数据
    int n;  // 下标上界
    vector<int> c;  // 树状数组本体，逻辑下标从 1 开始

public:  // 对外接口
    BinaryIndexedTree(int n)  // 构造函数，n 为下标上界
        : n(n)  // 记录上界
        , c(n + 1, 0) {}  // 开 n+1 个位置并全部清零

    void update(int x, int delta) {  // 把位置 x 加上 delta
        for (; x <= n; x += x & -x) {  // 沿 lowbit 向上跳，覆盖所有包含 x 的结点
            c[x] += delta;  // 把增量累加到当前结点
        }  // 更新循环结束
    }  // update 方法结束

    int query(int x) {  // 求前缀和 [1, x]
        int s = 0;  // 累加器
        for (; x > 0; x -= x & -x) {  // 沿 lowbit 向下跳，x 减到 0 结束
            s += c[x];  // 累加当前结点
        }  // 查询循环结束
        return s;  // 返回前缀和
    }  // query 方法结束
};  // 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countMajoritySubarrays(vector<int>& nums, int target) {  // nums：整数数组；target：要求成为严格主要元素的取值；返回满足条件的子数组个数
        int n = nums.size();  // 数组长度
        BinaryIndexedTree tree(2 * n + 1);  // 前缀和取值约在 [-n, n]，整体平移后树状数组开 2n+1 个位置
        int s = n + 1;  // 当前前缀和（已平移），空前缀记为 n+1
        tree.update(s, 1);  // 空前缀出现一次，先插入统计
        long long ans = 0;  // 记录答案
        for (int x : nums) {  // 逐个元素扫描，把以当前位置结尾的子数组一次性统计完
            s += (x == target ? 1 : -1);  // target 记 +1，其余元素记 -1
            ans += tree.query(s - 1);  // 此前出现的严格更小的前缀和个数，就是以当前位置结尾的合法子数组数
            tree.update(s, 1);  // 把当前前缀和计入统计，供后面的位置使用
        }  // 扫描结束
        return ans;  // 返回满足「target 数量严格过半」的子数组总数
    }  // 方法结束
};  // 类定义结束
