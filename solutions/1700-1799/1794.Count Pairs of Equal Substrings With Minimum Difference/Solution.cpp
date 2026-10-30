// 题目：1794. 统计距离最小的子串对个数（Count Pairs of Equal Substrings With Minimum Difference）
// 思路：相同子串对的距离由首字符起点决定，因此只需为 firstString 的每个字符找到它在 secondString 中最后出现的位置，取最小距离并统计并列个数。
// 时间复杂度：O(n + m)，两遍线性扫描；空间复杂度：O(1)，固定 26 个字母的表。
class Solution {  // 题解类
public:  // 对外接口
    int countQuadruples(string firstString, string secondString) {  // firstString / secondString：两个字符串，返回距离最小的子串对个数
        int last[26] = {0};  // last[c]：字符 c 在 secondString 中最后出现的下标 + 1，0 表示从未出现
        for (int i = 0; i < secondString.size(); ++i) {  // 先统计 secondString 中每个字母的最后位置
            last[secondString[i] - 'a'] = i + 1;  // 存 i + 1：既记下位置，又让 0 天然表示「不存在」
        }  // 统计结束
        int ans = 0, mi = 1 << 30;  // ans：最优距离的方案数；mi：当前最小距离，先设一个足够大的数
        for (int i = 0; i < firstString.size(); ++i) {  // 枚举 firstString 的字符作为子串起点 a
            int j = last[firstString[i] - 'a'];  // 取该字符在 secondString 中的最后位置（1 基）
            if (j) {  // 非 0 说明该字符在 secondString 里出现过，才可能成对
                int t = i - j;  // 距离量度：j 是 1 基下标，等价于 a - b - 1，统一偏移不影响取最小与计数
                if (mi > t) {  // 发现了更小的距离
                    mi = t;  // 更新最小距离
                    ans = 1;  // 之前累计的方案全部作废，重新从 1 计数
                } else if (mi == t) {  // 距离与当前最优并列
                    ++ans;  // 方案数加一
                }  // 分支结束
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回方案个数
    }  // 方法结束
};  // 类定义结束