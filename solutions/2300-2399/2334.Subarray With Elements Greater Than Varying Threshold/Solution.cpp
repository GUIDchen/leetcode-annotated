// 题目：2334. 元素值大于变化阈值的子数组（Subarray With Elements Greater Than Varying Threshold）
// 思路：把元素按值从大到小逐个「激活」，用并查集维护已激活的连续段长度；激活值 v 落在长度 s 的段里时，只要 v > threshold / s，该段就是长度 s 的合法子数组。
// 时间复杂度：O(n log n)，主要是排序（并查集路径压缩后近似 O(1)）；空间复杂度：O(n)。
using pii = pair<int, int>;  // 给「值, 下标」二元组起个别名，便于后面排序

class Solution {  // LeetCode 约定的题解类
public:  // 成员对外可见
    vector<int> p;  // 并查集父指针：p[x] 是 x 的父节点
    vector<int> size;  // size[x] 记录以 x 为根的连续段长度

    int validSubarraySize(vector<int>& nums, int threshold) {  // nums 为数组，threshold 为阈值；返回任一合法子数组长度，没有则 -1
        int n = nums.size();  // 元素个数
        p.resize(n);  // 父指针数组开到 n 个位置
        for (int i = 0; i < n; ++i) p[i] = i;  // 并查集初始化：每个元素各自成段，父节点就是自己
        size.assign(n, 1);  // 每段初始长度都是 1
        vector<pii> arr(n);  // 存放 (元素值, 原下标) 的数组，后面按值排序
        for (int i = 0; i < n; ++i) arr[i] = {nums[i], i};  // 填入每个元素的值与下标
        sort(arr.begin(), arr.end());  // 按值升序排好，之后倒序遍历就是从大到小激活
        vector<bool> vis(n);  // 标记下标是否已被激活，默认全是 false
        for (int j = n - 1; ~j; --j) {  // 从最大值开始倒序激活每个位置；~j 等价于 j 是合法下标
            int v = arr[j].first, i = arr[j].second;  // 取出当前激活的值 v 和它的原下标 i
            if (i && vis[i - 1]) merge(i, i - 1);  // 若左邻下标存在且已激活，就把两段合并成一段
            if (j < n - 1 && vis[i + 1]) merge(i, i + 1);  // 右邻已激活则合并；边界判断沿用原题解写法（取 j < n-1）
            if (v > threshold / size[find(i)]) return size[find(i)];  // 用整数除法判断 v * 段长 > threshold（避免乘法溢出）；成立就返回段长
            vis[i] = true;  // 把当前下标标记为已激活，供左右邻居日后合并
        }  // 倒序激活结束
        return -1;  // 遍历完没有合法子数组，返回 -1
    }  // 主方法结束

    int find(int x) {  // 并查集查找：返回 x 所在集合的根
        if (p[x] != x) p[x] = find(p[x]);  // 不是根就递归找根，同时把路径上的点直接挂到根上（路径压缩）
        return p[x];  // 返回根节点
    }  // find 结束

    void merge(int a, int b) {  // 合并 a、b 所在的两个连续段
        int pa = find(a), pb = find(b);  // 分别找出两段的根
        if (pa == pb) return;  // 已经是同一段，无需合并
        p[pa] = pb;  // 把 a 的根挂到 b 的根下面
        size[pb] += size[pa];  // 新段长度等于两段长度之和
    }  // merge 结束
};  // 类结束