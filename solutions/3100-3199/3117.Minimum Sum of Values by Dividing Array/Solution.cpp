// 题目：3117. 划分数组得到最小的值之和（Minimum Sum of Values by Dividing Array）
// 思路：记忆化搜索 dfs(i, j, a)：前 i 个数已切成 j 段、当前段按位与为 a，每步可选「并入当前段」或「按位与达标后切段」。
// 时间复杂度：O(n·m·log V)，按位与只减不增使状态数受控；空间复杂度：O(n·m·log V)，记忆化哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {  // nums：原数组；andValues：每个分组的目标按位与值
        this->nums = nums;  // 把输入数组存进成员变量，供 dfs 直接访问
        this->andValues = andValues;  // 把目标与值数组存进成员变量
        n = nums.size();  // 记录数组长度
        m = andValues.size();  // 记录目标分组数
        int ans = dfs(0, 0, -1);  // 从下标 0、第 0 组、按位与初值 -1（全 1）开始记忆化搜索
        return ans >= inf ? -1 : ans;  // 搜不到可行划分（结果为 inf）时按题目要求返回 -1
    }  // 结束 minimumValueSum

private:  // 以下为私有成员与递归辅助函数
    vector<int> nums;  // 成员：原数组
    vector<int> andValues;  // 成员：目标按位与值数组
    int n;  // 成员：数组长度
    int m;  // 成员：目标分组数
    const int inf = 1 << 29;  // 用一个足够大的数表示「不可达」
    unordered_map<long long, int> f;  // 记忆化哈希表：状态编码 → 最小和

    int dfs(int i, int j, int a) {  // dfs：前 i 个数已切成 j 段，当前段的按位与为 a
        if (n - i < m - j) {  // 剩余数字比还需要的段数少，不可能再分出足够多的组
            return inf;  // 返回不可达
        }  // 结束剪枝
        if (j == m) {  // 所有分组都已切完
            return i == n ? 0 : inf;  // 恰好也用完所有数字才是合法方案，返回 0 表示不再产生代价
        }  // 结束终止判断
        a &= nums[i];  // 把当前数字并入当前段的按位与
        if (a < andValues[j]) {  // 按位与只会变小，已经比目标小就不可能再等于目标
            return inf;  // 返回不可达
        }  // 结束剪枝
        long long key = (long long) i << 36 | (long long) j << 32 | a;  // 用 36/32 位分段把 (i, j, a) 编码成一个哈希键
        if (f.contains(key)) {  // 该状态已经算过，直接取缓存
            return f[key];  // 返回记忆化结果
        }  // 结束缓存判断
        int ans = dfs(i + 1, j, a);  // 选择一：把 nums[i] 继续并入当前段，不切段
        if (a == andValues[j]) {  // 当前段按位与正好等于目标，可以在此处切段
            ans = min(ans, dfs(i + 1, j + 1, -1) + nums[i]);  // 选择二：切段，并把 nums[i] 作为新一段的第一个元素
        }  // 结束切段判断
        return f[key] = ans;  // 两种选择取小，同时写入缓存
    }  // 结束 dfs
};  // 类定义结束
