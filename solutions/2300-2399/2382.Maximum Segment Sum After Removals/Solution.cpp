// 题目：2382. 删除操作后的最大子段和（Maximum Segment Sum After Removals）
// 思路：把删除序列倒过来看就是逐个「加回」元素，用并查集把相邻的已激活位置合并成连续段，并实时维护最大段和。
// 时间复杂度：O(n α(n))，n 为数组长度，并查集每次操作近似 O(1)；空间复杂度：O(n)，父指针与段和数组各占 O(n)。
using ll = long long;  // 段和可能超出 int 范围，统一用 64 位整数保存

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> p;  // 并查集父指针：p[i] 指向 i 所在连续段的代表元
    vector<ll> s;  // 段和数组：只有代表元下标上保存的 s 值才是整段的元素和

    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {  // nums：原数组；removeQueries：依次被删除的下标
        int n = nums.size();  // 数组长度，同时也是删除次数
        p.resize(n);  // 父指针数组开到 n 个位置
        for (int i = 0; i < n; ++i) p[i] = i;  // 初始时每个下标自成一个集合
        s.assign(n, 0);  // 段和清零；0 同时充当「该位置尚未被加回」的标记
        vector<ll> ans(n);  // ans[k] 保存第 k 次删除之后的最大子段和
        ll mx = 0;  // 当前所有连续段中的最大段和
        for (int j = n - 1; j; --j) {  // 倒序遍历，第 j 次删除对应把 removeQueries[j] 加回来；j 为 0 时无需处理
            int i = removeQueries[j];  // 本轮要加回的下标
            s[i] = nums[i];  // 激活该位置，先把它看成长度为 1 的独立段
            if (i && s[find(i - 1)]) merge(i, i - 1);  // 左邻居存在且已激活（段和非 0）就并成一段
            if (i < n - 1 && s[find(i + 1)]) merge(i, i + 1);  // 右邻居存在且已激活也并成一段
            mx = max(mx, s[find(i)]);  // 用合并后的整段和刷新全局最大值
            ans[j - 1] = mx;  // 第 j-1 次删除后的答案；最后一格保持 0，对应删空后的空段
        }
        return ans;  // 返回每次删除后的最大子段和
    }

    int find(int x) {  // 并查集查找，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 不是代表元就递归去找，并把路径上的点直接挂到代表元
        return p[x];  // 返回代表元
    }

    void merge(int a, int b) {  // 把 a、b 所在的两个连续段合并
        int pa = find(a), pb = find(b);  // 先分别取到两段的代表元
        p[pa] = pb;  // 把 a 所在段挂到 b 所在段下面
        s[pb] += s[pa];  // 段和累加到新的代表元上
    }
};