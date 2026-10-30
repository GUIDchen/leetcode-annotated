// 题目：927. 三等分（Three Equal Parts）
// 思路：三段二进制值相等则每段含 1 的个数相同；按 1 的序号定位三段起点，再逐位比较三段直到第三段结束，看三段是否同时走到末尾。
// 时间复杂度：O(n)，定位与逐位比较都是线性；空间复杂度：O(1)，只用常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> threeEqualParts(vector<int>& arr) {  // arr：只含 0 和 1 的数组
        int n = arr.size();  // 数组长度
        int cnt = accumulate(arr.begin(), arr.end(), 0);  // 统计整个数组中 1 的总个数
        if (cnt % 3) return {-1, -1};  // 1 的个数不能被 3 整除，不可能三等分
        if (!cnt) return {0, n - 1};  // 全是 0 时怎样切分都相等，取最左与最右的最短切法
        cnt /= 3;  // 每段应当包含的 1 的个数

        auto find = [&](int x) {  // 局部 lambda：找到第 x 个 1 出现的下标（即该段起点）
            int s = 0;  // 累计已遇到的 1 的个数
            for (int i = 0; i < n; ++i) {  // 从左到右扫描整个数组
                s += arr[i];  // 遇到 1 就累加计数
                if (s == x) return i;  // 数到第 x 个 1，返回它的下标作为该段起点
            }  // for 结束
            return 0;  // 理论上不会走到这里，返回 0 兜底
        };  // lambda 结束
        int i = find(1), j = find(cnt + 1), k = find(cnt * 2 + 1);  // 分别求三段各自第一个 1 的下标，并作为三段的对齐起点
        for (; k < n && arr[i] == arr[j] && arr[j] == arr[k]; ++i, ++j, ++k) {}  // 三段逐位对齐比较；第三段还没到头且三位相同就同时后移
        return k == n ? vector<int>{i - 1, j} : vector<int>{-1, -1};  // 第三段恰好走到末尾说明三段完全相同；否则无解
    }  // 方法结束
};  // 类定义结束