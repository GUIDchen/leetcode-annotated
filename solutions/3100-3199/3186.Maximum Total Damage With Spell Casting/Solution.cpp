// 题目：3186. 施咒的最大总伤害（Maximum Total Damage With Spell Casting）
// 思路：排序后按「相同伤害值」分组，记忆化搜索每个位置：要么整组跳过，要么整组全选并跳到第一个大于 power[i]+2 的位置，取两者最大值。
// 时间复杂度：O(n log n)，排序与二分；空间复杂度：O(n)，记忆化数组与辅助数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumTotalDamage(vector<int>& power) {  // power：每个法术的伤害值，返回施法能获得的最大总伤害
        sort(power.begin(), power.end());  // 升序排序：让相同伤害相邻，同时支持二分查找
        this->power = power;  // 复制到成员变量，供下面的私有 dfs 使用
        n = power.size();  // 记录数组长度，dfs 里用来判越界
        f.resize(n);  // 记忆化数组：f[i] 表示从下标 i 开始能取得的最大伤害（0 表示未计算）
        nxt.resize(n);  // 预处理数组：nxt[i] 是选完 power[i] 这一组后可跳到的下标
        for (int i = 0; i < n; ++i) {  // 遍历每个位置，统计频次并预处理后继下标
            cnt[power[i]]++;  // 统计该伤害值一共有多少个法术
            nxt[i] = upper_bound(power.begin() + i + 1, power.end(), power[i] + 2) - power.begin();  // 二分找出第一个大于 power[i]+2 的下标，作为「已选当前值」时的下一位置
        }  // 预处理结束
        return dfs(0);  // 从最小伤害值开始做记忆化搜索
    }  // 方法结束

private:  // 以下是内部状态与辅助函数
    unordered_map<int, int> cnt;  // 每个伤害值对应的法术个数
    vector<long long> f;  // 记忆化数组：f[i] 为从下标 i 开始的最大伤害
    vector<int> power;  // 升序排列后的伤害值数组（含重复元素）
    vector<int> nxt;  // nxt[i]：选完 power[i] 这一组后可直接跳到的最小下标
    int n;  // 数组长度

    long long dfs(int i) {  // 记忆化搜索：只考虑下标 i 及其之后的最大伤害
        if (i >= n) {  // 下标越界说明没有法术可选了
            return 0;  // 边界：收益为 0
        }  // 边界判断结束
        if (f[i]) {  // 已经算过就直接复用（伤害为正，所以 0 一定表示未计算）
            return f[i];  // 返回记忆化结果
        }  // 记忆化判断结束
        long long a = dfs(i + cnt[power[i]]);  // 方案一：这一种伤害一个都不选，直接跳过同值的整组
        long long b = 1LL * power[i] * cnt[power[i]] + dfs(nxt[i]);  // 方案二：同值法术全选（伤害为正，多选只赚不亏），再跳到与它差值超过 2 的位置
        return f[i] = max(a, b);  // 两种方案取较大者，并写入记忆化数组
    }  // 辅助函数结束
};
