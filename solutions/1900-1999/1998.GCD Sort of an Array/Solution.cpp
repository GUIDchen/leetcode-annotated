// 题目：1998. 数组的最大公因数排序（GCD Sort of an Array）
// 思路：把「数值 - 其质因数」用并查集连通，再与升序数组逐位比较：位置不同却不在同一连通块则无法排序。
// 时间复杂度：O(M log log M + n α(M))，M 为最大值；空间复杂度：O(M)，并查集与质因数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> p;  // 并查集父数组：p[x] 表示数值 x 所在连通块的代表元

    bool gcdSort(vector<int>& nums) {  // nums：待判断能否通过 GCD 交换完成排序的数组
        int n = 100010;  // 并查集容量，覆盖题目数值上界 1e5
        p.resize(n);  // 按容量分配父数组
        for (int i = 0; i < n; ++i) p[i] = i;  // 初始化：每个数值自成一个连通块
        int mx = 0;  // 记录数组中的最大数值，用于限制筛法上界
        for (auto num : nums) mx = max(mx, num);  // 扫描一遍求出最大值
        unordered_map<int, vector<int>> f;  // f[v] 保存数值 v 的所有不同质因数
        for (int i = 2; i <= mx; ++i) {  // 埃氏筛的变体：i 从小到大枚举
            if (!f[i].empty()) continue;  // i 已有质因数说明是合数，跳过
            for (int j = i; j <= mx; j += i) f[j].push_back(i);  // i 是质数，把所有倍数 j 的质因数表里加入 i
        }
        for (int i : nums) {  // 遍历原数组中的每个数值
            for (int j : f[i]) p[find(i)] = find(j);  // 数值与其每个质因数合并到同一连通块（可通过 GCD 交换）
        }
        vector<int> s = nums;  // 拷贝一份数组
        sort(s.begin(), s.end());  // 得到目标升序数组
        for (int i = 0; i < nums.size(); ++i) {  // 逐位比较原数组与升序数组
            if (s[i] != nums[i] && find(s[i]) != find(nums[i])) return false;  // 该位置需要换数但两数不连通，说明无法完成排序
        }
        return true;  // 所有位置都满足条件，可以完成排序
    }

    int find(int x) {  // 并查集查找，带路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 递归找到代表元，并把路径上的节点直接挂到代表元上
        return p[x];  // 返回所在连通块的代表元
    }
};