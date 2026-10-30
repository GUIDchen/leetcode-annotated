// 题目：823. 带因子的二叉树（Binary Trees With Factors）
// 思路：排序后用哈希表记录「数值 → 下标」。f[i] 表示以 arr[i] 为根的方案数：枚举因子对，若两个因子都在数组中，就按乘法原理累加 f[j]*f[k]，最后对所有 f 求和。
// 时间复杂度：O(n²)，双重枚举因子；空间复杂度：O(n)，dp 数组与下标哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numFactoredBinaryTrees(vector<int>& arr) {  // arr：可选作节点值的数组
        const int mod = 1e9 + 7;  // 取模常数
        sort(arr.begin(), arr.end());  // 排序，保证因子一定排在倍数前面
        unordered_map<int, int> idx;  // 数值 → 下标，便于 O(1) 判断某个因子是否在数组中
        int n = arr.size();  // 元素个数
        for (int i = 0; i < n; ++i) {  // 建立数值到下标的映射
            idx[arr[i]] = i;  // 记录下标
        }  // 映射建立完毕
        vector<long> f(n, 1);  // f[i]：以 arr[i] 为根的合法二叉树个数，单节点至少有 1 种
        for (int i = 0; i < n; ++i) {  // 依次把每个元素当作根
            int a = arr[i];  // 当前根的值
            for (int j = 0; j < i; ++j) {  // 枚举较小的那个因子
                int b = arr[j];  // 候选因子 b
                if (a % b == 0) {  // b 必须能整除 a
                    int c = a / b;  // 另一个因子 c = a / b
                    if (idx.count(c)) {  // 另一个因子也在数组中才有意义
                        int k = idx[c];  // 它在数组中的下标
                        f[i] = (f[i] + 1l * f[j] * f[k]) % mod;  // 左子树 f[j] 种、右子树 f[k] 种，用乘法原理累加并取模
                    }  // if 结束
                }  // if 结束
            }  // 因子枚举结束
        }  // 根枚举结束
        long ans = 0;  // 总方案数
        for (long v : f) {  // 累加所有可能的根
            ans = (ans + v) % mod;  // 累加并取模
        }  // 遍历结束
        return ans;  // 返回所有合法二叉树的总数
    }  // numFactoredBinaryTrees 方法结束
};  // Solution 类结束