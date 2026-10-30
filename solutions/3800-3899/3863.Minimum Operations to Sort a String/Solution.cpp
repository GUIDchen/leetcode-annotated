// 题目：3863. 将一个字符串排序的最小操作次数（Minimum Operations to Sort a String）
// 思路：分类讨论——已有序返回 0；长度为 2 无法选出真子串返回 -1；最小字符在首位或最大字符在末位 1 次；极值出现在中间 2 次；否则 3 次。
// 时间复杂度：O(n)，各分支都是线性扫描；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(string s) {  // 每次可以排序一个真子串，返回使 s 非降的最少操作次数
        int n = s.size();  // 字符串长度
        bool sorted = true;  // 标记原串是否已经非降序

        for (int i = 1; i < n; ++i) {  // 从左到右检查相邻字符
            if (s[i] < s[i - 1]) {  // 出现逆序对
                sorted = false;  // 说明还没有排好序
                break;  // 已能确定结果，无需继续检查
            }
        }

        if (sorted) {  // 本来就非降序
            return 0;  // 不需要任何操作
        }

        if (n == 2) {  // 长度为 2 时，可选的子串只能覆盖单个字符
            return -1;  // 无法完成排序
        }

        char mn = *min_element(s.begin(), s.end());  // 全局最小字符
        char mx = *max_element(s.begin(), s.end());  // 全局最大字符

        if (s[0] == mn || s[n - 1] == mx) {  // 最小已在首位（排序后缀）或最大已在末位（排序前缀）
            return 1;  // 一次操作即可排好
        }

        for (int i = 1; i < n - 1; ++i) {  // 检查极值字符是否出现在中间位置
            if (s[i] == mn || s[i] == mx) {  // 中间存在极值字符，可先把它排到端点
                return 2;  // 两次操作即可
            }
        }

        return 3;  // 其余情况三次操作足够
    }
};
