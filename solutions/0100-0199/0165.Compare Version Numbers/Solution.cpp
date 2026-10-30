// 题目：165. 比较版本号（Compare Version Numbers）
// 核心思路：双指针同时遍历两串，按 '.' 切段并把每段解析成整数比较；某串缺段时按 0 处理，首个不相等的段决定大小。
// 时间复杂度：O(m + n)，每个字符只被访问一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int compareVersion(string version1, string version2) {  // 按「修订号」逐段比较，返回 -1 / 0 / 1
        int m = version1.size(), n = version2.size();  // 两个版本号字符串的长度
        for (int i = 0, j = 0; i < m || j < n; ++i, ++j) {  // 双指针同步推进；任一串还没读完就继续，缺的段按 0 参与比较
            int a = 0, b = 0;  // 当前这一段的数值，初值 0 表示「空段视为 0」
            while (i < m && version1[i] != '.') {  // 把 version1 的当前段解析成整数
                a = a * 10 + (version1[i++] - '0');  // 逐位累加：左移一位再加新数字，i 自增跳过这一位
            }
            while (j < n && version2[j] != '.') {  // 把 version2 的当前段解析成整数
                b = b * 10 + (version2[j++] - '0');  // 同样的逐位累加，j 自增跳过这一位
            }
            if (a != b) {  // 当前段数值不同，结果已经确定
                return a < b ? -1 : 1;  // 小的返回 -1，大的返回 1
            }
        }  // 所有段都相等，两个版本相同
        return 0;
    }
};